# C01 storage capture proposal — excluded, not integrated

This package is a reviewable partial rollout (a). C01 remains NS. Only files under this package were written; frozen native sources, tests, CMake, schema and tools were not modified. No executable or checker was run by the author. Root owns execution and acceptance. O07 frozen native identity: 585 files, SHA-256 `9ca9005001bda9e56faa0951077e53fc106450d7350bf185cd62556a7af25d0a`; execution635 identity `8ae45108daed5530d67372c93b46bb198bf694a5c8bf429cb6905d4b367bbf12` (provided by root, not independently recomputed here).

## Source map

| Overlay path (relative to overlay/) | Native destination | Kind |
|---|---|---|
| include/crown/storage/reference.hpp | same path | mirror plus nested IndexKeyCursor/API |
| src/storage/reference.cpp | same path | mirror plus cursor implementation |
| include/crown/runtime/statistics.hpp | same path | new storage-scoped API |
| src/runtime/statistics.cpp | same path | new bounded collector |
| tests/unit/statistics_capture_test.cpp | same path | new standalone test executable |

`INPUT_SHA256SUMS` pins all native compilation inputs plus design inputs. `PACKAGE_SHA256SUMS` pins all package files except itself. CMake wiring is deliberately absent. Do not copy overlay files into native storage before O07 sealing and review.

## Implemented proposal scope

* ReferenceTable index-key cursor: one bounded startup allocation, borrowed key plus constant-time bucket size, weak ownership, no pins, no per-next allocation. Active journal access rejects; revision is checked before iterator access; destruction, index drop, real mutation and moved-from cursor reject. Duplicate no-op preserves validity. Table moves retain the same owner, matching live cursor behavior.
* Storage-only capture obtains actual owner/relation/revision and retains immutable layout/projection tokens. Revision explicitly does not claim committed epoch freshness. The API accepts no caller-manufactured completeness or epoch flags.
* Exact cardinality independently survives distribution exhaustion. Explicit requested ordered projections yield exact NDV, multiplicity histogram and deterministic top-K when complete. Existing indices yield exact nonempty-key degree distributions, NDV and top-K. Empty projection/population semantics are explicit in tests. Native int64/string/bool/date/Decimal semantics are preserved; string byte comparison is charged byte by byte and accepts embedded NUL/invalid UTF-8 without pretending to export JSON.
* A caller-owned Budget composes sequential captures without resetting caps. Work, visits, distinct insertions and cumulative accounted bytes are charged before corresponding copy/insertion. Length/field inspection and Decimal's bounded comparison/copy work are charged. Incomplete NDV/top-K remain disengaged; histograms are discarded. Only completed visit counts survive as clearly labeled prefix progress.
* Result keys own Row values; descriptors share immutable layout/projection metadata, never row storage. Allocation exceptions propagate; no owner mutation occurs, and existing reports remain intact. Scratch is local, so failure cannot publish a half-complete histogram/top-K.

## Deliberate limits and remaining gates

This is a storage primitive, not integrated SupportRuntime statistics. P/E counts are private `NodeState::parent/visible` maps in `src/runtime/support.cpp`; their membership tables do not encode support multiplicities. No P/E claim is made. Source/occurrence/generalized/S ownership labels, physical derivation multiplicities, non-connex E not-applicable status, committed epochs and owning plans require private owner append seams in later overlays. An S projection histogram can numerically reproduce support counts, but this package does not label arbitrary table projections P/E.

No transactional online hooks, counters, rates, sampling, reset/generation, mode/session/report/EXPLAIN/schema integration, clocks, cost model or CMake target is included. No OOM sweep, sanitizer run, runtime lifecycle test, performance benchmark or integration verification was performed. The 14 test groups are proposed checks, not passed evidence.

The collector uses a bounded linear list of distinct groups, avoiding an unmetered native map comparator and simplifying strong exception safety. Worst-case projection grouping is quadratic in admitted rows/keys, bounded by shared charged work. This is intentionally a small referenceable primitive, not an optimized estimator. Existing storage operations retain native structural complexity: live next is an amortized tree iterator step, get is a numeric handle lookup, index startup is a numeric index lookup. These are charged as logical actions; work units are not CPU instructions or nanoseconds. String comparison/copy byte work is separately charged.

