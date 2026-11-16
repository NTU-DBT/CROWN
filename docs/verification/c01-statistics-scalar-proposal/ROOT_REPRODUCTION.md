# Root-only verification and execution

The author compiled and linked both final consumers but executed neither. Run from `/home/userroot/Codex/CROWN`. Keep logs/results outside this frozen proposal directory.

Verify source and artifact identities first:

```bash
sha256sum -c --quiet docs/verification/c01-statistics-scalar-proposal/PACKAGE_SHA256SUMS
sha256sum -c --quiet docs/verification/c01-statistics-scalar-proposal/INPUT_SHA256SUMS
sha256sum -c --quiet docs/verification/c01-statistics-scalar-proposal/source-files.sha256
sha256sum -c --quiet docs/verification/c01-statistics-scalar-proposal/build-evidence/strict-artifacts.sha256
sha256sum -c --quiet docs/verification/c01-statistics-scalar-proposal/build-evidence/sanitized-artifacts.sha256
```

Execute the strict and matching sanitizer consumers independently:

```bash
/tmp/crown-c01-scalar-production-strict-final/scalar_statistics_test
ASAN_OPTIONS=detect_leaks=1:abort_on_error=1 UBSAN_OPTIONS=print_stacktrace=1:halt_on_error=1 /tmp/crown-c01-scalar-production-sanitized-final/scalar_statistics_test
```

On success each prints `C01 typed scalar/constraint statistics: 7 groups passed` and exits zero. This line is proposed program behavior, not an observed author result. Any failure should retain the exact error, exit code, binary hash and source/package pins. Do not weaken literal expectations merely to obtain a pass; distinguish a fixture/oracle mistake from an implementation defect.

Optional fresh compile/link uses distinct output directories and the already pinned accepted production closures:

```bash
bash docs/verification/c01-statistics-scalar-proposal/build-only.sh strict /tmp/crown-c01-scalar-root-strict-attempt-1
bash docs/verification/c01-statistics-scalar-proposal/build-only.sh sanitized /tmp/crown-c01-scalar-root-sanitized-attempt-1
```

Those scripts never execute the resulting binaries. Root may execute the newly built consumers after recording their new artifact identities. Rebuilding a consumer does not recompile its linked 15-unit implementation closure; that closure's original full strict/sanitizer acceptance is recorded in the combined package's root results. This package is production-only and does not substitute for root's policy, replay, window, report, native integration or performance acceptance work.
