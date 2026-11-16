# Controlled workload measurement (B03)

B03 is verified; see the [acceptance record](verification/b03-measurement-acceptance-2026-11-11.md).
The runner verifies the manifested workload and every requested native
mode/backend before warm-ups or measured repetitions. It keeps raw records,
build/environment evidence and failure diagnostics. Harness acceptance alone
establishes no speedup, held-out ranking accuracy or full release qualification.

## Run a finite experiment

Build the public CLI, native collector and complete package library closure:

```sh
cmake -S . -B build/measure -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=ON
cmake --build build/measure --target crown crown_measure_workload crown_selection_runtime --parallel 4
python3 tools/run_measurements.py --source . --build-dir build/measure \
  --crown build/measure/crown --collector build/measure/crown_measure_workload \
  --case hidden_witnesses/delete_after_charged_load \
  --case self_join_2/adversarial_churn \
  --repetitions 3 --warmups 1 --sink file --output build/measurement-packet
```

The output directory must not already exist. Cases come from the
[checksummed workload manifest](../benchmarks/workloads/manifest.json), and
native-ineligible cases are rejected. Defaults cover all admitted cases,
reference/indexed storage and maintenance/snapshot/delta output. Repeat
`--case`, `--backend` or `--mode` to select a matrix. Each child is a new process
and each measured runtime starts with empty physical tables. Warm-ups replay the
same complete input; they are retained and labeled, then excluded from summaries.

The optional `--cpu N` pins each child to one CPU in the allowed mask; actual
collector affinity and thread count are recorded. The runner does not change
frequency governors or flush hardware/OS caches. It observes the environment
and reports those uncontrolled factors. A deterministic recorded schedule orders
configurations within each repetition. The native runtime has one writer.

`--codec jsonl|none` controls external collector encoding. `--sink discard|file`
selects consumption or exclusive POSIX file creation/writes. Files are not
fsynced. `--sink-delay-us N` inserts and measures a declared per-record wait;
it is a controlled sink mechanism, not a model of every external service.
`--observe off|counters|timed` and `--no-workload-counters` identify actual native
instrumentation settings. Optional observations disabled by configuration stay
disabled rather than becoming measured zeros.

Installation includes `share/crown/examples/workload-measurement`. Its CMake
project finds `Crown 0.1` and links the public `CROWN::runtime` target; no test
library or query registration is needed. Build it against a moved installation
with `-DCrown_DIR=PREFIX/lib/cmake/Crown` (adjust the library directory if your
installation uses another one). The controlled runner additionally requires
the original CMake build inventory, so an installed collector by itself produces
raw functional records, not a complete controlled experiment packet.

## Correctness and reproducibility

Manifest regeneration, file checksums, source classifications, license disposition
and independent assignment/SQLite oracles are checked first. The runner compiles
and validates each query/backend, binds JSONL input to the native canonical
catalog and runs a separate verification process for every output mode. It checks
initial/current rows and raw signed deltas against the independent oracle. A
failed preflight stops the packet before performance samples are collected.

Verification and measurement records bind physical plan, input and request
configuration hashes. Measurement requests retain the earlier verification
receipt. Immutable request/command/raw-output files identify each invocation.
The runner checks measured per-epoch output counts. JSONL file-sink output is
also compared with the complete oracle row multiset after timing. Discard and
codec-none trials use the separately verified configuration and measured counts;
they do not recheck every measured tuple payload. It never substitutes imported aggregate,
bag, cyclic or windowed source queries with an easier set query under the same
benchmark name.

Actual executable, C++ object, source/header dependencies, linked archive,
compile/link command, CMake cache and parser-build hashes are recorded. The
compiler binary/version, repository HEAD, worktree-change flag, harness source
hashes and dependency lock accompany that inventory. The controlled runner requires
both binaries from the supplied CMake build directory; collector compiler text
alone does not identify runtime archive flags. Source, recorded headers or
compiler flags newer than an object require recompilation. Objects newer than
their archive and link inputs/commands newer than a measured executable require
rebuilding/relinking that target. Each linked project target needs a nonempty
recorded compilation closure. These filesystem-time checks detect ordinary
stale builds; hashes and timestamps are not cryptographic lineage against
deliberately rewritten timestamps. This version requires Makefile compiler
dependency records. Loaded system libraries
are not archived. Kernel/CPU/memory, affinity, governor observations, allocator
context and relevant environment settings are retained.

## Timing and work boundaries

Query compilation is measured as the public CLI child process wall time,
including startup, file reading, SQL admission/proof/lowering and artifact
encoding. It is not C++ compilation. Exit detection uses a recorded2ms wait4
poll interval. Raw process CPU usage and Linux maximum RSS are separate records.

The native collector separately records file input, artifact decoding/independent
height proof, empty-runtime/reader/sink initialization and the processing loop.
Within every physical input epoch it records disjoint phases:

- Native EventReader decoding/validation.
- Native begin, preparation and commit. Delta mode includes private delta
  preparation/spooling here, before public output can be consumed.
- Full cursor setup and successful/exhausted cursor calls, or committed delta
  spool reads. Maintenance-only mode performs neither result enumeration nor
  per-row encoding/sink work.