`accounted_bytes` is a cumulative logical payload/allocation-request model, NOT measured allocator bytes or peak live memory: Row element storage, string bytes plus terminator, bounded Decimal payload, group payload plus two link pointers, histogram reserve requests and heavy vector payload are charged. Allocator rounding/metadata, implementation-specific spare capacity, shared pre-existing layout metadata, stack objects and the one fixed cursor startup allocation are excluded. It is an explicit bound on accounted components, not S05 allocator accounting. Observed maximum Row, histogram and heavy-vector capacities are exposed in shared Usage, including completed allocations in failed components. These maxima are element counts, not cumulative allocated bytes; reserve may provide more than requested portably. Histograms reserve before growth and charge each requested payload; total charges are conservative cumulative costs. A future accounting allocator is needed for exact allocation-request evidence. Callers may retain arbitrarily many returned reports; the budget does not account for caller copies.

The immutable compiled Projection is the bounded request; projection width is capped before traversal. The caller supplies already-owned descriptors; compilation cost is outside capture. There is no hidden index construction or full snapshot/keys/bucket materialization. The native data is single-threaded; concurrent mutation is unsupported just as for the underlying storage API.

## Root build and execution commands

From `/home/userroot/Codex/CROWN`, compile/link the proposal directly without CMake or native edits:

```sh
c++ -std=c++20 -Wall -Wextra -Werror -I docs/verification/c01-statistics-proposal/overlay/include -I include docs/verification/c01-statistics-proposal/overlay/src/runtime/statistics.cpp docs/verification/c01-statistics-proposal/overlay/src/storage/reference.cpp docs/verification/c01-statistics-proposal/overlay/tests/unit/statistics_capture_test.cpp src/storage/layout.cpp src/storage/arena.cpp src/ir/model.cpp src/ir/scalar.cpp src/ir/digest.cpp src/catalog/catalog.cpp -o /tmp/crown-c01-capture-test
/tmp/crown-c01-capture-test
```

Only root should execute the second command. An independent diagnostic build can add `-g -O1 -fsanitize=address,undefined -fno-omit-frame-pointer` and use `/tmp/crown-c01-capture-test-sanitized`.

Author evidence: all three overlay translation units compiled with C++20, `-Wall -Wextra -Werror`; direct link with the six frozen native implementation files succeeded. A final direct build after the byte-accounting guard refinement also succeeded. No binary was executed. Build success does not establish test success or C01 verification.

## Test inventory

Fourteen groups: literal cardinality/NDV/histogram; independent raw positional map reference/index top-K; nonempty empty projection; empty population; prefix row exhaustion; exact/one-under work cap and finalization byte exhaustion; shared cap across requests; no-op versus mutation cursor invalidation; private-journal rejection; owning result after clear; zero key/byte/width caps; native binary string/canonical Decimal/tie ordering/repeated reordered projection; wide-string work cap; index drop/destruction/move cursor rejection. Missing acceptance includes exact/one-over byte/key/width cap calibration, boolean/date dedicated fixtures, exhaustive exception injection, repeated randomized reference differential tests and real P/E/owner lifecycle wiring.

### Allocation-failure proposal supplement

`overlay/tests/unit/statistics_capture_exception_test.cpp` is a second new native-destination test file. Two sweeps cover explicit projection capture and index capture, including cursor startup, key copies, group nodes, histogram growth and final top-K allocation. Each sweep injects `std::bad_alloc` at every allocation ordinal until the first successful capture (bounded by 512 positions), using the same unchanged table/index owner. After each failure/success it checks original rows, revision, owner, invariants, prior owning report and a fresh recovery capture. The ordinary allocation overloads cover these non-overaligned types; this is not a general aligned-allocation fault framework. The executable reports its actual injected-position count when root runs it; no guessed count is recorded here.

Build and run (root only executes the second command):

```sh
c++ -std=c++20 -Wall -Wextra -Werror -I docs/verification/c01-statistics-proposal/overlay/include -I include docs/verification/c01-statistics-proposal/overlay/src/runtime/statistics.cpp docs/verification/c01-statistics-proposal/overlay/src/storage/reference.cpp docs/verification/c01-statistics-proposal/overlay/tests/unit/statistics_capture_exception_test.cpp src/storage/layout.cpp src/storage/arena.cpp src/ir/model.cpp src/ir/scalar.cpp src/ir/digest.cpp src/catalog/catalog.cpp -o /tmp/crown-c01-capture-exception-test
/tmp/crown-c01-capture-exception-test
```

The supplement compiles/links with the same warning policy. It has not been run. Total inventory: 14 ordinary test groups plus 2 allocation sweep groups, across 2 executables. Earlier missing exhaustive exception-injection coverage remains true for integrated runtime/online/session behavior; this supplement supplies explicit-capture proposals only.
