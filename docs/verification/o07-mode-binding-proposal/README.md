# Excluded O07 per-attempt mode binding

O07 remains `not_started`. This is a separate, unapplied follow-up to the
frozen `o07-runtime-proposal` overlay. Native P07 inputs, that overlay, its
standalone tests, ordinary CMake/CLI/schema files and historical seals are
unchanged. Root owns every runtime execution and final integration decision.
This proposal performs direct compiler-only checks, never native builds/CTest.

## Defect and resulting behavior

The earlier overlay retains attempt/sequence metrics but only exposes the
runtime's current mode. A successful `DeltaRuntime::set_mode()` can therefore
leave an older last summary beside a different current profile. A reporter
must not label that older attempt with the new mode or guarantees.

This proposal introduces a privately constructed inline
`runtime::ObservationConfiguration`. `ObservationSnapshot::current_configuration`
is the current enabled observer configuration; `ObservationSummary::configuration`
is copied once at an outer delta attempt's begin. Nested support/physical hooks,
late output transfers/callbacks, cancellation and session drop never rewrite
that binding. A subsequent mode switch changes only current configuration.
Support-only/physical-only attempts and disabled observation have no delta
configuration (`std::nullopt`), rather than invented delta defaults.

The immutable value contains a complete exact copy of all `DeltaOptions`
fields, including nested `PhysicalRuntimeOptions`, `SupportOptions`,
`ObservationOptions`, cursor/view work ceilings and spool limits. It separately
records actual resolved mode, completion, live policy/view, query factor count,
support owner and configuration generation. All values are typed fixed-size
members; there is no JSON, digest, pointer identity, registry lookup, heap
payload, runtime reference or string conversion. `requested_options()` returns
an independent exact `DeltaOptions` value, preserving the originally requested
initial mode and automatic completion separately from current resolved choices.
Copies are trivially copyable and survive facade destruction/session drop.

The configuration is diagnostic identity, not proof, durable delivery identity,
query equivalence or authority to transplant metrics between owners. Owner and
generation are scoped to this process/runtime. The actual plan/evidence must
still come from the correctly bound report artifact. Initialization method,
input/window/queue configuration, per-attempt output retention, external codec
or sink identity and historical guarantee prose are not manufactured by this
value: they require separately declared reporting seams.

## Public read interface

Include `crown/runtime/delta.hpp` to use the full returned options type:

```cpp
const auto snapshot = runtime.observations();
if (snapshot.last && snapshot.last->configuration) {
  const auto& configuration = *snapshot.last->configuration;
  const auto requested = configuration.requested_options();
  const auto actual_mode = configuration.mode();
  const auto actual_completion = configuration.completion();
  const auto generation = configuration.generation();
  // Render these alongside this last attempt, not runtime.profile().
}
```

Other getters are `live_maintenance()`, `view()`, `support_owner()`,
`generation_saturated()`, `query_factors()` and static `format_version()` (1).
The constructor/capture operation is private to `DeltaRuntime`; callers can
copy a genuine diagnostic value but cannot create one from edited mode flags.
The snapshot itself remains a diagnostic aggregate, never checked authority.
Forward declarations of existing scoped enums and `DeltaOptions` keep the
observation header below the support/physical/delta dependency chain. Out-of-line
capture/reconstruction uses the full native types in observation.cpp.

## Generation and failure rules

Successful construction starts at generation zero only after initialization
bootstrap and restoration of ordinary options. Constructor-only bootstrap does
not count as an exposed mode switch or capture temporary build work ceilings.
A rebuilt runtime gets its own owner/generation zero, retaining the source's
original requested options and its actual current mode.

Only a successful later semantic mode change advances generation. Same-mode
requests, invalid/busy calls and failed live-image bootstrap preserve it. The
observation update follows the existing semantic commit and cannot allocate or
throw. No observation work/clock is added to the mandatory switch budget. Off
has no configuration/generation mutation or storage.

