#include "crown/runtime/flat.hpp"
#include "flat_plan.hpp"

#include <algorithm>
#include <array>
#include <bit>
#include <cstring>
#include <stdexcept>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace crown::runtime {
namespace {
using namespace flat_detail;

}  // namespace

struct FlatRuntime::Impl : FlatProgram {
  FlatOptions options;
  FlatStatistics stats;
  Impl(const CompiledProgram& program, FlatOptions value) : FlatProgram(program, value.delta, false), options(value) {}

  // ---------------------------------------------------------------- support
  void survivor(std::uint32_t v, std::uint32_t id, bool add) {
    auto& n = nodes[v];
    Word record[max_arity];
    std::memcpy(record, n.records.key(id), sizeof(Word) * n.arity);
    if (n.connex) {
      Word key[max_arity];
      for (std::size_t i = 0; i < n.visible_positions.size(); ++i) key[i] = record[n.visible_positions[i]];
      visible_change(v, key, add);
    }
    if (n.parent != none) {
      Word key[max_arity];
      for (std::size_t i = 0; i < n.parent_positions.size(); ++i) key[i] = record[n.parent_positions[i]];
      support_change(v, key, add);
    }
  }
  void visible_change(std::uint32_t v, const Word* key, bool add) {
    auto& n = nodes[v];
    auto& table = n.visible;
    if (add) {
      auto id = table.find(key);
      if (id == none) {
        id = table.insert(key);
        Word* payload = table.payload(id);
        payload[0] = 1;
        if (options.delta) { payload[1] = static_cast<Word>(route); n.changed.push_back(id); }
        return;
      }
      ++table.payload(id)[0];
      return;
    }
    const auto id = table.find(key);
    require(id != none, "visible key underflow");
    Word* payload = table.payload(id);
    require(low(payload[0]) > 0, "visible count underflow");
    payload[0] = pack(low(payload[0]) - 1, high(payload[0]));
    if (low(payload[0]) != 0) return;
    if (options.delta) { payload[1] = static_cast<Word>(route); n.changed.push_back(id); }
    else table.erase(id);
  }
  void support_change(std::uint32_t v, const Word* key, bool add) {
    auto& table = nodes[v].support;
    if (add) {
      const auto id = table.find(key);
      if (id != none) { ++table.payload(id)[0]; return; }
      table.payload(table.insert(key))[0] = 1;
      child_flip(nodes[v].parent, nodes[v].slot, key, true);
      return;
    }
    const auto id = table.find(key);
    require(id != none, "support key underflow");
    if (--table.payload(id)[0] > 0) return;
    table.erase(id);
    child_flip(nodes[v].parent, nodes[v].slot, key, false);
  }
  void child_flip(std::uint32_t p, std::uint32_t slot, const Word* key, bool appeared) {
    auto& n = nodes[p];
    const std::uint64_t bit = 1ULL << slot;
    if (n.native) {
      for (auto id = n.records.bucket(slot, key); id != none;) {
        const auto next = n.records.next(slot, id);
        Word* payload = n.records.payload(id);
        const auto satisfied = high(payload[0]);
        const bool before = satisfied == n.children;
        auto bits = static_cast<std::uint64_t>(payload[1]);
        require(((bits & bit) != 0) != appeared, "child presence applied twice");
        bits ^= bit;
        payload[1] = static_cast<Word>(bits);
        payload[0] = pack(low(payload[0]), appeared ? satisfied + 1 : satisfied - 1);
        const bool after = (appeared ? satisfied + 1 : satisfied - 1) == n.children;
        if (before != after) survivor(p, id, after);
        id = next;
      }
      return;
    }
    Word record[max_arity];
    const auto& place = n.generalized_place[slot];
    for (std::size_t i = 0; i < place.size(); ++i) record[place[i]] = key[i];
    auto id = n.records.find(record);
    if (appeared) {
      if (id == none) id = n.records.insert(record);
      Word* payload = n.records.payload(id);
      auto bits = static_cast<std::uint64_t>(payload[1]);
      require((bits & bit) == 0, "generalized presence applied twice");
      payload[1] = static_cast<Word>(bits | bit);
      const auto satisfied = high(payload[0]) + 1;
      payload[0] = pack(0, satisfied);
      if (satisfied == n.children) survivor(p, id, true);
      return;
    }
    require(id != none, "generalized candidate missing");
    Word* payload = n.records.payload(id);
    auto bits = static_cast<std::uint64_t>(payload[1]);
    require((bits & bit) != 0, "generalized presence removed twice");
    payload[1] = static_cast<Word>(bits & ~bit);
    const auto satisfied = high(payload[0]);
    payload[0] = pack(0, satisfied - 1);
    if (satisfied == n.children) survivor(p, id, false);
    if (satisfied == 1) n.records.erase(id);
  }

