# C01 statistics implementation preflight — 2026-11-07

**Design only; C01 NS.** C01 depends on O07 and R04. O07's native matrix is still frozen; begin no C01 integration until O07 is sealed. This document is the only repository write. No programs, tests, CMake, CTest, network operations or git operations were run. Requirements: `Refactor.md:912–934` and `1275–1277`. No unresolved semantic blocker was found; the following finite-scope API and implementation sequence is reviewable without introducing a cost optimizer.

## 1. Small coherent implementation

Implement two complementary collection paths, both default-off:

1. **Online event summaries:** exact committed physical operation/no-op counts plus bounded, optionally sampled event histograms stratified by initiating physical table and operation. Record occurrence adaptation acceptance, native derivation crossings, S membership changes, P/E support-count changes/crossings and parent degrees actually touched. Fixed preallocated numeric cells; no tuple copies, map insertion, JSON, clock reads in counters mode, or new runtime errors from an optional hook.
2. **Explicit state capture:** a synchronous quiescent, independently budgeted read for current cardinalities, requested projection NDVs, existing-index degree distributions, top-K heavy keys and P/E support multiplicity distributions. Complete scans are exact; exhausted scans report incomplete/unknown components. No automatic full-state scan after each update and no sketch presented as exact NDV. This path supplies exact small-data referenceability without unbounded update-maintained distinct-value dictionaries.

This meets C01's useful-statistics scope: current heavy keys are state facts at a stamped epoch; sampled touched-degree distributions are workload observations. Online top-K key-frequency sketches and statistical extrapolation of missing NDV are **not** claimed. C03 may later add estimators with explicit assumptions. C02 consumes recorded facts/unknowns only; it remains responsible for its own fallback and score.

## 2. Scope and definitions

| Scope/identity | Facts and denominator | Actual owner/read seam |
|---|---|---|
| Input source string/position | Intake identity, not a relation or arrival-rate measurement; no unbounded per-source-name map in C01 | `io::SourcePosition` / `InputProgress` in `include/crown/io/ingest.hpp:13–23`; session owns reader/queue |
| Physical source table `TableId` | Full-row **set** cardinality; accepted insert/erase attempts, changed membership, duplicate/absent no-ops; event frequency per committed physical input | `PhysicalRuntime::Impl::sources`, `physical.cpp:31–59,232–253`; includes catalog tables unused by this query |
| Occurrence `OccurrenceId` | Adapter visits/rejections, accepted physical derivations, distinct native tuples, distribution of derivation counts | `PhysicalInput.base/logical_table`, `physical.cpp:184–224`, `Impl::counts`; self-join aliases are separate even when sharing a table |
| Node records | Native adapted tuples or generalized candidate union; generalized candidates are not base rows | `support.cpp:29–38`, `PhysicalNode.records`; native/generalized kind retained |
| S(node) | Distinct surviving node tuples; membership insertions/deletions | `support.cpp:360–375`; not full output cardinality |
| P(node) | Distinct parent-projection keys; multiplicity = number of S tuples supporting each key | `NodeState.parent`, `Transaction::count/counter`; histogram population is **positive stored keys** |
| E(node), where compiled | Distinct visible-factor assignments; multiplicity = S tuples supporting each visible projection | `NodeState.visible`, `visible_relation`; non-connex absence is `not_applicable`, not zero; never full join result cardinality |
| Index requirement / directed edge | Existing reverse/visible index bucket degrees; NDV = nonempty key count; touched degree is event-weighted and directional | `PhysicalEdge.reverse_index`, `ReferencePlanStorage::index`, `ReferenceTable::State::Index::buckets` |

Use exact typed source column / node field / ordered projection IDs. Separate same-valued keys in different layouts, roles, nodes or owners. Empty projection has NDV 1 for a nonempty population and 0 for empty. Empty positive-key histograms have count/sum 0 but mean/min/max/quantiles unknown. Native `Value` currently has int64/string/bool/date/decimal and **no NULL representation**; do not invent SQL NULL statistics. Equality remains exact binary/native equality; canonical Decimal equality and byte strings must be preserved. Exports validate UTF-8 separately.

