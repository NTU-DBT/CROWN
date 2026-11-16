# Future source map (no native edits)

| Package file | Future placement | Scope |
|---|---|---|
| `docs/verification/c01-statistics-collection-warning-proposal/overlay/src/runtime/statistics_collection.hpp` | `src/runtime/statistics_collection.hpp` | Internal numeric collection API; byte-identical to the frozen excluded proposal |
| `docs/verification/c01-statistics-collection-warning-proposal/overlay/src/runtime/statistics_collection.cpp` | `src/runtime/statistics_collection.cpp` | Same collector behavior, with one explicit safe bin-index conversion to satisfy `-Wsign-conversion` |
| `docs/verification/c01-statistics-collection-warning-proposal/overlay/tests/unit/statistics_collection_test.cpp` | `tests/unit/statistics_collection_test.cpp` | Standalone independent contract fixtures; byte-identical expectations and no current target registration |

The sole source diff from frozen input `docs/verification/c01-statistics-collection-proposal/overlay/src/runtime/statistics_collection.cpp` changes `bins[std::bit_width(v)]` to `bins[static_cast<std::size_t>(std::bit_width(v))]`. `std::bit_width(U64)` yields 0 through 64, so the conversion preserves the selected bin and safely matches the array index type. The original package manifest is pinned in this revision's `input-pins.sha256`.

Future wiring must use the owner seams and exact locations recorded in `../c01-statistics-preflight-2026-11-07.md` section 5: physical prepare for one source input and no-op, route for occurrence observations, support transitions for before/after changes, child propagation for touched event degree, outer delta transaction for publication. The native observation root-ticket pattern is a reference seam only; this proposal does not modify O07.

The separate `../c01-statistics-proposal` package owns explicit data capture and public `crown::runtime::statistics` types. This package neither defines nor depends on those types. Both remain excluded until a separately reviewed integration. Requirements derive from Refactor.md section 9.2 and C01 plus the preflight; code is original, with no baseline implementation copied.
