#include "crown/runtime/sql_rows.hpp"
#include "sql_cold_rebuild.hpp"
#include "sql_tuple_table.hpp"
#include "../planner/compiled_source.hpp"
#include "../frontend/sql_rows_eval.hpp"
#include "crown/api/error.hpp"
#include "crown/planner/lower.hpp"
#include <algorithm>
#include <cassert>
#include <map>

namespace crown::runtime {
namespace {
using namespace sql_rows;
template<class T> using Items = std::vector<T, resource::MemoryAllocator<T>>;
template<class T> auto allocator(const resource::MemoryAccount& account,
    resource::MemoryPurpose purpose) { return resource::MemoryAllocator<T>(account, purpose); }
[[noreturn]] void fail(const char* code, const char* message) { throw Error(code, message); }

// Immutable nullable keys support borrowed probes (sql_tuple_table.hpp):
// equality is equivalence in the exact scalar order of the native core (NULL
// first). Capacity for every insert is reserved while preparing, so
// publication after native commit allocates nothing.
using Counts = sql_detail::TupleTable<std::uint64_t>;
constexpr auto absent = Counts::npos;
std::uint64_t count(const Counts& values, std::span<const Cell> key) {
  const auto found = values.find(key); return found == absent ? 0 : values.at(found).value;
}
// Publish one prepared counter change; the key was present at preparation
// iff `present`. Nonthrowing: an insert has reserved capacity.
void publish_count(Counts& target, Tuple key, std::uint64_t hash, bool present, std::uint64_t after) noexcept {
  if (!present) { if (after) target.insert(std::move(key), after, hash); return; }
  const auto position = target.find(key.view(), hash);
  if (!after) target.erase(position);
  else target.at(position).value = after;
}
std::uint64_t replace_count(std::uint64_t current, std::uint64_t before, std::uint64_t after) {
  if (before > current) fail("sql_rows_contract", "source contribution exceeds its key counter");
  const auto base = current - before;
  if (after > UINT64_MAX - base) fail("sql_rows_overflow", "SQL source key counter exceeds uint64");
  return base + after;
}
storage::IndexWork consumed(storage::IndexWork limit, const storage::IndexWork& remaining) noexcept {
  return {limit.structural_steps - remaining.structural_steps,
      limit.scalar_fields - remaining.scalar_fields, limit.scalar_bytes - remaining.scalar_bytes,
      limit.pointer_slots - remaining.pointer_slots, limit.link_actions - remaining.link_actions};
}
PhysicalPlan lower(const frontend::SqlRowsProgram& program, const FreeConnexTree& tree,
    const PhysicalOptions& options) {
  const auto core = program.export_core();
  return planner::lower_tree(core.catalog, core.query, tree, options);
}
}  // namespace

namespace {
// Touched source rows (domain = source table) and key counters (domain =
// constraint) of one prepared batch, each item owning its key.
struct Proposal {
  Counts* target;
  bool present;  // committed at preparation
  std::uint64_t before,after;
};
using Touched=sql_detail::TouchedSet<Proposal>;
}  // namespace

struct SqlRowsRuntime::Data {
  struct Edit {
    Counts* target;
    Tuple key;  // the committed key, or a reserved new copy
    std::uint64_t hash;
    bool present;
    std::uint64_t after;
  };
  resource::MemoryAccount account;
  frontend::SqlRowsProgram program;
  Options options;
  WeightedRuntime native;
  Items<Counts> sources, keys;
  Items<NodeId> nodes;
  Items<Cell> values, key, other;
  Items<storage::ScalarView> projected;
  Items<Edit> edits;
  std::size_t key_used = 0, other_used = 0, projected_used = 0;
  // Touched sets of the previous batch (empty, capacity kept) for the next.
  std::optional<Touched> spare_rows, spare_keys;
  // The open fused batch's touched source rows (prepare_fused..commit_fused).
  std::optional<Touched> fused;
  Touched take(std::optional<Touched>& spare) {
    if (!spare) return Touched(account);
    auto value = std::move(*spare); spare.reset(); return value;
  }
  static void give(std::optional<Touched>& spare, Touched& value) noexcept {
    value.clear();
    if (!spare) spare.emplace(std::move(value));
  }

  Data(const resource::MemoryAccount& owner, frontend::SqlRowsProgram source,
      const FreeConnexTree& tree, const PhysicalOptions& physical, Options requested)
      : account(owner), program(frontend::SqlRowsProgram::freeze(owner, source)), options(requested),
        native(WeightedRuntime::create_into(owner, lower(program, tree, physical), requested.native)),
        sources(allocator<Counts>(owner, resource::MemoryPurpose::source_counts)),
        keys(allocator<Counts>(owner, resource::MemoryPurpose::support_metadata)),
        nodes(program.occurrences().size(), NodeId{SIZE_MAX}, allocator<NodeId>(owner, resource::MemoryPurpose::immutable_metadata)),
        values(program.initial_values().begin(), program.initial_values().end(), allocator<Cell>(owner, resource::MemoryPurpose::scratch)),
        key(allocator<Cell>(owner, resource::MemoryPurpose::scratch)),
        other(allocator<Cell>(owner, resource::MemoryPurpose::scratch)),
        projected(allocator<storage::ScalarView>(owner, resource::MemoryPurpose::scratch)),
        edits(allocator<Edit>(owner, resource::MemoryPurpose::scratch)) {initialize();}
  Data(const resource::MemoryAccount& owner,frontend::SqlRowsProgram source,WeightedRuntime prepared,Options requested)
      : account(owner), program(frontend::SqlRowsProgram::freeze(owner, source)), options(requested),
        native(std::move(prepared)),
        sources(allocator<Counts>(owner, resource::MemoryPurpose::source_counts)),
        keys(allocator<Counts>(owner, resource::MemoryPurpose::support_metadata)),
        nodes(program.occurrences().size(), NodeId{SIZE_MAX}, allocator<NodeId>(owner, resource::MemoryPurpose::immutable_metadata)),
        values(program.initial_values().begin(), program.initial_values().end(), allocator<Cell>(owner, resource::MemoryPurpose::scratch)),
        key(allocator<Cell>(owner, resource::MemoryPurpose::scratch)),
        other(allocator<Cell>(owner, resource::MemoryPurpose::scratch)),
        projected(allocator<storage::ScalarView>(owner, resource::MemoryPurpose::scratch)),
        edits(allocator<Edit>(owner, resource::MemoryPurpose::scratch)) {initialize();}
  void initialize() {
    const auto& owner=account;
    options.native.memory_limit_bytes = account.statistics().limit_bytes;
    sources.reserve(program.sources().size()); keys.reserve(program.constraints().size());
    std::size_t width = 0, maximum_edits = 0;
    for (const auto& table : program.sources()) {
      sources.emplace_back(owner, resource::MemoryPurpose::source_counts);
      maximum_edits = std::max(maximum_edits, table.constraints.size());
    }
    for (const auto& constraint : program.constraints()) {
      keys.emplace_back(owner, resource::MemoryPurpose::support_metadata);
      width = std::max(width, constraint.columns.size());
    }
    key.resize(width); other.resize(width); edits.reserve(maximum_edits);
    width = 0;
    for (const auto& occurrence : program.occurrences()) width = std::max(width, occurrence.projection.size());
    projected.resize(width);
    for (const auto& node : native.structural_program().nodes())
      if (node.kind == NodeKind::native) nodes[node.occurrence->value] = node.id;
    // Contradiction has no executable nodes. Every other exported atom must
    // have one native port, as already established by supplied-tree validation.
    if (!program.contradiction()) for (const auto node : nodes)
      if (node.value == SIZE_MAX) fail("sql_rows_contract", "SQL occurrence has no native input port");
  }

