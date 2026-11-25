#include "crown/runtime/sql_aggregate.hpp"
#include "aggregate_detail.hpp"
#include "sql_cold_rebuild.hpp"
#include "sql_tuple_table.hpp"
#include "crown/runtime/keyed_engine.hpp"
#include <algorithm>
#include <cassert>
#include <map>
#include <type_traits>
#include <utility>

namespace crown::runtime {
namespace {
using namespace aggregate;
using namespace aggregate::detail;
// Hash table of groups (sql_tuple_table.hpp); snapshots sort by key.
using Groups = sql_detail::TupleTable<Group>;
constexpr auto absent = Groups::npos;
}  // namespace

namespace {
// A touched group: committed id at preparation (or absent) and its proposal.
struct GroupProposal {
  std::size_t position;
  Group after;
};
using TouchedGroups = sql_detail::TouchedSet<GroupProposal>;
}  // namespace

struct SqlAggregateRuntime::Data {
  resource::MemoryAccount account;
  frontend::SqlAggregateProgram program;
  sql_aggregate::Options options;
  SqlRowsRuntime source;
  Items<Cell> input, key, output;
  Groups groups; // Group count/sufficient statistics only; no joined-row ledger.
  std::uint64_t sequence = 0;
  bool busy = false;
  bool fused = false;  // Options::fused on a fused-capable source
  // The previous batch's touched set (empty, capacity kept) for the next.
  std::optional<TouchedGroups> spare_groups;
  TouchedGroups take_groups() {
    if (!spare_groups) return TouchedGroups(account);
    auto value = std::move(*spare_groups); spare_groups.reset(); return value;
  }
  void give_groups(TouchedGroups& value) noexcept {
    value.clear();
    if (!spare_groups) spare_groups.emplace(std::move(value));
  }

