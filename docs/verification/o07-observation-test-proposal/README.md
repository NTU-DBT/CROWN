# Excluded O07 runtime observation test proposal

This standalone test proposal targets only the O07 runtime-observation slice.
O07 remains `not_started`; this file and its source are preparatory and are not
runtime acceptance evidence. The native P07 tree and its execution inputs stay
frozen. The test is intended to compile against the staged overlay headers and
a complete runtime archive rebuilt from that same overlay revision.

## Coverage

`runtime_observation_test.cpp` uses the existing independent reference evaluator
and the baseline hand-trace fixture `Q(x) = R(x,y), S(y)`, with `R={(7,9)}` and
an insertion of `S(9)`. It checks the literal support work 40 and physical work
44 in off, counters, timed, and trace modes; exact support state, journals,
causes, and the `{7}` result; and both direct and insertion-replay physical
initialization. The support limit accepts 40 and rejects 39. The physical limit
accepts 44 and rejects 43, with both rejected paths preserving committed state.

The registry checks attempt scope, mandatory versus optional accounting,
explicit zero versus unavailable metrics, the separate 44 inclusive / 4
exclusive physical work values, and that support work 40 is included only once.
Metric values are asserted only when availability is `available`; a disabled
or unavailable entry may retain an uninterpreted numeric scratch payload.
A two-alias self-join checks a generalized join followed by projection. Its
head is `{y}` and both tree edges have separator `{y}`, so all three nodes are
in the maximal connex subtree under the verifier's separator-subset rule. Each
node has one visible `E(y=3)` key, giving three internal visible-key
transitions, while the projected query result still contains one row. These
internal transitions are not a count of emitted result rows. The
constraint-heavy rollback case starts with 100 unrelated `S(y)` rows and an
enforced unique constraint. Its coordinator prefix is derived from the existing
charges: 1 source change + 102 scanned rows + 1 validation + 1 alias + 1
derivation + 1 native crossing = 107. Limit 130 admits that prefix and fails
when the completed 40 support work is charged. The test requires both physical
work totals to be unavailable even though the charged coordinator prefix is
larger than support work. A second nested failure sets the support cap to 39
with ample physical budget.

A test-owned `noexcept` clock checks that off and counters perform zero optional
clock reads, timed and trace perform reads, and `trace_timings=false` disables
them while keeping mandatory counters. Trace checks cover sampled and
unsampled sequences, capacities 0, 1, and exact fill, truncation/drop counts,
abort terminals, and the numeric-only record representation. Session checks
retain the committed summary after draining and dropping the runtime.

Allocation counts are compared across modes around successful mutation,
cancellation, and work-limit failure. Runtime construction and diagnostic
snapshot/trace exports are outside those measurement windows. The comparisons
look for observation-added allocations; they do not assert that the runtime's
mandatory mutation machinery allocates nothing.

## Compile and link

Compile the test translation unit against overlay headers first. The test macro
must match the macro used for every runtime translation unit because it exposes
the injected-clock seam and affects the observation header ABI.

```sh
cd /home/userroot/Codex/CROWN
/usr/bin/c++ -O3 -DNDEBUG -std=c++23 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror \
  -DCROWN_RUNTIME_TESTING \
  -Idocs/verification/o07-runtime-proposal/overlay/include \
  -Iinclude -Itests/reference -isystem third_party \
  -c docs/verification/o07-observation-test-proposal/runtime_observation_test.cpp \
  -o /tmp/crown-o07-runtime-observation-test.o
```

Link only with the complete overlay runtime archive built from the same final
headers. The remaining archives below are the existing Release dependencies;
keep the runtime archive first for static-link resolution.

```sh
/usr/bin/c++ /tmp/crown-o07-runtime-observation-test.o \
  -o /tmp/crown-o07-runtime-observation-test \
  /tmp/crown-o07-runtime-overlay-compile/libcrown_runtime_o07_overlay.a \
  /home/userroot/Codex/CROWN/build/release/libcrown_reference.a \
  /home/userroot/Codex/CROWN/build/release/libcrown_plan.a \
  /home/userroot/Codex/CROWN/build/release/libcrown_sql.a \
  /home/userroot/Codex/CROWN/build/release/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a \
  /home/userroot/Codex/CROWN/build/release/libcrown_core.a
```

The source and archive were not executed as part of preparing this proposal.
The root agent owns the complete-overlay link and runtime run. Do not link the
new observation headers against the old native runtime archive.

## Acceptance still outside this slice

Passing this source would cover a focused runtime-observation proposal only. It
does not complete O07 acceptance for CLI or EXPLAIN schema behavior,
benchmarking, sanitizer coverage, or the remaining acceptance matrix, and it
does not change O07 status.

## Root-observed standalone run

The root executed the final matching proposal on 2026-11-07 (Asia/Shanghai).
Attempt 6 passes all seven named scenario groups, exit 0 in 0.032 seconds:
Q physical modes, direct support modes, work limits/rollback, trace capacity
and sampling, optional clock reads, generalized self-join projection, and
retained session summary after drain/drop. All 43 pinned native originals
remain unchanged. This is an excluded standalone proposal run, not native
O07 acceptance.

The accepted source SHA-256 is
`16e3d3f1ace5aa60018b9ad66850b7d0f732bddad83879b597983f8209863bad`;
its object is `4a172071cf65c89e3ba6dbc8bdeb6982df456ca615bef3a7def6ce0e1cd1a648`,
and binary is `34c90d0f0470e6440c7c649744999180c9c0f122c4c0c6ac565932b5f98f4915`.
The matching complete runtime archive SHA-256 is
`68d2ae303252527839cb515d0ed955e026850910d5a341f85ded654522e2ebd4`.
Raw logs and summaries are
`build/verification/o07-runtime-observation-proposal-attempt-6*`.

Attempts 1–5 are retained and are not acceptance. Corrections were an obsolete
registry description, an unsupported assumption that unavailable metric
payloads equal zero, and the independent self-join fixture and hand trace.
That fixture declares x/y/z, projects y, and has all three C* nodes because
both edge separators are `{y}`. Each E view gains one key: three internal
visible transitions, one generalized candidate, and one final SQL result.
The final assertions check those facts and each node's visible state; they
do not fit a total result count to the observed internal metric.

Root's separate complete nine-runtime-unit plus test build passes ASan/UBSan
and leak checking: test exit 0 in 0.566 seconds, 68.617 seconds including
compilation/linking. The run used `ASAN_OPTIONS=detect_leaks=1:halt_on_error=1`
and `UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1`; all ten translation units
compiled with strict warnings and both sanitizers. The sanitizer binary SHA-256
is `d66d4935cf0e144520ebff443817e7acc8f019fd43ce0b90e167cd1fa8044b32`.
Raw evidence is `build/verification/o07-runtime-observation-proposal-sanitize-*`;
session `72244` is terminal and closed. These results bind only the original
runtime overlay revision and source hashes above, not subsequent proposals.
Per-attempt resolved mode/configuration retention remains a known design
requirement; a current
runtime mode must not label an older retained summary. The EXPLAIN/CLI/schema,
mode-switch regression, saturated-count path, and full native matrix gates
remain open. O07 remains `not_started` until native integration.
