#include "candidate_machine.hpp"
#include "producer_cursor.hpp"

#include <algorithm>
#include <limits>
#include <stdexcept>
#include <utility>
#include <vector>

namespace crown::planner::candidate_detail {
namespace cd = continuation_detail;
namespace control = cd::producer_private;
namespace {
constexpr auto counter_max = std::numeric_limits<std::uint64_t>::max();
constexpr auto index_max = std::numeric_limits<std::size_t>::max();
void prepare_increment(std::uint64_t value) {
  if (value == counter_max) throw ContentStop(GeneratorStop::counter_overflow);
}
bool monotone(std::optional<std::uint64_t> old_limit,
              std::optional<std::uint64_t> new_limit) noexcept {
  return old_limit ? (!new_limit || *new_limit >= *old_limit) : !new_limit;
}
}  // namespace

ContentBudget::ContentBudget(ContentLimits limits) noexcept : limits_(limits) {}
// Preflight only. After allocation succeeds, commit the same charge without
// intervening budget mutation. Counts are cumulative logical cells/records;
// failed allocations commit nothing and consumed/discarded content is not refunded.
void ContentBudget::prepare(std::uint64_t records, std::uint64_t cells) const {
  if (records > counter_max - records_ || cells > counter_max - cells_)
    throw ContentStop(GeneratorStop::counter_overflow);
  if (limits_.records && (records_ > *limits_.records || records > *limits_.records - records_))
    throw ContentStop(GeneratorStop::record_limit);
  if (limits_.cells && (cells_ > *limits_.cells || cells > *limits_.cells - cells_))
    throw ContentStop(GeneratorStop::cell_limit);
}
void ContentBudget::commit(std::uint64_t records, std::uint64_t cells) noexcept {
  records_ += records;
  cells_ += cells;
}
bool ContentBudget::raise_limits(ContentLimits limits) noexcept {
  if (!monotone(limits_.records, limits.records) || !monotone(limits_.cells, limits.cells) ||
      (limits.records && *limits.records < records_) ||
      (limits.cells && *limits.cells < cells_)) return false;
  limits_ = limits;
  return true;
}
ContentLimits ContentBudget::limits() const noexcept { return limits_; }
std::uint64_t ContentBudget::records() const noexcept { return records_; }
std::uint64_t ContentBudget::cells() const noexcept { return cells_; }

struct NormalFormGenerator::Impl {
  struct NodeState { std::size_t parent = 0, children = 0; bool seen = false; };
  // One generalized scope: native anchor plus ascending-variable inclusion
  // bytes. Different anchors can represent the same set; dedup handles that.
  struct ScopeDigit { std::size_t anchor = 0; std::vector<unsigned char> bits; };
  struct Frame { std::size_t node, next_child, native_depth; };

  // Retained original IDs and dynamic cursors; no fixed-width subset masks.
  // ready owns a complete unchecked draft and blocks generation until consume.
  std::shared_ptr<const cd::BindingData> binding;
  std::size_t target;
  std::shared_ptr<ContentBudget> budget;
  std::vector<VariableSet> native_scopes;
  std::vector<NodeState> nodes;
  std::vector<ScopeDigit> scopes;
  std::vector<Frame> stack;
  std::shared_ptr<FreeConnexTree> building;
  std::shared_ptr<const FreeConnexTree> ready;
  GeneratorStatistics stats;
  control::Engine engine;
  control::Task task;
  bool started = false, finished = false, was_cancelled = false, overflow = false;

  Impl(std::shared_ptr<const cd::BindingData> input, std::size_t height,
       std::shared_ptr<ContentBudget> content)
      : binding(std::move(input)), target(height), budget(std::move(content)) {
    if (!binding || !budget) throw std::invalid_argument("null candidate generator input");
  }
  ~Impl() { engine.cancel(); }
  std::size_t depth() const noexcept {
    return !started || finished || was_cancelled ? 0 : 1 + stack.size();
  }
  template<class T> void append(std::vector<T>& out, T value, std::uint64_t records = 0) {
    if (out.size() == out.max_size()) throw ContentStop(GeneratorStop::counter_overflow);
    budget->prepare(records, 1);
    out.push_back(std::move(value));
    budget->commit(records, 1);
  }
  void put_variable(VariableSet& out, VariableId variable) {
    if (out.contains(variable)) return;
    if (out.size() == out.max_size()) throw ContentStop(GeneratorStop::counter_overflow);
    budget->prepare(0, 1);
    out.insert(variable);
    budget->commit(0, 1);
  }
  // Counter room first; shared ownership publication then cannot allocate.
  // The provider must still perform original P02, height and full-key checks.
  void publish() {
    prepare_increment(stats.drafts_ready);
    ready = building;
    building.reset();
    ++stats.drafts_ready;
  }

