# C01 online owner hooks — root preparation results, 2026-11-07

**Excluded online slice only. C01 remains not_started; native O07 inputs are
unchanged.** Root accepts the [frozen online package](c01-statistics-online-proposal/README.md),
manifest SHA-256 `61281d60312f371930a6ddcb4c2c51570eb6d5c70264432715a7da0a3d247281`.

All three executables pass assertion-enabled strict C++23/full warnings and
ASan+UBSan+leak checking. Root checked the author's strict command/binary pins,
then independently rebuilt all 11 implementation and three test translation
units for the sanitized closure, linking matching instrumented plan/SQL/core/
parser dependencies. Both runs use CROWN_RUNTIME_TESTING consistently; no
production-runtime acceptance or native CMake registration is claimed.

| Configuration | Native online groups | Configure OOM positions | Same-owner update OOM positions | Mode OOM positions |
| --- | ---: | ---: | ---: | ---: |
| Strict, assertions enabled | 10 | 6 | 278 | 16 |
| ASan+UBSan+leaks | 10 | 6 | 278 | 16 |

The accepted collector regression executable also passes in both configurations.
Its nesting, bounds, histogram, saturation, reset/rotation and allocation-free
checks remain separate from the ten actual-runtime online groups. The same
300 fault positions are exercised per configuration; they are not 600 distinct
fault locations.

Actual owner tests cover literal R/S counts and fractions, physical projection
and alias predicates, lower-only unavailable physical denominators, repeated
touched events, sample retries/no-ops/abort/truncation, O07-off parity/no C01
clocks, initialization/rebuild, mode barriers, late spool rollback, final outer
publication, unread output, session/window/thread/stop/drop and delayed root
admission. Detailed claims and intentional remaining cases are in the package.

Root review corrected three issues before package freeze: sampled event means
now use exact completed-sample input counts from the same table/op stratum;
derived fractions become unavailable when clipped counters cannot establish a
valid ratio; and copy-like snapshot moves keep both immutable handles readable.
The adversarial sample includes selected/unselected work differences, no-ops,
aborts and truncation. Physical input shares retain their full-population
counts. No unbiased extrapolation or per-second arrival estimate is claimed.

[Root summary](../../build/verification/c01-statistics-online-root-attempt-1.json)
records exact commands, binary/log hashes and unchanged before/after pins:
738 checksum records resolving to 689 distinct files (some root-relative and
absolute records name the same input). Raw logs use the same prefix. Root
sanitized build: `/tmp/crown-c01-online-root-sanitized-attempt-1/`.

This slice has not been merged with explicit state capture or integrated into
native sources. Production/test target separation, EXPLAIN/schema/freshness
exports, broader combined policy/constraint/scalar fixtures, measured native
engine overhead and full C01/native matrix acceptance remain open. The earlier
component microbenchmark does not substitute for those measurements. Memory
is capacity-derived collector/routes payload with stated exclusions, not S05
total allocator/live bytes. O07's original full sanitizer matrix is independent.
