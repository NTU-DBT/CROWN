# C01 native benchmark: child P oracle correction

This is a separate, excluded revision of the frozen native benchmark proposal
at `docs/verification/c01-statistics-native-benchmark-proposal/` (manifest
SHA-256 `a281668f3abf1a978d43fafb914fe8a6851b8876181581d755adb8cf21f53887`).
The original source, package, failed root attempt, and evidence are preserved.
This revision changes only the expected population used for the S leaf's P
map. It does not alter the event trace, numeric workload expectations, runtime,
collector, native sources, or measured code.

## Reason for the correction

The admitted plan is a native R(x,y,ignored) root with native S(y) child for
the query R(x,y,ignored) AND S(y), returning (x,y). A node's P support is
formed by projecting that node's own local survivors onto its separator with
its parent. It is not formed from the global query answer. For the child, the
local survivor set is every current S(y) row and the separator is {y}; thus a
child P key remains present even when no R row currently matches y. The root
P population remains the root survivors projected onto the empty separator,
and root E remains the returned (x,y) rows.

This follows the implementation and independent native test contract:

* `src/runtime/support.cpp` rebuilds and checks each node's parent support by
  projecting that node's own survivors through its `parent_key`.
* `tests/unit/physical_runtime_test.cpp` independently checks P using
  `projected_counts(survivors, node.scope, separator(plan,node))`.
* `tests/unit/support_model_test.cpp` increments the node's expected P map
  from its own expected survivors projected onto the parent separator.
* `src/planner/lower.cpp` gives the child P projection the admitted parent
  separator; in this fixture the child scope and separator are both `{y}`.

The former oracle grouped the global joined answer by y for the S child's P
map. The revised oracle instead groups the independently replayed literal S
survivor set by y. No hard-coded counts, expected answers, trace values, or
checksums were edited. The old first root attempt is preserved as a failed
oracle validation and emitted no benchmark JSON; see `input-pins.sha256` and
`build-evidence.md` for its exact artifacts.

## Build and execution boundary

The changed consumer is compiled with C++23, `-O3 -DNDEBUG`, and the full six
warning flags as errors. The link reuses exactly the 15 O3 production
runtime/collector/storage objects from the pinned original author build; the
script verifies every object SHA-256 before compiling or linking. Only the
changed benchmark consumer is recompiled. Existing Release archives are
linked by the same path and hashes as the original proposal.

From the repository root, the exact author compile/link command is:

    CXX=c++ bash docs/verification/c01-statistics-native-benchmark-oracle-revision-proposal/build-only.sh \
      /tmp/crown-c01-native-benchmark-oracle-revision-author \
      /tmp/crown-c01-native-benchmark-author

This revision's author work compiled and linked only. The benchmark was not
executed; root owns diagnostic and benchmark execution. No test, checker,
CMake, CTest, or `nm` command was run. Successful compilation and linkage do
not yet establish that all independent runtime guards pass, nor do they produce
overhead measurements. C01 remains `not_started` and excluded preparation;
native engine/report integration remains pending.
