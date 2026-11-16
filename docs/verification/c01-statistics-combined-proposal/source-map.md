# Combined overlay source map

Every path below is relative to `overlay/` and maps to the identical repository-relative native destination after the integration gate. This package performs no native copy, CMake edit, report edit or registration. `source-files.sha256` pins the complete overlay. `native-additions.patch` shows the four shared header/source merges against the frozen native baseline.

| Path | Origin/change |
| --- | --- |
| `include/crown/storage/reference.hpp` | Accepted state package; unchanged |
| `src/storage/reference.cpp` | Accepted state package; unchanged bounded index cursor |
| `include/crown/runtime/statistics.hpp` | Accepted state package; unchanged |
| `src/runtime/statistics.cpp` | Accepted state package; unchanged |
| `include/crown/runtime/owner_statistics.hpp` | Accepted state package; unchanged read-only handle |
| `src/runtime/owner_statistics_detail.hpp` | Accepted state package; unchanged internal mutable builder |
| `src/runtime/owner_statistics.cpp` | Accepted state package; unchanged |
| `include/crown/runtime/workload_statistics.hpp` | Accepted online package; unchanged immutable snapshot |
| `src/runtime/statistics_collection.hpp` | Accepted online package; unchanged internal collector |
| `src/runtime/statistics_collection.cpp` | Accepted online package; unchanged |
| `src/runtime/workload_statistics_detail.hpp` | Accepted online package; unchanged internal owner state/routes |
| `src/runtime/workload_statistics.cpp` | Accepted online package; unchanged |
| `include/crown/runtime/support.hpp` | Both accepted API sets plus joint capture declaration |
| `src/runtime/support.cpp` | Complete accepted online body/hooks plus accepted state append/capture/freshness definitions |
| `include/crown/runtime/physical.hpp` | Both accepted API sets plus joint capture declaration |
| `src/runtime/physical.cpp` | Complete accepted online body/hooks plus accepted source/derivation capture definitions |
| `include/crown/runtime/delta.hpp` | Both accepted API sets plus joint capture declaration |
| `src/runtime/delta.cpp` | Complete accepted online body/hooks plus accepted state forwarding definitions |
| `include/crown/runtime/session.hpp` | Both accepted API sets plus guarded optional joint capture |
| `src/runtime/session.cpp` | Both accepted forwarding sets; new joint read uses one session guard |
| `include/crown/runtime/combined_statistics.hpp` | New private-constructor immutable joint owning handle |
| `src/runtime/combined_statistics.cpp` | New actual-owner factories, binding agreement check and owning payload |
| `tests/unit/owner_statistics_fixture.hpp` | Corrected accepted state fixture; unchanged |
| `tests/unit/owner_statistics_test.cpp` | All 18 accepted groups unchanged |
| `tests/unit/owner_statistics_exception_test.cpp` | All three accepted sweeps unchanged |
| `tests/unit/owner_statistics_generalized_diagnostic.cpp` | Accepted diagnostic unchanged |
| `tests/unit/statistics_capture_test.cpp` | All 14 accepted storage groups unchanged |
| `tests/unit/statistics_capture_exception_test.cpp` | Both accepted storage sweeps unchanged |
| `tests/unit/statistics_collection_test.cpp` | Accepted numeric collector assertions unchanged |
| `tests/unit/workload_statistics_fixture.hpp` | Equivalent in-place construction of the ignored-column variant; expected data/assertions unchanged |
| `tests/unit/workload_statistics_test.cpp` | All 10 accepted integration groups unchanged |
| `tests/unit/workload_statistics_exception_test.cpp` | Accepted configure/update/mode failure assertions unchanged |
| `tests/unit/combined_statistics_fixture.hpp` | New cross-stamp/literal-state comparison helpers |
| `tests/unit/combined_statistics_test.cpp` | New nine-group owner-driven composition test |
| `tests/unit/combined_statistics_exception_test.cpp` | New same-owner allocation sweep, including retained previous workload segment |

Both variants compile the five unchanged native runtime/IO consumers: `src/io/support.cpp`, `src/io/inspection.cpp`, `src/runtime/replay.cpp`, `src/runtime/window.cpp`, and `src/runtime/observation.cpp`. They also compile the four unchanged EXPLAIN consumers for header/type compatibility: `src/observability/explain.cpp`, `src/io/explain.cpp`, `src/io/run_context.cpp`, and `src/io/cursor_observation.cpp`. Those report objects are deliberately excluded from the test link commands; current v2 serialization is not integrated or changed.

All runtime objects are rebuilt separately for production and `CROWN_RUNTIME_TESTING`. Five future runtime source-list additions would be statistics, owner statistics, numeric collection, workload statistics and combined statistics. Native source lists and test targets remain untouched here. The internal builder/collector headers stay under `src/runtime`; public consumers receive only factory-produced owning handles.
