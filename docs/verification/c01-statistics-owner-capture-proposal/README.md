# C01 owner state capture — excluded proposal

**C01 remains `not_started`. This is partial preparation, not native implementation or verification.** All repository writes are under this proposal directory. Native sources, headers, tests, CMake, schemas and tools remain frozen. No executable, checker, CMake or CTest was run by the author. Root owns execution and acceptance.

The preceding storage proposal remains unchanged at package-manifest SHA-256 `bcb41e25ab0e6287210fc694f5f84398c9fd86b7c258d0344747de5f4bf475fc`. Its accepted storage-only results do not establish results for this revised owner overlay. The independent online-collector proposal remains separate and unchanged at `0ad7771da11e2bb545ece48ef1f2ff5b93b62856b58279ed926b3ed50cecd5fd`. No online hook or collector is integrated here.

Root supplied these frozen identities: native585 `9ca9005001bda9e56faa0951077e53fc106450d7350bf185cd62556a7af25d0a`; execution635 `8ae45108daed5530d67372c93b46bb198bf694a5c8bf429cb6905d4b367bbf12`. The package's `INPUT_SHA256SUMS` pins the actual local source/header/design and Release-archive inputs. It is not a substitute for root's full frozen-input check. `PACKAGE_SHA256SUMS` pins every package file except itself.

## Source map

Paths in the first column are relative to `overlay/`. “Same path” means the eventual native destination after review and the O07 integration gate; this package performs no copying into native paths.

| Overlay file | Proposed native destination | Change |
| --- | --- | --- |
| `include/crown/storage/reference.hpp` | Same path | Accepted index-key cursor declaration, unchanged from prior storage proposal |
| `src/storage/reference.cpp` | Same path | Accepted cursor implementation, unchanged from prior storage proposal |
| `include/crown/runtime/statistics.hpp` | Same path | Storage API plus internal ordered-field and weighted-map collectors |
| `src/runtime/statistics.cpp` | Same path | Shared bounded scan, actual positive-weight grouping and charged finalization |
| `include/crown/runtime/owner_statistics.hpp` | Same path | New owning, read-only owner report and scope request API |
| `src/runtime/owner_statistics_detail.hpp` | Same path | New internal mutable builder; deliberately absent from public includes |
| `src/runtime/owner_statistics.cpp` | Same path | New shared owner budget, report construction and freshness comparison |
| `include/crown/runtime/support.hpp` | Same path | Public capture/freshness and private append declarations |
| `src/runtime/support.cpp` | Same path | Actual records/S tables and positive P/E maps, plus existing index requirements |
| `include/crown/runtime/physical.hpp` | Same path | Public capture/freshness declarations |
| `src/runtime/physical.cpp` | Same path | All physical source tables and actual occurrence derivation maps |
| `include/crown/runtime/delta.hpp` | Same path | Public capture/freshness declarations |
| `src/runtime/delta.cpp` | Same path | Actual-owner forwarding and private-state exclusion |
| `include/crown/runtime/session.hpp` | Same path | Optional capture/freshness declarations |
| `src/runtime/session.cpp` | Same path | Session guard, private-state exclusion and released-owner handling |
| `tests/unit/owner_statistics_fixture.hpp` | Same path | New literal independent map helpers |
| `tests/unit/owner_statistics_test.cpp` | Same path | New ordinary owner/lifecycle/budget tests |
| `tests/unit/owner_statistics_exception_test.cpp` | Same path | New capture and report-copy allocation sweeps |
| `tests/unit/statistics_capture_test.cpp` | Same path | Copied storage regression tests |
| `tests/unit/statistics_capture_exception_test.cpp` | Same path | Copied storage allocation sweeps |

## Report contract

`capture_statistics(request, limits)` is an explicit synchronous diagnostic read. A request contains at most 256 typed selections. Source scopes use physical catalog `TableId`, including unused tables; occurrence scopes use `OccurrenceId`; node scopes use `NodeId` plus `SupportRole`; index scopes use an existing `IndexRequirementId`. No statistics index is registered.

For source/records/S tables, absent `fields` requests cardinality only. Present fields request an exact ordered projection distribution, including the empty or repeated-field projection. A component retains the immutable **population layout** and its own ordered `FieldId` vector; projected keys are interpreted through those fields. No temporary `TupleLayout` or `Projection` is constructed, so source catalog/query binding metadata is preserved without copying arbitrarily large binding strings. `node_kind` distinguishes native records from generalized candidate unions.

