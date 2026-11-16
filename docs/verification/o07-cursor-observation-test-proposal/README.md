# O07 cursor observation — independent test proposal

This is a new excluded verification packet. It changes no native source, CMake
registration, frozen proposal, or current overlay. Root owns execution and any
integration decision. The C++ source and Python checker have **not been
executed**; the C++ consumer was strictly compiled and linked only.

## Frozen input identity

The consumer is pinned to cursor proposal package SHA-256
`5dcd916bda78bbe1bef6047a65b4a1fa7ef6ad405ee54877c8033b818d3b8259` from
`docs/verification/o07-cursor-observation-proposal/readiness.json`.

It uses the all-nine-translation-unit testing archive
`/tmp/crown-o07-cursor-observation-testing/libcrown_runtime_o07_cursor_observation.a`
(SHA-256
`4b4cb914e289172266ac25aeaafae0657872d02c07a92dafec6c8d682291159c`) and the
same package's report exporter object
`/tmp/crown-o07-cursor-observation-report-testing/0.o` (SHA-256
`22f3e58da968005327e5e74caee0c3f1785d1f662a0be06fb887160220a7ee33`). The
cursor package changes snapshot layouts and the registry count; do not use an
older runtime object or archive.

Include precedence is cursor observation → run context → mode binding →
runtime → EXPLAIN → native. Testing objects consistently use
`CROWN_RUNTIME_TESTING`. The reference archive supplies the independent A04
materializing evaluator; the remaining pinned archives supply planner, SQL,
PostgreSQL parser, and core dependencies.

| Link input | SHA-256 |
| --- | --- |
| `libcrown_runtime_o07_cursor_observation.a` | `4b4cb914e289172266ac25aeaafae0657872d02c07a92dafec6c8d682291159c` |
| cursor report exporter `0.o` | `22f3e58da968005327e5e74caee0c3f1785d1f662a0be06fb887160220a7ee33` |
| `libcrown_reference.a` | `035a204d7e00355b7f14e94255f8d77688f43a5688aabba898f6cedfd43f39f5` |
| `libcrown_plan.a` | `92a96fd0f01ade3862fb4fbbabe316337719f71eb43361f5eb6b250cdfe04d6a` |
| `libcrown_sql.a` | `6ba92b30615a1b35c7b499d1067647be49be47757b8ee58cb1098c65d275d26e` |
| `libpg_query.a` | `c254ea2e05708d5cf5e8526bad19d69d314d05a9af4f7a8b0be4b08e069e2174` |
| `libcrown_core.a` | `784b820ff9284ad75033552056fd2a81113f7eb54be5db56959f31ce778bcf9d` |

The standalone test object was compiled with strict C++23 conversion warnings
and linked into `/tmp/crown-o07-cursor-independent-link-20261107-a1/`. Its
SHA-256 values are recorded in the final paragraph. No generated executable has
been run.

## Cases in the C++ consumer

`cursor_observation_test.cpp` builds literal plans and checks actual cursor rows
against `crown::reference::evaluate`, including projected many-witness output,
empty and present nullary relations, constant true/false, SQL `EXISTS`, and
independent three- and eight-child products. It checks all five observation
configurations: off, counters, timed, trace without cursor timings, and trace
with cursor timings. Mandatory cursor work and result sets must match across
those modes.

The lifecycle cases retain copies across result production, cancel, destruction,
move construction, move replacement, facade destruction, and QuerySession
stop/drop. They cover multiple simultaneously live cursors, publication order,
startup cap failure, active-next work cap failure, exact and one-less work
ceilings with observation off, tentative-view rollback invalidation, invalid
and closed admission guards, persistent allocation failure in cursor startup
and `next`, and same-owner recovery. Clock cases check available exact zero,
backward-clock unavailability, clocks inside unsampled trace updates, active
delta reconciliation as `delta.clock_reads + cursor.nested_clock_reads`, and
that later current-result enumeration does not change a saved delta attempt.

Mode-bound cursor snapshots retain their begin-time options, owner, generation,
resolved completion and factor count across successful, failed and no-op mode
switches. The fixtures pin one C* factor for `Q(x) = R(x,y), S(y)` and three
factors for `G{y}` over `R(x,y), S(y,z)`, head `y`. A generation seam covers the
exact unsaturated maximum and diagnostic saturation without changing saved
older snapshots.

Gauge fixtures independently check base-table deduplication across aliases,
record/survivor/projected-parent-key/E-factor counts, generalized product leaf
factors, exact zero versus unavailable scope, pending-read rejection, insert,
delete, no-op and rollback, plus null unsupported total-result, memory and
durable metrics. Product results are checked against A04; their factor gauges
are not treated as full join cardinalities.

