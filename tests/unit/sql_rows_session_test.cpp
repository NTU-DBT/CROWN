#include "sql_rows_session_fixture.hpp"
#include "index_allocation.hpp"
#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <map>
#include <string>

namespace {
using namespace crown;
using namespace crown::sql_rows_session_test;
using Row = runtime::aggregate::Row; // Resolve the bag oracle row against crown::Row.
using Replacement = runtime::sql_rows::SourceReplacement;

template<std::size_t N>
void log_input(sr::Session& session, const std::array<Replacement, N>& replacements,
    std::uint64_t command, std::uint64_t offset) {
  session.log({command, std::span<const Replacement>(replacements),
      sr::SourcePosition{"rows", offset}, sr::ReaderPosition{offset, command}});
}

template<std::size_t N>
DecodedRowEpoch commit(sr::Session& session, const frontend::SqlRowsProgram& program,
    const std::array<Replacement, N>& replacements, const Changes& expected,
    bool source_changed = true) {
  const auto before = session.state();
  const auto command = before.logged + 1;
  const auto offset = command * 10;
  log_input(session, replacements, command, offset);
  const auto decision = session.decide();
  assert(!decision.rejected && decision.command_sequence == command);
  assert(decision.physical_sequence == before.committed + 1);
  const auto prepared = session.state();
  assert(prepared.logged == command && prepared.disposed == before.disposed + 1);
  assert(prepared.committed == before.committed + 1 && prepared.delivered == before.delivered);
  assert(prepared.output_pending);
  const auto bytes = session.output();
  assert(bytes);
  auto epoch = decode_row_epoch(program, *bytes);
  assert(epoch.generation == prepared.generation && epoch.input_sequence == command);
  assert(epoch.physical_sequence == decision.physical_sequence);
  assert(epoch.changed == source_changed && changes(epoch) == expected);
  assert(session.deliver() && !session.deliver());
  const auto delivered = session.state();
  assert(delivered.delivered == before.delivered + 1 && !delivered.output_pending);
  assert(session.progress().source_positions.at("rows") == offset);
  assert(session.reader_position() == (sr::ReaderPosition{offset, command}));
  return epoch;
}

template<std::size_t N>
sr::Decision reject(sr::Session& session, const std::array<Replacement, N>& replacements,
    sr::RejectReason expected) {
  const auto before = session.state();
  const auto command = before.logged + 1;
  const auto offset = command * 10;
  log_input(session, replacements, command, offset);
  const auto decision = session.decide();
  assert(decision.rejected == expected && decision.command_sequence == command);
  const auto after = session.state();
  assert(after.logged == command && after.disposed == before.disposed + 1);
  assert(after.committed == before.committed && after.delivered == before.delivered);
  assert(!after.pending && !after.output_pending && !session.output());
  assert(session.progress().source_positions.at("rows") == offset);
  assert(session.reader_position() == (sr::ReaderPosition{offset, command}));
  return decision;
}

void check_current(sr::Session& session, const Bag& expected) {
  assert(current_bag(session) == expected);
}

void plain_bag_uint64_retraction(bool indexed) {
  Fixture f(indexed);
  auto session = f.create();
  const std::array<Cell, 4> physical{number(1), number(1), number(9), text("large")};
  const auto large = (std::uint64_t{1} << 63) + 12345;
  const Row output{Value{std::int64_t{9}}};
  const std::array insert{Replacement{TableId{0}, physical, 0, large}};
  commit(session, f.program, insert, Changes{{output, Signed{false, large}}});
  check_current(session, Bag{{output, large}});
  assert(session.source_weight(TableId{0}, physical) == large);

  const std::array retract{Replacement{TableId{0}, physical, large, 0}};
  commit(session, f.program, retract, Changes{{output, Signed{true, large}}});
  check_current(session, {});
  assert(session.source_weight(TableId{0}, physical) == 0);
}

Bag self_join_oracle(const Bag& source) {
  Bag result;
  for (const auto& [left, left_weight] : source) {
    if (!left[1] || std::get<std::int64_t>(*left[1]) <= 0) continue;
    for (const auto& [right, right_weight] : source) {
      if (!right[1] || std::get<std::int64_t>(*right[1]) <= 0 || left[0] != right[0]) continue;
      Row projected{left[2]};
      result[projected] = add(result[projected], multiply(left_weight, right_weight));
    }
  }
  return result;
}

void nullable_projection_and_self_join(bool indexed) {
  constexpr std::string_view sql =
      "SELECT a.x FROM r a JOIN r b ON a.k=b.k WHERE a.id>0 AND b.id>0";
  Fixture f(indexed, bag_schema(), sql);
  auto session = f.create();
  const std::array<Cell, 4> a{number(7), number(1), Cell{}, text("left")};
  const std::array<Cell, 4> b{number(7), number(2), number(5), text("right")};
  Bag source;

  const auto apply = [&](const std::array<Cell, 4>& physical, std::uint64_t next) {
    const Row key = own_row(physical);
    const auto found = source.find(key);
    const auto prior = found == source.end() ? 0 : found->second;
    const auto before = self_join_oracle(source);
    if (next) source[key] = next;
    else source.erase(key);
    const auto after = self_join_oracle(source);
    const std::array edit{Replacement{TableId{0}, physical, prior, next}};
    commit(session, f.program, edit, difference(before, after));
    check_current(session, after);
  };

  apply(a, 2);
  assert((current_bag(session) == Bag{{Row{std::nullopt}, 4}}));
  apply(b, 3);
  assert((current_bag(session) == Bag{{Row{std::nullopt}, 10},
      {Row{Value{std::int64_t{5}}}, 15}}));
  apply(b, 1); // A witness loses two physical copies; both aliases see the weight change.
  assert((current_bag(session) == Bag{{Row{std::nullopt}, 6},
      {Row{Value{std::int64_t{5}}}, 3}}));
  apply(a, 0);
  assert((current_bag(session) == Bag{{Row{Value{std::int64_t{5}}}, 1}}));
}

void distinct_and_exists_zero_crossings(bool indexed) {
  const std::array<Cell, 4> a{number(1), number(1), number(5), text("a")};
  const std::array<Cell, 4> b{number(2), number(2), number(5), text("b")};
  const Row five{Value{std::int64_t{5}}};
  {
    Fixture f(indexed, bag_schema(), "SELECT DISTINCT x FROM r");
    auto session = f.create();
    const std::array add_a{Replacement{TableId{0}, a, 0, 3}};
    commit(session, f.program, add_a, Changes{{five, Signed{false, 1}}});
    check_current(session, Bag{{five, 1}});
    const std::array add_b{Replacement{TableId{0}, b, 0, 4}};
    commit(session, f.program, add_b, {}); // Visible DISTINCT support does not cross zero.
    check_current(session, Bag{{five, 1}});
    const std::array remove_a{Replacement{TableId{0}, a, 3, 0}};
    commit(session, f.program, remove_a, {});
    check_current(session, Bag{{five, 1}});
    const std::array remove_b{Replacement{TableId{0}, b, 4, 0}};
    commit(session, f.program, remove_b, Changes{{five, Signed{true, 1}}});
    check_current(session, {});
  }
  {
    Fixture f(indexed, bag_schema(), "SELECT EXISTS(SELECT FROM r WHERE x>0)");
    auto session = f.create();
    const Row no{Value{false}}, yes{Value{true}};
    check_current(session, Bag{{no, 1}});
    const std::array insert{Replacement{TableId{0}, a, 0, 3}};
    commit(session, f.program, insert,
        Changes{{no, Signed{true, 1}}, {yes, Signed{false, 1}}});
    check_current(session, Bag{{yes, 1}});
    const std::array erase{Replacement{TableId{0}, a, 3, 0}};
    commit(session, f.program, erase,
        Changes{{no, Signed{false, 1}}, {yes, Signed{true, 1}}});
    check_current(session, Bag{{no, 1}});
  }
}

Catalog foreign_key_schema() {
  Catalog catalog{1, {{"p", {{"id", ScalarType::int64, false}}},
      {"c", {{"pid", ScalarType::int64, false}, {"tag", ScalarType::string, true}}}}};
  catalog.tables[0].constraints.push_back(
      UniqueConstraint{"pk", {ColumnId{0}}, ConstraintStatus::enforced});
  catalog.tables[1].constraints.push_back(ForeignKeyConstraint{"fk", {ColumnId{0},},
      TableId{0}, {ColumnId{0}}, ConstraintStatus::enforced});
  return catalog;
}

void net_batch_foreign_key_and_semantic_overflow(bool indexed) {
  {
    Fixture f(indexed, Catalog{1, {{"r", {{"x", ScalarType::int64, true}}}}}, "SELECT x FROM r");
    auto session = f.create();
    const std::array<Cell, 1> physical{number(3)};
    const std::array cancel{Replacement{TableId{0}, physical, 0, 4},
        Replacement{TableId{0}, physical, 4, 0}};
    const auto epoch = commit(session, f.program, cancel, {}, false);
    assert(epoch.rows.empty() && epoch.changed == false);
    assert(!session.output()); // Delivery consumed the exact empty epoch spool.
    check_current(session, {});
    assert(session.source_weight(TableId{0}, physical) == 0);
  }
  {
    Fixture f(indexed, foreign_key_schema(), "SELECT pid FROM c");
    auto session = f.create();
    const std::array<Cell, 1> parent{number(2)};
    const std::array<Cell, 2> child{number(2), text("child")};
    const Row output{Value{std::int64_t{2}}};
    const std::array insert{Replacement{TableId{1}, child, 0, 1},
        Replacement{TableId{0}, parent, 0, 1}};
    commit(session, f.program, insert, Changes{{output, Signed{false, 1}}});
    check_current(session, Bag{{output, 1}});

    const std::array invalid_delete{Replacement{TableId{0}, parent, 1, 0}};
    const auto decision = reject(session, invalid_delete, sr::RejectReason::foreign_key_violation);
    assert(decision.physical_sequence == 1);
    check_current(session, Bag{{output, 1}});
    assert(session.source_weight(TableId{0}, parent) == 1 &&
        session.source_weight(TableId{1}, child) == 1);

    const std::array remove{Replacement{TableId{0}, parent, 1, 0},
        Replacement{TableId{1}, child, 1, 0}};
    commit(session, f.program, remove, Changes{{output, Signed{true, 1}}});
    check_current(session, {});
  }
  {
    Fixture f(indexed, bag_schema(), "SELECT a.x FROM r a JOIN r b ON a.k=b.k");
    auto session = f.create();
    const std::array<Cell, 4> physical{number(1), number(1), number(9), text("overflow")};
    const std::array too_wide{Replacement{TableId{0}, physical, 0, UINT64_MAX}};
    const auto decision = reject(session, too_wide, sr::RejectReason::annotation_overflow);
    assert(decision.physical_sequence == 0 && session.source_weight(TableId{0}, physical) == 0);
    check_current(session, {});

    const std::array retry{Replacement{TableId{0}, physical, 0, 1}};
    const Row output{Value{std::int64_t{9}}};
    commit(session, f.program, retry, Changes{{output, Signed{false, 1}}});
    check_current(session, Bag{{output, 1}});
  }
}

void pending_input_resource_retry_and_reopen() {
  Fixture f;
  const std::array<Cell, 4> physical{number(1), number(1), number(6), text("pending")};
  const std::array edit{Replacement{TableId{0}, physical, 0, 2}};
  {
    auto session = f.create();
    log_input(session, edit, 1, 10);
    bool failed = false;
    {
      s04_alloc::Scope deny(0);
      try { static_cast<void>(session.decide()); }
      catch (const std::bad_alloc&) { failed = true; }
    }
    assert(failed && !session.requires_reopen());
    state(session, 1, 0, 0, 0);
    assert(session.pending_input() && session.logged_reader_position() ==
        (sr::ReaderPosition{10, 1}));
    assert(session.progress().source_positions.empty() && !session.output());
  }
  auto reopened = f.recover();
  state(reopened, 1, 0, 0, 0);
  assert(reopened.pending_input() && reopened.logged_reader_position() ==
      (sr::ReaderPosition{10, 1}));
  const Row output{Value{std::int64_t{6}}};
  const auto decision = reopened.decide();
  assert(!decision.rejected && decision.command_sequence == 1 && decision.physical_sequence == 1);
  const auto bytes = reopened.output();
  assert(bytes);
  const auto epoch = decode_row_epoch(f.program, *bytes);
  assert((changes(epoch) == Changes{{output, Signed{false, 2}}}));
  assert(reopened.deliver());
  state(reopened, 1, 1, 1, 1);
  check_current(reopened, Bag{{output, 2}});
}

void committed_undelivered_reopen_and_exact_retry() {
  Fixture f;
  const std::array<Cell, 4> physical{number(1), number(1), number(8), text("spool")};
  const std::array edit{Replacement{TableId{0}, physical, 0, 3}};
  std::string committed_output;
  {
    auto session = f.create();
    log_input(session, edit, 1, 10);
    assert(!session.decide().rejected);
    state(session, 1, 1, 1, 0);
    committed_output = std::string(*session.output());
  }
  {
    auto session = f.recover();
    state(session, 1, 1, 1, 0);
    assert(session.output() && *session.output() == committed_output);
    const auto epoch = decode_row_epoch(f.program, *session.output());
    assert((changes(epoch) == Changes{{Row{Value{std::int64_t{8}}}, Signed{false, 3}}}));
    assert(session.deliver() && !session.deliver());
    state(session, 1, 1, 1, 1);
  }
  {
    auto session = f.recover();
    state(session, 1, 1, 1, 1);
    assert(!session.output() && !session.deliver());
    assert(frames(contents(f.sink)).size() == 2); // Header and one exact epoch.
    check_current(session, Bag{{Row{Value{std::int64_t{8}}}, 3}});
  }
}

void checkpoint_restore_next_update_and_history_cap(bool indexed) {
  Fixture f(indexed);
  const std::array<Cell, 4> physical{number(1), number(1), number(11), text("reopen")};
  const Row output{Value{std::int64_t{11}}};
  {
    auto session = f.create();
    const std::array insert{Replacement{TableId{0}, physical, 0, 2}};
    commit(session, f.program, insert, Changes{{output, Signed{false, 2}}});
  }
  {
    auto session = f.recover();
    state(session, 1, 1, 1, 1);
    assert(session.source_weight(TableId{0}, physical) == 2);
    assert(session.progress().source_positions.at("rows") == 10);
    assert(session.reader_position() == (sr::ReaderPosition{10, 1}));
    check_current(session, Bag{{output, 2}});
    const auto replay = session.replay_statistics();
    assert(replay.commands == 1 && replay.native_work != 0 &&
        replay.output_work != 0 && replay.source_work.structural_steps != 0);
    assert(session.checkpoint().generation == 2);
  }
  {
    auto session = f.recover();
    state(session, 1, 1, 1, 1);
    assert(session.selected_root().generation == 2);
    assert(session.source_weight(TableId{0}, physical) == 2);
    assert(session.progress().source_positions.at("rows") == 10);
    assert(session.reader_position() == (sr::ReaderPosition{10, 1}));
    check_current(session, Bag{{output, 2}});
    const std::array raise{Replacement{TableId{0}, physical, 2, 5}};
    commit(session, f.program, raise, Changes{{output, Signed{false, 3}}});
    check_current(session, Bag{{output, 5}});
    assert(session.checkpoint().generation == 3);
  }
  {
    auto session = f.recover();
    state(session, 2, 2, 2, 2);
    assert(session.selected_root().generation == 3);
    assert(session.source_weight(TableId{0}, physical) == 5);
    assert(session.progress().source_positions.at("rows") == 20);
    assert(session.reader_position() == (sr::ReaderPosition{20, 2}));
    check_current(session, Bag{{output, 5}});
  }

  Fixture capped(indexed);
  capped.limits.history_generations = 2;
  {
    auto session = capped.create();
    const std::array insert{Replacement{TableId{0}, physical, 0, 1}};
    commit(session, capped.program, insert,
        Changes{{output, Signed{false, 1}}});
    assert(session.checkpoint().generation == 2);
    refused([&] { static_cast<void>(session.checkpoint()); });
    assert(!session.requires_reopen() && session.selected_root().generation == 2);
  }
  {
    auto session = capped.recover();
    assert(session.selected_root().generation == 2);
    refused([&] { static_cast<void>(session.checkpoint()); });
    assert(!session.requires_reopen());
  }
}

void false_decision_and_sink_fail_before_torn_repair() {
  {
    Fixture f;
    const std::array<Cell, 4> physical{number(1), number(1), number(4), text("reject")};
    const std::array valid{Replacement{TableId{0}, physical, 0, 1}};
    const std::array invalid{Replacement{TableId{0}, physical, 9, 0}};
    {
      auto session = f.create();
      commit(session, f.program, valid,
          Changes{{Row{Value{std::int64_t{4}}}, Signed{false, 1}}});
      assert(reject(session, invalid, sr::RejectReason::weight_mismatch).physical_sequence == 1);
    }
    const auto wal_path = generation_file(f, 1);
    const auto valid_wal = contents(wal_path), valid_sink = contents(f.sink);
    auto wal_frames = frames(valid_wal);
    assert(wal_frames.size() == 5);
    const auto last = sr::inspect(f.program, wal_frames.back());
    auto false_reject = std::get<sr::Reject>(last.payload);
    false_reject.reason = sr::RejectReason::source_overflow;
    const auto encoded = sr::encode(f.account, f.program, last.ordinal, false_reject);
    wal_frames.back() = std::string(encoded.bytes());
    const auto false_wal = join(wal_frames, wal_frames.size()) + "T";
    const auto torn_sink = valid_sink + "T";
    put(wal_path, false_wal);
    put(f.sink, torn_sink);
    refused([&] { auto owner = f.recover(); });
    assert(contents(wal_path) == false_wal && contents(f.sink) == torn_sink);

    put(wal_path, valid_wal);
    put(f.sink, valid_sink);
    auto recovered = f.recover();
    state(recovered, 2, 2, 1, 1);
    assert(recovered.progress().source_positions.at("rows") == 20);
    check_current(recovered, Bag{{Row{Value{std::int64_t{4}}}, 1}});
  }

  {
    Fixture f;
    const std::array<Cell, 4> physical{number(1), number(1), number(4), text("sink")};
    const std::array insert{Replacement{TableId{0}, physical, 0, 1}};
    {
      auto session = f.create();
      commit(session, f.program, insert,
          Changes{{Row{Value{std::int64_t{4}}}, Signed{false, 1}}});
    }
    const auto wal_path = generation_file(f, 1);
    const auto valid_wal = contents(wal_path), valid_sink = contents(f.sink);
    auto wal_frames = frames(valid_wal), sink_frames = frames(valid_sink);
    assert(wal_frames.size() == 3 && sink_frames.size() == 2);

    // Replace the valid typed value 4 with 5 and recompute both frame checksums.
    // The independent payload parser confirms the fake epoch is otherwise valid.
    auto fake_epoch = sink_frames[1];
    std::size_t value_offset = sr::frame_header_size + 9 + 24 + 64 + 2 + 8 + 8 + 1 + 1;
    assert(static_cast<unsigned char>(fake_epoch[value_offset - 2]) == 1); // Present.
    assert(static_cast<unsigned char>(fake_epoch[value_offset - 1]) == 0); // int64 tag.
    for (unsigned i = 0; i < 8; ++i)
      fake_epoch[value_offset + i] = static_cast<char>(std::uint64_t{5} >> (8 * i));
    reseal(fake_epoch);
    assert((changes(decode_row_epoch(f.program, fake_epoch)) ==
        Changes{{Row{Value{std::int64_t{5}}}, Signed{false, 1}}}));

    const auto commit_info = sr::inspect(f.program, wal_frames[2]);
    auto committed = std::get<sr::Commit>(commit_info.payload);
    committed.output_bytes = fake_epoch.size();
    committed.output_sha256 = sha256_fixed(fake_epoch);
    const auto fake_commit = sr::encode(f.account, f.program, commit_info.ordinal, committed);
    wal_frames[2] = std::string(fake_commit.bytes());
    const auto false_wal = join(wal_frames, wal_frames.size()) + "T";
    const auto false_sink = sink_frames[0] + fake_epoch + "T";
    put(wal_path, false_wal);
    put(f.sink, false_sink);
    refused([&] { auto owner = f.recover(); });
    assert(contents(wal_path) == false_wal && contents(f.sink) == false_sink);

    put(wal_path, valid_wal);
    put(f.sink, valid_sink);
    auto recovered = f.recover();
    state(recovered, 1, 1, 1, 1);
    check_current(recovered, Bag{{Row{Value{std::int64_t{4}}}, 1}});
  }
}

} // namespace

int main() {
  for (const bool indexed : {false, true}) {
    plain_bag_uint64_retraction(indexed);
    nullable_projection_and_self_join(indexed);
    distinct_and_exists_zero_crossings(indexed);
    net_batch_foreign_key_and_semantic_overflow(indexed);
    checkpoint_restore_next_update_and_history_cap(indexed);
  }
  pending_input_resource_retry_and_reopen();
  committed_undelivered_reopen_and_exact_retry();
  false_decision_and_sink_fail_before_torn_repair();
  std::cout << "SQL rows durable Session bag, replay, signed output, and recovery tests passed\n";
}