For P/E and occurrences, absent fields requests the actual positive stored multiplicities. P/E reads `NodeState::parent` or `visible`, resolving each stored tuple ID to its owning key. Occurrences read `PhysicalRuntime::Impl::counts`. Their histograms count positive keys once per key, not once per source derivation. Supplying fields for these multiplicity scopes is rejected instead of silently substituting a membership-table projection. Non-connex E is `not_applicable`, with no zero-cardinality claim. Lower-only SupportRuntime marks source and occurrence facts `unavailable`.

Index components read the actual existing nonempty buckets. Their cardinality is the nonempty-key count; histogram multiplicity is bucket degree. The cursor yields a borrowed key and bucket size without `keys()`, `bucket()` or `snapshot()` materialization. Final report keys are owning copies. A reverse index over native records remains distinct from a similarly valued physical-source grouping.

Each complete distribution has exact NDV, a sorted `(multiplicity, positive-key-count)` histogram and top K sorted by multiplicity descending then exact native row order. The requested K is retained in `limits()`. Native string comparisons use charged unsigned raw-byte comparisons, including embedded NUL and invalid UTF-8; Decimal work uses the finite native domain. There is no NULL representation or export/encoding claim. An exact empty population has NDV zero, an empty histogram and a known empty top-K.

`OwnerCapture` has no default or caller-stamp constructor. Its stamp, owning plan, limits, usage and components have const accessors only. The fully defined mutable `OwnerBuilder` is confined to `src/runtime/owner_statistics_detail.hpp`; public headers only forward-declare it for friendship. Copy construction produces another owning report; copy assignment first constructs a complete replacement so allocation failure cannot pair a new stamp with old facts. Move operations do not allocate. Later EXPLAIN/C02 code should accept this factory-produced handle, not caller-declared `Component` or `OwnerStamp` values.

The stamp comes from the actual support owner, actual committed sequence, and support/physical layer. Delta and session forward the actual physical owner. `statistics_freshness(capture, max_event_lag)` reports current, within lag, stale, foreign owner, future sequence or scope mismatch. Lag is an explicit committed-event threshold; a committed no-op advances freshness. Equal data in another direct/replay/rebuilt runtime is still foreign. Optional component `storage_invalidation` records cursor owner/relation/revision only: rollback can advance revision without changing committed freshness.

Availability is independent of freshness. Pending support/physical preparation, delta processing or session-private work returns a current-stamped metadata-only `pending_private_state` report, with no tentative component reads. Committed unread delta output permits capture. A dropped session returns `nullopt`; prior reports keep their keys, plan and layouts. The API does not drain, mutate, reset or configure the runtime, and reads no clocks.

## Bounds and allocation model

One owner builder shares finite work, row-visit, distinct-key-insertion and cumulative accounted-component-byte budgets across all layers and selections. Counts are charged before corresponding payload copies/insertions. Field-vector and component reserve sizes use checked multiplication. Weighted collectors charge their actual fixed `Data` payload before allocating it. Numeric map/handle lookups and amortized iterator advances are logical actions, not CPU-instruction or time bounds. The fixed admission check of at most 256 selection widths precedes budgeted traversal.

Projected grouping uses the prior bounded linear list: worst-case grouping is quadratic in admitted rows/keys, stopped by the shared work limit. Raw byte copy/comparison work is charged by length/inspection, not as one constant action. Final sorting and histogram construction consume the same budget. On exhaustion, that distribution retains only explicitly named `visited` progress; its NDV/top-K are unknown and its histogram is empty. Exact cardinality metadata may remain available. Earlier complete components remain exact. If metadata admission itself exhausts, later selections may be absent; `requested_components()` makes this truncation explicit. Report availability becomes `budget_exhausted` if any component exhausted, while each component retains its own status.

`accounted_bytes` is a cumulative logical payload/request model, **not measured allocator bytes, peak live bytes, or S05 accounting**. It includes the report control object, requested component-vector payload, copied selection field-vector payload, weighted-builder control payload, Row element payload, string bytes plus terminator, finite Decimal payload, group payload plus two links, each histogram reserve request, and heavy-vector payload. Source-layout, projection and plan handles share existing immutable metadata. No new layout/projection descriptor construction occurs in owner scans. Observed maximum row/histogram/heavy-vector capacities are element counts and remain separate from the logical byte model.

