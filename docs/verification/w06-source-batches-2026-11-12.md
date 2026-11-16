# Prepared physical-source net batches: receiving checks

This W06 component adds a prepared physical-source command to the actual frozen
SqlRowsProgram. The [usage contract](../sql_rows_batches.md) describes expected
weight chains, final constraints, native staging, ownership and costs. The
separate single-row API keeps its immediate constraint behavior. Aggregate
coordination, durable outcomes, checkpoint/recovery and the operational batch CLI
remain required; W06 and the full Refactor goal remain active.

## Implementation and inspection

The source/key proposal retains only touched complete source rows and constraint
keys. It validates final UNIQUE/FK counters, including self/cyclic changes and
untouched children. It funds destination nodes, then stages all actual occurrence
decreases before increases through one native PendingEpoch. One source allowance
covers the command; the native epoch keeps its original retained allowance.
No full source/result copy, new production catch or separate undo log is added.

The token retains the SQL owner after facade movement/destruction. Commit and
rollback reset backing Data immediately. Root strengthened the new test to
measure released workspace while the closed facade still exists, then require
facade destruction to release no additional accounted bytes. A negative control
links the same receiving test against the preserved retaining implementation:
it fails at that exact assertion. The current implementation passes.

The production review supplies 37 additive and 45 keyed existing contracts.
All source/key methods have explicit usage, inputs/outputs, invariants,
ownership, failure, cost and references. The local prepared-publication protocol
is engineering for Refactor W06; it is not an additional paper theorem.

## Executed native gates

| Final source profile | Checks | Result |
| --- | --- | --- |
| Strict GCC C++23 Debug | sql_rows_binding, sql_rows_runtime, sql_rows_batch, sql_rows_oracle | 4/4 pass, 54.22 s |
| Strict GCC C++23 ASan/UBSan with leak checking | Same four checks | 4/4 pass, 65.23 s |
| Test-disabled production Release | Complete default build | Pass |
| Relocated installed Release SDK | Strict public consumer linked to CROWN::sql_rows | Pass; 216 installed files |

Assertions remain active in both test profiles. The new batch test takes
0.78 / 3.28 seconds in the final Debug/sanitizer runs. It exercises ordered and
indexed backends: exact expected-weight chains, final-only source caps, UNIQUE
swaps, nullable/composite/empty constraint keys, FK presence shares, self/cyclic
changes, hidden and filtered rows, aliases, native overflow with retry,
DISTINCT/EXISTS preview boundaries and unsigned delta magnitude above INT64_MAX.
Explicit result maps are independent of the runtime's source/key indexes.

The representative two-alias preparation measures its successful C++ new calls,
fails every covered allocation position, checks rollback and retries at the same
sequence. Exact source work succeeds; one structural unit less rejects the whole
command. Commit/rollback succeed with C++ new denied. Ownership checks destroy
caller cells/text and the runtime facade before committing retained state. The
installed consumer independently verifies copied text and retained output.
These sweeps cover their fixtures, not every possible allocation or workload.

The legacy-path cost probe uses the immutable v18 moved SDK as its actual
predecessor. Shared ownership adds a fixed 48 accounted payload/requested bytes;
facade size changes 40 to 16. Constructor and five ordinary single-row cases
preserve allocation/free/current-allocation counts, source/native work, source
weights and results. There is no latency, global-heap or portable ABI claim.

## Evidence and limits

Root recipes, archived terminal logs, source cohorts, native/SDK hashes and the
negative control live in build/verification/w06-source-batch-implementation-v1.
Recorder receipts named w06-source-batch-* preserve each command's input map and
terminal result. Final jobs have no in-command source drift. The first adoption
build was an old-mtime no-op; its correction is explicit and only later actual
compilation counts as new-source acceptance. Two negative-control setup failures
are retained separately from its successful regression check.

The source proposal, Luna test proposal and Luna production/block reviews are
immutable private packets. Root owns adoption, the prompt-close correction and
receiving execution. No new Astra review was used for this component. The full
327-test suite and a Clang gate were not run here. Read the
[inspection checkpoint](human-inspection-v19-2026-11-12.md) and
[handoff](../handoff.md) for current code-map coverage and the next actual work.
