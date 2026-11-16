# Planned S04 measurement, without an executed result

The goal is to identify the actual S02 bottleneck and assess the proposed
replacement on the same typed operation traces. There is no claimed speedup,
observed count or benchmark acceptance in this draft. Root owns eventual
compilation and execution after implementation authorization.

## Separate correctness, mechanism and timing runs

Use a deterministic operation tape with independently computed expected
membership and projected buckets. Both real ReferenceTable and the optimized
primitive consume the same tape, with distinct owners. Verify the canonical
state after each update in correctness runs; timed runs use the already
accepted tape and checksum the complete final state outside the timing region.
Do not time an independent model or wrapper and label it actual S02 execution.

Report compiler identity, optimization, assertions, sanitizer flags, CPU/run
environment, trace seed, tuple/key widths, populations and all configured caps.
Compare ordinary builds with the same optimization and instrumentation profile.
Sanitizer results establish memory/undefined-behavior safety separately; do not
compare an unoptimized sanitized run with optimized ordinary timing.

Run full logical/probe counters separately from an optional uninstrumented
timing profile, preserving identical trace and result checks. ReferenceTable
does not currently expose hash/probe counters; mark absent reference metrics
unavailable rather than fabricating them from a model. Any new reference
instrumentation requires its own source/overhead audit and cannot silently
replace the untouched oracle. Allocation tracing, if used, is another explicitly
instrumented profile; its timings are not uninstrumented throughput.

## Concrete trace families

| Family | Controlled change | What it exposes |
| --- | --- | --- |
| Primary lookup | Hit/miss/duplicate mix at fixed population; integer, string and Decimal values | Lookup and scalar preparation cost, including current Decimal formatting allocations |
| Secondary lookup | Distinct-key counts from one nullary/shared key to one key per row | Startup cost and exact fan-out dependence |
| Live traversal | Empty, one-row and small live populations after a large high-water population | Capacity/tombstone scans hidden by favorable density |
| Churn | Repeated erase/insert at fixed simultaneous population with fresh logical IDs | Recycled node shells, released payloads and historical-ID growth |
| Growth boundary | One insert immediately below/at/above each declared load threshold | Array preparation, admitted rehash work and stable payloads/order |
| Collision stress | Ordinary typed hashes and a separate private forced-collision profile | Distribution assumptions, chain-work charging and exact collision handling |
| Wide keys | Repeated/reordered projections, long NUL/high-byte strings and 38-digit Decimals | Field/byte costs that a count of dictionary operations would hide |
| Index lifecycle | Add/drop an index at fixed live population; independently equal versus shared Projection tokens | Complete index build/reverse-link work and idempotent registration semantics |
| Journal retention | Many disappearing/reappearing keys followed by commit or rollback | Private empty-key load, retained nodes/pins and bounded finalization |

Choose a finite population ladder that fits both backends' declared limits,
with empty and small literal cases included. Use the same deterministic seeds
and operation tapes across configurations. The final benchmark proposal must
pin concrete ladder values, distributions, warmup/repetition counts and tapes
before execution; this design does not cherry-pick those parameters after
seeing timings. Report repeated samples and spread, and keep cases in which
the optimized primitive loses.

## Read the evidence at its actual scope

Record live rows/keys/memberships separately from directory slots, free shells,
retained journal nodes, arena high-water slots and pins. Check logical
conservation equations after each correctness operation. Current component
counts do not establish allocator live/reserved/peak bytes or S05 budgets.
Transient overlapping rehash arrays belong to a separately disclosed temporary
population, even when a committed capacity limit is respected.

For live cursor steps, pair source inspection with exact step/visited-node
counters at a large capacity and tiny live population. A wall-time curve alone
does not prove absence of scans. For primary/bucket startup, show the actual
collision and scalar-width dependence. For growth, separate a slow admitted
rehash from ordinary probes and state the successful-sequence amortization
assumptions. Resource rejection is a recorded outcome, not discarded noise.

If the selected S04 scope includes runtime integration, repeat representative
typed Support/Physical/Delta/Session traces through the actual opt-in backend.
Keep preparation, propagation, delta enumeration, public output and cleanup
separate. A storage microbenchmark does not establish an end-to-end runtime
speedup, D05 wall-time bound or C03 calibration. Existing C01 observation
overhead measurements answer a different question and are not reused as S04
index-performance evidence.
