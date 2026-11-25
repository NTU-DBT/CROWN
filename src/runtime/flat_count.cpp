#include "crown/runtime/flat_count.hpp"
#include "flat_plan.hpp"

#include <cstring>
#include <limits>
#include <vector>

namespace crown::runtime {
namespace {
using namespace flat_detail;
constexpr std::uint64_t count_limit = static_cast<std::uint64_t>(std::numeric_limits<std::int64_t>::max());

inline std::uint64_t multiply(std::uint64_t a, std::uint64_t b) {
  std::uint64_t product;
  require(!__builtin_mul_overflow(a, b, &product) && product <= count_limit, "bag count exceeds the int64 range");
  return product;
}
// Visible payload (weighted): weight, flags (bit 0 = live), route stamp, weight at route start.
inline bool live(const Word* payload) { return (payload[1] & 1) != 0; }
}  // namespace

// Weights. For a record t of node v with derivation multiplicity m(t) (1 for a
// generalized candidate) and cached child sums S_c(key_c(t)):
//   full(t)  = m(t) * prod_c S_c            (its contribution to v's parent sum)
//   local(t) = m(t) * prod_{c not in C*} S_c, when every child sum is positive
// Each C* visible key e carries W_v(e) = sum of local(t) over t projecting to e.
// With C* separators inside the head, the bag count of head tuple a is
//   count(a) = prod over C* nodes v of W_v(a[X_v]),
// and e is a visible key exactly when W_v(e) > 0 (the set executor's E).
// A route with one polarity changes every weight monotonically, so changed
// groups are enumerated once each, owner = lowest-rank changed factor, in the
// after context for an insertion and the deferred before context for an erasure.
struct FlatCountRuntime::Impl : FlatProgram {
  FlatOptions options;
  std::vector<std::uint64_t> outside_mask;  // per node: child slots outside C*

  Impl(const CompiledProgram& program, FlatOptions value) : FlatProgram(program, value.delta, true), options(value) {
    for (auto& base : bases) base.dedupe = false;  // bag multiplicities, not sets
    outside_mask.assign(nodes.size(), 0);
    for (std::size_t v = 0; v < nodes.size(); ++v)
      for (std::uint32_t slot = 0; slot < nodes[v].children; ++slot)
        if (!nodes[nodes[v].child_nodes[slot]].connex) outside_mask[v] |= 1ULL << slot;
  }

  struct Weights { std::uint64_t full = 0, local = 0; };
  Weights weights(std::uint32_t v, const Word* payload) const {
    const auto& n = nodes[v];
    const std::uint64_t multiplicity = n.native ? low(payload[0]) : 1;
    if (multiplicity == 0 || high(payload[0]) != n.children) return {};
    std::uint64_t full = multiplicity, local = multiplicity;
    for (std::uint32_t slot = 0; slot < n.children; ++slot) {
      const auto sum = static_cast<std::uint64_t>(payload[1 + slot]);
      full = multiply(full, sum);
      if (outside_mask[v] >> slot & 1) local = multiply(local, sum);
    }
    return {full, local};
  }

