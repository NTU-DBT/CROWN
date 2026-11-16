#include "crown/runtime/sql_aggregate.hpp"
#include "aggregate_detail.hpp"
#include "sql_cold_rebuild.hpp"
#include <cassert>
#include <map>
#include <type_traits>
#include <utility>

namespace crown::runtime {
namespace {
using namespace aggregate;
using namespace aggregate::detail;
using Groups = std::map<Tuple, Group, Less,
    resource::MemoryAllocator<std::pair<const Tuple, Group>>>;
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

  Data(const resource::MemoryAccount& receiver, frontend::SqlAggregateProgram original,
      const FreeConnexTree& tree, const PhysicalOptions& physical, sql_aggregate::Options requested)
      : account(receiver), program(frontend::SqlAggregateProgram::freeze(receiver, original)), options(requested),
        source(SqlRowsRuntime::create_into(receiver, program.source_program(), tree, physical, requested.source)),
        input(program.inputs().size(), Cell{}, allocator<Cell>(receiver, resource::MemoryPurpose::scratch)),
        key(program.kernel_program().group_columns().size(), Cell{}, allocator<Cell>(receiver, resource::MemoryPurpose::scratch)),
        output(program.kernel_program().outputs().size(), Cell{}, allocator<Cell>(receiver, resource::MemoryPurpose::scratch)),
        groups(Less{}, allocator<Groups::value_type>(receiver, resource::MemoryPurpose::support_metadata)) {
    options.memory_limit_bytes = account.statistics().limit_bytes;
    options.source.native.memory_limit_bytes = options.memory_limit_bytes;
    Budget budget{options.group_work_limit,{}};initialize(budget);
  }
  Data(const resource::MemoryAccount& receiver,frontend::SqlAggregateProgram original,SqlRowsRuntime child,
      sql_aggregate::Options requested,std::uint64_t initial_sequence)
      : account(receiver), program(frontend::SqlAggregateProgram::freeze(receiver, original)), options(requested),
        source(std::move(child)),
        input(program.inputs().size(), Cell{}, allocator<Cell>(receiver, resource::MemoryPurpose::scratch)),
        key(program.kernel_program().group_columns().size(), Cell{}, allocator<Cell>(receiver, resource::MemoryPurpose::scratch)),
        output(program.kernel_program().outputs().size(), Cell{}, allocator<Cell>(receiver, resource::MemoryPurpose::scratch)),
        groups(Less{}, allocator<Groups::value_type>(receiver, resource::MemoryPurpose::support_metadata)),
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
      groups.emplace(Tuple::copy_of(account, {}), Group(account, kernel.measures().size()));
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
        auto& group = groups.begin()->second; group.rows = *weight;
        aggregate::detail::adjust<false>(kernel, group.values, input, *weight, false, budget);
        check_sums(kernel, group.values, budget);
      }
    }
  }
};

struct SqlAggregateRuntime::PreparedBatch::Data {
  struct Proposal {
    Groups::iterator position;
    Group after;
    Groups::node_type inserted;
  };
  using Touched = std::map<Tuple, Proposal, Less,
      resource::MemoryAllocator<std::pair<const Tuple, Proposal>>>;
  // Owner is first and dies last, including failed construction. Child rollback
  // and proposal/output teardown never outlive the complete outer owner.
  std::shared_ptr<SqlAggregateRuntime::Data> owner;
  SqlRowsRuntime::PreparedBatch source;
  Budget budget;
  Touched groups;
  sql_aggregate::Epoch result;
  bool live = false;

