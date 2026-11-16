# C01 online owner hooks — excluded proposal

2026-11-07. **C01 remains `not_started`; this is not native integration or acceptance.** O07 native execution inputs remain frozen. This package writes only its own directory and uses `/tmp/crown-c01-online-*` for direct compilation. The author executed no test binary, Python checker, CMake, CTest, `nm`, network or git operation. Root owns all execution, sanitizer closure and acceptance.

The collector starts from the accepted warning-only package, whose manifest SHA-256 is `0ad7771da11e2bb545ece48ef1f2ff5b93b62856b58279ed926b3ed50cecd5fd`. That package and its original predecessor remain untouched. The four owner mirrors start from frozen native Support/Physical/Delta/Session files. The separate owner-capture overlay is not a dependency and was not modified.

## Implemented contract

The new public header is `include/crown/runtime/workload_statistics.hpp`, in namespace `crown::runtime::workload`. Include it when using the new public methods. SupportRuntime, PhysicalRuntime and DeltaRuntime expose `configure_workload_statistics`, `reset_workload_statistics`, and `workload_statistics`. QuerySession exposes guarded forwarding and an optional snapshot; after drop it returns disengaged, while stop retains committed statistics. No CMake, registration, native report or schema change is included.

One `workload::detail::State` lives inside the actual Support owner. Physical and Delta keep nonowning pointers within their existing owner lifetime. Collection is initially off, including direct/replay/bootstrap/rebuild. It retains no descriptor, route or numeric-slab payload while off. Configure is an explicit quiescent writer barrier, rejecting pending work, pinned readers and committed unread delta output. Session also rejects metadata-only window private work and uses its existing creator-thread/reentry guard. Committed snapshots remain readable during private work and unread output; the snapshot's pending flag is explicit.

Configure derives descriptors from the actual immutable plan and full source catalog. It validates dense node/occurrence/edge identities and real alias routes, includes unused physical tables, and admits all required table/op × node/role/edge strata together. Adapter and derivation descriptors retain occurrence identity and appear only for that occurrence's actual source table. Native touched-degree descriptors retain directed edge, index and event polarity; generalized candidate probes are a different role, observing actual pre-probe presence 0/1. Missing E roles receive no invented cells. Lower-only Support uses a distinct logical-epoch root for each operation; `initiating_table()` is unavailable and its numeric legacy table token is `UINT64_MAX`, never a catalog table. No physical-input ratio is available for logical roots.

Insufficient `max_cells`, invalid sampling/mode, identity/arithmetic failure or allocation failure leaves the previous configuration, slabs, generations and committed counters intact. Candidate routing plus the collector's descriptor and three numeric vectors are allocated before publication. The final swap and reset do not throw. No partial stratum admission or update-time allocation is used to compensate for a small explicit bound.

### Actual transaction and event hooks

Delta admits a root ticket before Physical prepares source membership. The extended internal API separates `admit(root)` from the later nonallocating `physical_fact(changed)` call in Physical prepare. The original `begin(descriptor, changed)` overload remains usable. Physical and Support nest tickets; their success cannot publish while the outer Delta ticket remains open. Only the final outer commit merges. Every nested rollback poisons/discards that same scratch sample, including failures after aliases, support propagation, spool production or live work. A standalone logical Support root stages its real changed/no-op fact at commit. No root fact is inferred from optional O07 observations.

Physical hooks use actual source changed/no-op, adapter acceptance, and native derivation before/after values. Support hooks use actual S membership and P/E before/after counts, including positive-to-positive changes. They run directly beside mandatory mutation facts, not from an O07 trace or user callback. Native child events observe the already-computed matching bucket length once per applied event, including zero and repeated events on the same edge. Generalized probes never masquerade as reverse-index degrees.

Root tickets, hooks, merge/abort, reset and segment rotation allocate nothing and read no clocks. Their added work is `O(H guards + min(H,B) detailed actions + K clear/merge cell visits)`; a fixed cell merge also visits 65 bins. Descriptor lookup is dense numeric indexing, with no hot map allocation, hashing, key copy, formatting or collection callback. Invalid internal routes/tickets and arithmetic saturation degrade diagnostic coverage; optional collection never adds a semantic update exception.

### Sampling, counters and rational rates

Every committed physical input, changed input and no-op is counted independently of sampling and detail truncation. Admission ordinals include retries, aborted attempts and no-ops, independently of physical sequence and O07 sampling. Selection is deterministic `(ordinal % period) == offset`, with no random-unbiased estimate, extrapolation or confidence claim. Metadata separates attempted, committed, aborted, selected, selected-aborted, complete and truncated attempts. One extra detail action beyond the finite budget discards the entire detailed sample rather than merging its prefix.

Every root cell also stores `complete_detail_inputs`: committed, selected, untruncated inputs in that initiating table/op stratum. Selected no-ops are included; aborted and truncated attempts are excluded. `events_per_physical_input` divides observed detailed events by this matching complete-sample denominator and explicitly returns `complete_detail_sample_physical_stratum`. This is an observed sample mean, not a population estimate. Period one without loss is the full census. `input_share` separately uses all committed physical inputs and retains exact full-population input counters even if optional detail truncates. Crossings divide directional crossing events by observed unequal support-count changes; adapter selectivity divides accepted by visited routes. Every fraction identifies its denominator scope.

