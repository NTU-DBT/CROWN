# V02 independent review and human inspection: V46

V02 remains **in progress**. This checkpoint supplies source-pinned independent
arguments, a [15-claim source-to-invariant matrix](../independent_review.md),
counterexample dispositions and current selected native regressions. It does not
claim that the catalogue covers every public guarantee or that every internal
cross-module assumption has been independently discharged. The ledger is
**58 verified /2 in progress (A02, V02) /18 not started**, 78 total.
Bounded V33 W06 and V01 remain verified. The full Refactor/release goal is active.

The [receiving packet](../../build/verification/v02-independent-review-v1/proof-receiving-v1.json)
rehashes 16 completed packets, 533 scoped source pins /350 distinct paths,
model outputs and declared manifests. A separate reviewer inspected each relevant
algorithm; root supplied account/Session/file arguments and received independent
corrections. One Astra Max planner review was used; other reviews used the
existing root-model and Luna agents. Reviewers did not change maintained code or
run native tests. Root owns the native execution evidence below.

## Human-readable structure and source attribution

The [inspection guide](../code_review.md) now leads with current block contracts,
the query lifecycle, exact paper versions, source/design mappings and primitive
costs. Its previous chronology is preserved
[byte-for-byte](../code_review-history-v45-2026-11-14.md). Current W06 guides link
implemented runtime, Session, input and rebuild interfaces. Paper attribution
distinguishes full P1 Definition 3.2 from bare Definition 3.1, P2's native-anchor
convention, classical GYO recognition and local exact-height/residual arguments.

The matrix connects SQL admission, physical source identity, exact height,
projected set deltas, weighted factorization, atomic aggregates, memory funding,
file frontiers and performance qualifications to actual source and counters.
The [correction receipt](../../build/verification/v02-independent-review-v1/review-corrections-v1.json)
preserves nine investigated dispositions. These include the original weighted
model's out-of-admission shape and its valid replacement, narrower EXISTS and
repair-order wording, dispatcher-versus-raw-close counters, and the shared CBOR
item cap. Original packets remain unchanged. No admitted-input implementation
counterexample requiring a new runtime guard was demonstrated in these scopes.

## Executed regression boundary

| Profile | Current selected result | Terminal evidence |
| --- | --- | --- |
| GCC Debug | 33/33 pass; 1322.71 seconds | [Metadata and fingerprints](../../build/verification/v02-independent-review-v1/native-debug-after-v1/evidence.json) |
| GCC ASan/UBSan/leaks | 33/33 pass; 5472.43 seconds | [Metadata and fingerprints](../../build/verification/v02-independent-review-v1/native-san-after-v1/evidence.json) |

The [exact plan](../../build/verification/v02-independent-review-v1/native-regression-plan-v1.json)
maps 33 test names to actual targets/CMake declarations. The focused cohort covers
recognition/tree validation, exact/residual/candidate/continuation proof paths,
projected-delta specification/replay/live/anchor/lifecycle, initialization,
memory-account contracts and weighted messages/cursors/oracles. Both profiles
retain all 348 registrations; execution of all 348 is not claimed. The native
recorder proves 1,196 inputs stayed unchanged during each of the two builds and
two CTest commands. These are four new terminal source-stable receipts.

Post-run evidence retains actual selected strict C++23 warnings-as-errors
commands with assertions active, sanitizer configuration, cache/CTest/log/link
metadata and fingerprints for 33 selected objects/executables per profile.
Reusable build-tree object/archive/executable bytes are not retained immutable
in this packet. Ordinary CMake rebuild/freshness is not cryptographic compiler
lineage. Test timings are diagnostic; there is no controlled speedup experiment,
new Clang/Release/install matrix or whole-current-suite claim.

## Arguments and finite evidence

Planner and projected-delta reports provide general conditional arguments over
their admitted families, rather than inferring completeness from small cases.
Support/physical, storage, weighted, original-SQL aggregate, account-owner and
recovery reports identify the concrete leaf/caller obligations and actual
counter units. File protocol assumptions include a trusted stable namespace,
cooperating writers and successful configured Linux sync; they do not establish
arbitrary hardware power-loss or every-instruction behavior.

Finite supplemental evidence includes 3,746 literal-tree/recurrence cases;
36,111 admitted projected-delta endpoint pairs /72,222 directions; 1,408 support
states /26,112 FIFO/LIFO toggles /2,816 direct-replay builds; 4,096 physical
updates/schedules; 59,049 valid nested weighted states /118,098 before-after
checks; and 59,049 nullable physical-batch endpoint pairs /314,928 alias
replacements plus exact arithmetic probes. The preserved original 66,501-state
weighted model includes algebraic over-approximation and is not wholly an
admitted-runtime corpus. None of these models executes C++ or proves allocator,
CPU, crash or universal fault coverage.

## Unchanged implementation and remaining work

All **1,196 native inputs /355 production paths** remain byte-identical to V45.
No executable token, handler, defensive framework, persistent field or runtime
instrumentation was added. Documentation contributes no update-path overhead.
Existing rollback and uncertain-I/O catches keep their necessary consumers.

The generated map remains **751 files /172,040 lines /19,412 blocks** with
**16,717 contracts in 14,301 blocks**, zero selected callable/type/substantive
inline-cluster gaps, and 126,343 checked generated local references. The exact
**5,111 structural blocks /670 files /15,137 lines** and their bytes are unchanged.
They remain mapped rather than individually certified semantic specifications.

Next, reconcile the review graph against the complete public guarantee catalogue,
including [R1 history retirement](../history-retirement.md) and its
[actual deletion boundary](../../src/recovery/generation_retirement.cpp), and
identify any still-unreceived compiler/recovery/ownership leaf. Existing scoped
component acceptance remains intact; it does not itself close V02's broader
inventory requirement. Continue behavior-relevant structural dispositions and
the remaining Refactor gates. A02 still gates C04/B01; R2 retirement, experiments
and release remain open. The [handoff](../handoff.md) records the exact next state.