Definitions to freeze in schema/API:

- `degree_histogram`: population of existing nonempty index keys, weight one per key; sum degrees equals index membership count.
- `support_histogram`: positive P/E key counts, weight one per key; sum multiplicities equals S cardinality for that projection. Do not mistake P/E membership transitions for every support-count change.
- `touched_degree_histogram`: one observation per **applied child-key event**, including degree zero; key disappearance/appearance and operation signs are separate. Do not reduce an event multiset to “at least one event happened.”
- `heavy_keys`: top K by current degree/support count, descending count and exact native key order for deterministic ties; `population_scope`, `complete`, `top_k`, key layout and stamp mandatory. Partial scans cannot claim global top K.
- `crossing_fraction`: `(0→positive + positive→0) / support_count_changes`, with both numerators separate. Count `1→2`/`2→1` as changes without crossings. Also expose `events_per_committed_physical_input`; it is a different denominator. Rates with zero/incomplete denominators are unknown.
- `adapter_selectivity`: accepted routes / visited routes, separately per occurrence and insert/erase. This describes actual changed-row routing; duplicate physical events never visit aliases, so a no-op is not a predicate rejection.

## 3. Proposed minimal API and data shape

New `include/crown/runtime/statistics.hpp` and `src/runtime/statistics.cpp`; an internal `StatisticsState` remains below support/physical/delta/session, with no planner/report dependency. Keep configuration separate from `ObservationOptions`; O07 trace sampling and C01 sampling are independent and must both be identified in EXPLAIN.

```cpp
// Illustrative signatures; no implementation or ABI was changed here.
enum class StatisticsMode { off, counters, timed };
struct StatisticsOptions {
  StatisticsMode mode = StatisticsMode::off;
  uint64_t sample_period = 1, sample_offset = 0; // deterministic epoch sample
  size_t max_cells = 4096;                     // admitted fixed descriptor cells
  uint64_t max_detail_actions_per_attempt = 65536;
};
struct StatisticsCaptureLimits {
  uint64_t work = 1000000;
  size_t rows = 65536, distinct_keys = 65536;
  size_t accounted_bytes = 8*1024*1024, heavy_keys = 16;
};
// Immutable request owns finite source/node projections and existing index IDs.
// Capture factories derive actual owner, plan and sequence; no mutable flags
// supplied by callers can assert exactness/completeness.
void configure_statistics(const StatisticsOptions&); // exclusive quiescent barrier
void reset_statistics();                            // keeps configuration/storage
StatisticsSnapshot statistics() const;             // owning numeric summary copy
StatisticsCapture capture_statistics(const StatisticsRequest&,
                                     StatisticsCaptureLimits = {}) const;
```

Expose wrappers on SupportRuntime, PhysicalRuntime, DeltaRuntime, QuerySession. Lower-only captures explicitly have no source-table/physical-input denominator. Do **not** append another nested options structure to every existing constructor for the first slice: the explicit barrier configures the existing actual owner after construction; constructor initialization stays a separate build context. Session forwarding must use the actual owned runtime, reject reconfiguration during private work, and retain only a fixed-size release status after drop. Private state permits `statistics()` of previously committed totals with a pending flag; fresh state capture returns `pending_private_state`, without scanning tentative data. Committed unread delta output does not make state private; reconfiguration/reset should conservatively require fully quiescent writer readiness and no pinned cursor/output, matching existing `writable()` rules.

Snapshot fields: format version, owning typed plan/binding, support owner, reset generation plus saturation flag, configuration, committed epoch at reset/current capture, exact/sample/incomplete/unavailable status **per component**, sample selection policy, selected/completed/aborted/truncated attempts, committed coverage, numerator/denominator counts, histogram schema, scope descriptors, collector work, memory components and optional timing. No native binding hash/JSON construction at configuration. Runtime/plan IDs are process-local; plan handles retain metadata, not rows. Every historical report owns its configuration/stamp and survives mode changes, update, moves and owner drop.

## 4. Bounded data structures and costs

