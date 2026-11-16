# B05 adversarial scalability and memory evidence

B05 is verified for this finite experiment and its explicit limits. Root
receives the native matrix, source explanations, independent raw audit and
corrected usage contracts. The full Refactor goal remains active.
The requirement is [Refactor.md, B05](../../Refactor.md), lines 1393–1395.
The [methodology](../adversarial_scalability.md) defines each axis and the
[B03 contract](../measurement.md) defines the clocks and resource boundaries.
These experiments are local implementation evidence, not a paper complexity proof.

## Exact experiment

The [root entry audit](../../build/verification/b05-adversarial-acceptance-v1/entry-audit-v1.json)
preserves the input barrier, source deltas, controls, receiving records and
source-specific successors. The [native packet](../../build/verification/b05-adversarial-native-v1/experiment.json)
contains 19 families × four scales × two backends × three modes: 76 parameter
points and 456 configurations. Each passes independent current-result and signed
delta preflight before one warmup and three measured repetitions. All 1,368
measured reports and 456 warmups finish successfully. Measured JSONL file sinks
are checked against independent relational/SQLite per-epoch expectations.

The [raw-derived tables](../../build/verification/b05-adversarial-acceptance-v1/full-analysis-v1/summary.json)
contain 456 groups, 1,368 individual rows, 3,528 phase rows and 3,888 probes.
The [50 PNG/PDF files](../../build/verification/b05-adversarial-acceptance-v1/full-figures-v1/manifest.json)
show medians and observed repetition min/max, not confidence intervals.
[Root trend checks](../../build/verification/b05-adversarial-acceptance-v1/root-trend-check-v1.json)
and the [114 endpoint comparisons](../../build/verification/b05-adversarial-acceptance-v1/root-trends-v1.csv)
are additional finite crosschecks; they do not accept themselves.

The recorded build is GCC 13.3.0 Release (`-O3 -DNDEBUG`, tests disabled),
x86-64 Linux/glibc 2.39, Intel Xeon Platinum 8259CL. Native targets use one thread
on CPU 0. Python is 3.12.3; source, compiler, binaries, objects, dependencies,
actual compile/link commands and launchers are hashed in each child packet.
Governor `schedutil`, cache state and other host activity remain observed or
uncontrolled. Points and trials run serially in deterministic hashed order;
the full matrix has no concurrent CROWN build/control job. Plotting runs later
with an isolated Matplotlib 3.10.7 prefix and recorded wheel hashes.

## Observations and source explanations

The following numbers are medians of three measured repetitions for
`indexed_chained_v1`; both backends and all modes remain in the linked tables.
Input loading is charged. Nanosecond scopes overlap where explicitly inclusive;
selected counter layers must not be summed into a synthetic total.

| Stress | Observed endpoints | Interpretation |
| --- | --- | --- |
| Empty intersection | 8→512 unmatched rows, no results; snapshot prepare/commit 46.2→37.4 µs/event; query current maximum 272,142→3,166,110 bytes; source slots 9→513. | Empty output does not mean zero work or state. Retained inputs/support consume memory. Selected support visits stay one/event; that counter is not all validation, allocation or CPU work. |
| Full volume | 8→512 rows; snapshot emits 36→131,328 rows across the loading trace; active time 78.1→705.0 µs/event. | Repeated full snapshots charge growing output demand. Snapshot prepare/commit itself is 32.0→21.2 µs/event; it excludes cursor/encoding/sink phases. |
| Hot full fan-out | 2→16 rows per branch, final output 8→4,096; delta prepare/commit 74.2→269.9 µs/event. Maintenance is 53.0→40.0 µs/event. | Delta stages enumerate and map accepted changes into the bounded owning spool before atomic publication. Complete delta preparation is output-sensitive even when selected lower-layer support work stays flat. |
| Projected fan-out | Same physical branch sizes, one visible result; delta prepare/commit 52.9→27.2 µs/event and one emitted delta row. | Projection changes the query and admitted plan. This tests witness collapse; it is not a component-isolating ablation. |
| Hot versus balanced skew | At 64 rows/branch: final output 4,096 versus 64; snapshot active time 3,837→217 µs/event when comparing hot to balanced. | The full traces emit 176,800 versus 4,096 rows. Skew and output demand both change; a claim about storage alone would be unsupported. |
| Arity | At 128 rows: widths 1/8/32 have snapshot prepare/commit 23.7/27.3/39.0 µs/event and query-current maxima 505,929/798,268/1,816,659 bytes. | Wider tuples require scalar/tuple storage and mapping work. No constant-width primitive is extrapolated to arbitrary width. |
| Path shape/height | At 32 rows/relation: 2/4/6 atoms have checked native height 1/2/3 and snapshot prepare/commit 45.2/58.8/79.6 µs/event. | Shape, atom count, live input volume and checked height change together. This is a height stress, not a causal height-policy comparison. |