Exclusions are caller request construction, caller report copies/retention, pre-existing plan/layout metadata, allocator control blocks/rounding, implementation spare capacity, fixed cursor startup allocation, engine-owned data/index/map storage, standard-library scratch/stack costs, and exception cleanup/deallocation work. Report and weighted control payload charges do not pretend to measure allocator bookkeeping. Standard allocation failure propagates from this explicit read; the runtime and previous reports remain unchanged. No update path invokes these allocating diagnostics.

## Proposed tests and evidence

The owner executable has 18 ordinary groups: literal actual-owner facts; independent positional grouping of every baseline distribution and A04 visible-answer comparison; direct/replay/rebuilt ownership; private prepare plus rollback revision/epoch separation; no-op freshness and explicit lag; committed support changes plus move; shared exhaustion preserving earlier exact facts; lower-only unavailable scopes; generalized candidates/S and non-connex E; private and committed-unread delta forwarding; session release; request/field/index/scope errors; source derivation changes without native membership changes and final deletion; exact/one-under work/row/key/byte limits; repeated/ordered/empty projections and retained request/K metadata; exact empty populations; paused/private/stopped sessions; and owning report lifetime after destruction.

The literal owner fixture intentionally adds an ignored physical column and a second derivation of `(1,7)` to the preflight's R/S example. Expected source, native, survivor, P/E and reverse-index maps are independently built from those literal input sets. No old unaccepted JSON packet or production statistics output serves as its oracle. P/E histogram sums are checked against S cardinality.

The owner allocation executable proposes two explicit-capture sweeps on the same unchanged physical/support owner, plus a report-copy assignment sweep. Each failure checks owner, committed sequence, canonical state, invariants, previous report and recovery capture. The copy sweep checks original stamp/facts after failed replacement. It covers ordinary allocations used by these non-overaligned types, not a universal aligned-allocation fault framework. The copied storage executables add 14 ordinary groups and two storage-capture sweeps. Actual execution counts and injected-position totals belong in root results after execution.

`BUILD_RESULTS.md` records author compile/link evidence. Compilation alone establishes neither test success nor C01 acceptance. Root must run the four executables and matching sanitizer builds. Remaining scope includes online owner hooks/transactional publication, configuration/reset, rate and sampling semantics, workload mode segmentation, EXPLAIN/schema integration, measured integrated overhead, wider randomized/alias/constraint/window fixtures, and the full native matrix. This proposal is an explicit-state slice only.

## Root reproduction

From `/home/userroot/Codex/CROWN`, `compile.sh` recompiles all twelve storage/runtime/IO translation units that participate in the overlay, plus all four test translation units. It uses `overlay/include` first and prepends the overridden `reference.cpp` object before frozen archives, so the old archive definition is not selected. No cached native library is rebuilt. It records exact expanded compiler commands, per-command logs and linked archive hashes under the requested unique `/tmp/crown-c01-owner-max-*` directory.

```sh
bash docs/verification/c01-statistics-owner-capture-proposal/compile.sh /tmp/crown-c01-owner-max-root-strict build/release strict
/tmp/crown-c01-owner-max-root-strict/owner_statistics_test
/tmp/crown-c01-owner-max-root-strict/owner_statistics_exception_test
/tmp/crown-c01-owner-max-root-strict/statistics_capture_test
/tmp/crown-c01-owner-max-root-strict/statistics_capture_exception_test
```

Only root executes the test commands. After root supplies matching sanitized dependency archives and verifies their identities:

```sh
bash docs/verification/c01-statistics-owner-capture-proposal/compile.sh /tmp/crown-c01-owner-max-root-sanitized build/sanitize sanitized
ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1 /tmp/crown-c01-owner-max-root-sanitized/owner_statistics_test
ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1 /tmp/crown-c01-owner-max-root-sanitized/owner_statistics_exception_test
ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1 /tmp/crown-c01-owner-max-root-sanitized/statistics_capture_test
ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1 /tmp/crown-c01-owner-max-root-sanitized/statistics_capture_exception_test
```

Both modes use C++23 and `-Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror`; sanitized mode adds ASan, UBSan and frame pointers. No CMake wiring is part of this package.
