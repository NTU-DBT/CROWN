# C05 direct build checkpoint

Root alone runs the staged direct recipe. The author does not invoke compilers
after the workflow handoff, does not run any produced consumer/checker, and does
not invoke CMake/CTest/nm. The original six-unit GNU compile checkpoint in
`/tmp/crown-c05-selection-implementation-strict-1` remains historical as-of
evidence; it is not the final implementation closure.

The current recipe is `build-checkpoint-3.sh`. Its first argument must be a fresh
`/tmp/crown-c05-selection-implementation-*` directory; it refuses an existing
output. The second argument is `strict` or `sanitize`. It compiles, archives
and links only. Exact root argv for the initial full diagnostic pass is:

```sh
bash docs/verification/c05-selection-implementation-proposal/build-checkpoint-3.sh /tmp/crown-c05-selection-implementation-strict-3 strict
```

Root strict3 retained the eighteen unchanged passing TUs, three archives and
nine binaries. The only remaining compile issue was the binding consumer's
nested variant temporary. Its in-place construction correction has the targeted
root recipe below, with exact unchanged-source and prior-artifact guards:

```sh
bash docs/verification/c05-selection-implementation-proposal/build-checkpoint-4.sh /tmp/crown-c05-selection-implementation-strict-4
```

This fourth checkpoint rebuilds/links only selection_binding and copies the
verified matching artifacts. It preserves the full prior commands/statuses and
records the new commands plus before/after input and final artifact manifests.
Its one changed overlay source is selection_binding_test.cpp; API and all
implementation/support bytes are unchanged from strict3.

Root passed targeted4 and then all eight short strict consumers. A later
source-only correction quotes catalog name `R` in the normalized fault
fixture's SQL. Its targeted recipe is:

```sh
bash docs/verification/c05-selection-implementation-proposal/build-checkpoint-5.sh /tmp/crown-c05-selection-implementation-strict-5
```

This fifth checkpoint rebuilds/links only selection_normalized_exception. It
preserves the strict4-to-strict3 provenance chain, guards every unchanged
source/header/compiler/archive input, and records the fresh quoted-SQL source.
The public API, implementation, support helpers and other nine consumers are
unchanged. It executes no consumer. The exact source/checkpoint pins are in
`checkpoints/normalized-1/`; earlier checkpoints remain historical.

Root completed targeted5 and the later two ordinary fault executions. Their
exact receipt and observed totals are recorded in `EVIDENCE.md`; the recipe
itself still performs compilation/linking only.

A sanitizer checkpoint uses a distinct output and `sanitize`. It consumes only
the corresponding existing `build/sanitize` archives, never the Release C++
archives. A caller may choose a later numbered output after a recorded failed
compile, preserving all prior outputs and logs.

The full matching sanitizer command staged for root is:

```sh
bash docs/verification/c05-selection-implementation-proposal/build-checkpoint-3.sh /tmp/crown-c05-selection-implementation-sanitize-1 sanitize
```

This rebuilds all nineteen current translation units and links all ten
consumers; it does not reuse ordinary C05 objects from targeted4 or targeted5.
Root's terminal build receipt records all nineteen compiles, three archives
and ten links passing. Root then executed all ten matching sanitizer consumers
successfully; the terminal receipts in `EVIDENCE.md` distinguish that outcome
from build success alone.

The pure target has exactly five authored translation units: selection,
selection_budget, selection_binding, selection_payload and selection_cache.
It links the existing `crown_ranking` and its plan/sql/core dependencies. It uses
the existing private bounded P07/C02 binding and public payload walkers without
changing their bytes, behavior, ABI or authority. The two optional bridges use
the same runtime source compiled separately with no macro or
`CROWN_RUNTIME_TESTING=1`, then link only the corresponding ranking-runtime and
runtime archives. No C05 target requires a report archive.

The compile line is C++23 with `-Wall -Wextra -Wpedantic -Wconversion
-Wsign-conversion -Werror`. Strict uses `-O3 -UNDEBUG`. Sanitizer uses `-g
-UNDEBUG -fsanitize=address,undefined -fno-omit-frame-pointer`, with the matching
sanitizer link flags. Public overlay include paths precede native include paths.
The only third-party include root is the active native `third_party`, whose
patched nlohmann header is pinned separately. No original unpatched header or
cached alternate C++ closure is selected.

Each output records `commands.sh`, `status.tsv`, `targets.tsv`, per-command
stdout/stderr, per-TU `.d` dependencies, before/after input hashes, exact object/
archive/executable hashes and path inventories. Checkpoint 3 uses `-MD`, including
system dependencies; the active JSON header and compiler file are also explicit
guarded inputs. The preserved checkpoint-2 recipe used `-MMD`.
The recipe pins all current native include/src/test-support inputs, the native
compile database, matched link archives, the current C02 execution-freeze
receipt and C05 implementation authorization. The native libraries are read
only; authored archives exist solely in the fresh temporary output.

The ten executable names are `selection_pure_link`, `selection_contract`,
`selection_cache`, `selection_source`, `selection_current`, `selection_binding`,
`selection_resources`, `selection_census`, `selection_exception` and
`selection_normalized_exception`. All take no arguments and produce no output
files. The recipe never runs them. `selection_census` alone is a testing-runtime
consumer. The pure link consumer has no runtime/report link dependency.

Sanitizer execution requires root's matching environment, including leak
detection and immediate ASan/UBSan failure. No binary count, successful runtime
assertion or fault-position total is inferred from compile success. The final
packet pins the actual terminal checkpoints and correction history.
[Recorded outcomes](EVIDENCE.md) distinguish accepted excluded execution from
the staged recipes and still-pending native publication/matrix gates.
