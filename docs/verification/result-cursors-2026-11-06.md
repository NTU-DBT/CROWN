# D01 live current-result cursors, 2026-11-06

Input: uncommitted `master` based on
`e369a623517723b3be3ea3e9806779f3c591e7f9`. **D01 is implemented and verified.**
The full 78-card goal remains active: 22 verified, four in progress and 52 not
started. R05 integrated delta/output acceptance and D02 before/after fragment
cursors remain open.

Contracts: [result cursors](../result_cursors.md),
[conditional enumeration argument](../support_invariants.md),
[physical coordinator](../physical_runtime.md).
The [physical-runtime packet](physical-runtime-2026-11-06.md) and its manifest
describe the previous checkpoint.

## D01 requirement audit

| Requirement | Implementation and evidence |
| --- | --- |
| Lazy N-ary product over E | One frame per compiled C* step stores a live/bucket storage cursor and one borrowed selected tuple. The root uses `live()`; other steps project their actual selected parent's separator and use `bucket_cursor()`. An iterative nested-loop stack advances/backtracks without recursion. It never copies whole E relations/buckets, materializes a result set or stores output history. |
| Output assembly and no projection duplicates | Compiled numeric slots/equalities assemble an owning typed row. E membership is set-valued; positive support counts and hidden witnesses are not iterated. The C* coverage/connectivity argument makes the compatible assignment-to-head mapping injective. Three/eight-child fixtures produce actual 8/256-way products with hidden witnesses; disconnected, nested native-chain, reordered/repeated-head and root-projection cases match A04 without duplicates. |
| Correct separator source at depth | A native R(x,y)→S(y,z)→T(z,w) fixture uses parent step 1 for the final bucket, numeric field 1 for y/z projections, multiple completions and a reordered/repeated head. This checks non-root parent selection and suffix reset, beyond star products. |
| Empty, Boolean and constant handling | Empty current state yields no core rows; true/false constant routes and nullary atoms preserve core truth. SQL row mapping handles constants, repeats and ordering, including source-free and source-backed constant outputs. SQL EXISTS emits exactly one Boolean row, including false for an empty core. SQL typed layouts are shared per runtime across cursors/epochs and do not change serialized physical artifacts. |
| Committed epoch pinning | A reader count plus shared logical Impl lease blocks every mutation, including no-ops, while allowing ordinary reads and multiple cursors. Prepared writers reject cursor creation. End-null/cancel/destruction/failure releases one lease; remaining cursors still block writers. Active cursors survive facade moves/destruction; owning rows survive close and later updates. |
| Measured startup/result/termination | Startup charges one route check and frame initialization without data cursor advances. Successful rows, terminal-null actions, failures and the last action have separate counters; total and maximum successful-action work are checked. The unary hand trace has startup 2, one result 7 and termination 3 abstract units. Ordered lookup/field-width/allocation/mandatory cleanup costs remain explicit additional costs. |
| Failure and cancellation behavior | Persistent allocation injection covers cursor factory construction, first-row live/bucket opens, typed key projection, output assembly and long SQL constant copying. A later-third-row sweep forces suffix exhaustion, parent advancement and bucket reopening while retaining earlier owning rows. Failures close only the affected lease, preserve snapshots/handles/sequence, and allow a fresh same-epoch cursor. No-allocation cancel/destructor/move cleanup and facadeless lifetime paths are covered. |

The root implemented the cursor/read-lease/SQL layout path, reviewed the C*
argument and integrated the tests. Luna Max supplied semantic/fault tests and
the API contract. Test fixtures were corrected before acceptance to use valid
generalized scopes, the grounded normalized variable set, canonical empty
trees for constant-false routes and the full repeated core head. Internal
finite evidence does not replace the outstanding external G2/V02 review.

## Allocation sweep coverage

