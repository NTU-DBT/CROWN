# O07 native fixture compatibility audit

Read-only audit of the native test fixtures against the frozen cursor-observation options in `o07-cursor-observation-proposal/overlay`.

## Finding

No native fixture explicitly combines `ObservationMode::off` with `capture_transitions = true`; no compatibility edits are needed. The frozen `ObservationOptions` default is `ObservationMode::timed`, and `SupportOptions::observation` defaults to `{}`. Therefore the existing aggregate initializers and option factories that set transition capture but omit observation mode retain `timed`. The rejected combination is an explicit `off` selection with transition capture enabled.

A scan of `tests/` found **27** C++ `capture_transitions = true` sites across **13** translation units. Tests contain no `ObservationOptions` construction/assignment and no `ObservationMode::off` reference. The integration Python fixture mentions the serialized legacy flag but does not explicitly select an observation mode. All source locations and inspected-file SHA-256 pins are in `readiness.json` and `baseline-sha256.json`.

## Scope and status

This directory contains audit records only: no test overlays, source edits, or patch. Existing native files and prior proposal directories were left unchanged by this audit. O07 remains **not_started** pending native integration. No compilation, test, CMake, CTest, or binary execution was performed. The separate integration and verification gates remain outstanding.