  // Every root and non-self parent tuple is visited for g=0..m-1. The local
  // contraction/guard proof justifies this minimum-height representative family;
  // no global maintenance-cost completeness or new lower proof follows.
  control::Task run() {
    // Only nonallocating control flow runs inside resume(). Each operation is
    // stored in this suspended frame and executed by Engine::step externally.
#define GEN_AT(desired, ...) co_await control::operation([&] { __VA_ARGS__; }, desired)
#define GEN_OP(...) GEN_AT(depth(), __VA_ARGS__)
    const std::size_t m = binding->query.atoms.size();
    if (m == 0) {
      GEN_OP(budget->prepare(1, 0); building = std::make_shared<FreeConnexTree>(); budget->commit(1, 0));
      GEN_OP(publish());
      while (ready) { GEN_OP((void)0); }
      GEN_OP(finished = true);
      co_return;
    }
    // Reserve representable room for both m+g and logical frame-depth + 1.
    // No factorial, power-set size, topology count or bit mask is computed.
    GEN_OP(if (m > index_max - 2) throw ContentStop(GeneratorStop::counter_overflow));
    for (std::size_t a = 0; a < m; ++a) {
      GEN_OP(append(native_scopes, VariableSet{}, 1));
      for (const auto& term : binding->query.atoms[a].terms) {
        GEN_OP(if (const auto* variable = std::get_if<VariableId>(&term))
                 put_variable(native_scopes[a], *variable));
      }
      GEN_OP(append(nodes, NodeState{}, 1));
    }

    for (std::size_t g = 0; g < m; ++g) {
      GEN_OP(if (g > index_max - 2 - m) throw ContentStop(GeneratorStop::counter_overflow));
      const std::size_t n = m + g;
      if (g != 0) {
        GEN_OP(append(nodes, NodeState{}, 1));
        GEN_OP(append(scopes, ScopeDigit{}, 1));
      }
      for (std::size_t root = 0; root < n; ++root) {
        // Root's stored parent is itself but never interpreted as an edge.
        // Every other digit ranges over all labels except its own label.
        for (std::size_t i = 0; i < n; ++i) {
          GEN_OP(nodes[i].parent = i == root ? root : (i == 0 ? 1 : 0));
        }
        bool more_topologies = true;
        while (more_topologies) {
          GEN_OP(prepare_increment(stats.topologies_examined); ++stats.topologies_examined);
          bool valid = true;
          for (std::size_t i = 0; i < n; ++i) {
            GEN_OP(nodes[i].children = 0; nodes[i].seen = false);
          }
          for (std::size_t i = 0; i < n; ++i) {
            GEN_OP(if (i != root) {
              ++nodes[nodes[i].parent].children;
              if (i >= m && nodes[i].parent < m) valid = false;
            });
          }
          for (std::size_t i = m; i < n; ++i) {
            GEN_OP(if (nodes[i].children < 2) valid = false);
          }

          std::size_t reached = 0, height = 0;
          if (valid) {
            GEN_AT(2, append(stack, Frame{root, 0, root < m ? 1U : 0U}, 1);
                      nodes[root].seen = true; reached = 1; height = root < m ? 1 : 0);
          }
          while (valid && !stack.empty()) {
            if (stack.back().next_child == n) {
              GEN_OP(stack.pop_back());
              continue;
            }
            const std::size_t child = stack.back().next_child;
            if (child == root || nodes[child].parent != stack.back().node) {
              GEN_OP(++stack.back().next_child);
              continue;
            }
            if (nodes[child].seen) {
              GEN_OP(valid = false);
              continue;
            }
            const std::size_t child_height = stack.back().native_depth + (child < m ? 1U : 0U);
            // Push preparation precedes all other mutations in this operation.
            GEN_AT(2 + stack.size(), append(stack, Frame{child, 0, child_height}, 1);
                   ++stack[stack.size() - 2].next_child; nodes[child].seen = true;
                   ++reached; height = std::max(height, child_height));
          }
          while (!stack.empty()) { GEN_OP(stack.pop_back()); }
          GEN_OP(valid = valid && reached == n && height == target);
          if (valid) {
            GEN_OP(prepare_increment(stats.topology_survivors); ++stats.topology_survivors);
            // Reset each mixed-radix scope digit to anchor 0, empty subset.
            // Resizing is itself a saved series of one-cell operations.
            for (std::size_t s = 0; s < g; ++s) {
              GEN_OP(scopes[s].anchor = 0);
              while (scopes[s].bits.size() > native_scopes[0].size()) {
                GEN_OP(scopes[s].bits.pop_back());
              }
              while (scopes[s].bits.size() < native_scopes[0].size()) {
                GEN_OP(append(scopes[s].bits, static_cast<unsigned char>(0)));
              }
              for (std::size_t b = 0; b < scopes[s].bits.size(); ++b) {
                GEN_OP(scopes[s].bits[b] = 0);
              }
            }
            bool more_scopes = true;
            while (more_scopes) {
              GEN_OP(budget->prepare(1, 0); building = std::make_shared<FreeConnexTree>(); budget->commit(1, 0));
              GEN_OP(building->root = NodeId{root});
              for (std::size_t i = 0; i < n; ++i) {
                GEN_OP(if (building->nodes.size() == building->nodes.max_size())
                         throw ContentStop(GeneratorStop::counter_overflow);
                       budget->prepare(1, 1);
                       TreeNode node{"p07-" + std::to_string(i),
                         i < m ? NodeKind::native : NodeKind::generalized, {}, {},
                         i < m ? std::optional<std::size_t>(i) : std::nullopt, std::nullopt};
                       building->nodes.push_back(std::move(node)); budget->commit(1, 1));
                if (i < m) {
                  for (const auto variable : native_scopes[i]) {
                    GEN_OP(put_variable(building->nodes[i].scope, variable));
                  }
                } else {
                  const auto& digit = scopes[i - m];
                  std::size_t b = 0;
                  for (const auto variable : native_scopes[digit.anchor]) {
                    GEN_OP(if (digit.bits[b] != 0) put_variable(building->nodes[i].scope, variable); ++b);
                  }
                }
              }
              for (std::size_t i = 0; i < n; ++i) {
                GEN_OP(if (i != root) append(building->nodes[nodes[i].parent].children, NodeId{i}));
              }
              GEN_OP(publish());
              // The public step gate stops before this pending operation until
              // consume_draft acknowledges validation/rejection/publication.
              while (ready) { GEN_OP((void)0); }

              // Last generalized node is the least significant tuple digit.
              // Within a digit, bit 0 (lowest variable ID) carries first, then
              // the native anchor. Duplicate representations are intentional.
              bool carry = true;
              std::size_t s = g;
              while (carry && s != 0) {
                GEN_OP(--s);
                std::size_t b = 0;
                while (carry && b < scopes[s].bits.size()) {
                  GEN_OP(if (scopes[s].bits[b] == 0) {
                    scopes[s].bits[b] = 1; carry = false;
                  } else { scopes[s].bits[b] = 0; ++b; });
                }
                if (!carry) break;
                GEN_OP(if (scopes[s].anchor + 1 < m) {
                  ++scopes[s].anchor; carry = false;
                } else { scopes[s].anchor = 0; });
                const std::size_t width = native_scopes[scopes[s].anchor].size();
                while (scopes[s].bits.size() > width) { GEN_OP(scopes[s].bits.pop_back()); }
                while (scopes[s].bits.size() < width) {
                  GEN_OP(append(scopes[s].bits, static_cast<unsigned char>(0)));
                }
              }
              GEN_OP(more_scopes = !carry);
            }
          }

          // Numeric lexicographic parent vectors, excluding the fixed root
          // digit and each nonroot self-parent value. No n^n count is needed.
          bool carry = true;
          std::size_t p = n;
          while (carry && p != 0) {
            GEN_OP(--p);
            if (p == root) continue;
            GEN_OP(std::size_t next = nodes[p].parent + 1;
                   if (next == p) ++next;
                   if (next < n) { nodes[p].parent = next; carry = false; }
                   else { nodes[p].parent = p == 0 ? 1 : 0; });
          }
          GEN_OP(more_topologies = !carry);
        }
      }
    }
    GEN_OP(finished = true);
#undef GEN_OP
#undef GEN_AT
  }
};

NormalFormGenerator::NormalFormGenerator(std::shared_ptr<const cd::BindingData> binding,
    std::size_t height, std::shared_ptr<ContentBudget> budget)
    : data_(std::make_unique<Impl>(std::move(binding), height, std::move(budget))) {}
NormalFormGenerator::~NormalFormGenerator() = default;
NormalFormGenerator::NormalFormGenerator(NormalFormGenerator&&) noexcept = default;
NormalFormGenerator& NormalFormGenerator::operator=(NormalFormGenerator&&) noexcept = default;

// Ready drafts cannot be skipped by more grants. Control-frame admission and
// DFS pushes check owned logical depth; even empty-body generation owns its
// control frame. bad_alloc escapes with the same pending operation for retry.
Step NormalFormGenerator::step(const cd::UnitContext& context) {
  auto& d = *data_;
  if (d.ready) return {GeneratorEvent::draft_ready};
  if (d.was_cancelled) return {GeneratorEvent::stopped};
  if (d.overflow) return {GeneratorEvent::stopped, GeneratorStop::counter_overflow};
  if (d.finished) return {GeneratorEvent::exhausted};
  const std::size_t required = d.started ? d.depth() : 1;
  if (!context.permits(required)) return {GeneratorEvent::stopped, GeneratorStop::depth_limit, required};
  try {
    prepare_increment(d.stats.completed_steps);
    if (!d.started) {
      d.budget->prepare(1, 0);
      d.task = d.run();  // Allocates outside resume; failure leaves started false.
      d.engine.start(d.task);
      d.started = true;
      d.budget->commit(1, 0);
    } else {
      const auto result = d.engine.step(context);
      if (result.event == cd::UnitEvent::depth_blocked)
        return {GeneratorEvent::stopped, GeneratorStop::depth_limit, result.requested_depth};
    }
    ++d.stats.completed_steps;
    d.stats.peak_depth = std::max(d.stats.peak_depth, d.depth());
    return {d.ready ? GeneratorEvent::draft_ready :
            (d.finished ? GeneratorEvent::exhausted : GeneratorEvent::advanced)};
  } catch (const ContentStop& stop) {
    d.overflow = stop.reason == GeneratorStop::counter_overflow;
    return {GeneratorEvent::stopped, stop.reason};
  }
}
std::shared_ptr<const FreeConnexTree> NormalFormGenerator::draft() const noexcept { return data_->ready; }
// Acknowledge only after provider validation/rejection/publication. Reset
// before increment prevents duplicate acknowledgements from inflating history.
void NormalFormGenerator::consume_draft() noexcept {
  if (!data_->ready) return;
  data_->ready.reset();
  ++data_->stats.drafts_consumed;  // <= drafts_ready, checked before publication.
}
const GeneratorStatistics& NormalFormGenerator::statistics() const noexcept { return data_->stats; }
std::size_t NormalFormGenerator::current_depth() const noexcept { return data_->depth(); }
bool NormalFormGenerator::cancelled() const noexcept { return data_->was_cancelled; }
void NormalFormGenerator::cancel() noexcept {
  if (!data_ || data_->was_cancelled) return;
  data_->engine.cancel();
  data_->building.reset();
  data_->ready.reset();
  data_->native_scopes.clear();
  data_->nodes.clear();
  data_->scopes.clear();
  data_->stack.clear();
  data_->was_cancelled = true;
}
}  // namespace crown::planner::candidate_detail
