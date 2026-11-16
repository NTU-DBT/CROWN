# P05 sanitizer watchdog bridge

Status: the restricted policy bridge and complete sanitizer rerun pass.
All 89 tests pass at revision B in 5186.86 seconds, including normal
completion of all five allocation sweeps and leak-checking teardown.

The first final-source sanitizer run passed the semantic suite in648.54s.
Its monolithic allocation test completed423/952/1198/14140 failure positions,
then hit the external CTest3600-second watchdog during the7742-position
seven-atom repair sweep. CTest reported `***Timeout 3600.11 sec`. The process
did not finish its final sweep or normal leak-checking teardown. Remaining
tests were interrupted for a complete rerun; the attempt is not accepted.

Its original commands, logs, summary and Testing artifacts are preserved under
ignored `build/verification/residual-candidates-sanitize-attempt-1-watchdog/`.
The summary records the interruption and its original fingerprints. No failed
record or historical source seal was rewritten as a pass.

After independent Astra review, one line was added inside the existing
`if(CROWN_SANITIZERS)` test-policy block:

```cmake
set_tests_properties(planner_residual_exceptions PROPERTIES TIMEOUT 7200)
```

The existing3600-second default remains for other configurations. The test
assertions, all allocation positions, active-time/work/cell/record/depth
ceilings in the implementation, and ASan/UBSan/leak settings are unchanged.
Only this external sanitizer watchdog receives more time.

Revision A is the four successful89-test configurations: Debug1228.04s,
Release221.90s, Clang1037.14s and clean-source Release214.71s. Its native469
fingerprint is `69695cb7efc0a816fbce741cb311382521822d5d680f52a0c0dabf1068bc332a`;
its complete execution509 fingerprint is
`653e1a127f2cf2c601f6c6726fafa1b550254f6244e57629aefe035daad4d518`.

Revision B, the current source and sanitizer rerun, has native469 fingerprint
`20d00cca9705dfe8a1f9e5775865963bcc3b09f3f41bfe17a4d9d39f79c6d3ca`
and complete execution509 fingerprint
`c1a2d23edc5b605982b22db81ffbf706410e2d56614ad13af75d6aa9c4323d47`.

Per-file before/after inventories prove that only `CMakeLists.txt` changed;
the other508 execution inputs are byte-identical. Exact CMake snapshots and
a unified diff establish precisely the conditional addition above. Generated
compile commands are unchanged for Debug, Release, Clang and sanitizer builds.
Reconfigured CTest metadata preserves all89 test commands, environments and
properties for the three retained non-sanitizer build directories. Sanitizer
metadata changes only this test's TIMEOUT3600→7200.

The removed clean build's generated metadata is unavailable and was not
compared. Its unchanged helper configured Release without enabling sanitizers;
the unchanged default is OFF, so the added conditional is inactive there.

Concrete evidence is under ignored
`build/verification/residual-candidates-watchdog-preflight/`, with a machine
record at `build/verification/residual-candidates-watchdog-bridge.json`.
The independent matrix auditor accepts the bridge and all five completed
configurations. The final source auditor accepts the current 563-input seal,
claim scope and preserved historical manifest bytes. Both audits pass without
pending checks.

The resulting record must describe four successful configurations at A plus
successful sanitizer verification at B, connected by this restricted policy
change. It must not claim that all five full input fingerprints are identical.
No new native implementation, assertion removal, fault-position cap, compiler
warning suppression or weakened memory check forms part of this bridge.
