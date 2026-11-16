# W02 and human inspection verification — 11 November 2026

W02 exact weighted subtree messages are verified within the direct-CQ native
logical-port boundary. The full Refactor.md implementation remains active.
Weighted SQL, projected bag factors/cursors, SUM/AVG payloads and weighted
transaction recovery remain later cards. No R1 release is claimed.

## Human inspection revision

The user requested clearer structure/comments, inspectable usage specifications,
less unnecessary exception machinery and simple performance-sensitive primitives.
One explicitly requested Astra Max agent prepared the documentation overlay;
root reviewed/applied its changes and owns runtime implementation/verification.
A bounded Luna Max agent supplied the independent Python weighted oracle, which
root reviewed and corrected to omit zero-weight native records.

The [inspection index](../code_specs/README.md) covers **656 maintained code/build/
test files, 150,698 lines and 16,646 contiguous blocks**. Each source range links
its declaration, local calls/guards/returns/growth and nearby comment evidence.
**51 scoped semantic contracts** describe actual usage, inputs/outputs,
invariants, ownership, failure, cost and justified references:24 reviewed hot
primitives and 27 root-authored weighted contracts. Shared module context is
stored once. Structural maps are explicitly distinguished from those contracts.

Root applied 23 comment corrections across 18 files, including stale claims that
native memory integration remained partial. C++ executable tokens/literals are
preserved; actual g++ `-E -P` outputs are byte-equal for all 17 edited C++ units.
CMake noncomment lines are unchanged. These checks do not preserve debug line
tables or certify every alternate preprocessor configuration.

The source change in selection replaces `Operation::note`'s throw-then-catch
conversion with the shared noexcept `component_diagnostic` value mapper. The
enum mapping, component status and reason bits are preserved; callers that need
unwinding retain the throwing wrapper. [Error dispositions](../code_specs/error_handling.md)
explain required cleanup, transaction, resource-stop and durable-authority
boundaries. A handler count is not evidence that those boundaries are redundant.

The offline generator/checker adds no native build/runtime dependency or
instrumentation. The live checker validates 23,437 local/source/Markdown-fragment
links, current source hashes, complete maintained inventory and line partitions.
Root added checks for empty semantic fields and duplicate reviewed anchors;
one valid fixture and ten independent negative controls pass. The generator
marks reviewed contracts stale after source changes instead of updating their
review hashes automatically.

This is complete source-range mapping, not individually authored semantic
specifications for every block, blanket truth certification of retained comments,
a complete mathematical review or proof of every branch. The [paper map](../code_review.md)
retains corrected P1 arXiv:2301.04003v2 and P2 arXiv:2603.14754v1 provenance.
Native allocation, SQL, durability and full-subtree engineering contracts are
not relabeled as published theorems.

## Weighted behavior and cost

The [weighted contract](../weighted_messages.md) defines exact native
sum/product messages, generalized full-scope products followed by separator
summation, expected-value replacement and explicit empty-key root summaries.
Positive-to-positive numeric changes propagate through a causal FIFO queue.
Candidates retain partial child support and are reclaimed after the last child
disappears. The local induction argument is separate from later projected-output
factorization and performance theorems.

Live records store inline scalars and one cached child array. Numeric changes
save compact scalar/one-slot undo instead of allocating a new full record image.
Owning change/event histories are opt-in; snapshots are explicit bounded copies.
Default updates copy no diagnostic child arrays. Product recomputation still
visits child factors; ordered maps, deep fields, original grants and explicit
node-lifetime ledger scans have real costs. No measured speedup or Boolean
numeric-maintenance bound is inferred.

## Linked verification

| Configuration | Passed selected checks | Wall seconds |
| --- | ---: | ---: |
| GCC13 Debug | 8 | 6.34 |
| GCC13 Release | 6 | 1.50 |
| Clang18 Release | 6 | 1.55 |
| ASan/UBSan with leak checking | 6 | 26.52 |

These are verification durations, not comparative runtime measurements. Each
configuration checks 1,516 update states against an independent unbounded-integer
complete-assignment oracle and sweeps 894 actual allocation failure positions:
creation/deletion, ordered/indexed storage and capture disabled/enabled. The C++
model compares every maintained row/cache/message after each logical update.

Coverage includes hidden sums, nested generalized scopes, strict child supersets,
numeric-only changes, same-key event chains, typed disconnected three-child
empty-key products, Boolean/nullary/constant roots and a depth 256 chain. Failure
controls cover stale/type/node/sequence rejection, product/sum overflow,
multi-stage rollback, exact/one-under work and requested-byte heap, 64 resumed
stages plus private capture under one native grant at its exact/one-under
structural threshold, nonallocating commit/rollback, owner moves, capture
retention and bounded numeric churn.

Selection contract/resources and existing set annotation admission pass in all
four configurations. Debug additionally runs support journals and epoch-index
regressions. The testing runtime variant compiles separately. A strict external
Clang consumer compiles and runs from a moved installed SDK without source/test
headers or reference-library linkage. It checks compiler-artifact admission into
a new query owner, structural/weighted identity separation, exact counts above
2^53, owning snapshots/moves and SQL rejection through both constructors. All15
installed native archives match the final Clang build byte for byte.

All308 predecessor test commands/properties and installation declarations are
preserved;311 tests are registered. The complete311-test suite was not executed.

## Evidence and continuation

`build/verification/w02-acceptance-v1.json` binds 18 requirements, 1,093 matching
code/CMake/test/tool/schema inputs, 83 actual native archives/executables, 511
actual C++ object commands, the final receipts/raw test logs and all 1,750
preserved predecessor preimages. To repeat the audit, copy `build/verification/w02-acceptance-v1.py` and point
its `DESTINATION` at a new file; the original refuses to overwrite completed
acceptance evidence. Final source hashes/continuation
are recorded separately in `w02-progress-v1.json`.

The reviewer's frozen overlay, comment manifests/preimages, 17-unit preprocessing
audit, handler inventory and scoped review limitations remain under
`build/verification/human-spec-revision-v1`. Root subsequently corrected the
generator's applied-change wording and strengthened required-field/unique-anchor
checking. Current maps regenerate from repository sources with:

```
python3 tools/generate_code_specs.py
python3 tools/check_code_specs.py
```

Initial syntax/type fixes, invalid generalized/type/budget fixtures, missing local
Ninja and incorrect target invocations remain separately recorded developer
negatives. They are not successful verification. The W01/C06 historical seals
remain intact; preserve current W02 build trees and receipts at this checkpoint.
Next is W03 projected bag enumeration, with local visible factors that count
each explicitly enumerated child exactly once.
