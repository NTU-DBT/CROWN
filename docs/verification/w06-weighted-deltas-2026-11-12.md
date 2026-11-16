# W06 projected bag delta primitive

W06 is in progress. The implemented primitive captures genuine projected
logical-CQ bag changes inside one existing native epoch. It supplies no physical
SQL batch admission, grouped aggregate transaction or recovery coordinator.
Read the [calling/algebra/cost contract](../weighted_deltas.md),
[source index](../code_specs/README.md) and [task ledger](../task_ledger.md).

Root adopted five scoped files from the sealed private proposal, then supplied
an explicit default initializer for the new Epoch handle. Shared iterative
backtracking preserves committed cursor selection, prefix arithmetic and metrics.
The collector hooks the actual factor replacement before publication, fixes
absent anchors and defers multiplication until assignment compatibility is known.
Consolidation probes borrowed output first, freezes only new keys, swap-removes
canceled facts and drops the lookup index before immutable publication.
The existing sole stage abort boundary remains; no new production catch is added.

The source-pinned proposal and separate test review remain immutable. Their
uncompiled authoring status is distinct from root's receiving execution below.
Root corrected the test's AccountedTuple account query through its layout and
added deterministic randomized batches, arithmetic rollback, complete covered-new
allocation cuts and publication under allocation denial.

## Native evidence

Final strict Debug and ASan/UBSan/leaks each pass all ten selected weighted/SQL
tests on the final source: 51.73 seconds Debug / 111.04 seconds sanitizer. The
focused delta test takes 2.82 / 10.14 seconds. Both profiles exercise 159 ordered
and 178 indexed allocation-cut positions, each followed by same-sequence retry
and account release checks. Commit and rollback make zero covered C++ new
attempts under denial; this does not intercept every libc allocation or eliminate
free and account bookkeeping.

Both storage fixtures run 64 deterministic epochs with six generated stage
opportunities each; skipped no-ops still receive preview comparisons. The 768
random preview checks compare each current private net with independent full
native joins. Hand cases separately cover absent anchors, 2*3→4*5 cross terms,
slot repair, hidden/generalized factors, repeated fields, long-string ownership,
nullary ±UINT64_MAX, limit 100 dead prefixes, arithmetic abort and work exhaustion.
The tests use full before/after mirrors only in the independent oracle.

A ten-case Release before/after probe confirms disabled capture preserves native
allocation counts, logical work, grants and outputs. The measured fixed addition
is 72 account payload bytes per pending Data and 16 bytes per Epoch value; the
pending facade stays 40 bytes. The final account sample still holds a closed
pending token. These measurements do not establish post-destruction timing,
RSS, global-heap behavior or a portable ABI size.

Enabled contribution replacement is checked on both backends, including logical
totals 5→7→5 cancellation and a later nonzero net. The actual indexed threshold
runs 64 resumed stages: disabled structural work 1218, enabled 1474; exact 1474
succeeds and 1473 rejects atomically under the same retained grant.

A focused Astra Max review accepts its pinned logical-CQ variant without a
required correctness change. Root adopts its optional unique-anchor early exit.
The actual 32-step ordered/indexed before/after probe saves 31 capture/epoch work
units (capture 382→351, epoch 396→365), preserving all output/root, row/field/byte,
factor/product/comparison/term/mutation counters, allocation/free/payload facts
and five native-grant components. No runtime state or allocation is added by
that early exit. The accepted review preserves its earlier source/test snapshot;
root's later one-body performance edit and extra tests have separate receiving
proof and final execution above.

The complete test-disabled production Release build and both runtime-testing
variants pass. The three SQL regressions per profile are included in the final
ten. A moved installed strict C++23 Release consumer passes against 216 installed
files, copies Epoch without copying facts and reads them after runtime/token
destruction. All 325 predecessor test commands and execution properties remain
after excluding source-line backtraces; weighted_delta is the only added test,
for 326 total. The six added CMake commands are all within BUILD_TESTING.

## Review and limits

Root evidence: `build/verification/w06-weighted-delta-implementation-v1`.
Proposal: `build/verification/w06-weighted-delta-design-v1`, manifest SHA-256
`df9313925ddfe6f2d80bffcea79389b72c5885b9f64a6d3fe02625f5f6c0d528`.
Test proposal: `build/verification/weighted-delta-test-review-v1`, manifest
`00bb3de9d4068cb7f419c123fb7ffc3fae035d3e34ce805b9f3b437c03a17f6c`.
The proposal's final status-print error occurred after writing its complete
manifest; the separate seal-verification receipt and root payload hashes verify
its 51 payloads. No failed authoring print is presented as a native test.

Traversal still visits actual earlier prefixes before reaching a forced anchor;
it is not bounded only by final delta size. No weighted CROWN batch/delay theorem,
full 326-test run, performance speedup or complete W06/release claim is made.
The [v17 predecessor](human-inspection-v17-2026-11-12.md) is sealed separately;
its source and evidence remain preserved. The source-map and final sealing results are recorded in the accompanying
inspection checkpoint and handoff.
