#include "crown/runtime/aggregate.hpp"
#include "aggregate_detail.hpp"
#include "crown/api/error.hpp"
#include <algorithm>
#include <cassert>
#include <map>
#include <utility>
#include <type_traits>

namespace crown::runtime {
namespace {
using namespace aggregate;
using frontend::AggregateOutputKind;
using frontend::SqlKind;
using namespace aggregate::detail;
}  // namespace

struct AggregateRuntime::Data {
  using Rows = std::map<Tuple, std::uint64_t, Less,
      resource::MemoryAllocator<std::pair<const Tuple, std::uint64_t>>>;
  using Groups = std::map<Tuple, Group, Less,
      resource::MemoryAllocator<std::pair<const Tuple, Group>>>;
  resource::MemoryAccount account;
  frontend::AggregateProgram program;
  Options options;
  Items<Cell> input, key, output;
  Items<State> proposed;
  Rows rows;
  Groups groups;
  std::uint64_t sequence = 0;
  bool busy = false;

  Data(const resource::MemoryAccount& owner, frontend::AggregateProgram source, Options requested)
      : account(owner), program(std::move(source)), options(requested),
        input(program.input_types().size(), Cell{}, allocator<Cell>(owner, resource::MemoryPurpose::scratch)),
        key(program.group_columns().size(), Cell{}, allocator<Cell>(owner, resource::MemoryPurpose::scratch)),
        output(program.outputs().size(), Cell{}, allocator<Cell>(owner, resource::MemoryPurpose::scratch)),
        proposed(program.measures().size(), State{}, allocator<State>(owner, resource::MemoryPurpose::scratch)),
        rows(Less{}, allocator<std::pair<const Tuple, std::uint64_t>>(owner, resource::MemoryPurpose::source_counts)),
        groups(Less{}, allocator<std::pair<const Tuple, Group>>(owner, resource::MemoryPurpose::support_metadata)) {}

  // Reused arrays must not retain caller/erased-key string borrows after the
  // synchronous call, including failure. No query state is undone here.
  using Borrows = aggregate::detail::Borrows;
  bool global() const noexcept { return key.empty(); }
  void require_idle() const {
    if (busy) fail("aggregate_busy", "an aggregate batch is already prepared");
  }
  Budget open(std::uint64_t next) const {
    require_idle();
    if (!program.has_input()) fail("aggregate_input", "no-FROM aggregate has no mutable source");
    if (sequence == UINT64_MAX || next != sequence + 1)
      fail("invalid_sequence", "aggregate replacement must use the next epoch");
    Budget budget{options.work_limit, {}}; budget.take(); return budget;
  }
  void validate(std::span<const Cell> values, Budget& budget) const {
    aggregate::detail::validate(program, values, budget);
  }
  void project(std::span<const Cell> values, Budget& budget) {
    aggregate::detail::project(program, values, key, budget);
  }
  const Cell& argument(const frontend::AggregateMeasure& measure, std::span<const Cell> values) const {
    return aggregate::detail::argument(measure, values);
  }
  template<bool CheckInt64 = true>
  void adjust(std::span<State> states, std::span<const Cell> values, std::uint64_t amount,
      bool erase, Budget& budget) const {
    aggregate::detail::adjust<CheckInt64>(program, states, values, amount, erase, budget);
  }
  Tuple render(std::span<const Cell> group_key, std::uint64_t count, std::span<const State> states,
      Budget& budget) {
    return aggregate::detail::render(account, program, output, group_key, count, states, budget);
  }