| Entry point/action | Injected failure positions |
| --- | ---: |
| SupportRuntime cursor factory | 2 |
| PhysicalRuntime SQL/default cursor factory on direct CQ | 2 |
| PhysicalRuntime core cursor factory | 2 |
| First next for each of those three APIs | 9 each |
| Later third next with bucket reopen | 5 |
| Normalized SQL cursor factory | 2 |
| SQL mapping next with long constant | 3 |

The exhaustive sweeps stop at their first successful allocation index and
check allocation-category coverage. Allocation failure remains armed during
the cursor's internal cleanup. Already returned rows remain owned and valid;
the query itself is never mutated by cursor traversal. Separate quota tests
cover factory and next-call work exhaustion and phase sums.

## Matrix and compatibility

All five configurations pass. All 43 earlier tests remain alongside
`result_cursor` and `result_cursor_exceptions`.

| Configuration | Result | CTest time |
| --- | --- | --- |
| GCC 13.3 Debug | 45/45 pass | 58.63 s |
| GCC 13.3 Release | 45/45 pass | 8.00 s |
| ASan/UBSan including parser C | 45/45 pass | 296.18 s |
| Clang 18.1.3 C/C++ Debug | 45/45 pass | 44.41 s |
| Fresh source-only Release | 45/45 pass | 8.07 s |

All recorded verification process handles are terminal and successful. The
fresh configure/build/test took 235.07 s and removed its temporary source/
build tree. Native warnings remain errors. Sanitizers include parser C,
enable leak detection and halt on ASan/UBSan errors.

The initial optimized GCC build diagnosed the temporary Boolean variant in
EXISTS assembly. Constructing it directly in the reserved output vector
resolved the warning without suppressing warnings. Every final run includes
that source change; the initial diagnostic is retained in the ignored logs.

Frozen physical-plan v1, support-trace v1 and support-report v2 schemas and
their codecs remain unchanged. The C++ cursor API adds no CLI stream protocol
or serialized checkpoint format. The CLI passes 25 checks/34 manual logical
states normally and under Python `-O`. Optional schema audit passes 18 schema
meta-checks, 26 normalized artifacts, 19 identity artifacts, 59 admission
artifacts, two layout/projection artifacts, 31 physical artifacts, three
support traces/reports and two rejected-update reports. The
[458-input source manifest](result-cursors-sources.sha256) covers source, build,
test, fixture, dependency and ordinary-contract inputs; all fingerprints pass.

```sh
cmake --preset debug
cmake --build --preset debug --parallel 2
ctest --preset debug --output-on-failure
cmake --preset release
cmake --build --preset release --parallel 2
ctest --preset release --output-on-failure
cmake --preset sanitize
cmake --build --preset sanitize --parallel 2
ctest --preset sanitize --output-on-failure
cmake -S . -B build/clang-debug
cmake --build build/clang-debug --parallel 2
ctest --test-dir build/clang-debug --output-on-failure
python3 -O tests/integration/support.py build/debug/crown .
python3 tools/verify_schemas.py build/debug/crown
python3 tools/verify_clean_build.py --configuration Release --parallel 2 --log build/verification/result-cursors-clean-source.log
sha256sum -c docs/verification/result-cursors-sources.sha256
```

Logs are ignored `build/verification/result-cursors-*.log`. Source manifests
exclude verification packets/manifests and mutable handoff/ledger files, as in
prior checkpoints.

## Limits and continuation

D01 reads one committed epoch under a busy lease; it is not a versioned
database and cannot read a prepared writer's tentative state. D02 must add
typed fixed assignments beyond parent separators and explicit before/after
fragment context. Affected-value pins alone do not freeze outside context.
Full-query delta production, witness/liveness proofs, output staging and
delivery remain D03–D06/O06 and R05 acceptance work.

The reference backend uses ordered indexes and owning variable-width values.
The counters are abstract operations, not complete allocator/CPU/byte costs or
a constant-delay certification. Closing a last facadeless cursor can destroy
the retained query state outside the cursor budget. S04/S05/D05 and external
release gates remain open; no R1 release or durable delivery is claimed.
