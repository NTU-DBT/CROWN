# Live O07 report capture probe

This companion checks the `PlanExplanation::capture(runtime)` adapter against
real `DeltaRuntime` snapshots. It is a standalone excluded C++ emitter plus an
offline schema/semantic verifier. It does not change native sources, CMake,
CTest, or the frozen report/mode-binding packages. The proposal author does not
compile or execute it; root owns both steps.

The emitter accepts one already-produced P08 physical-plan artifact for a
one-table, one-string-column, one-atom query. It constructs a real runtime with
counters enabled, captures before an attempt, during a public pending epoch,
after commit, after a same-mode no-op, after a successful mode switch, and at
generation saturation. It retains the final `PlanExplanation` handle, destroys
the runtime, and only then serializes that detached report. It does not create
or edit an observation snapshot.

The mode generation test hook seeds the new runtime at `UINT64_MAX - 1`. The
two successful switches should produce `maintenance / UINT64_MAX / not
saturated`, then `delta / UINT64_MAX / saturated`. The committed attempt's
historical summary remains bound to `delta / UINT64_MAX - 1` through both
switches and runtime destruction. The verifier checks all supplied nested
options exactly, pending versus committed outcomes, no-op preservation,
current versus historical bindings, schema validity, and null numeric payloads
for disabled/unavailable metrics. The initial capture also confirms the
historical-summary field is null before any attempt.

## Compile and link

First build the frozen mode-binding report package using its existing direct
compile/link script. This emitter must use the same include layout, test macro,
report object files, and complete nine-unit replacement runtime archive. Never
link it against the old runtime archive. Output objects and executable belong
under the fresh `/tmp/crown-o07-explain-live-agent` directory. The strict
compile and link have completed there; no binary has been executed.

```sh
/usr/bin/c++ -std=c++23 -O0 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror \
  -DCROWN_RUNTIME_TESTING \
  -I /home/userroot/Codex/CROWN/docs/verification/o07-explain-proposal/overlay/include \
  -I /home/userroot/Codex/CROWN/docs/verification/o07-mode-binding-proposal/overlay/include \
  -I /home/userroot/Codex/CROWN/docs/verification/o07-runtime-proposal/overlay/include \
  -I /home/userroot/Codex/CROWN/include \
  -isystem /home/userroot/Codex/CROWN/third_party \
  -MMD -MF /tmp/crown-o07-explain-live-agent/runtime_report_emitter.d \
  -c /home/userroot/Codex/CROWN/docs/verification/o07-explain-test-proposal/runtime_report_emitter.cpp \
  -o /tmp/crown-o07-explain-live-agent/runtime_report_emitter.o

/usr/bin/c++ \
  /tmp/crown-o07-explain-live-agent/runtime_report_emitter.o \
  /tmp/crown-o07-explain-mode-binding/src_observability_explain.o \
  /tmp/crown-o07-explain-mode-binding/src_io_explain.o \
  -o /tmp/crown-o07-explain-live-agent/runtime_report_emitter \
  /tmp/crown-o07-mode-binding-compile/libcrown_runtime_o07_mode_binding.a \
  /home/userroot/Codex/CROWN/build/release/libcrown_plan.a \
  /home/userroot/Codex/CROWN/build/release/libcrown_sql.a \
  /home/userroot/Codex/CROWN/build/release/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a \
  /home/userroot/Codex/CROWN/build/release/libcrown_core.a
```

The pinned CLI compile evidence records the expected report object and archive
hashes. The verifier checks those archive hashes, the matching source
dependency manifest, both report objects, the emitter compiler depfile, the
schema, source, executable, and physical-plan input before running the emitter.

## Run the verifier

Use the native-lowered singleton plan from an independently recorded CLI run or
another P08 `lower-plan` result. For example, after the root smoke has created
the plan shown below:

```sh
python3 /home/userroot/Codex/CROWN/docs/verification/o07-explain-test-proposal/verify_runtime_reports.py \
  --emitter /tmp/crown-o07-explain-live-agent/runtime_report_emitter \
  --plan /home/userroot/Codex/CROWN/build/verification/o07-explain-root-smoke/plan.json \
  --depfile /tmp/crown-o07-explain-live-agent/runtime_report_emitter.d \
  --report-object /tmp/crown-o07-explain-mode-binding/src_observability_explain.o \
  --report-object /tmp/crown-o07-explain-mode-binding/src_io_explain.o \
  --repo /home/userroot/Codex/CROWN \
  --outputdir /tmp/crown-o07-runtime-report-verification
```

Python `jsonschema` 4 is required. The verifier uses the repository's
`RefResolver` pattern with local schema storage and rejects file/network
references outside the pinned schema. It writes exact emitter stdout/stderr,
the parsed reports, invocation details, input hashes, per-check results, and a
run summary beneath a unique output directory under `/tmp` or
`build/verification`.

## Scope

The emitter exercises a real pending update and a retained historical delta
summary through current-mode changes. It does not manufacture a lower-only
runtime snapshot, perform candidate-family admission checks, simulate proof
cross-binding, or run allocation-failure sweeps. The CLI harness separately
replays a native P06 certificate for exact query binding and wrong-binding/
height rejection. These checks do not replace the remaining root-owned O07
matrix and sanitizer gates.
