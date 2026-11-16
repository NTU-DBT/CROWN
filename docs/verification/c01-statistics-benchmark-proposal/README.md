# C01 collector overhead component benchmark

Excluded standalone benchmark proposal, 2026-11-07. **C01 remains incomplete.** This consumer does not change the frozen collector proposal or native runtime, and it does not establish whole-engine throughput, all-off parity, or an acceptance threshold.

## Inputs and build

The API and contract input is the frozen `c01-statistics-collection-proposal` package, whose supplied package digest is `SHA613b1ee2759a068d34c4077e29681225bc280e64013c0fd71beac78d7fa732ff`. Its original `package.sha256` manifest is pinned in `input-pins.sha256`.

The strict build links the API-identical warning-only revision at `docs/verification/c01-statistics-collection-warning-proposal/`, package digest `0ad7771da11e2bb545ece48ef1f2ff5b93b62856b58279ed926b3ed50cecd5fd`. That revision changes only the `std::bit_width` array index to an explicit in-range `std::size_t` conversion; the header and API are byte-identical to the frozen source. Both input package identities are recorded in `input-pins.sha256`.

Build from the repository root with the full project warning set, C++23 and optimization enabled. The command creates a distinct binary under `/tmp`; it does not run it.

```sh
c++ -std=c++23 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -UNDEBUG -O3 \
  -I docs/verification/c01-statistics-collection-warning-proposal/overlay/src/runtime \
  docs/verification/c01-statistics-collection-warning-proposal/overlay/src/runtime/statistics_collection.cpp \
  docs/verification/c01-statistics-benchmark-proposal/benchmark.cpp \
  -o /tmp/crown-c01-benchmark-component-20261107
```

Run from the repository root after the build:

```sh
/tmp/crown-c01-benchmark-component-20261107 50000 2 9 2026110701
```

The optional positional arguments are `events`, `warmups`, `repetitions`, and decimal `seed`. Defaults are 50,000 events, two warmups, nine measured repetitions, and seed `2026110701`. Output is one JSON object on stdout. Each profile reports every measured duration in nanoseconds and its median, minimum, maximum, and median replay rate. For an even repetition count the median is the floored midpoint of the two central sorted durations.

## Workload and profiles

The input stream is generated once before timing from the fixed seed using SplitMix64. It replays insert and erase attempts against 96 fixed row slots, divided into eight exact groups. A duplicate insert or erase of an absent row is a physical no-op. The local predicate is evaluated for every candidate in the changed-event alias traversal; an occurrence is accepted only when its candidate group matches the affected group and `(row_slot + candidate_slot + candidate_group) % 4 != 0`.

Each changed physical event opens one collector root and one nested propagation wrapper. The propagation touches two to four alias candidates, one changed group-support value, and three or four parent records. Parent degrees alternate between two values, so every changed event observes repeated values as separate hooks; the stream never deduplicates them. No-op events have only the physical root and no detail hooks. The same semantic loops, fixed row initialization, exact grouped counts, and checksums run in every profile; the `no_instrumentation_calls` specialization removes collector calls at compile time.

The four profiles are:

1. `no_instrumentation_calls`: semantic workload with collector hook calls compiled out; it supplies the independent exact reference result.
2. `off_collector_calls`: the same hooks are invoked on an off-configured collector.
3. `census_counters_period_1`: counters with period 1 and offset 0.
4. `sampled_counters_period_64_offset_0`: deterministic systematic sampling with period 64 and offset 0. Selection counts every admitted physical attempt, including no-ops; retries, randomness, and confidence claims are not involved.

For each profile, all warmups and repetitions are checked against the no-calls reference outside the timed interval. The reference is produced by the same pure semantic replay with hook calls removed, independent of collector cells, bins, and histogram code. The expected result preserves exact input/change/no-op totals, duplicate and absent counts, occurrence counts, final group row counts, and 64-bit state and trace checksums. The checksums use FNV-1a over each logical word encoded low-byte-first. A successful JSON result includes the expected reference and each profile's identical observed logical result; a mismatch stops output with an error.

## Timing and counters

Only the complete workload replay is timed with external `std::chrono::steady_clock` calls. Input generation, collector configuration, and collector reset are outside measured intervals. Fixed row-array initialization, the transaction stream, group accounting, semantic predicate and propagation loops, and trace/state checksums are inside each replay interval. The collector itself has no clock calls. `median_workload_events_per_second` is the synthetic replay rate for this interval, not an engine operation rate.

Each profile emits the actual collector sample configuration, exact per-run metadata and `memory()` values. Metadata includes attempts, commits, sample selection/completion, guard visits, detail actions, cleared-cell visits, and merged-cell visits, plus coverage flags. The final measured run's metadata is reported. Its `cleared_cells` includes the three slab clears from the pre-run reset, which is outside timing, as well as clears during that run. No-call output marks the collector absent and uses zero memory/counter fields; off mode reports the fixed collector object and zero vector payload when that is what `memory()` returns.

Memory is component requested payload accounting: actual vector capacities multiplied by element widths, plus `sizeof(Collector)` as a separate field. `retained_payload_bytes` excludes the object; `object_plus_payload_bytes` adds the two. Allocator metadata and rounding, configuration overlap, engine storage, snapshots, and report allocations are excluded, so this is not total process memory or S05 live-byte evidence.

## Limits

This is a standalone component microbenchmark over a deterministic synthetic table. It does not run the Crown engine, native transaction owners, public statistics facade, schema, or runtime mode handoff. It cannot show engine-level latency, all-off parity, allocator totals, concurrency behavior, production workload representativeness, or C01 acceptance. Results have no preselected speedup target or pass/fail performance threshold. Record the actual host, compiler/version, and run conditions alongside raw JSON before drawing conclusions.
