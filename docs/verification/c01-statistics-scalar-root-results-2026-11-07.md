# C01 typed scalar/constraint fixtures — root results, 2026-11-07

**Accepted excluded preparation; C01 remains `not_started`.** The frozen
[scalar proposal](c01-statistics-scalar-proposal/README.md), package manifest
`5fbbbc598fa724eda5042a680d3c34789a6c17a698c7ecbd102a4f7ad0008a48`,
passes all seven groups in strict C++23 O2 and ASan+UBSan/leak checking.
Root verifies its source/input/build-artifact manifests and executes both pinned
production consumers. The linked complete strict/sanitizer runtime closures were
already accepted; this check adds new consumer executions without rebuilding or
mixing those runtime variants.

Five literal scalar-order populations cover 42 distinct values: signed integer
endpoints, Boolean, date endpoints/leap days, canonical Decimal sign/scale and
38-digit boundaries, and byte strings with NUL/high bytes/long shared prefixes.
Expected heavy-key tie order comes from literal ascending ranks. Projection and
index NDV/multiplicity/top-K, repeated/empty fields, exact/one-under work caps,
zero-row exhaustion and retained facts after table clear all pass.

The mixed-type two-alias trace checks actual source, occurrence, generalized
candidate, S/P/E and visible-index populations against independently regrouped
source sets, plus every workload cell against independent arithmetic. The fixed
trace has 22 committed attempts, including no-ops and positive multiplicity
changes. The constrained trace has 14 committed attempts and seven aborted
attempts: five unique/FK violations, one fixed Decimal admission failure and one
explicit drained rollback. Same-owner canonical state, committed epoch and
committed cells survive each failure; attempt/abort metadata remains distinct.
Recovery at the unchanged next sequence, explicit pending-state unavailability,
source-stratum denominators and immutable historical captures after reset pass.

[Root evidence](../../build/verification/c01-statistics-scalar-root-attempt-1.json)
records binary/log hashes, exit statuses and 1010 unchanged distinct pins before
and after execution. The strict binary is
`92338c4ec53baf9e81456cab1472801416c8fa3c33827f28084f46701d2d7a67`;
the sanitizer binary is
`942386d18ee73e1927d040007e8938a144255fa67ed50d5f59340e634b11b456`.
Root session 96232 is terminal and closed. Native files and all predecessor
packages remain unchanged. This is neither native matrix acceptance nor timing,
serialization, total allocator memory or cost-model evidence.
