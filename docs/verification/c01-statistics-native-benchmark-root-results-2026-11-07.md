# C01 actual-engine benchmark — root preparation results, 2026-11-07

**Accepted excluded measurement; C01 remains `not_started`.** This runs the
actual production PhysicalRuntime and Delta maintenance update paths in the
frozen combined candidate. It is distinct from the earlier synthetic collector
microbenchmark and from a native project integration/matrix acceptance.

Root accepts the [metadata/guard revision](c01-statistics-native-benchmark-metadata-revision-proposal/README.md),
manifest `ec56c17328662ebf3470e86c50f1249de03deee390f1897cf9a1ed454c3741c9`.
It preserves the [oracle revision](c01-statistics-native-benchmark-oracle-revision-proposal/README.md),
manifest `6c9f818a539a1f44f05169795620fd82147a661e6a861ec474af17328bbcd39b`,
and the [original](c01-statistics-native-benchmark-proposal/README.md),
manifest `a281668f3abf1a978d43fafb914fe8a6851b8876181581d755adb8cf21f53887`.
The executed corrected binary is
`ada8dae17e73c568fdec0886466d19a0352377fefb778b8ff6ef445a9b1549d8`.
The 15 runtime/collector/storage objects are the original fresh O3 production
closure; only the oracle consumer was recompiled. Metadata correction rebuilt
no C++ source. Exact flags, dependency files, empty compiler/link logs and all
object identities are recorded by the packages and root pins. Cached CROWN
core/plan/SQL archives are separately pinned Release O3 dependencies; parser
flags are not inferred from this benchmark build.

Each profile has two untimed warmups and nine measured repetitions of the same
5000 prebuilt events, seed `2026110707`, with fresh owner initialization and
configuration outside the timer. O07 is explicitly off and transition capture
is false. C01 is off, census counters, or period-64 counters at offset zero.
The external steady clock brackets only the update stream. Delta uses
begin/drain/commit and pull-draining in maintenance mode; it produces no signed
output. Capture/export, parsing, initialization, plan lowering, sink delivery,
and other output/maintenance policies are outside these timings.

| Path | C01 | Median ms / 5000 | Min–max ms | MAD ms | Change versus that path off |
| --- | --- | ---: | ---: | ---: | ---: |
| Physical apply | off | 26.488 | 26.100–27.464 | 0.258 | +0.0% |
| Physical apply | census | 54.699 | 53.855–58.107 | 0.532 | +106.5% |
| Physical apply | period 64 | 43.542 | 43.167–45.102 | 0.374 | +64.4% |
| Delta maintenance | off | 36.288 | 35.912–36.988 | 0.132 | +0.0% |
| Delta maintenance | census | 64.639 | 64.255–65.250 | 0.138 | +78.1% |
| Delta maintenance | period 64 | 53.900 | 53.122–54.499 | 0.599 | +48.5% |

These are substantial collection costs on one small synthetic engine workload.
Period-64 sampling reduces detail cost but still pays dense scratch/merge and
physical-census work. No performance threshold or production prediction is
claimed. The off comparison is the candidate's disabled-collector path; it does
not measure the incremental cost of adding its off branch against an engine
without C01. The off path is not zero-memory.

Enabled profiles admit 62 cells. Actual retained vector-capacity payload is
126608 bytes: descriptors 6944, routes 624, and three numeric slabs of 39680
bytes each. The State object is another 624 bytes in every profile. Off retains
zero descriptor/route/slab payload and exposes coverage as disabled/null, rather
than treating raw disabled metadata zeros as a measured zero-event population.
Sampling uses the same admitted slab capacities as census; its 79 complete
selected attempts and all 5000 committed physical inputs remain distinct.
Census has 5000 complete selected attempts. No abort, truncation, protocol or
ordinal degradation occurs. These component fields exclude allocator rounding,
engine storage, caller snapshots, configuration overlap and peak/total memory;
this is not S05 acceptance.

All profiles and repetitions match literal source sets, local record/S/P/E facts
covered by the guard, and independently joined final results. Mandatory work
from a separate untimed warmup agrees across profiles within each owner path.
The trace has 2647 changed and 2353 no-op inputs; 1014 changed S inputs touch
nine different reverse-bucket sizes (2 through 10). The input checksum is
`1740d5ad9b90b0de`; the common semantic checksum is `9fd143240142d6cc`.
Processing throughput is not an arrival-rate measurement or cost model.

The host was Intel Xeon Platinum 8259CL at the advertised 2.50 GHz, Linux x86-64,
GCC 13.3.0, 96 logical CPUs with affinity 0–95. Root recorded no concurrent local
compiler/build process and ran no other project execution. Host load averages
were about 0.073/0.107/0.305 before and after. This was a shared host with no
exclusive scheduling, fixed frequency or thermal control. Profile order was
fixed: Physical off/census/sample, then Delta maintenance off/census/sample.
Raw durations and dispersion are preserved; no randomized causal comparison is
inferred.

[Root summary](../../build/verification/c01-statistics-native-benchmark-root-attempt-3.json)
reconciles every reported median/min/max/MAD/throughput, profile identity,
coverage, memory component sum, input changed/no-op census and per-run checksum.
It retains 139 distinct input/artifact identities unchanged before and after.
[Raw JSON](../../build/verification/c01-statistics-native-benchmark-root-attempt-3-raw.json)
contains all 54 measured durations and actual owner configurations. Root session
17459 is terminal and closed.

The [first actual run](../../build/verification/c01-statistics-native-benchmark-root-attempt-1.json)
failed its initial untimed oracle validation: child P was incorrectly grouped
from the global answer. Native contract and independent tests require its own
local survivors projected to the parent separator. Only that expected
population changed; runtime, timed loops, trace and other expectations stayed
unchanged. The [next preflight](../../build/verification/c01-statistics-native-benchmark-input-preflight-attempt-2.json)
stopped before executing the corrected binary because one copied object digest
had 63 characters. A new sealed metadata revision corrects it and enforces
strict checksum parsing. Both failures and all original packages remain intact.
Native source publication, report sanitizer acceptance and the final C01 matrix
remain separate work.
