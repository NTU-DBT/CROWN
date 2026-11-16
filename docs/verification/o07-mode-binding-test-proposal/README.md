# Excluded O07 mode-binding test proposal

O07 remains `not_started`. This is a standalone, independent consumer test for
the excluded per-attempt mode-binding overlay. It adds no native registration,
does not modify the earlier runtime-observation suite, and does not claim the
full O07 EXPLAIN/CLI/schema/benchmark acceptance. Root owns execution and any
integration decision. The source here is not evidence that the test passed.

## Test fixture and expectations

The test builds its own literal query `Q(x) = R(x,y), S(y)` with R as the
native root, S as its child, and initial R containing only `(7,9)`. It uses
the independent materializing evaluator for full query-result checks and
literal insert/erase expectations for emitted records. It never includes the
earlier observation test source or derives expected metrics/configurations from
production output.

This tree has two physical nodes but one enumeration factor: only root R is in
the maximal-connex program because child S's separator `{y}` is not a subset of
the query head `{x}`. The expected `query_factors()` value is therefore the
literal 1, independently derived from the C* rule; it is not the physical node
count.

The cases exercise:

* Direct and insertion-replay initialization at enabled generation zero,
  followed by current-versus-historical bindings across maintenance → delta →
  maintenance → delta. They distinguish originally requested maintenance and
  automatic completion from resolved delta mode and anchored completion.
* Same-mode requests, a busy mode switch while committed output is unread,
  attempt begin/rollback/commit, output completion, and historical summaries
  that remain attached to their original mode/generation after switches.
* Exact reconstruction of every `DeltaOptions` field. The independent request
  includes finite and absent work ceilings, finite support/derivation limits,
  LIFO order, legacy transition capture, all observation fields, automatic
  completion, the core view, and nondefault spool limits.
* A zero-work failed live-image bootstrap with owner/state/current config
  preserved; a global allocation-failure sweep over every allocation observed
  during a successful mode switch. For each position, two failed switches run
  on the same owner with that position still armed, rejecting allocations at
  and after the selected index throughout each operation's unwind. Both
  failures check full canonical/physical state, storage statistics, owner,
  mode, sequence, result and configuration before the same owner retries
  successfully. The test reports the actual number of injected `bad_alloc`
  requests once after the sweep.
* The test-only generation seam at `UINT64_MAX-1`: an exact unsaturated maximum,
  subsequent successful switches that retain the maximum and set saturation,
  an unchanged copied pre-saturation value, and an attempt summary with the
  saturated binding. The same seam is ignored when observation is off. A
  separate negative case preserves the constructor rejection for off combined
  with legacy `capture_transitions=true`.
* Runtime moves, a new owner/generation-zero rebuild, and detached inline
  snapshots/configuration values that survive mode switches and runtime
  destruction. Configuration reads and requested-options reconstruction are
  checked for zero allocation.
* Matched off/counters/timed updates using the same legacy
  `capture_transitions=false` policy for independent final results and mandatory
  support/physical/delta work. Mutation allocation counts must match; the owned
  fake clock must be untouched in off/counters mode and read in timed mode. The
  separate enabled full-options round trip retains `capture_transitions=true`.
* Direct support-only and physical-only attempts with null delta configuration,
  plus a trace-mode `QuerySession` that drains output and drops runtime state
  while retaining its exact historical configuration summary.

The allocation injector sweeps the ordinary and aligned global `new` paths. It
does not inject failures into `malloc`, allocator metadata, the operating
system, or arbitrary callbacks. It persists for all allocation requests at or
after the selected position within each of two repeated failed calls on the
same runtime, and is disabled only before the successful recovery call. The
fake clock and initial-generation override are available only under
`CROWN_RUNTIME_TESTING` and are reset by the test.

## Compiler-only artifact

Compile the test translation unit with the same mode-binding header and testing
macro as the complete overlay archive. Do not use the prior runtime archive;
the public `ObservationSnapshot` and `ObservationSummary` layouts changed.
Include search order is mode-binding overlay, frozen runtime overlay, native
include, reference headers, then system third-party headers.

The matching all-runtime archive supplied by the overlay author is:

`/tmp/crown-o07-mode-binding-compile/libcrown_runtime_o07_mode_binding.a`

SHA-256:

`3a51a21032690940c3c7c83f05ddd56e275811f61955f2ed438f9487b7bcb2b9`

Strict test compile flags are C++23, `-O0`,
`-Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror`, and
`-DCROWN_RUNTIME_TESTING`. Link this test object before that archive, then the
reviewed non-runtime dependency archives: `libcrown_reference.a`,
`libcrown_plan.a`, `libcrown_sql.a`, `libpg_query.a`, and `libcrown_core.a`, in
that order. Their sources do not include the changed runtime headers. The
compiler/link step produces an artifact under `/tmp`; it does not execute it,
configure a build tree, run CTest, or use `libcrown_runtime.a`.

## Remaining O07 work

This test covers only runtime configuration identity and a focused set of
runtime lifecycles. It does not complete EXPLAIN rendering or CLI behavior,
schema/report compatibility, full observation-mode and initialization
matrices, release evidence, or the final acceptance gates for O07. Per-attempt
configuration identity remains diagnostic context; it is not proof, durable
delivery identity, or complete classification of runtime guarantees.
