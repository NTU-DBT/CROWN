# V66 exact snapshot top-k review

X05 uses the ordinary exact recomputation route authorized in
[Refactor.md](../../Refactor.md). The optional `CROWN::topk` library collects a
genuine SQL row/bag or aggregate snapshot, sorts its compressed entries and
selects at most `k` logical rows. Read the [usage and cost contract](../topk.md)
before calling it. SQL `ORDER BY` and `LIMIT/OFFSET` admission remains separate.

## Implementation and literal requirements

The [public header](../../include/crown/runtime/topk.hpp) and
[implementation](../../src/runtime/topk.cpp) define the complete operator.
Requested fields compare in their declared directions and NULL order, followed
by identity ascending with NULLS FIRST. Row identity is the complete nullable
output tuple; aggregate identity is the complete group key, including omitted
output keys. Ranking uses actual rendered SQL values, including declared-scale
AVG rounding. Equal displayed aggregate values never merge distinct groups.

Bag copies stay compressed. A cutoff uses `min(remaining, multiplicity)` without
expanding rows or summing whole-result cardinality. DISTINCT and EXISTS retain
their genuine one-row weights; empty global aggregates and false EXISTS outputs
are collected from their actual producers. Updates are observed through the next
snapshot, with no cached ranking state or update hook.

Both overloads validate readiness and rank metadata before opening a producer.
`k=0` opens no producer and allocates no candidate/result storage. A single finite
producer grant and a separate shared sort/selection balance cover their stated
logical work. All native candidate/result storage uses the original account.
Private vectors and existing reader leases give failure cleanup without a new
catch, retry or rollback framework. Returned immutable tuples and program handles
retain ownership after runtime teardown.

Full collection and comparison sorting require candidate space proportional to
the compressed snapshot, plus existing producer/image costs. A compact selected
vector retains only selected identities. This is a local snapshot-sort design;
P10's specialized algorithm and delay bounds are not selected. It adds no work to
ordinary query updates and makes no measured speedup claim.

The [independent design review](../../build/verification/v66-topk-design-v1/final-readiness-v1.json)
checks all eight literal readiness rows. The
[final contract receiver](../../build/verification/v66-topk-final-independent-v1/receiving.json)
checks current source bindings, usage fields and parent-record lineage.

## Actual validation

Both [Release](../../build/verification/v66-topk-root-v1/release-tests-v2/receiving.json)
and [ASan/UBSan](../../build/verification/v66-topk-root-v1/sanitizer-tests-v2/receiving.json)
rebuild the actual library and run the registered unit and oracle commands.
Each profile reports 50 unit controls, 14,300 ranked snapshots across 26 native
cases and both storage backends, and 2,480 independent SQLite ordering checks.
The exact Python model uses integer/Fraction/date/byte ordering and quantizes AVG
before ranking. Huge symbolic bag weights are never expanded. Captured requests,
independent expectations and raw native outputs are retained in each packet.

Discriminating ties include groups whose unranked displayed SUM order opposes
their identity order, and distinct AVG values that both render as 1.00. Resource
and ownership controls cover candidate/producer/sort/account denial, exact and
one-under sort grants, allocation cuts, lease cleanup, compact retained capacity,
busy owners, zero grants and result survival after owner teardown.

A separately installed SDK is moved to a prefix containing spaces. An external
consumer finds `CROWN::topk`, compiles, links and executes six held-out SQL frames.
The [independent SDK receiver](../../build/verification/v66-topk-sdk-independent-v1/receiving.json)
matches all frames to SQLite/Fraction expectations and checks 417 compiler
dependencies, all 15 linked SDK archives and all 268 unchanged SDK files. The
consumer uses explicit runtime checks that remain active under `NDEBUG`.

Initial attempts are retained: building before reconfiguration found no new
target; reconfiguration resolved that setup error. Initial unit fixtures used
NUL/invalid-UTF8 TEXT outside the existing SQL domain; the author corrected the
fixtures and both profiles then passed. These are not relabeled as successful
initial runs or as production fixes. The reconstructed first fixture preimage
is explicitly labeled reconstructed in the author packet.

The [full-scope successor review](full-scope-review-v66-2026-11-16.md) records
whole-suite execution, current inventory and review depth separately. Original
R1/R2 release images retain their historical source points; this feature review
does not assemble or accept a new release image. The broader implementation goal
remains active.
