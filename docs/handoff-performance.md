# Performance hand-off: compact kernel and allocation header

This document hands over a performance effort on branch `review/native-v73`,
committed on top of `2291c1e` (which differs from `3b8c931`,
the commit the work started from, only in the review report). It is separate from the project hand-off in
[handoff.md](handoff.md), which records the verification and delivery state of
the full implementation; leave that file as it is. The earlier independent
review, [verification/review-2026-11-20.md](verification/review-2026-11-20.md),
lists confirmed efficiency problems that overlap with this work and should be
read alongside this document.

Terms used throughout:

- *Flink baseline*: the original Scala/Flink implementation of CROWN on git
  branch `master`, run as described in [Target and baseline](#target-and-baseline).
- *Existing runtime*: the C++ engine of this repository, `DeltaRuntime` over
  `SupportRuntime`, with its two storage backends, *reference* (`ref`, ordered
  `std::map`, the default) and *indexed* (`idx`).
- *Compact kernel* or *kernel*: the new fast-path engine
  `crown::runtime::compact::Runtime`.
- *Edge update*: one `+` or `-` line of an edge stream. In the compared queries
  every relation reads the same edge table, so one edge update changes three
  (L3) or four (L4, Star) relations.
- *Batched* and *one call per update*: the kernel's two ways of being driven,
  through `apply(std::span<const Update>)` with up to 1024 updates per call, or
  through the word-level `apply` once per update.
- *Cold* and *warm* Flink: a fresh JVM per timed run (the paper's method), or
  in-process repetitions after the JIT compiler has warmed up.

## Status summary

**How the kernel compares with the Flink baseline.** The stated goal is a C++
engine 20x to 50x faster than the Flink baseline. On the paper's three
self-join queries (L3, L4, Star), two stream kinds (insert-only and sliding
window) and three modes (maintenance only, full enumeration, delta
enumeration), measured on the same machine with the paper's own timer, the
kernel's speed-up factors are:

| Edges | Kernel entry point | Against | Range | Median | Cells below 20x |
|---|---|---|---|---|---|
| 1,000,000 | batched | Flink cold | 19.5 to 59.7 | 23.2 | 5 of 18 |
| 1,000,000 | one call per update | Flink cold | 11.3 to 52.0 | 16.3 | 11 of 18 |
| 1,000,000 | batched | Flink warm (cells measured) | 15.9 to 40.6 | 18.7 | 6 of 10 |
| 100,000 | batched | Flink cold | 26.5 to 71.6 | 34.9 | 0 of 18 |
| 100,000 | one call per update | Flink cold | 26.6 to 73.7 | 35.2 | 0 of 18 |
| 100,000 | batched | Flink warm (cells measured) | 13.4 to 59.5 | 21.2 | 9 of 18 |

What meets the goal and what does not:

- At 100,000 edges every cell is at or above 20x against cold Flink, with
  either entry point.
- At 1,000,000 edges, batched against cold Flink, 13 of 18 cells are at or
  above 20x and 5 are just below it: L3 insert-only maintenance 19.9x, L4
  insert-only delta 19.9x, L4 window maintenance 19.9x, L4 window delta 19.5x,
  and L4 insert-only maintenance, shown as 20.0x in the table but just under
  20 before rounding. All five are within 3% of 20x, which is inside the
  run-to-run noise: an earlier run of the whole matrix on the same build
  (apart from the batch validation added afterwards) differed per cell by -6%
  to +7% and had 3 cells below 20x. So for L3 and L4 the target is met only
  at its lower edge. Star is 30.5x to 59.7x; four Star cells exceed 50x.
- At 1,000,000 edges with one call per update, 11 of 18 cells are below 20x.
  This is the fair figure if one compares like with like on how many updates
  the engine may see in advance (Flink processes one element at a time).
- Against warm Flink the goal is not met in most cells: 6 of the 10 measured
  1,000,000-edge cells and 9 of 18 100,000-edge cells are below 20x.

The full tables and the caveats are in
[Like-for-like comparison with Flink](#like-for-like-comparison-with-flink) and
[How to read the comparison](#how-to-read-the-comparison).

**The existing runtime is slower than Flink.** Replaying the same L3 streams
at 100,000 edges, `DeltaRuntime` needs 19 to 94 microseconds per edge update,
against Flink's 4 to 10 (see
[Existing runtime on the Flink streams](#existing-runtime-on-the-flink-streams)).
This is why the work went into a separate kernel.

**The kernel.** It interprets the same lowered `PhysicalPlan` as the existing
runtime, stores every value as one 64-bit word in slabs behind open-addressing
hash directories, keeps the members of every join key in one contiguous array,
and performs no heap allocation per update in steady state. Its result deltas
are checked after every update against `DeltaRuntime` by a differential test.
It is a prototype: no rollback, no checkpoint image, set semantics only, no
aggregates.

**Allocation header.** Separately, the per-allocation header of
`resource::MemoryAccount` was shrunk from 95 to 48 bytes of framing, which
lowers every accounted byte figure of the existing runtime.

**The work is committed on this branch and not merged.** The kernel is not
wired into the CLI, `QuerySession`, recovery or the SQL sessions; only its
test and two benchmark drivers use it.

## Target and baseline

The target is stated by the owner as "20x to 50x more efficient than the Flink
baseline". The Flink baseline is the original Scala/Flink implementation on git
branch `master`, under `crown/` (the engine) and `experiments/` (the scripts and
data tools used for the paper's experiments). It is not built by this
repository's CMake project. "Efficient" is now read as time per edge update on
the paper's own metric; memory is reported beside it but was not part of the
stated target.

### How the baseline was measured

This section is the record of the baseline measurement. There is no
`REPORT.md`; the raw data, scripts and logs are in the untracked build area
`build/flink-baseline/` (not part of the repository): per-run JSONL files and
the summaries `results/summary_real.csv` (cold runs) and
`results/summary_driver.csv` (warm runs) under `results/`, the machine
description in `results/environment.txt`, and `REPRODUCE.sh`.

- **Code.** The unmodified Scala process functions of `git master` (`crown/`,
  identical to pin `e369a623517723b3be3ea3e9806779f3c591e7f9`), run as the real
  Flink 1.13.5 job in a local MiniCluster with parallelism 1.
- **Environment.** Apple M5 Max (18 cores), 64 GiB, macOS 26.6.1, JDK Temurin
  25.0.3 with G1, heap `-Xms8g -Xmx8g`. No CPU pinning (macOS does not allow
  it); the machine was shared with other work.
- **Workarounds**, neither of which touches the sources or the POM: Scala
  2.12.21 instead of the POM's 2.12.7 (`-Dscala.version=2.12.21` on the `mvn`
  command line, because 2.12.7 cannot read JDK 17/25 class files), and
  `--add-opens` for `java.base/java.lang` and `java.base/java.util`.
- **Metric.** The paper's own `AccumulateTime`: time spent inside the keyed
  process function (`BasedProcessFunction.processElement`). It excludes file
  reading, parsing, serialization, shuffle, JVM and MiniCluster start-up and
  the sink. It includes JIT warm-up and garbage collection of that run.
- **Cold and warm.** Every timed run is a fresh ("cold") JVM, as in the paper;
  the reported figure is the median of 5 runs at 100,000 edges and of 3 runs at
  1,000,000 edges, after one discarded pass. "Warm" figures are in-process
  repetitions of the same functions through Flink's operator test harness, with
  the JIT compiler warmed up; the median of later repetitions is reported. Warm
  figures exist for every 100,000-edge cell and for 10 of the 18
  1,000,000-edge cells.
- **Queries.** L3 = G1(A,B) JOIN G2(B,C) JOIN G3(C,D); L4 = a chain of four;
  Star = R1(A,B) R2(A,C) R3(A,D) R4(A,E). All aliases read one directed edge
  stream and all variables are output. StarCnt (a COUNT with GROUP BY) was also
  measured, but the kernel has no aggregates, so it is not compared.
- **Unit.** One edge update = one `+`/`-` input line = 3 (L3) or 4 (L4, Star)
  relation updates.
- **Streams.** Synthetic, seed 42, a uniform random directed graph with
  vertices = edges/4. `ins_*`: every edge inserted once, plus one final `*`
  (enumeration trigger). `win_*`: the paper's sliding count window of 0.2N
  edges (N inserts and N deletes, 10 `*` triggers), byte-identical to the
  output of the original `CountWindowPreprocessor`.
- **Modes.** `maint`: maintenance only. `full`: the paper's `crown` task,
  which enumerates the whole result at each `*` and drops it. `delta`: the
  paper's `crown_delta`, which enumerates each update's result delta and drops
  it.
- **Correctness of the baseline.** Result row counts for L3, L4 and Star were
  checked against an independent Python reference in all 12 size/stream
  combinations.
- **Noise.** Typical run-to-run spread is about +-5%; drift across a session
  up to about 10%.
- **Sensitivity (L3, 1,000,000 edges).** JDK 17 instead of 25: +-5%.
  ParallelGC instead of G1: 2% to 11% faster. SerialGC with 1 CPU (the closest
  to the paper's single pinned core): 50% to 77% slower.
- **Flink memory at 1,000,000 edges.** Maximum RSS 5.7 to 8.5 GiB. Retained
  heap after a forced GC in mode `full`: insert-only 1.38 (L3), 1.87 (L4), 2.09
  (Star) GiB; window peak 0.60, 0.90, 1.33 GiB.
- **Deviations from the paper.** An Apple laptop instead of a server with 500
  GB, one pinned core and a 128 GB heap; JDK 25 instead of 8; Scala 2.12.21
  instead of 2.12.7; a synthetic uniform graph instead of the SNAP graphs; no
  `--n` filter; parallelism 1 only; the SNB, dumbbell and projection queries
  were not run.

### Existing runtime on the Flink streams

`crown_stream_bench` (see [benchmark drivers](#4-benchmark-drivers-and-build-wiring))
replayed the L3 100,000-edge streams through `DeltaRuntime`, one repetition
per cell. Times are ns per edge update; the Flink column is the cold figure of
the same cell from the comparison tables below.

| Stream | Mode | Engine | Edge updates | Result rows | DeltaRuntime ns | Accounted end / peak MiB | Flink cold ns |
|---|---|---|---|---|---|---|---|
| ins | maint | idx | 100,000 | 0 | 22508.5 | 830.7 / 830.7 | 4678 |
| ins | maint | ref | 100,000 | 0 | 37526.0 | 731.2 / 731.2 | 4678 |
| ins | delta | idx | 100,000 | 1,591,230 | 70990.8 | 1077.0 / 1077.1 | 10481 |
| ins | delta | ref | 100,000 | 1,591,230 | 93585.5 | 977.6 / 977.7 | 10481 |
| win | maint | idx | 200,000 | 0 | 19147.6 | 34.9 / 171.7 | 4119 |
| win | maint | ref | 200,000 | 0 | 37998.3 | 28.4 / 151.2 | 4119 |
| win | delta | idx | 200,000 | 331,602 | 33665.4 | 34.9 / 193.6 | 5251 |
| win | delta | ref | 200,000 | 331,602 | 54881.1 | 28.4 / 173.2 | 5251 |

The existing runtime is therefore 4.6x to 10.5x slower than cold Flink on
these streams (DeltaRuntime ns divided by Flink cold ns per row).

## What changed in this work

All pieces are in the one commit that adds this document. `git status` also
shows an untracked `.DS_Store` at the repository root; it is not part of this
work and was left out of the commit.

### 1. Compact allocation header (`src/resource/memory.cpp`, modified)

Every allocation charged to a `MemoryAccount` is one `::operator new` call with
a header (`MemoryAccount::BlockData`) in front of the payload. Before this
change the header was 80 bytes (seven pointer-sized fields, two one-byte enums
padded to 8, and a 16-byte `MemoryAttribution`), followed by an 8-byte back
pointer just below the payload and `max(alignment, 8) - 1` bytes of alignment
allowance. For an ordinary allocation (alignment at most 8) that is 95 bytes of
framing; for alignment 16 it was 103.

The new header ([memory.cpp:78](../src/resource/memory.cpp#L78)) is 48 bytes:
`owner`, `previous`, `next`, `payload_size`, `attribution_id` (8 bytes each),
then `payload_offset` (4 bytes), `alignment_log2`, `purpose`, `lifetime` and
`attribution_kind` (1 byte each). The raw size, the alignment and the payload
address are no longer stored; they are derived
([raw_size at line 111](../src/resource/memory.cpp#L111)).

Placement works as follows:

- When the requested alignment is at most `__STDCPP_DEFAULT_NEW_ALIGNMENT__`
  (16 on the supported 64-bit platforms), the payload starts directly behind
  the header. There is no slack and no separate back pointer, because the
  header size is a multiple of that alignment and `operator new` returns
  storage with that alignment.
- The 4 bytes at `payload - 8` always hold the header-to-payload distance. For
  an adjacent payload these bytes are the header's own `payload_offset` field;
  a `static_assert` in `allocation_bytes` pins that `payload_offset` sits
  exactly 8 bytes before the end of the header. `BlockData::of(payload)`
  ([line 105](../src/resource/memory.cpp#L105)) reads them to find the header.
- An over-aligned payload lies at least one default alignment further on, and
  [allocate](../src/resource/memory.cpp#L269) writes a copy of the distance
  just below it ([line 301](../src/resource/memory.cpp#L301)). The allowance
  for this case is `alignment - 16`.
- `allocation_bytes(bytes, alignment)`
  ([line 116](../src/resource/memory.cpp#L116)) now returns
  `48 + slack(alignment) + max(bytes, 1)`. Alignments above 2^30 are now
  rejected with `MemoryFault::overflow`
  ([line 125](../src/resource/memory.cpp#L125)) because the stored distance is
  32 bits wide.
- `check_invariants` ([line 404](../src/resource/memory.cpp#L404)) checks the
  stored distance, the payload alignment, the derived raw size and the
  header-from-payload lookup instead of the old back pointer.

Consequences:

- Every "requested bytes" figure drops by 47 bytes per default-aligned
  allocation (55 for alignment 16). Allocation counts are unchanged. On the
  synthetic benchmark workloads bytes per stored tuple of the existing runtime
  fell by 21 to 27 percent.
- Code that preflights sizes through `allocation_bytes` (for example
  [session.cpp:1602](../src/runtime/session.cpp#L1602),
  [delta.cpp:831](../src/runtime/delta.cpp#L831),
  [accounted_row.cpp:247](../src/storage/accounted_row.cpp#L247),
  [batch.cpp:114](../src/io/batch.cpp#L114)) stays consistent because it calls
  the same function.
- Documentation still describes the old framing:
  [memory_accounts.md](memory_accounts.md) speaks of the "header and alignment
  allowance" without the new layout, and the code-spec card
  [code_specs/files/src/resource/memory.cpp.md](code_specs/files/src/resource/memory.cpp.md)
  describes "header+back-pointer+padding" and the old `BlockData` fields and
  line ranges.
- Any golden output that pins absolute accounted byte counts will change. None
  failed among the tests that run on macOS; Linux-only tests were not run.

How to verify: read the diff (`git diff src/resource/memory.cpp`); build and run
the full suite (see [Test and verification status](#test-and-verification-status));
on a Linux machine, run the full suite in Release and under the `sanitize`
preset, and look for golden files with absolute byte counts.

### 2. Compact kernel (`include/crown/runtime/compact.hpp`, `src/runtime/compact.cpp`, new)

A separate engine for tree-routed plans; its design is described in
[Compact kernel design](#compact-kernel-design) and its limits in
[Kernel limits](#kernel-limits). The public API
([compact.hpp:65](../include/crown/runtime/compact.hpp#L65)):

- Construction from a `PhysicalPlan` and `Options`
  ([line 28](../include/crown/runtime/compact.hpp#L28)):
  `memory_limit_bytes` for the kernel's own `MemoryAccount`, and
  `shared_separators` (default `true`), which lets tree edges whose separators
  range over the same source columns share one separator table (see
  [Shared separator rows](#shared-separator-rows)). It is purely a layout
  choice; `false` gives every edge its own table.
- `apply(table, operation, const Row&, sink)`
  ([line 80](../include/crown/runtime/compact.hpp#L80)): one physical set
  update given as owning values. Returns `false`, changing nothing, for a
  duplicate insert or an absent erase. With a sink, every result row that
  enters or leaves the output is reported once; without one only the state is
  maintained. This is the only entry point for SQL-normalized plans.
- `apply(table, operation, std::span<const Word>, sink)`
  ([line 84](../include/crown/runtime/compact.hpp#L84)): the same update for a
  row that is already encoded. An `int64` is its own word, a `bool` is 0 or 1,
  and any other scalar is the word that `encode(const Value&)`
  ([line 85](../include/crown/runtime/compact.hpp#L85)) returns.
- `apply(std::span<const Update>, sink)`
  ([line 91](../include/crown/runtime/compact.hpp#L91)): the batched entry
  point. Each `Update` ([line 59](../include/crown/runtime/compact.hpp#L59))
  names a table, an operation and a pointer to the encoded row. The effect, and
  the delta rows and their order, are exactly those of one word-level `apply`
  per update; the return value is the number of updates that changed the
  state. Knowing later updates lets the kernel start their memory loads early
  (see [Batched lookahead](#batched-lookahead)).
- `enumerate(sink)` for the full result, `has_answer()`, `result_arity()`,
  `decode(words)`, `statistics()`, `memory_statistics()` and
  `check_invariants()`.

Rows are delivered to a `RowSink` as `result_arity()` encoded words that are
valid only during the call. The header comment of `compact.hpp` points at this
document.

How to verify: run the differential test (item 3).

### 3. Differential test (`tests/unit/compact_runtime_test.cpp`, new)

The test lowers 23 query shapes with `planner::minimum_tree` and
`planner::lower_tree`:

| Shapes | Notes |
|---|---|
| `hierarchical_full` | Q(x,y,z) :- R(x,y), S(x,z) |
| `path3_full`, `path3_prefix`, `path3_middle`, `path3_boolean` | three-atom path, full / prefix / middle-variable / Boolean head |
| `path4_full` | four-atom path |
| `star3_full`, `star3_projected`, `star3_center` | three-atom star |
| `self_join_path2`, `self_join_path3` | the same table used two and three times |
| `self_join_path4`, `self_join_star4` | the Flink experiments' L4 and Star shapes: every alias reads one edge table |
| `self_join_path3_prefix`, `self_join_star3_projected` | self-joins with a projected head |
| `wide_separator_full`, `wide_separator_reordered`, `wide_separator_self_join` | three-column tables joined on two columns: full head; the two columns in a different order on each side with a projected head; a three-alias self-join |
| `disconnected_projected` | Q(a,c) :- R(a,b), S(c,d) |
| `repeated_constant_ignored` | R(a,a), a constant and an ignored column |
| `ignored_with_derivations` | Q(a) :- R(a,_), S(a,c): several source rows project to one record |
| `strings` | string columns and a head variable repeated in the output |
| `branching_projected` | five atoms, a branching tree, projected head |

Each shape runs with seeds 1 to 3 and 1,200 random inserts and erases (600
when the oracle runs on the indexed backend) over a small domain (3 to 5 values
per column). A second pass runs the six self-join shapes,
`branching_projected` and `strings` with domain 24, and the three
`wide_separator` shapes with domain 7, all with seed 7 and 4,000 updates
(1,500 with the indexed oracle); the wider domain gives keys with many members
and many keys with one, so arrays grow, shrink and move between size classes
and the directories and slabs are rebuilt several times.

Three kernels are driven per run:

1. `fast`, through the `Row` entry point with a delta sink. After every update
   its delta must equal `DeltaRuntime`'s signed delta as a multiset, and the
   oracle's delta sign must match the update. Duplicate inserts must return
   `false`.
2. `quiet`, through the word-level entry point without a sink (values encoded
   with `quiet.encode`).
3. `batched`, built with `shared_separators = false`, which replays the whole
   history, including the refused duplicate inserts, through the batched entry
   point in batches of 1 to 37 updates. It must accept the same number of
   updates and report the same delta rows in the same order as `fast` did.

Every 97 updates and at the end the full result, the Boolean answer and
`Runtime::check_invariants` of `fast` are compared with the oracle; at the end
the same is done for `quiet` and `batched`. `fast` and `quiet` must have equal
`Statistics`, and `batched` must too except for `separator_keys`, the one
figure that depends on the layout. Finally every live row is erased (each
second erase must return `false`) and `fast` must report zero source rows,
records, survivors, separator keys and visible keys.

It is registered as ctest `compact_runtime` and `compact_runtime_indexed`
(oracle on the indexed backend), compiled with `-UNDEBUG`, with a 1800 s
timeout. The binary prints the number of compared records, counted as the
number of oracle delta rows plus one per update.

Results are in [Test and verification status](#test-and-verification-status).

How to verify: `ctest --test-dir build/release -R compact_runtime --output-on-failure`.

### 4. Benchmark drivers and build wiring

Two single-thread drivers, neither of which is a test.

[benchmarks/kernel/stream_bench.cpp](../benchmarks/kernel/stream_bench.cpp)
(target `crown_stream_bench`) replays an edge stream in the original
experiments' file format, so that its result can be set beside Flink's
`AccumulateTime` for the same file. Usage, from its header comment:

```
crown_stream_bench QUERY FILE MODE [ENGINE [REPS]]
  QUERY   l3 | l4 | star            (every alias reads the one edge table G)
  FILE    lines `+,src,dst`, `-,src,dst` and `*` (full-enumeration trigger)
  MODE    maint | full | delta      (as in the Flink baseline)
  ENGINE  cmp (default)  compact kernel, batches of BATCH (environment,
                         default 1024) updates between two `*` lines
          cmp1           compact kernel, one word-level call per update
          ref | idx      DeltaRuntime on the reference / indexed backend
  REPS    timed repetitions, each on a fresh engine (default 5)
```

The file is parsed and encoded before the clock starts; the timed region
covers engine calls only (the apply calls and, in mode `full`, the
enumerations), which is the same boundary as `AccumulateTime`. Each repetition
constructs a fresh engine, so the kernel's time includes the growth of its own
storage. The output line gives edge updates, triggers, result rows, refused
updates, the median and range of the repetition times, ns per edge update, and
accounted end and peak MiB. The `ref` and `idx` engines run with all work
limits removed and observation off.

The stream files are under `build/flink-baseline/` (untracked). Example:

```
./build/release/crown_stream_bench l3 <path to ins_1000000 file> maint cmp 5
./build/release/crown_stream_bench l3 <path to ins_1000000 file> maint cmp1 5
```

[benchmarks/kernel/kernel_bench.cpp](../benchmarks/kernel/kernel_bench.cpp)
(target `crown_kernel_bench`) is the earlier synthetic driver. Usage:

```
crown_kernel_bench WORKLOAD ENGINE N MODE
  WORKLOAD  qh | line3 | star       (three separate tables, no self-join)
  ENGINE    ref | idx | cmp
  N         rows loaded round-robin over the relations
  MODE      delta (drain every signed delta) | maint (state maintenance only)
```

It pre-generates distinct integer rows (join keys drawn from `N/4` values),
loads about N rows, then runs a FIFO churn of `max(1000, N/4)` steps (override
with the environment variable `CHURN`), each erasing the oldest row of one
relation and inserting a fresh one, and finally enumerates the full result. It
prints load time per insert, accounted bytes and live accounted allocations
per stored tuple, per-update insert and erase time with accounted allocations
and global `operator new` calls (the driver replaces `operator new` only to
count calls), and time per enumerated row. The kernel is driven through the
`Row` entry point, one call per update, so its times include encoding.

[CMakeLists.txt](../CMakeLists.txt) changes: `src/runtime/compact.cpp` is
appended to `CROWN_RUNTIME_SOURCES`
([lines 122-123](../CMakeLists.txt#L122)), and the two driver targets, the test
executable, the two tests and their 1800 s timeout are added inside
`if(BUILD_TESTING)` ([lines 866-877](../CMakeLists.txt#L866)).

## Measurements

Machine for everything below: Apple M5 Max, macOS, Release preset, single
thread.

### Existing runtime and kernel on the synthetic workloads

N = 200,000 rows loaded (199,998 for `line3` and `star`, which divide N over
three tables), `crown_kernel_bench` as described above.

"Before" is the existing runtime at `3b8c931`; "after" is the same runtime with
the 48-byte allocation header. Both were measured earlier in this work, one
run per cell, with a Flink baseline job possibly running in the background;
the "before" binary was built from `3b8c931` with the same driver source minus
the `cmp` engine. "Kernel" is the current compact kernel, measured later in a
separate run. Insert and erase are the mean time per update during the FIFO
churn (kernel values converted from the driver's ns output). Allocations are
accounted allocations per insert / per erase; for the existing runtime they
are the same before and after. Bytes are accounted bytes per stored source row
after the load. The raw output of the existing-runtime runs is not in the
repository; rerun the commands below to reproduce it.

```
cmake --preset release && cmake --build --preset release -j
./build/release/crown_kernel_bench qh cmp 200000 delta
./build/release/crown_kernel_bench qh ref 200000 delta
./build/release/crown_kernel_bench qh idx 200000 delta
```

Replace `qh` with `line3` and `star`, and `delta` with `maint`, for the other
cells.

Delta mode (every update drains its signed result delta):

| Workload | Engine | Insert µs | Erase µs | Allocations per update | Bytes per row | Enumeration ns/row |
|---|---|---|---|---|---|---|
| qh | reference, before | 37.8 | 49.2 | 134 / 121 | 5,963 | 945 |
| qh | reference, after | 37.5 | 42.2 | 134 / 121 | 4,399 | 1,232 |
| qh | indexed, before | 21.8 | 27.1 | 135 / 127 | 6,174 | 605 |
| qh | indexed, after | 20.8 | 23.5 | 135 / 127 | 4,848 | 558 |
| qh | kernel | 0.127 | 0.096 | 0 / 0 | 139 | 6 |
| line3 | reference, before | 35.7 | 40.9 | 136 / 125 | 4,897 | 1,356 |
| line3 | reference, after | 37.7 | 41.0 | 136 / 125 | 3,613 | 1,663 |
| line3 | indexed, before | 22.8 | 28.9 | 136 / 130 | 5,099 | 796 |
| line3 | indexed, after | 24.4 | 27.8 | 136 / 130 | 4,006 | 861 |
| line3 | kernel | 0.155 | 0.118 | 0 / 0 | 147 | 12 |
| star | reference, before | 41.8 | 49.5 | 142 / 130 | 5,606 | 1,300 |
| star | reference, after | 36.7 | 40.1 | 142 / 130 | 4,128 | 1,276 |
| star | indexed, before | 23.3 | 28.5 | 143 / 135 | 5,786 | 727 |
| star | indexed, after | 22.8 | 25.1 | 143 / 135 | 4,543 | 739 |
| star | kernel | 0.156 | 0.109 | 0 / 0 | 186 | 9 |

Maintenance mode (state only, no delta output):

| Workload | Engine | Insert µs | Erase µs | Allocations per update | Bytes per row | Enumeration ns/row |
|---|---|---|---|---|---|---|
| qh | reference, before | 22.4 | 29.5 | 73 / 65 | 4,688 | 946 |
| qh | reference, after | 20.3 | 22.6 | 73 / 65 | 3,410 | 1,132 |
| qh | indexed, before | 10.5 | 16.2 | 74 / 70 | 4,899 | 620 |
| qh | indexed, after | 9.4 | 11.2 | 74 / 70 | 3,859 | 555 |
| qh | kernel | 0.095 | 0.076 | 0 / 0 | 139 | 6 |
| line3 | reference, before | 24.2 | 29.4 | 74 / 65 | 4,103 | 1,351 |
| line3 | reference, after | 20.2 | 21.3 | 74 / 65 | 2,992 | 1,461 |
| line3 | indexed, before | 11.1 | 14.9 | 74 / 70 | 4,305 | 754 |
| line3 | indexed, after | 10.1 | 12.3 | 74 / 70 | 3,385 | 669 |
| line3 | kernel | 0.128 | 0.104 | 0 / 0 | 147 | 12 |
| star | reference, before | 24.8 | 28.0 | 76 / 67 | 4,724 | 1,311 |
| star | reference, after | 20.9 | 23.4 | 76 / 67 | 3,443 | 1,324 |
| star | indexed, before | 10.6 | 15.5 | 77 / 73 | 4,904 | 770 |
| star | indexed, after | 10.6 | 12.5 | 77 / 73 | 3,858 | 697 |
| star | kernel | 0.113 | 0.079 | 0 / 0 | 186 | 9 |

The kernel's load time is 124 (qh), 124 (line3) and 130 (star) ns per insert
in delta mode and 102, 110 and 114 in maintenance mode. Its global `operator
new` calls per churn update and its live accounted allocations per stored
tuple are both 0.0.

Read across (kernel against the "after" rows, insert and erase taken
separately): the kernel's update time is 146 to 245 times lower than the
indexed backend's in delta mode and 79 to 158 times lower in maintenance mode;
against the default reference backend it is 235 to 440 times lower in delta
mode and 158 to 297 times lower in maintenance mode. Its accounted memory per
row is 18.5 to 34.9 times lower. Because the kernel rows come from a later
run than the existing-runtime rows, treat these factors as approximate.

Headline figures for the existing runtime (from earlier, noisier runs):

- Before this work: 10 to 13 microseconds per update in maintenance mode on
  the indexed backend, 29 to 56 microseconds in delta mode on the default
  reference backend; 4.1 to 6.2 KB and 20 to 33 live accounted allocations per
  stored tuple; about 74 (maintenance) to 135 (delta) allocations per update;
  0.6 to 2 microseconds per enumerated row.
- After the header change: bytes per stored tuple 21 to 27 percent lower;
  allocation counts unchanged.

Profile of the existing runtime (macOS `sample`, `qh` workload, indexed
backend, maintenance mode): there is no single hot spot. Roughly 60 percent of
update time is in `SupportRuntime` staging (native, survivor, count and counter
updates and their journal inserts), about 14 percent in constructing a
`SupportRuntime::EpochView::Group` per update
([support.cpp:1516](../src/runtime/support.cpp#L1516), `stage_view`), about 13
percent in ordered-map row comparisons for the per-occurrence derivation counts
([physical.cpp:90](../src/runtime/physical.cpp#L90), a `std::map` keyed by
`AccountedRow`), and the rest in source-table inserts and commit. This is why
the work switched from incremental fixes to a separate kernel.

### Like-for-like comparison with Flink

`crown_stream_bench` replayed the very same `ins_*` and `win_*` files as the
Flink baseline. One edge update is one kernel call that changes 3 or 4
relations. Kernel figures are the median of 5 repetitions at 1,000,000 edges
and of 7 at 100,000 edges, each on a fresh kernel. Flink "cold" figures are
the medians from `build/flink-baseline/results/summary_real.csv`; "warm"
figures come from `summary_driver.csv`. All times are ns per edge update,
including enumeration in modes `full` and `delta`. `x` = Flink cold / kernel.
The kernel reproduces Flink's result row counts exactly in all 36 cells.

1,000,000 edges:

| Query | Stream | Mode | Edge updates | Result rows | Flink cold | Flink warm | Kernel batched | x | Kernel one call per update | x | Batched vs warm Flink |
|---|---|---|---|---|---|---|---|---|---|---|---|
| L3 | ins | maint | 1,000,000 | 0 | 4036 | 3234 | 203 | 19.9 | 308 | 13.1 | 15.9 |
| L3 | ins | full | 1,000,000 | 16,009,375 | 6926 | 5980 | 324 | 21.3 | 427 | 16.2 | 18.4 |
| L3 | ins | delta | 1,000,000 | 16,009,375 | 9204 | 7972 | 441 | 20.9 | 586 | 15.7 | 18.1 |
| L3 | win | maint | 2,000,000 | 0 | 3527 | 2941 | 156 | 22.7 | 259 | 13.6 | 18.9 |
| L3 | win | full | 2,000,000 | 1,171,020 | 4448 | 3781 | 171 | 26.0 | 271 | 16.4 | 22.1 |
| L3 | win | delta | 2,000,000 | 3,330,494 | 4948 | 4182 | 208 | 23.8 | 313 | 15.8 | 20.1 |
| L4 | ins | maint | 1,000,000 | 0 | 6038 | 5057 | 302 | 20.0 | 480 | 12.6 | 16.7 |
| L4 | ins | full | 1,000,000 | 64,055,498 | 18156 | - | 582 | 31.2 | 746 | 24.3 | - |
| L4 | ins | delta | 1,000,000 | 64,055,498 | 29133 | - | 1461 | 19.9 | 1785 | 16.3 | - |
| L4 | win | maint | 2,000,000 | 0 | 6140 | 5450 | 308 | 19.9 | 545 | 11.3 | 17.7 |
| L4 | win | full | 2,000,000 | 931,792 | 7431 | - | 338 | 22.0 | 572 | 13.0 | - |
| L4 | win | delta | 2,000,000 | 3,484,390 | 8844 | - | 453 | 19.5 | 678 | 13.0 | - |
| Star | ins | maint | 1,000,000 | 0 | 4356 | 3546 | 143 | 30.5 | 203 | 21.4 | 24.8 |
| Star | ins | full | 1,000,000 | 189,598,366 | 25711 | - | 453 | 56.7 | 494 | 52.0 | - |
| Star | ins | delta | 1,000,000 | 189,598,366 | 35464 | - | 668 | 53.1 | 794 | 44.6 | - |
| Star | win | maint | 2,000,000 | 0 | 6071 | 5310 | 131 | 46.4 | 200 | 30.4 | 40.6 |
| Star | win | full | 2,000,000 | 20,160,656 | 10474 | - | 175 | 59.7 | 251 | 41.8 | - |
| Star | win | delta | 2,000,000 | 45,652,500 | 13857 | - | 271 | 51.2 | 360 | 38.5 | - |

100,000 edges:

| Query | Stream | Mode | Edge updates | Result rows | Flink cold | Flink warm | Kernel batched | x | Kernel one call per update | x | Batched vs warm Flink |
|---|---|---|---|---|---|---|---|---|---|---|---|
| L3 | ins | maint | 100,000 | 0 | 4678 | 2157 | 160 | 29.2 | 161 | 29.1 | 13.4 |
| L3 | ins | full | 100,000 | 1,591,230 | 8012 | 4764 | 209 | 38.4 | 210 | 38.2 | 22.8 |
| L3 | ins | delta | 100,000 | 1,591,230 | 10481 | 6425 | 284 | 36.9 | 292 | 36.0 | 22.6 |
| L3 | win | maint | 200,000 | 0 | 4119 | 2297 | 145 | 28.4 | 136 | 30.2 | 15.8 |
| L3 | win | full | 200,000 | 116,418 | 4882 | 2753 | 154 | 31.7 | 146 | 33.4 | 17.9 |
| L3 | win | delta | 200,000 | 331,602 | 5251 | 3087 | 178 | 29.4 | 174 | 30.2 | 17.3 |
| L4 | ins | maint | 100,000 | 0 | 5967 | 3406 | 225 | 26.5 | 225 | 26.6 | 15.1 |
| L4 | ins | full | 100,000 | 6,342,090 | 19703 | 14206 | 417 | 47.3 | 418 | 47.2 | 34.1 |
| L4 | ins | delta | 100,000 | 6,342,090 | 32250 | 21837 | 760 | 42.5 | 764 | 42.2 | 28.8 |
| L4 | win | maint | 200,000 | 0 | 6334 | 3816 | 227 | 27.9 | 218 | 29.1 | 16.8 |
| L4 | win | full | 200,000 | 92,207 | 7511 | 4601 | 232 | 32.4 | 228 | 32.9 | 19.8 |
| L4 | win | delta | 200,000 | 345,354 | 8376 | 5565 | 302 | 27.8 | 282 | 29.7 | 18.4 |
| Star | ins | maint | 100,000 | 0 | 4444 | 2642 | 135 | 32.9 | 129 | 34.4 | 19.6 |
| Star | ins | full | 100,000 | 18,754,000 | 27695 | 23995 | 403 | 68.7 | 394 | 70.2 | 59.5 |
| Star | ins | delta | 100,000 | 18,754,000 | 37789 | 32821 | 616 | 61.3 | 609 | 62.1 | 53.3 |
| Star | win | maint | 200,000 | 0 | 6227 | 3613 | 127 | 49.0 | 122 | 50.9 | 28.4 |
| Star | win | full | 200,000 | 2,033,824 | 11523 | 8614 | 161 | 71.6 | 156 | 73.7 | 53.5 |
| Star | win | delta | 200,000 | 4,578,604 | 13378 | 10089 | 257 | 52.0 | 250 | 53.4 | 39.2 |

Ranges of the factors:

| Edges | Kernel entry point | Against | min | median | max | cells below 20x |
|---|---|---|---|---|---|---|
| 1,000,000 | batched | Flink cold | 19.5 | 23.2 | 59.7 | 5 of 18 |
| 1,000,000 | one call per update | Flink cold | 11.3 | 16.3 | 52.0 | 11 of 18 |
| 1,000,000 | batched | Flink warm (cells measured) | 15.9 | 18.7 | 40.6 | 6 of 10 |
| 100,000 | batched | Flink cold | 26.5 | 34.9 | 71.6 | 0 of 18 |
| 100,000 | one call per update | Flink cold | 26.6 | 35.2 | 73.7 | 0 of 18 |
| 100,000 | batched | Flink warm (cells measured) | 13.4 | 21.2 | 59.5 | 9 of 18 |

Kernel time spread and memory (batched). "median s [min-max]" is the wall time
of one whole run over the stream. "Accounted" is the requested bytes of the
kernel's `MemoryAccount` at the end of the run and at its peak; it excludes
the dictionary (unused here, all values are integers) and anything outside
the account. The Flink column is the process's maximum RSS, which includes the
JVM heap reservation; it is not the same measure (Flink's retained heap is
listed in [How the baseline was measured](#how-the-baseline-was-measured)).

| Edges | Query | Stream | Mode | median s [min-max] | accounted end MiB | accounted peak MiB | Flink max RSS GiB |
|---|---|---|---|---|---|---|---|
| 1,000,000 | L3 | ins | maint | 0.2028 [0.2005-0.2225] | 244 | 300 | 6.2 |
| 1,000,000 | L3 | ins | full | 0.3244 [0.3215-0.3549] | 244 | 300 | 7.2 |
| 1,000,000 | L3 | ins | delta | 0.4411 [0.4356-0.4877] | 244 | 300 | 7.1 |
| 1,000,000 | L3 | win | maint | 0.3115 [0.3105-0.3171] | 72 | 84 | 5.7 |
| 1,000,000 | L3 | win | full | 0.3421 [0.3397-0.3428] | 72 | 84 | 6.0 |
| 1,000,000 | L3 | win | delta | 0.4166 [0.4156-0.4224] | 72 | 84 | 5.9 |
| 1,000,000 | L4 | ins | maint | 0.3020 [0.3000-0.3382] | 484 | 612 | 6.7 |
| 1,000,000 | L4 | ins | full | 0.5824 [0.5720-0.6133] | 484 | 612 | 7.7 |
| 1,000,000 | L4 | ins | delta | 1.4606 [1.4489-1.5079] | 484 | 612 | 7.8 |
| 1,000,000 | L4 | win | maint | 0.6163 [0.6072-0.6261] | 112 | 124 | 6.3 |
| 1,000,000 | L4 | win | full | 0.6755 [0.6609-0.6982] | 112 | 124 | 6.8 |
| 1,000,000 | L4 | win | delta | 0.9051 [0.8960-0.9163] | 112 | 124 | 6.7 |
| 1,000,000 | Star | ins | maint | 0.1427 [0.1409-0.1628] | 260 | 316 | 7.2 |
| 1,000,000 | Star | ins | full | 0.4532 [0.4505-0.4802] | 260 | 316 | 7.9 |
| 1,000,000 | Star | ins | delta | 0.6682 [0.6480-0.6732] | 260 | 316 | 8.0 |
| 1,000,000 | Star | win | maint | 0.2614 [0.2597-0.2668] | 94 | 108 | 7.6 |
| 1,000,000 | Star | win | full | 0.3507 [0.3469-0.3546] | 94 | 108 | 8.1 |
| 1,000,000 | Star | win | delta | 0.5415 [0.5379-0.5507] | 94 | 108 | 8.5 |
| 100,000 | L3 | ins | maint | 0.0160 [0.0159-0.0179] | 28 | 36 | 1.4 |
| 100,000 | L3 | ins | full | 0.0209 [0.0208-0.0230] | 28 | 36 | 1.9 |
| 100,000 | L3 | ins | delta | 0.0284 [0.0283-0.0305] | 28 | 36 | 2.1 |
| 100,000 | L3 | win | maint | 0.0290 [0.0287-0.0295] | 8 | 10 | 2.2 |
| 100,000 | L3 | win | full | 0.0308 [0.0307-0.0311] | 8 | 10 | 2.3 |
| 100,000 | L3 | win | delta | 0.0357 [0.0357-0.0364] | 8 | 10 | 2.5 |
| 100,000 | L4 | ins | maint | 0.0225 [0.0222-0.0249] | 40 | 46 | 1.7 |
| 100,000 | L4 | ins | full | 0.0417 [0.0412-0.0450] | 40 | 46 | 4.2 |
| 100,000 | L4 | ins | delta | 0.0760 [0.0757-0.0787] | 40 | 46 | 5.3 |
| 100,000 | L4 | win | maint | 0.0454 [0.0441-0.0461] | 12 | 13 | 3.0 |
| 100,000 | L4 | win | full | 0.0464 [0.0462-0.0469] | 12 | 13 | 3.1 |
| 100,000 | L4 | win | delta | 0.0603 [0.0596-0.0627] | 12 | 13 | 3.5 |
| 100,000 | Star | ins | maint | 0.0135 [0.0133-0.0153] | 32 | 39 | 1.8 |
| 100,000 | Star | ins | full | 0.0403 [0.0392-0.0441] | 32 | 39 | 5.2 |
| 100,000 | Star | ins | delta | 0.0616 [0.0610-0.0645] | 32 | 39 | 5.5 |
| 100,000 | Star | win | maint | 0.0254 [0.0253-0.0259] | 10 | 10 | 4.0 |
| 100,000 | Star | win | full | 0.0322 [0.0322-0.0327] | 10 | 10 | 5.1 |
| 100,000 | Star | win | delta | 0.0515 [0.0510-0.0518] | 10 | 10 | 5.2 |

### How to read the comparison

- **Which Flink figure.** Against the paper's metric (a cold JVM per data
  point) the batched kernel is 19.5x to 59.7x faster at 1,000,000 edges and
  one call per update is 11.3x to 52.0x. At 100,000 edges both are 26.5x to
  73.7x, but Flink's 100,000-edge figures are dominated by JIT warm-up, which
  inflates the factors. Against warm (JIT-compiled) Flink the factors are
  lower: 15.9x to 40.6x on the ten measured 1,000,000-edge cells and 13.4x to
  59.5x at 100,000 edges.
- **The 20x line.** At 1,000,000 edges, batched, five of 18 cells are below
  20x, all within 3% of it, and two full runs of the matrix differed per cell
  by -6% to +7%. Cells this close to the line move across it between runs. L3
  and L4 sit at the lower edge of the target; only Star clears it comfortably.
- **Lookahead.** The batched entry point sees up to 16 updates ahead of the
  one it applies; Flink processes one element at a time. The semantics are
  identical (same state, same delta rows in the same order); only memory loads
  are started early. With one call per update the kernel sees nothing ahead,
  and at 1,000,000 edges 11 of 18 cells are then below 20x.
- **Durability.** The kernel has no durability or rollback. Neither had the
  Flink job as run: heap state, and no checkpointing configured by the harness
  as far as the job source shows.
- **Machine.** Both sides ran on a shared laptop, not on the paper's server
  with a pinned core. Kernel run-to-run noise was observed up to about +-8%;
  Flink's typical spread is +-5% with session drift up to about 10%. Pinning
  Flink to one CPU with SerialGC made it 50% to 77% slower in the sensitivity
  check, so the setup matters in both directions.
- **Memory.** The kernel's accounted bytes and Flink's RSS or retained heap are
  different measures; compare orders of magnitude only.
- **Existing runtime.** The existing C++ runtime is slower than Flink on these
  streams (19 to 94 microseconds per edge update on L3 at 100,000 edges, against
  Flink's 4 to 10). Every speed-up above belongs to the kernel alone.

### How the kernel got here

Progress on one cell, L3 insert-only at 1,000,000 edges, maintenance mode, ns
per edge update. The first row is the version this document originally
described; once the Flink baseline arrived, it was clear that version was
only 3x to 10x faster than Flink at 1,000,000 edges, and the kernel was
rewritten.

| Step | ns | Note |
|---|---|---|
| First kernel (linked lists, separate visible-member slabs, per-node record slabs) | 758 | 5.3x Flink |
| Arrays per key, direct rows, no separate visible-member copy for identity nodes | 414 | |
| Contract check inlined; storage pointer cached (`MemoryBlock::data()` is an out-of-line call) | 362 | one call per update |
| Batched entry point with lookahead | 244 | |
| Branch-free lookahead, sibling-entry probes | 236 | |
| Shared separator rows | 227 | |
| Recent-row cache, source hash reuse, anchor pre-check | 210 | |
| Lookahead stage for expected support changes | 206 | |

The final table's value for this cell (204) is from a later run and differs by
noise.

Tried and not kept, with measurements:

- **Segmented (non-copying) slabs and list pool.** Accounted peak memory 35%
  lower (L3 1,000,000 edges 300 to 198 MiB, L4 612 to 296 MiB), but 7% to 12%
  slower on the window runs and 10% slower on L3 insert-only: one more table
  load on every row access costs more than the avoided copies save.
- **Segmented list pool only.** Insert-only 2% faster, window 3% to 6% slower,
  peak memory 30% lower (L3 300 to 212 MiB, L4 612 to 396 MiB). A reasonable
  choice if peak memory, or the pause while a pool of more than 100 MiB is
  copied, matters more than the last few percent.
- **Real loads instead of prefetch hints in the lookahead.** Slower (308 against
  244 ns).
- **Lookahead distance of 2, 4, 6 or 10 updates per stage.** No measurable
  difference.

A profile of the final kernel is flat: no function above about 14%
(`survive`, `crossing`, separator-row lookup, `apply` and `pull` each 6% to
14%). The remaining time is spread over the propagation itself.

## Compact kernel design

The kernel consumes the same lowered `PhysicalPlan` as `SupportRuntime` and
`DeltaRuntime`: its nodes, edges, inputs and enumeration program (see
[include/crown/ir/physical.hpp](../include/crown/ir/physical.hpp) and
`compile_nodes`, `compile_inputs`, `compile_edges` and `compile_enumeration` in
[src/planner/lower.cpp](../src/planner/lower.cpp#L307)). It maintains the same
state as the existing runtime: S (the surviving records of each node, i.e.
those all of whose children support them), P (per separator key, how many
surviving child records carry it) and E (the visible members of each connex
node, i.e. the projections of surviving records onto the variables the node
shows to enumeration). Only the physical representation differs. The layout
summary at the top of [compact.cpp](../src/runtime/compact.cpp#L15) is
accurate and is the shortest description; this section expands it.

The guiding rule for every structure: an update should touch as few distinct
cache lines as possible, enumeration should read result values from
contiguous memory, and the lookups an update needs should depend only on the
update's own row, so that they can be started before the update is applied.

Construction runs `compile_tree`, `compile_connex`, `compile_stores`,
`compile_edges` and `compile_enumeration`
([compact.cpp:406-417](../src/runtime/compact.cpp#L406)), which turn the plan
into fixed word offsets. Nothing is interpreted per update beyond these
offsets.

### Value encoding

Every value is one 64-bit word ([encode, line 784](../src/runtime/compact.cpp#L784)).
`int64` and `bool` are stored directly. Strings, dates and decimals go through
a grow-only dictionary (a `std::map<Value, Word>` plus a `std::vector<Value>`
for decoding) that assigns ids in first-seen order. Equality and hashing
therefore never inspect types; a tuple is simply `arity` words. This relies on
each field having a single scalar type, which typed query variables provide.
`Runtime::decode` ([line 1693](../src/runtime/compact.cpp#L1693)) uses the
result column types to turn words back into `Value`s.

### Storage primitives

- `Words` ([line 94](../src/runtime/compact.cpp#L94)): a growable word array in
  one `MemoryBlock` charged to the kernel's `MemoryAccount`. Growth is one
  allocation plus one `memcpy`, at least doubling. The data pointer is cached
  because `MemoryBlock::data()` is an out-of-line call.
- `Slab` ([line 123](../src/runtime/compact.cpp#L123)): fixed-stride rows
  addressed by a 32-bit index, with a free list threaded through one
  designated word of each released row (next free index in the upper half,
  zero in the lower half; a live row keeps a non-zero lower half there, which
  is how a scan tells live rows from free ones). `high_water` is the number of
  rows ever handed out.
- `Index` ([line 157](../src/runtime/compact.cpp#L157)): an open-addressing
  hash directory whose slot is `(upper 32 bits of the hash) << 32 | (row index
  + 1)`, so a probe compares a tag before touching the row. Linear probing,
  load factor at most 3/4, backward-shift deletion (no tombstones, so probes
  stay short under insert/delete churn). It starts at 16 slots, doubles, and is
  capped at 2^32 slots. `prefetch` and `peek` exist only for the batched
  lookahead: `peek` guesses the row from the tags of the home slot and the one
  after it, without comparing keys.
- `Pool` ([line 236](../src/runtime/compact.cpp#L236)): the shared storage for
  all per-key arrays. Blocks are powers of two words in 32 size classes,
  addressed by a 32-bit word offset, with one free list per class.

### Source rows and direct nodes

Each base table has one slab and one hash index of its rows
(`SourceState`, [line 371](../src/runtime/compact.cpp#L371)). A row is
`[values | meta | state of every direct node fed by this table]`.

A native node is *direct* when it has exactly one input, that input keeps
every source column (a permutation), and it has no equalities or constants;
SQL-normalized plans have no direct nodes. A direct node's record *is* the
source row: it has no slab, no index and no derivation count of its own, and
its record state lives in the trailing words of the source row
(`compile_stores`, [line 521](../src/runtime/compact.cpp#L521)). For a
self-join such as L3, one edge row therefore carries the state of all three
nodes it feeds, and one update touches one source row instead of four rows in
four places.

Any other native node keeps `[tuple | meta | state]` rows in its own slab
behind a hash index over the tuple; `meta` holds the derivation count (how many
source rows project to this tuple), so inputs with ignored columns or filters
share one record and the record lives from the first derivation to the last
(`route`, [line 1226](../src/runtime/compact.cpp#L1226)). A generalized node
keeps its candidates in a slab without an index.

Record state, in either place, is: one child-presence mask word (bit *i* set
when child slot *i* currently supports the record's key), one word per child
slot holding `(separator row id, position in that row's rev array)`, and, if
the node has a parent, one word holding `(parent separator row id, position)`.
A record survives when its mask is full (`survives`,
[line 899](../src/runtime/compact.cpp#L899)). Storing positions lets every
removal below be a swap with the last element.

### Separator rows and per-key arrays

Each tree edge connects a parent and a child over a separator (the shared
variables). Per separator key value there is one *separator row*
(`EdgeState`, [line 340](../src/runtime/compact.cpp#L340); rows found or
created by `entry`, [line 806](../src/runtime/compact.cpp#L806), and released
by `release_entry`, [line 829](../src/runtime/compact.cpp#L829), once all its
counts and arrays are empty). For each edge it uses, the row holds a *section*:

- a count word: the low 32 bits are the number of surviving child records with
  this key (P); the bytes above hold the size class of each array;
- a `rev` head: the array of every parent record with this key, whether it
  survives or not. A change of the child's support for the key flips the
  presence bit of exactly these records;
- for an edge inside the connex part, a `down` head: the child's visible
  members with this key;
- and an `up` head: the parent's visible members with this key, unless the
  edge is *merged* (below).

A head word is `[block offset in the pool (low 32) | length (high 32)]`. An
array element is `[member id (low 32) | onward separator row id (high 32)]`
followed by a payload: the member's visible values outside the separator.
Enumeration therefore reads result values straight from the array it is
walking, and the onward row id lets it go on to the next separator row without
looking up the member. The onward id is the one the usual traversal needs
next: towards the root if there is one, else the first other connex branch
(`compile_edges`, [line 604](../src/runtime/compact.cpp#L604)).

When the parent is an *identity* node (its visible tuple is its whole scope,
so its visible members are exactly its surviving records), the edge is
merged: there is no separate `up` array. Instead the `rev` array keeps the
parent's surviving records in a prefix, and the section holds the prefix
length in an extra word. `link` and `unlink`
([lines 1096](../src/runtime/compact.cpp#L1096) and
[1130](../src/runtime/compact.cpp#L1130)) move a record across the prefix
boundary by exchanging it with the element at the boundary (`exchange`,
[line 1088](../src/runtime/compact.cpp#L1088)). This saves one array and one
copy of every identity node's records.

Arrays grow and shrink through `push` and `pull`
([lines 849](../src/runtime/compact.cpp#L849) and
[871](../src/runtime/compact.cpp#L871)): the first block has room for two
elements; a full block moves to the next size class; a block at most one
quarter used moves to the previous class (never below the first); an empty
array returns its block. `pull` removes by moving the last element into the
hole and returns the moved member so the caller can repair its stored
position.

Why arrays rather than the linked lists of the first version: walking an array reads consecutive
words, whereas a list costs one dependent cache miss per member; and the
payload copy means enumeration does not visit member rows at all.

### Shared separator rows

With `Options::shared_separators` (default `true`), edges whose separators
range over the same source columns share one table (a `Group`,
[line 361](../src/runtime/compact.cpp#L361)); a row then holds one section per
member edge. `compile_edges` decides this with a union-find over variables:
two variables are in one domain when some source column binds both (for
example through a self-join), and edges whose separators agree domain by
domain form a group. In L3, L4 and Star every separator is a single vertex
id and every variable is bound by a column of the one edge table, so all edges
share one table, and an update of edge (u, v) reaches the rows of u and v
directly. Without sharing, the same update would touch one row per edge in
separate tables. Sharing is only a layout choice: any grouping of equal-arity
edges is correct, which the test checks by running one kernel with sharing
off. `Statistics::separator_keys` counts rows and so depends on this option.

### Visible members

For an identity connex node the visible members are its surviving records, in
place. Any other connex node keeps `[visible tuple | count | parent word | one
word per connex child]` rows in its own slab behind a hash index over the
visible tuple; `count` is the number of surviving records with that visible
tuple, and the member exists exactly while it is non-zero (`appear` and
`vanish`, [lines 1036](../src/runtime/compact.cpp#L1036) and
[1065](../src/runtime/compact.cpp#L1065)). The parent and child words hold
`(separator row id, position)` in the `down` and `up` arrays, so `link` and
`unlink` add and remove a member with swap-with-last.

### Update propagation

- `apply` ([line 1271](../src/runtime/compact.cpp#L1271)) looks the row up in
  its table's index, returns `false` for a duplicate insert or an absent erase,
  and otherwise stores (or, at the end of an erase, releases) the source row
  and handles every occurrence of the table: a direct node directly, any other
  node through `route`. A guard marks the kernel poisoned if anything throws
  after this point.
- `attach` and `detach` ([lines 904](../src/runtime/compact.cpp#L904) and
  [924](../src/runtime/compact.cpp#L924)) enter a new record into the `rev`
  array of each child edge (computing its presence mask from the child support
  counts) and remove it again.
- `flip` ([line 936](../src/runtime/compact.cpp#L936)) toggles one presence
  bit and calls `survive` only when the mask becomes or stops being full.
- `survive` ([line 949](../src/runtime/compact.cpp#L949)) moves a record into
  or out of S. On the way in it increments the P count of the record's key in
  the parent edge's separator row and, if that count went from 0 to 1, calls
  `crossing`; then, for a connex node, `appear`. On the way out it calls
  `vanish` first, then decrements the count and calls `crossing` on 1 to 0. At
  the root it adjusts `root_support` instead.
- `crossing` ([line 987](../src/runtime/compact.cpp#L987)) flips the presence
  bit of every record in the key's `rev` array. Flips propagate towards the
  root only, so the array keeps its members during the walk; on a merged edge
  the members that change survival move across the prefix boundary, which is
  why the removal walk takes the survivors from the back.
- Generalized nodes: a candidate's tuple is its separator key. It is created
  by `create_candidate` ([line 1019](../src/runtime/compact.cpp#L1019)) when
  the first child supplies the key (it is then entered into the `rev` array
  of every child edge), and dropped when no child supplies it any more.
  Generalized nodes never receive inputs.
- Self-joins: one source row is stored once and then applied to each
  occurrence in turn, each seeing the state left by the previous one.

### Delta enumeration

At every appearance or disappearance of a visible member the kernel enumerates
all result rows that pass through that member in the current state (`emit`,
[line 1155](../src/runtime/compact.cpp#L1155)). On the way in this happens
after the member is added to its arrays; on the way out before it is removed.
This reports every changed result row exactly once: on insert a new row is
reported when the last of its new members appears (earlier appearances could
not reach it because that member was not yet present), and on erase a
vanishing row is reported when the first of its members disappears (later
ones cannot reach it because that member is already gone). Within one
`survive` call the order is: on the way in, the support count reaches the
parent first and the node's own visible member is added last; on the way out,
the member is removed first and the count follows. Either way a row is
enumerated only while all of its members are in their arrays, along a single
update and across the occurrences of a self-join.

`emit` follows a traversal of the whole connex subtree *anchored* at the
member's node, compiled once per connex node by `compile_enumeration`
([line 719](../src/runtime/compact.cpp#L719)): a breadth-first order over
tree neighbours in which each step moves up (to the parent) or down (to a
connex child) across one edge and iterates the `up` (or merged `rev` prefix)
or `down` array of one separator row. The row id comes from the anchor
member, from the onward id in the previous step's element, or, failing both,
from the previous step's member row. A result column is bound at the step
where its variable first appears, which is always in that step's payload.
Before looping, the arrays that hang off the anchor itself are opened; if one
is empty there is no row at all and `emit` returns. When a step's elements
carry the next step's row id, opening the step prefetches the next separator
rows and their arrays for up to 16 elements together instead of meeting the
misses one at a time.

For a Boolean query (no connex root), the sink receives `row(nullptr)` when
`root_support` changes between zero and non-zero.

### Full enumeration

`enumerate` ([line 1421](../src/runtime/compact.cpp#L1421)) runs `emit` from
every live visible member of the root. Going down from the root every reached
member has full bottom-up support, so no step is wasted apart from the scan of
the root's member slab, which runs to its high-water mark rather than over live
members only.

### Batched lookahead

`apply_batch` ([line 1394](../src/runtime/compact.cpp#L1394)) applies the
updates in order and runs `lookahead`
([line 1325](../src/runtime/compact.cpp#L1325)) in four stages, four updates
apart, so the first stage runs 16 updates ahead of the update being applied:

1. hash the source row and every *probe key* of the update (the separator
   keys its direct nodes will reach; they depend on the row alone and are
   precomputed per table in `compile_edges`, at most 15 used per update), and
   prefetch the home directory slots;
2. `peek` the directories and prefetch the source row and the separator rows;
3. prefetch the tail of every array of those separator rows;
4. where the update is expected to change the child's support for a key
   (insert with P = 0, erase with P = 1), prefetch up to four parent records of
   the key's `rev` array.

Lookahead never changes state and nothing relies on it: a wrong guess only
costs the load it started. The stages choose addresses without branching
(an absent row is replaced by a static dummy), because whether a key exists
yet is not predictable. Integer arithmetic is used where an address could be
formed from an absent block, so no invalid pointer is ever created. The hash
of the source row from stage 1 is reused by `apply`.

### Recent-row cache

`entry` keeps the last four resolved separator rows for single-word keys
(`Recent`, [line 803](../src/runtime/compact.cpp#L803)). One update reaches
the same row through several nodes and edges, so most lookups end there.
`release_entry` clears a released row from the cache.

### Invariant check

`check_invariants` (`check`, [line 1440](../src/runtime/compact.cpp#L1440))
rebuilds everything from the live source rows and records alone and compares:
source and record censuses with their indexes, derivation counts, presence
masks, survivor counts and `root_support`, P counts, visible members and their
counts, every array's membership, stored positions, payloads and onward row
ids, the survivor-prefix partition of merged arrays, that each array fits its
size class, that no empty separator row is retained, and that the pool's
blocks are neither lost nor shared (listed blocks plus free blocks equal the
high-water mark). It then calls `MemoryAccount::check_invariants`.

## Kernel limits

- **No atomicity.** There is no journal and no rollback. A sink that throws or
  an exhausted memory limit during an update marks the instance as poisoned
  (the `Guard` in `apply`, [line 1276](../src/runtime/compact.cpp#L1276)); every
  later `apply` or `enumerate` throws. Contract failures detected before any
  state changes (for example a wrong row arity or an unknown table, checked by
  `validate`, [line 1410](../src/runtime/compact.cpp#L1410)) do not poison it.
  In a batch, the updates before a failing one stay applied.
- **Missing features of the full runtime:** no epoch views, no
  checkpoint/restore image, no observation trace, no workload statistics, no
  work admission and no windows.
- **Set semantics only.** No bag semantics, aggregates, comparisons or
  differences; StarCnt is therefore not comparable.
- **Route.** Only `PhysicalRoute::tree` plans are accepted
  ([line 408](../src/runtime/compact.cpp#L408)).
- **SQL-normalized plans.** When `PhysicalPlan::normalized()` is present the
  kernel calls `PhysicalPlan::adapt_input` per occurrence and re-encodes the
  result ([route, line 1230](../src/runtime/compact.cpp#L1230)). These plans
  work only through the `Row` entry point (the word-level and batched entry
  points refuse them), have no direct nodes, and group separators by variable
  identity only. This path allocates on every update, was not benchmarked, and
  is not covered by the differential test, which only uses plans from
  `planner::lower_tree`.
- **Fixed limits** ([lines 59-61](../src/runtime/compact.cpp#L59)): at most 64
  fields per scope, separator or source row; at most 63 children per node (the
  presence mask is one word); 256 result columns; 64 connex nodes (enumeration
  steps). Row ids, counts and array lengths are 32-bit; the list pool holds at
  most 2^32 words (32 GiB); directories are capped at 2^32 slots. Violations
  throw `Error` with code `compact_runtime_contract`.
- **Dictionary.** Grow-only, a `std::map` and `std::vector` outside the
  `MemoryAccount`, not reference counted. A new string, date or decimal value
  costs heap allocations, so "no allocation per update" holds only once no new
  non-integer values appear (all benchmark workloads are integer-only).
  Encoding a string costs a `std::map` lookup with string comparisons.
- **Delta enumeration is not constant delay.** It is output-sensitive on data
  without dangling tuples, but the anchored traversal has no top-down liveness
  information: when it moves up from the anchor it can reach parents whose own
  ancestors do not support them, after having visited sibling subtrees, so it
  can walk arrays that lead to no result. The output is correct, but the
  per-row bound of the paper does not hold in the worst case. The existing
  anchored completion in [delta.cpp](../src/runtime/delta.cpp#L237) keeps
  "live" images for exactly this purpose; see
  [anchored_delta.md](anchored_delta.md).
- **Growth.** Slabs, the list pool and directories grow by doubling and
  copying: a single update can pause for the copy, and the accounted peak is
  above the end state (for example 300 against 244 MiB for L3 insert-only at
  1,000,000 edges). Slabs and directories never shrink; arrays do.
- **Full enumeration** scans the root's member slab up to its high-water mark.
- **The sink must not call back into the kernel.**
- **Lookahead** relies on `__builtin_prefetch`; it reads only in-bounds
  kernel state. The batched entry point refuses a whole batch, before reading
  or changing anything, if any update names an unknown table or operation or
  has a null row. It cannot check that each `Update::row` really holds the
  table's arity in words; that is the caller's contract, as the API documents.
- **Not wired in.** The kernel is not reachable from the CLI, `QuerySession`,
  the SQL row or aggregate runtimes, or recovery. Only the test and the two
  benchmark drivers use it.
- **Plan copy.** The kernel stores its own copy of the `PhysicalPlan`.

## Test and verification status

Environment: macOS, Apple Clang, Release preset unless stated otherwise.

Baseline at `3b8c931` before any change in this work: of 396 registered tests,
351 pass, 1 is skipped (`example_output_failure`) and 44 fail. The failures
are environmental: missing Python packages `jsonschema`, `referencing`,
`duckdb` and `matplotlib`, missing GNU `time`, and Linux-only tools; see
"Environment notes" in [review-2026-11-20.md](verification/review-2026-11-20.md),
which counts 41 such failures on its own machine. Some of the blocked tests
are SQL oracle tests, so SQL behaviour is less covered on this machine than on
Linux. The baseline failing-test list is saved at
`build/release/perf-baseline-failures.txt` (untracked). After the header
change alone the pass/fail set was identical.

Final full Release ctest run with the current kernel: of 398 registered tests
(the 396 above plus `compact_runtime` and `compact_runtime_indexed`), 353
pass, 1 is skipped, and the same 44 fail as in the baseline. The final failing
list is `build/release/perf-final-failures.txt` (untracked).
`compact_runtime` took 14.3 s and `compact_runtime_indexed` 2.4 s in that run;
both pass. Three two-column-separator shapes were added to the test after that
run; with them the two tests compare 7,279,422 records (reference backend, 15 s)
and 1,007,381 (indexed), and pass.

Sanitizers (`sanitize` preset, ASan and UBSan, Debug): on the final source
both kernel tests (`crown_compact_runtime_test` with and without the `indexed`
argument, 23 shapes) pass with no report when started directly with
`ASAN_OPTIONS=detect_leaks=0`; the first takes about 9 minutes. During development UBSan found one real
defect: the lookahead formed `null + offset` when an array had no block; it now
uses integer arithmetic. Four existing tests that exercise the changed
allocation header were also built and run there and pass with no sanitizer
report: `memory_account_contract`, `runtime_memory`, `delta_runtime` and
`s04_storage_table`. All of these must be started directly (for example
`ASAN_OPTIONS=detect_leaks=0 ./build/sanitize/crown_memory_account_contract_test`):
through `ctest` they abort at start-up on macOS, because the preset's test
environment enables leak detection, which AddressSanitizer does not support on
this platform. That is a property of the preset on macOS, not of this change.

Mutation checks: seven bugs were injected into the kernel one at a time, each
rebuilt and the test re-run:

1. `unlink` leaves a demoted survivor in the prefix;
2. the moved member's position is not repaired after a `down` array removal;
3. a released row stays in the recent-row cache;
4. the payload of a `rev` element is not written;
5. candidate removal releases the separator row twice;
6. the removal walk in `crossing` takes the survivor prefix forwards;
7. a promoted element keeps a stale onward row id.

All seven are detected. Mutation 3 does not fail an assertion: the mutated
test never finishes (killed after 10 minutes; the unmutated test takes 14 s),
so it is caught only by the timeout. Mutation 7 crashes rather than reporting.
For whoever repeats this: Apple's `make` compares modification times at
one-second resolution, so a mutation written in the same second as the
previous object file is silently not rebuilt; wait a second or check that the
object was rebuilt.

The kernel reproduces Flink's result row counts in all 36 compared cells (see
[Like-for-like comparison](#like-for-like-comparison-with-flink)), which is an
independent end-to-end check on large inputs.

Not done: any Linux/GCC build, the rest of the suite under the `sanitize`
preset, and the 44 environment-blocked tests.

## Findings and their status

These are the design-review findings this effort started from. They concern the
existing runtime. The compact kernel avoids all of them on its fast path by
construction (one word per value, one slab row per tuple and none for direct
nodes, no per-object allocation, hash directories only, no work admission).
The existing runtime is unchanged except for the smaller header, and it
remains 4.6x to 10.5x slower than cold Flink on the L3 streams; these findings
matter only if the existing runtime itself must become faster.

| # | Finding (existing runtime) | Where | Status |
|---|---|---|---|
| F1 | Every object is its own accounted heap block; framing was 95 bytes per allocation | [memory.cpp:78](../src/resource/memory.cpp#L78) | Partly addressed: framing now 48 bytes; allocation count unchanged |
| F2 | A stored cell (`storage::ScalarView`) is 56 bytes because the variant inlines a 41-byte decimal | [accounted_row.hpp:42](../include/crown/storage/accounted_row.hpp#L42), [InlineDecimal at line 18](../include/crown/storage/accounted_row.hpp#L18) | Open in the existing runtime; avoided by the kernel (one word per value) |
| F3 | Indexed backend nodes: row 200 bytes, key 176, member 104, each carrying a 32-byte allocator copy and 48-byte directory hooks; a separate by-id directory duplicates what the arena slot and generation handle could provide | [accounted_indexed_nodes.hpp:37](../src/storage/accounted_indexed_nodes.hpp#L37), [hash_directory.hpp:19](../src/storage/hash_directory.hpp#L19) | Open in the existing runtime (node sizes are from the design review and not re-measured here; the 32- and 48-byte member sizes follow from the declared fields on LP64) |
| F4 | Insert allocates a projected key per index just to probe, plus a scratch vector per insert; enumeration allocates a key and a cursor per frame | [accounted_indexed.cpp:267](../src/storage/accounted_indexed.cpp#L267) and [:271](../src/storage/accounted_indexed.cpp#L271); [support.cpp:1133](../src/runtime/support.cpp#L1133) | Open in the existing runtime; the kernel projects keys into stack arrays and allocates nothing per update |
| F5 | Work admission (`IndexWorkAllowance::admit`) runs several times per cell | [index_work.hpp:38](../include/crown/storage/index_work.hpp#L38), [index_scalar_work.hpp:18](../src/storage/index_scalar_work.hpp#L18) | Open in the existing runtime; the kernel has no work admission at all |
| F6 | Support metadata lives in `std::map<TupleId, …>` side tables with a heap vector of child flags per record; one presence flip costs several allocations and lookups | [support.cpp:65](../src/runtime/support.cpp#L65) (`RecordState`), [support.cpp:91](../src/runtime/support.cpp#L91) (`NodeState`) | Open in the existing runtime; in the kernel record state is a few words inside the record (or source row) |
| F7 | The same tuple is deep-copied into the source table, the derivation-count key, records and survivors; P and E are separate tables with side count maps | [physical.cpp:90](../src/runtime/physical.cpp#L90), [support.cpp:93](../src/runtime/support.cpp#L93) | Open in the existing runtime; in the kernel a direct node's record is the source row and identity nodes keep no separate visible copy |
| F8 | The default backend is the ordered `std::map` reference backend unless `PhysicalOptions::indexed_storage` is set | [physical.hpp:93](../include/crown/ir/physical.hpp#L93), [physical.cpp:132](../src/runtime/physical.cpp#L132) | Open |
| F9 | `MemoryAccount::set_lifetime_containing` scanned the whole allocation ledger on every delete | `ContainingSite` overload in [memory.cpp](../src/resource/memory.cpp) | Fixed before this work in commit `bc4a396` (O(1) per call site) |

Additional profile findings for the existing runtime, both open: per-update
construction of `SupportRuntime::EpochView::Group` in `stage_view`
([support.cpp:1516](../src/runtime/support.cpp#L1516)), and the ordered
per-occurrence derivation-count map
([physical.cpp:90](../src/runtime/physical.cpp#L90)).

## Roadmap

### Done since the first draft of this document

Fixing the comparison with Flink (same queries, same stream files, same timer
boundary, one driver); per-key arrays instead of linked lists; record state in
source rows (direct nodes); shared separator rows; the batched entry point
with lookahead; the word-level and batched entry points; a stronger invariant
check; self-join shapes, a wide-domain pass and a batched replay in the test.

### Kernel track

In rough order of expected value; each item has an acceptance check.

1. **Wire the kernel behind `QuerySession` and the CLI as an opt-in engine.**
   This needs atomicity first: an undo log or copy-on-write for the rows one
   update touches, so that a throwing sink or memory-limit failure leaves the
   kernel in its pre-update state instead of poisoned. `DeltaRuntime` stays the
   default and the oracle. *Accept when* a test injects failures at every
   allocation and sink call of an update and the kernel afterwards matches an
   instance that never saw the update (with `check_invariants` passing), and
   the same CLI input produces identical sink output with both engines, with
   the option documented in [cli.md](cli.md).
2. **Generalized nodes as "hub rows".** All child edges of a generalized node
   have the same key, so the candidate, the per-child counts and the arrays
   could live in the one shared separator row. This removes candidate
   creation and destruction and the one-element `rev` arrays. Expected to help
   L4-like trees most; not measured. *Accept when* the differential test
   passes and the L4 cells of the comparison improve beyond noise.
3. **One more lookahead level for cascades:** prefetch the parent separator
   rows of the records an update will flip. *Accept when* the 1,000,000-edge
   cells improve beyond noise without slowing the others.
4. **Segmented list pool as an option** (measured above: about 30% lower peak
   memory, 3% to 6% slower on window streams). *Accept when* both layouts pass
   the differential test and the option is documented.
5. **SQL-lowered plans.** Add SQL-lowered cases to the differential test, then
   replace the per-update `PhysicalPlan::adapt_input` call with a word-level
   adapter compiled once at construction, so these plans can use direct nodes
   and the batched path. *Accept when* the test covers plans with
   `normalized()` present and those updates allocate nothing in steady state
   (measured with the `operator new` counter of `crown_kernel_bench`).
6. **Remaining features and limits.** Aggregates and bag semantics (needed
   for StarCnt; accept when differential tests against the existing bag and
   aggregate runtimes pass); an accounted, reference-counted dictionary with a
   hash index (accept when a churn over string keys shows bounded dictionary
   size and no allocation per update once warm); incremental directory growth
   (accept when the maximum single-update latency is within a small factor of
   the median); top-down liveness for constant-delay delta enumeration (accept
   when a counter of arrays that yield no output stays bounded per emitted row
   on an adversarial deep path); a checkpoint image (accept when restore
   followed by the remaining updates matches an uninterrupted run).

### Full-runtime track (optional, lower priority)

Only if the existing runtime itself must get faster, take the open findings in
the order the profile suggests: (a) stop constructing an `EpochView::Group` per
update; (b) replace the ordered derivation-count map with a hash table; (c)
remove per-transition metadata allocations (F6); (d) probe without
materializing projected keys (F4); (e) slim the indexed nodes (F2, F3). Each
change must keep the existing test suite and the rollback/journal guarantees
intact.

### Housekeeping

- Update [memory_accounts.md](memory_accounts.md) and the
  [code_specs](code_specs/README.md) registry for the header change and the new
  files (`python3 tools/generate_code_specs.py`, then
  `python3 tools/check_code_specs.py`).
- Re-run the whole suite on Linux/GCC in Release and under the `sanitize`
  preset; look in particular for goldens that pin accounted byte counts.
- Install the Python test dependencies (`jsonschema`, `referencing`, `duckdb`,
  `matplotlib`) and GNU `time` so the 44 environment-blocked tests, which
  include SQL oracle tests, run.
- The header change, the kernel with its test, and the benchmark drivers are
  in one commit; split it before merging if separate review is wanted. Remove
  the stray, untracked `.DS_Store`. Decide whether the Flink baseline scripts in `build/flink-baseline/` should
  be kept somewhere durable; at present they exist only in the untracked build
  area.

## Open questions for the owner

1. Which Flink figure defines the 20x to 50x target: the paper's cold-JVM
   `AccumulateTime` (met at 100,000 edges, met at the lower edge for L3 and L4
   at 1,000,000 edges with the batched entry point), or warm Flink (not met in
   most cells)? And may the kernel use the batched entry point, which sees up
   to 16 updates ahead, or must the comparison use one call per update?
2. Should the comparison be repeated on a machine closer to the paper's (a
   Linux server, one pinned core, JDK 8), given that pinning Flink to one CPU
   changed its time by 50% to 77%?
3. May the fast path trade the full runtime's rollback and journal guarantees
   (and epoch views, checkpoints, work admission) for speed, or must it reach
   parity before it can be used outside benchmarks?
4. Is peak memory, or the pause while a large array pool is copied, important
   enough to accept a few percent of time for the segmented list pool?
5. Are the changed accounted-byte figures acceptable for existing goldens and
   documentation, or must the old accounting be preserved for compatibility?
6. Is set semantics enough, or must the aggregate queries (such as StarCnt) be
   part of the comparison?
7. Should the kernel eventually replace `DeltaRuntime` as the default engine,
   or remain an opt-in fast path?
