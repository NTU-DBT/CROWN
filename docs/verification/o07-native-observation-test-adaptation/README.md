# Final-layer copies of prior accepted observation tests

This excluded root-owned adaptation leaves all prior frozen packages and native
files unchanged. It copies the accepted runtime, mode-binding and run-context
tests for compilation against the final full runtime layout.

Only contract changes are made: the now owning Snapshot/Summary must retain
noexcept copy construction/assignment rather than the obsolete trivial-copy
property; attempt fake-clock reads reconcile as delta-owned plus the disjoint
nested-cursor subset. The run-context test snapshots its immediate attempt
interval, checks later committed-result cursor reads separately against that
actual cursor, and requires the older attempt counts remain unchanged. Existing
off/counters zero-clock, deterministic work, result, persistent OOM, rollback,
trace and allocation parity gates remain intact. Default observation mode is
timed, preserving legacy timing; original native legacy capture fixtures need
no migration. Root attempt 2 passes all twenty groups against the final composed full runtime:
seven runtime-observation, seven mode-binding and six run-context groups. The
matching highest native-integration overlay sanitizer build also passes all
twenty groups, rebuilding nine runtime and six report units plus three tests
(18 translation units, 126.510s total), with 240 pinned inputs unchanged.

`comparison-to-accepted.patch` shows every source adaptation. Original accepted
sources are pinned in `baseline-sha256.json`. Attempt 1 is retained as a failed
compilation preparation (the new counter enum was transposed in the adaptation);
its source copies are under build/verification. No implementation source was
changed to fix that test identifier.

Evidence: `build/verification/o07-final-layer-adapted-tests-attempt-2.json` and
`build/verification/o07-final-sanitize-build-attempt-1.json`. Sessions 27953 and
24809 are terminal and closed. The preserved original packages are not edited.
Native CMake/CTest integration and the full five-configuration matrix remain
open, and O07 stays not started until native source integration.
