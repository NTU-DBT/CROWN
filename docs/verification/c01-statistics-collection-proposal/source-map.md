# Future source map (no native edits)

| Package file | Future placement | Scope |
|---|---|---|
| overlay/src/runtime/statistics_collection.hpp | src/runtime/statistics_collection.hpp | Internal numeric collection types only |
| overlay/src/runtime/statistics_collection.cpp | src/runtime/statistics_collection.cpp | Fixed descriptor admission, three slabs, transactions, saturation, reset/rotation |
| overlay/tests/unit/statistics_collection_test.cpp | tests/unit/statistics_collection_test.cpp | Standalone independent contract fixtures; no current target registration |

Future wiring must use the owner seams and exact locations recorded in `../c01-statistics-preflight-2026-11-07.md` section 5: physical prepare for one source input and no-op, route for occurrence observations, support transitions for before/after changes, child propagation for touched event degree, outer delta transaction for publication. The native observation root-ticket pattern is a reference seam only; this proposal does not modify O07.

The separate `../c01-statistics-proposal` package owns explicit data capture and public `crown::runtime::statistics` types. This package neither defines nor depends on those types. Both remain excluded until a separately reviewed integration. Requirements derive from Refactor.md section 9.2 and C01 plus the preflight; code is original, with no baseline implementation copied.