- Collector JSONL encoding, sink write/wait, owning tuple/cursor release and
  committed epoch release.
- Input acknowledgment and separately recorded diagnostic capture.

Raw output-call records distinguish returned rows from termination.
`first_result_delay_ns` sums output setup and the first successful public next
call. It excludes native update/delta preparation, encoding and sink work; empty
epochs have no first-result sample. Full
snapshot requests occur after each committed physical update; the verification
process additionally checks the epoch-zero result. Query account memory and
operator counters are sampled outside active event timing. The loop wall time
also includes collector diagnostics and record storage between events. Final
workload capture, sink close, owner teardown and report encoding have explicit
boundaries; final JSON report encoding is excluded from native processing.

All loading remains input work from the empty state. Phase labels such as
`charged_load` preserve the workload's declared prefixes and contribute to total
work. Phase-specific totals are partitions/subsets; do not add them again to an
inclusive maintenance or loop total.

Mandatory epoch work and the O07 registry retain native counter names, units,
availability, saturation and overlap rules. Inclusive physical work already
contains lower-layer work. C01 cells preserve physical/support/degree counts,
histogram bins, descriptors and collection status. No static average is
substituted for a touched-bucket count, and annotation arithmetic is not enabled
by an exact-set benchmark.

## Memory, distributions and raw artifacts

Native account current/payload/allocation counts and cumulative requested-byte
peak are distinct from process RSS. The shared native grant includes admitted
runtime/program/reader state. Caller input streams, standalone compiler work,
explicit report/encoding DTOs and process overhead are outside it. A cumulative
peak cannot be subtracted to produce an independent phase peak.
Samples are taken at setup and completed processing boundaries; the final sample
precedes final workload export/teardown. Later diagnostic allocations are outside
that sample, so it is not the complete process-lifetime allocation peak.

The controlled runner uses GNU time's lightweight target child for
`process_maxrss_KiB`; the [format definition](https://www.gnu.org/software/time/manual/html_node/Memory-Resources.html)
describes target peak resident memory. Tool paths/hashes, actual launcher argv
and the per-command resource file/hash are retained. CPU affinity uses taskset.
Outer wait4 RSS remains `launcher_maxrss_KiB`, while its CPU usage describes
the owned launch chain. Wrapper wall time includes launcher startup and polling;
native phase clocks remain inside the collector.

Earlier wait4-only packets can inherit a large Python parent's pre-exec RSS.
Their RSS fields are historical launcher observations, not clean target-memory
curves. The B05 analyzer rejects them for current memory curves. It does not
relabel or rewrite old packets. A parent-buffer regression checks the corrected
target/launcher separation. The Python runner also stores raw report paths and
loads one repetition group for summaries, rather than retaining every parsed
configuration in memory. Extra summary reads occur after timing trials.

Raw event/cursor latencies, current/peak account samples and process maximum RSS
support later analysis. Nearest-rank p50/p95/p99, min/max, integer count/sum and
power-of-two histogram counts are exact empirical values. Mean and sample
standard deviation use floating arithmetic. Empty/singleton availability remains
explicit. These are finite observed distributions,
not confidence intervals, held-out accuracy or future guarantees. Warm-ups are
excluded from measured distributions but remain available for inspection.

`experiment.json`, `commands.json`, immutable requests, compiled artifacts,
bound input, raw stdout/stderr, resource records and optional sink files form the packet. The
[native record schema v2](../schemas/workload-measurement-v2.schema.json) and
[experiment schema](../schemas/measurement-experiment-v1.schema.json) are versioned.
The [historical raw v1 schema](../schemas/workload-measurement-v1.schema.json)
remains available. Raw v2 adds source/support arena slot, live, retained, pin,
free and exhausted counts plus derivation-key counts at each completed epoch.
The collector calls the existing native storage diagnostic after active timing
and acknowledgment. Its table/node traversal is included in diagnostics and
loop wall, outside native prepare/commit and output timings. Slot populations
are not slot-visit counters or allocator bytes. The request format remains v1.
An owned child exceeding its timeout is terminated and its command/failure
record is kept. Event/output-call/encoded-byte/report/command-count limits fail
honestly. `--max-total-bytes` bounds cumulative child stdout/stderr, checked after
each command; it excludes sink files and packet metadata. Encoded sink bytes have
a separate per-collector limit. Exceptions inside the protected trial loop mark
the partial packet failed when its manifest can be saved. Provenance/setup
failures before that loop, interruption or failed manifest writes can leave no
packet or an incomplete/running directory. Complete is published only after all
required gates, trials and summaries succeed. This is not a crash-safe packet
transaction. The [independent reporting argument](../build/verification/v02-measurement-review-v1/review.md)
records these boundaries.

This collector measures a volatile native core with a separately driven funded
EventReader. It has no WAL, checkpoint or durable sink synchronization. The
[existing CLI benchmark](cli.md) instead measures a durable-file workflow with
broader input/delivery clocks; those scopes cannot be pooled as one unlabeled
experiment. Real dataset acquisition/qualification, baseline reproduction,
B04 evaluation, [B05 stress acceptance](adversarial_scalability.md), C07 held-out
ranking and full release gates remain separate.
