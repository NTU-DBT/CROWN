# V67 guarded key-specialization acceptance

X02 is verified for the declared non-null direct-CQ set family. The opt-in
`CROWN::keys` compiler removes redundant FK parent occurrences, retaining the
original general plan and the complete original source catalog/constraint owner.
Read the [exact rule, ownership and cost contract](../key_specialization.md).
Normalized SQL and constant routes remain general; nullable bags and aggregates
retain their separate interfaces. No default planner policy or wire format changes.

## Implementation and proof

The [header](../../include/crown/planner/keys.hpp) and
[implementation](../../src/planner/keys.cpp) use enforced FK/UNIQUE premises,
exact typed key terms and only ignored/private once-used non-key fields. A rule
needs a distinct live witness; sequential removals cannot erase an FK cycle's
final atom. Private-variable compaction preserves types, head order/repetitions
and original-ID maps. Original and reduced source identities stay distinct after
a nonempty rewrite, and the retained minimum certificate belongs only to the
reduced query. C05 uses its existing explicit physical-plan export bridge.

The existing runtime still retains and validates every source table. Referenced
parent updates cannot bypass constraints merely because their native alias route
is empty. Same-table self-FKs retain their surviving alias route. The original
general backend remains a comparison route; no second production runtime,
ranking cache, catch/retry framework or per-event optimization hook is introduced.
Source storage/constraint scans and cold guard/search/lowering work retain their
actual costs. P5's specialized algorithm and update bound are not selected.

The [design review](../../build/verification/v67-key-design-v1/requirements.json)
derives eleven literal requirement rows and the local proof obligations. The
[actual source review](../../build/verification/v67-key-source-review-v1/receiving.json)
reads both complete new production files. Its K-LIFE-01 finding is fixed: every
borrowed metadata accessor now rejects a temporary result. The factory borrows
its immutable input, preserving it even when compilation refuses resources.

## Actual native and installed-SDK validation

Both [Release](../../build/verification/v67-key-root-v1/release-checks-v1/receiving.json)
and [ASan/UBSan](../../build/verification/v67-key-root-v1/sanitizer-checks-v1/receiving.json)
build and execute the genuine registered unit/oracle commands. Each profile has
1,009 unit checks and 44 native oracle cases: 22 queries on both storage backends,
1,884 source events, 1,928 snapshots per execution route and 316 expected
constraint rejections. The independent Python/SQLite model materializes the full
original CQ and validates full source state and decisions. It does not compute
expected answers from the reduced program or native output.

The corpus distinguishes composite/reordered/empty keys, constants, repeated
terms, private/nonlocal variables, ordered/repeated/Boolean heads, untrusted
constraints/hints/statistics, source-ID/proof scope, self-FKs/cycles, referenced-key
updates, duplicate/absent events and scalar domains. Resource controls cover exact
and one-under guard work, search/lowering refusal, bounded sampled allocation
cuts, original-account exhaustion, abandoned preparation and result lifetime.
The [author receiver](../../build/verification/v67-key-oracle-v1/final-author-receiving.json)
receives actual source hashes and both raw native outputs; outputs are byte-identical.

An actual Release installation is moved to a prefix containing spaces. A public
consumer links `CROWN::keys` and `CROWN::runtime`, with `NDEBUG` and explicit
runtime checks. The [independent SDK receiver](../../build/verification/v67-key-sdk-review-v1/receiving.json)
matches all twelve held-out frames, including three rejected updates, and checks
423 compiler dependencies (one consumer, 55 SDK headers, 367 system paths), all
eleven linked SDK archives and all 271 unchanged SDK files. No original production
source/build or old installation supplies a compiler/archive dependency.

Initial attempts remain preserved. One unit source first failed strict compilation
for misleading indentation. An early fixture then assumed unselected plans used
zero guard work; classification/ID maps are charged even when search is skipped.
The fixture now supplies guard work and sets search work to zero. Its exact failed
preimage is retained, not reconstructed. Neither correction changes production
semantics. All final checks bind the corrected test sources and current compiler.

## Human inspection and source vintages

The current inventory is 868 maintained code/configuration paths: 476 primary,
including 393 production files, plus 392 tests/helpers. All 391 existing production
files retain exact V66 bytes. Only two new cold compiler files extend production;
the existing CMake and offline documentation helper changes have separate lineage.

Maps cover 866 files / 195,388 lines / 21,685 regions. All 18,439 nonblank regions
have usage contracts; 3,246 blank regions remain structurally described. The
20,926-record registry SHA-256 is
`ac7f826cc39c9db15396e4451dca91b25f1df98e7c7781f02641c15fe28f3488`.
There are 128 new contracts, 1,760 existing metadata rebindings (two routing
semantic amendments), and twelve citation-only record corrections for five
inherited stale reference strings. Correct targets are inspected by function,
not clamped to file ends. All 19,026 unrelated records remain exact. A shifted
helper scaffolding gap receives its own precise usage card.

The [final independent receiver](../../build/verification/v67-key-final-independent-v1/README.md)
checks every current binding, field, local path/range and nonblank region, along
with exact parent lineage and the actual selected native evidence. Generation and
checking pass, including 152,798 generated local links. Initial incomplete
candidate findings and their corrections remain versioned in that packet.

All 385 prior registered commands/properties are preserved; two checks bring the
current count to 387. This feature runs the two new registered commands per
profile, not the full 387-test suite. The actual V66 full 385 Release + 385
ASan/UBSan passes retain their exact source vintage. Original accepted R1/R2 images
remain preserved; this is separate successor source/SDK validation, with no new
release image accepted or performance claim from validation timings.

The implementation goal remains active: 71 tasks verified, one in progress and
six not started. Comparisons/difference may use ordinary propagation or exact
recomputation. Approximation, shared-query optimization and parallel/distributed
execution remain deferred; each query retains independent serial state/budgets.
