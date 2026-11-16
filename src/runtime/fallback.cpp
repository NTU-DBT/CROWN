#include "crown/runtime/fallback.hpp"
#include "crown/api/error.hpp"
#include "cq_recompute.hpp"
#include <algorithm>
#include <array>
#include <compare>
#include <limits>
#include <set>
#include <type_traits>

namespace crown::runtime::fallback {
namespace {
constexpr resource::MemoryAttribution memory{resource::MemoryOwnerKind::support_node, 0};
template<class T> using Vector = std::vector<T, resource::MemoryAllocator<T>>;
template<class T> auto allocator(const resource::MemoryAccount& account,
    resource::MemoryPurpose purpose = resource::MemoryPurpose::scratch) {
  return resource::MemoryAllocator<T>(account, purpose, memory);
}
TupleVector output(const resource::MemoryAccount& account) {
  return TupleVector(resource::OwnerAllocator<storage::Tuple>(account, resource::MemoryPurpose::output_buffer, memory));
}
void require(bool condition, const char* message) {
  if (!condition) throw Error("fallback_invariant", message);
}

// One balance covers a constructor's metadata/initial answer, or one update's
// source image, prefix traversal, deduplication and endpoint output. Byte units
// conservatively admit string/decimal extents; they are not elapsed time.
struct Budget {
  Metrics& metrics;
  std::uint64_t limit;
  void take(std::uint64_t amount = 1) {
    if (amount > limit - metrics.work) throw Error("fallback_work_limit", "fallback work grant exhausted");
    metrics.work += amount;
  }
  [[nodiscard]] std::uint64_t remaining() const noexcept { return limit - metrics.work; }
  void scalar(const storage::ScalarView& value) {
    take(); ++metrics.scalar_fields;
    std::uint64_t bytes = 0;
    if (const auto* text = std::get_if<std::string_view>(&value)) bytes = text->size();
    else if (const auto* decimal = std::get_if<storage::InlineDecimal>(&value)) bytes = decimal->parts().digits.size();
    take(bytes); metrics.scalar_bytes += bytes;
  }
  void payload(storage::RowView row) { for (const auto& value : row.cells()) scalar(value); }
  std::strong_ordering compare(const storage::ScalarView& a, const storage::ScalarView& b) {
    scalar(a); scalar(b); return a <=> b;
  }
  std::strong_ordering compare(storage::RowView a, storage::RowView b) {
    take(); ++metrics.row_comparisons;
    for (std::size_t i = 0; i < std::min(a.size(), b.size()); ++i)
      if (const auto order = compare(a[i], b[i]); order != 0) return order;
    return a.size() <=> b.size();
  }
  std::strong_ordering compare(const storage::Tuple& a, const storage::Tuple& b) {
    const auto left = a.values().native_view(), right = b.values().native_view();
    require(left.has_value() && right.has_value(), "fallback result lost native payload ownership");
    return compare(*left, *right);
  }
};
// Only private evaluation scratch retains this borrowed balance. Persistent
// sorted state is a vector and cannot carry a dangling comparator context.
struct RowLess {
  using is_transparent = void;
  Budget* budget;
  bool operator()(const storage::AccountedRow& a, const storage::AccountedRow& b) const { return budget->compare(a.view(), b.view()) < 0; }
  bool operator()(const storage::AccountedRow& a, storage::RowView b) const { return budget->compare(a.view(), b) < 0; }
  bool operator()(storage::RowView a, const storage::AccountedRow& b) const { return budget->compare(a, b.view()) < 0; }
};
struct Writing {
  bool& flag;
  explicit Writing(bool& value) noexcept : flag(value) { flag = true; }
  ~Writing() { flag = false; }
};

// Iterative occurrence-by-occurrence nested loops, including cyclic joins.
// Frames own positions/marks, not source rows. A trail contains at most V newly
// bound variables; restoring a frame clears only bindings introduced beneath
// it. This is private evaluation scratch, not a second publication journal.
Vector<storage::Tuple> evaluate(const Binding& binding, const physical::SourceImage& image,
    Limits limits, Budget& budget) {
  const auto& query = binding.query(); const auto& account = binding.account();
  budget.metrics.recomputed = true;
  Vector<storage::Tuple> result(allocator<storage::Tuple>(account, resource::MemoryPurpose::table_state));
  if (query.contradiction) return result;
  std::set<storage::AccountedRow, RowLess, resource::MemoryAllocator<storage::AccountedRow>> distinct(
      RowLess{&budget}, allocator<storage::AccountedRow>(account));
  cq_recompute::visit(query, image, account, budget, [&](storage::RowView row) {
    if (distinct.find(row) != distinct.end()) { ++budget.metrics.duplicates; return !query.head.empty(); }
    if (distinct.size() >= limits.rows) throw Error("fallback_row_limit", "fallback distinct-result row limit exceeded");
    budget.take(); budget.payload(row);
    distinct.emplace(storage::AccountedRow::copy_of(account, row, memory));
    return !query.head.empty(); // Preserve first-witness Boolean SET semantics.
  });
  budget.take(distinct.size()); result.reserve(distinct.size());
  // DISTINCT keys and final tuple payloads coexist temporarily. Both copies,
  // ordered scalar/byte comparisons and all allocator costs remain explicit.
  for (const auto& row : distinct) {
    budget.take(); budget.payload(row.view());
    result.push_back(storage::Tuple::from_accounted(binding.result_layout().tuple(row.view(), memory)));
  }
  budget.metrics.outputs = result.size(); return result;
}
void difference(const Vector<storage::Tuple>& before, const Vector<storage::Tuple>& after,
    TupleVector& added, TupleVector& removed, Budget& budget) {
  std::size_t i = 0, j = 0;
  while (i < before.size() && j < after.size()) {
    const auto order = budget.compare(before[i], after[j]);
    if (order == 0) { ++i; ++j; }
    else if (order < 0) { budget.take(); removed.push_back(before[i++]); }
    else { budget.take(); added.push_back(after[j++]); }
  }
  while (i < before.size()) { budget.take(); removed.push_back(before[i++]); }
  while (j < after.size()) { budget.take(); added.push_back(after[j++]); }
  budget.metrics.added = added.size(); budget.metrics.removed = removed.size();
}
} // namespace

struct Binding::Data {
  resource::MemoryAccount account;
  CompiledProgram sources;
  Profile profile;
  cq_recompute::FrozenQuery frozen;
  Data(const CompiledProgram& source, const planner::fallback::Plan& plan, Budget& budget)
      : account(source.account()), sources(source), profile(plan.profile()),
        frozen(source, plan.query(), cq_recompute::output_id(source, "fallback_overflow"),
            "fallback-original-head-v1", budget, "fallback_overflow") {}
};
const Binding::Data& Binding::data() const {
  if (!data_) throw Error("fallback_state", "empty fallback binding");
  return *data_;
}
const program::Query& Binding::query() const & { return data().frozen.query; }
const Profile& Binding::profile() const & { return data().profile; }
const CompiledProgram& Binding::sources() const & { return data().sources; }
const storage::AccountedLayout& Binding::result_layout() const & { return data().frozen.layout; }
const resource::MemoryAccount& Binding::account() const & { return data().account; }

struct Runtime::Data {
  resource::MemoryAccount account;
  PhysicalRuntime sources;
  Binding binding;
  Limits limits;
  Vector<storage::Tuple> rows;
  Vector<std::uint64_t> cardinalities;
  Vector<std::uint8_t> used;
  bool busy = false;
  Data(PhysicalRuntime source, const planner::fallback::Plan& plan, Limits selected, Budget& budget)
      : account(source.plan().account()), sources(std::move(source)),
        binding(resource::make_accounted_shared<Binding::Data>(memory, account,
            resource::MemoryPurpose::immutable_metadata, sources.plan(), plan, budget)), limits(selected),
        rows(allocator<storage::Tuple>(account, resource::MemoryPurpose::table_state)),
        cardinalities(allocator<std::uint64_t>(account, resource::MemoryPurpose::support_metadata)),
        used(allocator<std::uint8_t>(account, resource::MemoryPurpose::immutable_metadata)) {
    const auto tables = sources.plan().source_catalog().tables.size();
    budget.take(tables); cardinalities.assign(tables, 0);
    budget.take(tables); used.assign(tables, 0);
    for (const auto& atom : binding.query().atoms) { budget.take(); used[atom.table.value] = 1; }
  }
  void readable() const {
    if (busy || !sources.ready()) throw Error("fallback_busy", "fallback source/result publication is active");
  }
};

Runtime::Runtime(const planner::fallback::Plan& plan, Options options) {
  Metrics metrics; Budget budget{metrics, options.recompute.work}; budget.take();
  PhysicalRuntime sources(plan.source_only(), options.sources); const auto account = sources.plan().account();
  data_ = resource::make_accounted_unique<Data>(memory, account, resource::MemoryPurpose::support_metadata,
      std::move(sources), plan, options.recompute, budget);
  auto& d = data(); Writing writing(d.busy); budget.take();
  // All original physical relations start empty. A nonempty body has no
  // witness, including nullary atoms; the empty noncontradictory body has one.
  if (!d.binding.query().contradiction && d.binding.query().atoms.empty()) {
    if (!d.limits.rows) throw Error("fallback_row_limit", "fallback distinct-result row limit exceeded");
    budget.take(); d.rows.push_back(storage::Tuple::from_accounted(d.binding.result_layout().tuple(storage::RowView{}, memory)));
  }
}
Runtime::~Runtime() = default;
Runtime::Runtime(Runtime&&) noexcept = default;
Runtime& Runtime::operator=(Runtime&&) noexcept = default;
Runtime::Data& Runtime::data() const {
  if (!data_) throw Error("fallback_state", "moved-from fallback runtime");
  return *data_;
}
const Binding& Runtime::binding() const & { return data().binding; }
const resource::MemoryAccount& Runtime::account() const & { return data().account; }
bool Runtime::ready() const { const auto& d = data(); return !d.busy && d.sources.ready(); }
std::uint64_t Runtime::sequence() const { const auto& d = data(); d.readable(); return d.sources.sequence(); }
bool Runtime::has_answer() const { const auto& d = data(); d.readable(); return !d.rows.empty(); }

Epoch Runtime::apply(const PhysicalSetUpdate& update) {
  auto& d = data(); d.readable(); Writing writing(d.busy);
  Metrics metrics; Budget budget{metrics, d.limits.work}; budget.take();
  auto source = d.sources.prepare(update);
  const bool changed = source.preview().physical_changed;
  auto count = d.cardinalities[update.table.value];
  if (changed) {
    if (update.operation == SetOperation::insert) {
      if (count == UINT64_MAX) throw Error("fallback_overflow", "fallback table cardinality overflow");
      ++count;
    } else { require(count != 0, "fallback table cardinality underflow"); --count; }
  }
  Vector<storage::Tuple> next(allocator<storage::Tuple>(d.account, resource::MemoryPurpose::table_state));
  auto added = output(d.account), removed = output(d.account);
  // A source-only program has no derivation routes: physical change plus the
  // ORIGINAL query's table-use mask is the trigger, never native_changed.
  if (changed && d.used[update.table.value] && !d.binding.query().contradiction) {
    auto image = source.source_image(physical::SourceImageLimits{d.limits.source_rows, budget.remaining()});
    budget.take(image.work); metrics.source_work = image.work;
    for (const auto& table : image.tables) { budget.take(); metrics.source_rows += table.size(); }
    next = evaluate(d.binding, image, d.limits, budget);
    difference(d.rows, next, added, removed, budget);
  } else metrics.outputs = d.rows.size();
  // Image/cursors and every fallible result/delta step are already retired.
  // Valid source commit, scalar count publication, vector swap and aggregate
  // return are nonallocating. The guard also spans old-result/token teardown.
  auto input = source.commit(); d.cardinalities[update.table.value] = count;
  if (metrics.recomputed) d.rows.swap(next);
  return {std::move(input), d.binding, std::move(added), std::move(removed), metrics};
}
Snapshot Runtime::snapshot(Limits limits) const {
  auto& d = data(); d.readable(); Writing writing(d.busy);
  Metrics metrics; Budget budget{metrics, limits.work}; budget.take();
  if (d.rows.size() > limits.rows) throw Error("fallback_row_limit", "fallback snapshot row limit exceeded");
  auto rows = output(d.account); budget.take(d.rows.size()); rows.reserve(d.rows.size());
  for (const auto& row : d.rows) { budget.take(); rows.push_back(row); }
  metrics.outputs = rows.size(); return {d.sources.sequence(), d.binding, std::move(rows), metrics};
}
Explain Runtime::explain() const {
  auto& d = data(); d.readable(); Writing writing(d.busy);
  Cardinalities tables(resource::OwnerAllocator<std::uint64_t>(d.account, resource::MemoryPurpose::capture, memory));
  tables.assign(d.cardinalities.begin(), d.cardinalities.end());
  std::optional<std::uint64_t> product = 1, prefix = 0;
  for (const auto& atom : d.binding.query().atoms) {
    const auto count = d.cardinalities[atom.table.value];
    if (!count) product = 0; // A later zero makes the full product exactly zero even after overflow.
    else if (product) {
      if (*product > UINT64_MAX / count) product.reset(); else *product *= count;
    }
    if (prefix) {
      if (!product || *product > UINT64_MAX - *prefix) prefix.reset(); else *prefix += *product;
    }
  }
  return {d.binding.profile(), std::move(tables), product, prefix,
      static_cast<std::uint64_t>(d.rows.size()), d.account.statistics()};
}
Database Runtime::source_snapshot() const {
  auto& d = data(); d.readable(); Writing writing(d.busy); return d.sources.snapshot().physical;
}
static_assert(std::is_nothrow_move_constructible_v<Epoch>);
static_assert(std::is_nothrow_move_constructible_v<Snapshot>);
} // namespace crown::runtime::fallback
