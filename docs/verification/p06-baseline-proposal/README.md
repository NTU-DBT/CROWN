# P06 private v1 baseline extraction proposal

Prepared by Luna Max and source-reviewed by root during the frozen P04 matrix.
These files are not compiled, integrated or acceptance-verified. They preserve
current unoptimized v1 labelled-state search while separating it from future
production continuation code. Do not count this proposal as P06 implementation.

Proposed files: [baseline](planner_exact_baseline.cpp) and
[private budget](planner_baseline_budget.hpp). Copy them together to tests/support
only when P06 integration starts. Compile the baseline source only in
crown_planner_testing with CROWN_PLANNER_TESTING; remove the current second
compilation of production exact.cpp. Its sole external definition is
crown::planner::testing::minimum_tree_baseline. Preserve the existing probe
header signature and verify both CLI and combined baseline/ExactSearch linkage.

The recurrence, partition/root order, exact state keys, tree/proof export and
independent public v1 replay are retained. The private budget differs from the
current production header only by namespace, an explicit string include and
formatting. Component/hierarchy shortcuts, equal-scope symmetry, incumbent
pruning and scope-orbit proof transport are removed from this baseline.

The [implementation seams](../p06-implementation-seams-2026-11-06.md) and
[transition plan](../p06-transition-plan-2026-11-06.md) govern actual integration.
No builds or tests have run against this extracted proposal.
