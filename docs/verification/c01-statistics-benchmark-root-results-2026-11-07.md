# C01 numeric collection — measured component preparation, 2026-11-07

**Synthetic standalone component only. C01 remains not_started.** The
[frozen benchmark consumer](c01-statistics-benchmark-proposal/README.md), manifest
`9bf61e764a052414f92d34d89875208902a7b95028f9a0fe43b428e1a242ff05`,
passes root execution against the accepted warning-only collector. Root rebuilt
both translation units with C++23, O3, assertions enabled and the complete six
project warnings as errors.

Each profile replays 50,000 identical generated physical attempts over 96 fixed
slots/eight groups, with seed 2026110701, two warmups and nine measured runs.
Duplicates/absent erases, local alias predicates, positive group count changes
and repeated synthetic parent-degree events are retained. All four profiles
produce the same logical totals, state checksum and trace checksum.

| Profile | Median ms / 50k attempts | Min–max ms | Retained collector payload bytes |
| --- | ---: | ---: | ---: |
| no_instrumentation_calls | 2.062 | 1.914–2.287 | 0 |
| off_collector_calls | 2.341 | 2.229–2.455 | 0 |
| census_counters_period_1 | 31.863 | 31.098–32.573 | 15424 |
| sampled_counters_period_64_offset_0 | 19.956 | 19.755–20.861 | 15424 |

Timing uses an external steady clock around complete simulation replay,
including its checksums. Input generation/configuration/reset are outside the
interval; collection itself reads no clocks. There is no performance threshold.
Sampled collection still pays guard and finite slab-clear/merge costs, so its
cost is not the census cost divided by the sampling period. These are
component measurements under a synthetic workload, not engine latency,
production throughput, expected maintenance cost or engine all-off parity.

The enabled collector admits eight descriptors and three numeric slabs. Bytes
are actual vector capacities times element sizes. The fixed collector object
is separately reported in the raw JSON. Allocator metadata/rounding, temporary
old+new configuration overlap, engine storage, reports and caller snapshots are
excluded; these numbers are not S05 total allocator/live bytes.

Root independently checks exact attempt/commit/selection/completion totals,
zero degraded/abort/truncated status, exact cleared and merged cell counts,
four-way logical parity, nine positive durations per profile and component-byte
identities. The sample selects 782 of 50,000 admitted attempts. A native O07
sanitizer fault sweep was concurrently active; run order is fixed and host/load
conditions can affect measurements. Do not extrapolate these timings to native
query execution. Compiler/CPU/affinity counts and all raw durations are retained.

[Root summary](../../build/verification/c01-statistics-benchmark-root-attempt-1.json)
and [raw JSON](../../build/verification/c01-statistics-benchmark-root-attempt-1-raw.json)
record exact inputs, commands, compiler/machine, binary/log hashes and
before/after pins. All 646 pins are unchanged. Build:
`/tmp/crown-c01-benchmark-root-attempt-1/`. No native source, test, tool,
schema or CMake input changed. Engine integration/overhead, owner rollback,
state capture and full C01 acceptance remain separate unfinished gates.