  Data(const resource::MemoryAccount& receiver, frontend::SqlAggregateProgram original,
      const FreeConnexTree& tree, const PhysicalOptions& physical, sql_aggregate::Options requested)
      : account(receiver), program(frontend::SqlAggregateProgram::freeze(receiver, original)), options(requested),
        source(SqlRowsRuntime::create_into(receiver, program.source_program(), tree, physical, requested.source)),
        input(program.inputs().size(), Cell{}, allocator<Cell>(receiver, resource::MemoryPurpose::scratch)),
        key(program.kernel_program().group_columns().size(), Cell{}, allocator<Cell>(receiver, resource::MemoryPurpose::scratch)),
        output(program.kernel_program().outputs().size(), Cell{}, allocator<Cell>(receiver, resource::MemoryPurpose::scratch)),
        groups(receiver, resource::MemoryPurpose::support_metadata) {
    options.memory_limit_bytes = account.statistics().limit_bytes;
    options.source.native.memory_limit_bytes = options.memory_limit_bytes;
    fused = options.fused && source.fused_available();
    Budget budget{options.group_work_limit,{}};initialize(budget);
  }
  Data(const resource::MemoryAccount& receiver,frontend::SqlAggregateProgram original,SqlRowsRuntime child,
      sql_aggregate::Options requested,std::uint64_t initial_sequence)
      : account(receiver), program(frontend::SqlAggregateProgram::freeze(receiver, original)), options(requested),
        source(std::move(child)),
        input(program.inputs().size(), Cell{}, allocator<Cell>(receiver, resource::MemoryPurpose::scratch)),
        key(program.kernel_program().group_columns().size(), Cell{}, allocator<Cell>(receiver, resource::MemoryPurpose::scratch)),
        output(program.kernel_program().outputs().size(), Cell{}, allocator<Cell>(receiver, resource::MemoryPurpose::scratch)),
        groups(receiver, resource::MemoryPurpose::support_metadata),
        sequence(initial_sequence) {
    options.memory_limit_bytes=account.statistics().limit_bytes;
    options.source.native.memory_limit_bytes=options.memory_limit_bytes;
  }
  bool global() const noexcept { return key.empty(); }
  void require_idle() const {
    if (busy) fail("sql_aggregate_busy", "a composed aggregate batch is already prepared");
  }
  Budget open(std::uint64_t next) const {
    require_idle();
    if (sequence == UINT64_MAX || next != sequence + 1)
      fail("invalid_sequence", "composed SQL batch must use the next epoch");
    Budget budget{options.group_work_limit, {}}; budget.take(); return budget;
  }
  // The opaque compiler checked complete-head coverage, exact SqlTypes and
  // nullable/default encoding. These fields come only from this owner's child
  // source token; no public row, metadata DTO or weight-bypass enters this port.
  void decode(storage::RowView native, Budget& budget) {
    if (native.size() != program.native_fields())
      fail("sql_aggregate_contract", "genuine native fact differs from its bound decode width");
    const auto fields = program.inputs();
    const auto constants = program.source_program().initial_values();
    for (std::size_t i = 0; i < fields.size(); ++i) {
      budget.take(); ++budget.metrics.input_fields;
      if (const auto* field = std::get_if<frontend::SqlRowsResultField>(&fields[i].value)) {
        if (field->presence) {
          budget.take();
          if (!std::get<bool>(native[*field->presence])) { input[i].reset(); continue; }
        }
        input[i] = native[field->payload];
      } else input[i] = constants[std::get<frontend::ExpressionId>(fields[i].value).value];
      if (input[i]) if (const auto* text = std::get_if<std::string_view>(&*input[i])) {
        budget.take(text->size()); budget.metrics.input_bytes += text->size();
      }
    }
  }
  void initialize(Budget& budget) {
    const auto& kernel = program.kernel_program();
    if (!kernel.has_input() || kernel.input_types().size() != input.size())
      fail("sql_aggregate_contract", "composed kernel must have its genuine mutable synthetic input");
    budget.take(); budget.take(input.size()); budget.take(key.size()); budget.take(output.size());
    if (global()) {
      budget.take(kernel.measures().size());
      auto key = Tuple::copy_of(account, {});
      Group group(account, kernel.measures().size());
      groups.reserve(1);
      groups.insert(std::move(key), std::move(group), sql_detail::hash_cells({}));
    }
    // Weighted constant routes already have their authentic 0/1 root at epoch
    // zero. Bootstrap only that compiler-authenticated immutable nullary source;
    // this is construction, never a synthetic operational batch or W04 change.
    if (const auto weight = program.static_source_weight()) {
      budget.take();
      if (*weight > 1 || source.root_weight().value != *weight)
        fail("sql_aggregate_contract", "static source weight differs from its genuine native root");
      if (*weight) {
        if (!input.empty() || !global())
          fail("sql_aggregate_contract", "nonempty static source requires a nullary global kernel");
        if (*weight > options.count_limit)
          fail("aggregate_overflow", "static aggregate count exceeds its signed bigint limit");
        auto& group = groups.at(0).value; group.rows = *weight;
        aggregate::detail::adjust<false>(kernel, group.values, input, *weight, false, budget);
        check_sums(kernel, group.values, budget);
      }
    }
  }
};

struct SqlAggregateRuntime::PreparedBatch::Data {
  using Proposal = GroupProposal;
  // Touched groups, finalized and published in key order.
  using Touched = TouchedGroups;
  // Owner is first and dies last, including failed construction. Child rollback
  // and proposal/output teardown never outlive the complete outer owner.
  std::shared_ptr<SqlAggregateRuntime::Data> owner;
  // The child token; empty for a fused batch, whose open state lives in the
  // owner's source (SqlRowsRuntime::prepare_fused..commit_fused).
  std::optional<SqlRowsRuntime::PreparedBatch> source;
  Budget budget;
  Touched groups;
  sql_aggregate::Epoch result;
  bool live = false;