  Epoch replace(std::uint64_t next, std::uint64_t before, std::uint64_t after, bool capture, Budget& budget) {
    const auto row = rows.find(std::span<const Cell>(input));
    budget.take(); ++budget.metrics.row_probes;
    const auto actual = row == rows.end() ? 0 : row->second;
    if (before != actual) fail("aggregate_weight_mismatch", "aggregate prior row weight differs from committed state");
    Epoch result{next, before != after, capture, {}, {}};
    if (before == after) { result.metrics = budget.metrics; sequence = next; return result; }
    project(input, budget);
    const auto group = groups.find(std::span<const Cell>(key));
    budget.take(); ++budget.metrics.group_probes;
    const auto old_rows = group == groups.end() ? 0 : group->second.rows;
    assert(before <= old_rows);
    const auto base = old_rows - before;
    if (after > options.count_limit - base) fail("aggregate_overflow", "aggregate group count exceeds its signed bigint limit");
    const auto next_rows = base + after;
    if (group == groups.end()) std::fill(proposed.begin(), proposed.end(), State{});
    else std::copy(group->second.values.begin(), group->second.values.end(), proposed.begin());
    adjust(proposed, input, before > after ? before - after : after - before, before > after, budget);

    // New immutable keys and requested output stay private until all checks and
    // both map nodes are funded. Existing-row updates reuse the scratch arrays.
    Tuple row_key, group_key;
    if (row == rows.end() && after) {
      if (program.full_input_group_key() && group != groups.end()) row_key = group->first;
      else row_key = Tuple::copy_of(account, input);
    }
    const Tuple* selected_key = group == groups.end() ? nullptr : &group->first;
    const bool exists_after = global() || next_rows != 0;
    if (!selected_key && exists_after) {
      group_key = program.full_input_group_key() ? row_key : Tuple::copy_of(account, key);
      selected_key = &group_key;
    }
    if (capture) {
      std::optional<Tuple> previous, following;
      if (group != groups.end()) previous = render(group->first.view(), old_rows, group->second.values, budget);
      if (exists_after) following = render(selected_key->view(), next_rows, proposed, budget);
      const bool different = previous.has_value() != following.has_value() ||
          (previous && following && !(*previous == *following));
      if (different) result.output = GroupChange{*selected_key, std::move(previous), std::move(following)};
    }
    typename Rows::node_type new_row;
    typename Groups::node_type new_group;
    if (row == rows.end() && after) new_row = node_for(rows, std::move(row_key), after);
    if (group == groups.end() && exists_after) {
      Group value(account, proposed.size()); value.rows = next_rows;
      std::copy(proposed.begin(), proposed.end(), value.values.begin());
      new_group = node_for(groups, std::move(group_key), std::move(value));
    }
    budget.take();
    if (group == groups.end()) ++budget.metrics.groups_created;
    else if (!exists_after) ++budget.metrics.groups_removed;
    result.metrics = budget.metrics;

    // Publication has no allocation, output formatting or fallible numeric work.
    // All inserted nodes use the destination allocator and a no-throw comparator.
    if (!new_row.empty()) { const auto inserted = rows.insert(std::move(new_row)); assert(inserted.inserted); }
    else if (!after) rows.erase(row);
    else row->second = after;
    if (!new_group.empty()) { const auto inserted = groups.insert(std::move(new_group)); assert(inserted.inserted); }
    else if (!exists_after) groups.erase(group);
    else {
      group->second.rows = next_rows;
      std::copy(proposed.begin(), proposed.end(), group->second.values.begin());
    }
    sequence = next;
    return result;
  }
  void initialize() {
    Budget budget{options.work_limit, {}};
    budget.take(1); budget.take(input.size()); budget.take(key.size());
    budget.take(output.size()); budget.take(proposed.size());
    if (global()) groups.emplace(Tuple::copy_of(account, {}), Group(account, proposed.size()));
    if (!program.has_input()) {
      Borrows borrowed{input, key};
      static_cast<void>(replace(0, 0, 1, false, budget));
    }
  }
};

// One proposal per full logical row/group. No committed table changes until
// commit; destroying preparation only discards detached nodes and owned tuples.
struct AggregateRuntime::PreparedBatch::Data {
  using Owner = AggregateRuntime::Data;
  struct GroupProposal {
    Owner::Groups::iterator position;
    Group after;
    Owner::Groups::node_type inserted;
  };
  struct RowProposal {
    Owner::Rows::iterator position;
    std::uint64_t after, amount;
    bool erase;
    GroupProposal* group;
    Owner::Rows::node_type inserted;
  };
  using GroupProposals = std::map<Tuple, GroupProposal, Less,
      resource::MemoryAllocator<std::pair<const Tuple, GroupProposal>>>;
  using RowProposals = std::map<Tuple, RowProposal, Less,
      resource::MemoryAllocator<std::pair<const Tuple, RowProposal>>>;
  // Declared first for failed-construction unwinding. Explicit close clears
  // proposal entries before releasing this owner; allocators retain the same
  // account independently until their own destruction.
  std::shared_ptr<Owner> owner;
  Budget budget;
  GroupProposals groups;
  RowProposals rows;
  BatchEpoch result;
  bool live = false;