**Online:** configure constructs a new state and validated dense descriptor-to-cell routing table, then swaps it into the owner only after allocation succeeds. Include table/op, occurrence/op and selected `(initiating table, operation, edge-or-node/role)` cells within `max_cells`; validate multiplication/size arithmetic before allocating. If the plan's complete requested strata do not fit, fail this explicit configuration request with the old configuration intact; never silently drop cells or reject a later query update. A narrower explicitly selected stratum set is allowed and labeled `not_collected` elsewhere. No hot-path `std::map` of table×edge combinations.

Each admitted cell has fixed counters and a fixed 65-bin integer histogram: bin 0 for zero; bins 1..64 for `[2^(b−1), 2^b−1]` with the final bound capped at UINT64_MAX. This is an **exact binned histogram**, not an exact quantile sketch. Also retain exact observed count/sum/min/max when representable; saturation has an explicit lower-bound flag and invalidates exact derived means. Period-1 collection with no truncation gives exact event totals. Exact per-value histograms come from explicit state capture, not 65-bin interpolation.

Allocate current committed, current-attempt scratch and one previous-segment numeric slab once; nested wrappers share one root ticket. On completion combine/discard by touching only the admitted finite slabs (O(K) worst-case), then zero scratch; no dynamic undo list and no allocations in commit/abort/reset. Scalar per-table committed operation/no-op counters are always collected when enabled. Admission memory is three K-cell slabs plus fixed descriptor/routing vectors and scalar metadata; report actual capacities × sizeof(element), not a guessed constant bytes per key. Detailed cells stop at their separate attempt budget; mark the **entire detailed sample** truncated and do not merge a misleading prefix as a complete distribution. Publish exact table-level counts independently. Retain attempted/truncated metadata, not arbitrarily biased partial histograms.

An event hook has a constant guard and descriptor lookup. Selected detail performs bounded integer work with no key hashing, key comparison/copy, clock or formatting; at most B detailed actions per attempt. Total extra complexity is `O(H guards + min(H,B) detail + K begin/close)` for H existing hook visits and K admitted cells, not O(1) per physical update. Large affected buckets already imply large H; fixed budget does not remove guard cost. Report guard visits, detail actions, cleared/merged cells, saturation and selected/truncated samples so overhead is reproducible. Initially keep reset/merge O(K) explicit rather than a complicated lazy generation table.

**Sampling:** select once from a C01 admitted-attempt ordinal, independent of retrying the same physical sequence, using `(ordinal % period)==offset`. Period 1 is the exact event census. Other periods are deterministic systematic samples: report seed-free policy, eligible/selected/complete counts and coverage; no random-unbiased estimate or statistical confidence interval is claimed. Keep attempted/aborted samples separate from committed sample statistics. Never upweight partial samples into population totals. A zero-crossing frequency is known for the complete observed sample; its future/population estimate remains unknown unless a later estimator supplies assumptions.

**Explicit state scan:** use existing ordered containers and native `Row`/Tuple equality. Maintain a bounded `std::map<Row,uint64_t>` per requested projection when no existing index supplies the grouping; cap requested projection count/width, rows, distinct keys, work and component payload bytes **before** each insertion/copy. Use an accounting allocator for builder-owned map/vector nodes if an exact requested-allocation-byte counter is desired; standard allocator metadata/rounding still excluded. Charge row visits, projection fields, comparison scalar/byte work and copies, not just successful map insertions. A charge-aware comparator must compare raw byte strings with charged length/byte inspections, not invoke an unmetered arbitrarily wide `operator<` and call it one bounded action. Decimal comparison/copy is bounded by the native 38-digit domain. Do not add statistics indexes to live storage implicitly.

Existing `keys()`, `bucket()` and `snapshot()` materialize whole vectors before the caller can enforce a budget (`reference.cpp:371–377`); **do not use them as the budgeted collector primitive**. Add an explicit read-only `ReferenceTable::IndexKeyCursor` yielding a borrowed native key plus `bucket.size()`, with owner/revision invalidation like `ReferenceTable::Cursor`; one bounded startup allocation, no allocation per next, no mutation/index registration and no retained pins. Current-row traversal uses existing `live()/get()`; typed copies occur only in the allocating collector. The cursor's borrow expires with the next traversal/mutation; final reports contain owning keys only. A private support/physical `append_statistics(builder)` composes all scopes into one shared budget, preventing each layer from independently spending the full cap.

