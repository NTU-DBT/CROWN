# Root C05 allocation-count review

Root completed this review using its own model after the user requested less Astra
usage. No new compiler, binary, benchmark or component probe was run. Native
sources, test assertions and the execution freeze remain unchanged.

The retained C02 construction experiment measures five additional temporary string
allocations and frees for a default GuaranteeProfile under the held Clang/libstdc++
combination. Its vector-member controls split that effect as 1 + 2 + 2, with
request sizes 33, 28, 28, 29 and 52 bytes. That is a diagnostic construction
observation, not an allocator or peak-memory budget claim or a compiler-bug proof.

The current P08 Lowering builder creates one PhysicalPlan::Data per lower_tree or
lower_normalized call. Data owns one default GuaranteeProfile. Normalized replay
reaches the same single builder. C05 did not change either source file; their
current hashes match the fresh guarded integration capture and current freeze.
No historical source-manifest entries were re-evaluated for this review.

C02 slot assessment calls memory_score for every retained candidate. That path
lowers each candidate and retains its modeled_plan. C05 reuses the selected
modeled_plan; adding a depth assessment does not add another physical lowering.
Height and depth-only cold decisions lower one winner. A warm height decision
reuses the whole cached plan and lowers none. The direct fixture verifies three
retained candidates; the normalized fixture verifies one. Cache seeding precedes
the measured interval. Request, evidence-presence and origin fields explain the
intended cold misses; the warm case repeats its exact request and origin.

| Direct profile, in test order | Physical lowerings | Observed Clang increase |
| --- | ---: | ---: |
| Height policy | 1 | 5 |
| Depth policy | 1 | 5 |
| Slot policy | 3 | 15 |
| Dual assessment | 3 | 15 |
| Warm artifact | 0 | 0 |
| Current height | 1 | 5 |
| Current dual assessment | 3 | 15 |
| Total | 12 | 60 |

The three normalized profiles each lower once: increases of 5, 5 and 5, totaling
15. The two old C02 tests each lower three candidates and retain their observed
increase of 15. These independently source-derived multiplicities match every
current reported allocation difference; this is supported source attribution,
not a new instrumented C05 call-stack or machine-code measurement.

Each successful call first measures its own allocation count. The fault harness
then visits every position, requires the injected persistent failure to trigger,
checks the diagnostic class, complete owner/workload/candidate/proof state, old
owning results and cache/FIFO/statistics, then verifies a successful retry. The
Clang runs cover 33,026 direct and 20,435 normalized positions. Cleanup recoveries
stay zero, late-publication failures stay two, and the separate focused consumer
retains 22 positions, two publication failures and zero completed fault positions.
All nonallocation output, command, compilation and symbol checks passed in the
three completed independently audited configurations.

The root approval is restricted to the 26 exact observed comparisons in the
second preliminary matrix receipt: four old-test comparisons and 22 new-profile
comparisons. Both historical/preparation and cross-configuration comparisons are
listed separately. No future row, semantic change, byte/peak-memory assertion,
timeout change or generic compiler waiver is approved. The prior C02 approval is
historical evidence only; current approval has its own C05 freeze and content IDs.
