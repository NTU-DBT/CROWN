# V68 full-scope correctness review

No new actionable correctness defect was confirmed. This review receives all
868 maintained code/configuration paths, including 393 production files and
392 tests/helpers. All production bytes are unchanged from V67: 389 retain the
[V65 full or targeted semantic review](full-scope-review-v65-2026-11-16.md), two
implement [V66 snapshot top-k](snapshot-topk-v66-2026-11-16.md), and two implement
[V67 guarded keys](key-specialization-v67-2026-11-16.md).
The [current lineage inventory](../../build/verification/v68-full-review-root-v1/source-lineage.json)
binds every path and hash. Full scope includes inherited, source-identical review
arguments and fresh targeted reading; it does not mean a fresh every-line reread
or a universal correctness proof.

## Findings and source arguments

| Review | Fresh inspection and limits |
| --- | --- |
| [Root source review](../../build/verification/v68-full-review-root-v1/README.md) | Catalog/scalar premises, frontend admission/normalization, lowering and compiled metadata, planner authority, window/session lifetime, observations, CLI and packaging. Exact source windows are recorded separately. |
| [Runtime review](../../build/verification/v68-full-review-runtime-v1/README.md) | Nullable SQL bags and final-state constraints, weighted projections, aggregate arithmetic/publication, cold rebuilds, top-k, source/alias barriers, cursor and session ownership, independent queries. |
| [Storage/recovery review](../../build/verification/v68-full-review-storage-v1/README.md) | 48 freshly read files and 8,948 lines within a 194-file inventory: original-account allocation, scalar ordering/hash, arena pinning, indexed undo, file uncertainty and input/recovery boundaries. Unread ranges remain explicit. |
| [Planning review](../../build/verification/v68-full-review-planning-v1/README.md) | Checked upper versus original exact authority, independent certificate replay, residual repair, candidate/cache publication and same-owner allocation-stop resumability. It does not re-prove recurrence completeness. |
| [Bounded Astra key monitor](../../build/verification/v68-full-review-key-monitor-v1/review.txt) | Complete reading of the two new key files; independent guard, sequential witness, head/remapping, proof-scope and failure-ownership argument. Inherited runtime/lowering premises are identified. |
| [Mechanical receiving](../../build/verification/v68-full-review-integrity-v1/README.md) | All 4,911 entry-time live/frozen source pairs agree with V67. Current source/specification bindings and guide links pass. Hash agreement is not semantic proof. |

For a key removal, the enforced FK supplies a parent row whose key values match
the surviving witness terms. Other parent fields are ignored or private
existential variables outside the head. Every remaining assignment therefore
extends to the removed atom without changing its output. Sequential use counts
and distinct live witnesses make removals compose; reversing the recorded steps
reconstructs witnesses removed later. The last atom of a cycle cannot disappear.
Head variables survive in a live key witness or block removal. Compaction copies
types, aliases and ordered/repeated outputs. The complete source catalog survives
lowering and runtime after-state enforcement, including referenced-only tables.
Reduced-query minimum evidence stays scoped to the reduced query.

The inspected runtime paths fund private state/output before publication and
retain original-account row ownership through returned results and reader leases.
SQL aggregates distinguish group existence, non-NULL counts and signed sum
cancellation. Final-state checks avoid rejecting valid replacements for transient
arithmetic/constraint states. Top-k performs exact snapshot collection and sorting
with explicit NULL order and complete identity ties. Planner resource stops and
checked upper bounds do not become an original-query optimum.

Two investigated distinctions are existing contracts rather than defects.
Standalone logical aggregation may retain an explicitly supplied immutable
compiler account; SQL composed owners freeze into their receiver. Legacy local
file recovery may explicitly discard an unauthenticated incomplete suffix after
the complete validated prefix. The partial-tail discriminator in the storage
packet was authored but not executed and supplies no runtime finding.

No production refactor or new exception framework was justified. Existing
rollback, borrowed-token lifetime, reader cleanup and uncertain-I/O boundaries
retain their documented roles. Source constraint scans, ordered dictionary and
scalar-width work, atomic output preparation/spooling, cleanup and snapshot sort
remain real costs. Neither finite tests nor paper citations establish a new
constant update/delay or wall-clock performance claim.

## Actual current-source validation

Both complete builds pass. The actual
[Release suite](../../build/verification/v68-full-regression-v1/release-suite-v2/receiving.json)
and [ASan/UBSan suite](../../build/verification/v68-full-regression-v1/sanitizer-suite-v2/receiving.json)
each pass all **387 registered tests: 774 executions, zero failures or skips**.
Exact JUnit names match registrations. All 868 code/configuration hashes match
before/after build and suite, and registrations/build metadata remain unchanged.
This is a fresh full current-387 run; V66's full 385-test profiles and V67's two
targeted checks retain their historical source points. The initial V68 suite
runner lookup stopped before CTest; its corrected producer binding and both
actual completed runs remain separately recorded.

The current specification checker passes for 866 files, 195,388 lines and 21,685
regions, resolving 152,798 generated local links without errors. All 18,439
nonblank regions have usage contracts; 3,246 blank regions retain structural
descriptions. The 20,926-record registry remains byte-identical to V67, SHA-256
`ac7f826cc39c9db15396e4451dca91b25f1df98e7c7781f02641c15fe28f3488`.
The final guide audit receives this report and the successor handoff separately.

The [root receiving record](../../build/verification/v68-full-review-root-v1/receiving.json)
joins current code, source reviews and completed native profiles. No new release
image is accepted; original R1/R2 archives and closed evidence remain unchanged.
X03 star proof/fixture preparation is unimplemented work and is not accepted by
this review. The overall implementation goal remains active at 71 verified,
one in progress and six not started. Approximation, shared-query optimization
and parallel/distributed execution remain deferred; each query remains an
independent serial owner.
