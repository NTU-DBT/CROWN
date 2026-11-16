#include "crown/runtime/difference.hpp"
#include "cq_recompute.hpp"
#include <algorithm>
#include <map>
#include <type_traits>

namespace crown::runtime::difference {
namespace {
constexpr resource::MemoryAttribution memory{resource::MemoryOwnerKind::support_node, 0};
template<class T> using Vector = cq_recompute::Vector<T>;
template<class T> auto allocator(const resource::MemoryAccount& account,
    resource::MemoryPurpose purpose = resource::MemoryPurpose::scratch) {
  return cq_recompute::allocator<T>(account, purpose);
}
template<class T> OutputVector<T> output(const resource::MemoryAccount& account) {
  return OutputVector<T>(resource::OwnerAllocator<T>(account, resource::MemoryPurpose::output_buffer, memory));
}
void require(bool condition, const char* message) {
  if (!condition) throw Error("difference_invariant", message);
}
struct Budget {
  Metrics& metrics;
  std::uint64_t limit;
  void take(std::uint64_t amount = 1) {
    if (amount > limit - metrics.work) throw Error("difference_work_limit", "difference work grant exhausted");
    metrics.work += amount;
  }
  [[nodiscard]] std::uint64_t remaining() const noexcept { return limit - metrics.work; }
  void scalar(const storage::ScalarView& value) {
    take(); ++metrics.scalar_fields; std::uint64_t bytes = 0;
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
    require(left.has_value() && right.has_value(), "difference result lost native ownership");
    return compare(*left, *right);
  }
};
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
Multiplicity residual(Mode mode, Multiplicity left, Multiplicity right,
    const annotations::MultiplicityPolicy& policy) {
  if (mode == Mode::set_except) return {left.present() && !right.present() ? 1U : 0U};
  return left > right ? policy.remove(left, right) : Multiplicity{};
}

// One union-key scratch map retains both complete operand counts. A key can
// belong to either operand; rows bounds each side separately, hence at most
// twice that many union nodes. Raw RHS keys need no left-layout coercion.
Vector<Entry> recompute(const Binding& binding, const physical::SourceImage& image,
    Limits limits, Budget& budget) {
  const auto& account = binding.account(); const auto mode = binding.profile().mode;
  const annotations::MultiplicityPolicy policy(binding.multiplicity_limit());
  struct Counts { Multiplicity left, right; };
  using Value = std::pair<const storage::AccountedRow, Counts>;
  std::map<storage::AccountedRow, Counts, RowLess, resource::MemoryAllocator<Value>> counts(
      RowLess{&budget}, allocator<Value>(account));
  budget.metrics.recomputed = true;
  const auto collect = [&](const program::Query& query, bool left) {
    const auto before = budget.metrics.assignments;
    auto& keys = left ? budget.metrics.left_keys : budget.metrics.right_keys;
    cq_recompute::visit(query, image, account, budget, [&](storage::RowView row) {
      auto found = counts.find(row);
      const bool new_operand_key = found == counts.end() || !(left ? found->second.left : found->second.right).present();
      if (new_operand_key && keys == limits.rows)
        throw Error("difference_row_limit", "difference operand distinct-row limit exceeded");
      if (found == counts.end()) {
        budget.take(); budget.payload(row);
        found = counts.emplace(storage::AccountedRow::copy_of(account, row, memory), Counts{}).first;
      }
      auto& value = left ? found->second.left : found->second.right;
      budget.take();
      const auto next = mode == Mode::set_except ? Multiplicity{1} : policy.add(value, Multiplicity{1});
      if (new_operand_key) ++keys; else ++budget.metrics.duplicates;
      value = next;
      return mode == Mode::bag_except_all || !query.head.empty();
    });
    (left ? budget.metrics.left_assignments : budget.metrics.right_assignments) = budget.metrics.assignments - before;
  };
  collect(binding.left(), true); collect(binding.right(), false);
  Vector<Entry> result(allocator<Entry>(account, resource::MemoryPurpose::table_state));
  // Only positive left residuals receive output payloads in the LEFT schema.
  // Per-key W01 overflow is a refusal even if subtraction would later cancel.
  for (const auto& [row, value] : counts) {
    budget.take(); const auto count = residual(mode, value.left, value.right, policy);
    if (!count.present()) continue;
    budget.take(); budget.payload(row.view());
    result.push_back({storage::Tuple::from_accounted(binding.result_layout().tuple(row.view(), memory)), count});
  }
  budget.metrics.outputs = result.size(); return result;
}
void replacements(const Vector<Entry>& before, const Vector<Entry>& after,
    OutputVector<Change>& changes, Budget& budget) {
  const auto append = [&](const storage::Tuple& tuple, Multiplicity old, Multiplicity next) {
    if (old == next) return;
    budget.take(); changes.push_back({tuple, old, next});
    if (!old.present()) ++budget.metrics.added;
    if (!next.present()) ++budget.metrics.removed;
  };
  std::size_t i = 0, j = 0;
  while (i < before.size() && j < after.size()) {
    const auto order = budget.compare(before[i].tuple, after[j].tuple);
    if (order == 0) { append(after[j].tuple, before[i].multiplicity, after[j].multiplicity); ++i; ++j; }
    else if (order < 0) { append(before[i].tuple, before[i].multiplicity, {}); ++i; }
    else { append(after[j].tuple, {}, after[j].multiplicity); ++j; }
  }
  while (i < before.size()) { append(before[i].tuple, before[i].multiplicity, {}); ++i; }
  while (j < after.size()) { append(after[j].tuple, {}, after[j].multiplicity); ++j; }
  budget.metrics.changes = changes.size();
}
std::pair<std::optional<std::uint64_t>, std::optional<std::uint64_t>> products(
    const program::Query& query, std::span<const std::uint64_t> tables) {
  std::optional<std::uint64_t> product = 1, prefix = 0;
  for (const auto& atom : query.atoms) {
    const auto count = tables[atom.table.value];
    if (!count) product = 0;
    else if (product) { if (*product > UINT64_MAX / count) product.reset(); else *product *= count; }
    if (prefix) { if (!product || *product > UINT64_MAX - *prefix) prefix.reset(); else *prefix += *product; }
  }
  return {product, prefix};
}
} // namespace

struct Binding::Data {
  resource::MemoryAccount account;
  CompiledProgram sources;
  Profile profile;
  std::uint64_t limit;
  cq_recompute::FrozenQuery left, right;
  Data(const CompiledProgram& source, const planner::difference::Plan& plan,
      std::uint64_t count_limit, Budget& budget)
      : account(source.account()), sources(source), profile(plan.profile()), limit(count_limit),
        left(source, plan.left().query(), cq_recompute::output_id(source, "difference_overflow"),
            "difference-left-head-v1", budget, "difference_overflow"),
        right(source, plan.right().query(), std::nullopt, {}, budget, "difference_overflow") {}
};
const Binding::Data& Binding::data() const {
  if (!data_) throw Error("difference_state", "empty difference binding");
  return *data_;
}
const program::Query& Binding::left() const & { return data().left.query; }
const program::Query& Binding::right() const & { return data().right.query; }
const Profile& Binding::profile() const & { return data().profile; }
const CompiledProgram& Binding::sources() const & { return data().sources; }
const storage::AccountedLayout& Binding::result_layout() const & { return data().left.layout; }
const resource::MemoryAccount& Binding::account() const & { return data().account; }
std::uint64_t Binding::multiplicity_limit() const { return data().limit; }

struct Runtime::Data {
  resource::MemoryAccount account;
  PhysicalRuntime sources;
  Binding binding;
  Limits limits;
  Vector<Entry> rows;
  Vector<std::uint64_t> cardinalities;
  Vector<std::uint8_t> used;
  bool busy = false;
  Data(PhysicalRuntime source, const planner::difference::Plan& plan, const Options& options, Budget& budget)
      : account(source.plan().account()), sources(std::move(source)),
        binding(resource::make_accounted_shared<Binding::Data>(memory, account,
            resource::MemoryPurpose::immutable_metadata, sources.plan(), plan, options.multiplicity_limit, budget)),
        limits(options.recompute), rows(allocator<Entry>(account, resource::MemoryPurpose::table_state)),
        cardinalities(allocator<std::uint64_t>(account, resource::MemoryPurpose::support_metadata)),
        used(allocator<std::uint8_t>(account, resource::MemoryPurpose::immutable_metadata)) {
    const auto tables = sources.plan().source_catalog().tables.size();
    budget.take(tables); cardinalities.assign(tables, 0); budget.take(tables); used.assign(tables, 0);
    for (const auto* query : {&binding.left(), &binding.right()}) if (!query->contradiction)
      for (const auto& atom : query->atoms) { budget.take(); used[atom.table.value] = 1; }
  }
  void readable() const {
    if (busy || !sources.ready()) throw Error("difference_busy", "difference publication is active");
  }
};
Runtime::Runtime(const planner::difference::Plan& plan, Options options) {
  const annotations::MultiplicityPolicy policy(options.multiplicity_limit);
  Metrics metrics; Budget budget{metrics, options.recompute.work}; budget.take();
  PhysicalRuntime sources(plan.source_only(), options.sources); const auto account = sources.plan().account();
  data_ = resource::make_accounted_unique<Data>(memory, account, resource::MemoryPurpose::support_metadata,
      std::move(sources), plan, options, budget);
  auto& d = data(); Writing writing(d.busy); budget.take();
  const auto initial = [](const program::Query& query) -> Multiplicity {
    return {!query.contradiction && query.atoms.empty() ? 1U : 0U};
  };
  const auto left = initial(d.binding.left()), right = initial(d.binding.right());
  if (!d.limits.rows && (left.present() || right.present()))
    throw Error("difference_row_limit", "difference initial operand-row limit exceeded");
  const auto count = residual(d.binding.profile().mode, left, right, policy);
  if (count.present()) {
    budget.take(); d.rows.push_back({storage::Tuple::from_accounted(d.binding.result_layout().tuple(storage::RowView{}, memory)), count});
  }
}
Runtime::~Runtime() = default;
Runtime::Runtime(Runtime&&) noexcept = default;
Runtime& Runtime::operator=(Runtime&&) noexcept = default;
Runtime::Data& Runtime::data() const {
  if (!data_) throw Error("difference_state", "moved-from difference runtime");
  return *data_;
}
const Binding& Runtime::binding() const & { return data().binding; }
const resource::MemoryAccount& Runtime::account() const & { return data().account; }
bool Runtime::ready() const { const auto& d = data(); return !d.busy && d.sources.ready(); }
std::uint64_t Runtime::sequence() const { const auto& d = data(); d.readable(); return d.sources.sequence(); }
bool Runtime::has_answer() const { const auto& d = data(); d.readable(); return !d.rows.empty(); }
Epoch Runtime::apply(const PhysicalSetUpdate& update) {
  auto& d = data(); d.readable(); Writing writing(d.busy);
  Metrics metrics; Budget budget{metrics, d.limits.work}; budget.take(); auto source = d.sources.prepare(update);
  const bool changed = source.preview().physical_changed; auto count = d.cardinalities[update.table.value];
  if (changed) {
    if (update.operation == SetOperation::insert) {
      if (count == UINT64_MAX) throw Error("difference_overflow", "difference table cardinality overflow");
      ++count;
    } else { require(count != 0, "difference table cardinality underflow"); --count; }
  }
  Vector<Entry> next(allocator<Entry>(d.account, resource::MemoryPurpose::table_state));
  auto changes = output<Change>(d.account);
  if (changed && d.used[update.table.value]) {
    auto image = source.source_image(physical::SourceImageLimits{d.limits.source_rows, budget.remaining()});
    budget.take(image.work); metrics.source_work = image.work;
    for (const auto& table : image.tables) { budget.take(); metrics.source_rows += table.size(); }
    next = recompute(d.binding, image, d.limits, budget); replacements(d.rows, next, changes, budget);
  } else metrics.outputs = d.rows.size();
  // The one image, all visitors/maps and every fallible replacement allocation
  // have retired. Valid source commit and count/vector publication allocate
  // nothing; the guard remains alive through old-state/source-token retirement.
  auto input = source.commit(); d.cardinalities[update.table.value] = count;
  if (metrics.recomputed) d.rows.swap(next);
  return {std::move(input), d.binding, std::move(changes), metrics};
}
Snapshot Runtime::snapshot(Limits limits) const {
  auto& d = data(); d.readable(); Writing writing(d.busy); Metrics metrics; Budget budget{metrics, limits.work}; budget.take();
  if (d.rows.size() > limits.rows) throw Error("difference_row_limit", "difference snapshot row limit exceeded");
  auto rows = output<Entry>(d.account); budget.take(d.rows.size()); rows.reserve(d.rows.size());
  for (const auto& row : d.rows) { budget.take(); rows.push_back(row); }
  metrics.outputs = rows.size(); return {d.sources.sequence(), d.binding, std::move(rows), metrics};
}
Explain Runtime::explain() const {
  auto& d = data(); d.readable(); Writing writing(d.busy);
  Cardinalities tables(resource::OwnerAllocator<std::uint64_t>(d.account, resource::MemoryPurpose::capture, memory));
  tables.assign(d.cardinalities.begin(), d.cardinalities.end()); std::optional<std::uint64_t> total = 0;
  for (const auto& row : d.rows) if (total) {
    if (row.multiplicity.value > UINT64_MAX - *total) total.reset(); else *total += row.multiplicity.value;
  }
  const auto left = products(d.binding.left(), tables), right = products(d.binding.right(), tables);
  return {d.binding.profile(), std::move(tables), static_cast<std::uint64_t>(d.rows.size()), d.binding.multiplicity_limit(),
      total, left.first, right.first, left.second, right.second, d.account.statistics()};
}
Database Runtime::source_snapshot() const {
  auto& d = data(); d.readable(); Writing writing(d.busy); return d.sources.snapshot().physical;
}
static_assert(std::is_nothrow_move_constructible_v<Epoch>);
static_assert(std::is_nothrow_move_constructible_v<Snapshot>);
} // namespace crown::runtime::difference
