# Query and trace corpus

[workloads/manifest.json](workloads/manifest.json) is the generated native corpus:
24 SQL definitions,144 trace cases, explicit semantics/head/structure/update/
backend/output contracts and checksummed inputs/oracles. See the
[workload guide](../docs/workloads.md) for reproduction and native replay.

[legacy/manifest.json](legacy/manifest.json) classifies13 pinned legacy labels
and116 scenarios without claiming builds or dataset replay.
[legacy/dynagox/manifest.json](legacy/dynagox/manifest.json) retains24 pinned
original aggregate SQL definitions and reviewed classifications; none is enabled
for native R1 timing. [external_imports.json](external_imports.json) binds source
packets and records missing real dataset/catalog/license contracts. Generated
synthetic names are separate from original benchmark names. The
[controlled measurement runner](../docs/measurement.md) uses admitted cases and
preserves actual output/storage modes, raw repetitions and preflight results.
B03's [harness acceptance passed](../docs/verification/b03-measurement-acceptance-2026-11-11.md).
A02 licensing and actual B04/B05 comparative/scalability evaluations remain open.

[ranking/manifest.json](ranking/manifest.json) contains the C07 disjoint trace
split:15 traces/916 physical events across three SQL families. The
[held-out evaluation](../docs/ranking_evaluation.md) preserves training choices,
calibration and actual measured-candidate regret/error records. Shared query
families across splits are explicit; this is not unseen-query generalization.
