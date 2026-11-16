# C01 combined state and workload proposal

2026-11-07. **C01 remains `not_started`. This package is excluded preparation, not native implementation or verification.** It merges the two root-accepted C01 slices and adds an owner-driven joint capture. Strict production and testing variants compile and link; root has not yet executed the combined package. [BUILD_RESULTS.md](BUILD_RESULTS.md) records the evidence and [ROOT_REPRODUCTION.md](ROOT_REPRODUCTION.md) gives exact next commands.

The accepted [owner package](../c01-statistics-owner-generalized-revision-proposal/README.md), manifest `dc7276b9c6427784f67372a95efa0365de3859203a0c1706fe2fe494ef02869e`, and [online package](../c01-statistics-online-proposal/README.md), manifest `61281d60312f371930a6ddcb4c2c51570eb6d5c70264432715a7da0a3d247281`, remain unchanged. All writes for this task are confined to this directory and distinct `/tmp/crown-c01-combined-*` compile outputs. Native source/header/test/schema/CLI/CMake files are unchanged. Root has sealed O07 separately; its acceptance does not advance C01.

## Merge and authority

[source-map.md](source-map.md) lists all 35 overlay files and their eventual native destinations. The four shared runtime sources preserve the accepted online bodies and hooks, then add the accepted state capture/freshness definitions. Their headers expose both APIs. The unique state and online implementations are copied unchanged. Every accepted owner/storage/collector/online assertion is preserved. The only inherited fixture edit is equivalent in-place construction of an ignored-column variant to satisfy GCC's full `-O2` warning checks; [the one-line patch](build-evidence/fixture-construction.patch) and failed initial warning log are recorded.

SupportRuntime, PhysicalRuntime and DeltaRuntime additionally expose:

```cpp
statistics::CombinedCapture capture_combined_statistics(
    const statistics::OwnerRequest&, statistics::Limits limits = {}) const;
```

QuerySession exposes the corresponding optional result, disengaged after runtime release. Include [combined_statistics.hpp](overlay/include/crown/runtime/combined_statistics.hpp). `CombinedCapture::state()` and `workload()` return const references to owning reports. The joint handle has no default constructor, public constructor from reports, mutable metadata or public exactness switches. Its constructor is private to the four actual owner classes. The mutable state builder and numeric collector remain fully defined only under `src/runtime`.

One synchronous capture reads both domains from the actual runtime. Before publishing the joint handle, the constructor checks support-owner identity, committed sequence, owning physical-plan identity and pending-state agreement. A mismatch raises `statistics_binding` rather than publishing a mixed pair. This comparison checks forwarding consistency between factory-produced handles; it grants no new Catalog/Query admission or structural proof authority.

Direct runtime capture follows the native single-writer contract. It introduces no callback, write, reset or drain between its two reads; it is not a new concurrent-read guarantee. Session capture holds one existing creator-thread/reentry guard across both reads. A session-private barrier, including metadata-only window work, creates the accepted metadata-only state report and a pending workload snapshot at the same actual committed boundary without exposing private rows. No recursively guarded public Session method is called.

Joint data is private and immutable. Copies and copy-like moves share that immutable owned payload and leave both handles readable. The report owns its keys, descriptors and immutable plan/layout handles, retaining no runtime owner pointer, row lease, journal, cursor or result pin. All three allocation stages—state read, workload copy and final joint control allocation—can fail without changing runtime state or a prior report. No update path calls the allocating state or joint diagnostic.

## Independent populations and stamps

The state request and facts preserve the accepted source/native/generalized/S/P/E/index distinctions. Source scopes include unused catalog tables; native occurrence distributions use actual derivation counts; generalized records are candidate unions; P/E distributions use actual positive support maps; reverse/index distributions use existing bucket degrees. A generalized node's output-only separator determines C* membership; the corrected accepted fixture requires all three present E distributions and separately checks a genuinely hidden separator. No whole `snapshot()`, `keys()` or `bucket()` materialization is introduced for state diagnostics.

Complete distributions retain exact NDV, positive-key multiplicity histograms and top-K. An incomplete distribution has unknown NDV/top-K and no fabricated histogram, while earlier complete components remain exact. Non-connex E is `not_applicable`; lower-only source scopes are `unavailable`. Pending captures retain current actual stamps but no tentative component facts. Public freshness compares an actual owner and committed sequence using an explicit maximum event lag. Storage revision remains invalidation metadata; rollback does not make unchanged committed data stale. Equal rebuilt/replayed data has a foreign owner identity.

Online populations remain independent: physical input census distinguishes changed inputs and no-ops; support observations count unequal before/after events; touched degrees measure actual directed edge probes. Event after-value histograms are not current positive-key histograms. Deterministic sample ordinals include aborts/retries/no-ops; truncated detail attempts publish no partial detailed sample. Matching complete-sample stratum denominators remain explicit. Off/counters mode, sampling period/offset, finite detail-action cap, admitted cells, reset/configuration generations, interval start, mode segment and previous segment are retained from the actual collector. There is no timed mode, arrival-rate measurement, extrapolation or implicit population estimate.

