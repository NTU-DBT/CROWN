# Human inspection continuation: scalar and native table primitives

This pass follows the [Boolean/native review](human-inspection-v2-2026-11-11.md).
Two read-only reviewers supplied the scalar and indexed-table contracts. Root
reviewed the ordered reference backend and integrated a bounded Luna Max
dispatch review and inventory. No additional Astra run was used. Root owns the
code changes and executed validation below. The full implementation and
repository-wide comment and usage-specification review remain active.

## Direct implementation and failure boundaries

[`TupleValuesView` equality](../../src/storage/tuple_values.cpp) reads each arity
once and rejects different widths before reading cells. Equal-width views use
the existing scalar three-way comparisons. Row and RowView wrappers delegate
to that equality operation; lexicographic ordering is unchanged. Different-width
equality now takes fixed work, while equal-width equality visits the compared
prefix and any compared string/decimal bytes. There is no additional allocation,
state, owner or framework, and no measured speedup claim.

For valid stable views this preserves the result: the former lexicographic
comparison could not return equality for different widths, and equal widths use
the same field comparisons in the same order. Borrowed cells must remain valid
through the call. Equality is not an admission API for expired or invalid views.
The source-edit audit records this argument and proves all other executable
tokens in the nine changed native files are preserved. Eight files change
comments alone. One additional maintained input changes only a test's diagnostic
string, separating prototype component checks from the independently recorded
whole-query acceptance. No assertion or test registration changes.

The scalar/table review found no justified catch removal in this slice. Native
construction cleanup releases raw storage on failed construction; table/journal
preparation and undo preserve state and pin lifetimes across failures. Public
error translation retains its separate diagnostic boundary. Two optimization
candidates remain explicit: repeated public/native tuple validation, and the
projection wrapper's repeated token check. Removing them requires preserving
field diagnostics and moved-from/error ordering. See the
[error dispositions](../code_specs/error_handling.md).

## Human usage specifications and comments

This pass adds 406 authored contracts: 126 scalar/row/layout/projection cards,
118 indexed-table/journal/node cards, 101 root-authored ordered-reference cards
and 61 dispatch/protocol cards. There are **723 scoped contracts in 709 mapped
blocks**. The [inspection index](../code_specs/README.md) maps 664 maintained
files, 152,293 lines and 16,816 blocks with exact current hashes and contiguous
source ranges. [Primitive cards](../code_specs/primitives.md) state usage,
ownership, invariants, failure phases, cost and design references.

Every non-scaffolding callable/type block in the five reviewed scalar/row/layout/
projection implementation files, the ordered reference implementation and the
dispatch implementation has an attached authored card. Some indexed/header
constructors, trivial forwarders and testing helpers remain outside the
individually carded scope. Across production include/src/apps code, 4,578 selected
callable/type/inline-cluster blocks still lack an individual authored contract.
That count is an inventory, not a semantic coverage percentage. Structural facts
do not certify every line, branch or retained comment.

Nine staged comment/documentation corrections and root's local comments clarify:

- `ScalarView` string bytes borrow storage. Only tuple-derived views retain
  their payload; explicitly borrowed rows remain caller-owned. Preflight and
  copy require stable cells and bytes for the entire call.
- Public projection validates its actual source/target path; the direct native
  prevalidated-token path has a separate contract. SQL scalar arithmetic and
  aggregate admission remain distinct from implemented scalar identity and
  annotation arithmetic.
- Insertion prepares detached indexes before arena publication. Primary pointers
  are rebound from the caller's input to stable arena values before publication.
  Journal pin-room admission precedes insertion.
- Low-level cursors borrow entries under weak table ownership, a revision and
  the documented synchronization requirement. Runtime cursor leases provide a
  separate stronger lifetime contract. Indexed journal cursors retain their
  original grant; repeated end calls can still debit low-level work.
- Ordered `change(i)` walks list history in O(i); indexed history uses direct
  vector lookup. Bucket materialization takes O(matches) handles, while native
  bucket cursors avoid that result collection.
- Account reports scan the ledger, arena high-water storage and indexes.
  Allocation-free diagnostics can still take quadratic or population-product
  work. Commit's containing-pointer classifications scan the allocation ledger.
  Snapshot copies preserve IDs, revision and traversal order under a new owner,
  while resetting action history and excluding external pins/retired slots.

The [native journal protocol](../storage_journal.md#accounted-native-interfaces)
collects the preparation, publication, grants, history and borrowed-read rules.
Seventeen stale status paragraphs across twelve guides now distinguish dated
checkpoints from implemented native accounting, compiler/input/export boundaries
and RSS. They do not expand the accepted language or release scope.

Scalar representation, allocator framing and native journal guarantees are local
engineering contracts. Cards link their actual guides. Corrected P1 v2 support,
enumeration and annotation sections provide algorithm context where applicable;
they do not prove the allocator, exceptions or SQL boundary. Exact paper versions
and engineering distinctions remain in the [review guide](../code_review.md).

## Executed validation

| Configuration | Selected linked checks | Elapsed |
| --- | ---: | ---: |
| Fresh GCC Debug | 5 passed | 0.44 s |
| Fresh ASan + UBSan with leak detection | 5 passed | 1.63 s |

The selected tests are `scalars`, `layouts`, `memory_account_contract`,
`public_tuple_memory` and `s04_storage_table`. They cover exact scalar order,
hashing and codecs, typed projection, tuple account/lifetimes, ordered/indexed
tables, dispatch and plan ownership. Each configuration reports 508 allocation
positions across native table, indexed, dispatch and plan operations, plus four
public-tuple allocation faults. Indexed work/component boundary checks report
44 and 9 boundaries; plan grant checks report five. The StorageTable model runs
500 independent operations, copy faults and cross-backend journal lifetimes.
Prototype factory/row/arena controls run separately; they are not silently added
to those reported fault counts. Timings describe this run, not a benchmark.

The fresh builds produce 30 linked native artifacts and 220 actual C++ objects
across both profiles. They include the testing runtime required by these tests;
this is not a new production-runtime acceptance claim. Two further actual
`tuple_values.cpp` objects compile with strict optimized GCC and Clang flags.
These are compilation controls, not linked Release test runs. Final native
build/test receipts bind the same 1,101 current code inputs without concurrent
input changes.

The specification checker passes 28,083 local links, current hashes and complete
line partitions. All 723 authored anchors resolve uniquely; eight anchor fixtures
and ten negative checker controls pass. Same-profile comparisons preserve all
314 test commands/properties, and CMake/install declarations are unchanged.
This pass does not claim a full 314-test run or complete semantic review.

All 2,444 predecessor source paths have preserved before-images. The previous
56 linked artifacts are revalidated unchanged. Prior frozen source/build/evidence
trees remain sealed. Acceptance is recorded in
`build/verification/inspection-v3-acceptance-v1.json`; the source/evidence closure
is `build/verification/inspection-v3-progress-v1.json`. Raw final test logs are
`inspection-v3-ctest-final-{debug,sanitizer}-v2.LastTest.log`; final linked build
receipts are `inspection-v3-build-final-{debug,sanitizer}-v3`.
The [handoff](../handoff.md) records remaining review and implementation work.