  void changed_record(std::uint32_t v, const Word* record, Weights before, Weights after) {
    const auto& n = nodes[v];
    if (n.connex && before.local != after.local) {
      Word key[max_arity];
      for (std::size_t i = 0; i < n.visible_positions.size(); ++i) key[i] = record[n.visible_positions[i]];
      visible_add(v, key, static_cast<std::int64_t>(after.local) - static_cast<std::int64_t>(before.local));
    }
    if (n.parent != none && before.full != after.full) {
      Word key[max_arity];
      for (std::size_t i = 0; i < n.parent_positions.size(); ++i) key[i] = record[n.parent_positions[i]];
      support_add(v, key, static_cast<std::int64_t>(after.full) - static_cast<std::int64_t>(before.full));
    }
  }
  void visible_add(std::uint32_t v, const Word* key, std::int64_t delta) {
    auto& n = nodes[v];
    auto& table = n.visible;
    auto id = table.find(key);
    if (id == none) {
      require(delta > 0, "visible weight underflow");
      id = table.insert(key);
    }
    Word* payload = table.payload(id);
    if (delta_mode() && payload[2] != static_cast<Word>(route)) {
      payload[2] = static_cast<Word>(route);
      payload[3] = payload[0];
      n.changed.push_back(id);
    }
    payload[0] += delta;
    require(payload[0] >= 0, "visible weight underflow");
    if (payload[0] == 0 && !delta_mode()) table.erase(id);
  }
  void support_add(std::uint32_t v, const Word* key, std::int64_t delta) {
    auto& table = nodes[v].support;
    auto id = table.find(key);
    const std::int64_t before = id == none ? 0 : table.payload(id)[0];
    const std::int64_t after = before + delta;
    require(after >= 0, "support sum underflow");
    if (id == none) id = table.insert(key);
    table.payload(id)[0] = after;
    if (after == 0) table.erase(id);
    child_update(nodes[v].parent, nodes[v].slot, key, before, after);
  }
  void child_update(std::uint32_t p, std::uint32_t slot, const Word* key, std::int64_t before, std::int64_t after) {
    auto& n = nodes[p];
    const int crossing = before == 0 ? 1 : after == 0 ? -1 : 0;
    auto update = [&](std::uint32_t id) {
      Word* payload = n.records.payload(id);
      const auto old = weights(p, payload);
      payload[1 + slot] = after;
      if (crossing) payload[0] = pack(low(payload[0]), crossing > 0 ? high(payload[0]) + 1U : high(payload[0]) - 1U);
      const auto now = weights(p, payload);
      if (old.full == now.full && old.local == now.local) return;
      Word record[max_arity];
      std::memcpy(record, n.records.key(id), sizeof(Word) * n.arity);
      changed_record(p, record, old, now);
    };
    if (n.native) {
      for (auto id = n.records.bucket(slot, key); id != none;) {
        const auto next = n.records.next(slot, id);
        update(id);
        id = next;
      }
      return;
    }
    Word record[max_arity];
    const auto& place = n.generalized_place[slot];
    for (std::size_t i = 0; i < place.size(); ++i) record[place[i]] = key[i];
    auto id = n.records.find(record);
    if (id == none) {
      require(before == 0 && after > 0, "generalized candidate missing");
      id = n.records.insert(record);
    }
    update(id);
    if (high(n.records.payload(id)[0]) == 0) n.records.erase(id);
  }
  [[nodiscard]] bool delta_mode() const { return options.delta; }

  // ------------------------------------------------------------------- live
  void make_live(std::uint32_t v, std::uint32_t id) {
    auto& n = nodes[v];
    n.visible.payload(id)[1] |= 1;
    if (n.cchildren.empty()) return;
    Word row[max_arity];
    std::memcpy(row, n.visible.key(id), sizeof(Word) * n.visible.arity());
    for (const auto& child : n.cchildren) {
      Word key[max_arity];
      for (std::size_t i = 0; i < child.parent_positions.size(); ++i) key[i] = row[child.parent_positions[i]];
      auto& d = nodes[child.node];
      const auto found = d.live.find(key);
      if (found != none) { ++d.live.payload(found)[0]; continue; }
      d.live.payload(d.live.insert(key))[0] = 1;
      for (auto f = d.visible.bucket(0, key); f != none; f = d.visible.next(0, f))
        if (!live(d.visible.payload(f))) make_live(child.node, f);
    }
  }
  void make_dead(std::uint32_t v, std::uint32_t id) {
    auto& n = nodes[v];
    n.visible.payload(id)[1] &= ~Word{1};
    if (n.cchildren.empty()) return;
    Word row[max_arity];
    std::memcpy(row, n.visible.key(id), sizeof(Word) * n.visible.arity());
    for (const auto& child : n.cchildren) {
      Word key[max_arity];
      for (std::size_t i = 0; i < child.parent_positions.size(); ++i) key[i] = row[child.parent_positions[i]];
      auto& d = nodes[child.node];
      const auto found = d.live.find(key);
      require(found != none, "live separator underflow");
      if (--d.live.payload(found)[0] > 0) continue;
      d.live.erase(found);
      for (auto f = d.visible.bucket(0, key); f != none; f = d.visible.next(0, f))
        if (live(d.visible.payload(f))) make_dead(child.node, f);
    }
  }