  Data(std::shared_ptr<Owner> target, const NetBatch& batch, Budget allowance)
      : owner(std::move(target)), budget(std::move(allowance)),
        groups(Less{}, allocator<GroupProposals::value_type>(owner->account, resource::MemoryPurpose::scratch)),
        rows(Less{}, allocator<RowProposals::value_type>(owner->account, resource::MemoryPurpose::scratch)),
        result(owner->account, batch.sequence, owner->program, owner->options.capture_changes) {
    Owner::Borrows borrowed{owner->key, {}};
    for (const auto& delta : batch.deltas) touch(delta);
    // Every retraction sees a subbag of the committed bag. Additions then see
    // subbags of the final bag; counts never exceed the old/final group bound.
    adjust_rows(true); adjust_rows(false);
    if (result.captured && !groups.empty()) {
      budget.take(); result.output.reserve(groups.size());
    }
    for (auto& [key, group] : groups) finalize(key, group);
    for (auto& [key, row] : rows) {
      budget.take();
      if (row.position == owner->rows.end() && row.after)
        row.inserted = node_for(owner->rows, key, row.after);
    }
    budget.take();
    result.changed = !rows.empty(); static_cast<Metrics&>(result.metrics) = budget.metrics;
    live = true; // The caller latches owner->busy without any throwing step.
  }
  ~Data() { rollback(); }
  bool active() const noexcept { return live; }

