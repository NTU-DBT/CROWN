#include "star_detail.hpp"
#include "crown/storage/accounted_index_work.hpp"
#include <algorithm>

namespace crown::runtime::star {
namespace sd = detail;
namespace {
storage::RowView scalar_key(const storage::ScalarView& value) noexcept {
  return storage::RowView::borrow(std::span<const storage::ScalarView>(&value, 1));
}
bool above_twice(std::uint64_t value, std::uint64_t threshold) noexcept {
  return value > threshold && value - threshold > threshold;
}
std::optional<std::uint64_t> epoch_threshold(std::uint64_t scale, std::size_t d) noexcept {
  if (d == 1) return 1;
  if (scale == UINT64_MAX) return {};
  return sd::HIndex::power(scale + 1, d - 1);
}
CompiledProgram import_program(const resource::MemoryAccount& account, const PhysicalPlan& plan,
    storage::IndexWork limit) {
  if (const auto& indexed = plan.options().indexed_storage) {
    const auto& cap = indexed->per_operation;
    limit.structural_steps = std::min(limit.structural_steps, cap.structural_steps);
    limit.scalar_fields = std::min(limit.scalar_fields, cap.scalar_fields);
    limit.scalar_bytes = std::min(limit.scalar_bytes, cap.scalar_bytes);
    limit.pointer_slots = std::min(limit.pointer_slots, cap.pointer_slots);
    limit.link_actions = std::min(limit.link_actions, cap.link_actions);
  }
  auto work = storage::AccountedIndexWork::create(account, limit);
  return CompiledProgram::freeze(account, plan, work.get());
}
} // namespace

Runtime::Data::Data(PhysicalRuntime source, const planner::star::Plan& plan, std::uint64_t limit,
    storage::IndexWork metadata_work)
    : account(source.plan().account()), program(import_program(account, plan.general(), metadata_work)),
      sources(std::move(source)), work_limit(limit), center(plan.center_table()),
      dimensions(sd::allocator<sd::Dimension>(account, resource::MemoryPurpose::immutable_metadata)),
      routes(program.source_catalog().tables.size(), {},
          sd::allocator<std::optional<std::size_t>>(account, resource::MemoryPurpose::immutable_metadata)),
      head(sd::allocator<FieldId>(account, resource::MemoryPurpose::immutable_metadata)),
      free(plan.dimension(), 0, sd::allocator<std::uint8_t>(account, resource::MemoryPurpose::immutable_metadata)),
      facts(sd::rows<sd::Fact>(account)), groups(sd::rows<sd::Group>(account)), live(sd::set<sd::Group>(account)) {
  dimensions.reserve(plan.dimension());
  for (std::size_t i = 0; i < plan.dimension(); ++i) {
    const auto satellite = plan.satellite_tables()[i];
    dimensions.emplace_back(account, plan.dimension(), satellite.has_value());
    if (satellite) routes[satellite->value] = i;
  }
  head.reserve(plan.head_coordinates().size());
  for (const auto coordinate : plan.head_coordinates()) {
    head.push_back(FieldId{coordinate}); free[coordinate] = 1;
  }
}
void Runtime::Data::readable() const {
  if (updating || !sources.ready()) throw Error("star_busy", "a private star source update is active");
}
storage::RowView Runtime::Data::head_key(const sd::Fact& fact, sd::Scratch& scratch) const {
  scratch.head.clear();
  for (const auto field : head) scratch.head.push_back(fact.values->view()[field.value]);
  return storage::RowView::borrow(scratch.head);
}
storage::RowView Runtime::Data::group_key(const sd::Fact& fact, sd::Scratch& scratch) const {
  scratch.group.clear(); scratch.heavy.clear();
  // A Boolean flag plus one value per coordinate encodes the full dynamic mask.
  // Light slots use the same ignored integer sentinel. No machine-word arity cap.
  for (auto* key : fact.keys) {
    scratch.group.emplace_back(key->heavy);
    if (key->heavy) {
      scratch.group.push_back(key->values->view()[0]);
      scratch.heavy.push_back(key);
    } else scratch.group.emplace_back(std::int64_t{0});
  }
  return storage::RowView::borrow(scratch.group);
}

// VS stores every light-eligible center row once. A group keeps counted DISTINCT
// full-head projections; VC is only the live-group set, never an eager union.
void Runtime::Data::attach(sd::Fact& fact, sd::Journal& journal, sd::Budget& budget, sd::Scratch& scratch) {
  sd::require(fact.missing == 0 && !fact.group, "invalid light-filter attachment");
  budget.take(); ++budget.metrics.projection_changes;
  const auto identity = group_key(fact, scratch);
  auto found = groups.find(identity);
  if (found == groups.end()) {
    found = journal.emplace(groups, storage::AccountedRow::copy_of(account, identity, sd::memory),
        sd::Group(account, std::span<sd::Key* const>(scratch.heavy.data(), scratch.heavy.size())));
    found->second.identity = &found->first;
    for (auto* key : found->second.heavy) journal.emplace(key->groups, &found->second);
  }
  auto& group = found->second;
  const auto output = head_key(fact, scratch);
  auto projected = group.projections.find(output);
  if (projected == group.projections.end())
    journal.emplace(group.projections, storage::AccountedRow::copy_of(account, output, sd::memory), std::uint64_t{1});
  else {
    sd::require(projected->second != UINT64_MAX, "projected support overflow");
    journal.assign(projected->second, projected->second + 1);
  }
  sd::require(group.supports != UINT64_MAX, "group support overflow");
  journal.assign(group.supports, group.supports + 1);
  journal.assign(fact.group, &group);
  if (group.supports == 1 && group.missing == 0) journal.emplace(live, &group);
}
void Runtime::Data::detach(sd::Fact& fact, sd::Journal& journal, sd::Budget& budget, sd::Scratch& scratch) {
  if (!fact.group) return;
  budget.take(); ++budget.metrics.projection_changes;
  auto& group = *fact.group;
  const auto projected = group.projections.find(head_key(fact, scratch));
  sd::require(projected != group.projections.end() && group.supports != 0, "missing projected support");
  if (projected->second == 1) journal.erase(group.projections, projected);
  else journal.assign(projected->second, projected->second - 1);
  journal.assign(group.supports, group.supports - 1);
  journal.assign(fact.group, static_cast<sd::Group*>(nullptr));
  if (group.supports) return;
  if (!group.missing) journal.erase(live, live.find(&group));
  for (auto* key : group.heavy) journal.erase(key->groups, key->groups.find(&group));
  journal.erase(groups, groups.find(group.identity->view()));
}

// Degree-directory edits move one intrusive key between occupied-degree buckets.
// Every pointer/count inverse is funded before mutation. Zero buckets disappear.
void Runtime::Data::degree(sd::Dimension& dimension, sd::Key& key, std::uint64_t next,
    sd::Journal& journal, sd::Budget& budget) {
  budget.take();
  if (key.degree) {
    const auto old = dimension.buckets.find(key.degree);
    sd::require(old != dimension.buckets.end() && old->second.count, "missing degree bucket");
    if (key.previous) journal.assign(key.previous->next, key.next);
    else journal.assign(old->second.head, key.next);
    if (key.next) journal.assign(key.next->previous, key.previous);
    journal.assign(key.previous, static_cast<sd::Key*>(nullptr));
    journal.assign(key.next, static_cast<sd::Key*>(nullptr));
    journal.assign(old->second.count, old->second.count - 1);
    if (!old->second.count) journal.erase(dimension.buckets, old);
  }
  journal.assign(key.degree, next);
  if (!next) return;
  auto target = dimension.buckets.find(next);
  if (target == dimension.buckets.end()) target = journal.emplace(dimension.buckets, next, sd::Bucket{});
  journal.assign(key.next, target->second.head);
  if (target->second.head) journal.assign(target->second.head->previous, &key);
  journal.assign(target->second.head, &key);
  journal.assign(target->second.count, target->second.count + 1);
}

// A relabel changes roles without changing real sources, degrees or H. Detach
// the old VS contributions, change the label, then attach the new contributions.
// Only this key's incident rows move; unchanged heavy buckets are never rebuilt.
void Runtime::Data::relabel(sd::Dimension& dimension, sd::Key& key, bool heavy,
    sd::Journal& journal, sd::Budget& budget, sd::Scratch& scratch) {
  if (key.heavy == heavy) return;
  budget.take(); ++budget.metrics.key_relabels;
  for (auto* fact : key.facts) {
    budget.take(); ++budget.metrics.center_visits; ++budget.metrics.migrated_rows;
    detach(*fact, journal, budget, scratch);
  }
  journal.assign(key.heavy, heavy);
  if (heavy) journal.emplace(dimension.heavy, &key);
  else journal.erase(dimension.heavy, dimension.heavy.find(&key));
  for (auto* fact : key.facts) {
    budget.take(); ++budget.metrics.center_visits;
    std::size_t missing = 0;
    for (const auto* field : fact->keys) missing += !field->heavy && !field->present;
    journal.assign(fact->missing, missing);
    if (!missing) attach(*fact, journal, budget, scratch);
  }
}
void Runtime::Data::rebalance(sd::Dimension& dimension, sd::Key& changed, std::uint64_t h,
    sd::Journal& journal, sd::Budget& budget, sd::Scratch& scratch) {
  budget.take();
  const auto threshold = dimension.threshold;
  if (changed.heavy && (!threshold || changed.degree < *threshold / 2 + *threshold % 2))
    relabel(dimension, changed, false, journal, budget, scratch);
  else if (!changed.heavy && threshold && above_twice(changed.degree, *threshold))
    relabel(dimension, changed, true, journal, budget, scratch);
  const auto heavy_count = static_cast<std::uint64_t>(dimension.heavy.size());
  if (!above_twice(heavy_count, dimension.scale) && h >= dimension.scale / 2 + dimension.scale % 2) return;

  ++budget.metrics.scale_resets;
  const auto scale = std::max(std::uint64_t{1}, h);
  const auto next = epoch_threshold(scale, dimensions.size());
  sd::Vector<sd::Key*> candidates(sd::allocator<sd::Key*>(account, resource::MemoryPurpose::scratch));
  candidates.reserve(dimension.heavy.size());
  for (auto* key : dimension.heavy) { budget.take(); candidates.push_back(key); }
  if (next) {
    // Only old LIGHT keys in [new_tau,2*old_tau] can become heavy. Sparse
    // buckets skip arbitrary gaps and keys with small degree. Existing heavy
    // candidates above the band were already collected without touching rows.
    for (auto it = dimension.buckets.lower_bound(*next); it != dimension.buckets.end(); ++it) {
      budget.take();
      if (threshold && above_twice(it->first, *threshold)) break;
      for (auto* key = it->second.head; key; key = key->next) {
        budget.take(); if (!key->heavy) candidates.push_back(key);
      }
    }
  }
  for (auto* key : candidates)
    relabel(dimension, *key, next && key->degree >= *next, journal, budget, scratch);
  journal.assign(dimension.scale, scale);
  journal.assign(dimension.threshold, next);
}

void Runtime::Data::satellite(std::size_t coordinate, storage::RowView row, bool insertion,
    sd::Journal& journal, sd::Budget& budget, sd::Scratch& scratch) {
  auto& dimension = dimensions[coordinate];
  auto found = dimension.keys.find(row);
  if (found == dimension.keys.end()) {
    sd::require(insertion, "missing satellite source key");
    found = journal.emplace(dimension.keys, storage::AccountedRow::copy_of(account, row, sd::memory),
        sd::Key(account, false));
    found->second.values = &found->first;
  }
  auto& key = found->second;
  sd::require(key.present != insertion, "satellite source membership disagrees");
  budget.take(); ++budget.metrics.satellite_changes;
  journal.assign(key.present, insertion);
  if (key.heavy) {
    // No center row, head projection or result union is visited here.
    for (auto* group : key.groups) {
      budget.take(); ++budget.metrics.group_visits;
      if (insertion) {
        sd::require(group->missing != 0, "heavy predicate count underflow");
        journal.assign(group->missing, group->missing - 1);
        if (!group->missing) journal.emplace(live, group);
      } else {
        if (!group->missing) journal.erase(live, live.find(group));
        journal.assign(group->missing, group->missing + 1);
      }
    }
  } else {
    for (auto* fact : key.facts) {
      budget.take(); ++budget.metrics.center_visits;
      if (insertion) {
        sd::require(fact->missing != 0, "light predicate count underflow");
        journal.assign(fact->missing, fact->missing - 1);
        if (!fact->missing) attach(*fact, journal, budget, scratch);
      } else {
        detach(*fact, journal, budget, scratch);
        journal.assign(fact->missing, fact->missing + 1);
      }
    }
  }
  if (!key.degree && !key.present) journal.erase(dimension.keys, found);
}

void Runtime::Data::center_change(storage::RowView row, bool insertion, sd::Journal& journal,
    sd::Budget& budget, sd::Scratch& scratch, sd::Vector<sd::HIndex::Prepared>& histogram) {
  budget.take(); ++budget.metrics.center_changes; ++budget.metrics.center_visits;
  auto found = facts.find(row);
  sd::require(insertion == (found == facts.end()), "center source membership disagrees");
  if (insertion) {
    sd::require(facts.size() < UINT64_MAX, "center cardinality overflow");
    found = journal.emplace(facts, storage::AccountedRow::copy_of(account, row, sd::memory), sd::Fact(account, dimensions.size()));
    found->second.values = &found->first;
  }
  auto& fact = found->second;
  histogram.reserve(dimensions.size());
  for (std::size_t i = 0; i < dimensions.size(); ++i) {
    budget.take(); auto& dimension = dimensions[i];
    sd::Key* key;
    if (insertion) {
      const auto value = row[i];
      auto entry = dimension.keys.find(scalar_key(value));
      if (entry == dimension.keys.end()) {
        entry = journal.emplace(dimension.keys, storage::AccountedRow::copy_of(account, scalar_key(value), sd::memory),
            sd::Key(account, !dimension.satellite));
        entry->second.values = &entry->first;
      }
      key = &entry->second; fact.keys[i] = key;
    } else key = fact.keys[i];
    sd::require(insertion ? key->degree != UINT64_MAX : key->degree != 0, "center degree overflow/underflow");
    const auto next = insertion ? key->degree + 1 : key->degree - 1;
    histogram.push_back(dimension.h.prepare(key->degree, next, [&] { budget.take(); }));
    if (insertion) journal.emplace(key->facts, &fact);
  }
  if (!insertion) detach(fact, journal, budget, scratch);
  for (std::size_t i = 0; i < dimensions.size(); ++i) {
    auto& key = *fact.keys[i];
    if (!insertion) journal.erase(key.facts, key.facts.find(&fact));
    degree(dimensions[i], key, insertion ? key.degree + 1 : key.degree - 1, journal, budget);
  }
  if (insertion) {
    std::size_t missing = 0;
    for (const auto* key : fact.keys) missing += !key->heavy && !key->present;
    journal.assign(fact.missing, missing);
    if (!missing) attach(fact, journal, budget, scratch);
  }
  // Histogram tokens remain private until the same final source/view barrier.
  // Rebalancing reads their exact prospective H, never a source-size estimate.
  for (std::size_t i = 0; i < dimensions.size(); ++i) {
    auto& dimension = dimensions[i]; auto& key = *fact.keys[i];
    rebalance(dimension, key, histogram[i].next_h(), journal, budget, scratch);
    if (!key.degree && (!dimension.satellite || !key.present)) {
      sd::require(key.facts.empty() && key.groups.empty() && !key.heavy, "unreclaimed zero-degree key");
      journal.erase(dimension.keys, dimension.keys.find(key.values->view()));
    }
  }
  // Keep the fact in its map until the last use of its coordinate vector.
  // Raw references must not be dereferenced while a node handle owns it.
  if (!insertion) journal.erase(facts, found);
}

Runtime::Runtime(const planner::star::Plan& plan, Options options) {
  PhysicalRuntime sources(plan.source_only(), options.sources);
  const auto account = sources.plan().account();
  data_ = resource::make_accounted_shared<Data>(sd::memory, account, resource::MemoryPurpose::support_metadata,
      std::move(sources), plan, options.work, options.metadata_work);
}
Runtime::~Runtime() = default;
Runtime::Runtime(Runtime&&) noexcept = default;
Runtime& Runtime::operator=(Runtime&&) noexcept = default;
Runtime::Data& Runtime::data() const {
  if (!data_) throw Error("star_state", "star runtime was moved from");
  return *data_;
}
const CompiledProgram& Runtime::program() const & { return data().program; }
const resource::MemoryAccount& Runtime::account() const & { return data().account; }
std::uint64_t Runtime::sequence() const { const auto& d = data(); d.readable(); return d.sources.sequence(); }
bool Runtime::ready() const { const auto& d = data(); return !d.updating && !d.readers && d.sources.ready(); }
bool Runtime::has_answer() const { const auto& d = data(); d.readable(); return !d.live.empty(); }
Epoch Runtime::apply(const PhysicalSetUpdate& update) {
  auto& d = data(); d.readable();
  if (d.readers) throw Error("star_busy", "star cursors pin the committed epoch");
  // Covers source publication, histogram commit and private journal retirement
  // as one externally unreadable operation, including allocator callbacks.
  struct Writing {
    bool& flag;
    explicit Writing(bool& value) noexcept : flag(value) { flag = true; }
    ~Writing() { flag = false; }
  } writing(d.updating);
  auto source = d.sources.prepare(update);
  Metrics metrics; sd::Budget budget{metrics, d.work_limit}; budget.take();
  sd::Journal journal(d.account, budget);
  sd::Vector<sd::HIndex::Prepared> histogram(sd::allocator<sd::HIndex::Prepared>(d.account, resource::MemoryPurpose::scratch));
  const auto& preview = source.preview();
  if (preview.physical_changed && (update.table == d.center || d.routes[update.table.value])) {
    sd::Scratch scratch(d.account, d.dimensions.size(), d.head.size());
    sd::require(preview.source.has_value(), "changed source has no pinned row");
    const auto row = preview.source->tuple().values();
    const bool insertion = update.operation == SetOperation::insert;
    if (update.table == d.center) d.center_change(row, insertion, journal, budget, scratch, histogram);
    else d.satellite(*d.routes[update.table.value], row, insertion, journal, budget, scratch);
  }
  Epoch result{update.sequence, preview.physical_changed, preview.metrics, metrics};
  // Every fallible view edit and token allocation is complete. Valid source
  // commit is allocation-free; subsequent histogram/journal publication is
  // noexcept. Earlier failure unwinds this journal and the source token.
  const auto committed = source.commit();
  for (auto& token : histogram) token.commit();
  journal.commit();
  return result;
}
State Runtime::state() const {
  const auto& d = data(); d.readable();
  State result{d.sources.sequence(), static_cast<std::uint64_t>(d.facts.size()),
      static_cast<std::uint64_t>(d.groups.size()), static_cast<std::uint64_t>(d.live.size()),
      std::vector<DimensionState, resource::OwnerAllocator<DimensionState>>(
          resource::OwnerAllocator<DimensionState>(d.account, resource::MemoryPurpose::capture, sd::memory))};
  result.dimensions.reserve(d.dimensions.size());
  for (const auto& dimension : d.dimensions) result.dimensions.push_back({dimension.h.h(), dimension.scale,
      dimension.h.keys(), static_cast<std::uint64_t>(dimension.heavy.size()), dimension.threshold});
  return result;
}
std::optional<KeyState> Runtime::key(std::size_t coordinate, storage::ScalarView value) const {
  const auto& d = data(); d.readable();
  if (coordinate >= d.dimensions.size()) throw Error("star_coordinate", "star coordinate is outside the center");
  const auto& dimension = d.dimensions[coordinate]; const auto found = dimension.keys.find(scalar_key(value));
  if (found == dimension.keys.end()) return {};
  return KeyState{found->second.degree, found->second.heavy, found->second.present};
}
Database Runtime::source_snapshot() const { const auto& d = data(); d.readable(); return d.sources.snapshot().physical; }

// Cold O(d*N + maintained index entries) inspection, with funded scratch and
// one shared selected grant. It checks internal view consistency; independent
// original-CQ/source semantic agreement belongs to the separate A04 oracle.
void Runtime::check_invariants(std::uint64_t work) const {
  const auto& d = data(); d.readable(); Metrics metrics; sd::Budget budget{metrics, work};
  sd::Scratch scratch(d.account, d.dimensions.size(), d.head.size());
  using Counts = std::map<const std::uint64_t*, std::uint64_t, std::less<const std::uint64_t*>,
      resource::MemoryAllocator<std::pair<const std::uint64_t* const, std::uint64_t>>>;
  Counts expected(std::less<const std::uint64_t*>{}, sd::allocator<Counts::value_type>(d.account, resource::MemoryPurpose::scratch));
  for (const auto& [values, fact] : d.facts) {
    budget.take(); sd::require(fact.values == &values && fact.keys.size() == d.dimensions.size(), "invalid fact payload");
    std::size_t missing = 0;
    for (std::size_t i = 0; i < fact.keys.size(); ++i) {
      budget.take(); const auto* key = fact.keys[i];
      sd::require(key->values->view()[0] == values.view()[i] && key->facts.contains(const_cast<sd::Fact*>(&fact)), "invalid fact reverse key");
      missing += !key->heavy && !key->present;
    }
    sd::require(fact.missing == missing && (fact.group != nullptr) == (missing == 0), "invalid light-filter membership");
    if (fact.group) {
      const auto group = d.groups.find(d.group_key(fact, scratch));
      sd::require(group != d.groups.end() && &group->second == fact.group, "wrong heavy group");
      const auto projection = group->second.projections.find(d.head_key(fact, scratch));
      sd::require(projection != group->second.projections.end(), "missing fact projection");
      ++expected[&projection->second];
    }
  }
  for (const auto& [identity, group] : d.groups) {
    budget.take(); std::uint64_t supports = 0; std::size_t missing = 0;
    sd::require(group.identity == &identity && group.supports && !group.projections.empty(), "empty retained group");
    for (const auto* key : group.heavy) {
      budget.take(); sd::require(key->heavy && key->groups.contains(const_cast<sd::Group*>(&group)), "invalid heavy reverse group");
      missing += !key->present;
    }
    for (const auto& [row, count] : group.projections) {
      budget.take(); static_cast<void>(row);
      const auto found = expected.find(&count);
      sd::require(count && found != expected.end() && found->second == count && count <= UINT64_MAX - supports, "wrong projected support");
      supports += count;
    }
    sd::require(supports == group.supports && missing == group.missing && d.live.contains(const_cast<sd::Group*>(&group)) == (missing == 0), "wrong group liveness/support");
  }
  for (const auto& dimension : d.dimensions) {
    budget.take();
    for (std::size_t i = 0; i < dimension.h.histogram_buckets(); ++i) budget.take();
    dimension.h.check_invariants();
    std::uint64_t keys = 0, heavy = 0, rows = 0;
    for (const auto& [values, key] : dimension.keys) {
      budget.take(); sd::require(key.values == &values && key.degree == key.facts.size(), "wrong key degree");
      sd::require(key.degree || (dimension.satellite && key.present), "unreclaimed source key");
      keys += key.degree != 0; heavy += key.heavy; rows += key.degree;
      sd::require(dimension.heavy.contains(const_cast<sd::Key*>(&key)) == key.heavy, "wrong heavy key index");
      if (!key.heavy && dimension.threshold) sd::require(!above_twice(key.degree, *dimension.threshold), "light degree exceeds hysteresis band");
    }
    sd::require(keys == dimension.h.keys() && heavy == dimension.heavy.size() && rows == d.facts.size(), "wrong dimension census");
    for (const auto& [degree, bucket] : dimension.buckets) {
      budget.take(); sd::require(degree && bucket.count && bucket.head && !bucket.head->previous, "invalid occupied degree bucket");
      std::uint64_t count = 0; const sd::Key* previous = nullptr;
      for (auto* key = bucket.head; key; key = key->next) {
        budget.take(); sd::require(key->degree == degree && key->previous == previous, "invalid degree links");
        previous = key; ++count;
      }
      sd::require(count == bucket.count, "wrong degree bucket count");
    }
  }
}
} // namespace crown::runtime::star
