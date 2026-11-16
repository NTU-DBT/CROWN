# `tests/integration/installed_meta_candidates.py` — block usage map

[Source](../../../../../tests/integration/installed_meta_candidates.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `d2cd437f11e99f9302e868b100232686f4b1ddb05402ce30cfc8c1ca4def49bf`. 62 lines partitioned into 3 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../tests/integration/installed_meta_candidates.py#L1) | Imports dependencies. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 11–58](../../../../../tests/integration/installed_meta_candidates.py#L11) | Callable definition: def main(): | calls ArgumentParser, in, add_argument, parse_args; returns result.stdout; failure when its buffered report is lost.; 4 loop sites; source comment (unverified): # The emitter must also return failure when its buffered report is lost. · [reviewed contract](#b0002) |
| [B0003 · 59–62](../../../../../tests/integration/installed_meta_candidates.py#L59) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |

## B0001

[Lines 1–10](../../../../../tests/integration/installed_meta_candidates.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:608280a414c5182965c62b542f7e9a2186f03f9bbcd0f5791fac194dc62e85ab
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define a Python integration driver for an installed, relocated public meta-candidate consumer. |
| inputs / outputs | The shebang/docstring and imports provide argparse, filesystem, JSON, subprocess, temporary-directory, and path utilities for the test. |
| invariants | The integration scope is package installation/relocation, public target consumption, sample execution, and output failure handling; it is not a source-level all-input correctness proof. |
| ownership | Imports and module documentation hold no persistent test state. |
| failure | Unavailable Python standard modules stop the script before setup. |
| cost | Python startup and module import only. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake) |

## B0002

[Lines 11–58](../../../../../tests/integration/installed_meta_candidates.py#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L11-L58:sha256:448cb16e3be23facf902af67e58425b34f062efa96bc43cffc6ab992c6d5b58e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install Crown into a temporary prefix, relocate it, build an isolated consumer, and validate the example's output and stream failure path. |
| inputs / outputs | Reads source/build/compiler and optional sanitizer arguments; installs to a staging prefix, renames it (including a spaced path), rejects build/testing artifacts in the package, configures a fresh CMake consumer from the installed example, builds it, checks compile_commands for C++23 and repository-path isolation, runs and parses JSON, validates finite family/status and checked height-one output, then redirects a second run to /dev/full and requires a nonzero exit. |
| invariants | The test establishes behavior only for this configured source/build/compiler and host. The output must report one rooted/undirected tree, exhausted finite mapped/normalized statuses, no heuristic and no global cost optimum; the candidate reports finite-proposals-v1 and checked_upper.height=1. /dev/full is a host-specific facility, not portable runtime behavior. |
| ownership | A TemporaryDirectory owns install, moved prefix, consumer source/build, and generated files; subprocesses are synchronous and outputs captured for diagnostics. |
| failure | A command failure, timeout, leaked testing/reference artifact, missing standard flag, repo-path leakage, JSON/status mismatch, or successful /dev/full write-path run raises a test failure with command/output context. |
| cost | Each subprocess has a 240-second timeout and the consumer build uses -j2; there are multiple install/configure/build/run phases, so this is not a total wall-clock or native planner cost bound. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [examples/meta-candidates/CMakeLists.txt](../../../../../examples/meta-candidates/CMakeLists.txt), [examples/meta-candidates/main.cpp](../../../../../examples/meta-candidates/main.cpp) |

## B0003

[Lines 59–62](../../../../../tests/integration/installed_meta_candidates.py#L59); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L59-L62:sha256:8a794f2c6b77bf5133b639a55d99eb34900b5c835e6fff07e6a511fd4502719a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run main() when the integration script is invoked directly. |
| inputs / outputs | Converts main's returned status into the Python process exit code. |
| invariants | This guard supports both direct script execution and importing main for another test harness. |
| ownership | The guard retains no state after process exit. |
| failure | Any exception from main propagates as a failing script; its returned status becomes the exit status. |
| cost | One call and process-status conversion. |
| Design | [tests/integration/installed_meta_candidates.py](../../../../../tests/integration/installed_meta_candidates.py) |