Full component completion yields exact NDV/degree/heavy-key/support distributions at the captured epoch. On work/row/key/byte cap, return component status `budget_exhausted` and progress; previously completed independent components remain exact. Incomplete NDV/top-K is null, with observed-prefix facts separately labeled if retained. A report must never call prefix distinct count exact NDV. Genuine allocation failure may throw from this explicit diagnostic call; runtime, configuration and previous reports remain unchanged.

## 5. Actual hook/source map and transaction ownership

| Native seam | Proposed addition; why this location |
|---|---|
| `support.cpp:119–142` Impl; `observation.hpp:251–291` existing root-ticket pattern | Shared optional StatisticsState owned by SupportRuntime, forwarded privately by wrappers; separate from optional O07 observer so off/timing configuration is explicit |
| `physical.cpp:232–253` prepare | Stage one table/op input and changed/no-op fact after the existing source membership test; avoid counting duplicate aliases or upstream rejected inputs |
| `physical.cpp:184–224` route | Stage visited/rejected/accepted occurrence counts and derivation before/after crossings; use existing `before/after`, do not rescan source rows or counts |
| `support.cpp:268–310` note/counter, `360–375` survivor | Stage exact positive-support before/after changes and S transitions; the existing JournalRecord metadata distinguishes member/counter changes. Do not inspect optional trace buffers or require allocating full transition capture |
| `support.cpp:414–435` child | For native parent, capture the already materialized `matching.size()` once per child event before the visit loop; degree zero counts. For generalized parent, report separate candidate probe/membership behavior; do not invent a reverse-index bucket |
| `support.cpp:1167–1204,1267–1279`; `physical.cpp:112–169,291–304`; `delta.cpp` PendingEpoch Data/rollback and `1144–1176` commit | Begin root statistics ticket at the outermost admitted owner, share it with nested physical/support work, and publish only at that root's final nonthrowing commit. Nested commit cannot publish totals early; root rollback discards staged committed facts |
| `physical.cpp:315–385`; `support.cpp:1290–1398` initialization | Construction/rebuild statistics are explicit build facts. Suppress ordinary stream hooks during unpublished direct/insertion-replay bootstrap, as existing observation initialization already does |
| `delta.cpp:1365–1377` successful set_mode | Retain data-statistics epoch, but close/reset the workload measurement interval with a new configuration segment only after a successful semantic mode switch. No-op/failed switches leave it unchanged |
| `support.cpp:1454–1470`, `physical.cpp:591–599` current gauges | Reuse exact count definitions and the same private-state exclusion; extend through bounded traversal for requested distributions, not via full diagnostic snapshots |
| `storage/reference.hpp`, `reference.cpp:34–65,236–255,370–377` | Read-only index-key cursor; retain existing owner/index/layout tokens, no membership/allocator/index-policy changes |
| `session.cpp:155–180,228–255`, public report seams | Forward actual owner capture/configuration, record window command versus physical input scopes separately; retain fixed released summary only, release collection slabs/key storage on drop |
| New runtime statistics unit; `io/explain.cpp`, `observability/explain.cpp`, v2 schema | Own immutable statistics capture in EXPLAIN; explicit unknown/stale/sample fields and timing/byte units. Report target depends on runtime; core storage never depends on report or cost planner |
| CMake runtime source list and future accepted test targets | Add statistics.cpp to both production/testing runtime variants; recompile all option/report consumers if public layouts change. No target edit is made by this document |

No hook executes allocating callbacks supplied by a caller. A sampled detail overflow/budget stop degrades statistics completeness, not update correctness. Required runtime work limits, journal/event IDs, support/derivation overflow checks and O07 metrics remain unchanged. Failures after partial aliases or after support staging never merge committed samples. Finish hooks require only saturating numeric additions, clearing fixed cells and changing status; no stringify, allocation or exception in unwind.

## 6. Reset, version, freshness, timing and lifecycle

