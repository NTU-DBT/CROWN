# C01 combined statistics — root preparation results, 2026-11-07

**Excluded preparation only; C01 remains not_started.** Root accepts the
[frozen combined package](c01-statistics-combined-proposal/README.md), manifest
`cb0ecb64935f80bf4915aa069de1bf01bcf1ea2f22a591f6f7408d405fcf4cfe`.
The accepted state and online ancestors remain unchanged.

All seven production and five testing executables pass strict C++23 O2 and
ASan+UBSan+leak checking. Production and CROWN_RUNTIME_TESTING objects are
separate in every executable. Root verifies the author strict commands,
objects/dependencies and binary identities, then independently rebuilds both
full sanitizer variants: 19 implementation/report-consumer units per variant,
seven production and five testing test/diagnostic units. Fifteen implementation
objects are linked; four frozen report compatibility consumers are compiled
but do not imply statistics-aware report behavior.

| Evidence per applicable configuration | Result |
| --- | --- |
| Joint owner/state/workload ordinary groups, both variants | 9 passed |
| Joint capture allocation sweep, both variants | 58 injected positions passed |
| Production owner ordinary / storage ordinary groups | 18 / 14 passed |
| Production owner-capture/copy sweeps | 3 sweeps, 100 positions passed |
| Production storage capture sweeps | 2 sweeps, 34 positions passed |
| Testing online integration groups | 10 passed |
| Testing online configure / update / mode faults | 6 / 278 / 16 positions passed |
| Testing numeric collector regressions | passed |

The same joint groups/fault positions repeat across variant/build combinations;
these are not additional independent scenarios merely because they run again.
The generalized diagnostic is separately identified as diagnostic output.

CombinedCapture is an immutable factory-produced owning handle. Before
publication it checks actual support owner, committed epoch, physical-plan
binding and pending agreement. Session capture uses one session guard. State
freshness and workload reset/configuration/segment stamps remain distinct.
Joint tests compare actual literal facts after successful/no-op/aborted work,
reset/mode changes, private/unread/window/session states, rebuild/drop and
historical report retention. No runtime rows, cursors or owner pointers are
retained by reports. One inherited fixture expression uses equivalent in-place
IgnoredColumn construction to resolve the optimized GCC warning; all golden
expectations remain unchanged.

[Root summary](../../build/verification/c01-statistics-combined-root-attempt-1.json)
records exact commands, binary/log hashes and 939 distinct unchanged input/artifact
files. Sanitized builds are
`/tmp/crown-c01-combined-root-production-sanitized-attempt-1/` and
`/tmp/crown-c01-combined-root-testing-sanitized-attempt-1/`.

Native code, CMake, schemas, CLI and old EXPLAIN v2 remain unchanged. The
[report integration inventory](c01-statistics-combined-proposal/explain-integration-inventory.md)
identifies why an explicitly versioned statistics-aware report is needed;
compiling old report consumers does not prove benchmark mode identification
with enabled C01. Native engine overhead, broader policy/scalar/constraint
coverage, native integration and the full C01 matrix/seal remain unfinished.
Component memory excludes allocator totals/rounding, engine state and caller
snapshots; no S05 or cost-ranking acceptance is claimed.