  // ------------------------------------------------------------------- live
  static bool is_live(const Table& table, std::uint32_t id) {
    return (static_cast<std::uint64_t>(table.payload(id)[0]) & live_bit) != 0;
  }
  void make_live(std::uint32_t v, std::uint32_t id) {
    auto& n = nodes[v];
    Word* payload = n.visible.payload(id);
    payload[0] = static_cast<Word>(static_cast<std::uint64_t>(payload[0]) | live_bit);
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
        if (!is_live(d.visible, f)) make_live(child.node, f);
    }
  }
  void make_dead(std::uint32_t v, std::uint32_t id) {
    auto& n = nodes[v];
    Word* payload = n.visible.payload(id);
    payload[0] = static_cast<Word>(static_cast<std::uint64_t>(payload[0]) & ~live_bit);
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
        if (is_live(d.visible, f)) make_dead(child.node, f);
    }
  }

  // ------------------------------------------------------------ enumeration
  std::uint64_t enumerate(const Plan& plan, std::uint32_t first, SetOperation operation, FlatSink sink) const {
    const auto count = plan.steps.size();
    const Table* tables[max_nodes];
    for (std::size_t s = 0; s < count; ++s) tables[s] = &nodes[plan.steps[s].node].visible;
    std::uint32_t current[max_nodes];
    Word out[256];
    const auto width = plan.output.size();
    const auto stamp = static_cast<Word>(route);
    std::uint64_t rows = 0;
    auto valid = [&](std::size_t s, std::uint32_t id) {
      const auto& step = plan.steps[s];
      const Word* payload = tables[s]->payload(id);
      if (step.live && !(static_cast<std::uint64_t>(payload[0]) & live_bit)) return false;
      if (step.prune && payload[1] == stamp) return false;
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
      for (std::size_t i = 0; i < width; ++i) {
        const auto [s, field] = plan.output[i];
        out[i] = s == none ? output_constants[field] : tables[s]->key(current[s])[field];
      }
      if (sink.row) sink.row(sink.context, operation, out, width);
      ++rows;
    };
    current[0] = first;
    if (count == 1) { emit(); return rows; }
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
    return rows;
  }

  // ------------------------------------------------------------------ apply
  void apply(TableId table, SetOperation operation, const Word* row, FlatSink sink) {
    auto& base = bases.at(table.value);
    ++stats.physical_events;
    const bool add = operation == SetOperation::insert;
    if (base.dedupe) {
      const auto id = base.rows.find(row);
      if (add) { if (id != none) return; base.rows.insert(row); }
      else { if (id == none) return; base.rows.erase(id); }
    }
    for (const auto occurrence : base.routes) apply_route(base, inputs[occurrence], add, row, sink);
  }
  void apply_route(const Base& base, const Input& in, bool add, const Word* row, FlatSink sink) {
    ++stats.routes;
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
    auto& n = nodes[in.node];
    auto& records = n.records;
    auto id = records.find(key);
    if (add) {
      if (id != none) {
        if (base.dedupe) records.payload(id)[0] = pack(low(records.payload(id)[0]) + 1, high(records.payload(id)[0]));
        return;
      }
      ++route;
      id = records.insert(key);
      std::uint32_t satisfied = 0;
      std::uint64_t bits = 0;
      for (std::uint32_t slot = 0; slot < n.children; ++slot) {
        const auto& positions = n.child_positions[slot];
        Word probe[max_arity];
        for (std::size_t i = 0; i < positions.size(); ++i) probe[i] = key[positions[i]];
        if (nodes[n.child_nodes[slot]].support.find(probe) != none) { bits |= 1ULL << slot; ++satisfied; }
      }
      Word* payload = records.payload(id);
      payload[0] = pack(1, satisfied);
      payload[1] = static_cast<Word>(bits);
      if (satisfied == n.children) survivor(in.node, id, true);
    } else {
      if (id == none) return;
      Word* payload = records.payload(id);
      if (low(payload[0]) > 1) { payload[0] = pack(low(payload[0]) - 1, high(payload[0])); return; }
      ++route;
      if (high(payload[0]) == n.children) survivor(in.node, id, false);
      records.erase(id);
    }
    ++stats.route_changes;
    if (options.delta) finish_route(add, sink);
  }
  void finish_route(bool add, FlatSink sink) {
    const auto operation = add ? SetOperation::insert : SetOperation::erase;
    if (add) {
      for (const auto v : by_rank) {
        auto& n = nodes[v];
        for (const auto id : n.changed) {
          if (is_live(n.visible, id)) continue;
          bool live = v == root;
          if (!live) {
            Word key[max_arity];
            const Word* row = n.visible.key(id);
            for (std::size_t i = 0; i < n.separator_positions.size(); ++i) key[i] = row[n.separator_positions[i]];
            live = n.live.find(key) != none;
          }
          if (live) make_live(v, id);
        }
      }
    }
    for (const auto v : by_rank) {
      auto& n = nodes[v];
      stats.changed_keys += n.changed.size();
      for (const auto id : n.changed)
        if (is_live(n.visible, id)) stats.delta_rows += enumerate(anchor[v], id, operation, sink);
    }
    if (!add) {
      for (const auto v : by_rank) {
        auto& n = nodes[v];
        for (const auto id : n.changed) {
          if (is_live(n.visible, id)) make_dead(v, id);
          n.visible.erase(id);
        }
      }
    }
    for (const auto v : by_rank) nodes[v].changed.clear();
  }

  void snapshot(FlatSink sink) {
    const auto& table = nodes[root].visible;
    for (std::uint32_t id = 0; id < table.ids(); ++id)
      if (table.used(id)) stats.snapshot_rows += enumerate(snapshot_plan, id, SetOperation::insert, sink);
  }
};

