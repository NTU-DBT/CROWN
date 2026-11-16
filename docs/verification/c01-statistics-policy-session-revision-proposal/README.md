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
