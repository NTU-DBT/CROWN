// Supplemental proposal probe; not a repository target or P07 acceptance suite.
#define main crown_p05_original_exception_test_main
#include "../../../tests/unit/residual_exception_test.cpp"
#undef main
#include "key_machine.hpp"

namespace ap = crown::planner::alternatives_proposal;
namespace {
std::shared_ptr<const FreeConnexTree> key_tree() {
  auto tree = std::make_shared<FreeConnexTree>();
  tree->root = NodeId{1};
  tree->nodes = {
      TreeNode{"R", NodeKind::native, {VariableId{0}}, {}, 0, {}},
      TreeNode{"S", NodeKind::native, {VariableId{0}, VariableId{1}}, {NodeId{0}, NodeId{2}}, 1, {}},
      TreeNode{"T", NodeKind::native, {VariableId{1}}, {}, 2, {}}};
  return tree;
}
void finish_key(ap::StructuralKeyMachine& key) {
  for (std::uint64_t i = 0; i < 1'000'000; ++i) {
    const auto step = key.step({256});
    check(step.event != ap::KeyEvent::stopped, "proposal key unexpectedly stopped");
    if (step.event == ap::KeyEvent::key_ready) return;
  }
  check(false, "proposal key exceeded finite probe bound");
}
bool same_key_stats(const ap::KeyStatistics& a, const ap::KeyStatistics& b) {
  return a.completed_steps == b.completed_steps && a.completed_nodes == b.completed_nodes &&
      a.compared_characters == b.compared_characters && a.peak_depth == b.peak_depth;
}
}

int main() {
  try {
    const auto fixture = scoped_fixture({{0}, {0, 1}, {1}}, {});
    const auto tree = key_tree();
    check(validate_tree(fixture.catalog, fixture.query, *tree).valid, "key probe input failed P02");
    auto baseline_budget = std::make_shared<ap::ContentBudget>();
    ap::StructuralKeyMachine baseline(tree, baseline_budget);
    allocation_count = 0;
    finish_key(baseline);
    const auto allocations = allocation_count;
    const auto expected = baseline.key();
    const auto stats = baseline.statistics();
    check(expected && allocations > 0, "key probe did not publish an allocated key");
    for (std::size_t point = 0; point < allocations; ++point) {
      auto budget = std::make_shared<ap::ContentBudget>();
      ap::StructuralKeyMachine key(tree, budget);
      bool failed = false, repeats = true;
      {
        FaultScope fault(static_cast<std::ptrdiff_t>(point));
        try { finish_key(key); } catch (const std::bad_alloc&) { failed = true; }
        const auto before = key.statistics();
        const auto records = budget->records(), cells = budget->cells();
        for (int retry = 0; retry != 2; ++retry) {
          bool again = false;
          try { static_cast<void>(key.step({256})); } catch (const std::bad_alloc&) { again = true; }
          repeats = repeats && again && same_key_stats(before, key.statistics()) &&
              budget->records() == records && budget->cells() == cells && !key.key();
        }
      }
      check(failed && repeats, "key proposal did not retain the same allocation failure");
      finish_key(key);
      check(key.key() && *key.key() == *expected && same_key_stats(key.statistics(), stats) &&
                budget->records() == baseline_budget->records() && budget->cells() == baseline_budget->cells(),
            "key proposal did not recover to its uninterrupted key/accounting");
    }
    auto budget = std::make_shared<ap::ContentBudget>(ap::ContentLimits{{}, 0});
    ap::StructuralKeyMachine limited(tree, budget);
    const auto zero_depth = limited.step({0});
    check(zero_depth.reason == ap::KeyStop::depth_limit && budget->records() == 0,
          "zero-depth proposal key constructed a frame");
    bool cell_stop = false;
    for (std::size_t n = 0; n < 100; ++n) {
      const auto update = limited.step({256});
      if (update.reason == ap::KeyStop::cell_limit) { cell_stop = true; break; }
    }
    check(cell_stop && !limited.key(), "zero-cell key budget did not stop without publication");
    check(budget->raise_limits({{}, 100'000}), "key content grant extension failed");
    finish_key(limited);
    check(limited.key() && *limited.key() == *expected, "key content stop did not resume correctly");
    const auto retained = limited.key();
    limited.cancel();
    check(*retained == *expected, "completed key changed after cancel");
    std::cout << "proposal_key fault_positions=" << allocations
              << " persistent_retries=2 same_owner_recovery=yes depth_and_cell_resume=yes\n";
  } catch (const std::exception& error) {
    fail_after = -1;
    std::cerr << error.what() << '\n';
    return 1;
  }
}