  Data(std::shared_ptr<SqlAggregateRuntime::Data> target, SqlRowsRuntime::PreparedBatch child, Budget allowance)
      : owner(std::move(target)), source(std::move(child)), budget(std::move(allowance)),
        groups(Less{}, allocator<Touched::value_type>(owner->account, resource::MemoryPurpose::scratch)),
        result(owner->account, source.sequence(), owner->program, owner->options.capture_changes) {
    Borrows borrowed{owner->input, owner->key};
    const auto facts = source.native_bag_delta_preview();
    if (!facts) fail("sql_aggregate_contract", "private source did not capture its genuine native bag facts");
    result.changed = source.changed(); result.group_changed = !facts->empty();
    result.source_work = source.source_work(); result.native = source.native_preview();
    contribute(*facts, true); contribute(*facts, false);
    if (result.captured && !groups.empty()) { budget.take(); result.output.reserve(groups.size()); }
    for (auto& [key, proposal] : groups) finalize(key, proposal);
    budget.take(); static_cast<aggregate::Metrics&>(result.metrics) = budget.metrics;
    live = true; // Caller sets owner->busy after this constructor returns.
  }
  ~Data() {
    if (live) {
      groups.clear(); source.rollback(); owner->busy = false;
    }
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
    budget.take(); ++budget.metrics.group_probes;
    const auto queued = groups.find(key);
    if (queued != groups.end()) return queued->second;
    budget.take(); ++budget.metrics.group_probes;
    const auto current = owner->groups.find(key);
    Tuple owned;
    if (current != owner->groups.end()) owned = current->first;
    else { charge_copy(key); owned = Tuple::copy_of(owner->account, key); }
    const auto width = owner->program.kernel_program().measures().size();
    budget.take(width); result.metrics.state_fields_prepared += width;
    Group after = current == owner->groups.end() ? Group(owner->account, width)
        : Group(owner->account, current->second);
    budget.take();
    return groups.emplace(std::move(owned), Proposal{current, std::move(after), {}}).first->second;
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
  void finalize(const Tuple& key, Proposal& proposal) {
    budget.take(); ++result.metrics.groups_finalized;
    check_sums(owner->program.kernel_program(), proposal.after.values, budget);
    const bool exists_after = owner->global() || proposal.after.rows != 0;
    if (result.captured) {
      std::optional<Tuple> before, after;
      if (proposal.position != owner->groups.end()) before = render(key, proposal.position->second);
      if (exists_after) after = render(key, proposal.after);
      if (before.has_value() != after.has_value() || (before && after && !(*before == *after))) {
        budget.take(); result.output.push_back({key, std::move(before), std::move(after)});
      }
    }
    if (proposal.position == owner->groups.end() && exists_after) {
      budget.take(); proposal.inserted = node_for(owner->groups, key, std::move(proposal.after));
      ++budget.metrics.groups_created;
    } else if (!exists_after) ++budget.metrics.groups_removed;
  }
  sql_aggregate::Epoch commit() noexcept {
    assert(live && owner->busy && source.active());
    // Child is closed to every other caller. Its active checks are established
    // above; its actual publication uses already funded journals/detached nodes.
    // No concurrent observer can run between the following scalar frontiers.
    auto child = source.commit();
    // Native capture was required only by this private contributor. Every key
    // and requested output is already owned; release D facts before returning G
    // output. Explicitly requested native journals retain their existing meaning.
    child.native.bag_deltas = {};
    result.native = std::move(child.native);
    for (auto& [key, proposal] : groups) {
      static_cast<void>(key);
      if (!proposal.inserted.empty()) {
        const auto added = owner->groups.insert(std::move(proposal.inserted)); assert(added.inserted);
      } else if (!owner->global() && !proposal.after.rows) owner->groups.erase(proposal.position);
      else {
        proposal.position->second.rows = proposal.after.rows;
        assert(proposal.position->second.values.get_allocator() == proposal.after.values.get_allocator());
        proposal.position->second.values.swap(proposal.after.values);
      }
    }
    owner->sequence = result.sequence;
    groups.clear(); owner->busy = false; live = false;
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
  for (const auto& [key, group] : value.groups)
    result.groups.push_back({key, aggregate::detail::render(value.account, value.program.kernel_program(), value.output,
        key.view(), group.rows, group.values, budget)});
  return result;
}
sql_aggregate::SourceSnapshot SqlAggregateRuntime::source_snapshot(sql_rows::SourceSnapshotLimits limits) const {
  const auto& value = data(); value.require_idle();
  auto source = value.source.source_snapshot(limits);
  assert(source.sequence == value.sequence);
  return {value.program, std::move(source)};
}
}  // namespace crown::runtime