  const frontend::SqlRowsSource& source(TableId id) const {
    if (id.value >= program.sources().size()) fail("invalid_sql_rows_source", "SQL source table is outside the bound catalog");
    return program.sources()[id.value];
  }
  void validate(const frontend::SqlRowsSource& table, std::span<const Cell> input,
      storage::IndexWorkAllowance* work) const {
    if (input.size() != table.columns.size()) fail("invalid_sql_rows_row", "SQL source row arity differs from its schema");
    for (std::size_t i = 0; i < input.size(); ++i) {
      frontend::rows_detail::step(work);
      if (input[i]) frontend::sql_detail::admit_value(work, *input[i]);
      if (!frontend::rows_detail::fits(input[i], table.columns[i].type))
        fail("invalid_sql_rows_row", "SQL source cell violates its type, nullability or UTF8 domain");
    }
  }
  // Both UNIQUE (NULLS DISTINCT) and MATCH SIMPLE foreign keys omit any key
  // containing NULL. A zero-column key is present and denotes the unit key.
  std::optional<std::span<const Cell>> project_key(const frontend::SqlRowsConstraint& constraint,
      std::span<const Cell> input, Items<Cell>& target, std::size_t& used, storage::IndexWorkAllowance& work) {
    used = std::max(used, constraint.columns.size());
    for (std::size_t i = 0; i < constraint.columns.size(); ++i) {
      frontend::rows_detail::step(&work);
      target[i] = input[constraint.columns[i].value];
      if (!target[i]) return std::nullopt;
      frontend::sql_detail::admit_value(&work, *target[i]);
    }
    return std::span<const Cell>(target.data(), constraint.columns.size());
  }
  bool same_key(std::span<const Cell> left, std::span<const Cell> right, storage::IndexWorkAllowance& work) const {
    if (left.size() != right.size()) return false;
    for (std::size_t i = 0; i < left.size(); ++i)
      if (!frontend::rows_detail::same(left[i], right[i], &work)) return false;
    return true;
  }
  // Probe the proposed single-row state without publishing it. This handles
  // self-referencing inserts/deletes and last-parent deletion using indexes,
  // rather than scanning source tables or special-casing self references away.
  std::uint64_t proposed_count(std::size_t index, std::span<const Cell> probe,
      const Update& update, storage::IndexWorkAllowance& work) {
    frontend::rows_detail::step(&work); auto result = count(keys[index], probe);
    const auto& constraint = program.constraints()[index];
    if (constraint.source == update.source) {
      const auto own_key = project_key(constraint, update.values, other, other_used, work);
      if (own_key && same_key(*own_key, probe, work)) {
        const auto before = constraint.parent ? std::uint64_t(update.before != 0) : update.before;
        const auto after = constraint.parent ? std::uint64_t(update.after != 0) : update.after;
        result = replace_count(result, before, after);
      }
    }
    return result;
  }
  void prepare_keys(const frontend::SqlRowsSource& table, const Update& update, storage::IndexWorkAllowance& work) {
    for (const auto index : table.constraints) {
      frontend::rows_detail::step(&work); const auto& constraint = program.constraints()[index];
      const auto selected = project_key(constraint, update.values, key, key_used, work);
      if (!selected) continue;
      auto& target = keys[index]; const auto hash = sql_detail::hash_cells(*selected);
      const auto found = target.find(*selected, hash);
      const auto current = found == absent ? 0 : target.at(found).value;
      frontend::rows_detail::step(&work);
      const auto before = constraint.parent ? std::uint64_t(update.before != 0) : update.before;
      const auto after = constraint.parent ? std::uint64_t(update.after != 0) : update.after;
      const auto next = replace_count(current, before, after);
      if (constraint.parent) {
        if (update.after && !proposed_count(*constraint.parent, *selected, update, work))
          fail("foreign_key_violation", "SQL source foreign key has no live parent");
      } else {
        if (next > 1) fail("unique_violation", "SQL source UNIQUE key has more than one row");
        if (!next) for (const auto reference : constraint.referenced_by)
          if (proposed_count(reference, *selected, update, work))
            fail("foreign_key_violation", "SQL source parent key is still referenced");
      }
      if (next == current) continue;
      Tuple owned;
      if (found != absent) owned = target.at(found).key;
      else if (next) { owned = Tuple::copy_of(account, *selected); target.reserve(1); }
      edits.push_back({&target, std::move(owned), hash, found != absent, next});
    }
  }
  // Only touched scratch prefixes are cleared. Detached edits own private
  // nodes until publication; clearing them also handles failed preparation.
  // The native PendingEpoch owns all rollback of tentative native changes.
  struct Scratch {
    Data& data;
    ~Scratch() noexcept {
      std::fill_n(data.key.begin(), data.key_used, Cell{});
      std::fill_n(data.other.begin(), data.other_used, Cell{});
      std::fill_n(data.projected.begin(), data.projected_used, storage::ScalarView{std::int64_t{0}});
      data.key_used = data.other_used = data.projected_used = 0; data.edits.clear();
    }
  };
  Epoch apply(const Update& update) {
    auto pending = native.begin_epoch(update.sequence);
    Scratch scratch{*this};
    storage::IndexWorkAllowance work(options.source_work_limit, true);
    frontend::rows_detail::step(&work); const auto& table = source(update.source);
    validate(table, update.values, &work);
    if (update.after > options.native.multiplicity_limit)
      fail("sql_rows_overflow", "SQL source weight exceeds the configured multiplicity limit");
    auto& rows = sources[update.source.value]; const auto row_hash = sql_detail::hash_cells(update.values);
    const auto found = rows.find(update.values, row_hash);
    frontend::rows_detail::step(&work);
    const auto actual = found == absent ? 0 : rows.at(found).value;
    if (actual != update.before) fail("sql_rows_weight_mismatch", "SQL prior source weight differs from committed state");
    Tuple inserted;
    if (update.before != update.after) {
      if (found == absent && update.after) { inserted = Tuple::copy_of(account, update.values); rows.reserve(1); }
      prepare_keys(table, update, work);
      if (!program.contradiction()) for (const auto id : table.occurrences) {
        frontend::rows_detail::step(&work); const auto& occurrence = program.occurrences()[id.value];
        projected_used = std::max(projected_used, occurrence.projection.size());
        const auto output = std::span<storage::ScalarView>(projected.data(), occurrence.projection.size());
        if (frontend::rows_detail::adapt(program, occurrence, update.values, values, output, &work))
          static_cast<void>(pending.stage_contribution(nodes[id.value],
              storage::TupleValuesView::borrow(storage::RowView::borrow(output)), {update.before}, {update.after}));
      }
    }
    const auto spent = consumed(options.source_work_limit, work.remaining());
    auto result = pending.commit();
    // All throwing work is finished: inserts have reserved capacity and the
    // immutable validated keys hash and compare without throwing.
    if (update.before != update.after) {
      for (auto& edit : edits) publish_count(*edit.target, std::move(edit.key), edit.hash, edit.present, edit.after);
      if (found == absent) { if (update.after) rows.insert(std::move(inserted), update.after, row_hash); }
      else if (!update.after) rows.erase(found);
      else rows.at(found).value = update.after;
    }
    return {update.before != update.after, spent, std::move(result)};
  }
};


// All SQL source/key state remains committed while one native token is private.
// The owner keeps committed iterators and shared tuple payloads alive even when
// its facade moves or dies. No caller row/Cell span survives construction.
struct SqlRowsRuntime::PreparedBatch::Data {
  // Iterated in (domain, key) order; borrowed from the owner's spares.
  std::shared_ptr<SqlRowsRuntime::Data> owner;
  WeightedRuntime::PendingEpoch pending;
  storage::IndexWorkAllowance work;
  Touched rows,keys;
  bool changed=false;
  std::optional<OutputLimits> output_limits; // Fixed opt-in metadata; no output-row mirror.
  std::uint64_t output_spent=0;

