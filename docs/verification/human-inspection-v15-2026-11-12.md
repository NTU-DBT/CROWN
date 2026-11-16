# Native capture cleanup and inspectable offline tools

The source maps now contain **8,972 scoped contracts in 6,757 blocks**, across
692 maintained files / 159,357 lines / 17,852 mapped blocks. Every maintained
line belongs to a structural block. Each scoped contract describes purpose,
inputs/outputs, invariants, ownership, failure and cost, with source/design
references. Start with the [source index](../code_specs/README.md),
[primitive cards](../code_specs/primitives.md) and [review guide](../code_review.md).

All 5,468 selected production callable/type/inline scopes retain contracts.
Structural maps and scoped review do not establish every possible execution;
remaining nonproduction semantic gaps are recorded independently. Local
ownership, resource and error policies remain distinguished from paper claims.

## Integrate the remaining bounded reviews

The [examples review](../../build/verification/public-examples-human-review-v1/integration-plan.md)
adds 168 contracts for five C++ examples and their CMake files. It documents
actual phase order, borrowed sinks, output preparation, provenance supplied by
the runner and explicit demonstration forecasts. CMake files remain byte-identical.

The [test-support review](../../build/verification/test-support-contracts-human-review-v1/README.md)
adds 177 contracts across eleven support headers, including all 149 selected
gaps in that scope. Allocation seams identify their actual domains: a C++ new
denial hook is not a malloc meter, a query-account limit or a total-byte meter.
Guard nesting/copy preconditions and borrowed result references remain explicit.

The [tool review](../../build/verification/code-spec-tools-human-review-v1/report.md)
adds 162 contracts across all three maintained mapping/checking tools. Root adds
five exact-path role contracts. These are offline Python operations; they add no
query instrumentation, runtime state or per-update checking.

All prior 8,460 canonical entries remain. One native finish contract changes
semantics and seventeen native records change source hashes after exact scope
review. The 512 new records preserve unrelated reviewer work. Comment-only
changes are verified separately from the three functional files below.

## Remove unnecessary histogram lookup work

[Native statistics finish](../../src/runtime/native_statistics.cpp) already sorts
groups by descending multiplicity. Equal multiplicities are contiguous, so an
incoming group can match only the final histogram bin. Replacing the earlier-bin
scan with one last-bin comparison preserves bins and the final ascending sort.
The [original proposal](../../build/verification/runtime-private-work-statistics-human-review-v1/native-histogram-proposal.md)
states the induction and exact debit formulas.

This adds no container, state, allocation, catch, retry or rollback layer. Limit
checks, original-account allocation, private preparation and all-or-nothing fact
publication remain. Fewer actual comparisons consume fewer work units; a finite
grant may now complete a capture that previously exhausted its work allowance.

A private probe links each actual before/after implementation through the real
account-funded WeightedBuilder. An independent std::map histogram and count/key
ranking oracle verifies 21 cases per profile, each at generous, exact and
one-under work caps. All graph allocations release back to the original account.
For 128 distinct multiplicities, lookup work falls from 8,128 to 127; full capture
work falls from 17,762 to 9,761. Other recorded usage/allocation facts match.

This is an actual-work result, not a latency measurement or whole-operation
linearity claim. Per-bin reserve/move behavior and cumulative logical payload
and growth charges remain; projected-key grouping can also remain quadratic.

## Correct offline source identity and role documentation

[Generation](../../tools/generate_code_specs.py) explicitly decodes UTF8 bytes
without universal-newline conversion. A CRLF source therefore hashes to its
actual bytes, matching the checker's byte hash. Existing LF checks were valid;
the defect requires the separately exercised CRLF trigger.

Generation computes the source digest once per file and reuses it for every
attached card and file descriptor. It no longer re-encodes/hashes the whole
source for each card. Anchor, parse, attachment and stale-review rules remain.
No exception framework or automatic review-hash refresh is introduced.

Five exact-path role descriptions take priority over the existing stem fallback,
separating IO serializers/declarations and the support CLI test from runtime
collectors/maintenance. The values context now links the existing
[dated tuple guide](s05-public-tuples-2026-11-09.md), explicitly as historical
ownership evidence, rather than silently dropping a nonexistent path.

Actual isolated tool execution and its negative controls are preserved in
`build/verification/code-spec-tools-functional-validation-v1`. The live map
checker passes with 82,447 local links and no stale or unmatched contracts.

## Native verification and preservation

Both strict C++23 eleven-target builds pass with warnings as errors. All eleven
selected native capture, scalar, indexed owner, combined, allocation-failure and
report-memory tests pass: Debug 1.03 seconds; ASan/UBSan with leak detection
5.11 seconds. The private before/after probe passes in both profiles, with
63 captures per variant/profile. Recorded native inputs stay fixed throughout.

All 325 registrations remain unchanged. Raw terminal CTest logs, exact source
preimages, proposal/card migration, independent acceptance and the actual linked
closure are preserved. The wider IO/package tests remain preserved as
[v14 evidence](human-inspection-v14-2026-11-12.md); they were not repeated for
comment edits. No full 325-test, Release/Clang or timing benchmark claim is made.

Root recipes/proofs: `build/verification/inspection-native-capture-tools-v1`.
Seal: `build/verification/human-inspection-v15-progress-v1.json`; frozen source:
`build/verification/human-inspection-v15-source-v1`. Earlier seals stay immutable;
main build directories remain active/reusable after preservation.

Full Refactor implementation remains active. W06 remains unimplemented;
its [independent assessment](../../build/verification/w06-contract-assessment-v1/assessment.md)
records actual reusable transaction boundaries, missing projected bag deltas and
required durable rejection disposition. Assessment is not implementation evidence.
