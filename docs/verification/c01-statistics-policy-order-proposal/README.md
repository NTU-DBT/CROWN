# C01 enabled policy and window acceptance preparation

Excluded preparation; native files remain unchanged and C01 remains `not_started`.
The three fixture overlays preserve the existing A04/prefix/list-oracle assertions
and add opt-in `CROWN_STATISTICS_ACCEPTANCE` census checks. With the macro absent,
their original behavior is preserved. `prepare-fixtures.py` performs checked,
single-occurrence insertions into the pinned original files; it does not run a
compiler or executable.

The new support header checks actual source cardinalities against each fixture's
independent database, factory owner/committed epoch binding, selected physical
changed/no-op inputs, and derivation after-value distributions/zero crossings.
The derivation audit used here is independently checked by the existing prefix
oracle; the helper does not call collector accumulation methods. Window checks
use the independent command expansion and distinguish actual physical work from
metadata-only barriers. Explicit cardinality-only requests perform no NDV scan.

The root runner compiles only these new production consumers, reusing the
already accepted complete strict and ASan/UBSan production runtime closures.
It records actual commands, object/archive identities, logs and each exit status.
It runs the delta fixture with default, eager, incremental, anchored and root_first
selections, plus the separate explicit ordered-replay and window fixtures. These
are seven selected executions, not an exhaustive Cartesian product of policies.
O07 observation settings and every original semantic/work assertion remain as in
the predecessor fixtures. This packet is not timing evidence or native C01
acceptance. Typed-domain/constraint checks and report/schema work are separate.

`PACKAGE_SHA256SUMS` seals this package before root execution; the root result is
stored outside the package to avoid changing its identity after testing.

## Session metadata accessor revision

The first root attempt failed compilation before executing any fixture because the new helper incorrectly called `QuerySession::owner()`. This revision obtains the actual owner through the existing factory-produced `report_metadata().owner()` accessor. No engine code, numeric expectation or predecessor assertion changes. The frozen original package and failed attempt are preserved.

## Window observation-boundary revision

Attempt 2 passed the five strict delta selections and the explicit replay fixture, then the new window helper rejected the first command. Source tracing establishes that `begin_next_result()` has already admitted its physical root before `Harness::commit_step` takes the before-snapshot. The snapshot therefore already includes that attempt/selection, while committed cells/complete counters still await publication. This revision requires exactly one such private admitted root and expects no second admission at commit. Direct Delta checks continue to require one new admission. Engine sources, original semantic assertions, input counts and histogram expectations are unchanged. Attempt 3 reuses the six passing strict executions from attempt 2, runs corrected strict window acceptance, and compiles/runs all seven sanitizer consumers.

## Propagation-order extension

The same accepted census assertions now accept a test-only compile-time order selection. Without `CROWN_STATISTICS_LIFO`, enabled fixtures use FIFO. The new runner defines that macro and runs all seven selections under LIFO, in strict and sanitizer consumers. Actual Delta/session options are checked before collection is enabled; the executable prints the selected order. All original semantic and numeric expectations remain. `order-changes.diff` records the exact additional test-only edits against the frozen window revision. This extends selected order coverage, not the Cartesian combination of every mode/completion/live-policy option. The original fixture-preparation script is historical in the base package; this package's sealed overlay/diff are the generated sources.