  // ------------------------------------------------------------ enumeration
  // Visits every completion of the plan; emits (key, before, after) products.
  void enumerate(const Plan& plan, std::uint32_t first, bool changes, FlatCountSink sink) const {
    const auto count = plan.steps.size();
    const Table* tables[max_nodes];
    for (std::size_t s = 0; s < count; ++s) tables[s] = &nodes[plan.steps[s].node].visible;
    std::uint32_t current[max_nodes];
    Word out[256];
    const auto width = plan.output.size();
    const auto stamp = static_cast<Word>(route);
    auto valid = [&](std::size_t s, std::uint32_t id) {
      const auto& step = plan.steps[s];
      const Word* payload = tables[s]->payload(id);
      if (step.live && !live(payload)) return false;
      if (step.prune && payload[2] == stamp) return false;
      return true;
    };
    auto advance = [&](std::size_t s, std::uint32_t id) {
      const auto index = plan.steps[s].index;
      while (id != none && !valid(s, id)) id = tables[s]->next(index, id);
      return id;
    };
    auto open = [&](std::size_t s) {
      const auto& step = plan.steps[s];
      const Word* source = tables[step.from]->key(current[step.from]);
      Word probe[max_arity];
      for (std::size_t i = 0; i < step.key_positions.size(); ++i) probe[i] = source[step.key_positions[i]];
      return advance(s, tables[s]->bucket(step.index, probe));
    };
    auto emit = [&] {
      std::uint64_t after = 1, before = 1;
      for (std::size_t s = 0; s < count; ++s) {
        const Word* payload = tables[s]->payload(current[s]);
        const auto weight = static_cast<std::uint64_t>(payload[0]);
        after = multiply(after, weight);
        if (changes) before = multiply(before, static_cast<std::uint64_t>(payload[2] == stamp ? payload[3] : payload[0]));
      }
      if (!changes) before = 0;
      if (before == after) return;
      for (std::size_t i = 0; i < width; ++i) {
        const auto [s, field] = plan.output[i];
        out[i] = s == none ? output_constants[field] : tables[s]->key(current[s])[field];
      }
      if (sink.group) sink.group(sink.context, out, width, before, after);
    };
    current[0] = first;
    if (count == 1) { emit(); return; }
    std::size_t s = 1;
    current[1] = open(1);
    for (;;) {
      if (current[s] == none) {
        if (--s == 0) break;
        current[s] = advance(s, tables[s]->next(plan.steps[s].index, current[s]));
        continue;
      }
      if (s + 1 == count) {
        emit();
        current[s] = advance(s, tables[s]->next(plan.steps[s].index, current[s]));
        continue;
      }
      ++s;
      current[s] = open(s);
    }
  }