  Data(std::shared_ptr<SqlRowsRuntime::Data> sql,const NetBatch& batch,WeightedRuntime::PendingEpoch native)
      :owner(std::move(sql)),pending(std::move(native)),
       work(owner->options.source_work_limit,true),
       rows(owner->take(owner->spare_rows)),keys(owner->take(owner->spare_keys)) {prepare(batch);}
  Data(std::shared_ptr<SqlRowsRuntime::Data> sql,const NetBatch& batch,WeightedRuntime::PendingEpoch native,
      storage::IndexWorkAllowance& cold)
      :owner(std::move(sql)),pending(std::move(native)),work(storage::detail::IndexWorkAlias::fixed(cold)),
       rows(owner->take(owner->spare_rows)),keys(owner->take(owner->spare_keys)) {prepare(batch);}
  void prepare(const NetBatch& batch) {
    SqlRowsRuntime::Data::Scratch scratch{*owner};
    for(const auto& edit:batch.replacements) {
      frontend::rows_detail::step(&work);
      const auto& table=owner->source(edit.source);
      owner->validate(table,edit.values,&work);
      if(edit.before==edit.after) {
        frontend::rows_detail::step(&work);
        const auto* queued=rows.find(edit.source.value,edit.values,sql_detail::hash_cells(edit.values));
        std::uint64_t current;
        if(queued)current=queued->payload.after;
        else {frontend::rows_detail::step(&work);current=count(owner->sources[edit.source.value],edit.values);}
        if(current!=edit.before)fail("sql_rows_weight_mismatch","SQL prior source weight differs from proposed state");
        continue; // A no-op validates its chain but needs no new key/payload.
      }
      auto& proposal=touch(rows,edit.source.value,owner->sources[edit.source.value],edit.values,edit.before);
      proposal.after=edit.after; // Only the final chained weight is admitted below.
    }
    rows.sort();
    for(const auto& item:rows.items()) {
      const auto& proposal=item.payload;frontend::rows_detail::step(&work);
      if(proposal.after>owner->options.native.multiplicity_limit)
        fail("sql_rows_overflow","final SQL source weight exceeds the configured multiplicity limit");
      changed|=proposal.before!=proposal.after;
    }
    // Remove all key shares before adding any. This permits key swaps and
    // final-valid cyclic/self FK changes without transient counter overflow.
    update_keys(true);update_keys(false);keys.sort();validate_keys();
    prepare_nodes(rows);prepare_nodes(keys);
    stage_native(true);stage_native(false);
  }
  std::optional<std::size_t> output_size() const {
    if(!output_limits)return std::nullopt;
    if(owner->program.wrapper()==frontend::SqlWrapper::exists) {
      const auto& epoch=pending.preview();
      return epoch.before.present()!=epoch.after.present()?2:0;
    }
    const auto changes=owner->program.semantics()==frontend::SqlSemantics::set?
        pending.support_delta_preview():pending.bag_delta_preview();
    if(!changes)fail("sql_rows_contract","SQL output capture differs from its native policy");
    return changes->size();
  }
  OutputChangeView output_change(std::size_t index,std::span<Cell> scratch) {
    const auto size=output_size();
    if(!size)fail("sql_rows_output_disabled","SQL-presented output capture was not requested");
    if(index>=*size || scratch.size()!=owner->program.outputs().size())
      fail("sql_rows_output_contract","SQL output index or scratch width differs from its program");
    // One selected row unit and one field unit per call, across all codec passes.
    // String payload bytes stay borrowed; the codec funds actual byte visits.
    if(output_spent>=output_limits->work || scratch.size()>output_limits->work-output_spent-1)
      fail("sql_rows_output_work_limit","SQL output decode allowance exhausted");
    output_spent+=1+static_cast<std::uint64_t>(scratch.size());
    if(owner->program.wrapper()==frontend::SqlWrapper::exists) {
      const auto& epoch=pending.preview();
      scratch[0]=storage::ScalarView{index==0?epoch.before.present():epoch.after.present()};
      return {scratch,{index==0,{1}}};
    }
    const auto changes=owner->program.semantics()==frontend::SqlSemantics::set?
        pending.support_delta_preview():pending.bag_delta_preview();
    const auto& change=(*changes)[index];const auto fields=change.tuple.values();
    const auto columns=owner->program.outputs();
    // The genuine compiler makes this payload/presence mapping injective in
    // ordered SQL output, including repeated/constant fields; no re-count map.
    for(std::size_t i=0;i<columns.size();++i) {
      if(const auto* field=std::get_if<frontend::SqlRowsResultField>(&columns[i].value)) {
        if(field->presence && !std::get<bool>(fields[*field->presence]))scratch[i].reset();
        else scratch[i]=fields[field->payload];
      } else scratch[i]=owner->program.initial_values()[std::get<frontend::ExpressionId>(columns[i].value).value];
    }
    return {scratch,change.change};
  }
  ~Data() {rollback();}
  bool active() const noexcept {return bool(owner)&&pending.active();}
  Proposal& touch(Touched& touched,std::size_t id,Counts& target,std::span<const Cell> row,
      std::optional<std::uint64_t> expected=std::nullopt) {
    const auto hash=sql_detail::hash_cells(row);
    frontend::rows_detail::step(&work);auto* queued=touched.find(id,row,hash);
    if(queued) {
      if(expected && queued->payload.after!=*expected)
        fail("sql_rows_weight_mismatch","duplicate source edits do not form an expected-weight chain");
      return queued->payload;
    }
    frontend::rows_detail::step(&work);const auto position=target.find(row,hash);
    const auto current=position==absent?0:target.at(position).value;
    if(expected && current!=*expected)
      fail("sql_rows_weight_mismatch","SQL prior source weight differs from committed state");
    Tuple owned;
    if(position!=absent)owned=target.at(position).key; // Actual shared immutable Tuple copy.
    else {
      // New keys alone copy descriptors/string bytes; charge that copy as well
      // as the separate validation/project work already spent.
      for(const auto& value:row) {
        frontend::rows_detail::step(&work);
        if(value)frontend::sql_detail::admit_value(&work,*value);
      }
      owned=Tuple::copy_of(owner->account,row);
    }
    frontend::rows_detail::step(&work);
    return touched.add(id,std::move(owned),hash,Proposal{&target,position!=absent,current,current}).payload;
  }
  void update_keys(bool decreasing) {
    for(const auto& source_key:rows.items()) {
      const auto& proposal=source_key.payload;
      frontend::rows_detail::step(&work);
      if(proposal.before==proposal.after)continue;
      const auto& table=owner->source(TableId{source_key.domain});
      for(const auto index:table.constraints) {
        frontend::rows_detail::step(&work);const auto& constraint=owner->program.constraints()[index];
        const auto before=constraint.parent?std::uint64_t(proposal.before!=0):proposal.before;
        const auto after=constraint.parent?std::uint64_t(proposal.after!=0):proposal.after;
        if(before==after || (after<before)!=decreasing)continue;
        const auto selected=owner->project_key(constraint,source_key.key.view(),owner->key,owner->key_used,work);
        if(!selected)continue; // NULLS DISTINCT / MATCH SIMPLE; empty key is present.
        auto& key=touch(keys,index,owner->keys[index],*selected);
        key.after=replace_count(key.after,before,after);
      }
    }
  }
  std::uint64_t final_count(std::size_t id,std::span<const Cell> row) {
    frontend::rows_detail::step(&work);const auto* found=keys.find(id,row,sql_detail::hash_cells(row));
    if(found)return found->payload.after;
    frontend::rows_detail::step(&work);return count(owner->keys[id],row);
  }
  void validate_keys() {
    for(const auto& key:keys.items()) {
      const auto& proposal=key.payload;
      frontend::rows_detail::step(&work);const auto& constraint=owner->program.constraints()[key.domain];
      if(constraint.parent) {
        if(proposal.after && !final_count(*constraint.parent,key.key.view()))
          fail("foreign_key_violation","final SQL source foreign key has no live parent");
      } else {
        if(proposal.after>1)fail("unique_violation","final SQL UNIQUE key has more than one row");
        if(!proposal.after)for(const auto reference:constraint.referenced_by) {
          frontend::rows_detail::step(&work);
          if(final_count(reference,key.key.view()))
            fail("foreign_key_violation","final SQL source parent key is still referenced");
        }
      }
    }
  }
  // Reserve every insert. Sorted items sharing a domain share their target.
  void prepare_nodes(Touched& touched) {
    std::size_t inserts=0;
    const auto items=touched.items();
    for(std::size_t i=0;i<items.size();++i) {
      frontend::rows_detail::step(&work);
      const auto& proposal=items[i].payload;
      if(proposal.before!=proposal.after && !proposal.present && proposal.after)++inserts;
      if(inserts && (i+1==items.size() || items[i+1].domain!=items[i].domain)) {proposal.target->reserve(inserts);inserts=0;}
    }
  }
  void stage_native(bool decreasing) {
    for(const auto& key:rows.items()) {
      const auto& proposal=key.payload;
      frontend::rows_detail::step(&work);
      if(proposal.before==proposal.after || (proposal.after<proposal.before)!=decreasing)continue;
      if(owner->program.contradiction())continue;
      const auto& table=owner->source(TableId{key.domain});
      for(const auto id:table.occurrences) {
        frontend::rows_detail::step(&work);const auto& occurrence=owner->program.occurrences()[id.value];
        owner->projected_used=std::max(owner->projected_used,occurrence.projection.size());
        const auto output=std::span<storage::ScalarView>(owner->projected.data(),occurrence.projection.size());
        if(frontend::rows_detail::adapt(owner->program,occurrence,key.key.view(),owner->values,output,&work))
          static_cast<void>(pending.stage_contribution(owner->nodes[id.value],
              storage::TupleValuesView::borrow(storage::RowView::borrow(output)),
              {proposal.before},{proposal.after}));
      }
    }
  }
  static void publish(Touched& touched) noexcept {
    for(auto& item:touched.items()) {
      const auto& proposal=item.payload;
      if(proposal.before==proposal.after)continue;
      publish_count(*proposal.target,std::move(item.key),item.hash,proposal.present,proposal.after);
    }
  }
  Epoch commit() {
    const auto spent=consumed(owner->options.source_work_limit,work.remaining());
    auto native=pending.commit(); // No throwing preparation remains after this barrier.
    publish(keys);publish(rows);
    Epoch result{changed,spent,std::move(native)};
    release();return result;
  }
  void rollback() noexcept {
    if(!owner)return;
    pending.rollback();release();
  }
  void release() noexcept {
    SqlRowsRuntime::Data::give(owner->spare_keys,keys);SqlRowsRuntime::Data::give(owner->spare_rows,rows);owner.reset();
  }
};

struct SqlRowsRuntime::ResultCursor::Data {
  resource::MemoryAccount account;
  frontend::SqlRowsProgram program;
  WeightedRuntime::ResultCursor native;
  Items<Cell> output;
  weighted::CursorState state = weighted::CursorState::active;
  bool exists, emitted = false;
  Data(const resource::MemoryAccount& owner, frontend::SqlRowsProgram source,
      WeightedRuntime::ResultCursor cursor, bool present)
      : account(owner), program(std::move(source)), native(std::move(cursor)),
        output(program.outputs().size(), Cell{}, allocator<Cell>(owner, resource::MemoryPurpose::output_buffer)), exists(present) {}

