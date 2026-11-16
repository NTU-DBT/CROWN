# Report overlay source map

Every path below is relative to `overlay/` and maps to the identical repository-relative native destination after integration. No native destination is modified by this package. Files marked unchanged retain the frozen combined proposal bytes. The Python checker and build/reproduction documents remain package-local verification artifacts.

| Overlay path / eventual native destination | Origin and change |
| --- | --- |
| `include/crown/io/statistics_explain.hpp` | New explicit byte/item export limits and complete-artifact result |
| `include/crown/observability/explain.hpp` | Native mirror; private statistics-context friendship/helper declarations |
| `include/crown/observability/statistics_explain.hpp` | New factory-only immutable v3 capture API and separate comparison domains |
| `include/crown/runtime/combined_statistics.hpp` | Frozen combined overlay; unchanged |
| `include/crown/runtime/delta.hpp` | Combined mirror plus nonallocating workload options accessor |
| `include/crown/runtime/owner_statistics.hpp` | Frozen combined overlay; unchanged |
| `include/crown/runtime/physical.hpp` | Frozen combined overlay; unchanged |
| `include/crown/runtime/session.hpp` | Combined mirror plus private-constructor runtime-only SessionStatisticsContext and guarded capture |
| `include/crown/runtime/statistics.hpp` | Frozen combined overlay; unchanged |
| `include/crown/runtime/support.hpp` | Frozen combined overlay; unchanged |
| `include/crown/runtime/workload_statistics.hpp` | Frozen combined overlay; unchanged |
| `include/crown/storage/reference.hpp` | Frozen combined overlay; unchanged |
| `schemas/statistics-explain-v3.schema.json` | New closed schema; all existing native schemas remain untouched |
| `src/io/statistics_explain.cpp` | New bounded JSON/human renderer with typed hex bytes and unknown/lower-bound semantics |
| `src/observability/explain.cpp` | Native mirror; enabled-C01 legacy capture rejection and private read without unbudgeted gauges |
| `src/observability/statistics_explain.cpp` | New actual-owner report composition, reconciliation and historical comparisons |
| `src/runtime/combined_statistics.cpp` | Frozen combined overlay; unchanged |
| `src/runtime/delta.cpp` | Combined mirror plus workload options accessor and testing-only actual-owner saturation forwarding |
| `src/runtime/owner_statistics.cpp` | Frozen combined overlay; unchanged |
| `src/runtime/owner_statistics_detail.hpp` | Frozen combined overlay; unchanged |
| `src/runtime/physical.cpp` | Frozen combined overlay; unchanged |
| `src/runtime/session.cpp` | Combined mirror plus fixed retained options and one-guard runtime-only context; no observability symbols |
| `src/runtime/statistics.cpp` | Frozen combined overlay; unchanged |
| `src/runtime/statistics_collection.cpp` | Frozen combined overlay; unchanged |
| `src/runtime/statistics_collection.hpp` | Combined internal collector plus testing-only clipped-counter seed |
| `src/runtime/support.cpp` | Frozen combined overlay; unchanged |
| `src/runtime/workload_statistics.cpp` | Frozen combined overlay; unchanged |
| `src/runtime/workload_statistics_detail.hpp` | Combined internal owner state plus fixed options accessor and testing-only seed |
| `src/storage/reference.cpp` | Frozen combined overlay; unchanged |
| `tests/support/runtime_probe.hpp` | Native private testing header mirror plus actual-owner saturation probe |
| `tests/unit/combined_statistics_exception_test.cpp` | Frozen combined overlay; unchanged |
| `tests/unit/combined_statistics_fixture.hpp` | Frozen combined overlay; unchanged |
| `tests/unit/combined_statistics_test.cpp` | Frozen combined overlay; unchanged |
| `tests/unit/owner_statistics_exception_test.cpp` | Frozen combined overlay; unchanged |
| `tests/unit/owner_statistics_fixture.hpp` | Frozen combined overlay; unchanged |
| `tests/unit/owner_statistics_generalized_diagnostic.cpp` | Frozen combined overlay; unchanged |
| `tests/unit/owner_statistics_test.cpp` | Frozen combined overlay; unchanged |
| `tests/unit/statistics_capture_exception_test.cpp` | Frozen combined overlay; unchanged |
| `tests/unit/statistics_capture_test.cpp` | Frozen combined overlay; unchanged |
| `tests/unit/statistics_collection_test.cpp` | Frozen combined overlay; unchanged |
| `tests/unit/statistics_explain_exception_test.cpp` | New same-owner report/capture/export/session allocation sweeps |
| `tests/unit/statistics_explain_test.cpp` | New 31 lifecycle/transport fixtures; one additional testing saturation fixture; exact export boundaries |
| `tests/unit/statistics_legacy_control.cpp` | New C01-off producer compiled independently against frozen combined/native report inputs |
| `tests/unit/statistics_report_fixture.hpp` | New independent fixture and artifact helpers |
| `tests/unit/statistics_runtime_only_test.cpp` | New runtime-only Session context consumer; links zero report/observability objects |
| `tests/unit/workload_statistics_exception_test.cpp` | Frozen combined overlay; unchanged |
| `tests/unit/workload_statistics_fixture.hpp` | Frozen combined overlay; unchanged |
| `tests/unit/workload_statistics_test.cpp` | Frozen combined overlay; unchanged |

The report builds recompile 23 implementation/consumer translation units independently per macro variant: the 15-unit combined runtime closure, the modified observability EXPLAIN implementation, two new statistics report units, and five unchanged native report consumers (`src/io/explain.cpp`, `src/io/run_context.cpp`, `src/io/cursor_observation.cpp`, `src/io/query_explain.cpp`, `src/observability/query_explain.cpp`). The runtime-only consumer links only the first 15, plus frozen core/plan/SQL/reference/parser archives. It links no observability or report IO object.

The separate legacy control reuses 19 pinned frozen combined production objects (15 runtime and four original report compatibility objects), then compiles the two unchanged query report units and the control consumer against the frozen combined/public native headers. It has no report-proposal runtime object or v3 header in its include path.

Future source-list work adds the two new statistics report units to the observability/report layer, whose dependency on runtime is already allowed. Runtime gains no observability dependency. The combined package's five earlier runtime additions still need their separate integration. No native CMake/source list, CLI dispatch, schema copy or installation target is changed here. All inherited assertions remain intact; the added testing saturation seam is absent from production builds.

