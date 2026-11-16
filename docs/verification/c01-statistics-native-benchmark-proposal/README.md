# C01 native update-stream overhead benchmark proposal

**C01 remains not_started and excluded from native publication.** This
standalone production benchmark is an isolated measurement proposal against the
frozen combined C01 overlay, manifest
cb0ecb64935f80bf4915aa069de1bf01bcf1ea2f22a591f6f7408d405fcf4cfe. It does
not change native sources, schemas, reports, tools, or CMake inputs. The
earlier synthetic component benchmark remains separate evidence and is not
used to predict engine throughput.

## Workload and measured paths

The benchmark lowers the typed set query R(x,y,ignored) ∧ S(y) with output
(x,y), a native R root and native S child. The catalog also contains an
unused table. The initial database has 48 of 96 fixed R rows and four of
eight S keys. Every profile replays one prebuilt sequence, defaulting to
5,000 physical insert/erase attempts with seed 2026110707. It includes
duplicate inserts, absent erases, changing full-row R projections, and
S membership changes. A fixed part of each 40-attempt block makes an S
change touch two different R reverse-index bucket sizes; the remaining
events are selected by a deterministic SplitMix64 stream. Trace generation and
literal expected-state replay occur before any timed interval.

Two actual owner paths are measured:

* PhysicalRuntime::apply(update) over the complete source update stream.
* DeltaRuntime in maintenance mode using begin(update), drain(), commit(),
  and pull-draining any returned Epoch rows with next(). This includes Delta's
  required maintenance preparation/finalization path. There is no sink callback
  or serialization. The untimed warmup guard requires maintenance mode to
  produce no signed output.

Each path is measured with C01 off, counters at period 1, and counters at
period 64 with offset 0. Each fresh owner is initialized from the same database
and configured before the interval. O07 observation is explicitly off and
support transition capture is false for every profile. The program reads these
settings back from each actual owner's options. The C01 mode, period, offset,
cell limit, detail budget, descriptors, cells, metadata, coverage status, and
Snapshot::memory() capacities are read from the actual post-run snapshot.

The external std::chrono::steady_clock is read twice per measured stream,
around the update loop only. Runtime initialization, plan lowering, input
construction, C01 configuration, warmups, post-run state/result checks,
collector snapshot creation, and JSON writing are outside the interval. C01
does not have a timed collection mode or arrival-rate measurement.

## Independent guards and output

The benchmark separately replays every physical full row into standard set
tables. After each run, outside timing, it compares the runtime's full physical
tables (including the unused table), native R/S record and survivor sets,
root and child support counts, root visible keys, and current query result with
that literal replay and an independent nested join. It compares mandatory
physical/support/Delta work totals collected during the first untimed warmup
across C01 modes. Each measured repetition must produce the same final
source/support/result checksums.

Checksums hash stable integer table/row values and typed support facts. They do
not include owner, tuple, or other process-local identifiers. The output is
raw JSON with every measured duration in nanoseconds, median/minimum/maximum,
median absolute deviation, events per second, exact work totals, final row
counts/checksums, and complete C01 coverage counters. For C01 off, availability
is disabled and coverage counts are null; raw zero metadata is also shown,
so disabled collection is not mistaken for a run with zero input events.

Snapshot::memory() reports the collector object's and collector vector
capacity payloads, including routes where present. This is component
accounting, not allocator or peak memory. It excludes allocator bookkeeping
and rounding, engine tables/indexes/arenas, plan and runtime objects, temporary
configuration overlap, caller-retained snapshots, result output, initialization,
capture/export, and JSON formatting. Those setup and export paths are not
included in update-stream time.

The benchmark sets no pass threshold and makes no speedup claim. It measures
these two synthetic runtime paths and does not measure input parsing, SQL
ingestion, a result sink, serialization, other Delta policies, full application
workloads, native C01 report/schema integration, or a production performance
prediction.

## Build and run

From the repository root, the build-only script compiles the benchmark and all
native runtime/collector translation units at -O3 with C++23 and all six
project warning flags as errors, then links against the pinned existing Release
plan/SQL/core libraries. Every runtime object receives the same exact flags;
no CROWN_RUNTIME_TESTING define or O2 combined-package object is reused.
Native static dependencies are read and linked from the pinned
build/release artifacts. The script only compiles and links.

    CXX=c++ bash docs/verification/c01-statistics-native-benchmark-proposal/build-only.sh \
      /tmp/crown-c01-native-benchmark-root

Root can record the host and run conditions through the two environment fields,
then run the binary and preserve its raw JSON:

    CROWN_BENCH_MACHINE='root records CPU/model and host' \
    CROWN_BENCH_RUN_CONDITION='root records affinity, load, and run order' \
      /tmp/crown-c01-native-benchmark-root/crown_c01_native_benchmark \
      --events 5000 --warmups 2 --repetitions 9 --seed 2026110707 \
      > /tmp/crown-c01-native-benchmark-root/raw.json

The machine and run-condition text above are placeholders for root to replace
with observed values. The binary emits its compiler version; the exact compiler
flags and pinned Release dependency hashes are recorded in
build-evidence.md. Optional numeric arguments can change the event count,
warmup count, repetition count, and seed. The default run uses two warmups and
nine measured repetitions for each of six scenario/profile combinations.

The author compiled and linked the proposal only. The benchmark binary was not
executed here. Root owns execution and recording machine/run conditions. This
compile/link result does not establish a C01 test pass, sanitizer result,
measured native overhead, or C01 acceptance. Compatible O07 report/schema
integration and broader native cost evidence remain pending.
