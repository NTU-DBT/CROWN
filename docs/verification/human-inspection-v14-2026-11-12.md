# Complete production function/type inventory and unused parser cleanup

This checkpoint reaches **8,460 contracts in 6,471 blocks**, across 692
maintained files / 159,290 lines / 17,831 mapped blocks. Every selected
production callable/type/inline cluster now has an individual reviewed contract:
1,001 include, 4,409 src and 58 apps blocks; **zero selected production gaps**.
The [source/spec reconciliation](../../build/verification/inspection-gap-inventory-v8/README.md)
checks actual source hashes, line counts, anchors and attachments.

The [source index](../code_specs/README.md) covers all maintained lines;
[primitive cards](../code_specs/primitives.md) specify usage, inputs/outputs,
invariants, ownership/lifetime, failure and real cost. Lexical coverage and these
selected counts do not certify every possible execution or complete the separate
test/tool/example semantic review. Paper/local provenance remains explicit in
[the review guide](../code_review.md).

## Remove unused code while preserving active validation

Root adopts the separate reviewed deletion from the
[input admission/bindings packet](../../build/verification/input-admission-bindings-human-review-v1/README.md).
The unused delimited-record reader, text-cell overloads and their exclusive
helpers have no callers in the 692 maintained source files. Package exports
contain no public declarations or private helper header.

The deletion removes 194 net source/header lines, seven callable definitions,
six direct throw sites and one std::function alias. It adds no catches, runtime
state, allocation, callback or retry. The active event_reader.cpp integer parser
is separate and remains. All three complete UTF-8 helper bodies—invalid_document,
continuation and require_utf8—preserve their C++/literal tokens. The remaining
private header declares only shared strict UTF-8 validation with its explicit
string_view dependency. Callers continue enforcing their own byte/domain limits.

Nine draft-only cards for deleted blocks are excluded. Three live-function cards
and a thin-header declaration card have exact adopted source hashes. This is an
explicit functional deletion, not a comment-only equivalence claim. No new test
mirrors unused code and no runtime speed improvement is claimed.

## Complete the production usage contracts

The [remaining report/input IO review](../../build/verification/remaining-report-input-io-human-review-v1/report.md)
adds 244 cards with concrete DOM, account-funded decode scratch, input-progress
and borrowed-event lifetimes. Its narrow JSON exception translation remains.
Source-position publication still depends on the actual reader/queue ordering
gates and can perform ordered tree comparisons without allocating a new node.

The [public interface review](../../build/verification/public-io-runtime-headers-human-review-v1/report.md)
and its [copy correction addendum](../../build/verification/public-interface-copy-corrections-v1/README.md)
add 662 cards. Root caught the original key-sharing claim: InputPositions copies
clone map nodes **and nonempty AccountedText bytes** on the original account.
AccountedInputOptions descriptor copies share actual Values; direct Values
copies clone their owned members. NativeSeed is noncopyable through AccountedTuple.
The addendum corrects 56 semantic records plus 12 comment-source hash records,
preserving the original packet and every key.

The [private runtime work/statistics review](../../build/verification/runtime-private-work-statistics-human-review-v1/README.md)
adds 195 cards and preserves four earlier records with source-hash changes only.
Its 21 handlers retain their actual cleanup/capture/continuation roles.
The [Astra recovery review](../../build/verification/astra-recovery-boundaries-human-review-v1/README.md)
adds 119 cards distinguishing provisional header limits, borrowed artifacts,
one-shot read failure and actual durable publication phases. It proposes no
runtime change or handler removal.

The [root primitive review](../../build/verification/remaining-primitives-human-review-v1/README.md)
adds 79 cards for native reflection, statistics-report assembly and coherent
private test hooks. Reflection traits have no runtime allocation themselves;
Builder work remains explicit. Current report graphs own real captures while
previous-report comparisons copy values. Test collision/counter hooks are
confined to their coherent private variants.

Across the changed native inputs, 65 sources differ only in comments and
preserve whole C++/literal streams. Two sources contain the independently
proved parser deletion. All prior 7,080 canonical records remain; only four
reviewed-source hashes change after exact token review. The checkpoint adds
1,380 records. Source comments add 121 lines, giving a net reduction of 73 lines.
No per-update or per-primitive runtime overhead is introduced.

## Native verification and preservation

Both strict C++23 17-target builds pass with warnings as errors. All 24 selected
tests pass Debug (65.98 seconds) and ASan/UBSan with leak detection (253.98
seconds), on identical 1,129 maintained input pins with no drift. The cohort
covers ingestion/scalar fixtures and allocation failures, native metadata,
typed/stream memory, transport, checkpoint/grant/restore, observation/cursor/
EXPLAIN, CLI process failures, file workflow and relocated package consumption.
The package test installs a fresh temporary prefix and compiles/runs an external
consumer through new-process restore. It does not overwrite preserved SDKs.

All 325 registrations remain unchanged. Raw terminal LastTest logs, source
preimages, exact body/card migration, immutable review manifests and actual
selected native link closure are preserved. No full 325-test, Release/Clang or
latency claim is made.

Root recipes/proofs: `build/verification/inspection-io-cleanup-v1`.
Seal: `build/verification/human-inspection-v14-progress-v1.json`; frozen source:
`build/verification/human-inspection-v14-source-v1`. Earlier seals remain
immutable; active build directories remain reusable after preservation.

The native histogram last-bin optimization remains unapplied with its own debit
and adjacency proof. Tool role labels, a filtered missing tuple-guide reference
and a CRLF-only generator/checker hash mismatch have separate unapplied fixes;
current sources are LF and current link/hash checks pass. Example/test-support/
tool reviews continue. Full Refactor work, W06 and release acceptance remain open.
