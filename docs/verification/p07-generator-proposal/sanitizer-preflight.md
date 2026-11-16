# P07 proposal sanitizer preflight

**Excluded preflight only. P07 remains `not_started`.** These isolated
ASan/UBSan runs are not native P07 acceptance and do not complete or replace
the P07 gate. The root-owned P05 CTest matrix was in progress when this
preflight began; no CMake configuration, native build directory, CTest run, or
ordinary source/test input was changed here.

## Build and runtime settings

GCC 13.3.0 directly compiled the proposal implementations and probes as C++23
with ASan and UBSan, frame pointers, and strict warnings:

```text
-std=c++23 -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer
-Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wshadow -Werror
```

The instrumented objects and executables are under `/tmp/p07-sanitizer/`.
Executables link the existing `build/sanitize/libcrown_core.a`; the independent
comparison also links the existing `build/sanitize/libcrown_reference.a`.
No CMake configure/build or CTest command was used.

Every run used these settings without suppressions:

```text
ASAN_OPTIONS=detect_leaks=1:halt_on_error=1:abort_on_error=1
UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1
```

## Results

All five requested sanitizer probes completed successfully with exit status 0:

| Probe | Result |
| --- | --- |
| Generator fault probe | All 613 observed allocation positions; 51 ordered drafts, 26,411 steps, 1,400 topologies, 9 survivors, 357 records / 706 cells. Two persistent retries and same-owner recovery matched the full baseline. Depth, record, cell, ready-observation, retained-draft, and allocation-free cancellation checks passed. Runtime: 6.55 s. |
| Structural-key fault probe | All 17 observed allocation positions; two persistent retries, same-owner recovery, depth/cell resume passed. Runtime: 0.04 s. |
| Facade runtime probe | All 2,369 observed advance allocation positions, with no cap on the sweep; two persistent retries and same-owner recovery passed. Its proof, resource, cache, and lifetime checks also passed. Runtime: 79.29 s. |
| Witness probe | Non-normal unary witness replay, proof preservation, family-plus-seed, cache reuse, and retained handle checks passed. Runtime: 0.07 s. |
| Independent comparison | All 225 three-atom/two-variable valid-head cases exhausted. Across them: 516 distinct plans, 56,481 generator drafts, and 5,685 P02-accepted drafts. Every signature set matched and the key/reference relation was bijective. The five additional fixtures and incomplete resource-stop checks passed. Runtime: 31.94 s. |

The comparison inputs were the existing
`docs/verification/p07-case-proposal/queries/boolean_rst.cq.json` and
`docs/verification/p07-case-proposal/queries/self_join_equal_scope_three.cq.json`.
An initial invocation used the head-`x` variant of the Boolean query; the probe
rejected that mismatched fixture at its expected-plan-count check. That
invocation is retained in `build/verification/p07-sanitizer-preflight/` as
`comparison-wrong-input.log`. The corrected run passed all 225 cases. No
sanitizer runtime or environment failure was observed.

Compile, link, and run logs are in the ignored
`build/verification/p07-sanitizer-preflight/` directory. These checks exercise
proposal code with instrumented libraries; drafts remain untrusted and the
results make no minimum-height or candidate-authority claim. They are separate
from the native P07 acceptance suite and make no statement about completion of
the P05 matrix.