- **Reset:** quiescent explicit call, no allocation; clear current/previous interval totals and sample ordinals, and increment a separate statistics generation with a saturation flag. Reset is not a query epoch, changes no plan/data/mandatory work, and never mutates prior report copies. Reconfiguration constructs/replaces a full collector first, then performs the same interval boundary. Defaults off; off means no collector storage, sample hooks or C01 clocks. Turning off releases slabs at the explicit barrier, not during an update.
- **Freshness:** stamp captures with actual owner + committed sequence + statistics configuration/reset generation + native format version + exact owning plan. A caller may supply a maximum lag in **committed events** for an explicit freshness comparison; this is policy, not a wall-clock inference. Same-sequence reports from a rebuilt owner are not interchangeable. Old immutable reports retain `as_of`; current EXPLAIN can label stale against its actual current owner/epoch. Default capture reports facts at its own stamp, never silently calls them current later.
- **Storage revisions are not commit versions:** `ReferenceTable::revision()` advances on tentative mutations and index changes; rollback restores membership but does not restore its cursor-invalidating revision. Use it only to validate an active scan, not to infer committed-state staleness or count updates. No-op physical events still advance committed sequence, so a conservative epoch-lag freshness policy can stale a report even if its data values happen to be unchanged.
- **Abort/OOM:** failed explicit configure/capture preserves the previous collector and engine; update allocation failure preserves old committed statistics as well as the database. Attempt/abort diagnostic counts may advance with explicit scope. No detailed sample publishes until final root commit. No-op input commits count as input frequency but not changed-row/alias/support activity. Overflow saturates diagnostic counts and invalidates exact derived results; it cannot raise a new semantic error.
- **Build/rebuild:** a new empty/direct/replay/rebuilt owner begins a new stream interval with zero observed ordinary updates. Current state counts come from explicit capture, so direct/replay initialization gives the same data statistics despite different BuildMetrics. Do not count bootstrap inserts as measured workload. `rebuilt()` returns a new owner and preserves physical committed sequence; report initialization route plus fresh owner/generation, never carry rates across it by default. Explicit copying of historical reports is allowed, with old identity intact.
- **Mode:** maintain source/S/P/E state-statistic meaning across maintenance/delta and live policies; live annotations are a separate scope, not support counters. A successful semantic mode change starts a new workload segment and records old/new resolved configuration; rotate the committed slab into the single preallocated previous-segment slot and clear the new current slab. A second switch replaces that retained slot, with replaced-history status explicit; caller-owned snapshots remain unchanged. Failed mode bootstrap/OOM leaves interval and old mode unchanged. Do not mix active-service timing across modes silently. No-op set_mode is not a segment boundary.
- **Session/window:** normal generated window deletions are real physical erase inputs. Watermark/label-only commands can advance command sequence without a physical epoch: count them, if exposed, in a distinct session-command field, not table update rates. Session pause stops admission; previously prepared scratch remains private. Stop aborts pending work and retains committed runtime/statistics while readable; drop releases all collector/slab/key memory and records `released`. Only fixed numeric status/config metadata may remain automatically; caller-owned snapshots retain their own key copies, not runtime pins. Source-position acceptance is not durability.
- **Rates/timing:** always export exact rational event shares (e.g. table inserts / all committed physical inputs). Per-second arrival rate is unknown unless an explicit measurement window supplies its clock/boundaries; upstream arrival time cannot be inferred from processing or sink callbacks. Optional timed mode accumulates active owner API-call spans only: construction/step/drain/commit spans exclude caller pause between calls; caller hold/sink/serialization/current-result demand have their own scopes. A pending lifetime is not active time. Count only outer scopes, not nested support/physical/delta timers twice. O07 nested cursor time is a subset of enclosing phases, not an additive total. Reuse the testable monotonic clock function, with separate C01 clock-read counters; counters/off read no clocks. Enabling C01 timed collection while O07 observation is off must be explicitly visible as independently enabled instrumentation; default all-off parity remains testable.

## 7. Independent acceptance fixtures and rollout gates

