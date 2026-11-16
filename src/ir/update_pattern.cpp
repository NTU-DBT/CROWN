#include "update_pattern_detail.hpp"
#include "crown/ir/program.hpp"

namespace crown::patterns {
namespace {
// Charge deterministic construction work and payload before allocating. All
// actual container/control/framing bytes also consume the receiving account.
struct Budget {
  Limits limits;
  Usage usage;
  static void add(std::uint64_t& value, std::uint64_t amount, std::uint64_t cap, Fault fault) {
    if (value > cap || amount > cap - value) throw Failure(fault);
    value += amount;
  }
  void work(std::uint64_t n = 1) { add(usage.work, n, limits.work, Fault::work_limit); }
  void cells(std::uint64_t n) { add(usage.cells, n, limits.cells, Fault::cell_limit); }
  void bytes(std::uint64_t n) { add(usage.payload_bytes, n, limits.payload_bytes, Fault::byte_limit); }
};
template<class T> void reserve(detail::Vector<T>& values, std::size_t count, Budget& budget) {
  if (count > UINT64_MAX / sizeof(T)) throw Failure(Fault::byte_limit);
  budget.cells(static_cast<std::uint64_t>(count));
  budget.bytes(static_cast<std::uint64_t>(count) * sizeof(T));
  values.reserve(count);
}
}

// Canonicalize R rules in O(R log R) comparisons and O(R) retained cells.
// No FIFO-group scratch directory is built: consumers compare explicit IDs.
// Failure publishes nothing; funded local owners unwind without a catch/retry.
Declaration detail::Factory::make(const resource::MemoryAccount& account, std::array<char, 64> source,
    std::uint64_t tables, std::span<const TableRule> rules, const Limits& limits) {
  Budget budget{limits, {}};
  require(rules.size() <= tables);
  budget.work(64);
  require(std::all_of(source.begin(), source.end(), [](char c) {
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f');
  }));
  budget.bytes(sizeof(Data));
  auto data = resource::make_accounted_shared<Data>(
      owner, account, resource::MemoryPurpose::capture, account, source, tables);
  reserve(data->rules, rules.size(), budget);
  for (const auto& rule : rules) {
    budget.work();
    require(rule.table.value < tables);
    data->rules.push_back(rule);
    data->constrained = data->constrained || rule.insertion_only || rule.fifo_scope;
  }
  std::sort(data->rules.begin(), data->rules.end(), [&](const auto& a, const auto& b) {
    budget.work();
    return a.table < b.table;
  });
  for (std::size_t i = 1; i < data->rules.size(); ++i) {
    budget.work();
    require(data->rules[i - 1].table != data->rules[i].table);
  }
  data->usage = budget.usage;
  return Declaration(std::move(data));
}

// Read the existing immutable source digest; do not hash or clone the program.
Declaration Declaration::capture(const resource::MemoryAccount& account, const CompiledProgram& source,
    std::span<const TableRule> rules, const Limits& limits) {
  detail::require(bool(source));
  std::array<char, 64> hash{};
  const auto text = source.physical_source_sha256();
  detail::require(text.size() == hash.size());
  std::copy(text.begin(), text.end(), hash.begin());
  return detail::Factory::make(account, hash, source.source_catalog().tables.size(), rules, limits);
}
Declaration Declaration::import(const resource::MemoryAccount& account, const Record& record, const Limits& limits) {
  return detail::Factory::make(account, record.source_sha256, record.source_tables, record.rules, limits);
}
Declaration Declaration::import(const resource::MemoryAccount& account, std::array<char, 64> hash,
    std::uint64_t tables, std::span<const TableRule> rules, const Limits& limits) {
  return detail::Factory::make(account, hash, tables, rules, limits);
}
Usage Declaration::copy_usage() const noexcept {
  if (!data_) return {};
  // Construction already bounded this sum and count by uint64 payload/cell caps.
  const auto count = static_cast<std::uint64_t>(data_->rules.size());
  return {64 + count, count, sizeof(detail::Data) + count * sizeof(TableRule)};
}

// Transfer validated metadata to a receiving account in O(R), without sorting
// again. Callers admit copy_usage first; the allocator independently caps bytes.
Declaration detail::Factory::copy(const resource::MemoryAccount& account, const Declaration& source) {
  require(bool(source));
  const auto& old = *source.data_;
  auto data = resource::make_accounted_shared<Data>(
      owner, account, resource::MemoryPurpose::capture, account, old.source, old.tables);
  data->constrained = old.constrained;
  data->usage = source.copy_usage();
  data->rules.reserve(old.rules.size());
  data->rules.insert(data->rules.end(), old.rules.begin(), old.rules.end());
  return Declaration(std::move(data));
}
Declaration Declaration::copy_of(const resource::MemoryAccount& account, const Declaration& source) {
  return detail::Factory::copy(account, source);
}

Declaration Declaration::copy_of(const resource::MemoryAccount& account,
    const Declaration& source, const Limits& limits) {
  const auto usage = source.copy_usage();
  Budget budget{limits, {}};
  budget.work(usage.work);
  budget.cells(usage.cells);
  budget.bytes(usage.payload_bytes);
  return detail::Factory::copy(account, source);
}

// Explicit external export: ordinary caller-owned allocation may throw.
Record Declaration::export_record() const {
  detail::require(bool(data_));
  Record result{data_->source, data_->tables, {}};
  result.rules.reserve(data_->rules.size());
  for (const auto& rule : data_->rules) result.rules.push_back(rule);
  return result;
}
bool Declaration::matches(const CompiledProgram& source) const noexcept {
  if (!data_ || !source) return false;
  const auto hash = source.physical_source_sha256();
  return hash.size() == data_->source.size() && std::equal(hash.begin(), hash.end(), data_->source.begin()) &&
      source.source_catalog().tables.size() == data_->tables;
}
bool Declaration::constrained() const noexcept { return data_ && data_->constrained; }
std::uint64_t Declaration::source_tables() const noexcept { return data_ ? data_->tables : 0; }
Usage Declaration::captured_usage() const noexcept { return data_ ? data_->usage : Usage{}; }
std::span<const TableRule> Declaration::rules() const & noexcept {
  return data_ ? std::span<const TableRule>{data_->rules.data(), data_->rules.size()} :
                std::span<const TableRule>{};
}
// Logarithmic lookup, with no allocation. A processing visitor must charge its
// own comparisons (the planner analyser uses its budgeted lower_bound visitor).
const TableRule* Declaration::find(TableId table) const & noexcept {
  if (!data_) return nullptr;
  const auto found = std::lower_bound(data_->rules.begin(), data_->rules.end(), table,
      [](const auto& rule, TableId id) { return rule.table < id; });
  return found != data_->rules.end() && found->table == table ? &*found : nullptr;
}
const std::array<char, 64>& Declaration::source_sha256() const & {
  detail::require(bool(data_));
  return data_->source;
}
} // namespace crown::patterns