std::string FlatRuntime::unsupported(const CompiledProgram& program) { return check(program); }
FlatRuntime::FlatRuntime(const CompiledProgram& program, FlatOptions options)
    : impl_(std::make_unique<Impl>(program, options)) {}
FlatRuntime::~FlatRuntime() = default;
FlatRuntime::FlatRuntime(FlatRuntime&&) noexcept = default;
FlatRuntime& FlatRuntime::operator=(FlatRuntime&&) noexcept = default;

void FlatRuntime::encode(TableId table, const Row& row, std::int64_t* out) {
  const auto& base = impl_->bases.at(table.value);
  require(row.size() == base.types.size(), "row arity differs from the source table");
  for (std::size_t i = 0; i < row.size(); ++i) out[i] = impl_->encode_value(row[i]);
}
std::size_t FlatRuntime::arity(TableId table) const { return impl_->bases.at(table.value).types.size(); }
void FlatRuntime::apply(TableId table, SetOperation operation, const std::int64_t* row, FlatSink sink) {
  impl_->apply(table, operation, row, sink);
}
void FlatRuntime::snapshot(FlatSink sink) const { impl_->snapshot(sink); }
std::size_t FlatRuntime::result_arity() const { return impl_->output_types.size(); }
Value FlatRuntime::decode(std::size_t column, std::int64_t value) const {
  return impl_->dictionary.decode(impl_->output_types.at(column), value);
}
const FlatStatistics& FlatRuntime::statistics() const { return impl_->stats; }
FlatOptions FlatRuntime::options() const { return impl_->options; }

}  // namespace crown::runtime