  // Validation/projection, actual tuple copies and actual State preparations
  // spend this same budget. Map/string comparisons retain their actual cost.
  void charge_copy(std::span<const Cell> values) {
    for (const auto& cell : values) {
      budget.take(); ++result.metrics.copied_fields;
      if (cell) if (const auto* text = std::get_if<std::string_view>(&*cell)) {
        budget.take(text->size()); result.metrics.copied_bytes += text->size();
      }
    }
  }
  Tuple copy_key(std::span<const Cell> values) {
    charge_copy(values);
    return Tuple::copy_of(owner->account, values);
  }
  GroupProposal& touch_group(const Tuple& row) {
    owner->project(row.view(), budget);
    const auto key = std::span<const Cell>(owner->key);
    budget.take(); ++budget.metrics.group_probes;
    const auto queued = groups.find(key);
    if (queued != groups.end()) return queued->second;
    budget.take(); ++budget.metrics.group_probes;
    const auto current = owner->groups.find(key);
    Tuple owned;
    if (current != owner->groups.end()) owned = current->first;
    else owned = owner->program.full_input_group_key() ? row : copy_key(key);
    const auto width = owner->program.measures().size();
    budget.take(width); result.metrics.state_fields_prepared += width;
    Group after = current == owner->groups.end() ? Group(owner->account, width)
        : Group(owner->account, current->second);
    budget.take();
    return groups.emplace(std::move(owned), GroupProposal{current, std::move(after), {}}).first->second;
  }
  void touch(const RowDelta& delta) {
    budget.take();
    owner->validate(delta.values, budget);
    if (!delta.magnitude) fail("invalid_aggregate_batch", "aggregate bag deltas must be nonzero");
    budget.take(); ++budget.metrics.row_probes;
    if (rows.find(delta.values) != rows.end())
      fail("invalid_aggregate_batch", "aggregate bag deltas must have unique complete row keys");
    budget.take(); ++budget.metrics.row_probes;
    const auto current = owner->rows.find(delta.values);
    const auto before = current == owner->rows.end() ? 0 : current->second;
    std::uint64_t after;
    if (delta.erase) {
      if (delta.magnitude > before)
        fail("aggregate_weight_mismatch", "aggregate retraction exceeds its committed logical row weight");
      after = before - delta.magnitude;
    } else {
      if (delta.magnitude > UINT64_MAX - before)
        fail("aggregate_overflow", "aggregate logical row weight exceeds uint64");
      after = before + delta.magnitude;
    }
    if (after > owner->options.count_limit)
      fail("aggregate_overflow", "aggregate logical row exceeds its group count bound");
    auto key = current == owner->rows.end() ? copy_key(delta.values) : current->first;
    auto& group = touch_group(key);
    budget.take();
    rows.emplace(std::move(key), RowProposal{current, after, delta.magnitude, delta.erase, &group, {}});
  }
  void adjust_rows(bool erasing) {
    for (const auto& [key, row] : rows) {
      budget.take();
      if (row.erase != erasing) continue;
      auto& group = row.group->after;
      if (erasing) { assert(row.amount <= group.rows); group.rows -= row.amount; }
      else {
        if (row.amount > owner->options.count_limit - group.rows)
          fail("aggregate_overflow", "aggregate final group count exceeds its signed bigint limit");
        group.rows += row.amount;
      }
      owner->adjust<false>(group.values, key.view(), row.amount, erasing, budget);
    }
  }
  Tuple render(const Tuple& key, const Group& group) {
    auto values = owner->render(key.view(), group.rows, group.values, budget);
    // render owns the copy already; debit its fields/bytes before it can escape
    // preparation. A denial destroys it with all other private proposals.
    charge_copy(values.view());
    return values;
  }
  void finalize(const Tuple& key, GroupProposal& group) {
    budget.take(); ++result.metrics.groups_finalized;
    aggregate::detail::check_sums(owner->program, group.after.values, budget);
    const bool exists_after = owner->global() || group.after.rows != 0;
    if (result.captured) {
      std::optional<Tuple> before, after;
      if (group.position != owner->groups.end()) before = render(group.position->first, group.position->second);
      if (exists_after) after = render(key, group.after);
      const bool different = before.has_value() != after.has_value() ||
          (before && after && !(*before == *after));
      if (different) { budget.take(); result.output.push_back({key, std::move(before), std::move(after)}); }
    }
    if (group.position == owner->groups.end() && exists_after) {
      budget.take();
      group.inserted = node_for(owner->groups, key, std::move(group.after));
      ++budget.metrics.groups_created;
    } else if (!exists_after) ++budget.metrics.groups_removed;
  }
  BatchEpoch commit() noexcept {
    assert(live && owner->busy);
    for (auto& [key, row] : rows) {
      static_cast<void>(key);
      if (!row.inserted.empty()) {
        const auto added = owner->rows.insert(std::move(row.inserted)); assert(added.inserted);
      } else if (!row.after) owner->rows.erase(row.position);
      else row.position->second = row.after;
    }
    for (auto& [key, group] : groups) {
      static_cast<void>(key);
      if (!group.inserted.empty()) {
        const auto added = owner->groups.insert(std::move(group.inserted)); assert(added.inserted);
      } else if (!owner->global() && !group.after.rows) owner->groups.erase(group.position);
      else {
        group.position->second.rows = group.after.rows;
        assert(group.position->second.values.get_allocator() == group.after.values.get_allocator());
        group.position->second.values.swap(group.after.values);
      }
    }
    // No allocation, arithmetic, output or admission remains between table
    // publication and this one contiguous epoch advance.
    owner->sequence = result.sequence;
    rows.clear(); groups.clear();
    owner->busy = false; live = false; owner.reset();
    return std::move(result);
  }
  void rollback() noexcept {
    if (!live) return;
    rows.clear(); groups.clear();
    owner->busy = false; live = false; owner.reset();
  }
};

aggregate::BatchEpoch::BatchEpoch(const resource::MemoryAccount& account, std::uint64_t next,
    frontend::AggregateProgram source, bool capture)
    : sequence(next), captured(capture), program(std::move(source)),
      output(resource::OwnerAllocator<GroupChange>(account, resource::MemoryPurpose::output_buffer)) {}
static_assert(std::is_nothrow_move_constructible_v<aggregate::BatchEpoch>);

AggregateRuntime::AggregateRuntime(std::shared_ptr<Data> value) noexcept : data_(std::move(value)) {}
AggregateRuntime AggregateRuntime::create_into(const resource::MemoryAccount& account,
    frontend::AggregateProgram program, Options options) {
  if (!program) fail("invalid_aggregate_program", "aggregate runtime requires a factory-produced program");
  if (options.count_limit > static_cast<std::uint64_t>(INT64_MAX))
    fail("invalid_options", "aggregate count limit exceeds signed bigint");
  auto value = resource::make_accounted_shared<Data>(account, resource::MemoryPurpose::table_state,
      account, std::move(program), options);
  value->initialize(); return AggregateRuntime(std::move(value));
}
AggregateRuntime::AggregateRuntime(frontend::AggregateProgram program, Options options)
    : AggregateRuntime(create_into(resource::MemoryAccount::create(options.memory_limit_bytes), std::move(program), options)) {}
AggregateRuntime::AggregateRuntime(AggregateRuntime&&) noexcept = default;
AggregateRuntime& AggregateRuntime::operator=(AggregateRuntime&&) noexcept = default;
AggregateRuntime::~AggregateRuntime() = default;
AggregateRuntime::Data& AggregateRuntime::data() const {
  if (!data_) fail("invalid_aggregate_runtime", "aggregate runtime handle is empty");
  return *data_;
}
const frontend::AggregateProgram& AggregateRuntime::program() const & { return data().program; }
std::uint64_t AggregateRuntime::sequence() const { return data().sequence; }
aggregate::Epoch AggregateRuntime::apply(const aggregate::Update& update) {
  auto& value = data(); auto budget = value.open(update.sequence); Data::Borrows borrowed{value.input, value.key};
  if (update.values.size() != value.input.size()) fail("invalid_aggregate_row", "aggregate input has the wrong arity");
  for (std::size_t i = 0; i < update.values.size(); ++i)
    value.input[i] = update.values[i] ? Cell{storage::borrow_scalar(*update.values[i])} : std::nullopt;
  value.validate(value.input, budget);
  return value.replace(update.sequence, update.before, update.after, value.options.capture_changes, budget);
}
aggregate::Epoch AggregateRuntime::apply_weighted(std::uint64_t next, storage::TupleValuesView values,
    std::uint64_t before, std::uint64_t after) {
  auto& value = data(); auto budget = value.open(next); Data::Borrows borrowed{value.input, value.key};
  if (values.size() != value.input.size()) fail("invalid_aggregate_row", "weighted aggregate input has the wrong arity");
  for (std::size_t i = 0; i < values.size(); ++i) value.input[i] = values[i];
  value.validate(value.input, budget);
  return value.replace(next, before, after, value.options.capture_changes, budget);
}
AggregateRuntime::PreparedBatch AggregateRuntime::prepare_batch(const aggregate::NetBatch& batch) {
  auto& value = data(); auto budget = value.open(batch.sequence);
  auto prepared = resource::make_accounted_unique<PreparedBatch::Data>(value.account,
      resource::MemoryPurpose::scratch, data_, batch, std::move(budget));
  value.busy = true;
  return PreparedBatch(std::move(prepared));
}
AggregateRuntime::PreparedBatch::PreparedBatch(resource::AccountedUnique<Data> value) noexcept
    : data_(std::move(value)) {}
AggregateRuntime::PreparedBatch::PreparedBatch(PreparedBatch&&) noexcept = default;
AggregateRuntime::PreparedBatch& AggregateRuntime::PreparedBatch::operator=(PreparedBatch&&) noexcept = default;
AggregateRuntime::PreparedBatch::~PreparedBatch() = default;
AggregateRuntime::PreparedBatch::Data& AggregateRuntime::PreparedBatch::data() const {
  if (!data_ || !data_->active()) fail("invalid_aggregate_batch", "aggregate batch token is closed or moved from");
  return *data_;
}
bool AggregateRuntime::PreparedBatch::active() const noexcept { return data_ && data_->active(); }
const aggregate::BatchEpoch& AggregateRuntime::PreparedBatch::preview() const & { return data().result; }
aggregate::BatchEpoch AggregateRuntime::PreparedBatch::commit() {
  auto result = data().commit(); data_.reset(); return result;
}
void AggregateRuntime::PreparedBatch::rollback() noexcept { data_.reset(); }
aggregate::Snapshot AggregateRuntime::snapshot(aggregate::SnapshotLimits limits) const {
  auto& value = data(); value.require_idle(); Budget budget{limits.work_limit, {}}; budget.take();
  if (value.groups.size() > limits.groups) fail("aggregate_result_limit", "aggregate snapshot group limit exceeded");
  Snapshot result(value.account, value.sequence, value.program); result.groups.reserve(value.groups.size());
  for (const auto& [key, group] : value.groups)
    result.groups.push_back({key, value.render(key.view(), group.rows, group.values, budget)});
  return result;
}
resource::MemoryStatistics AggregateRuntime::accounted_memory_statistics() const { return data().account.statistics(); }
void AggregateRuntime::check_invariants() const {
  auto& value = data(); value.require_idle(); Data::Borrows borrowed{value.key, {}}; Budget budget{{}, {}};
  Data::Groups expected(Less{}, allocator<std::pair<const Tuple, Group>>(value.account, resource::MemoryPurpose::scratch));
  if (value.global()) expected.emplace(Tuple::copy_of(value.account, {}, resource::MemoryPurpose::scratch),
      Group(value.account, value.proposed.size(), resource::MemoryPurpose::scratch));
  if (!value.program.has_input() && (value.rows.size() != 1 || value.rows.begin()->first.size() != 0 || value.rows.begin()->second != 1))
    fail("aggregate_invariant", "no-FROM input must remain one implicit nullary row");
  for (const auto& [row, weight] : value.rows) {
    if (!weight || weight > value.options.count_limit) fail("aggregate_invariant", "stored aggregate input weight is invalid");
    const auto cells = row.view(); value.validate(cells, budget); value.project(cells, budget);
    auto group = expected.find(std::span<const Cell>(value.key));
    if (group == expected.end()) {
      auto key = value.program.full_input_group_key() ? row : Tuple::copy_of(value.account, value.key, resource::MemoryPurpose::scratch);
      group = expected.emplace(std::move(key), Group(value.account, value.proposed.size(), resource::MemoryPurpose::scratch)).first;
    }
    if (weight > value.options.count_limit - group->second.rows)
      fail("aggregate_invariant", "stored aggregate group exceeds its count bound");
    group->second.rows += weight;
    // Diagnostic recomputation can visit cancelling rows in any key order.
    // Only the completed SQL sum needs to fit its declared result type.
    const auto measures = value.program.measures();
    for (std::size_t i = 0; i < measures.size(); ++i) {
      const auto& cell = value.argument(measures[i], cells);
      if (!cell) continue;
      auto& state = group->second.values[i];
      state.count += weight;
      if (measures[i].sum) state.sum.replace(std::get<std::int64_t>(*cell), weight, false);
    }
  }
  if (expected.size() != value.groups.size()) fail("aggregate_invariant", "aggregate group membership differs from input");
  for (const auto& [key, group] : expected) {
    const auto actual = value.groups.find(key);
    if (actual == value.groups.end() || actual->second.rows != group.rows || actual->second.values.size() != group.values.size())
      fail("aggregate_invariant", "aggregate group shape/count differs from input");
    for (std::size_t i = 0; i < group.values.size(); ++i)
      if ((value.program.measures()[i].int64_sum && !actual->second.values[i].sum.fits_int64()) ||
          actual->second.values[i].count != group.values[i].count ||
          actual->second.values[i].sum.value() != group.values[i].sum.value())
        fail("aggregate_invariant", "aggregate sufficient statistics differ from input");
  }
  value.account.check_invariants();
}
}  // namespace crown::runtime
