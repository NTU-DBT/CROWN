# Adversarial scalability and historical-state experiments

B05 exercises input scale, fan-out, query shape, arity, skew, output demand and
history at a fixed live population. The [dated receiving report](verification/b05-adversarial-scalability-2026-11-14.md)
records the exact matrix, trend explanations and acceptance state; completion
of a batch does not by itself verify the B05 ledger gate.
The [B03 measurement contract](measurement.md) defines the actual clocks,
correctness gate, counters, byte account, RSS and failure boundaries.

## Reproduce a finite run

Use an explicit Release build. The runner requires a fresh output directory and
does not select or modify a private historical build.

```sh
cmake -S . -B build/b05-release -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF
cmake --build build/b05-release --target crown crown_measure_workload --parallel 2
PYTHONDONTWRITEBYTECODE=1 python3 tools/run_adversarial_scalability.py \
  --source . --build-dir build/b05-release --output build/b05-experiment \
  --suite all --repetitions 3 --warmups 1
python3 tools/analyze_adversarial_scalability.py \
  --packet build/b05-experiment --output build/b05-analysis
```

Optional `--cpu N` pins each measured target to a permitted CPU. Host frequency,
other processes and caches remain observed conditions, not controlled guarantees.
`--scale` and `--family` are repeatable selectors. Defaults use scales 1, 2, 4,
8; all 19 families; both storage backends; and maintenance, snapshot and delta.
Each of the 76 parameter points has a separate B03 packet, avoiding retention
of all raw report objects in one Python process. Cases run sequentially in a
deterministic hashed order. Three measured repetitions and one retained warmup
produce 1,368 measured reports and 456 warmups. A smaller selection has its
actual narrower scope; it is not relabeled as full B05 acceptance.

Each child verifies every requested backend/mode against independent results
before its timing trials. Measured JSONL file content is also checked. Loading,
output consumption, encoding and file-sink writes are retained with their actual
clock boundaries. Compilation and setup are separate; wrapper elapsed time is
not native update time. A failed child stops the batch nonzero and retains its
log. Setup/interruption can leave an incomplete directory; only a finished batch
receives complete status. There is no overwrite, automatic retry or recovery
framework for experimental packets.

## Axes and independent expectations

The [generator](../tools/generate_adversarial_workloads.py) emits checksummed
SQL, catalogs, ordered source events, independent per-epoch results and axes.
The shared [finite relational evaluator and SQLite](../tools/generate_workloads.py)
must agree at every epoch. A separate analytic final cardinality checks each
family. The [manifest verifier](../tools/verify_workloads.py) regenerates every
byte and admits only the named B02/B05 generator paths.

| Families | Variable and fixed controls |
| --- | --- |
| volume_full / volume_projected | 8, 32, 128, 512 complete physical rows; full head versus one projected key. |
| empty_intersection | 8–512 unmatched rows plus one nonmatching key; zero answers throughout. |
| fanout_full / fanout_projected | Three hot-key branches with 2, 4, 8, 16 rows each; final full output grows from 8 to 4,096 rows while projected output is one. |
| skew_hot / skew_balanced | Two branches with 8–64 rows each; one hot hub versus one hub per row. Output grows quadratically versus linearly, so demand must accompany time. |
| arity_1 / arity_8 / arity_32 | Fixed widths 1, 8, 32 across 16–128 rows. Compare widths at an equal size; scalar and encoded-byte work differ. |
| path_2 / path_4 / path_6 | Two, four, six native atoms across 4–32 rows per relation. Actual checked minimum height is read from the plan, not inferred from path length. |
| churn_fresh / churn_reuse | 16, 64, 256, 1,024 insert/delete cycles; eight stable live rows, nine transiently. Fresh historical keys versus one reused key; power-of-two no-op probes, final drain and empty probe. |
| churn_projected / churn_star / churn_path | Fresh hidden-witness churn at a shared parent key, a projected hot star and a four-edge projected path. Stable physical populations are 8, 9 and 12, respectively; each has one transient extra row. |
| churn_self_join | Three stable physical loops, four transiently; each update fans out to both occurrences, including the new/new self-join term. |