The joint handle deliberately keeps these domains separate. A no-op advances committed data freshness. Reset changes workload history/generation without changing data epoch. A successful mode switch rotates workload segments without changing data facts. An aborted update can change attempt metadata while preserving committed cells and state. `CombinedCapture` asserts boundary agreement when captured; it does not add a caller-controlled or fused “all current/exact” flag.

## Bounds and accounting

One finite state budget is shared across all selected layers/components: work actions, visited rows, new distinct keys and cumulative accounted component bytes. Accepted charge-before-copy/insert behavior, checked component/field-vector size products and charged raw byte comparison/finalization are unchanged. An earlier exact component survives a later exhausted component. Query-fixed selection admission is bounded by 256 requests. Bounded grouping can still be quadratic in admitted rows/keys and stops at the work cap.

State `accounted_bytes` models report/weighted control payloads, requested component and field-vector payloads, owning row/string/finite Decimal payloads, group/link allowances, histogram requests and heavy-vector payloads. It is cumulative logical payload, not allocator usage or peak live memory. Caller request construction, caller report copies/retention, pre-existing immutable plans/layouts, allocator bookkeeping/rounding, spare capacity, fixed cursor startup allocation, native engine storage, library scratch/stack and cleanup remain excluded. No layout/projection descriptor is built during owner scanning.

Online memory reports separately model vector capacity times element size for admitted descriptors, dense routes and three numeric slabs, plus the State object. Admission checks the arithmetic before publishing a configuration. Engine storage/fixed wrapper pointers, allocator control/rounding, immutable plan allocations, caller snapshots and simultaneous old/new configuration storage remain excluded. Hot hooks, commit/abort, reset and rotation allocate nothing and read no clocks; their guard/detail/cell/bin work is not erased from the cost model when collection is on.

The new joint read adds workload descriptor/current/previous numeric snapshot copies and one fixed shared control allocation. Those costs are outside the state scan's `Limits::accounted_bytes` and state usage. Workload copies are bounded by the already-admitted `max_cells` and fixed descriptor/cell sizes; the report does not relabel them as state component bytes. Total retained reports, allocator metadata, configure overlap, export formatting and native engine memory need separate limits/evidence. This package makes no S05 total-allocator or peak-memory claim.

## Added joint assertions

The new ordinary executable has nine groups, compiled in both production and testing variants:

1. Off/configured owner/epoch/plan agreement, successful S insertion, duplicate no-op and exact input/detail denominators.
2. Physical private preparation excludes state components; rollback preserves committed state/cells and current data freshness while exposing abort metadata.
3. Two support after-value events differ from the final one-key P population; reset advances workload generation and interval start without advancing data epoch.
4. Delta pending-before/after-drain and committed unread capture agree; no-op and real mode switches preserve the proper independent domains.
5. Failed mode construction and a real late spool-limit abort preserve the prior combined boundary and committed data.
6. Lower-only availability, period-two sampling and state-budget exhaustion remain independent; an exact earlier component survives exhaustion.
7. Rebuild changes owner and clears collection history; runtime moves and immutable retained report moves preserve historical facts.
8. Session private/pause/stop/drop behavior composes under one guard and retained reports remain readable after drop.
9. Six real inputs run through off/on Delta owners with every signed output and canonical state compared; each capture is also checked against independent literal row maps.

The literal maps independently derive source projection, native derivation, survivors, P/E and existing reverse-index facts from source sets, including P/E histogram sums equal to S cardinality. They do not use production statistics output or the old unaccepted JSON as the oracle. The inherited owner/storage/online suites remain separate and unchanged so a joint assertion cannot replace their coverage.

One new allocation sweep enumerates capture allocation failures until first success on the same actual Delta owner, with a retained previous workload segment. After every failure it checks owner/epoch, canonical state, invariants, historical state/workload and a successful recovery capture. It covers the ordinary allocations used by these non-overaligned types; it is not a universal aligned-allocation fault framework. Actual failure totals await root execution.

## Evidence and remaining work

`INPUT_SHA256SUMS` pins actual external build and design inputs; `source-files.sha256` pins all overlay bytes; `PACKAGE_SHA256SUMS` pins every package file except itself. Expanded commands and per-artifact hashes are retained under `build-evidence`. Both macro variants compile every affected runtime consumer anew, with matching overridden storage ahead of the frozen archives. Four native report consumers also compile unchanged. No mixed runtime linkage, sanitizer pass, native test pass or measured overhead is inferred from this compile evidence.

[The EXPLAIN integration inventory](explain-integration-inventory.md) identifies the existing closed v2 `cost.statistics = unavailable` contract, the open C01 gate and the need to expose independently configured C01 alongside O07 in standalone benchmark reports. It proposes an explicit versioned opt-in while retaining default v2 bytes, and lists typed key transport, bounded export, owner authority and schema tests still needed. It creates no replacement schema or serializer.

Root still needs combined ordinary/fault execution and full sanitized dependency closure. Native API/CMake/report/schema/CLI registration, combined policy matrices across maintenance/completion/order variants, wider scalar/constraint/Boolean/disconnected/window cases, measured native-engine overhead and component-memory evidence remain open. C02 cost selection and structural guarantees remain separate. No status file is updated by this package.
