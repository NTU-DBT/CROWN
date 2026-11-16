#include "generation_fixture.hpp"
#include "indexed_runtime_fixture.hpp"
#include "ranking_fixture.hpp"
#include "crown/api/error.hpp"
#include "crown/io/compiler_plan_artifact.hpp"
#include "crown/runtime/queries.hpp"
#include "crown/runtime/session_reoptimization.hpp"

#include <iostream>
#include <limits>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string_view>

namespace {
using namespace crown;
using namespace crown::runtime;
using SignedRows = std::set<std::pair<SetOperation, Row>>;
using Rows = std::set<Row>;

void check(bool condition, std::string_view message) {
  if (!condition) throw std::runtime_error(std::string(message));
}

template<class Action>
void expect_error(Action&& action, std::string_view code) {
  try {
    action();
  } catch (const Error& error) {
    check(error.code() == code, "unexpected CROWN error code");
    return;
  }
  throw std::runtime_error("expected CROWN error was not raised");
}

SessionOptions session_options() {
  SessionOptions result;
  result.delta.mode = DeltaMode::delta;
  result.delta.physical.support.memory_limit_bytes = 64U * 1024U * 1024U;
  return result;
}

reoptimization::Options migration_options() {
  reoptimization::Options result;
  result.forecast = reoptimization::Forecast{1'000'000'000, 1, UINT64_MAX};
  return result;
}

QuerySession::Owner make_session(const PhysicalPlan& plan, const Database& initial) {
  return QuerySession::create_typed(plan, initial, {}, session_options());
}

Rows rows(QuerySession& session) {
  Rows result;
  for (const auto& tuple : session.snapshot().rows)
    check(result.insert(storage::export_row(tuple.values())).second, "duplicate session snapshot row");
  return result;
}

Rows rows(const SessionSnapshot& snapshot) {
  Rows result;
  for (const auto& tuple : snapshot.rows)
    check(result.insert(storage::export_row(tuple.values())).second, "duplicate retained snapshot row");
  return result;
}

SignedRows update(QuerySession& session, const PhysicalSetUpdate& item) {
  io::TransportBatch batch({io::InputEvent{item,
      io::SourcePosition{"independent-queries", item.sequence * 10}}});
  check(session.enqueue(batch) == io::Admission::accepted && batch.empty(), "session input was not admitted");
  check(session.begin_next(), "session input disappeared before execution");
  std::size_t steps = 0;
  while (session.step() != DeltaStep::prepared)
    check(++steps < 10000, "session update exceeded the test step bound");
  session.commit();
  SignedRows result;
  while (auto output = session.next_output())
    check(result.emplace(output->operation, storage::export_row(output->tuple.values())).second,
        "session repeated a signed result row");
  return result;
}

struct Fingerprint {
  io::InputProgress progress;
  Rows result;
  std::string plan;
  std::uint64_t query_owner;
  std::uint64_t native_account;
  std::uint64_t committed_sequence;
};

Fingerprint fingerprint(QuerySession& session) {
  const auto memory = session.accounted_memory_statistics();
  check(memory.has_value(), "live session did not report its native account");
  const auto status = session.status();
  return {session.progress(), rows(session), std::string(session.report_metadata().plan().physical_sha256()),
      session.report_metadata().owner().value, memory->owner, status.committed_sequence};
}

void unchanged(QuerySession& session, const Fingerprint& expected) {
  const auto actual = fingerprint(session);
  check(actual.progress == expected.progress && actual.result == expected.result &&
      actual.plan == expected.plan && actual.query_owner == expected.query_owner &&
      actual.native_account == expected.native_account &&
      actual.committed_sequence == expected.committed_sequence,
      "another query changed during independent session work");
}

Database empty_database(std::size_t tables) {
  Database result;
  result.tables.resize(tables);
  return result;
}

void interleaved_ids_and_snapshot(const PhysicalPlan& plan, const Database& initial) {
  IndependentQueries directory({8, 4U * 1024U * 1024U});
  auto first = make_session(plan, initial);
  auto second = make_session(plan, empty_database(initial.tables.size()));
  first->start();
  second->start();
  const auto first_native = first.get_deleter().account().statistics().owner;
  const auto second_native = second.get_deleter().account().statistics().owner;
  const auto first_id = directory.admit(first);
  const auto second_id = directory.admit(second);
  check(!first && !second && first_native != second_native, "admission merged or retained caller ownership");
  check(directory.size() == 2 && directory.contains(first_id) && directory.contains(second_id),
      "query directory omitted an admitted owner");
  const auto directory_memory = directory.directory_memory();
  check(directory_memory.owner != first_native && directory_memory.owner != second_native &&
      directory_memory.current.requested_bytes > 0,
      "directory metadata shared a session account or was not charged");

  // The C02 fixture has an empty query head: its true Boolean witness is Row{}.
  const Row answer{};
  check(rows(directory.at(first_id)) == Rows{answer} && rows(directory.at(second_id)).empty(),
      "initial independent query states differ");
  check(directory.at(first_id).report_metadata().owner().value !=
      directory.at(second_id).report_metadata().owner().value,
      "independent sessions reused a native query owner ID");

  const PhysicalSetUpdate erase_t{1, TableId{2}, SetOperation::erase, Row{std::int64_t{1}}};
  const PhysicalSetUpdate insert_r{1, TableId{0}, SetOperation::insert, Row{std::int64_t{1}}};
  const PhysicalSetUpdate restore_t{2, TableId{2}, SetOperation::insert, Row{std::int64_t{1}}};
  const PhysicalSetUpdate insert_s{2, TableId{1}, SetOperation::insert,
      Row{std::int64_t{1}, std::int64_t{1}}};
  const PhysicalSetUpdate insert_t{3, TableId{2}, SetOperation::insert, Row{std::int64_t{1}}};
  check(update(directory.at(first_id), erase_t) == SignedRows{{SetOperation::erase, answer}} &&
      rows(directory.at(first_id)).empty(), "first query did not publish its own removal");
  check(update(directory.at(second_id), insert_r).empty() && rows(directory.at(second_id)).empty(),
      "second query inherited the first query's source state");
  check(update(directory.at(first_id), restore_t) == SignedRows{{SetOperation::insert, answer}} &&
      rows(directory.at(first_id)) == Rows{answer}, "first query did not independently restore its result");
  check(update(directory.at(second_id), insert_s).empty() && rows(directory.at(second_id)).empty(),
      "second query advanced from the wrong source state");
  check(update(directory.at(second_id), insert_t) == SignedRows{{SetOperation::insert, answer}} &&
      rows(directory.at(second_id)) == Rows{answer}, "second query did not publish its own result");
  check(directory.at(first_id).progress().sequence == 2 && directory.at(second_id).progress().sequence == 3,
      "query progress was combined across independent sessions");

  IndependentQueries foreign_directory({1, 4U * 1024U * 1024U});
  auto foreign_owner = make_session(plan, empty_database(initial.tables.size()));
  foreign_owner->start();
  const auto foreign_id = foreign_directory.admit(foreign_owner);
  check(foreign_id.value == first_id.value && foreign_id.directory != first_id.directory,
      "foreign-ID fixture did not isolate directory identity");
  check(!directory.contains(foreign_id), "foreign ID was reported as a member");
  expect_error([&] { static_cast<void>(directory.at(foreign_id)); }, "query_id");

  const auto held = directory.at(second_id).snapshot();
  check(held.sequence == 3 && rows(held) == Rows{answer}, "owning snapshot fixture is incorrect");
  const auto held_account = held.rows.account_statistics().owner;
  directory.erase(second_id);
  check(directory.size() == 1 && !directory.contains(second_id) && rows(held) == Rows{answer} &&
      held.rows.account_statistics().owner == held_account,
      "erasing a query invalidated its owning snapshot");
  expect_error([&] { static_cast<void>(directory.at(second_id)); }, "query_id");

  auto replacement = make_session(plan, empty_database(initial.tables.size()));
  replacement->start();
  const auto replacement_id = directory.admit(replacement);
  check(replacement_id.directory == second_id.directory && replacement_id.value > second_id.value &&
      !directory.contains(second_id) && directory.contains(replacement_id),
      "erasure reused a stale query ordinal");
  auto released = directory.release(replacement_id);
  check(released && !directory.contains(replacement_id), "release did not transfer ownership");
  const auto readmitted_id = directory.admit(released);
  check(!released && readmitted_id.value > replacement_id.value && !directory.contains(replacement_id),
      "released query ID aliased after readmission");
  expect_error([&] { static_cast<void>(directory.at(replacement_id)); }, "query_id");
}

void admission_limits(const PhysicalPlan& plan, const Database& initial) {
  IndependentQueries zero_slots({0, 4U * 1024U * 1024U});
  QuerySession::Owner null_owner;
  expect_error([&] { static_cast<void>(zero_slots.admit(null_owner)); }, "query_owner");
  check(!null_owner && zero_slots.size() == 0, "null-owner rejection changed a zero-slot directory");
  auto zero_incoming = make_session(plan, initial);
  zero_incoming->start();
  const auto zero_incoming_account = zero_incoming.get_deleter().account().statistics().owner;
  expect_error([&] { static_cast<void>(zero_slots.admit(zero_incoming)); }, "query_limit");
  check(zero_incoming && zero_incoming.get_deleter().account().statistics().owner == zero_incoming_account &&
      zero_slots.size() == 0,
      "zero-query-slot rejection consumed its incoming owner");

  IndependentQueries count_limited({1, 4U * 1024U * 1024U});
  auto installed = make_session(plan, initial);
  installed->start();
  const auto installed_id = count_limited.admit(installed);
  auto incoming = make_session(plan, initial);
  incoming->start();
  const auto incoming_account = incoming.get_deleter().account().statistics().owner;
  expect_error([&] { static_cast<void>(count_limited.admit(incoming)); }, "query_limit");
  check(incoming && incoming.get_deleter().account().statistics().owner == incoming_account &&
      count_limited.size() == 1 && count_limited.contains(installed_id) &&
      count_limited.at(installed_id).progress().sequence == 0,
      "query-count rejection consumed the incoming owner or changed the installed query");

  std::uint64_t one_node_budget = 0;
  {
    IndependentQueries calibration({2, 4U * 1024U * 1024U});
    auto owner = make_session(plan, initial);
    owner->start();
    static_cast<void>(calibration.admit(owner));
    one_node_budget = calibration.directory_memory().current.requested_bytes;
    check(one_node_budget > 0, "calibration did not charge directory metadata");
  }
  IndependentQueries metadata_limited({2, one_node_budget});
  auto first = make_session(plan, initial);
  first->start();
  const auto first_id = metadata_limited.admit(first);
  check(metadata_limited.directory_memory().current.requested_bytes == one_node_budget,
      "exact one-node metadata budget changed during admission");
  auto second = make_session(plan, initial);
  second->start();
  const auto second_account = second.get_deleter().account().statistics().owner;
  bool limited = false;
  try {
    static_cast<void>(metadata_limited.admit(second));
  } catch (const resource::MemoryFailure& failure) {
    limited = failure.fault() == resource::MemoryFault::limit;
  }
  check(limited && second && second.get_deleter().account().statistics().owner == second_account &&
      metadata_limited.size() == 1 && metadata_limited.contains(first_id) &&
      metadata_limited.at(first_id).progress().sequence == 0 &&
      metadata_limited.directory_memory().current.requested_bytes == one_node_budget,
      "metadata-account exhaustion consumed the incoming owner or altered an admitted session");
}

void failures_are_independent(const PhysicalPlan& plan, const Database& initial) {
  IndependentQueries directory({4, 4U * 1024U * 1024U});
  SessionOptions options = session_options();
  auto malformed = QuerySession::create(plan, std::make_unique<std::istringstream>("{\n"), options);
  auto healthy = make_session(plan, empty_database(initial.tables.size()));
  malformed->start();
  healthy->start();
  const auto malformed_id = directory.admit(malformed);
  const auto healthy_id = directory.admit(healthy);
  bool parse_failed = false;
  try {
    static_cast<void>(directory.at(malformed_id).begin_next());
  } catch (const Error&) {
    parse_failed = true;
  }
  check(parse_failed && directory.at(malformed_id).status().input_failed &&
      directory.at(malformed_id).progress().sequence == 0,
      "malformed input did not remain local to its session");
  expect_error([&] { static_cast<void>(directory.at(malformed_id).begin_next()); }, "input_failed");

  // Keep the same empty-head Boolean witness in the healthy query.
  const Row answer{};
  check(update(directory.at(healthy_id), {1, TableId{0}, SetOperation::insert, Row{std::int64_t{1}}}).empty(),
      "healthy session did not accept input after its neighbor's parse error");
  check(update(directory.at(healthy_id), {2, TableId{1}, SetOperation::insert,
      Row{std::int64_t{1}, std::int64_t{1}}}).empty(), "healthy session lost its second input");
  check(update(directory.at(healthy_id), {3, TableId{2}, SetOperation::insert, Row{std::int64_t{1}}}) ==
      SignedRows{{SetOperation::insert, answer}} && rows(directory.at(healthy_id)) == Rows{answer},
      "healthy session failed to publish after its neighbor's parse error");

  auto budget_owner = make_session(plan, empty_database(initial.tables.size()));
  budget_owner->start();
  const auto account = budget_owner.get_deleter().account();
  const auto budget_id = directory.admit(budget_owner);
  const auto stats = account.statistics();
  const auto remaining = stats.limit_bytes - stats.current.requested_bytes;
  const auto framing = resource::MemoryAccount::allocation_bytes(0, alignof(std::max_align_t));
  check(remaining > framing + 64, "native-budget failure fixture has insufficient headroom");
  auto reserve = account.allocate(static_cast<std::size_t>(remaining - framing - 32),
      alignof(std::max_align_t), resource::MemoryPurpose::scratch);
  bool native_limit = false;
  try {
    static_cast<void>(update(directory.at(budget_id),
        {1, TableId{0}, SetOperation::insert, Row{std::int64_t{1}}}));
  } catch (const resource::MemoryFailure& failure) {
    native_limit = failure.fault() == resource::MemoryFault::limit;
  }
  reserve.reset();
  check(native_limit && directory.at(budget_id).progress().sequence == 0 &&
      directory.at(budget_id).status().committed_sequence == 0 &&
      !directory.at(budget_id).status().input_failed,
      "native memory exhaustion published or poisoned a partial query input");
  check(update(directory.at(healthy_id), {4, TableId{0}, SetOperation::erase, Row{std::int64_t{1}}}) ==
      SignedRows{{SetOperation::erase, answer}} && rows(directory.at(healthy_id)).empty(),
      "another query could not continue after native-budget exhaustion");
}

reoptimization::Status verify_replan(QuerySession& session) {
  session.pause();
  session.request_reoptimization_barrier();
  reoptimization::Status status;
  for (std::size_t step = 0; step < 10000; ++step) {
    status = session.advance_reoptimization(10000);
    if (status.phase == reoptimization::Phase::verified ||
        status.phase == reoptimization::Phase::failed ||
        status.phase == reoptimization::Phase::rejected)
      return status;
  }
  throw std::runtime_error("replan verification exceeded its test step bound");
}

void replan_and_recovery_are_independent(const PhysicalPlan& basis,
    const planner::CandidateSnapshot& family, const PhysicalOptions& physical,
    const Database& initial) {
  IndependentQueries directory({3, 8U * 1024U * 1024U});
  auto switching = make_session(basis, initial);
  auto other = make_session(basis, empty_database(initial.tables.size()));
  auto reference = make_session(basis, initial);
  switching->start();
  other->start();
  reference->start();
  session_file_test::Directory files;
  const auto root = files.file("independent.root");
  switching->enable_generation(root, generation_test::options());
  const auto switching_id = directory.admit(switching);
  const auto other_id = directory.admit(other);

  check(update(directory.at(other_id), {1, TableId{0}, SetOperation::insert, Row{std::int64_t{1}}}).empty() &&
      update(directory.at(other_id), {2, TableId{1}, SetOperation::insert,
          Row{std::int64_t{1}, std::int64_t{1}}}).empty(),
      "other-query state fixture did not commit its independent prefix");
  const auto other_before = fingerprint(directory.at(other_id));
  const auto switching_account = directory.at(switching_id).accounted_memory_statistics()->owner;
  const auto original_owner = directory.at(switching_id).report_metadata().owner().value;

  const auto target_member = family.candidate(1);
  check(target_member.has_value(), "C06 candidate fixture lacks its alternative plan");
  const auto target = planner::lower_tree(target_member->catalog(), target_member->query(),
      target_member->tree(), physical);
  check(target.physical_sha256() != basis.physical_sha256(), "C06 candidate did not change the physical plan");
  directory.at(switching_id).begin_reoptimization(*target_member, migration_options());
  const PhysicalSetUpdate remove_t{1, TableId{2}, SetOperation::erase, Row{std::int64_t{1}}};
  check(update(directory.at(switching_id), remove_t) == update(*reference, remove_t) &&
      rows(directory.at(switching_id)).empty(), "replan preparation changed the switching query output");
  check(verify_replan(directory.at(switching_id)).phase == reoptimization::Phase::verified,
      "real query candidate did not pass its source/result publication barrier");

  auto compiler = resource::MemoryAccount::create(32U * 1024U * 1024U);
  auto artifact = io::CompilerPlanArtifact::prepare(compiler, target);
  const auto publication = directory.at(switching_id).publish_reoptimization(artifact);
  check(publication.phase == reoptimization::Phase::complete &&
      directory.at(switching_id).report_metadata().plan().physical_sha256() == target.physical_sha256() &&
      directory.at(switching_id).accounted_memory_statistics()->owner == switching_account &&
      directory.at(switching_id).report_metadata().owner().value != original_owner,
      "real candidate publication changed the query account or missed the target plan");
  unchanged(directory.at(other_id), other_before);

  auto old_owner = directory.release(switching_id);
  check(old_owner && !directory.contains(switching_id), "switching query release failed before recovery");
  old_owner.reset();
  expect_error([&] { static_cast<void>(directory.at(switching_id)); }, "query_id");

  auto locked = QuerySession::lock_generation_recovery(CompiledProgram::standalone(basis),
      root, generation_test::recovery_options());
  check(locked->has_plan() && !locked->compiler_artifact().empty(),
      "published query did not retain a selected C06 recovery plan");
  auto recovery_compiler = resource::MemoryAccount::create(32U * 1024U * 1024U);
  auto recovered_artifact = io::CompilerPlanArtifact::replay(recovery_compiler, locked->compiler_artifact());
  auto recovered = QuerySession::restore_selected_generation(std::move(locked), recovered_artifact);
  recovered->discard_recovered_output();
  check(recovered->status().committed_sequence == 1 && recovered->progress() == reference->progress() &&
      rows(*recovered) == rows(*reference) &&
      recovered->report_metadata().plan().physical_sha256() == target.physical_sha256(),
      "recovered query did not readmit its published progress/result and plan");
  unchanged(directory.at(other_id), other_before);

  const auto recovered_id = directory.admit(recovered);
  check(!recovered && recovered_id.directory == switching_id.directory &&
      recovered_id.value > switching_id.value && directory.contains(recovered_id),
      "recovered query aliased its released query ID");
  directory.at(recovered_id).start();
  const PhysicalSetUpdate restore_t{2, TableId{2}, SetOperation::insert, Row{std::int64_t{1}}};
  check(update(directory.at(recovered_id), restore_t) == update(*reference, restore_t) &&
      directory.at(recovered_id).progress() == reference->progress() &&
      rows(directory.at(recovered_id)) == rows(*reference),
      "recovered query did not accept its next correct update");
  unchanged(directory.at(other_id), other_before);
}

void backend_case(bool indexed, const c02_test::Fixture& fixture,
    const planner::CandidateSnapshot& family) {
  const auto physical = indexed ? s04_runtime::options() : PhysicalOptions{};
  const auto basis = planner::lower_tree(fixture.catalog, fixture.query,
      family.candidate(0)->tree(), physical);
  interleaved_ids_and_snapshot(basis, fixture.database);
  admission_limits(basis, fixture.database);
  failures_are_independent(basis, fixture.database);
  replan_and_recovery_are_independent(basis, family, physical, fixture.database);
}
} // namespace

int main() {
  try {
    const auto fixture = c02_test::fixture();
    const auto family = c02_test::candidates(fixture);
    check(family.candidate_count() == 3, "independent-query C06 candidate family changed");
    for (const bool indexed : {false, true}) backend_case(indexed, fixture, family);
    std::cout << "X10 independent query directory PASS: both physical backends; interleaved source/progress/account identity, stale/foreign handles, transfer/erase/snapshot lifetimes, count and metadata admission rollback, isolated parse/native-memory failures, real C06 publication/recovery/readmission and next update.\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}