  // ------------------------------------------------------------------ apply
  void apply(TableId table, std::int64_t delta, const Word* row, FlatCountSink sink) {
    require(delta == 1 || delta == -1, "multiplicity changes are +1 or -1");
    const auto& base = bases.at(table.value);
    for (const auto occurrence : base.routes) apply_route(inputs[occurrence], delta, row, sink);
  }
  void apply_route(const Input& in, std::int64_t delta, const Word* row, FlatCountSink sink) {
    for (const auto& [left, right] : in.equal) if (row[left] != row[right]) return;
    for (const auto& [column, value] : in.constant) if (row[column] != value) return;
    for (const auto& predicate : in.predicates) {
      const Word a = predicate.left.column ? row[predicate.left.index] : predicate.left.value;
      const Word b = predicate.right.column ? row[predicate.right.index] : predicate.right.value;
      bool keep;
      switch (predicate.operation) {
        case frontend::SqlOperator::equal: keep = a == b; break;
        case frontend::SqlOperator::not_equal: keep = a != b; break;
        case frontend::SqlOperator::less: keep = a < b; break;
        case frontend::SqlOperator::less_equal: keep = a <= b; break;
        case frontend::SqlOperator::greater: keep = a > b; break;
        default: keep = a >= b; break;
      }
      if (!keep) return;
    }
    Word key[max_arity];
    for (std::size_t i = 0; i < in.map.size(); ++i) key[i] = row[in.map[i]];
    const auto v = in.node;
    auto& n = nodes[v];
    auto id = n.records.find(key);
    ++route;
    if (id == none) {
      require(delta > 0, "base multiplicity underflow");
      id = n.records.insert(key);
      Word* payload = n.records.payload(id);
      std::uint32_t satisfied = 0;
      for (std::uint32_t slot = 0; slot < n.children; ++slot) {
        const auto& positions = n.child_positions[slot];
        Word probe[max_arity];
        for (std::size_t i = 0; i < positions.size(); ++i) probe[i] = key[positions[i]];
        const auto& support = nodes[n.child_nodes[slot]].support;
        const auto found = support.find(probe);
        payload[1 + slot] = found == none ? 0 : support.payload(found)[0];
        if (payload[1 + slot] > 0) ++satisfied;
      }
      payload[0] = pack(0, satisfied);
    }
    Word* payload = n.records.payload(id);
    const auto before = weights(v, payload);
    const auto multiplicity = static_cast<std::int64_t>(low(payload[0])) + delta;
    require(multiplicity >= 0 && multiplicity < (std::int64_t{1} << 32), "base multiplicity out of range");
    payload[0] = pack(static_cast<std::uint32_t>(multiplicity), high(payload[0]));
    const auto after = weights(v, payload);
    changed_record(v, key, before, after);
    if (multiplicity == 0) n.records.erase(id);
    if (options.delta) finish_route(delta > 0, sink);
  }
  void finish_route(bool add, FlatCountSink sink) {
    if (add) {
      for (const auto v : by_rank) {
        auto& n = nodes[v];
        for (const auto id : n.changed) {
          const Word* payload = n.visible.payload(id);
          if (live(payload) || payload[3] != 0) continue;  // only newly visible keys
          bool is_live = v == root;
          if (!is_live) {
            Word key[max_arity];
            const Word* row = n.visible.key(id);
            for (std::size_t i = 0; i < n.separator_positions.size(); ++i) key[i] = row[n.separator_positions[i]];
            is_live = n.live.find(key) != none;
          }
          if (is_live) make_live(v, id);
        }
      }
    }
    for (const auto v : by_rank)
      for (const auto id : nodes[v].changed)
        if (live(nodes[v].visible.payload(id))) enumerate(anchor[v], id, true, sink);
    if (!add) {
      for (const auto v : by_rank) {
        auto& n = nodes[v];
        for (const auto id : n.changed) {
          if (n.visible.payload(id)[0] != 0) continue;
          if (live(n.visible.payload(id))) make_dead(v, id);
          n.visible.erase(id);
        }
      }
    }
    for (const auto v : by_rank) nodes[v].changed.clear();
  }
  void snapshot(FlatCountSink sink) const {
    const auto& table = nodes[root].visible;
    for (std::uint32_t id = 0; id < table.ids(); ++id)
      if (table.used(id)) enumerate(snapshot_plan, id, false, sink);
  }
};

std::string FlatCountRuntime::unsupported(const CompiledProgram& program) { return check(program); }
FlatCountRuntime::FlatCountRuntime(const CompiledProgram& program, FlatOptions options)
    : impl_(std::make_unique<Impl>(program, options)) {}
FlatCountRuntime::~FlatCountRuntime() = default;
FlatCountRuntime::FlatCountRuntime(FlatCountRuntime&&) noexcept = default;
FlatCountRuntime& FlatCountRuntime::operator=(FlatCountRuntime&&) noexcept = default;
void FlatCountRuntime::encode(TableId table, const Row& row, std::int64_t* out) {
  const auto& base = impl_->bases.at(table.value);
  require(row.size() == base.types.size(), "row arity differs from the source table");
  for (std::size_t i = 0; i < row.size(); ++i) out[i] = impl_->encode_value(row[i]);
}
std::size_t FlatCountRuntime::arity(TableId table) const { return impl_->bases.at(table.value).types.size(); }
void FlatCountRuntime::apply(TableId table, std::int64_t delta, const std::int64_t* row, FlatCountSink sink) {
  impl_->apply(table, delta, row, sink);
}
void FlatCountRuntime::snapshot(FlatCountSink sink) const { impl_->snapshot(sink); }
std::size_t FlatCountRuntime::result_arity() const { return impl_->output_types.size(); }
Value FlatCountRuntime::decode(std::size_t column, std::int64_t value) const {
  return impl_->dictionary.decode(impl_->output_types.at(column), value);
}

}  // namespace crown::runtime
