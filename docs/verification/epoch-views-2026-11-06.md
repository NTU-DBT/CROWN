# D02 epoch-view foundation, 2026-11-06

Input: uncommitted `master` based on
`e369a623517723b3be3ea3e9806779f3c591e7f9`. The journal-backed visible-fragment
foundation is implemented and verified. **D02 remains in progress.** The
78-card ledger has 22 verified, five in progress and 51 not started.

Contract: [epoch views](../epoch_views.md). The
[D01 cursor packet](result-cursors-2026-11-06.md) and its 458-input manifest
describe the prior checkpoint.

## Scope and implementation audit

| Foundation requirement | Implementation and evidence |
| --- | --- |
| Typed assignments beyond the parent separator | `FixedAssignment` binds variable IDs to exact tagged values. Construction rejects unknown IDs, wrong types and conflicting duplicate bindings; equal duplicate bindings are accepted. A full-head unary witness with an empty root separator restricts output to that witness. Fully bound E steps use a primary lookup; partial bindings filter live/restored tuples. |
| Explicit old/new context without a database clone | `PendingEpoch::view(before/after)` shares an inverse patch over current support storage. Membership insertions are excluded from before walks; deletions are restored from journal-pinned tuples. Positive-to-positive support changes do not create visibility changes. One shared runtime read lease stabilizes unchanged context. Patch construction scans affected journal records, including all relation roles for future fragment work. |
| Owner-only tentative traversal | `ReferenceTable::Journal::live/bucket_cursor` lazily allocate an owner reader token. Ordinary public cursors still report busy during a journal. A committed owner cursor survives commit, a different active journal blocks it, real mutation invalidates its revision, and rollback marks its token aborted before inverse operations. Cursors retain weak storage ownership; the view group retains the logical runtime. |
| Visible C* subtrees | `VisibleFragment` selects a C* root and its C* descendants. The derived numeric enumeration program removes the outside parent key, retains internal parent buckets and outputs available visible variables in sorted order. Whole-query completion output retains the original repeated/reordered core head. SQL mapping remains the D01 API's responsibility. |
| Commit, rollback and staging boundary | Any external view/cursor seals its drained prefix. Further staging reports busy without aborting. Releasing all external references permits staging to resume; a fresh group reconstructs the whole epoch's before state. Commit allocates nothing and preserves views/cursors. Rollback closes the intrusive cursor list before undo, releases the group lease, and invalidates held views so the same sequence can be retried. |
| Owning outputs and independent leases | Returned tuples outlive views, facade moves and destruction. View copies share one lease; closing one does not release its peers. Exhausted/failed/cancelled cursors drop their group reference and keep metadata only. A held view still blocks writes even when every cursor is closed. |

The API deliberately rejects hidden-variable bindings with
`unsupported_fragment_binding` and fragment roots outside C* with
`invalid_fragment`. A visible binding absent from a selected subtree is
validated and ignored by that local subtree. These are unfinished D02 scope,
not an implementation of arbitrary relevant-variable/general-fragment
completion. The full D02 acceptance criteria in Refactor.md §7.2 remain open.

## Semantic and allocation coverage

`epoch_view` checks empty-separator witness restriction, binding validation,
three-level parent/child keys, core output order, sorted subtree output,
projection support collisions, insertion/deletion views, prefix sealing,
commit/rollback, copied handles, no-op/nullary/constant routes and owning value
lifetimes. Expected complete results use the independent A04 evaluator;
explicit subtree relations check the local fragment contract.
A three-level prepared leaf deletion removes visible E rows at the leaf and
both ancestors. Whole and bound child-root results on each side agree with
separate A04 database evaluations; a partially consumed before cursor keeps
the restored rows through commit. The inverse insertion checks exclusion of
new rows from the before side through the same parent-key buckets.

`epoch_view_exceptions` persistently injects global allocation failures at
view factories, completion factories and first/later cursor advances. It
checks exact state/handles/sequence, retries, prior owning rows and remaining
view/peer leases. Separate cases forbid allocations through commit, rollback,
destruction and move cleanup, including linked cursors and facade destruction.
Raw journal cursor cases check owner-token creation faults and invalidation
before iterator access.

The final GCC Debug sweep counts are:

| Action | Injected failure positions before first success |
| --- | ---: |
| Logical view factory, insertion before/after | 17 / 17 |
| Logical view factory, deletion before/after | 9 / 9 |
| Physical view factory, before/after | 4 / 4 |
| Completion factory, logical/physical | 34 / 34 |
| Insertion before first next / after later next | 9 / 5 |
| Deletion before later next / after first next | 5 / 8 |
| Committed view first/later next | 6 / 5 |
| Raw journal cursor factory | 2 |

The raw journal cursor's first `next()` also succeeds with all allocations
forbidden. Unlike a runtime cursor opening a bucket or emitting an owning
tuple, this handle-only storage advance needs no allocation. Rejections that
occur after the final matching result are checked in termination metrics.

The root implemented/audited the view, cursor overlay and storage reader
paths. Luna Max supplied semantic/fault tests and the contract; follow-up Luna
Max tasks corrected test API/fixture expectations and expanded deep-overlay
coverage. Internal finite tests do not replace external G2/V02 review.
An additional read-only Luna Max consistency review found no concrete
source/contract contradiction or clear correctness defect in the reviewed
view, lease, journal-reader and continuation sections.

## Matrix and compatibility

All 45 earlier tests remain alongside `epoch_view` and
`epoch_view_exceptions`. All five configurations pass:

| Configuration | Result | CTest time |
| --- | --- | --- |
| GCC 13.3 Debug | 47/47 pass | 63.38 s |
| GCC 13.3 Release | 47/47 pass | 8.29 s |
| ASan/UBSan including parser C | 47/47 pass | 302.31 s |
| Clang 18.1.3 C/C++ Debug | 47/47 pass | 47.42 s |
| Fresh source-only Release | 47/47 pass | 8.35 s |

All four in-place runs have matching before/after source fingerprints and
use the same source fingerprint. Every final matrix process is terminal and
successful. The fresh
configure/build/test took 243.25 s and removed its temporary source/build tree.
Native warnings remain errors; sanitizers include parser C with leak
detection and halt on ASan/UBSan errors. The
[461-input manifest](epoch-views-sources.sha256) covers build, source, tests,
fixtures, dependencies and ordinary contracts; all fingerprints pass. Earlier
packets/manifests remain historical and unchanged.

Frozen physical-plan v1, support-trace v1 and support-report v2 formats are
unchanged. These C++ APIs add no CLI streaming or serialized snapshot format.
CLI compatibility passes 25 checks/34 manual logical states under Python
`-O` using the rebuilt Release executable. The optional schema audit passes
18 schema meta-checks, 26 normalized artifacts, 19 identity artifacts, 59
admission artifacts, two layout/projection artifacts, 31 physical artifacts,
three support traces/reports and two rejected-update reports. The clean build
passed. Logs and per-configuration summaries are ignored
`build/verification/epoch-views-*` files. Source manifests exclude verification
packets/manifests and mutable handoff/ledger files, as in previous checkpoints.

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
python3 -O tests/integration/support.py build/release/crown .
python3 tools/verify_schemas.py build/release/crown
python3 tools/verify_clean_build.py --configuration Release --parallel 2 --log build/verification/epoch-views-clean-source.log
sha256sum -c docs/verification/epoch-views-sources.sha256
```

## Costs and continuation

View construction charges journal records, membership changes and patch
entries; its default cap is 1,000,000 abstract units. Options apply when the
shared group is first built; later views of the same prefix reuse it.
Per-cursor work limits independently account for binding, fragment, lookup,
overlay, output and traversal operations. Plan metadata, allocation, value
width and ordered comparisons have separate costs. Restored tuples are
scanned for each applicable bucket rather than indexed by every separator;
partial bindings can scan unrelated live rows. No D05 constant-delay or
memory-byte guarantee follows.

Next D02 work must support hidden-variable witness restrictions and remaining
fragments while retaining explicit old/new context. D03 witness partition and
liveness proofs, D04 exact full-query delta output, D05/D06 draining/delay and
O06 spool/sink integration remain open. R05 integrated output acceptance and
R06 bootstrap/rebuild are unfinished. No R0/R1 release or durable delivery is
claimed; the full goal stays active.