  std::optional<Result> next() {
    if (state == weighted::CursorState::failed) fail("invalid_cursor", "SQL rows cursor has failed");
    if (state != weighted::CursorState::active) return std::nullopt;
    // Decode/copy can fail after native next() succeeds. This one boundary
    // makes such a cursor terminal and releases its reader lease immediately.
    try {
      if (program.wrapper() == frontend::SqlWrapper::exists) {
        if (emitted) { native.cancel(); state = weighted::CursorState::exhausted; return std::nullopt; }
        output[0] = storage::ScalarView{exists};
        auto row = Tuple::copy_of(account, output, resource::MemoryPurpose::output_buffer);
        emitted = true; return Result{std::move(row), 1, program};
      }
      const auto row = native.next();
      if (!row) { state = weighted::CursorState::exhausted; return std::nullopt; }
      const auto fields = row->tuple.values();
      struct Borrows { Items<Cell>& values; ~Borrows() { std::fill(values.begin(), values.end(), Cell{}); } } borrows{output};
      const auto columns = program.outputs();
      for (std::size_t i = 0; i < columns.size(); ++i) {
        if (const auto* field = std::get_if<frontend::SqlRowsResultField>(&columns[i].value)) {
          if (field->presence && !std::get<bool>(fields[*field->presence])) output[i].reset();
          else output[i] = fields[field->payload];
        } else output[i] = program.initial_values()[std::get<frontend::ExpressionId>(columns[i].value).value];
      }
      auto result = Tuple::copy_of(account, output, resource::MemoryPurpose::output_buffer);
      // Payload/presence encoding is injective in the ordered SQL outputs;
      // repeated and constant outputs add no hidden distinguishing core fields.
      const auto weight = program.semantics() == frontend::SqlSemantics::set ? 1 : row->multiplicity.value;
      return Result{std::move(result), weight, program};
    } catch (...) { native.cancel(); state = weighted::CursorState::failed; throw; }
  }
};

// Copy only the genuine immutable tree/options recipe; the source export and
// actual lower_tree factory revalidate the complete coupling. These cold DTOs
// use existing compiler allocation conventions and are never retained live.
std::shared_ptr<detail::StorageWorkContext> detail::SqlColdRebuild::context(const resource::MemoryAccount& account,
    const SourceSnapshot& image,const RebuildLimits& limits) {
  if(!account)throw resource::MemoryFailure(resource::MemoryFault::contract);
  if(!image.program || !image.native_program)
    fail("invalid_sql_rows_snapshot","physical image requires genuine source and native programs");
  if(image.rows.size()>limits.rows || (!image.sequence && !image.rows.empty()))
    fail("invalid_sql_rows_snapshot","physical image exceeds its row bound or nonempty epoch-zero state");
  if(!limits.lowering.work_limit || !limits.lowering.identity.work_limit)
    fail("invalid_options","cold lowering and identity work must be finite");
  if(image.native_program.options().indexed_storage.has_value()!=limits.indexed_work.has_value())
    fail("invalid_options","cold indexed grant must exactly match the authentic backend kind");
  return resource::make_accounted_shared<StorageWorkContext>(account,resource::MemoryPurpose::support_metadata,
      account,limits.indexed_work);
}
SqlRowsRuntime detail::SqlColdRebuild::empty(const resource::MemoryAccount& account,const SourceSnapshot& image,
    frontend::SqlRowsProgram source,Options requested,const RebuildLimits& limits,const std::shared_ptr<StorageWorkContext>& context,
    storage::IndexWorkAllowance& source_work,RebuildMetrics& metrics) {
  // Selected cold recipe admissions precede its owning export. Map/set sorting
  // and compiler validation/JSON costs retain their existing separate contracts.
  frontend::rows_detail::step(&source_work);
  source_work.admit(storage::IndexWork{.scalar_bytes=static_cast<std::uint64_t>(image.program.source().size())});
  const auto& actual=image.native_program;
  for(const auto& node:actual.tree().nodes) {
    frontend::rows_detail::step(&source_work);
    source_work.admit(storage::IndexWork{.scalar_fields=static_cast<std::uint64_t>(node.scope.size()+node.children.size()),
        .scalar_bytes=static_cast<std::uint64_t>(node.id.size())});
  }
  const auto tree=planner::compiler_source_detail::tree(actual.tree());
  const auto physical=planner::compiler_source_detail::options(actual.options());
  const auto core=source.export_core();
  auto shape=planner::lower_tree(core.catalog,core.query,tree,physical,limits.lowering);
  if(shape.physical_sha256()!=actual.physical_sha256() ||
      shape.physical_source_sha256()!=actual.physical_source_sha256())
    fail("sql_rows_snapshot_binding","source image does not reproduce its actual native shape");
  if(requested.native.multiplicity_limit!=image.native_binding.multiplicity_limit)
    fail("sql_rows_snapshot_binding","operational multiplicity limit differs from the image binding");
  metrics.lowering_work=shape.work();
  requested.source_work_limit=limits.source_work;requested.native.work_limit=limits.native_work;
  requested.native.capture_changes=false;requested.native.capture_events=false;
  auto rebuilt=native(account,shape,requested.native,context,image.sequence?image.sequence-1:0);
  if(rebuilt.binding()!=image.native_binding)
    fail("sql_rows_snapshot_binding","weighted binding differs from the genuine rebuilt source");
  return SqlRowsRuntime(resource::make_accounted_shared<SqlRowsRuntime::Data>(account,
      resource::MemoryPurpose::support_metadata,account,std::move(source),std::move(rebuilt),requested));
}
SqlRowsRuntime::PreparedBatch detail::SqlColdRebuild::seed(SqlRowsRuntime& target,const SourceSnapshot& image,
    storage::IndexWorkAllowance& source_work,weighted::DeltaCapture capture) {
  auto& owner=target.data();
  // One owned descriptor vector; row payloads borrow the immutable image only
  // until this function returns. New persistent tuples copy into the receiver.
  Items<SourceReplacement> edits(allocator<SourceReplacement>(owner.account,resource::MemoryPurpose::scratch));
  constexpr auto words=(sizeof(SourceReplacement)+sizeof(void*)-1)/sizeof(void*);
  if(image.rows.size()>UINT64_MAX/words)
    fail("invalid_sql_rows_snapshot","physical image descriptor count overflows");
  source_work.admit(storage::IndexWork{.pointer_slots=static_cast<std::uint64_t>(image.rows.size())*words});
  edits.reserve(image.rows.size());
  for(const auto& entry:image.rows) {
    frontend::rows_detail::step(&source_work);
    if(!entry.weight)fail("invalid_sql_rows_snapshot","physical image contains a zero-weight row");
    edits.push_back({entry.source,entry.row.view(),0,entry.weight});
  }
  // Expected zero on every unique positive row rejects any duplicate complete
  // source identity; existing validation enforces full types and final keys/FKs.
  const NetBatch batch{image.sequence,edits};
  auto pending=owner.native.begin_epoch(image.sequence,capture);
  return SqlRowsRuntime::PreparedBatch(resource::make_accounted_unique<SqlRowsRuntime::PreparedBatch::Data>(
      owner.account,resource::MemoryPurpose::scratch,target.data_,batch,std::move(pending),source_work));
}
void detail::SqlColdRebuild::close_source(SqlRowsRuntime& target,Options options) {
  auto& owner=target.data();close_native(owner.native,options.native);
  options.native.memory_limit_bytes=owner.account.statistics().limit_bytes;owner.options=options;
}
SqlRowsRuntime SqlRowsRuntime::rebuild_into(const resource::MemoryAccount& account,const SourceSnapshot& image,
    Options options,const RebuildLimits& limits,RebuildMetrics* observed) {
  RebuildMetrics metrics;storage::IndexWorkAllowance source_work(limits.source_work,true);
  auto context=detail::SqlColdRebuild::context(account,image,limits);
  auto rebuilt=[&] {
    detail::StorageOperation operation(context);
    auto result=detail::SqlColdRebuild::empty(account,image,image.program,options,limits,context,source_work,metrics);
    if(image.sequence) {
      auto pending=detail::SqlColdRebuild::seed(result,image,source_work,weighted::DeltaCapture::disabled);
      auto epoch=pending.commit();metrics.native_work=epoch.native.metrics.work;
    }
    metrics.source_work=consumed(limits.source_work,source_work.remaining());
    if(context->indexed())metrics.indexed_work=consumed(context->limit(),detail::compact_storage_work(context)->remaining());
    return result;
  }(); // Every cold token, journal, result and operation closes before replacement.
  detail::SqlColdRebuild::close_source(rebuilt,options);
  if (observed) *observed = metrics;
  return rebuilt;
}

SqlRowsRuntime::SqlRowsRuntime(std::shared_ptr<Data> value) noexcept : data_(std::move(value)) {}
sql_rows::SourceSnapshot::SourceSnapshot(const resource::MemoryAccount& account, std::uint64_t epoch,
    const frontend::SqlRowsProgram& source, const CompiledProgram& native, const weighted::Binding& binding)
    : sequence(epoch), program(source), native_program(native), native_binding(binding),
      rows(resource::OwnerAllocator<SourceEntry>(account, resource::MemoryPurpose::output_buffer)) {}
SqlRowsRuntime::SqlRowsRuntime(frontend::SqlRowsProgram source, const FreeConnexTree& tree,
    const PhysicalOptions& physical, Options options)
    : SqlRowsRuntime(create_into(resource::MemoryAccount::create(options.native.memory_limit_bytes),
          std::move(source), tree, physical, options)) {}
SqlRowsRuntime SqlRowsRuntime::create_into(const resource::MemoryAccount& account,
    frontend::SqlRowsProgram source, const FreeConnexTree& tree, const PhysicalOptions& physical, Options options) {
  if (!account) throw resource::MemoryFailure(resource::MemoryFault::contract);
  return SqlRowsRuntime(resource::make_accounted_shared<Data>(account, resource::MemoryPurpose::support_metadata,
      account, std::move(source), tree, physical, options));
}
SqlRowsRuntime::SqlRowsRuntime(SqlRowsRuntime&&) noexcept = default;
SqlRowsRuntime& SqlRowsRuntime::operator=(SqlRowsRuntime&&) noexcept = default;
SqlRowsRuntime::~SqlRowsRuntime() = default;
SqlRowsRuntime::Data& SqlRowsRuntime::data() const {
  if (!data_) fail("invalid_sql_rows_runtime", "SQL rows runtime handle is empty");
  return *data_;
}
const frontend::SqlRowsProgram& SqlRowsRuntime::program() const & { return data().program; }
std::uint64_t SqlRowsRuntime::sequence() const { return data().native.sequence(); }
std::string_view SqlRowsRuntime::engine() const { return data().native.engine(); }
bool SqlRowsRuntime::ready() const { return data_ && data_->native.ready(); }
weighted::Multiplicity SqlRowsRuntime::root_weight() const { return data().native.root_weight(); }
resource::MemoryStatistics SqlRowsRuntime::accounted_memory_statistics() const { return data().account.statistics(); }
Epoch SqlRowsRuntime::apply(const Update& update) { return data().apply(update); }
std::uint64_t SqlRowsRuntime::source_weight(TableId id, std::span<const Cell> values) const {
  auto& d = data(); static_cast<void>(d.native.root_weight()); // Reject private batch state; readers remain allowed.
  d.validate(d.source(id), values, nullptr); return count(d.sources[id.value], values);
}
bool SqlRowsRuntime::fused_available() const {
  const auto& d = data(); return d.native.fused_available() && d.program.constraints().empty();
}
bool SqlRowsRuntime::prepare_fused(const NetBatch& batch, keyed::WeightSink& sink) {
  auto& d = data();
  if (!fused_available()) fail("sql_rows_fused_unavailable", "fused batches need the keyed core and no key constraints");
  if (d.fused) fail("sql_rows_busy", "a fused SQL batch is already open");
  d.native.fused_begin(batch.sequence);
  d.fused.emplace(d.take(d.spare_rows));
  try {
    Data::Scratch scratch{d};
    auto& rows = *d.fused;
    // Chain the net edits per source row against committed weights.
    for (const auto& edit : batch.replacements) {
      const auto& table = d.source(edit.source);
      d.validate(table, edit.values, nullptr);
      const auto hash = sql_detail::hash_cells(edit.values);
      if (auto* queued = rows.find(edit.source.value, edit.values, hash)) {
        if (queued->payload.after != edit.before)
          fail("sql_rows_weight_mismatch", "duplicate source edits do not form an expected-weight chain");
        queued->payload.after = edit.after;
        continue;
      }
      auto& target = d.sources[edit.source.value];
      const auto position = target.find(edit.values, hash);
      const auto current = position == absent ? 0 : target.at(position).value;
      if (current != edit.before) fail("sql_rows_weight_mismatch", "SQL prior source weight differs from committed state");
      if (edit.before == edit.after) continue;
      auto owned = position != absent ? target.at(position).key : Tuple::copy_of(d.account, edit.values);
      rows.add(edit.source.value, std::move(owned), hash, Proposal{&target, position != absent, current, edit.after});
    }
    // Publication inserts without allocating.
    for (const auto& item : rows.items())
      if (!item.payload.present && item.payload.after && item.payload.before != item.payload.after) item.payload.target->reserve(1);
    bool changed = false;
    for (const bool decreasing : {true, false}) {
      for (const auto& item : rows.items()) {
        const auto& proposal = item.payload;
        if (proposal.before == proposal.after || (proposal.after < proposal.before) != decreasing) continue;
        if (proposal.after > d.options.native.multiplicity_limit)
          fail("sql_rows_overflow", "final SQL source weight exceeds the configured multiplicity limit");
        changed = true;
        if (d.program.contradiction()) continue;
        for (const auto id : d.source(TableId{item.domain}).occurrences) {
          const auto& occurrence = d.program.occurrences()[id.value];
          d.projected_used = std::max(d.projected_used, occurrence.projection.size());
          const auto output = std::span<storage::ScalarView>(d.projected.data(), occurrence.projection.size());
          if (frontend::rows_detail::adapt(d.program, occurrence, item.key.view(), d.values, output, nullptr))
            d.native.fused_stage(d.nodes[id.value], storage::RowView::borrow(output), {proposal.before}, {proposal.after}, &sink);
        }
      }
    }
    return changed;
  } catch (...) { rollback_fused(); throw; }
}
weighted::Epoch SqlRowsRuntime::commit_fused() {
  auto& d = data();
  if (!d.fused) fail("invalid_epoch", "no fused SQL batch is open");
  auto epoch = d.native.fused_commit();
  for (auto& item : d.fused->items()) {
    const auto& proposal = item.payload;
    if (proposal.before != proposal.after)
      publish_count(*proposal.target, std::move(item.key), item.hash, proposal.present, proposal.after);
  }
  Data::give(d.spare_rows, *d.fused); d.fused.reset();
  return epoch;
}
void SqlRowsRuntime::rollback_fused() noexcept {
  if (!data_ || !data_->fused) return;
  auto& d = *data_;
  d.native.fused_rollback();
  Data::give(d.spare_rows, *d.fused); d.fused.reset();
}
sql_rows::SourceSnapshot SqlRowsRuntime::source_snapshot(sql_rows::SourceSnapshotLimits limits) const {
  const auto& d = data();
  if (!d.native.ready()) fail("sql_rows_busy", "physical source image requires a quiescent runtime");
  storage::IndexWorkAllowance work(limits.work_limit, true);
  work.admit({.structural_steps = 1});
  std::uint64_t count = 0;
  for (const auto& table : d.sources) {
    work.admit({.structural_steps = 1});
    if (table.size() > limits.rows - count)
      fail("sql_rows_source_limit", "physical source image row limit exceeded");
    count += table.size();
  }
  sql_rows::SourceSnapshot result(d.account, d.native.sequence(), d.program,
      d.native.structural_program(), d.native.binding());
  result.rows.reserve(static_cast<std::size_t>(count));
  // Hash-ordered tables are presented in the source's exact tuple order.
  Items<const Counts::Entry*> order(allocator<const Counts::Entry*>(d.account, resource::MemoryPurpose::scratch));
  for (std::size_t i = 0; i < d.sources.size(); ++i) {
    work.admit({.structural_steps = 1});
    order.clear();
    for (const auto& entry : d.sources[i].entries()) order.push_back(&entry);
    std::sort(order.begin(), order.end(), [](const Counts::Entry* a, const Counts::Entry* b) {
      return sql_detail::less(a->key.view(), b->key.view());
    });
    for (const auto* entry : order) {
      const auto& row = entry->key; const auto weight = entry->value;
      work.admit({.structural_steps = 1});
      for (const auto& cell : row.view()) {
        std::uint64_t bytes = 0;
        if (cell) if (const auto* text = std::get_if<std::string_view>(&*cell)) bytes = text->size();
        work.admit({.scalar_fields = 1, .scalar_bytes = bytes});
      }
      result.rows.push_back({TableId{i}, row, weight});
    }
  }
  work.admit({.structural_steps = 1});
  result.work = consumed(limits.work_limit, work.remaining());
  return result;
}
SqlRowsRuntime::ResultCursor SqlRowsRuntime::results(weighted::CursorOptions options) const {
  auto& d = data(); auto cursor = d.native.results(options); const auto present = d.native.root_weight().value != 0;
  return ResultCursor(resource::make_accounted_unique<ResultCursor::Data>(d.account,
      resource::MemoryPurpose::output_buffer, d.account, d.program, std::move(cursor), present));
}
SqlRowsRuntime::PreparedBatch SqlRowsRuntime::prepare_batch(const NetBatch& batch,weighted::DeltaCapture capture) {
  auto& d=data();
  auto pending=d.native.begin_epoch(batch.sequence,capture);
  return PreparedBatch(resource::make_accounted_unique<PreparedBatch::Data>(d.account,
      resource::MemoryPurpose::scratch,data_,batch,std::move(pending)));
}
SqlRowsRuntime::PreparedBatch SqlRowsRuntime::prepare_output_batch(const NetBatch& batch,OutputLimits limits) {
  const auto& program=data().program;
  const auto capture=program.wrapper()==frontend::SqlWrapper::exists?weighted::DeltaCapture::disabled:
      program.semantics()==frontend::SqlSemantics::set?weighted::DeltaCapture::support:weighted::DeltaCapture::enabled;
  auto prepared=prepare_batch(batch,capture);auto& state=prepared.data();state.output_limits=limits;
  if(*state.output_size()>limits.rows)
    fail("sql_rows_output_limit","SQL change count exceeds the output allowance");
  return prepared;
}
SqlRowsRuntime::PreparedBatch::PreparedBatch(resource::AccountedUnique<Data> value) noexcept:data_(std::move(value)) {}
SqlRowsRuntime::PreparedBatch::PreparedBatch(PreparedBatch&&) noexcept=default;
SqlRowsRuntime::PreparedBatch& SqlRowsRuntime::PreparedBatch::operator=(PreparedBatch&&) noexcept=default;
SqlRowsRuntime::PreparedBatch::~PreparedBatch()=default;
SqlRowsRuntime::PreparedBatch::Data& SqlRowsRuntime::PreparedBatch::data() const {
  if(!data_ || !data_->active())fail("invalid_sql_rows_batch","SQL net-batch token is closed or moved from");
  return *data_;
}
bool SqlRowsRuntime::PreparedBatch::active() const noexcept {return data_ && data_->active();}
std::uint64_t SqlRowsRuntime::PreparedBatch::sequence() const {return data().pending.preview().sequence;}
bool SqlRowsRuntime::PreparedBatch::changed() const {return data().changed;}
const frontend::SqlRowsProgram& SqlRowsRuntime::PreparedBatch::program() const & {return data().owner->program;}
storage::IndexWork SqlRowsRuntime::PreparedBatch::source_work() const {
  auto& d=data();return consumed(d.owner->options.source_work_limit,d.work.remaining());
}
const weighted::Epoch& SqlRowsRuntime::PreparedBatch::native_preview() const & {return data().pending.preview();}
std::optional<std::span<const weighted::BagDelta>> SqlRowsRuntime::PreparedBatch::native_bag_delta_preview() const & {
  return data().pending.bag_delta_preview();
}
std::optional<std::size_t> SqlRowsRuntime::PreparedBatch::output_size() const {return data().output_size();}
OutputChangeView SqlRowsRuntime::PreparedBatch::output_change(std::size_t index,std::span<Cell> scratch) const & {
  return data().output_change(index,scratch);
}
std::uint64_t SqlRowsRuntime::PreparedBatch::output_work() const {return data().output_spent;}
Epoch SqlRowsRuntime::PreparedBatch::commit() {
  auto result=data().commit();data_.reset();return result;
}
void SqlRowsRuntime::PreparedBatch::rollback() noexcept {data_.reset();}

SqlRowsRuntime::ResultCursor::ResultCursor(resource::AccountedUnique<Data> value) noexcept : data_(std::move(value)) {}
SqlRowsRuntime::ResultCursor::ResultCursor(ResultCursor&&) noexcept = default;
SqlRowsRuntime::ResultCursor& SqlRowsRuntime::ResultCursor::operator=(ResultCursor&&) noexcept = default;
SqlRowsRuntime::ResultCursor::~ResultCursor() = default;
SqlRowsRuntime::ResultCursor::Data& SqlRowsRuntime::ResultCursor::data() const {
  if (!data_) fail("invalid_cursor", "SQL rows cursor handle is empty");
  return *data_;
}
bool SqlRowsRuntime::ResultCursor::active() const noexcept { return data_ && data_->state == weighted::CursorState::active; }
weighted::CursorState SqlRowsRuntime::ResultCursor::state() const { return data().state; }
std::uint64_t SqlRowsRuntime::ResultCursor::sequence() const { return data().native.sequence(); }
std::optional<Result> SqlRowsRuntime::ResultCursor::next() { return data().next(); }
void SqlRowsRuntime::ResultCursor::cancel() noexcept {
  if (active()) { data_->native.cancel(); data_->state = weighted::CursorState::cancelled; }
}
}  // namespace crown::runtime
