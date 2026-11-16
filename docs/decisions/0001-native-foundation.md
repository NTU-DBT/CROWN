# 0001: C++23 executable specification

Date: 2026-11-05. Status: accepted and foundation build verified.

Use C++23 and CMake for CROWN Next, following Refactor.md §3 and §16.2.
Keep all legacy source and experiment scripts in place. The new root build is
independent of Scala/Flink, DBToaster, and their environments. Do not implement
a second Rust engine.

Use owned typed values and standard containers in the specification. Compile
the independent evaluator as `crown_reference` from `tests/reference/`; it may
depend on validated CQ/catalog types but not on future support propagation,
tree construction, index, or cursor helpers. The reference CLI reports its
backend explicitly as `reference_recompute`.

Vendor nlohmann/json 3.12.0 with its MIT notice and published SHA256, avoiding
an implicit system dependency or network operation during core configuration.
The dependency lock records every external source actually used. Keep parser
syntax, binding, normalization and semantic admission separate; verifying
libpg_query in a spike does not implement the SQL frontend.

Toolchain baseline for this checkpoint: Linux, GCC 13 / libstdc++ 13, CMake
3.25+, Python 3.10+ for tests, Unix Makefiles. Debug, Release, and ASan+UBSan
presets use the same tests. Project code builds with `-Wall -Wextra
-Wpedantic -Wconversion -Wsign-conversion -Werror`; upstream includes are
system headers. An actual second compiler run must be recorded before A01 is
verified. The actual GCC/Clang and sanitizer runs are recorded in the
[foundation packet](../verification/foundation-2026-11-05.md). New toolchain
combinations must be tested before being called supported.

No legacy CROWN or DynaGox source is copied into the new engine. Their license
status and comparison environments belong in A02. New-code distribution
licensing remains an owner decision; no root license is invented here.
