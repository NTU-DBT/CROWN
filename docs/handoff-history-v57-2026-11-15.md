# CROWN continuation handoff — V57

Original goal ACTIVE. Ledger:63 verified /1 in_progress (A02) /14 not_started=78.
B01 technical acceptance is progress, not completion of Refactor or release gates.
[V56 history](handoff-history-v56-2026-11-15.md) preserves the exact previous handoff.
Current seal: build/verification/human-inspection-v57-progress-v1.json.
Frozen source: build/verification/human-inspection-v57-source-v1.
Postcheck: build/verification/human-inspection-v57-postseal-check-v1.json.
Root packet: build/verification/legacy-baselines-v57-v1.
Parent V56 SHA256:
b602abea5cf1d6aedc7ff2c05b69b079ad6752286aa5ab3aa4a4ac4eaf168f43.

The [B01 record](verification/legacy-baselines-v57-2026-11-15.md) and
[guide](legacy_baselines.md) receive isolated unchanged Scala/Flink and C++ CROWN
baseline builds. All64 Scala and144 C++ files Git-blob match original pins.
Scala Java8 compile/package pass; the published OutputResultTest FAILS in its
stale tuple parser and stays unchanged. Independent adapter/checker passes22
snapshots/18signed records. All375 main class bytes match the accepted replay
and both packaged JARs. Package explicitly skips tests and is not a suite pass;
no Main-Class or shaded-runtime replay is claimed.

Scala qualification is the original L3 process function plus real full drains
after EVERY event. Its iterator can change global-alive markers, so do not infer
delta-only/maintenance-only, Job routing, windows or MiniCluster correctness.
The separate helper changes no legacy algorithm. C++ Release crown_exec passes
line5cd10 distinct-count milestones and line5gc22full+22replacement milestones.
Replacement records are absolute current counts, including8zero removals, not
signed deltas. Other fixed queries stay unqualified. line5cd ignores signs;
exclude deletes/delta there. Both baselines use floating-point/epsilon behavior;
tiny integer correctness is not general arithmetic certification. C++ VmPeak
is not RSS and the diagnostic leaks handles at milestones; exclude unreviewed
long-milestone/timing/memory uses. No performance comparison was performed.

Private completed baseline prefix: build/legacy-baselines-v57-v1. Treat its
sources, dependency caches, toolchain and build/output files as immutable after
acceptance. Reproduce into a NEW directory. Reuse binaries read-only; put new
replay inputs, JVM user/tmp directories and outputs in a new packet. Separate
sealed packets:
v57-b01-scala-recon-v1, v57-b01-cpp-recon-v1,
v57-b01-independent-review-v1 and v57-b01-spec-proposal-v1.
All their jobs are terminal. The parent entry audit passed all4701 source paths,
104425protected artifacts and46375external pins. Its wording-only initial and
whitespace retry failures remain alongside corrected pass; source hashes were
already verified and were not needlessly recomputed for the wording correction.

All370 production paths stayV56 bytes. Full-source receiving covers427 primary
paths; retain425 prior reads and receive3changed+2new primary files. New tests,
traces/captures have separate inspection. Current362 registered CTests include
one new offline checker. Debug and sanitizer configurations each pass2selected
checks, plus the new test in a fresh sourcecopy; production testsOFF configure
passes. No new full362-test or legacy C++ sanitizer claim. The current checker
has4actual-capture passes/24negative controls; review fixed unobserved graph tails
and Python-only numeric spellings. Earlier receipts remain supporting versions.

Maps:788files/179848lines/20105blocks; all17144nonblank blocks have19579contracts,
2961blank regions. V57 adds24cards, rebinds1578CMake/generator/checker attachments and
amends3inventory cards; rootcorrected12proposal fields for exact phase/region/cost
scope and1sectionreference. The final documentation checker inventory mismatch
was fixed with the same exact Scala-helper admission; its failed check is
preserved. The Scala helper uses2generic chunks, not Scala AST regions. Existing45
numeric CMake refs stayunchanged. New code is optional offline verification;
there is no engine update hook, retained row/index graph or runtime error layer.
No new Astra was used; parallel workhorse/Luna reviews and root receiving remain
separate evidence. Full source/block/link/native scopes are not proof equivalences.

Next: B04 component evaluation under unchanged Refactor requirements, then B06
reproducible report. Dependencies B03/C07/B01 are verified. Plan complete ablations
(storage, generic/specialized runtime, generalized nodes, height/cost policies,
statistics, batching), matching semantic/output demand and charging setup once.
These tiny baseline qualifications do not authorize unverified large workloads
or turn private diagnostic times into benchmarks. Check whether each baseline
query maps to the new engine's admitted surface before comparing performance;
retain unsupported/exact/approximate and static/dynamic distinctions. B05 keeps
its finite prior cohort. Complete Refactor/release/X-extension work stays open.

Preserve completed packets/frozen source/private SDKs/dependencies/.git.
HEAD e369a623517723b3be3ea3e9806779f3c591e7f9; no AGENTS found.
Every exec_command requires require_escalated; set PYTHONDONTWRITEBYTECODE=1.
Revalidate seal/pins/ledger/native quiescence before new work. Main mutable builds
remain build/w05-debug, build/w05-sanitizer, build/inspection-build-scope-off-v1.
Coordinate source freezes before builds/install/source-copy jobs. Preserve all
rights/notices; license checks remain deferred, not a technical blocker. Keep
each query's state/results/progress/budgets independent. Comparisons/top-k/
difference may use standard propagation or exact recomputation. Approximation,
shared-query algorithms and parallel/distributed engine execution stay deferred.
Use own model power, parallel agents, Astra Max sparingly and Luna Max for simple
work. Never promote A02 or the full goal on B01's acceptance alone.
