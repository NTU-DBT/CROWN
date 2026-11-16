# S05 native public result ownership — 9 November 2026

Status: **in progress**. Ledger remains41 verified /3 in progress /34 not started.
Root implemented and checked this checkpoint without agents. The full78-card
Refactor.md goal remains active. The user's preference is to reserve Astra Max
for exceptional problems and do most work in the root model.

## Ownership and public values

Actual runtime `storage::Tuple` owns an immutable native AccountedTuple through
an account-allocated shared object/control block. Moving an admitted native row
into the public tuple preserves its scalar address, layout token and original
query account. Native copies share that payload; no standard Row/string mirror
or accounting-only reservation is retained. `memory_usage()` includes the real
compact row and object/control requests, including account framing. Immutable
metadata shared by many tuples remains charged once to the same account.

`values()` now returns read-only TupleValuesView. Tuple-derived views and their
iterators retain the owner without allocating and remain readable after tuple/
runtime destruction. Individual ScalarView strings borrow from that owner;
explicit `borrow` inputs require their source lifetime. External callers needing
ordinary owning values use `export_row/export_scalar`. Standalone compiler/tool
layouts retain their legacy owning Row behavior.

Native layout/projection descriptors retain direct factories using the original
metadata/account. Projection uses scalar-view/native scratch, without an owning
standard row/string intermediate. Actual public cursor output, Delta SQL/scalar
mapping and physical derivation payloads now use native tuples. The spool limit
counts exact real scalar/shared-owner/node requests; the snapshot payload limit
uses the same tuple usage. Snapshot vector slots/growth blocks and several
session/input/capture owners still need routing.

## Verification and source scopes

Append-only receipts, input maps and preimages live in
`build/verification/s05-public-tuples-*`. Source7 freezes918 paths and is the
tested C++ implementation. Its all-target Debug build8 passes with strict
warnings enabled. The test scopes are:

| Configuration | Source and observed result |
| --- | --- |
| GCC Debug, full registered suite | source7:208/208,901.14s |
| GCC Debug, broad ownership/model/failure cohort | source7:56/56,123.73s |
| GCC Release, selected native integration | source7:11/11,0.33s; separately `layouts`1/1,0.01s |
| Clang18 Debug, selected native integration | source7:11/11,2.09s; separately `layouts`1/1,0.01s |
| ASan+UBSan/leaks, selected cohort | source7:17/18; storage journal timed out at120.11s |
| Same sanitizer journal executable, direct | source7:1/1,150.13s wall time |
| Registered sanitizer journal retry | source8:1/1,143.71s; sanitizer-only300s timeout |

The initial Release/Clang regex used singular `layout`; the registered name is
`layouts`, which has its own supplemental receipt. The initial sanitizer timeout
is preserved. The unchanged binary completes12,960 tentative model operations
across12 seeds and32/8 insert/erase allocation-failure positions. Source8 changes
only its sanitizer CTest timeout; all assertions and C++ sources remain unchanged.
Its binary SHA is identical before the direct run and registered retry. These
separate successful scopes cover all18 selected sanitizer names, and do not
constitute one18/18 CTest run. Source9 changes documentation and a snapshot-limit
comment only; this is not a fresh-source/full multi-compiler acceptance claim.

The actual public-result test proves scalar/token/account identity; exact real
scalar/object/control usage; allocation-free native copy/view/hash/release;
native projection with no unaccounted owning scratch; exact/one-under caps;
persistent failures and smaller retries; post-facade values; and allocation-free
prepared commit/output transfer. For both backends, a caller-retained output
exhausts the original finite budget on a later update, preserves the prior epoch
and permits a same-sequence retry after release. Spool bytes reconcile with the
actual freed FIFO node plus retained native tuple usage.

Detailed source7 sanitizer stdout records native public tuple peak10222/four
persistent fault positions and retained-output crossing peaks337506 reference /
344847 indexed. These are fixture-specific testing-runtime measurements, not
universal production peaks or Debug measurements. The original sanitizer
LastTest.log snapshot preserves that stdout. Debug's mutable temporary LastTest
history was overwritten by registration enumeration, and its failed-test list
is stale source6 history; use the full outer CTest4 receipt for208/208. The
`debug-attempt4-ctest-history-v2.json` annotation records this limit explicitly.

## Compatibility and retained failures

Explicit owning exports adapt independent expected-row/reference collections in
57 existing test/helper files. Assertion call counts match their preserved
preimages; that syntactic audit alone is not semantic proof. One precise cursor
failure-work assertion changes from one output field to the declared width:
native production reads all scalar views before its compact row allocation can
fail. Existing failure state, lease release, retained output and previous-epoch
checks remain. Source6's original failing receipt and all collecting build
diagnostics remain intact. No frozen CLI package, schema or executed proof helper
was changed.

Final immutable progress-v2 binds source maps, binary inventory, raw pass/failure
receipts, adaptation audit and the handoff. All cohort jobs/handles are closed.
Never overwrite prior maps, preimages or logs, or restart an active recorded job.

## Remaining acceptance

Fund outer snapshot/result capacity and transient growth, session controls/run
contexts, typed transport and reader values/control/progress, and capture/
diagnostic/asynchronous owners. The next-boundary inventory records61 candidates
in7 selected files; it is a starting inventory, not an exhaustive ownership audit.
Preserve atomic admission/rejection, existing account/work grants, previous
epochs and nonallocating publication/cleanup. Authentic operator record/byte
reconciliation, complete byte/overflow/churn acceptance and full compiler/
sanitizer/fresh-source matrices remain. Whole-query memory-budget completion and
S05 acceptance are **false**. See the [handoff](../handoff.md) and
[memory contract](../memory_accounts.md).
