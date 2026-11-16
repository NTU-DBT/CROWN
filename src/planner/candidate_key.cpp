#include "candidate_key.hpp"
#include "producer_cursor.hpp"

#include <algorithm>
#include <array>
#include <charconv>
#include <limits>
#include <stdexcept>
#include <string_view>
#include <system_error>
#include <utility>
#include <vector>

namespace crown::planner::candidate_detail {
namespace cd = continuation_detail;
namespace control = cd::producer_private;
namespace {
constexpr std::uint64_t counter_max = std::numeric_limits<std::uint64_t>::max();

void prepare_increment(std::uint64_t value) {
  if (value == counter_max) throw ContentStop(GeneratorStop::counter_overflow);
}

KeyStop key_stop(GeneratorStop reason) noexcept {
  switch (reason) {
    case GeneratorStop::none: return KeyStop::none;
    case GeneratorStop::depth_limit: return KeyStop::depth_limit;
    case GeneratorStop::record_limit: return KeyStop::record_limit;
    case GeneratorStop::cell_limit: return KeyStop::cell_limit;
    case GeneratorStop::counter_overflow: return KeyStop::counter_overflow;
  }
  return KeyStop::counter_overflow;
}
}  // namespace

struct StructuralKeyMachine::Impl {
  struct Frame {
    std::size_t node = 0;
    std::size_t next_child = 0;
    std::vector<std::size_t> order;
  };

  std::shared_ptr<const FreeConnexTree> tree;
  std::shared_ptr<ContentBudget> budget;
  std::vector<std::string> tokens;
  std::vector<Frame> stack;
  std::string building_key;
  std::shared_ptr<const std::string> published;
  KeyStatistics stats;
  control::Engine engine;
  control::Task task;
  bool started = false;
  bool finished = false;
  bool was_cancelled = false;
  bool overflow = false;
  bool root_frame_pushed = false;
  bool traversal_complete = false;
  bool invalid_input = false;

  Impl(std::shared_ptr<const FreeConnexTree> input,
       std::shared_ptr<ContentBudget> content)
      : tree(std::move(input)), budget(std::move(content)) {
    if (!tree || !budget) throw std::invalid_argument("null candidate key input");
    const bool empty = tree->nodes.empty();
    if ((empty && tree->root.has_value()) || (!empty && !tree->root.has_value()) ||
        (!empty && tree->root->value >= tree->nodes.size())) {
      invalid_input = true;
    }
  }

  ~Impl() { engine.cancel(); }

  std::size_t depth() const noexcept {
    if (finished || was_cancelled) return 0;
    return stack.size();
  }

  template<class Container, class Value>
  void append(Container& output, Value&& value, std::uint64_t records,
              std::uint64_t cells) {
    if (output.size() == output.max_size())
      throw ContentStop(GeneratorStop::counter_overflow);
    budget->prepare(records, cells);
    output.push_back(std::forward<Value>(value));
    budget->commit(records, cells);
  }

  void append_char(std::string& output, char value) {
    if (output.size() == output.max_size())
      throw ContentStop(GeneratorStop::counter_overflow);
    budget->prepare(0, 1);
    output.push_back(value);
    budget->commit(0, 1);
  }

  void publish() {
    // Call after the resumable cursor has drained its temporary token/frame
    // storage; this operation contains only publication allocation and commit.
    budget->prepare(1, 0);
    auto result = std::make_shared<const std::string>(std::move(building_key));
    published = std::move(result);
    budget->commit(1, 0);
    finished = true;
  }

