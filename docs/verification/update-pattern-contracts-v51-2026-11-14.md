# V51: source-bound declarations and conditional selection

X01 remains in progress. This checkpoint implements requested insertion/FIFO
metadata, conservative candidate analysis and actual optional selection filtering.
It does not implement insertion/mixed runtime monitoring, committed pattern
profiles, persistence or reoptimization continuity. The full Refactor and release
gates remain open; the ledger stays 60 verified /2 in progress /16 not started.

The [usage guide](../update_patterns.md) gives the exact API, source-transfer
argument, sufficient cases, owners, failure boundaries and costs. The predecessor
[V50 record](update-pattern-fifo-v50-2026-11-14.md) covers physical-row lifetime
FIFO in the existing window owner. The immutable V50 source/paper audit remains
`build/verification/v50-pattern-proof-audit-v1`; it excludes successor code
acceptance and is not a complete taller mixed-pattern characterization.

## Implemented boundary

The new IR `Declaration` stores only canonical table-sorted rules and the actual
compiler source SHA-256/table count. Raw positive IDs identify explicit disjoint
joint FIFO scopes; zero makes no FIFO request. Insertion-only forbids effective
physical lifetime termination after a separately established enforcement origin.
Capture/import establish no origin or observed compliance. The unused dense
scope index, group scratch/sort and duplicate analysis usage field were removed.

Planner analysis retains the genuine P02/P07 candidate and source-bound
Declaration handles. New scratch/edge allocations use the receiving account;
existing owners keep their own allocation/lifetime contracts. Transfer defaults
to `not_checked`, constant routes report `not_required`, and `checked_typed_cq`
is set only after all applicable gates. Repeated variables/constants reconstruct
accepted full rows; ignored columns, self-joins and normalized source remain
outside this transfer fragment. The direct-CQ compiler already rejects nullable
columns. All-insertion is recognized independently of height; other mixed cases
above height two remain unknown. No Trim/MixDetect certificate or runtime
maintenance/delay guarantee is manufactured.

Pure selection accepts an optional declaration only with a real native program,
checks its source binding once, copies rules under the aggregate/account grants,
and analyses every retained candidate. It excludes unproved pattern cases from
winner choice while preserving the original certified height and family. If none
is eligible, it refuses before unnecessary primary ranking; otherwise required
C02 assessments cover the full retained family. Cache keys bind every raw rule
field in a versioned domain. Default requests skip the new copy/analysis and
retain prior request bytes, with fixed empty optional/vector storage added.

Factories use direct ownership cleanup. One new public analysis `noexcept`
boundary translates existing ranking/resource failures; private visitors add no
catch layer. Selection uses its existing publication boundary. No runtime input
path, row mirror, monitor scan or recovery wire format changes in V51.

## Human specifications and review

All 19,573 mapped blocks /174,044 source lines across 763 maintained files are
accounted for. There are 19,102 source-bound usage contracts covering all 16,671
nonblank blocks; only 2,902 blank blocks retain structural facts alone. The checker
passes 139,502 generated local links with no stale or unused contracts.

This pass adds 98 contracts and reviews/amends 22 changed existing blocks. It
preserves original authors on 1,623 hash-only updates, 69 identical span rebases
and two identical CMake endfunction commands whose old disambiguating text
anchors crossed the inserted test calls. A Luna reviewer authored 92 new-file
cards. Root reviewed all purposes and ownership/cost fields, 24 complete critical
cards, corrected 12 wordings, received seven changed successor blocks, and authored
six integration/allocation cards. Binding checks do not imply a fresh semantic
reread of every pre-existing repository contract.

The completed review packets are:

- [Entry integrity](../../build/verification/continuation-v51-entry-v1/checks.json):
  all 4,624 V50 live/frozen paths and 68,726 protected artifacts checked before edits.
- [Initial usage review](../../build/verification/v51-declaration-usage-review-v1/review.md):
  pinned findings retained without rewriting the earlier snapshot.
- [Authored card review](../../build/verification/v51-new-usage-cards-v1/review.md):
  92 initial new-file blocks, with subsequent root receiving amendments preserved.
- [Final bounded code review](../../build/verification/v51-final-pattern-code-review-v1/review.md):
  13 effective native source pins, separate successor copies and zero open findings.
  The reviewer ran no tests; its packet records sanitizer execution as pending at
  review time. Root receives the completed sanitizer evidence separately.

## Native evidence

There are 13 changed native inputs: eight new files and five changed existing
files. Six new and four existing production paths change; the remaining 351
predecessor production paths remain V50 bytes. The maintained native input
inventory is 1,209; CTest has 351 registrations, adding only `update_pattern` and
`selection_pattern` to the 349 predecessor definitions.

The final exact-source ASan/UBSan/leak run passes all ten targeted groups:
`update_pattern`, `selection_pattern`, `selection_pure_link`, `selection_contract`,
`selection_cache`, `selection_source`, `selection_binding`, `selection_resources`,
`selection_result_memory` and `selection_native_admission`. The production
Release build passes with `BUILD_TESTING=OFF`. Debug coverage is the union of nine
successful groups in the final production-code run and the corrected final
`selection_pattern` run. The latter fixes only the cap fixture's minimum one-byte
payload accounting; it changes no production code or other test target.

The new selection control passes 332 persistent covered C++ allocation denials,
including nine during `pattern_analysis`, plus an independent native account-cap
refusal. It checks no partial result/cache publication, unchanged live allocation
totals and a valid previously retained analysis. Raw malloc denial and C++
exception-runtime storage are outside the seam's coverage. The other controls
exercise canonical rules, exact/one-under grants, source/candidate mismatch,
ordinary export, receiving-account copies, actual winner change, joint versus
per-table scope, transfer gates, constants and a genuine height-three witness.

Raw final receipts are `x01-pattern-selection-test-sanitizer-v51-v2`,
`x01-pattern-selection-allocation-test-debug-v51-v1`,
`x01-pattern-selection-test-debug-v51-v3` and
`x01-pattern-selection-build-release-v51-v3` under `build/verification`.
Earlier failed builds/tests and successful older-source runs remain recorded;
they are not relabeled as final evidence. No full 351-case run, new benchmark,
Clang run, moved SDK or whole-session performance claim is made.

The root receiving/seal packet is
`build/verification/update-pattern-contracts-v51-v1`. The maintained
[handoff](../handoff.md) identifies the current source/evidence seal and the next
runtime obligations. This component is a checkpoint toward full X01 acceptance.
