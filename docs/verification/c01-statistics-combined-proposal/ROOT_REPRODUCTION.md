# Root-only reproduction

These commands are for the root runner. The package author compiled and linked the strict variants but executed no test or diagnostic. Start in `/home/userroot/Codex/CROWN`. Check `INPUT_SHA256SUMS`, `PACKAGE_SHA256SUMS`, and the two accepted ancestor package manifests before execution. Neither source manifest incorporates a claim that the tests pass.

The build script accepts an output directory, `production` or `testing`, a dependency directory, and `strict` or `sanitized`. It only compiles and links. All outputs must use the `/tmp/crown-c01-combined-` prefix. It records expanded commands, dependency hashes, dependency files and command logs. Give each new attempt its own directory.

## Strict builds

```sh
bash docs/verification/c01-statistics-combined-proposal/build-only.sh /tmp/crown-c01-combined-root-production-strict production build/release strict
bash docs/verification/c01-statistics-combined-proposal/build-only.sh /tmp/crown-c01-combined-root-testing-strict testing build/release strict
```

The author-built equivalents already exist at `/tmp/crown-c01-combined-production` and `/tmp/crown-c01-combined-testing`. Their exact commands and artifact identities are in [build-evidence](build-evidence/production-artifacts.sha256) and [the testing manifest](build-evidence/testing-artifacts.sha256). Root can execute those pinned binaries directly instead of needlessly repeating completed strict compilation.

Run production and testing executables against their matching object variants. The joint tests deliberately exist in both variants; no executable mixes runtime macros.

```sh
for c01_test in combined_statistics_test combined_statistics_exception_test owner_statistics_test owner_statistics_exception_test statistics_capture_test statistics_capture_exception_test owner_statistics_generalized_diagnostic; do
  /tmp/crown-c01-combined-root-production-strict/"$c01_test"
done
for c01_test in combined_statistics_test combined_statistics_exception_test statistics_collection_test workload_statistics_test workload_statistics_exception_test; do
  /tmp/crown-c01-combined-root-testing-strict/"$c01_test"
done
```

Use `set -e` in a root wrapper and preserve each exit status and log. The diagnostic prints facts and is not a substitute for the ordinary assertions. The numeric collector regression is silent on success. Allocation sweeps print their observed injected-failure totals; do not copy predecessor totals into the combined result.

## Complete sanitizer variants

After root supplies and pins matching sanitized dependency archives, build both variants from their entire source closure. The example dependency root is the existing `build/sanitize`; use the actual verified root if different. Never link strict runtime objects into these executables.

```sh
bash docs/verification/c01-statistics-combined-proposal/build-only.sh /tmp/crown-c01-combined-root-production-sanitized production build/sanitize sanitized
bash docs/verification/c01-statistics-combined-proposal/build-only.sh /tmp/crown-c01-combined-root-testing-sanitized testing build/sanitize sanitized
for c01_test in combined_statistics_test combined_statistics_exception_test owner_statistics_test owner_statistics_exception_test statistics_capture_test statistics_capture_exception_test owner_statistics_generalized_diagnostic; do
  ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1 /tmp/crown-c01-combined-root-production-sanitized/"$c01_test"
done
for c01_test in combined_statistics_test combined_statistics_exception_test statistics_collection_test workload_statistics_test workload_statistics_exception_test; do
  ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1 /tmp/crown-c01-combined-root-testing-sanitized/"$c01_test"
done
```

Each mode recompiles 15 linked implementation/consumer translation units and four further unchanged report consumers. Production adds seven test/diagnostic translation units; testing adds five. `CROWN_RUNTIME_TESTING` is applied consistently to all translation units within the testing build. The `reference.cpp` override and all affected runtime objects precede the frozen archive group. Report compatibility objects are compiled but never linked into these tests. The script rebuilds no cached native library and invokes no CMake, CTest or schema checker.

Sanitized mode retains C++23 and all six warning/error flags, adds ASan, UBSan and frame pointers, and uses `-O1`. Strict mode uses `-O2 -g -UNDEBUG`. Compilation, ordinary execution, allocation sweeps and sanitizer results must be reported separately. Full native C01 policy matrices, serialization, measured overhead and project acceptance remain outside these standalone commands.