1. **Literal reference data:** Q `R(x,y), S(y)`, native R root/S child, head `(x,y)`; R `{(1,7),(2,7),(3,8)}`, S `{(7)}`. Source NDV(R.x)=3, NDV(R.y)=2; R S-cardinality=2, survivor NDV(y)=1; reverse R.y bucket degrees 2 and 1; heavy key 7 degree 2. Root P(empty key) has one key, support 2; root E has two full visible assignments, support 1 each. Insert S(8): touched degree 1, one R survivor appears, root P 2→3 with **no** P zero crossing. Delete S(7): touched degree 2, two survivors disappear, P 3→2→1 still no crossing. Independently derive every denominator and histogram.
2. **Derivation vs membership:** physical R(x,z) rows `(7,10),(7,11)` with ignored z in its occurrence. Native tuple 7 has derivations 2. Adding `(7,12)` changes source cardinality and derivation 2→3, not native/S/P membership. Deleting through the last derivation gives exactly one native crossing. Test duplicate insert/absent delete separately.
3. **Self-join/generalized/empty:** two aliases of R with different equalities/constants; one physical event, two routes, separate filtered/accepted denominators. Generalized candidate union vs survivor distinction, empty/Boolean/nullary plans, disconnected components, empty projection, non-connex E not-applicable, unused physical source table, empty snapshots and deterministic heavy-key ties.
4. **Exact reference:** independently group native fixture rows/visible S rows using a simple reference relation/map; compare complete state cardinality/NDV/degree/support histograms and top-K. Period 1 online counts must equal independently reconstructed committed event transitions, not only implementation metrics. FIFO/LIFO may differ in event order/work; final state statistics must agree and event-scope differences must be explained rather than erased.
5. **Conditional weighting:** trace with many events touching degree-1 keys and rare degree-100 keys; distinguish uniform-key mean from event-weighted mean and from probability of any crossing. Multiple events on one edge in one physical update remain multiple observations. Periodic adversarial traces demonstrate that deterministic sampling has no unstated unbiased guarantee.
6. **Bounds/faults:** exactly-at/one-over cells, rows, keys, width, work and component-byte limits; cap after nonzero scratch, selected sample truncation, counter/generation saturation, invalid native byte strings and very wide keys. OOM sweep explicit configuration, state capture and underlying update fault positions; no committed statistic leakage after aborted alias/support/spool/constraint work. All closure/reset paths remain allocation-free.
7. **Lifecycle/timing:** pending/prepared/paused captures, explicit cancel, unread output, pinned cursor reset rejection, failed/no-op/successful mode switches, direct/replay/rebuild equivalence, move and drop, window metadata-only commands; fake-clock caller pause excluded and C01/O07 clock scopes reconciled. Off/counters zero optional C01 clocks; all instrumentation off preserves result/journal/required-cap behavior.
8. **Measured overhead/memory:** fixed data/trace/config runs compare all-off, counters census, sampled counters and timed collection, same semantic output hash and mandatory metrics. Record hardware/build/seed, warmup/repetitions, active time/throughput and dispersion; no speedup threshold invented here. Also assert exact collector guard/detail/merge counts and admitted cell/slab capacity. Measure builder allocation-requested bytes with scoped counting allocator and high-water temporary/current/retained bytes separately. Standard allocator metadata/rounding, engine storage/arenas, caller-owned reports and temporary old+new configuration overlap remain explicit exclusions; **not S05 total allocator/live bytes**. Root runs these tests/benchmarks after implementation; none were run for this preflight.

Recommended rollout after O07 seal: (a) bounded state capture + native index-key cursor and exact reference tests; (b) transactional fixed numeric collector, root nesting, reset/version and fault tests; (c) owner/session/report wiring and rate/timing/sample tests; (d) measured overhead/component-memory evidence and full required native checks. Each slice is reviewable, but C01 is not verified until all artifact/acceptance gates above pass. No C02 ranking, recognition/search advancement, altered tree height, fabricated P06/P07 authority, cost-optimality claim, checkpoint format or recovery promise enters C01.

## Native baseline pins

The following SHA-256 pins were read from the frozen native inputs during this preflight. Recheck before integration; do not apply this design to a changed baseline without review. These are input identity checks, not runtime/test evidence.

