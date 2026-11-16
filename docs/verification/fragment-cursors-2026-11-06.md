# D02 pinned-assignment and witness-fragment cursors, 2026-11-06

Input: uncommitted `master` based on
`e369a623517723b3be3ea3e9806779f3c591e7f9`. **D02 is implemented and verified.**
The [47-test epoch-view foundation](epoch-views-2026-11-06.md) and its
461-input manifest describe the previous checkpoint, not the current source.
The full 78-card implementation goal remains active: 23 verified, four in
progress and 51 not started. D03 projected delta proof/liveness and R05
integrated output acceptance remain open.

Contract: [epoch views and fragments](../epoch_views.md).

## Requirement and correctness audit

| D02 requirement | Implementation and acceptance evidence |
| --- | --- |
| Typed partial assignment beyond the parent separator | Both completion APIs validate every variable ID, exact scalar type and duplicate compatibility at construction. Hidden variables are accepted. A fully bound native root, including a root with an empty separator, uses its actual fields rather than an empty parent key. Projected candidates still retain every fixed restriction through their witness probe. |
| Projected completions with hidden restrictions | The outer walk enumerates distinct compatible E assignments as in D01. When hidden bindings matter, an iterative search over the complete local survivor subtree checks existence under all fixed values and the selected visible values. Repeated or hidden witnesses cannot duplicate an outer projected candidate. No full result relation or output-history set is built. |
| Subtrees and general fragments | `witnesses` traverses a complete subtree rooted at any physical node, including outside C*, or an exact set of survivor factors. It emits all selected variables in sorted ID order, including hidden variables. Nonadjacent/disconnected selected factors enforce their shared variables numerically. The empty factor set is the nullary identity. Unknown/repeated nodes and simultaneous root/factor-set selection reject at construction. |
| Explicit old/new state and deleted-row lifetime | The existing group has inverse membership patches for every relation role, including S. Before-side walks restore deleted rows through pins and exclude inserted IDs, while one lease stabilizes unchanged context. Full witness cursors and projected probes share the intrusive rollback list: rollback closes both main and probe frames before undo; commit preserves views and partially consumed cursors. |

The maintained S invariant means a node row has a completion in each child
subtree. In a complete subtree, checking these rows and shared variables
reconstructs the subquery witnesses. For projected completion, a fixed visible
assignment determines the outer E tuples uniquely; the survivor probe is a
Boolean filter, not an additional output product. Running intersection makes
different child witnesses independent once a parent row is fixed. The
iterative probe therefore rejects a parent row when a child has no witness,
without revisiting successful sibling choices.

For an exact factor set, a complete assignment to its variable union uniquely
determines a row in each selected set-valued factor. Thus the full-assignment
join emits no duplicate tuples, even across omitted ancestors. Such a fragment
joins maintained S factors: omitted descendants can still supply their
original unrestricted existence support through S. It is not a query over
only the selected raw native atoms. A binding absent from the selected local
fragment is validated and has no effect there. Projected whole-query
completion retains every relevant query-variable restriction.

The private walk programs do not change frozen physical-plan v1. Partial S
constraints scan live/restored rows because S has no new secondary index;
fully determined tuples use primary lookups combining fixed values, selected
earlier factors, or the outer visible candidate. Costs are measured and capped,
without claiming D05 constant delay or a byte budget.

## Targeted tests and allocation evidence

The semantic test passes hidden-value match/miss, projection collisions,
local versus whole-query context, physical subtrees outside C*, repeated
hidden values across a three-level chain, arbitrary/nonadjacent factor joins,
three/eight-child products, typed values, nullary/constants and owning
lifetimes. A04 independently evaluates full assignments and their bound
projections, including local subtree queries. Hand S-factor joins distinguish
exact factor selection from raw-atom subset semantics.

A physical self-join erasure updates both aliases. The unbound projected
answer remains while full assignments shrink from four to one and a specific
hidden binding loses its witness. Both sides agree with A04, demonstrating S
overlays even when projected E membership does not change. Deletion cursors
also continue across commit, and rollback closes/invalidates both API kinds.

The new persistent `fragment_cursor_exceptions` test and the updated
`epoch_view_exceptions` test both pass targeted GCC Debug runs. Their
new-path sweep counts are:

| Action | Failure positions before first success |
| --- | ---: |
| Current logical witness factory | 56 |
| Current physical witness factory | 56 |
| Pending before/after witness factory | 56 / 56 |
| Hidden-bound projected completion factory | 71 |
| Before first/later witness next | 6 / 3 |
| After first/later witness next | 6 / 4 |

The sweeps preserve state/handles/sequence, prior owning rows and a peer
cursor's lease. Allocation failure stays armed during cleanup. Separate paths
forbid allocation through commit, rollback, destruction and move assignment
with live cursors. Work limits check factory and traversal failures; counters
include `witness_probes`, `witness_rows` and `join_rejections` in all phases.

The root owns implementation/integration. Luna Max supplied the semantic and
fault tests, contract updates and read-only contract/source reviews. The
source review found no concrete correctness/lifetime defect in the inspected
tree probe, lookup, factor selection or cleanup paths. This internal review
does not replace the outstanding external G2/V02 review.

## Matrix and continuation

All 47 earlier tests remain alongside `fragment_cursor` and
`fragment_cursor_exceptions`. All five configurations pass:

| Configuration | Result | CTest time |
| --- | --- | --- |
| GCC 13.3 Debug | 49/49 pass | 60.53 s |
| GCC 13.3 Release | 49/49 pass | 8.25 s |
| ASan/UBSan including parser C | 49/49 pass | 311.74 s |
| Clang 18.1.3 C/C++ Debug | 49/49 pass | 46.77 s |
| Fresh source-only Release | 49/49 pass | 8.35 s |

All four in-place runs have matching before/after source fingerprints and use
the same source fingerprint. Every final matrix process is terminal and
successful. The fresh configure/build/test took 247.84 s and removed its
temporary source/build tree. Native warnings remain errors; sanitizers include
parser C with leak detection and halt on ASan/UBSan errors.

Frozen physical-plan v1, support-trace v1 and support-report v2 schemas and
codecs remain unchanged. No CLI streaming or serialized snapshot format was
added. The CLI passes 25 checks/34 manual states under Python `-O`; the
optional schema audit passes 18 schema meta-checks, 26 normalized artifacts,
19 identity artifacts, 59 admission artifacts, two layout/projection artifacts,
31 physical artifacts, three support traces/reports and two rejected-update
reports. Logs and per-configuration summaries are ignored
`build/verification/fragment-cursors-*` files.

The [463-input manifest](fragment-cursors-sources.sha256) covers build, source,
tests, fixtures, dependencies and ordinary contracts; all fingerprints pass.
Verification packets/manifests and mutable handoff/ledger files are excluded
as in previous checkpoints. Earlier packets/manifests remain historical.

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
python3 tools/verify_clean_build.py --configuration Release --parallel 2 --log build/verification/fragment-cursors-clean-source.log
sha256sum -c docs/verification/fragment-cursors-sources.sha256
```

D03 must separately specify and audit projected delta witness partition and
liveness. No exact full-query delta, spool/sink acceptance, draining protocol,
durable recovery, D05 complexity certification or R1 release is claimed here.
