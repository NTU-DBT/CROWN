#include "crown/runtime/comparisons.hpp"
#include "crown/api/error.hpp"
#include <algorithm>
#include <array>
#include <compare>
#include <set>
#include <type_traits>

namespace crown::runtime::comparisons {
namespace {
constexpr resource::MemoryAttribution memory{resource::MemoryOwnerKind::support_node, 0};
template<class T> using Vector = std::vector<T, resource::MemoryAllocator<T>>;
template<class T> auto allocator(const resource::MemoryAccount& account,
    resource::MemoryPurpose purpose = resource::MemoryPurpose::scratch) {
  return resource::MemoryAllocator<T>(account, purpose, memory);
}
TupleVector output(const resource::MemoryAccount& account) {
  return TupleVector(resource::OwnerAllocator<storage::Tuple>(account,
      resource::MemoryPurpose::output_buffer, memory));
}
void require(bool condition, const char* message) {
  if (!condition) throw Error("comparison_invariant", message);
}

// One selected wrapper balance covers the whole recompute/difference. Scalar
// bytes are conservative admitted string/decimal extents, not elapsed time or
// a claim about the exact character prefix examined by the native comparison.
struct Budget {
  Metrics& metrics;
  std::uint64_t limit;
  void take(std::uint64_t amount = 1) {
    if (amount > limit - metrics.work)
      throw Error("comparison_work_limit", "comparison work grant exhausted");
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
  void payload(storage::RowView row) {
    for (const auto& value : row.cells()) scalar(value);
  }
  std::strong_ordering compare(const storage::ScalarView& left, const storage::ScalarView& right) {
    scalar(left); scalar(right);
    return left <=> right; // Admission and native schemas fix the exact same scalar kind.
  }
  std::strong_ordering compare(storage::RowView left, storage::RowView right) {
    take(); ++metrics.row_comparisons;
    const auto count = std::min(left.size(), right.size());
    for (std::size_t i = 0; i < count; ++i)
      if (const auto order = compare(left[i], right[i]); order != 0) return order;
    return left.size() <=> right.size();
  }
  std::strong_ordering compare(const storage::Tuple& left, const storage::Tuple& right) {
    const auto a = left.values().native_view(), b = right.values().native_view();
    require(a.has_value() && b.has_value(), "comparison state lost native payload ownership");
    return compare(*a, *b);
  }
};

// This comparator exists ONLY in recomputation scratch. Its borrowed balance
// outlives the set; no comparator/budget pointer enters the retained result.
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

storage::ScalarView operand(const Operand& input, storage::RowView assignment) {
  if (const auto* variable = std::get_if<VariableId>(&input)) return assignment[variable->value];
  return std::get<storage::ScalarView>(input);
}
bool accepts(std::span<const Predicate> predicates, storage::RowView assignment, Budget& budget) {
  for (const auto& predicate : predicates) {
    budget.take(); ++budget.metrics.predicate_tests;
    const auto order = budget.compare(operand(predicate.left, assignment), operand(predicate.right, assignment));
    bool accepted = false;
    switch (predicate.operation) {
      case Operator::equal: accepted = order == 0; break;
      case Operator::not_equal: accepted = order != 0; break;
      case Operator::less: accepted = order < 0; break;
      case Operator::less_equal: accepted = order <= 0; break;
      case Operator::greater: accepted = order > 0; break;
      case Operator::greater_equal: accepted = order >= 0; break;
    }
    if (!accepted) return false;
  }
  return true;
}

// Full survivor-factor witnesses retain hidden comparison variables. Native
// validation binds every declared variable, and every occurrence contributes
// its complete scope. The whole-tree witness program emits those IDs sorted.
// A constant-false operator may retain declared variables but emits no tuple;
// its canonical empty tree must not be mistaken for missing live variables.
Vector<storage::Tuple> recompute(const CompiledProgram& program, const Binding& binding,
    SupportRuntime::EpochView view, Limits limits, Budget& budget) {
  const auto& account = binding.account();
  budget.metrics.recomputed = true;
  budget.metrics.view_work = view.metrics().work;
  budget.take(budget.metrics.view_work);
  auto cursor = view.witnesses({}, {}, ResultCursorOptions{limits.producer_work});
  const auto fields = cursor.layout().fields();
  if (program.route() == PhysicalRoute::tree) {
    require(fields.size() == program.query().variables.size(), "whole-tree witness omitted a query variable");
    for (std::size_t i = 0; i < fields.size(); ++i) {
      budget.take();
      require(fields[i].variable == VariableId{i}, "whole-tree witness variables are not in ID order");
    }
  }
  const auto head = program.query().head;
  Vector<storage::ScalarView> projected(allocator<storage::ScalarView>(account));
  budget.take(head.size()); projected.reserve(head.size());
  std::set<storage::AccountedRow, RowLess, resource::MemoryAllocator<storage::AccountedRow>> distinct(
      RowLess{&budget}, allocator<storage::AccountedRow>(account));
  while (auto witness = cursor.next_native()) {
    budget.take(); ++budget.metrics.witnesses;
    if (!accepts(binding.predicates(), witness->values(), budget)) continue;
    ++budget.metrics.projected; projected.clear();
    for (const auto& field : head) {
      const auto value = witness->values()[field.variable.value];
      budget.scalar(value); projected.push_back(value);
    }
    const auto row = storage::RowView::borrow(projected);
    if (distinct.find(row) != distinct.end()) { ++budget.metrics.duplicates; continue; }
    if (distinct.size() >= limits.rows)
      throw Error("comparison_row_limit", "comparison distinct-result row limit exceeded");
    budget.take(); budget.payload(row);
    distinct.emplace(storage::AccountedRow::copy_of(account, row, memory));
  }
  budget.metrics.producer_work = cursor.metrics().total_work;
  // Current EpochView work is construction-only. Read its final value too, so
  // the report/remaining wrapper balance do not assume that stays immutable.
  const auto view_work = view.metrics().work;
  require(view_work >= budget.metrics.view_work, "epoch view work counter decreased");
  budget.take(view_work - budget.metrics.view_work); budget.metrics.view_work = view_work;
  Vector<storage::Tuple> result(allocator<storage::Tuple>(account, resource::MemoryPurpose::table_state));
  budget.take(distinct.size()); result.reserve(distinct.size());
  // Materialize only distinct outputs in the genuine original head layout.
  // The set's keys and these output payloads coexist temporarily: account and
  // work limits admit that real O(result bytes) copy, never a source clone.
  for (const auto& row : distinct) {
    budget.take(); budget.payload(row.view());
    result.push_back(storage::Tuple::from_accounted(program.result_layout().tuple(row.view(), memory)));
  }
  budget.metrics.outputs = result.size();
  view.close();
  return result;
}

// Sorted endpoint merge creates owning immutable row handles before source
// publication. Physical/support membership events are not answer deltas.
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
  CompiledProgram program;
  Vector<storage::AccountedRow> constants;
  Vector<Predicate> predicates;
  Data(const CompiledProgram& source, std::span<const planner::comparisons::Predicate> input,
      Budget& budget)
      : account(source.account()), program(source),
        constants(allocator<storage::AccountedRow>(account, resource::MemoryPurpose::immutable_metadata)),
        predicates(allocator<Predicate>(account, resource::MemoryPurpose::immutable_metadata)) {
    budget.take();
    if (input.size() > SIZE_MAX / 2) throw Error("comparison_work_limit", "comparison operand count overflow");
    budget.take(input.size()); predicates.reserve(input.size());
    budget.take(2 * input.size()); constants.reserve(2 * input.size());
    const auto freeze = [&](const planner::comparisons::Operand& value) -> Operand {
      budget.take();
      if (const auto* variable = std::get_if<VariableId>(&value)) return *variable;
      const std::array cell{storage::borrow_scalar(std::get<Value>(value))};
      budget.scalar(cell[0]);
      constants.push_back(storage::AccountedRow::copy_of(account, storage::RowView::borrow(cell), memory));
      return constants.back().view()[0];
    };
    for (const auto& predicate : input) {
      budget.take();
      auto left = freeze(predicate.left), right = freeze(predicate.right);
      predicates.push_back({std::move(left), predicate.operation, std::move(right)});
    }
  }
};
const Binding::Data& Binding::data() const {
  if (!data_) throw Error("comparison_state", "empty comparison binding");
  return *data_;
}
const CompiledProgram& Binding::program() const & { return data().program; }
std::span<const Predicate> Binding::predicates() const & { return data().predicates; }
const resource::MemoryAccount& Binding::account() const & { return data().account; }

struct Runtime::Data {
  resource::MemoryAccount account;
  PhysicalRuntime sources;
  Binding binding;
  Limits limits;
  Vector<storage::Tuple> rows;
  bool busy = false;
  Data(PhysicalRuntime source, const planner::comparisons::Plan& plan, Limits selected, Budget& budget)
      : account(source.plan().account()), sources(std::move(source)),
        binding(resource::make_accounted_shared<Binding::Data>(memory, account,
            resource::MemoryPurpose::immutable_metadata, sources.plan(), plan.predicates(), budget)),
        limits(selected), rows(allocator<storage::Tuple>(account, resource::MemoryPurpose::table_state)) {}
  void readable() const {
    if (busy || !sources.ready()) throw Error("comparison_busy", "comparison source/result publication is active");
  }
};

Runtime::Runtime(const planner::comparisons::Plan& plan, Options options) {
  // Cold predicate freeze and initial answer construction share this ONE
  // wrapper balance. Original source/program admission retains its own grant.
  Metrics metrics; Budget budget{metrics, options.recompute.work}; budget.take();
  PhysicalRuntime sources(plan.general(), options.sources);
  const auto account = sources.plan().account();
  data_ = resource::make_accounted_unique<Data>(memory, account, resource::MemoryPurpose::support_metadata,
      std::move(sources), plan, options.recompute, budget);
  auto& d = data(); Writing writing(d.busy);
  auto next = recompute(d.sources.plan(), d.binding,
      d.sources.current_view(EpochViewOptions{budget.remaining()}), d.limits, budget);
  d.rows.swap(next);
}
Runtime::~Runtime() = default;
Runtime::Runtime(Runtime&&) noexcept = default;
Runtime& Runtime::operator=(Runtime&&) noexcept = default;
Runtime::Data& Runtime::data() const {
  if (!data_) throw Error("comparison_state", "moved-from comparison runtime");
  return *data_;
}
const CompiledProgram& Runtime::program() const & { return data().binding.program(); }
const Binding& Runtime::binding() const & { return data().binding; }
const resource::MemoryAccount& Runtime::account() const & { return data().account; }
bool Runtime::ready() const { const auto& d = data(); return !d.busy && d.sources.ready(); }
std::uint64_t Runtime::sequence() const { const auto& d = data(); d.readable(); return d.sources.sequence(); }
bool Runtime::has_answer() const { const auto& d = data(); d.readable(); return !d.rows.empty(); }

Epoch Runtime::apply(const PhysicalSetUpdate& update) {
  auto& d = data(); d.readable();
  // Declare this before every temporary: it covers source/H-free publication,
  // source-token and old-result retirement, and synchronous allocator callbacks.
  Writing writing(d.busy);
  Metrics metrics; Budget budget{metrics, d.limits.work}; budget.take();
  auto source = d.sources.prepare(update);
  Vector<storage::Tuple> next(allocator<storage::Tuple>(d.account, resource::MemoryPurpose::table_state));
  auto added = output(d.account), removed = output(d.account);
  // Equal projected native keys retain the exact same assignment set even
  // when derivation multiplicity, unused sources or filtered source rows change.
  // All self-join aliases have drained before prepare returns.
  const auto& derivations = source.preview().derivations;
  if (std::any_of(derivations.begin(), derivations.end(), [](const auto& change) { return change.native_changed; })) {
    next = recompute(d.sources.plan(), d.binding,
        source.view(SnapshotSide::after, EpochViewOptions{budget.remaining()}), d.limits, budget);
    difference(d.rows, next, added, removed, budget);
  } else metrics.outputs = d.rows.size();
  // Every fallible cursor/output/endpoint step has completed and its view has
  // closed. Valid physical commit and equal-allocator vector swap allocate
  // nothing. Earlier refusal simply destroys private work and rolls back source.
  auto input = source.commit();
  if (metrics.recomputed) d.rows.swap(next);
  return {std::move(input), d.binding, std::move(added), std::move(removed), metrics};
}

Snapshot Runtime::snapshot(Limits limits) const {
  auto& d = data(); d.readable(); Writing writing(d.busy);
  Metrics metrics; Budget budget{metrics, limits.work}; budget.take();
  if (d.rows.size() > limits.rows) throw Error("comparison_row_limit", "comparison snapshot row limit exceeded");
  auto rows = output(d.account);
  budget.take(d.rows.size()); rows.reserve(d.rows.size());
  for (const auto& row : d.rows) { budget.take(); rows.push_back(row); }
  metrics.outputs = rows.size();
  return {d.sources.sequence(), d.binding, std::move(rows), metrics};
}
Database Runtime::source_snapshot() const {
  auto& d = data(); d.readable(); Writing writing(d.busy);
  return d.sources.snapshot().physical;
}
static_assert(std::is_nothrow_move_constructible_v<Epoch>);
static_assert(std::is_nothrow_move_constructible_v<Snapshot>);
} // namespace crown::runtime::comparisons
