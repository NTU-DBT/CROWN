# Root-only report reproduction

The author compiled/linked the final strict variants and the independent legacy control. No producer, allocation test, runtime-only test, diagnostic, Python checker, CMake, CTest or `nm` command was executed. Root owns the following execution and acceptance. Start in `/home/userroot/Codex/CROWN` and verify the package/input manifests before running.

## Existing strict binaries

The pinned final directories are `/tmp/crown-c01-report-production-final`, `/tmp/crown-c01-report-testing-final`, and `/tmp/crown-c01-report-legacy-control`. The third directory uses frozen combined production runtime objects and original native report objects, with no report-proposal runtime object. It supplies the independent v2 byte reference.

```sh
set -e
/tmp/crown-c01-report-legacy-control/statistics_legacy_control /tmp/crown-c01-report-root-legacy-reference

/tmp/crown-c01-report-production-final/statistics_explain_test /tmp/crown-c01-report-root-production-fixtures
/tmp/crown-c01-report-production-final/statistics_explain_exception_test
/tmp/crown-c01-report-production-final/statistics_runtime_only_test
/tmp/crown-c01-report-production-final/combined_statistics_test
/tmp/crown-c01-report-production-final/statistics_legacy_control /tmp/crown-c01-report-root-production-control
cmp /tmp/crown-c01-report-root-legacy-reference/legacy-runtime.json /tmp/crown-c01-report-root-production-control/legacy-runtime.json
cmp /tmp/crown-c01-report-root-legacy-reference/legacy-session.json /tmp/crown-c01-report-root-production-control/legacy-session.json

/tmp/crown-c01-report-testing-final/statistics_explain_test /tmp/crown-c01-report-root-testing-fixtures
/tmp/crown-c01-report-testing-final/statistics_explain_exception_test
/tmp/crown-c01-report-testing-final/statistics_runtime_only_test
/tmp/crown-c01-report-testing-final/combined_statistics_test
/tmp/crown-c01-report-testing-final/workload_statistics_test
/tmp/crown-c01-report-testing-final/statistics_legacy_control /tmp/crown-c01-report-root-testing-control
cmp /tmp/crown-c01-report-root-legacy-reference/legacy-runtime.json /tmp/crown-c01-report-root-testing-control/legacy-runtime.json
cmp /tmp/crown-c01-report-root-legacy-reference/legacy-session.json /tmp/crown-c01-report-root-testing-control/legacy-session.json

PYTHONDONTWRITEBYTECODE=1 python3 docs/verification/c01-statistics-report-proposal/check_reports.py --schema docs/verification/c01-statistics-report-proposal/overlay/schemas/statistics-explain-v3.schema.json --fixtures /tmp/crown-c01-report-root-production-fixtures --legacy-baseline /tmp/crown-c01-report-root-legacy-reference --legacy-schema schemas/explain-report-v2.schema.json
PYTHONDONTWRITEBYTECODE=1 python3 docs/verification/c01-statistics-report-proposal/check_reports.py --schema docs/verification/c01-statistics-report-proposal/overlay/schemas/statistics-explain-v3.schema.json --fixtures /tmp/crown-c01-report-root-testing-fixtures --legacy-baseline /tmp/crown-c01-report-root-legacy-reference --legacy-schema schemas/explain-report-v2.schema.json --testing
```

Preserve per-command logs and statuses; stop at the first failure. The checker uses installed `jsonschema`, records its version, validates the new schema and every produced report, checks independent literal row maps and event counts, compares v2 bytes, and rejects mutations. It expects 31 ordinary v3 artifacts and 15 rejected mutations in production; testing adds one saturation artifact and two mutations. These are proposed counts, not observed successes. Each exception executable reports the actual injected-failure counts for four sweeps.

## Fresh strict compilation if required

```sh
bash docs/verification/c01-statistics-report-proposal/build-only.sh /tmp/crown-c01-report-root-production-strict production build/release strict
bash docs/verification/c01-statistics-report-proposal/build-only.sh /tmp/crown-c01-report-root-testing-strict testing build/release strict
bash docs/verification/c01-statistics-report-proposal/build-legacy-control.sh /tmp/crown-c01-report-root-legacy-control /tmp/crown-c01-combined-production
```

Use fresh output names for further attempts. The control script pins the 19 actual frozen combined objects it uses. If those objects have been removed, root can reproduce the accepted combined production build first, then supply that matching frozen directory. Do not substitute report-proposal runtime objects into the legacy control.

## Complete sanitizer closure

After root pins matching sanitized dependency archives, build both full variants. The example archive directory is the existing `build/sanitize`; supply the verified actual root if different.

```sh
bash docs/verification/c01-statistics-report-proposal/build-only.sh /tmp/crown-c01-report-root-production-sanitized production build/sanitize sanitized
bash docs/verification/c01-statistics-report-proposal/build-only.sh /tmp/crown-c01-report-root-testing-sanitized testing build/sanitize sanitized
```

Each build recompiles all 23 implementation/report units and all matching consumers. Sanitized mode uses C++23, all six warning/error flags, `-O1 -g -UNDEBUG -fsanitize=address,undefined -fno-omit-frame-pointer`. Testing defines `CROWN_RUNTIME_TESTING` for every runtime and report/consumer unit; production never does. The runtime-only executable links the 15-unit runtime closure, without any observability/report unit, in either variant.

```sh
set -e
export ASAN_OPTIONS=detect_leaks=1:halt_on_error=1
export UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1
for c01_variant in production testing; do
  c01_build=/tmp/crown-c01-report-root-$c01_variant-sanitized
  "$c01_build/statistics_explain_test" "/tmp/crown-c01-report-root-$c01_variant-sanitized-fixtures"
  "$c01_build/statistics_explain_exception_test"
  "$c01_build/statistics_runtime_only_test"
  "$c01_build/combined_statistics_test"
  "$c01_build/statistics_legacy_control" "/tmp/crown-c01-report-root-$c01_variant-sanitized-control"
  cmp /tmp/crown-c01-report-root-legacy-reference/legacy-runtime.json "/tmp/crown-c01-report-root-$c01_variant-sanitized-control/legacy-runtime.json"
  cmp /tmp/crown-c01-report-root-legacy-reference/legacy-session.json "/tmp/crown-c01-report-root-$c01_variant-sanitized-control/legacy-session.json"
done
/tmp/crown-c01-report-root-testing-sanitized/workload_statistics_test
unset ASAN_OPTIONS UBSAN_OPTIONS
PYTHONDONTWRITEBYTECODE=1 python3 docs/verification/c01-statistics-report-proposal/check_reports.py --schema docs/verification/c01-statistics-report-proposal/overlay/schemas/statistics-explain-v3.schema.json --fixtures /tmp/crown-c01-report-root-production-sanitized-fixtures --legacy-baseline /tmp/crown-c01-report-root-legacy-reference --legacy-schema schemas/explain-report-v2.schema.json
PYTHONDONTWRITEBYTECODE=1 python3 docs/verification/c01-statistics-report-proposal/check_reports.py --schema docs/verification/c01-statistics-report-proposal/overlay/schemas/statistics-explain-v3.schema.json --fixtures /tmp/crown-c01-report-root-testing-sanitized-fixtures --legacy-baseline /tmp/crown-c01-report-root-legacy-reference --legacy-schema schemas/explain-report-v2.schema.json --testing
```

The original v2 schema and all original native fixtures remain unmodified. The two explicit byte comparisons are targeted compatibility checks, not the full legacy or native matrix. Native CMake/CLI wiring and broader policy/overhead/matrix acceptance remain separate gates.
