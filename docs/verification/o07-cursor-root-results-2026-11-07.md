# O07 cursor observation root results — 2026-11-07

The excluded cursor proposal passes the independent suite and ASan/UBSan/leak
checks. O07 remains not started until native integration; the final composed
report and full native matrix remain separate acceptance gates.

Subject package: `5dcd916bda78bbe1bef6047a65b4a1fa7ef6ad405ee54877c8033b818d3b8259`.
The accepted [independent fixture revision](o07-cursor-observation-test-fixture-proposal/README.md)
has source SHA `e3a83de87c2cca64b0de5590984523dd36f48d4e8a0c27c6bd8a58208d659a2b`
and checker SHA `61920761b7159e4bfdcbe22372aa1c69b783adf78ba79dc8ae1c8bfe2003491e`.
Its strict test object and matching complete nine-runtime-unit archive use the
same CROWN_RUNTIME_TESTING headers; no older Runtime ABI is linked.

## Accepted coverage

Root [attempt 2](../../build/verification/o07-cursor-observation-acceptance-attempt-2.json)
passes **1,133 C++ checks**, then the independent standard-library JSON verifier
accepts **52 actual cursor snapshots and ten committed-state gauge snapshots**.
All 100 pinned inputs/objects/archives match before and after. C++ execution
takes 0.115s and the checker 0.044s.

The suite covers all seven required subject groups, with twelve emitted
completion markers: registry; independent A04 rows/scalar routes; three/eight-way
generalized factors; five observation configurations; epoch sources and rollback
invalidation; cursor lifecycle/work caps/startup failure; persistent OOM and
same-owner recovery; detached facades and QuerySession; exact configuration,
mode bootstrap and generation saturation; nested delta clocks and unsampled
trace; exact-zero/backward clocks; literal committed gauges/private-state guards.
No factor cardinality is promoted to a full join-result count. Off and counters
retain zero optional clock reads. An immediate delta interval reconciles with
its own delta reads plus the nested-cursor subset; later current-result cursor
reads are checked separately and do not relabel the older attempt.

The [sanitizer build/run](../../build/verification/o07-cursor-observation-sanitize-attempt-1.json)
rebuilds all nine runtime units plus exporter and accepted independent test,
using strict warnings, ASan/UBSan, matching sanitized native dependencies and
leak/halt-on-error options. C++ passes in 0.596s, the checker in 0.044s, and the
complete build/run/check takes 77.581s. All 105 pins remain unchanged. Session
`57837` is terminal and closed. Raw logs are
`build/verification/o07-cursor-observation-{acceptance-attempt-2,sanitize-attempt-1}*`.

## Preserved failed preparation and limits

Attempt 1 and its original frozen package remain unchanged. It passed preceding
groups but failed the last gauge fixture: inserted edge (3,30) was called
unmatched even though existing edge (20,3) makes a new join answer. The accepted
revision consistently substitutes truly unmatched (99,100) for prepare,
rollback, insertion, no-op and deletion, retaining every literal A04/gauge
assertion. It also prints per-group completion after restoring test overrides.
No implementation source changed to resolve this test-data failure.

The allocator injector remains armed through cleanup/recovery, but covers the
first startup/next allocation rather than every possible cursor allocation
position. Earlier native exhaustive cursor fault sweeps remain required in the
full matrix. These focused numeric reports do not claim user-string UTF-8 or
Graphviz rendering coverage. Total allocator bytes, hard deadlines, durable
checkpoints/recovery/delivery and the complete 78-card goal remain open.