  control::Task run() {
    // Every potentially allocating operation below is a saved closure and is
    // executed by Engine::step after it has checked the requested depth.
#define KEY_AT(desired, ...) \
    co_await control::operation([&] { __VA_ARGS__; }, (desired))
#define KEY_OP(...) KEY_AT(depth(), __VA_ARGS__)
#define KEY_CHAR(output, value) KEY_OP(append_char((output), (value)))
#define KEY_LITERAL(output, literal)                    \
    do {                                                 \
      for (const char key_literal_char : std::string_view{literal}) { \
        KEY_CHAR((output), key_literal_char);            \
      }                                                  \
    } while (false)
#define KEY_SIZE(output, expression)                                                   \
    do {                                                                               \
      const std::size_t key_number_value = (expression);                               \
      std::array<char, std::numeric_limits<std::size_t>::digits10 + 1> key_digits{};   \
      const auto key_conversion = std::to_chars(                                      \
          key_digits.data(), key_digits.data() + key_digits.size(), key_number_value); \
      KEY_OP(if (key_conversion.ec != std::errc{})                                     \
               throw ContentStop(GeneratorStop::counter_overflow));                    \
      for (char* key_digit = key_digits.data(); key_digit != key_conversion.ptr;       \
           ++key_digit) {                                                              \
        KEY_CHAR((output), *key_digit);                                                \
      }                                                                                \
    } while (false)

    const std::size_t node_count = tree->nodes.size();
    if (node_count == 0) {
      KEY_LITERAL(building_key, "CROWN-STRUCTURAL-KEY;1;X;");
      KEY_OP(publish());
      co_return;
    }

    // Allocate one indexed token slot at a time. NodeId values are only lookup
    // coordinates; they never enter the encoding.
    for (std::size_t index = 0; index < node_count; ++index) {
      KEY_OP(append(tokens, std::string{}, 1, 1));
    }

    const std::size_t root = tree->root->value;
    KEY_AT(1, append(stack, Frame{root, 0, {}}, 1, 1); root_frame_pushed = true);

    while (!stack.empty()) {
      const std::size_t node_index = stack.back().node;
      const TreeNode& node = tree->nodes[node_index];

      if (stack.back().next_child < node.children.size()) {
        const std::size_t child_position = stack.back().next_child;
        const std::size_t child = node.children[child_position].value;
        if (child >= node_count) {
          KEY_OP(invalid_input = true);
          co_return;
        }
        KEY_OP(if (stack.size() == std::numeric_limits<std::size_t>::max())
                 throw ContentStop(GeneratorStop::counter_overflow));
        const std::size_t requested_depth = stack.size() + 1;
        KEY_AT(requested_depth,
               append(stack, Frame{child, 0, {}}, 1, 1);
               ++stack[stack.size() - 2].next_child);
        continue;
      }

      // The order vector stores positions in the supplied child array. Its
      // values are sorted by the complete child token below, never by NodeId.
      while (stack.back().order.size() < node.children.size()) {
        const std::size_t child_position = stack.back().order.size();
        KEY_OP(append(stack.back().order, child_position, 0, 1));
      }

      // Resumable insertion sort. Each token character comparison and each
      // order-cell move is a distinct saved operation. Equal tokens stay
      // adjacent; their byte-identical encoding makes their source order moot.
      for (std::size_t insertion = 1; insertion < stack.back().order.size(); ++insertion) {
        std::size_t position = insertion;
        const std::size_t pivot_position = stack.back().order[insertion];
        const std::size_t pivot_node = node.children[pivot_position].value;
        while (position != 0) {
          const std::size_t previous_position = stack.back().order[position - 1];
          const std::size_t previous_node = node.children[previous_position].value;
          const std::string& left = tokens[pivot_node];
          const std::string& right = tokens[previous_node];
          std::size_t compare_position = 0;
          int comparison = 0;
          while (compare_position < left.size() && compare_position < right.size()) {
            KEY_OP(prepare_increment(stats.compared_characters);
                   const auto left_char = static_cast<unsigned char>(left[compare_position]);
                   const auto right_char = static_cast<unsigned char>(right[compare_position]);
                   if (left_char < right_char) comparison = -1;
                   else if (left_char > right_char) comparison = 1;
                   else ++compare_position;
                   ++stats.compared_characters);
            if (comparison != 0) break;
          }
          if (comparison == 0) {
            if (left.size() < right.size()) comparison = -1;
            else if (left.size() > right.size()) comparison = 1;
          }
          if (comparison >= 0) break;
          KEY_OP(stack.back().order[position] = stack.back().order[position - 1]; --position);
        }
        KEY_OP(stack.back().order[position] = pivot_position);
      }

      std::string& output = tokens[node_index];
      KEY_LITERAL(output, "N;K");
      KEY_CHAR(output, node.kind == NodeKind::native ? 'N' : 'G');
      KEY_CHAR(output, ';');
      KEY_CHAR(output, 'O');
      if (node.kind == NodeKind::native && node.occurrence.has_value()) {
        KEY_CHAR(output, '1');
        KEY_CHAR(output, ';');
        KEY_SIZE(output, *node.occurrence);
        KEY_CHAR(output, ';');
      } else {
        KEY_LITERAL(output, "0;");
      }
      KEY_CHAR(output, 'S');
      KEY_SIZE(output, node.scope.size());
      KEY_CHAR(output, ';');
      for (const VariableId variable : node.scope) {
        KEY_CHAR(output, 'V');
        KEY_SIZE(output, variable.value);
        KEY_CHAR(output, ';');
      }
      KEY_CHAR(output, 'C');
      KEY_SIZE(output, node.children.size());
      KEY_CHAR(output, ';');
      for (const std::size_t child_position : stack.back().order) {
        const std::size_t child_node = node.children[child_position].value;
        const std::string& child_token = tokens[child_node];
        KEY_CHAR(output, 'F');
        KEY_SIZE(output, child_token.size());
        KEY_CHAR(output, ':');
        for (const char byte : child_token) KEY_CHAR(output, byte);
      }
      KEY_LITERAL(output, "Z;");
      KEY_OP(prepare_increment(stats.completed_nodes);
             ++stats.completed_nodes;
             stack.pop_back();
             if (stack.empty()) traversal_complete = true);
    }

    if (!traversal_complete) {
      KEY_OP(invalid_input = true);
      co_return;
    }

    KEY_LITERAL(building_key, "CROWN-STRUCTURAL-KEY;1;R");
    const std::string& root_token = tokens[root];
    KEY_SIZE(building_key, root_token.size());
    KEY_CHAR(building_key, ':');
    for (const char byte : root_token) KEY_CHAR(building_key, byte);
    while (!tokens.empty()) KEY_OP(tokens.pop_back());
    KEY_OP(publish());
#undef KEY_SIZE
#undef KEY_LITERAL
#undef KEY_CHAR
#undef KEY_OP
#undef KEY_AT
  }
};

StructuralKeyMachine::StructuralKeyMachine(std::shared_ptr<const FreeConnexTree> tree,
                                           std::shared_ptr<ContentBudget> budget)
    : data_(std::make_unique<Impl>(std::move(tree), std::move(budget))) {}
// Move assignment can synchronously release the destination's prior scratch
// and last-owned input; only move construction is a plain owner transfer.
StructuralKeyMachine::~StructuralKeyMachine() = default;
StructuralKeyMachine::StructuralKeyMachine(StructuralKeyMachine&&) noexcept = default;
StructuralKeyMachine& StructuralKeyMachine::operator=(StructuralKeyMachine&&) noexcept = default;

KeyStep StructuralKeyMachine::step(const cd::UnitContext& context) {
  if (!data_) return {KeyEvent::stopped, KeyStop::cancelled};
  auto& d = *data_;
  if (d.published) return {KeyEvent::key_ready};
  if (d.was_cancelled) return {KeyEvent::stopped, KeyStop::cancelled};
  if (d.invalid_input) return {KeyEvent::stopped, KeyStop::invalid_input};
  if (d.overflow) return {KeyEvent::stopped, KeyStop::counter_overflow};
  if (d.finished) return {KeyEvent::stopped, KeyStop::invalid_input};

  const bool needs_root_depth = !d.tree->nodes.empty() && !d.root_frame_pushed;
  const std::size_t required_depth = needs_root_depth ? 1 : d.depth();
  if (!context.permits(required_depth))
    return {KeyEvent::stopped, KeyStop::depth_limit, required_depth};

  try {
    prepare_increment(d.stats.completed_steps);
    if (!d.started) {
      d.budget->prepare(1, 0);
      d.task = d.run();  // Coroutine frame allocation is outside resume().
      d.engine.start(d.task);
      d.started = true;
      d.budget->commit(1, 0);
    } else {
      const auto result = d.engine.step(context);
      if (result.event == cd::UnitEvent::depth_blocked)
        return {KeyEvent::stopped, KeyStop::depth_limit, result.requested_depth};
    }
    ++d.stats.completed_steps;
    d.stats.peak_depth = std::max(d.stats.peak_depth, d.depth());
    if (d.invalid_input) return {KeyEvent::stopped, KeyStop::invalid_input};
    return {d.published ? KeyEvent::key_ready : KeyEvent::advanced};
  } catch (const ContentStop& stop) {
    d.overflow = stop.reason == GeneratorStop::counter_overflow;
    return {KeyEvent::stopped, key_stop(stop.reason)};
  }
}

std::shared_ptr<const std::string> StructuralKeyMachine::key() const noexcept {
  return data_ ? data_->published : nullptr;
}
const KeyStatistics& StructuralKeyMachine::statistics() const noexcept {
  static const KeyStatistics empty{};
  return data_ ? data_->stats : empty;
}
std::size_t StructuralKeyMachine::current_depth() const noexcept {
  return data_ ? data_->depth() : 0;
}
bool StructuralKeyMachine::cancelled() const noexcept {
  return !data_ || data_->was_cancelled;
}
// clear drops live elements but may retain outer-vector/string capacity until
// this worker is destroyed. A published key makes cancellation a no-op.
void StructuralKeyMachine::cancel() noexcept {
  if (!data_ || data_->was_cancelled || data_->published) return;
  auto& d = *data_;
  d.engine.cancel();
  d.stack.clear();
  d.tokens.clear();
  d.building_key.clear();
  d.tree.reset();
  d.was_cancelled = true;
}

}  // namespace crown::planner::candidate_detail
