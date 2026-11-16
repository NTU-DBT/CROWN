# Excluded O07 baseline hand-trace probe

This standalone probe records only the current native `SupportRuntime` and
`PhysicalRuntime` baseline. It does not change O07 status, implement a trace
registry, add off-mode acceptance, or claim trace completeness. The source is
limited to the checked-in public factories, epoch results, snapshots, journals,
and current-result cursors. It neither reads private runtime state nor uses
production accounting code to construct expected values.

The surrounding P07 source and execution inputs remain frozen. The only probe
files are `handtrace.cpp` and this README. Its binary is built in `/tmp`; do not
build through CMake, run a CTest target, or change existing targets for this
probe.

## Build and invoke

From the repository root, compile directly against the already-built Release
archives using the same archive order as
`build/release/CMakeFiles/crown_physical_runtime_test.dir/link.txt`:

```sh
cd /home/userroot/Codex/CROWN/build/release
/usr/bin/c++ -O3 -DNDEBUG -std=c++23 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror \
  -I../../include -I../../tests/reference -isystem ../../third_party \
  ../../docs/verification/o07-baseline-probe/handtrace.cpp \
  -o /tmp/crown-o07-baseline-handtrace \
  libcrown_runtime.a libcrown_reference.a libcrown_plan.a libcrown_sql.a \
  _deps/libpg_query/libpg_query-18.1.0/libpg_query.a libcrown_core.a
```

Then invoke `/tmp/crown-o07-baseline-handtrace` from any directory. The probe
does not use CMake or invoke itself during compilation.

## Independent fixture ledger

The first fixture is `Q(x) = R(x,y), S(y)`, with native R root and native S
child, FIFO propagation, and no source constraints. It initializes physical
`R={(7,9)}`, `S={}` through both direct and insertion-replay initialization,
then measures only physical `insert S(9)`. Its independent pre-update result
is empty. Its after-state is exactly `R={(7,9)}`, `S={(9)}`, root survivor
`(7,9)`, child survivor `(9)`, root `P(())=1`, child `P(9)=1`, root `E(7)=1`,
and answer `{(7)}`. The independent reference evaluator must report exactly
`+{(7)}`. A pending physical update's public before-view must still return an
empty result; its tentative after-view must match `{(7)}`. After commit, a
current-result cursor must return `(7)` exactly once.

Each measured Q support epoch is expected to report:

| Metric | Expected |
|---|---:|
| support work | 40 |
| whole-state copied rows/index memberships/metadata/child flags | 0 / 0 / 0 / 0 |
| native record visits | 2 |
| child-key probes/events | 0 / 1 |
| survivor/parent/visible key transitions | 2 / 2 / 1 |
| generalized candidates created/reclaimed | 0 / 0 |
| storage/metadata changes | 6 / 5 |
| saved child flags/journal records | 1 / 7 |
| events enqueued/applied; queue peak | 2 / 2; 1 |

The paired physical epoch is expected to report work 44, including support
work 40. Its four additional physical charges are one source change, one alias
visit, one derivation change, and one native crossing. Constraint counters
remain zero. Direct support follows the same logical before-state by committing
`R(7,9)` in sequence 1, then measuring only `S(9)` at sequence 2; that seed
epoch is not added to the measured epoch.

## Root's observed baseline

Root executed `/tmp/crown-o07-baseline-handtrace` against the existing Release
archives after this excluded probe was linked. It exited successfully in
0.004 seconds. Both physical initialization routes and the direct support
route match the literal Q ledger: support work 40, physical work 44, two
enqueued/applied events, two native visits and one result row. All exact
journal, flag, counter, before/after state and independent-reference result
checks in the probe pass. The separate reverse-index-visit metric remains
explicitly unavailable; the run does not claim it was measured.

The unary physical insert reports work 25 with support work 21; direct support
reports 21. Both duplicate paths report zero work, and erasure restores empty
result membership. Raw output and run metadata are retained under ignored
`build/verification/o07-baseline-handtrace.log` and
`build/verification/o07-baseline-handtrace-summary.json`.

These are observed existing-runtime baselines, not an O07 registry, timing-off,
sampling, EXPLAIN, full-mode or allocation-failure acceptance suite. O07 remains
`not_started`. No frozen P07 execution input changed.

The journal check expects native `S(9)` event 1, propagated child-key event 2
with cause 1, and all R journal changes under cause 2. Root R's saved child flag
changes false to true. This is a baseline hand-trace check, not a generalized
causal trace export or registry/off comparison.

The public `SupportMetrics` has `native_record_visits=2`, but it has no separate
`reverse_index_records_visited` field. The preflight paper ledger predicts one
reverse-index record visit. The probe prints that optional observation as
unavailable; it does not infer it by subtracting another counter.

The second fixture is native unary `U(x)`, initially empty. Insert `U(7)` must
produce support work 21 and physical work 25. A duplicate physical insert
commits the next sequence while changing no source, derivation, support state,
or answer; both epochs report zero work and no support journal/transitions. An
erase restores empty result membership. Direct support repeats the unary
insert/duplicate/erase path and checks the same 21/0 support work expectations.

## Counter boundaries

`SupportEpoch::metrics` and `PhysicalEpoch::input.metrics` are per returned
update epoch. The physical scenarios use `PhysicalRuntime::initialize` with
both R06 build methods and assert the subsequent update's literal 40/44
metrics independently of `initialization_metrics()`. Those R06 startup metrics
are not folded into the update. The direct logical API has no public bulk
initialization factory, so its R before-state is established by a separate
native update and only the following S epoch is measured.
