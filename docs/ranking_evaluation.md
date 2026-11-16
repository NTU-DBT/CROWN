# Held-out baseline ranking evaluation (C07)

C07 is verified; see the [acceptance record](verification/c07-ranking-acceptance-2026-11-11.md)
and [finite held-out observations](verification/c07-heldout-observations-2026-11-11.md).
The native exporter and controlled runner retain the contract below. These
finite results establish no fixed speedup, global cost optimum or release claim.

## Generate and run

The checked-in `benchmarks/ranking` packet contains three SQL/catalog families
and15 traces. Regenerate into a new directory, or check its exact bytes:

```sh
python3 tools/generate_ranking_evaluation.py --check benchmarks/ranking
python3 tools/generate_ranking_evaluation.py --seed 20261112 --output build/new-ranking-split
cmake -S . -B build/ranking -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=ON
cmake --build build/ranking --target crown crown_measure_workload crown_export_ranking --parallel 4
python3 tools/run_ranking_evaluation.py --source . --build-dir build/ranking \
  --crown build/ranking/crown --collector build/ranking/crown_measure_workload \
  --exporter build/ranking/crown_export_ranking --repetitions 3 --warmups 1 \
  --output build/ranking-evaluation
```

Use `--pack build/new-ranking-split` for the generated alternate seed. Repeat
`--query`, `--backend` and `--mode` to choose a matrix. The default covers all
three queries, reference/indexed storage and maintenance/snapshot/delta output.
`--cpu N`, timeout/raw-byte grants and actual build provenance follow the
[B03 measurement contract](measurement.md). The output directory must be new.
No query class or handwritten native result oracle is registered.

The default codec is `none` with a discard sink. Snapshot and delta modes still
consume their actual native rows. Select `--codec jsonl --sink file` for external
encoding/writes and exact measured-file comparison after timing. Every candidate
uses the same declared output/backend/trace/memory/instrumentation context.
This is volatile native work, with no WAL/checkpoint/fsync.
The C07 default raw stdout/stderr grant is1GiB, checked after each child; large
snapshot call records remain raw rather than being dropped to fit a smaller
packet. Sink files and packet metadata have separate scopes as in B03.

## Split and information boundaries

The SQL and catalogs originate from the B02 Boolean path, three-leaf full star
and composite-separator definitions. Data is newly generated. Each query has
one training trace, one calibration trace and three evaluation traces:

- Fresh data with the calibration update mix.
- Fresh data with a different hot relation.
- Fresh data with a different hot relation and larger separator fan-out.

Every trace starts empty and charges all loading. Deletion/insertion pairs restore
membership; duplicate insertions commit no-op epochs and remain in weights and
timing horizons. A later phase changes the hot relation again. Rate shift here
means a relation update-mix change, not an observed arrival rate in Hz.

Physical tuple domains are disjoint across the five traces for each query.
Semantic event fingerprints are also distinct; source-feed names alone do not
establish independence. The same SQL family crosses roles: this is held-out
trace/data transfer, not unseen-query-family generalization. Each scenario has
one finite deterministic trace; repeated processes are runtime samples, not new
independently generated data. Native and SQLite/relational assignment evaluators
agree after every physical input, including raw signed deltas.

The native exporter receives only SQL, catalog, training JSONL and bounded
options. Its actual C05 calls choose height-only, committed-input-weighted native
depth and tuple/index slots. Exact rational proxy scores, decomposition, weights,
source cardinalities, native stops/constraints/fallbacks and selected artifact
hashes are recorded. No calibration/evaluation stream is supplied to that process.
The chosen plans are frozen before timing; measurements never replace a choice.

After all retained candidates pass independent verification on every split and
mode, calibration repetitions run first. A separate evaluation-layer affine
mapping is fitted from training proxy values and calibration costs. Its exact
coefficients and input pairs are frozen before evaluation warm-ups or samples.
Evaluation results cannot refit that mapping or change C05 choices.