The 65 histogram bins are zero and `[2^(b-1), 2^b-1]`, capped at `UINT64_MAX`. Support histograms observe after-values of changed events, including zero, not the current positive-key population. Histograms/count/sum/extrema are exact for the admitted complete observed samples while representable. Empty extrema are unavailable by the zero count. Saturated raw counters carry explicit lower-bound flags; derived fractions involving capped counts are **unavailable**, since a ratio of two lower bounds is not a valid bound. Per-second arrival rates and timed C01 collection remain unimplemented/unavailable. Existing independently enabled O07 timing is unchanged.

### Owning snapshots, intervals and memory

Snapshots are factory-produced handles with private immutable shared data. They expose const spans/references, retain only numeric/descriptor copies and an owning immutable plan, and accept no caller exactness/current-owner flags. Copy-like noexcept moves leave both handles readable. Historical snapshots survive update, reset, reconfiguration, mode switch, move, stop and drop without runtime rows, journals, cursors or leases.

Each snapshot carries actual Support owner, committed epoch, interval-start epoch, format version, configuration generation, reset generation and segment, with saturation flags; it owns the actual collection configuration and requested/resolved Delta mode/completion facts. These are as-of facts, not a claim that an old handle is still current. A rebuilt owner has a new identity and zero ordinary-work history even though native rebuild preserves committed sequence. Explicit configure starts its interval at that actual sequence.

Successful semantic Delta mode switches rotate exactly once after successful mode publication, even with O07 off. Failed/OOM/no-op switches leave the interval unchanged. Constructor mode/bootstrap binding does not create an observed workload segment. One previous numeric slab, previous metadata, exact previous mode facts and start/end epoch are retained; another switch replaces it and marks replaced history. Saturating the numeric segment label does not suppress a real rotation. Reset clears current/previous history and sample ordinals without allocation, changes no query epoch and increments a separate reset generation. Reconfigure increments configuration and reset generations only after success.

Memory reports actual vector `capacity() * sizeof(element)` separately for descriptors, dense routes and the three numeric slabs, plus `sizeof(State)`. Combined capacity arithmetic is checked before publication. Engine storage/fixed wrapper pointers, allocator metadata/rounding, immutable pre-existing plan allocations, caller snapshots and temporary old+new configure overlap are excluded. This is component payload accounting, not an S05 total-byte or peak-memory claim. Snapshot reads can allocate and throw without changing the owner. Drop performs no statistics snapshot allocation; its disengaged optional denotes released collection storage.

## Compile-only evidence and exact root commands

The final author build used Ubuntu GCC 13.3.0, C++23, assertions enabled and all six flags: `-Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror`. It directly compiled all nine native runtime source-list translation units (four mirrored), both new units and all three proposed test executables, then linked the approved immutable Release plan/SQL/core/parser archives. The final command completed with exit 0:

```sh
bash docs/verification/c01-statistics-online-proposal/build-only.sh /tmp/crown-c01-online-author-final
```

`build-only.sh` never runs a project executable. Its object/dependency/log outputs are under the supplied `/tmp/crown-c01-online-*` directory. `author-build.sha256` pins the three final binaries. Native inputs, dependency archives and predecessor manifests are pinned separately in `input-pins.sha256`; `package.sha256` pins this package excluding itself. `native-additions.patch` is a review aid, not authorization to edit frozen native files.

From `/home/userroot/Codex/CROWN`, root can reproduce and then execute:

```sh
bash docs/verification/c01-statistics-online-proposal/build-only.sh /tmp/crown-c01-online-root-normal
/tmp/crown-c01-online-root-normal/statistics_collection_test
/tmp/crown-c01-online-root-normal/workload_statistics_test
/tmp/crown-c01-online-root-normal/workload_statistics_exception_test
```

No test pass, OOM sweep count, throughput result or sanitizer result is claimed here. These normal binaries link Release dependencies; they must not be presented as a fully instrumented sanitizer closure.

## Proposed tests and remaining gates

The copied accepted collector fixture covers nesting/stale tickets, saturation/ordinal boundaries, bins, bounded detail, explicit invalid configuration, allocation-free hot closure and strong configure OOM. The new integration executable has ten groups:

1. Literal R/S raw-set/map hand trace and exact fractions.
2. Projection derivation/no-ops, alias predicates and generalized probes.
3. Lower-only scope, pinned-reader barriers, reset and move.
4. Multiple native touched events and skewed event weighting.
5. Mixed complete-sample denominators, overflow and readable moved handles.
6. Sampling retries, truncation and invalid configuration.
7. O07-off output parity/no-clock checks, successful/no-op/failed mode switches and direct/replay/rebuild initialization.
8. Late spool rollback, final root publication and unread output barriers.
9. Session pending/window metadata/thread/reentry/stop/drop lifetime.
10. Direct delayed-root admission and nested rollback protocol.

The exception executable covers strong configure allocation positions, same-owner update OOM plus real recovery, nonallocating commit/rollback/reset/disable and failed snapshot read, and failed mode-bootstrap OOM. Counts printed by those tests are assertions to be executed by root, not observed evidence.

Root execution may expose fixture or implementation defects; compilation alone cannot establish rollback correctness. Remaining C01 work includes merge/review with the independent explicit-state capture overlay; bounded capture and online composition; native/report/EXPLAIN/schema/API registration after O07 seal; explicit workload freshness comparisons/exports; full native semantic and fault matrices across all live/completion policies, more scalar/constraint/Boolean/disconnected cases; full sanitizer dependency closure; and measured runtime overhead/allocator/component-memory evidence. No C02 optimizer, total state-byte claim, timing/arrival estimator or acceptance status is introduced.