  Data(std::shared_ptr<SqlAggregateRuntime::Data> target, SqlRowsRuntime::PreparedBatch child, Budget allowance)
      : owner(std::move(target)), source(std::move(child)), budget(std::move(allowance)),
        groups(owner->take_groups()),
        result(owner->account, source->sequence(), owner->program, owner->options.capture_changes) {
    Borrows borrowed{owner->input, owner->key};
    const auto facts = source->native_bag_delta_preview();
    if (!facts) fail("sql_aggregate_contract", "private source did not capture its genuine native bag facts");
    result.changed = source->changed(); result.group_changed = !facts->empty();
    result.source_work = source->source_work(); result.native = source->native_preview();
    contribute(*facts, true); contribute(*facts, false);
    finish_preparation();
    live = true; // Caller sets owner->busy after this constructor returns.
  }
  struct FusedTag {};
  // Fused batch: each head tuple change folds into its group while the
  // source stages it (Options::fused).
  Data(std::shared_ptr<SqlAggregateRuntime::Data> target, const sql_rows::NetBatch& batch, Budget allowance, FusedTag)
      : owner(std::move(target)), budget(std::move(allowance)), groups(owner->take_groups()),
        result(owner->account, batch.sequence, owner->program, owner->options.capture_changes) {
    Borrows borrowed{owner->input, owner->key};
    // group_changed reports net head-tuple changes. Edits of one direction
    // move every head count monotonically, so any change is net; a batch with
    // both decreasing and increasing edits keeps a per-head ledger instead.
    bool decreasing = false, increasing = false;
    for (const auto& edit : batch.replacements) {
      decreasing |= edit.after < edit.before; increasing |= edit.after > edit.before;
    }
    struct Sink final : keyed::WeightSink {
      Data& self;
      bool mixed, changed = false;
      struct Entry { Tuple key; std::uint64_t hash, first, last; };
      std::vector<Entry> ledger;
      std::vector<Cell> cells;
      Sink(Data& data, bool both) : self(data), mixed(both) {}
      void change(storage::RowView values, std::uint64_t before, std::uint64_t after) override {
        if (before == after) return;
        if (mixed) note(values, before, after); else changed = true;
        self.contribute_change(values, before, after);
      }
      void note(storage::RowView values, std::uint64_t before, std::uint64_t after) {
        cells.assign(values.cells().begin(), values.cells().end());
        const auto hash = sql_detail::hash_cells(cells);
        for (auto& entry : ledger)
          if (entry.hash == hash && std::ranges::equal(entry.key.view(), cells)) { entry.last = after; return; }
        ledger.push_back({Tuple::copy_of(self.owner->account, cells), hash, before, after});
      }
      bool net() const {
        if (!mixed) return changed;
        return std::ranges::any_of(ledger, [](const Entry& entry) { return entry.first != entry.last; });
      }
    } sink(*this, decreasing && increasing);
    try {
      result.changed = owner->source.prepare_fused(batch, sink);
      result.group_changed = sink.net();
      result.native.sequence = batch.sequence; result.native.changed = result.group_changed;
      finish_preparation();
    } catch (...) {
      owner->source.rollback_fused(); owner->give_groups(groups); throw;
    }
    live = true;
  }
  void finish_preparation() {
    groups.sort();
    if (result.captured && !groups.empty()) { budget.take(); result.output.reserve(groups.size()); }
    std::size_t created = 0;
    for (auto& item : groups.items()) created += finalize(item.key, item.payload);
    owner->groups.reserve(created);  // publication inserts without allocating
    budget.take(); static_cast<aggregate::Metrics&>(result.metrics) = budget.metrics;
  }
  ~Data() {
    if (live) {
      owner->give_groups(groups);
      if (source) source->rollback(); else owner->source.rollback_fused();
      owner->busy = false;
    }
  }
  // One native head-tuple count change (fused batches), as contribute().
  void contribute_change(storage::RowView values, std::uint64_t before, std::uint64_t after) {
    budget.take(); ++result.metrics.native_deltas;
    const bool erasing = after < before;
    const auto amount = erasing ? before - after : after - before;
    owner->decode(values, budget);
    auto& group = touch().after;
    if (erasing) {
      if (amount > group.rows) fail("sql_aggregate_contract", "genuine native retraction exceeds its committed group");
      group.rows -= amount;
    } else {
      if (amount > owner->options.count_limit - group.rows)
        fail("aggregate_overflow", "final aggregate group count exceeds its signed bigint limit");
      group.rows += amount;
    }
    aggregate::detail::adjust<false>(owner->program.kernel_program(), group.values, owner->input, amount, erasing, budget);
  }
  void charge_copy(std::span<const Cell> cells) {
    for (const auto& cell : cells) {
      budget.take(); ++result.metrics.copied_fields;
      if (cell) if (const auto* text = std::get_if<std::string_view>(&*cell)) {
        budget.take(text->size()); result.metrics.copied_bytes += text->size();
      }
    }
  }
  Proposal& touch() {
    aggregate::detail::project(owner->program.kernel_program(), owner->input, owner->key, budget);
    const auto key = std::span<const Cell>(owner->key);
    const auto hash = sql_detail::hash_cells(key);
    budget.take(); ++budget.metrics.group_probes;
    if (auto* queued = groups.find(0, key, hash)) return queued->payload;
    budget.take(); ++budget.metrics.group_probes;
    const auto current = owner->groups.find(key, hash);
    Tuple owned;
    if (current != absent) owned = owner->groups.at(current).key;
    else { charge_copy(key); owned = Tuple::copy_of(owner->account, key); }
    const auto width = owner->program.kernel_program().measures().size();
    budget.take(width); result.metrics.state_fields_prepared += width;
    Group after = current == absent ? Group(owner->account, width)
        : Group(owner->account, owner->groups.at(current).value);
    budget.take();
    return groups.add(0, std::move(owned), hash, Proposal{current, std::move(after)}).payload;
  }
  void contribute(std::span<const weighted::BagDelta> facts, bool erasing) {
    for (const auto& fact : facts) {
      budget.take();
      if (fact.change.negative != erasing) continue;
      budget.take(); ++result.metrics.native_deltas;
      const auto amount = fact.change.magnitude.value;
      if (!amount) fail("sql_aggregate_contract", "genuine native bag fact has a zero delta");
      owner->decode(fact.tuple.values(), budget);
      auto& group = touch().after;
      if (erasing) {
        if (amount > group.rows)
          fail("sql_aggregate_contract", "genuine native retraction exceeds its committed group");
        group.rows -= amount;
      } else {
        if (amount > owner->options.count_limit - group.rows)
          fail("aggregate_overflow", "final aggregate group count exceeds its signed bigint limit");
        group.rows += amount;
      }
      aggregate::detail::adjust<false>(owner->program.kernel_program(), group.values, owner->input,
          amount, erasing, budget);
    }
  }
  Tuple render(const Tuple& key, const Group& group) {
    auto tuple = aggregate::detail::render(owner->account, owner->program.kernel_program(), owner->output,
        key.view(), group.rows, group.values, budget);
    charge_copy(tuple.view()); return tuple;
  }
  // True when publication inserts a new group.
  bool finalize(const Tuple& key, Proposal& proposal) {
    budget.take(); ++result.metrics.groups_finalized;
    check_sums(owner->program.kernel_program(), proposal.after.values, budget);
    const bool exists_after = owner->global() || proposal.after.rows != 0;
    if (result.captured) {
      std::optional<Tuple> before, after;
      if (proposal.position != absent) before = render(key, owner->groups.at(proposal.position).value);
      if (exists_after) after = render(key, proposal.after);
      if (before.has_value() != after.has_value() || (before && after && !(*before == *after))) {
        budget.take(); result.output.push_back({key, std::move(before), std::move(after)});
      }
    }
    if (proposal.position == absent && exists_after) {
      budget.take(); ++budget.metrics.groups_created;
      return true;
    }
    if (!exists_after) ++budget.metrics.groups_removed;
    return false;
  }
  sql_aggregate::Epoch commit() noexcept {
    assert(live && owner->busy && (!source || source->active()));
    if (!source) {
      result.native = owner->source.commit_fused();
    } else {
    // Child is closed to every other caller. Its active checks are established
    // above; its actual publication uses already funded journals/detached nodes.
    // No concurrent observer can run between the following scalar frontiers.
    auto child = source->commit();
    // Native capture was required only by this private contributor. Every key
    // and requested output is already owned; release D facts before returning G
    // output. Explicitly requested native journals retain their existing meaning.
    child.native.bag_deltas = {};
    result.native = std::move(child.native);
    }
    // Ids may move as groups are erased: each committed group is found again.
    for (auto& item : groups.items()) {
      auto& proposal = item.payload;
      const bool exists_after = owner->global() || proposal.after.rows != 0;
      if (proposal.position == absent) {
        if (exists_after) owner->groups.insert(std::move(item.key), std::move(proposal.after), item.hash);
        continue;
      }
      const auto position = owner->groups.find(item.key.view(), item.hash);
      if (!exists_after) { owner->groups.erase(position); continue; }
      auto& group = owner->groups.at(position).value;
      group.rows = proposal.after.rows;
      assert(group.values.get_allocator() == proposal.after.values.get_allocator());
      group.values.swap(proposal.after.values);
    }
    owner->sequence = result.sequence;
    owner->give_groups(groups); owner->busy = false; live = false;
    return std::move(result); // Account/program/output moves are nonallocating.
  }
};

sql_aggregate::Epoch::Epoch(const resource::MemoryAccount& account, std::uint64_t next,
    frontend::SqlAggregateProgram source, bool capture)
    : sequence(next), captured(capture), native{next, false, {}, {}, {}, {}, {}}, program(std::move(source)),
      output(resource::OwnerAllocator<aggregate::GroupChange>(account, resource::MemoryPurpose::output_buffer)) {}
sql_aggregate::Snapshot::Snapshot(const resource::MemoryAccount& account, std::uint64_t next,
    frontend::SqlAggregateProgram source)
    : sequence(next), program(std::move(source)),
      groups(resource::OwnerAllocator<aggregate::GroupResult>(account, resource::MemoryPurpose::output_buffer)) {}
static_assert(std::is_nothrow_move_constructible_v<sql_aggregate::Epoch>);
static_assert(std::is_nothrow_move_assignable_v<weighted::Epoch>);

SqlAggregateRuntime::SqlAggregateRuntime(std::shared_ptr<Data> value) noexcept : data_(std::move(value)) {}
SqlAggregateRuntime SqlAggregateRuntime::create_into(const resource::MemoryAccount& account,
    frontend::SqlAggregateProgram program, const FreeConnexTree& tree, const PhysicalOptions& physical,
    sql_aggregate::Options options) {
  if (!account) throw resource::MemoryFailure(resource::MemoryFault::contract);
  if (!program) fail("invalid_sql_aggregate_program", "composed runtime requires an actual compiler program");
  if (options.count_limit > static_cast<std::uint64_t>(INT64_MAX))
    fail("invalid_options", "aggregate count limit exceeds signed bigint");
  return SqlAggregateRuntime(resource::make_accounted_shared<Data>(account, resource::MemoryPurpose::table_state,
      account, std::move(program), tree, physical, options));
}
SqlAggregateRuntime SqlAggregateRuntime::rebuild_into(const resource::MemoryAccount& account,
    const sql_aggregate::SourceSnapshot& image,sql_aggregate::Options options,
    const sql_aggregate::RebuildLimits& limits,sql_aggregate::RebuildMetrics* observed) {
  if(!image.program || !image.source.program ||
      image.program.source_program().source_sha256()!=image.source.program.source_sha256())
    fail("invalid_sql_aggregate_snapshot","original aggregate binding and source image differ");
  if(options.count_limit>static_cast<std::uint64_t>(INT64_MAX))
    fail("invalid_options","aggregate count limit exceeds signed bigint");
  sql_aggregate::RebuildMetrics metrics;
  storage::IndexWorkAllowance source_work(limits.source.source_work,true);
  Budget group_work{limits.group_work,{}};
  auto context=::crown::runtime::detail::SqlColdRebuild::context(account,image.source,limits.source);
  // Import actual compiler metadata once; child freeze is then a same-account
  // share. No AST, edited BoundSql or normalized DTO is an admission authority.
  auto program=frontend::SqlAggregateProgram::freeze(account,image.program);
  auto rebuilt=[&] {
    ::crown::runtime::detail::StorageOperation operation(context);
    auto source=::crown::runtime::detail::SqlColdRebuild::empty(account,image.source,program.source_program(),options.source,limits.source,
        context,source_work,metrics.source);
    auto loading=options;loading.group_work_limit=limits.group_work;loading.capture_changes=false;
    auto owner=resource::make_accounted_shared<Data>(account,resource::MemoryPurpose::table_state,
        account,std::move(program),std::move(source),loading,image.source.sequence?image.source.sequence-1:0);
    owner->initialize(group_work); // Exact same static 0/1 and global-empty kernel.
    if(image.source.sequence) {
      group_work.take(); // Same open admission, using the unrefilled init budget.
      auto source_token=::crown::runtime::detail::SqlColdRebuild::seed(owner->source,image.source,source_work,weighted::DeltaCapture::enabled);
      auto data=resource::make_accounted_unique<PreparedBatch::Data>(account,resource::MemoryPurpose::scratch,
          owner,std::move(source_token),std::move(group_work));
      owner->busy=true;PreparedBatch pending(std::move(data));
      auto epoch=pending.commit();
      metrics.groups=static_cast<const aggregate::Metrics&>(epoch.metrics);
      metrics.source.native_work=epoch.native.metrics.work;
    } else metrics.groups=group_work.metrics;
    const auto source_left=source_work.remaining();const auto source_limit=limits.source.source_work;
    metrics.source.source_work={source_limit.structural_steps-source_left.structural_steps,
        source_limit.scalar_fields-source_left.scalar_fields,source_limit.scalar_bytes-source_left.scalar_bytes,
        source_limit.pointer_slots-source_left.pointer_slots,source_limit.link_actions-source_left.link_actions};
    if(context->indexed()) {
      const auto left=::crown::runtime::detail::compact_storage_work(context)->remaining();const auto cap=context->limit();
      metrics.source.indexed_work={cap.structural_steps-left.structural_steps,cap.scalar_fields-left.scalar_fields,
          cap.scalar_bytes-left.scalar_bytes,cap.pointer_slots-left.pointer_slots,cap.link_actions-left.link_actions};
    }
    return SqlAggregateRuntime(std::move(owner));
  }(); // Closes every cold cursor/journal/token/result/lease before normal context.
  ::crown::runtime::detail::SqlColdRebuild::close_source(rebuilt.data().source,options.source);
  options.memory_limit_bytes=account.statistics().limit_bytes;
  options.source.native.memory_limit_bytes=options.memory_limit_bytes;rebuilt.data().options=options;
  if (observed) *observed = metrics;
  return rebuilt;
}

SqlAggregateRuntime::SqlAggregateRuntime(frontend::SqlAggregateProgram program, const FreeConnexTree& tree,
    const PhysicalOptions& physical, sql_aggregate::Options options)
    : SqlAggregateRuntime(create_into(resource::MemoryAccount::create(options.memory_limit_bytes),
          std::move(program), tree, physical, options)) {}
SqlAggregateRuntime::SqlAggregateRuntime(SqlAggregateRuntime&&) noexcept = default;
SqlAggregateRuntime& SqlAggregateRuntime::operator=(SqlAggregateRuntime&&) noexcept = default;
SqlAggregateRuntime::~SqlAggregateRuntime() = default;
SqlAggregateRuntime::Data& SqlAggregateRuntime::data() const {
  if (!data_) fail("invalid_sql_aggregate_runtime", "composed runtime handle is empty");
  return *data_;
}
const frontend::SqlAggregateProgram& SqlAggregateRuntime::program() const & { return data().program; }
const resource::MemoryAccount& SqlAggregateRuntime::account() const & { return data().account; }
std::uint64_t SqlAggregateRuntime::sequence() const { return data().sequence; }
std::string_view SqlAggregateRuntime::engine() const { return data().source.engine(); }
bool SqlAggregateRuntime::fused() const { return data().fused; }
bool SqlAggregateRuntime::ready() const noexcept { return data_ && !data_->busy && data_->source.ready(); }
weighted::Multiplicity SqlAggregateRuntime::root_weight() const {
  const auto& value = data(); value.require_idle(); return value.source.root_weight();
}
resource::MemoryStatistics SqlAggregateRuntime::accounted_memory_statistics() const { return data().account.statistics(); }
std::uint64_t SqlAggregateRuntime::source_weight(TableId id, std::span<const sql_rows::Cell> cells) const {
  const auto& value = data(); value.require_idle(); return value.source.source_weight(id, cells);
}
SqlAggregateRuntime::PreparedBatch SqlAggregateRuntime::prepare_batch(const sql_rows::NetBatch& batch) {
  auto& value = data(); auto budget = value.open(batch.sequence);
  if (value.fused) {
    auto prepared = resource::make_accounted_unique<PreparedBatch::Data>(value.account, resource::MemoryPurpose::scratch,
        data_, batch, std::move(budget), PreparedBatch::Data::FusedTag{});
    value.busy = true; return PreparedBatch(std::move(prepared));
  }
  auto source = value.source.prepare_batch(batch, weighted::DeltaCapture::enabled);
  auto prepared = resource::make_accounted_unique<PreparedBatch::Data>(value.account, resource::MemoryPurpose::scratch,
      data_, std::move(source), std::move(budget));
  value.busy = true; return PreparedBatch(std::move(prepared));
}
SqlAggregateRuntime::PreparedBatch::PreparedBatch(resource::AccountedUnique<Data> value) noexcept : data_(std::move(value)) {}
SqlAggregateRuntime::PreparedBatch::PreparedBatch(PreparedBatch&&) noexcept = default;
SqlAggregateRuntime::PreparedBatch& SqlAggregateRuntime::PreparedBatch::operator=(PreparedBatch&&) noexcept = default;
SqlAggregateRuntime::PreparedBatch::~PreparedBatch() = default;
SqlAggregateRuntime::PreparedBatch::Data& SqlAggregateRuntime::PreparedBatch::data() const {
  if (!data_ || !data_->live) fail("invalid_sql_aggregate_batch", "composed batch token is closed or moved from");
  return *data_;
}
bool SqlAggregateRuntime::PreparedBatch::active() const noexcept { return data_ && data_->live; }
const sql_aggregate::Epoch& SqlAggregateRuntime::PreparedBatch::preview() const & { return data().result; }
sql_aggregate::Epoch SqlAggregateRuntime::PreparedBatch::commit() {
  auto result = data().commit(); data_.reset(); return result;
}
void SqlAggregateRuntime::PreparedBatch::rollback() noexcept { data_.reset(); }
sql_aggregate::Snapshot SqlAggregateRuntime::snapshot(aggregate::SnapshotLimits limits) const {
  auto& value = data(); value.require_idle(); Budget budget{limits.work_limit, {}}; budget.take();
  if (value.groups.size() > limits.groups) fail("aggregate_result_limit", "aggregate snapshot group limit exceeded");
  sql_aggregate::Snapshot result(value.account, value.sequence, value.program);
  result.groups.reserve(value.groups.size());
  // Groups are presented in their exact key order.
  Items<const Groups::Entry*> order(allocator<const Groups::Entry*>(value.account, resource::MemoryPurpose::scratch));
  order.reserve(value.groups.size());
  for (const auto& entry : value.groups.entries()) order.push_back(&entry);
  std::sort(order.begin(), order.end(), [](const Groups::Entry* a, const Groups::Entry* b) {
    return sql_detail::less(a->key.view(), b->key.view());
  });
  for (const auto* entry : order)
    result.groups.push_back({entry->key, aggregate::detail::render(value.account, value.program.kernel_program(), value.output,
        entry->key.view(), entry->value.rows, entry->value.values, budget)});
  return result;
}
sql_aggregate::SourceSnapshot SqlAggregateRuntime::source_snapshot(sql_rows::SourceSnapshotLimits limits) const {
  const auto& value = data(); value.require_idle();
  auto source = value.source.source_snapshot(limits);
  assert(source.sequence == value.sequence);
  return {value.program, std::move(source)};
}
}  // namespace crown::runtime