Generation increments through UINT64_MAX exactly; the next successful change
retains UINT64_MAX and sets `generation_saturated=true`. It never rejects or
changes a semantic mode switch. Once saturated, owner/generation cannot be
claimed as a unique configuration epoch, but the exact typed configuration
still identifies the actual options/mode for each summary. Earlier copied
summaries keep their previous exact generation and saturation state.

With `CROWN_RUNTIME_TESTING`, the exclusive test-only function
`detail::set_observation_initial_generation_for_testing(uint64_t)` seeds newly
constructed enabled observers; zero restores normal construction. It cannot
modify an existing owner. This permits actual mode-switch overflow tests
without 2^64 switches and without a production mutation setter. It is separate
from the existing optional clock hook and must be reset by the test owner.

## Patch, pinned baseline and compilation

Only three files are mirrored here: observation.hpp, observation.cpp and
delta.cpp. `mode-binding.patch` applies to the **excluded runtime overlay**,
not directly to the native source tree. `make_patch.py` verifies pinned inputs,
generates that patch and hashes local mirrors; it never applies anything.
`baseline-sha256.json` pins the 43 original native inputs, all ten frozen
runtime overlay inputs and its audit/build/hash metadata. Changed baselines
require explicit review/rebase; neither script silently regenerates the pins.

Public ObservationSnapshot/ObservationSummary layouts change. Rebuild all nine
runtime translation units and every consumer with this header; never link an
old runtime archive or old observation consumer. Include search order is this
proposal overlay, the pinned runtime overlay, then native include. The original
49-TU non-runtime include audit remains relevant: none consumes the changed
runtime headers; compiler dependency hashes additionally identify the actual
files used for this build. The test macro must match all runtime consumers.

```sh
python3 docs/verification/o07-mode-binding-proposal/build_proposal.py \
  /tmp/crown-o07-mode-binding-compile --testing --opt 0
```

The script compiles all eight existing runtime TUs plus observation.cpp, creates
`libcrown_runtime_o07_mode_binding.a`, and writes complete commands, compiler
logs/dependencies and hash evidence under the requested `/tmp` directory.
It validates the pinned baseline before and after compilation. It does not
configure CMake, run tests or execute any produced binary. The separate EXPLAIN
proposal must compile against these same headers if consuming the new layout.

## Required independent acceptance

Root/test-owner coverage must compare every requested option field against
independent nondefault values, including finite/absent ceilings, FIFO/LIFO,
legacy capture, all observation fields, automatic/resolved completion and
spool limits. Check initial maintenance/delta, empty/nonempty direct/replay
initialization, rebuilt owner/requested options, successful switches both ways,
no-op/invalid/busy/failing bootstrap, retained committed/aborted summaries,
late output/callback completion, captured snapshots and session stop/drop.
Use an initial generation near UINT64_MAX to verify exact maximum, overflow
saturation, subsequent changes and failed/no-op behavior. Compare mandatory
results/work/errors and optional allocations/clock calls with observation off.

The EXPLAIN adapter must render current configuration separately from each
summary's own binding, preserve null/unavailable lower-only bindings, and
avoid copying current runtime guarantee prose onto historical attempts. Current
and historical option identity is not full O07 execution-mode classification.
All full O07 EXPLAIN/CLI/tree/schema/matrix gates remain open.

## Recorded compiler-only evidence

All nine runtime translation units compile successfully with strict C++23
warning/error flags in both O0 + `CROWN_RUNTIME_TESTING` and production O3.
Full compiler commands and actual dependency hashes are preserved in
`compile-evidence-testing.json` and `compile-evidence-production.json`; the
short `compile-summary.json` records both complete replacement archive hashes.
All 57 pinned inputs matched before and after both builds: the original
43-file baseline, ten frozen overlay files and four overlay audit/build/hash
metadata files. No executable was run, and these checks establish compilation
and compatible header use only. Independent mode-switch/failure/retention
runtime tests and report adaptation remain root-owned pending gates.