| Frozen input | SHA-256 |
|---|---|
| `Refactor.md` | `bb90e4a4e97e2817a0869ad86c5c8b00e571bb241f153fb44641c71f86fcd5ce` |
| `CMakeLists.txt` | `81dbe6daffe09a4a769b4d02a2c3276bb9e13009ae381bb2ddc20a7851339b63` |
| `include/crown/runtime/observation.hpp` | `8ff201a70fd960dba6609ee82c45aa76a3a8d23a8960bacec051fe864becde32` |
| `include/crown/runtime/initialization.hpp` | `0db9b407824801d690d0bf6422323240fba00b57a276d3f3e1f46d04427d2c40` |
| `include/crown/runtime/support.hpp` | `54f27d7b62479c88415ad3c26416e7086ddcc1920212707bd987f669c569f160` |
| `include/crown/runtime/physical.hpp` | `8c10eee6be58db515b57af67c7a46506e3bf7c01d58c3f09f6bc732979570594` |
| `include/crown/runtime/delta.hpp` | `ddd60c1583b03555943b0013a4dd6030e7e4222375b9660851e535f508f0f9c8` |
| `include/crown/runtime/session.hpp` | `590658d4ef804a916ba0f8004da2a5bf797a4c2e6a8a20d80e00993a081e9e67` |
| `include/crown/runtime/window.hpp` | `38446a5054d5a41fcf84e9732b8d1cbb1469e53ec30ad2f44747bc1697e1a05a` |
| `include/crown/storage/reference.hpp` | `0c4ca86f88d8210e3beddec9b912f293095fb9873d220e22de76ccdb961506e9` |
| `include/crown/storage/physical.hpp` | `02c518031b20a10713add793489c1e5d123d89faa4272dd04667259d849859f6` |
| `include/crown/ir/model.hpp` | `e0f4e162b0eeff12a864f94ff40258f19d7753b282215c5259c4e5ef9d6cdaec` |
| `include/crown/ir/scalar.hpp` | `24fe26bf2b32ce3960d744a4209c6ccfec545fef830245e2c56e28f9cafa00a4` |
| `include/crown/ir/physical.hpp` | `6851fb17c7efb4a23f139ccef1eac00eb30ba556fd824c099db4bd7db4e8054f` |
| `include/crown/io/ingest.hpp` | `4924bf5d2837d25175fc848fb0354ef509673601ccf8cb7dac36361f25f9536c` |
| `src/storage/reference.cpp` | `74a2e5b92a72c4a98f4034d8ef6c441181c2fac91433eaedf6250c93308ba2b4` |
| `src/storage/physical.cpp` | `bf8e660b3b246ce8939e88825c034569b4960c1ec8b08f47f505421bbe2ab365` |
| `src/runtime/observation.cpp` | `0bf7cda74c132206de6b3194b5a8e319d2cfd840f5af175c19cdb1de20f8bc82` |
| `src/runtime/support.cpp` | `0f3b62a22bcabb2c24586852e886321f8b11e3d17faaba507dc897f4dbc45afe` |
| `src/runtime/physical.cpp` | `54222792d22afe8dce5dc496a7a18d5a8c4962f2258e4db24bdc293375be871b` |
| `src/runtime/delta.cpp` | `17bf227b5d2e6fe1abb1d1cc75a14065e03c8b953223f73c007bfdb6e721111f` |
| `src/runtime/session.cpp` | `21912440bd3827aa9b8b92f86ad141291290c01bce4739255054ad3804645e95` |
| `src/runtime/window.cpp` | `c352de333cfb2386949beae12ae607811cdc1a445cc77b3c6a16e55fe30ef172` |
| `src/runtime/inspection_detail.hpp` | `47519666dccaf6610305f27111b965fcf28f9a11fed10c1685dfc40024477e1b` |
| `src/observability/explain.cpp` | `632e0248507f62d0d69585448f5457b53f14382cac3a8cb1b7c41426b76f2303` |
| `src/io/explain.cpp` | `31a3d3f13347dbd84f2c81b56f389891d71c8ccdace259c7d81c0fa4149ca8be` |
| `schemas/explain-report-v2.schema.json` | `c4aa8c7c62e0608d7b035128a9bd9b561387c0c16491efa704d8b95b469c9f74` |
