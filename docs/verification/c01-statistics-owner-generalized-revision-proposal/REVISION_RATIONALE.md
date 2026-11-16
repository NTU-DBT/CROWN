# Generalized fixture correction

Root attempt 1 of owner package `b2599d31f8f982bf764e1c65b0f8001357f299363c39b847647d7e53d73ce89d` stopped at `owner_statistics_test.cpp:84`. The compound assertion combined valid generalized cardinalities with an invalid demand for at least one non-connex node in that geometry. The preserved failure log is `build/verification/c01-statistics-owner-root-attempt-1-strict-owner_statistics_test.log`; it does not identify a numerical collector discrepancy.

## The actual C* rule

`src/planner/verify.cpp:340–351` traverses from the root and includes a child when every variable in its **parent separator** belongs to the output head. It does not require the child's whole scope to contain only output variables. `src/planner/lower.cpp:251–268` creates E precisely for the resulting maximal connex nodes and projects each node's scope onto head variables.

The original query has head y and the supplied tree `G(y) -> {R(x,y), S(y)}`. Both child separators are `{y}`. Therefore C* contains nodes G, R and S, even though R also contains hidden x. All three E factors exist. The old test only appended E requests for nodes without a visible relation, so it appended none and its `components().size()>2` condition failed.

Generalized population expectations remain unchanged. `src/runtime/support.cpp:1348–1379` builds generalized records from the union of child P keys and retains a survivor exactly when all child keys are present. Literal R source rows are `(1,7,10),(1,7,11),(2,7,20),(3,8,30)`; ignored suffixes make native R `{(1,7),(2,7),(3,8)}`. Literal S is `{(7)}`. Thus:

| Node | Records | S | P multiplicities | E multiplicities |
| --- | --- | --- | --- | --- |
| G(y) | `{7,8}` | `{7}` | `{():1}` | `{7:1}` |
| R(x,y) | `{(1,7),(2,7),(3,8)}` | Same three rows | `{7:2,8:1}` | `{7:2,8:1}` |
| S(y) | `{7}` | `{7}` | `{7:1}` | `{7:1}` |

R's E is a local factor population, so y=8 remains there while absent from G's S and the final answer. The corrected group 9 asserts C* exactly, keeps G records=2/S=1 and both original exact distributions, and adds all three E distributions plus G's P distribution. It does not reduce the cardinality requirement or alter the collector.

## A genuinely hidden separator

A separate catalog and data fixture adds table T(x) with rows `{1,2,3}`. Its tree is `G(y) -> {R(x,y), S(y)}` with T(x) below R. R's separator to G remains `{y}`, while T's separator to R is `{x}`. Since the head is still `{y}`, C* is exactly `{G,R,S}` and T is outside C*.

All three native R rows match T, so G retains the same records `{7,8}` and S `{7}`. T has three records, three survivors and three P keys with support one. E(T) is `not_applicable`, with no cardinality or distribution. This distinguishes absent E from an empty existing E factor and supplies the non-connex assertion that the original geometry could not exercise.

## Preservation and diagnostic boundary

All runtime/storage source and public/internal header bytes match the frozen owner package. Every assertion outside ordinary test group 9 is unchanged, including finite budgets, owning immutable reports, freshness, lifecycle and allocation sweeps. The common fixture header only adds the independent hidden-separator plan/data helpers; existing helpers remain unchanged.

`owner_statistics_generalized_diagnostic.cpp` prints both compiled plans' node kinds, scopes, separators, C* and E availability. It separately prints native `canonical_state()` rows/P/E maps and explicit capture results. This small diagnostic is allowed to read native canonical state; bounded collector paths remain unchanged and do not materialize snapshots. The diagnostic is not an expected-value oracle for the test, and the author does not execute it. Root may execute it before the complete strict and sanitizer suites. C01 remains `not_started` until the broader acceptance work is complete.
