# C07 finite held-out observations

C07 is verified; [acceptance](c07-ranking-acceptance-2026-11-11.md) records the
compiler/package/source-only gates and final audit. These observations come from the complete
[persistent development packet](../../build/verification/c07-heldout-acceptance-development-v2/controlled/experiment.json),
whose [independent acceptance](../../build/verification/c07-heldout-acceptance-development-v2.json)
passed240 preflights,576 retained runs and486 exact raw-cost/regret/error checks
in304.64s. They are finite measurements, not a fixed-speedup or release claim.

## Search and split

The three SQL families use freshly generated disjoint training, calibration and
three evaluation traces:15 traces/916 physical events. Evaluation includes an
unchanged relation mix, a different hot relation and increased separator fan-out.
Rows are disjoint across roles; SQL families are shared. Independent relational
assignment and SQLite results agree after every event. This is trace/data transfer,
not unseen-query-family generalization or multiple independently sampled datasets.

Native P06/P07 reports the following on both storage backends:

| Query | Proved native height | Retained checked candidates | Declared family exhausted |
| --- | ---: | ---: | --- |
| Boolean three-edge path | 2 | 3 | Yes |
| Full three-leaf star | 1 | 4 | Yes |
| Composite separator | 1 | 1 | Yes |

Family exhaustion covers `exact_seed_residual_seed_normal_form_v1`, not every
physical implementation or a global minimum maintenance cost. The composite case
is a single-candidate control: its zero regret supplies no ranking-discrimination
evidence. The high-fan-out star reaches720 full result rows; this bounded stress
does not establish a scalability curve.

## Choices and actual runtime

C05 chooses Boolean candidate0 for height/slots and candidate2 for training-weighted
native depth. It chooses candidate0 for all three policies on the star and
composite control. Choices, exact scores and artifact hashes are frozen before
timing. A different candidate is never substituted after observing evaluation.

The table shows relative active-event-time regret for the reference backend's
fan-out/rate-shift evaluation. Each cost is the mean of two measured complete
runs per candidate after one retained warm-up; all loading, enumeration, encoding,
sink writes and required cleanup remain charged according to output mode.
Comparisons stay within the same query, trace, backend, mode, memory grant and
instrumentation. Values are rounded percentages of the best measured feasible
candidate, not speedups over another system.

| Query / mode | Height-only regret | Weighted-depth regret | Slot-policy regret |
| --- | ---: | ---: | ---: |
| Boolean / maintenance | 0.00% | 7.15% | 0.00% |
| Boolean / snapshot | 0.00% | 5.83% | 0.00% |
| Boolean / delta | 0.00% | 4.82% | 0.00% |
| Star / maintenance | 0.00% | 0.00% | 0.00% |
| Star / snapshot | 0.27% | 0.27% | 0.27% |
| Star / delta | 0.00% | 0.00% | 0.00% |

For Boolean fan-out shift, weighted-depth requested-byte peak regret is19.30%
in maintenance/snapshot and18.99% in delta. This is measured native-account peak,
not process RSS, a slot-based byte forecast or a phase peak. No policy is changed
in response. The observation demonstrates why a training proxy and a proved
height do not establish actual optimal runtime or memory under a workload shift.
The cumulative account peak is sampled through the processing boundary, before
final workload export/teardown; later diagnostic allocations are outside that sample.
Differences can include finite-run noise; there are no confidence intervals or
significance claims. All other contexts and exact rational values remain raw.

## Estimation quality

C02 height, input-weighted depth and tuple/index slots remain unitless native
proxies. The report separately fits a nonnegative affine evaluation mapping from
calibration costs, freezes it before evaluation and reports actual held-out
absolute/signed/squared/relative errors and pairwise ordering. That mapping never
chooses a plan or enables the C03 maintenance-cost policy.

Equal height scores expose a rank-one design with an unidentified slope and an
intercept-only prediction. A zero slope under nonnegative fitting and an
unidentified slope are distinct. All calibration pairs, exact coefficients,
residuals, predictions and actual costs are retained; source timestamps/order and
frozen-file hashes prevent evaluation feedback. Native score agreement is not
used as runtime ground truth. The acceptance checker independently reconstructs
every measured objective and all486 regret/error comparisons from raw frames.

For the same reference Boolean delta/fan-out-shift context, held-out active-time
prediction error is:

| Proxy | Calibration design rank | Held-out mean absolute error | Mean absolute relative error |
| --- | ---: | ---: | ---: |
| Height | 1; slope unidentified | 6.900µs/input | 17.23% |
| Weighted depth | 2; fitted slope constrained to zero | 6.900µs/input | 17.23% |
| Tuple/index slots | 2 | 6.900µs/input | 17.13% |

The similar rounded absolute errors do not establish identical predictions or
identified event costs. In particular, a zero fitted depth slope does not change
the actual C05 weighted-depth choice. This is observed transfer error under the
declared mapping, not a validation of optimal CBO.

## Reproducibility and limits

The packet binds actual compiler/version/flags, source/header/object/archive and
binary hashes, dependency lock, hardware/affinity/thread/allocator context,
output configuration, schedule seed, warm-ups and repetitions. It measures the
volatile native core with external JSONL encoding and file writes, with no WAL,
checkpoint or fsync. Cache/frequency state is observed, not controlled. Artifact
validation and setup have separate clocks; active-event objectives do not include
the standalone compiler/export process. Shared training/selection setup is recorded
once and is not charged repeatedly to only one candidate.

The first full packet failed honestly at the512MiB raw stdout/stderr grant after
540 retained runs; it remains marked failed with its commands, raw data and
source preimages. The complete packet uses an explicit1GiB grant and retains
the per-call evidence. The larger grant does not alter correctness checks or
silently truncate output. Fresh integration/compiler controls validate methodology
and semantics; their timings are not pooled into this observation table.

C03/C04/C06 are not enabled in this baseline packet. B04 component attribution,
B05 scale/churn studies, external datasets/baselines, held-out query families and
full release reviews remain separate. See the [methodology](../ranking_evaluation.md)
and [handoff](../handoff.md) for current acceptance state.
