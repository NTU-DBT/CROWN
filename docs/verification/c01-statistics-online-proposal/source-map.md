# Online proposal source map

All paths below are relative to `overlay/`, and map to the same native-relative destination only after root review and O07 sealing. The owner-capture proposal is separate; merge the additions to shared mirrors rather than overwriting one overlay with the other.

| Path | Change |
|---|---|
| `include/crown/runtime/workload_statistics.hpp` | New public configuration, typed scopes/roles, immutable owning numeric snapshot, sample-denominator scope and as-of stamp. |
| `src/runtime/workload_statistics_detail.hpp` | New internal State owned below Support, dense routing, nonthrowing owner hook interface. |
| `src/runtime/workload_statistics.cpp` | New actual-plan descriptor admission, configuration/reset, exact mode segment facts, owning snapshot factory and honest rational fractions. |
| `src/runtime/statistics_collection.hpp/.cpp` | Accepted collector extended for delayed root facts, honest logical scope, root complete-sample denominators, external route-capacity accounting and forced real segment rotation at saturation. `begin(desc,bool)` compatibility remains. |
| `include/crown/runtime/support.hpp` | New workload forward declarations, three public methods and private `workload_state()` forwarding; no constructor option change. |
| `src/runtime/support.cpp` | State in Impl; `Transaction::note` stages actual S/P/E values; `Transaction::child` records actual native bucket/event or generalized pre-probe presence; Support PendingEpoch nests/closes its ticket; appended public methods. |
| `include/crown/runtime/physical.hpp` | Three public methods and private `workload_state()` forwarding. |
| `src/runtime/physical.cpp` | Shared lower-owner State pointer; Physical Data admission/closure; actual adapter and derivation hooks; physical fact staged after membership test and before no-op early return; appended public methods. |
| `include/crown/runtime/delta.hpp` | Three public methods. |
| `src/runtime/delta.cpp` | Shared lower-owner State pointer; independent mode facts before O07 observer guard; root admission before staged Physical work; closure only after final success or all rollback; appended public methods. |
| `include/crown/runtime/session.hpp` | Workload header and guarded optional public forwarding. |
| `src/runtime/session.cpp` | Appended methods reuse actual Impl Guard and `has_private()`; metadata-only window pending snapshots are marked private; dropped owner returns disengaged. No retained slabs/copies are added to session tombstones. |
| `tests/unit/statistics_collection_test.cpp` | Byte-identical copy of the accepted warning-only collector test, compiled against the extended internal API. |
| `tests/unit/workload_statistics_fixture.hpp` | New isolated plans/helpers; no owner-capture dependency. |
| `tests/unit/workload_statistics_test.cpp` | New actual-owner integration assertions and independent raw-set/map event expectations. |
| `tests/unit/workload_statistics_exception_test.cpp` | New allocation-position/closure/recovery/mode fixtures; only root executes. |

Existing native `src/io/support.cpp`, `src/io/inspection.cpp`, `src/runtime/replay.cpp`, `src/runtime/window.cpp`, and `src/runtime/observation.cpp` are recompiled unchanged against the mirrored public headers. The direct build links only the pinned immutable `libcrown_plan.a`, `libcrown_sql.a`, `libcrown_core.a` and `libpg_query.a`; it never links an old runtime archive.

The new public header deliberately does not use `statistics.hpp` or `owner_statistics.hpp`. The separate capture package adds `capture_statistics`, `statistics_freshness`, and a private append seam, with no Impl field collision. Root must combine both sets of appended source methods/includes and header declarations, and supply the capture overlay's matching ReferenceTable cursor implementation when exercising both paths.

`input-pins.sha256` records the dependency closure emitted by the final compiler, the original four native header/source mirrors, planning documents and frozen predecessor manifests. `package.sha256` records all proposal source, documentation, patch and build-command files. No native mutation or execution identity was advanced by this package.