## Candidate and proof boundaries

P06 independently proves the minimum native height. P07 supplies a finite checked
candidate family, with retained count, enumeration budget/stop and exhaustion
recorded. Reaching `--candidates N` does not establish exhaustion. Even exhausted
`exact_seed_residual_seed_normal_form_v1` is a declared family, not a search over
every possible physical implementation or a global minimum maintenance cost.
`--require-exhausted-family` asks C05 to reject an incomplete family. Optional
`--slot-limit N` uses the existing unitless slot constraint, never allocator bytes.
Native policy failures remain unavailable results with actual stop details.

Alternative artifacts use
[compiled-candidate-v2](../schemas/compiled-candidate-v2.schema.json). The original
height certificate keeps its original upper tree. The collector independently
rebuilds/validates the actual candidate and replays that unchanged certificate
against the same source. Equal candidate/proved height establishes the candidate's
minimum height; it does not replace the original witness. Ordinary O08 compiled
workflow v1 continues to require matching witness identity. The ordinary CLI
compiled-workflow reader remains v1; candidate v2 is an explicit collector input.

Any semantic/preflight/resource failure stops the experiment and preserves the
failed packet and raw command. The runner does not silently remove a failing
candidate and report a better regret against the survivors. Reported regret uses
actually verified/measured candidates and the policy's explicit eligibility set.

## Three separate quality reports

Search quality records the proved height, actual retained family, exhaustion and
work/stop counters. The cost-search scope always remains finite and explicit.

Runtime quality compares a frozen C05 choice with the best measured feasible
candidate in the identical context. Objectives are active-event nanoseconds per
physical input, native preparation plus committed-epoch-release nanoseconds per
input, and cumulative native query-account peak requested bytes. Raw frame/call
records, process RSS, warm-ups and between-run distributions remain available.
Loading and required cleanup are included. Epoch release can depend on output
mode, so these objectives are never pooled across modes.
Account peaks are sampled through processing boundaries, with the final sample
before final workload export/teardown; later diagnostic allocations are outside
that sample. They are not a whole-process peak or a phase-local subtraction.

Estimation quality reports held-out errors and proxy-order agreement against
those actual measurements. C02 height/depth/slots are not native nanosecond or
allocator-byte forecasts. The nonnegative affine mapping is an explicit analysis
assumption, with exact coefficients and calibration residuals; it does not enable
C03 in C05. Equal proxy values produce an intercept-only mapping with an
unidentified slope, rather than an invented coefficient. Error summaries retain
absolute/signed/squared/max errors; zero actual costs are excluded only from
relative-error denominators and counted explicitly. Zero best cost makes relative
regret unavailable. Pairwise ties and finite concordance are reported, without
statistical significance or confidence claims.

C03 event-cost modeling, C04 candidate adapters and C06 reoptimization are not
enabled by this baseline evaluation. Their future evaluations remain separate.
No claim of an optimal cost optimizer follows from agreeing with its own score,
having the proved height or winning one noisy finite run.

## Raw records and acceptance

`experiment.json`, `commands.json`, native exports, compiled candidates, immutable
requests, bound input, raw stdout/stderr, `choices-frozen.json`,
`calibration-frozen.json` and optional sink files retain provenance. Closed
[native export](../schemas/ranking-export-v1.schema.json),
[trace split](../schemas/ranking-trace-split-v1.schema.json) and
[evaluation packet](../schemas/ranking-evaluation-v1.schema.json) schemas describe
the interfaces. Build provenance additionally binds the native selection exporter
and selection libraries, not just the CLI and collector.

Compiler/sanitizer controls, moved installed examples, all15 selected fresh-source
tests and twelve requirement/provenance checks pass; see the acceptance record
for the final seal and exact scope. These small synthetic traces do not replace
B05 scale/churn experiments, external dataset/license qualification or full release
gates. Follow the [handoff](handoff.md) for the actual current checkpoint.