The longest projected-path churn trace has 2,084 events (singleton: 2,076).
These test a finite 64-fold history range,
not arbitrary history length. All inputs are nonnullable integer physical sets,
with exact projected set results. These families do not cover arbitrary SQL,
bags, aggregates, distributed execution or real datasets. Changing a head or
query shape can also change the admitted tree. These are mechanism stresses,
not a claim that only one runtime component differs; B04 ablations remain separate.
Synthetic-data and unresolved project-license dispositions remain in each manifest.

## Inspect work, historical slots and memory

The [analyzer](../tools/analyze_adversarial_scalability.py) joins pinned native
records to the exact live-source and output expectations. It checks event
identity, source population, slot partitions, returned rows, termination calls
and sink counts. Its scope is these relevant semantic/provenance checks, not
validation of every unrelated schema field.

`rows.csv` retains individual measured repetitions and raw report hashes;
`phases.csv` separates loading, churn, sentinel, drain and empty phases.
`counters.csv` retains selected per-layer units, availability, saturation and
includes metadata. `availability.csv` covers all exported metric names. Layers
overlap: their totals must not be added into synthetic CPU work. Disabled or
unavailable metrics are not zero observations. A zero-output dataset can still
require source preparation or validation scans outside selected abstract actions.

`probes.csv` pairs exact live counts with source/support arena slots, requested
bytes, cursor work and timings. Slot populations reveal retained historical
capacity; they do not count every visited tombstone. Full snapshots consume all
rows, so cursor startup/result/termination work and wall time remain visible
alongside slot counts. Compare sentinel probes at each family's fixed live state
across increasing history, then inspect final drained-state samples separately.
Unexpected trends need a source explanation or a recorded blocker.

Current requested/payload bytes and allocations belong to the native query
account; its peak is cumulative. Arena slots count records/capacity. Process RSS
includes input strings, raw-record vectors, observations and report/encoding
buffers held by the collector. Their growth is not interchangeable with native
state retention. Storage diagnostics call existing table/node counters after
active event timing; their cost remains in diagnostics and loop wall. No engine
instrumentation, state field, catch or update-path hook is added for B05.

The runner obtains target peak RSS through GNU time and retains outer launcher
RSS separately. Earlier wait4-only measurements can inherit the Python parent's
pre-exec high-water and are ineligible for these curves. Resource-file values
and hashes bind the corrected samples to their actual native command.
The [schema usage contracts](code_specs/schema_contracts.md) specify the allowed
generator paths, raw version, arena fields and their validation limits.

## Figures and interpretation

The [plotter](../tools/plot_adversarial_scalability.py) uses Matplotlib Agg and
writes standalone PNG/PDF figures. Install plotting dependencies into a separate
local prefix or virtual environment; the experiment process does not import them.
The recorded environment uses [Matplotlib 3.10.7](https://pypi.org/project/matplotlib/3.10.7/).

```sh
python3 -m pip install --target build/b05-plot-python matplotlib==3.10.7
PYTHONPATH=build/b05-plot-python MPLCONFIGDIR=/tmp/crown-b05-plot-cache \
  python3 tools/plot_adversarial_scalability.py \
  --input build/b05-analysis --output build/b05-figures
```

Figures show medians and observed min/max across repetitions, not confidence
intervals. Zero observations remain visible; unavailable samples remain missing.
Churn sentinel figures exclude drain/empty phases and use the largest selected
history. Tables and plots retain raw input hashes. No universal speedup,
asymptotic bound, allocator-byte prediction or external-baseline result follows
from this finite experiment.

The dated packet preserves the exact generator used in its run. A later
docstring correction changes the generator's self-hash and therefore newly
generated manifest hashes, while leaving its computation unchanged. Replaying
that historical packet requires its preserved source image; generating a new
packet uses the current source and records its own hashes. The successor record
and source overlay are linked in the receiving report.