The delta explanation follows
[accepted stage mapping](../../src/runtime/delta.cpp#L993),
[owning spool admission](../../src/runtime/delta.cpp#L809) and
[stage preparation](../../src/runtime/delta.cpp#L1160).
Collector [cursor, encoding and sink scopes](../../examples/workload-measurement/main.cpp#L205)
explain why native preparation and full active-event time have different trends.
The data do not establish a cause for faster per-event values at larger scales;
startup amortization, caches and host frequency are plausible influences, not
independently isolated effects. No backend winner or universal speedup is claimed.

The [independent raw audit](../../build/verification/b05-raw-receiving-review-v1/report.md)
hashes all 1,824 retained reports (7,016,550,036
bytes) against their child-run records and analyzer pins, then parses each final
C01 workload object. All counters-mode reports have complete/selected/committed
counts equal to their 6–2,084 event horizon, with no aborted, truncated,
saturated, invalid-descriptor or protocol-error flags. This checks that bounded
C01 detail was not silently truncated. The separate 79,344-row O07 availability
table contains 20,095,056 available and 1,895,760 disabled metric samples,
with zero unavailable or saturated samples. Five internal timing hooks are
disabled under counters mode, not observed zero-duration timings. The raw audit
uses direct O07 epoch checks on 11 report samples; it does not claim full-schema
validation of every other raw field. Its actual sample paths and hashes are in
[pins.json](../../build/verification/b05-raw-receiving-review-v1/pins.json), under
`fully_parsed_raw_json_samples`; the review's prose name `read-scope.json` is a
filename typo, corrected here without changing that completed packet.

## Historical state and the RSS correction

Six shapes exercise fresh keys, reused keys, hidden projected witnesses,
a projected star, a four-edge path and physical self-join occurrence fan-out.
History grows from 16 to 1,024 insert/delete cycles at fixed live populations.
The longest trace is 2,084 events. Across all 108 largest-scale
family/backend/mode/repetition series, source slots, support slots, query-current
requested bytes and cursor work are identical at every power-of-two sentinel
from cycle 4 through 1,024. The star first fills one reusable transient slot in
each of three tables: its source-slot sum reaches 12 by cycle 4, although its
simultaneous live population peaks at 10. This is per-table capacity, not a leak.
All 432 final empty probes have zero live source rows. Draining need not release
reusable arena capacity or reset cumulative allocation peaks.

Examples of stable indexed snapshot source/support slot populations are 9/28
for singleton churn, 9/4 for projected churn, 12/16 for the star, 13/40 for the
path and 4/45 for the self-join. Path snapshot cursor work stays 55 at all
sentinels. No rising history-driven event-time trend appears in these runs;
timings still have observed repetition noise. Slot counts are populations,
not direct counts of visited tombstones. Finite churn plus cursor work and
wall clocks cannot prove an unbounded no-history-scan guarantee.

Process RSS does grow. Singleton snapshot median target RSS is
13,324/22,496/60,120/209,180 KiB at the four history scales, while query-current
maximum stays 110,944 bytes and its cumulative peak stays 127,318 bytes.
The raw report grows from 747,806 to 28,562,779 bytes. The collector retains
[per-event records and observations](../../examples/workload-measurement/main.cpp#L151),
then constructs [frame JSON and the final encoded report](../../examples/workload-measurement/main.cpp#L259).
These caller-owned buffers are outside the query grant; process RSS includes
them, input buffering and allocator effects. This explains a concrete source of
trace-length memory growth; it does not assign every RSS byte to one owner or
claim the harness has constant memory. The runner also retains report paths
and loads one repetition group for summaries instead of all raw report DOMs.

An actual runner defect was fixed before this matrix: wait4 RSS could inherit
the Python parent's pre-exec high-water. A 96 MiB parent buffer changed the old
launcher measurement dramatically, even with direct posix_spawn. The corrected
[GNU-time resource probe](../../build/verification/b05-adversarial-acceptance-v1/rss-correction-probe-v2/result.json)
keeps target RSS at 8,708→8,740 KiB while outer launcher RSS grows
25,732→124,036 KiB. The runner now saves hashed target-resource sidecars and
labels launcher RSS separately. GNU time `%M` is target maximum RSS in KiB
([primary documentation](https://www.gnu.org/software/time/manual/html_node/Memory-Resources.html)).
Old wait4-only packets remain immutable and are not used for these curves.

## Code, specifications and validation

All 355 `apps/include/src` paths equal V47: no engine field, catch, hook or
update-path instrumentation was introduced. The example collector adds an
ordinary storage snapshot in diagnostics after acknowledgment and active timing.
[Storage sampling](../../src/runtime/physical.cpp#L707) visits logical tables/nodes,
not every historical slot; its actual cost remains in diagnostics and loop wall.
Raw report schema v2 carries that sample; request schema v1 and the original
raw-v1 schema retain their separate contracts. The generator, runner, analyzer
and plotter use direct bounded flows without retry/recovery frameworks.
Verification also collects and retains per-event statistics with zero collector
clock values; it returns before encoding event frames. The diagnostic sampling
therefore has a real preflight cost as well as a measured-run diagnostic cost.

The inspection map passes with 755 files /172,803 lines /19,462 blocks,
16,844 contracts in 14,413 blocks and zero selected callable/type/inline gaps.
This pass adds 51 contracts, amends 23 and removes three obsolete wrapper cards;
1,530 exact source-hash rebindings retain their original authors. Eight duplicate
or overlapping draft proposals are dropped. Four
[schema contracts](../code_specs/schema_contracts.md) use explicit JSON pointers.
The remaining 5,049 structural regions include 2,901 blanks. The bytes of all
2,148 remaining nonblank regions match V47; mapping is not semantic certification.
The [independent contract replay](../../build/verification/b05-contract-receiving-review-v1/review.md)
checks exact predecessor/postimage records, unique anchors, references, schema
pointers and original authors. Its five wording findings receive a separate
[correction check](../../build/verification/b05-contract-corrections-review-v2/review.md).
Root also incorporates that check's request-hash precision note: the binding
hash uses normalized request serialization with command/receipt fields omitted,
while the report copies the full request.

Focused controls pass 72 native configurations in Release and 72 under
ASan/UBSan across all six churn shapes. They cover independent results, actual
scaling, arena partitions/reuse references, v2 shape, transformed legacy-v1
compatibility, unknown-field rejection, preserved outputs and nonzero child
failure. Corrected B03 controls include target-RSS isolation, instrumentation
off, owned timeout and prior oracle/clock checks. C07 controlled ranking and
moved installed collector/exporter controls also pass (12 collector cases and
48 candidate/mode checks). All new terminal recorder receipts bind stable input
bytes. CMake preserves the previous 348 definitions and adds one B05 test;
349 registered tests does not mean a new whole-suite execution.
Each 72-configuration B05 control performs 72 correctness preflights and 72
measured collector executions, with zero warmups, plus setup/helper commands.

The exact benchmark input image is preserved under the root packet's
`experiment-source-delta-v1`, over unchanged V47 bytes. After all native and plot
jobs finish, one generator docstring is corrected to say it performs no output
writes; it does read source assets. Its
[successor record](../../build/verification/b05-adversarial-acceptance-v1/generator-documentation-successor-v1.json)
checks AST equality after removing docstrings and binds both versions. Newly
generated manifests include the new generator SHA; the retained measurements
belong to the earlier exact input image.

B04 component ablations, B01 external comparison environments, the project
license, B06 publication and release gates remain separate. These finite
nonnullable-integer physical-set experiments establish neither arbitrary SQL
coverage nor a native asymptotic time, delay, memory or external-baseline claim.
