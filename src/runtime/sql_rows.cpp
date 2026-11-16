#include "crown/runtime/sql_rows.hpp"
#include "sql_cold_rebuild.hpp"
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

// Immutable nullable keys support borrowed probes. NULL sorts first; all
// present alternatives use the same exact scalar order as the native core.
struct Less {
  using is_transparent = void;
  static bool compare(std::span<const Cell> a, std::span<const Cell> b) noexcept {
    return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
  }
  bool operator()(const Tuple& a, const Tuple& b) const noexcept { return compare(a.view(), b.view()); }
  bool operator()(const Tuple& a, std::span<const Cell> b) const noexcept { return compare(a.view(), b); }
  bool operator()(std::span<const Cell> a, const Tuple& b) const noexcept { return compare(a, b.view()); }
};
using Counts = std::map<Tuple, std::uint64_t, Less,
    resource::MemoryAllocator<std::pair<const Tuple, std::uint64_t>>>;

// A detached node uses the receiving map's allocator. Insertion after native
// commit therefore allocates nothing; the comparator is nonthrowing.
Counts::node_type node_for(Counts& target, Tuple key, std::uint64_t value) {
  Counts prepared(target.key_comp(), target.get_allocator());
  return prepared.extract(prepared.emplace(std::move(key), value).first);
}
std::uint64_t count(const Counts& values, std::span<const Cell> key) {
  const auto found = values.find(key); return found == values.end() ? 0 : found->second;
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

struct SqlRowsRuntime::Data {
  struct Edit {
    Counts* target;
    Counts::iterator position;
    std::uint64_t after;
    Counts::node_type inserted;
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
      sources.emplace_back(Less{}, allocator<Counts::value_type>(owner, resource::MemoryPurpose::source_counts));
      maximum_edits = std::max(maximum_edits, table.constraints.size());
    }
    for (const auto& constraint : program.constraints()) {
      keys.emplace_back(Less{}, allocator<Counts::value_type>(owner, resource::MemoryPurpose::support_metadata));
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
      auto& target = keys[index]; const auto found = target.find(*selected);
      frontend::rows_detail::step(&work);
      const auto before = constraint.parent ? std::uint64_t(update.before != 0) : update.before;
      const auto after = constraint.parent ? std::uint64_t(update.after != 0) : update.after;
      const auto next = replace_count(found == target.end() ? 0 : found->second, before, after);
      if (constraint.parent) {
        if (update.after && !proposed_count(*constraint.parent, *selected, update, work))
          fail("foreign_key_violation", "SQL source foreign key has no live parent");
      } else {
        if (next > 1) fail("unique_violation", "SQL source UNIQUE key has more than one row");
        if (!next) for (const auto reference : constraint.referenced_by)
          if (proposed_count(reference, *selected, update, work))
            fail("foreign_key_violation", "SQL source parent key is still referenced");
      }
      if (next == (found == target.end() ? 0 : found->second)) continue;
      Counts::node_type inserted;
      if (found == target.end() && next)
        inserted = node_for(target, Tuple::copy_of(account, *selected), next);
      edits.push_back({&target, found, next, std::move(inserted)});
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
    auto& rows = sources[update.source.value]; const auto found = rows.find(update.values);
    frontend::rows_detail::step(&work);
    const auto actual = found == rows.end() ? 0 : found->second;
    if (actual != update.before) fail("sql_rows_weight_mismatch", "SQL prior source weight differs from committed state");
    Counts::node_type inserted;
    if (update.before != update.after) {
      if (found == rows.end() && update.after)
        inserted = node_for(rows, Tuple::copy_of(account, update.values), update.after);
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
    // All throwing work is finished. Node handles share their destination
    // allocators; immutable validated keys have a nonthrowing comparator.
    if (update.before != update.after) {
      for (auto& edit : edits) {
        if (edit.position == edit.target->end()) edit.target->insert(std::move(edit.inserted));
        else if (!edit.after) edit.target->erase(edit.position);
        else edit.position->second = edit.after;
      }
      if (found == rows.end()) { if (update.after) rows.insert(std::move(inserted)); }
      else if (!update.after) rows.erase(found);
      else found->second = update.after;
    }
    return {update.before != update.after, spent, std::move(result)};
  }
};


// All SQL source/key state remains committed while one native token is private.
// The owner keeps committed iterators and shared tuple payloads alive even when
// its facade moves or dies. No caller row/Cell span survives construction.
struct SqlRowsRuntime::PreparedBatch::Data {
  struct Probe { std::size_t domain; std::span<const Cell> row; };
  struct Key { std::size_t domain; Tuple row; };
  struct Order {
    using is_transparent=void;
    bool operator()(const Key& a,const Key& b) const noexcept {
      return a.domain!=b.domain?a.domain<b.domain:Less::compare(a.row.view(),b.row.view());
    }
    bool operator()(const Key& a,Probe b) const noexcept {
      return a.domain!=b.domain?a.domain<b.domain:Less::compare(a.row.view(),b.row);
    }
    bool operator()(Probe a,const Key& b) const noexcept {
      return a.domain!=b.domain?a.domain<b.domain:Less::compare(a.row,b.row.view());
    }
  };
  struct Proposal {
    Counts* target;
    Counts::iterator position;
    std::uint64_t before,after;
    Counts::node_type inserted;
  };
  using Touched=std::map<Key,Proposal,Order,
      resource::MemoryAllocator<std::pair<const Key,Proposal>>>;
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
       rows(Order{},allocator<Touched::value_type>(owner->account,resource::MemoryPurpose::scratch)),
       keys(Order{},allocator<Touched::value_type>(owner->account,resource::MemoryPurpose::scratch)) {prepare(batch);}
  Data(std::shared_ptr<SqlRowsRuntime::Data> sql,const NetBatch& batch,WeightedRuntime::PendingEpoch native,
      storage::IndexWorkAllowance& cold)
      :owner(std::move(sql)),pending(std::move(native)),work(storage::detail::IndexWorkAlias::fixed(cold)),
       rows(Order{},allocator<Touched::value_type>(owner->account,resource::MemoryPurpose::scratch)),
       keys(Order{},allocator<Touched::value_type>(owner->account,resource::MemoryPurpose::scratch)) {prepare(batch);}
  void prepare(const NetBatch& batch) {
    SqlRowsRuntime::Data::Scratch scratch{*owner};
    for(const auto& edit:batch.replacements) {
      frontend::rows_detail::step(&work);
      const auto& table=owner->source(edit.source);
      owner->validate(table,edit.values,&work);
      if(edit.before==edit.after) {
        frontend::rows_detail::step(&work);const auto queued=rows.find(Probe{edit.source.value,edit.values});
        std::uint64_t current;
        if(queued!=rows.end())current=queued->second.after;
        else {frontend::rows_detail::step(&work);current=count(owner->sources[edit.source.value],edit.values);}
        if(current!=edit.before)fail("sql_rows_weight_mismatch","SQL prior source weight differs from proposed state");
        continue; // A no-op validates its chain but needs no new key/payload.
      }
      auto& proposal=touch(rows,edit.source.value,owner->sources[edit.source.value],edit.values,edit.before);
      proposal.after=edit.after; // Only the final chained weight is admitted below.
    }
    for(const auto& [key,proposal]:rows) {
      static_cast<void>(key);frontend::rows_detail::step(&work);
      if(proposal.after>owner->options.native.multiplicity_limit)
        fail("sql_rows_overflow","final SQL source weight exceeds the configured multiplicity limit");
      changed|=proposal.before!=proposal.after;
    }
    // Remove all key shares before adding any. This permits key swaps and
    // final-valid cyclic/self FK changes without transient counter overflow.
    update_keys(true);update_keys(false);validate_keys();
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
    frontend::rows_detail::step(&work);const auto queued=touched.find(Probe{id,row});
    if(queued!=touched.end()) {
      if(expected && queued->second.after!=*expected)
        fail("sql_rows_weight_mismatch","duplicate source edits do not form an expected-weight chain");
      return queued->second;
    }
    frontend::rows_detail::step(&work);const auto position=target.find(row);
    const auto current=position==target.end()?0:position->second;
    if(expected && current!=*expected)
      fail("sql_rows_weight_mismatch","SQL prior source weight differs from committed state");
    Tuple owned;
    if(position!=target.end())owned=position->first; // Actual shared immutable Tuple copy.
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
    return touched.emplace(Key{id,std::move(owned)},Proposal{&target,position,current,current,{}}).first->second;
  }
  void update_keys(bool decreasing) {
    for(const auto& [source_key,proposal]:rows) {
      frontend::rows_detail::step(&work);
      if(proposal.before==proposal.after)continue;
      const auto& table=owner->source(TableId{source_key.domain});
      for(const auto index:table.constraints) {
        frontend::rows_detail::step(&work);const auto& constraint=owner->program.constraints()[index];
        const auto before=constraint.parent?std::uint64_t(proposal.before!=0):proposal.before;
        const auto after=constraint.parent?std::uint64_t(proposal.after!=0):proposal.after;
        if(before==after || (after<before)!=decreasing)continue;
        const auto selected=owner->project_key(constraint,source_key.row.view(),owner->key,owner->key_used,work);
        if(!selected)continue; // NULLS DISTINCT / MATCH SIMPLE; empty key is present.
        auto& key=touch(keys,index,owner->keys[index],*selected);
        key.after=replace_count(key.after,before,after);
      }
    }
  }
  std::uint64_t final_count(std::size_t id,std::span<const Cell> row) {
    frontend::rows_detail::step(&work);const auto found=keys.find(Probe{id,row});
    if(found!=keys.end())return found->second.after;
    frontend::rows_detail::step(&work);return count(owner->keys[id],row);
  }
  void validate_keys() {
    for(const auto& [key,proposal]:keys) {
      frontend::rows_detail::step(&work);const auto& constraint=owner->program.constraints()[key.domain];
      if(constraint.parent) {
        if(proposal.after && !final_count(*constraint.parent,key.row.view()))
          fail("foreign_key_violation","final SQL source foreign key has no live parent");
      } else {
        if(proposal.after>1)fail("unique_violation","final SQL UNIQUE key has more than one row");
        if(!proposal.after)for(const auto reference:constraint.referenced_by) {
          frontend::rows_detail::step(&work);
          if(final_count(reference,key.row.view()))
            fail("foreign_key_violation","final SQL source parent key is still referenced");
        }
      }
    }
  }
  void prepare_nodes(Touched& touched) {
    for(auto& [key,proposal]:touched) {
      frontend::rows_detail::step(&work);
      if(proposal.before!=proposal.after && proposal.position==proposal.target->end() && proposal.after)
        proposal.inserted=node_for(*proposal.target,key.row,proposal.after);
    }
  }
  void stage_native(bool decreasing) {
    for(const auto& [key,proposal]:rows) {
      frontend::rows_detail::step(&work);
      if(proposal.before==proposal.after || (proposal.after<proposal.before)!=decreasing)continue;
      if(owner->program.contradiction())continue;
      const auto& table=owner->source(TableId{key.domain});
      for(const auto id:table.occurrences) {
        frontend::rows_detail::step(&work);const auto& occurrence=owner->program.occurrences()[id.value];
        owner->projected_used=std::max(owner->projected_used,occurrence.projection.size());
        const auto output=std::span<storage::ScalarView>(owner->projected.data(),occurrence.projection.size());
        if(frontend::rows_detail::adapt(owner->program,occurrence,key.row.view(),owner->values,output,&work))
          static_cast<void>(pending.stage_contribution(owner->nodes[id.value],
              storage::TupleValuesView::borrow(storage::RowView::borrow(output)),
              {proposal.before},{proposal.after}));
      }
    }
  }
  static void publish(Touched& touched) noexcept {
    for(auto& [key,proposal]:touched) {
      static_cast<void>(key);
      if(proposal.before==proposal.after)continue;
      if(proposal.position==proposal.target->end()) {
        if(proposal.after)proposal.target->insert(std::move(proposal.inserted));
      } else if(!proposal.after)proposal.target->erase(proposal.position);
      else proposal.position->second=proposal.after;
    }
  }
  Epoch commit() {
    const auto spent=consumed(owner->options.source_work_limit,work.remaining());
    auto native=pending.commit(); // No throwing preparation remains after this barrier.
    publish(keys);publish(rows);
    Epoch result{changed,spent,std::move(native)};
    keys.clear();rows.clear();owner.reset();return result;
  }
  void rollback() noexcept {
    if(!owner)return;
    pending.rollback();keys.clear();rows.clear();owner.reset();
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
bool SqlRowsRuntime::ready() const { return data_ && data_->native.ready(); }
weighted::Multiplicity SqlRowsRuntime::root_weight() const { return data().native.root_weight(); }
resource::MemoryStatistics SqlRowsRuntime::accounted_memory_statistics() const { return data().account.statistics(); }
Epoch SqlRowsRuntime::apply(const Update& update) { return data().apply(update); }
std::uint64_t SqlRowsRuntime::source_weight(TableId id, std::span<const Cell> values) const {
  auto& d = data(); static_cast<void>(d.native.root_weight()); // Reject private batch state; readers remain allowed.
  d.validate(d.source(id), values, nullptr); return count(d.sources[id.value], values);
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
  for (std::size_t i = 0; i < d.sources.size(); ++i) {
    work.admit({.structural_steps = 1});
    for (const auto& [row, weight] : d.sources[i]) {
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