Every exported report comes from an actual runtime cursor observation or
`committed_state_gauges()` result. The C++ source checks exact encoded-byte
ceilings and N-1 rejection for every exported report. The Python companion
validates the resulting JSON against the literal v1 metric descriptors and
availability/null rules. It uses only the Python standard library and does not
recreate runtime snapshots.

## Compiler-only reproduction

The command below writes only to `/tmp`. The first command is compile-only; the
second is static link-only. Preserve this exact cursor-to-native include order
and link the exporter object before the matching complete testing runtime.

```sh
mkdir -p /tmp/crown-o07-cursor-independent-link
/usr/bin/c++ -std=c++23 -O0 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -DCROWN_RUNTIME_TESTING \
  -I /home/userroot/Codex/CROWN/docs/verification/o07-cursor-observation-proposal/overlay/include \
  -I /home/userroot/Codex/CROWN/docs/verification/o07-run-context-proposal/overlay/include \
  -I /home/userroot/Codex/CROWN/docs/verification/o07-mode-binding-proposal/overlay/include \
  -I /home/userroot/Codex/CROWN/docs/verification/o07-runtime-proposal/overlay/include \
  -I /home/userroot/Codex/CROWN/docs/verification/o07-explain-proposal/overlay/include \
  -I /home/userroot/Codex/CROWN/include \
  -I /home/userroot/Codex/CROWN/tests/reference \
  -isystem /home/userroot/Codex/CROWN/third_party \
  -MMD -MF /tmp/crown-o07-cursor-independent-link/cursor_observation_test.d \
  -c /home/userroot/Codex/CROWN/docs/verification/o07-cursor-observation-test-proposal/cursor_observation_test.cpp \
  -o /tmp/crown-o07-cursor-independent-link/cursor_observation_test.o
/usr/bin/c++ \
  /tmp/crown-o07-cursor-independent-link/cursor_observation_test.o \
  /tmp/crown-o07-cursor-observation-report-testing/0.o \
  /tmp/crown-o07-cursor-observation-testing/libcrown_runtime_o07_cursor_observation.a \
  /home/userroot/Codex/CROWN/build/release/libcrown_reference.a \
  /home/userroot/Codex/CROWN/build/release/libcrown_plan.a \
  /home/userroot/Codex/CROWN/build/release/libcrown_sql.a \
  /home/userroot/Codex/CROWN/build/release/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a \
  /home/userroot/Codex/CROWN/build/release/libcrown_core.a \
  -o /tmp/crown-o07-cursor-independent-link/cursor_observation_test
```

Root can run the linked test and then inspect its emitted actual snapshots with
the Python checker. Keep run products in `/tmp` or `build/verification`:

```sh
mkdir -p /tmp/crown-o07-cursor-independent-run
/tmp/crown-o07-cursor-independent-link-20261107-a1/cursor_observation_test \
  > /tmp/crown-o07-cursor-independent-run/runtime-output.json
python3 docs/verification/o07-cursor-observation-test-proposal/verify_cursor_observation_output.py \
  /tmp/crown-o07-cursor-independent-run/runtime-output.json
```

The suite is an independent focused probe, not full O07 acceptance. The global
allocator override injects persistent failure at the first allocation for
startup and `next`; it is not an exhaustive every-allocation-position sweep.
Cursor and gauge JSON contain numeric/enum descriptors rather than user text,
so this packet does not claim strict UTF-8 or control escaping coverage for
native strings. It does check exporter registry names, units, scopes, lifecycle
fields, availability, null payloads, and byte ceilings. The test source,
Python checker, and linked binary remain unexecuted by this author.

## Compiler artifacts

| Artifact | SHA-256 |
| --- | --- |
| `cursor_observation_test.cpp` | `ff8a0aefa3e6759535e95b70b5d29ce70a994bda13a656feaeabc4df0e290387` |
| `verify_cursor_observation_output.py` | `b25ee859ffba420a716f4a4061007d8e1a077ea7b903b295e9415fe44ad2cb47` |
| strict test object `cursor_observation_test.o` | `c455f2149a9b07bbf3f5ce6abdd5eaa2fda3ea825a052cda1a39441f5520a64b` |
| compiler dependency file `cursor_observation_test.d` | `fe66f750a64d6018acef262eda45d3227dcb641aa3da81d979310d9c62910416` |
| linked, unexecuted `cursor_observation_test` | `3467646edebb84b4faba6576f7ca56eb0f4c9afe2ae9569622cf1440496ded30` |
