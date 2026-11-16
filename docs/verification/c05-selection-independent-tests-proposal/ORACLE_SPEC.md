# Independent C05 fixture expectations

These expectations were authored from the accepted design, literal row maps and
the reviewer's earlier accepted C02 public fixtures before reading C05 selection
implementation bodies. P06/P07 factories supply every proof and snapshot. No
test creates a Selection, current wrapper or Evidence through a private factory.

The Boolean CQ is R(x), S(x,y), T(y), with no output variables and exactly the
three height-two retained shapes: native S root; generalized x root; generalized
y root. Initial sources are R={(x)}, S={(x,y)}, T={(y)} and the answer is {()}.
Removing the sole S row removes the answer; restoring it restores {()}. Ninety
duplicate R inserts, five duplicate S inserts and five duplicate T inserts are
100 committed physical no-ops. Occurrence depths are respectively (2,1,2),
(1,1,2), (2,1,1), giving literal numerators 195, 105, 190 over denominator 100.
The retained candidate-local slot proxies are respectively 24, 32, 32.

| Slot cap | Feasible shapes | Depth policy C05 choice |
| --- | --- | --- |
| 23 | none | No selection; all three checked |
| 24 | native S | native S, although complete C02 depth assessment picks x |
| 31 | native S | native S, although complete C02 depth assessment picks x |
| 32 | all three | generalized x |

Equal R/S/T counts give numerators 5/4/4 over 3; full structural key orders the
x/y tie. Reversing the 90-count table to T gives 195/190/105. Prefix snapshots
stay prefixes; exhaustion is never inferred from a selected shape or cache hit.

The normalized alias case uses an unused table plus r(x,flag,payload), physical
rows (1,1,a),(2,0,b), and SELECT DISTINCT a.x FROM r a JOIN r b ON a.x=b.x WHERE
a.flag=1. Its literal output is {(1)}. Three duplicate r inserts, two absent r
erases, and two unused-table no-ops give denominator 7. Both aliases have native
depth one, so the numerator is 10; unused-table depth contribution is zero.
Source cardinality is the two physical r rows, not the one filtered answer.

The Decimal case has two physical rows sharing one projected value, only one
passing the Decimal constant, and two repeated output positions. It has one
height-one candidate, exact output {(value,value)}, and Q=13. A populated
nullary projection of three unary rows has Q=4; the unary projection has Q=14.
Their empty sources have Q=0. A zero-node constant true/false operator has Q=0
and respectively one empty answer/no answer. These cases prevent confusing
zero-width, zero-row and zero-node populations.

Actual owners establish current capture. Pending/released boundaries cannot be
bypassed by height fallback. Valid off/empty census can use an explicitly
configured primary fallback; a mandatory slot cap cannot. A resource, unsupported
model, allocator-byte constraint, source mismatch or lowering stop publishes no
selection and changes no cache. Old factory-produced results remain owning
history through updates, reset, mode changes, moves, rebuild, clear and drop.

Cache expectations are exact-key, bounded FIFO: no hit reordering, no insertion
on read-only misses, successful-only counters, all-or-nothing admission/eviction,
and fresh current proof/snapshot/evidence on hits. Raw tree order/IDs remain key
material even when P07 structural keys agree. Full-field mutation coverage is
recorded separately; byte-only encoding does not grant proof or cache authority.

For two complete assessments, aggregate preparation is counted once. Complete
public usages and delegated ceilings must reproduce the declared P + sum(V-P)
relationship with separately nonnegative C05 overhead. Fixed synthetic resource
accounting exercises the same algebra without creating semantic authority.
Exact/one-under boundaries use the actual successful measured usage, and every
shortfall must remain a resource stop even with fallback enabled. Timing-off
usage is zero; previously untimed preparation is explicitly unmeasured when a
later caller requests a timer. No allocator or wall-clock bound is inferred.

Focused fault probes target early, middle and final allocation positions of an
actual current selection that would evict a FIFO entry, and of a warm hit. They
complement the producer's full sweeps. Measurements and persistent-failure
assertions are separate. Full canonical owner state, workload metadata/cells,
cache statistics/order and retained old result are compared after each failure
and retry; no expected allocation count is hardcoded.

No source-level implementation defect or execution result is asserted by this
oracle document. All compilation and execution is reserved to root.
