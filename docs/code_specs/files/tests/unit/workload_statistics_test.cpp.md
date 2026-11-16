# `tests/unit/workload_statistics_test.cpp` — block usage map

[Source](../../../../../tests/unit/workload_statistics_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `fd759cdc87fe3b01189ad3a1fc37cb68b137f9a0064f8955cca9c5a9d3adced6`. 453 lines partitioned into 21 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../tests/unit/workload_statistics_test.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 10–18](../../../../../tests/unit/workload_statistics_test.cpp#L10) | Type/record definition: struct CollectorTestAccess | 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 19–20](../../../../../tests/unit/workload_statistics_test.cpp#L19) | declares namespace scope. |  · [reviewed contract](#b0003) |
| [B0004 · 21–23](../../../../../tests/unit/workload_statistics_test.cpp#L21) | Type/record definition: struct StateTestAccess |  · [reviewed contract](#b0004) |
| [B0005 · 24–29](../../../../../tests/unit/workload_statistics_test.cpp#L24) | declares namespace scope; declares aliases. | source comment (unverified): // The oracle stores raw physical sets and independently recomputes literal · [reviewed contract](#b0005) |
| [B0006 · 30–44](../../../../../tests/unit/workload_statistics_test.cpp#L30) | Type/record definition: struct Expected | 1 loop sites; source comment (unverified): // The oracle stores raw physical sets and independently recomputes literal · [reviewed contract](#b0006) |
| [B0007 · 45–118](../../../../../tests/unit/workload_statistics_test.cpp#L45) | Callable definition: void literal_hand_trace() | calls plan, runtime, delta_options, configure_workload_statistics; guard check(snapshot.stamp().owner==runtime.owner() && snapshot.stamp().committed_epoch==runtime.sequence…; returns result; growth insert; 7 loop sites · [reviewed contract](#b0007) |
| [B0008 · 119–154](../../../../../tests/unit/workload_statistics_test.cpp#L119) | Callable definition: void projection_aliases_and_generalized() | calls runtime, plan, configure_workload_statistics, enabled; guard check(ins.changes==2 && ins.zero_to_positive==1 && ins.sum==3);; growth insert; 3 loop sites; source comment (unverified): // One physical row fans out to two child events: this must stay a multiset. · [reviewed contract](#b0008) |
| [B0009 · 155–180](../../../../../tests/unit/workload_statistics_test.cpp#L155) | Callable definition: void lower_scope_and_barriers() | calls runtime, plan, configure_workload_statistics, enabled; guard check(pending.stage({0},{n(1),n(7)})); check(pending.stage({1},{n(7)}));; growth insert; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 181–210](../../../../../tests/unit/workload_statistics_test.cpp#L181) | Callable definition: void direct_noop_census_and_sampling() | calls runtime, plan, configure_workload_statistics, enabled; guard const auto epoch=runtime.apply(updates\[i\]); check(epoch.native_changed==changed\[i\] && epoch.sequenc…; growth insert; 3 loop sites · [reviewed contract](#b0010) |
| [B0011 · 211–246](../../../../../tests/unit/workload_statistics_test.cpp#L211) | Callable definition: void native_touched_event_multiset() | calls planner::lower_tree, runtime, delta_options, n; guard check(edge&lt;compiled.edges().size());; growth insert; 6 loop sites; source comment (unverified): // A skewed event multiset differs from the two nonempty keys' uniform mean. · [reviewed contract](#b0011) |
| [B0012 · 247–287](../../../../../tests/unit/workload_statistics_test.cpp#L247) | Callable definition: void sampled_rate_denominators_and_overflow() | calls runtime, plan, delta_options, n; guard check(report.cells()\[root\].inputs==7 && report.cells()\[root\].complete_detail_inputs==3 && report.ce…; growth insert; 2 loop sites; source comment (unverified): // selected degree 1; exactly 8 detail actions · [reviewed contract](#b0012) |
| [B0013 · 288–319](../../../../../tests/unit/workload_statistics_test.cpp#L288) | Callable definition: void sample_retry_and_truncation() | calls runtime, plan, delta_options, configure_workload_statistics; guard const auto staged=runtime.workload_statistics(); check(staged.pending() && staged.metadata().detail…; growth insert; 2 loop sites · [reviewed contract](#b0013) |
| [B0014 · 320–320](../../../../../tests/unit/workload_statistics_test.cpp#L320) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0014) |
| [B0015 · 321–321](../../../../../tests/unit/workload_statistics_test.cpp#L321) | Callable definition: std::uint64_t clock() noexcept | calls ; returns ++clock_calls · [reviewed contract](#b0015) |
| [B0016 · 322–362](../../../../../tests/unit/workload_statistics_test.cpp#L322) | Callable definition: void modes_initialization_and_parity() | calls detail::set_observation_clock_for_testing, plan, off, delta_options; guard check(off.workload_statistics().memory().retained_payload_bytes==0);; growth insert; 3 loop sites · [reviewed contract](#b0016) |
| [B0017 · 363–381](../../../../../tests/unit/workload_statistics_test.cpp#L363) | Callable definition: void late_abort_and_output_barrier() | calls delta_options, runtime, plan, configure_workload_statistics; guard auto after=runtime.workload_statistics(); check(runtime.sequence()==2 && runtime.ready());; growth insert · [reviewed contract](#b0017) |
| [B0018 · 382–433](../../../../../tests/unit/workload_statistics_test.cpp#L382) | Callable definition: void sessions_and_owning_lifetime() | calls delta_options, QuerySession::create_typed, plan, configure_workload_statistics; guard check(session-&gt;enqueue(batch)==io::Admission::accepted); session-&gt;finish_input(); session-&gt;start();; returns position==bytes.size()?traits_type::eof():traits_type::to_int_type(bytes\[position\]); next; growth insert, make_unique; 1 loop sites; source comment (unverified): // A metadata-only window command has private work without a Delta ticket. · [reviewed contract](#b0018) |
| [B0019 · 434–443](../../../../../tests/unit/workload_statistics_test.cpp#L434) | Callable definition: void delayed_root_admission() | calls configure, enabled, admit, nest; guard check(collector.finish(support,true) && collector.finish(physical,true));; growth insert · [reviewed contract](#b0019) |
| [B0020 · 444–446](../../../../../tests/unit/workload_statistics_test.cpp#L444) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(!std::is_default_constructible_v&lt;ws::Snapshot&gt;); · [reviewed contract](#b0020) |
| [B0021 · 447–453](../../../../../tests/unit/workload_statistics_test.cpp#L447) | Callable definition: int main() | calls literal_hand_trace, projection_aliases_and_generalized, lower_scope_and_barriers, direct_noop_census_and_sampling · [reviewed contract](#b0021) |

## B0001

[Lines 1–9](../../../../../tests/unit/workload_statistics_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:7da20c66efe8142a56b7d674db3c50425a89f2e9cef6bf4cce56ba119a2f4aef
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare workload_statistics_test.cpp: include "workload_statistics_fixture.hpp", "statistics_collection.hpp", "workload_statistics_detail.hpp", &lt;iostream&gt;, &lt;sstream&gt;, &lt;thread&gt;, &lt;type_traits&gt;. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 10–18](../../../../../tests/unit/workload_statistics_test.cpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CollectorTestAccess {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seed committed collector counters to their saturation boundary through test-only access. |
| inputs / outputs | Mutable Collector reference enters; committed cells have counters set to UINT64_MAX and saturated=true. |
| invariants | Only the test friend bypasses runtime event hooks; it deliberately creates otherwise unreachable boundary state. |
| ownership | Mutates collector-owned committed cells; no snapshot is retained. |
| failure | No expected failure. |
| cost | One pass over committed cells; writes fixed numeric fields. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0003

[Lines 19–20](../../../../../tests/unit/workload_statistics_test.cpp#L19); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L20:sha256:477aaf0b44b91b27658e7d6f37950525b8a961ff8ef768593271b2f52da2ed0a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare workload_statistics_test.cpp: declare the recorded helper API/type boundary. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 21–23](../../../../../tests/unit/workload_statistics_test.cpp#L21); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct StateTestAccess {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seed workload State's collector saturation for ratio-unavailability checks. |
| inputs / outputs | Mutable State reference enters; delegates to CollectorTestAccess::saturate. |
| invariants | This is test-only private-state setup for overflow behavior, not an API for production counters. |
| ownership | Mutates State-owned Collector in place. |
| failure | No expected failure. |
| cost | One pass over committed cells, delegated to B0002. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0005

[Lines 24–29](../../../../../tests/unit/workload_statistics_test.cpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L29:sha256:7e5782cd4a4d33db48f8b62a8d6743b1652989ca2c0cae4d9ab8de8e654a9acd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare workload_statistics_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 30–44](../../../../../tests/unit/workload_statistics_test.cpp#L30); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Expected {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Maintain an independent numeric oracle for event cells and support transitions. |
| inputs / outputs | Expected contains one Cell; observe(value) updates min/max/count/sum/log bin; support(before,after) counts only changed transitions and observes the after value. |
| invariants | Does not call Cell::observe/merge or collector hooks; every event is counted as supplied; zero is bin zero; transition boundaries are exact. |
| ownership | Expected cells are local test-owned scalar arrays; no runtime pointer or Snapshot is held. |
| failure | Counter overflow is not tested here; test fixture values remain small. |
| cost | Constant fixed-width counter work plus at most 64 integer divisions per observation. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0007

[Lines 45–118](../../../../../tests/unit/workload_statistics_test.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void literal_hand_trace() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconstruct the R(x,y) AND S(y) workload trace from raw physical sets and compare every snapshot. |
| inputs / outputs | Builds independent source sets/maps, applies fourteen physical events, updates literal derivation/S/P/E/degree counters, and checks each runtime snapshot. |
| invariants | Inputs/noops, accepted adapters, derivation transitions, survivor/support changes, and native touched degrees are derived from the literal sets; committed snapshot matches every Cell; all physical inputs form input-share denominator; event means use matching complete sample inputs; arrival rate unavailable. |
| ownership | Raw Relations/maps and Expected cells are owned by the test; runtime owns its separate source/index state; each Snapshot owns its descriptor/cell copy. |
| failure | Unexpected runtime/assertion errors fail the function; no allocation fault injection here. |
| cost | Fourteen fixed updates, literal regrouping of small relations, per-event snapshot copies and full-cell comparison; no timing claim. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md), [Refactor.md](../../../../../Refactor.md) |

## B0008

[Lines 119–154](../../../../../tests/unit/workload_statistics_test.cpp#L119); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void projection_aliases_and_generalized() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check projection aliases, generalized probes, adapter outcomes, and repeated child-event multiplicity. |
| inputs / outputs | Runs a projected ignored-witness R plan, a tagged two-alias predicate plan, and a same-key two-child event. |
| invariants | Duplicate witness changes derivation but only zero-boundary membership changes S/P/E; right alias reject is counted; generalized probe values are 0/1 and distinct from reverse-index degree; one input may fan out to multiple child events. |
| ownership | Each PhysicalRuntime owns its independent compiled state; report snapshots own counters until replaced. |
| failure | Unexpected operation/assertion error propagates. |
| cost | Executes fixed six/two-event traces and scans descriptor arrays for role counts. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0009

[Lines 155–180](../../../../../tests/unit/workload_statistics_test.cpp#L155); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void lower_scope_and_barriers() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check SupportRuntime logical-epoch observations, busy barriers, and reset generation. |
| inputs / outputs | Stages two node events in one pending epoch, observes private snapshot, commits, tests result cursor barrier, resets, and moves runtime. |
| invariants | Support descriptors are logical_epoch with no initiating physical table; physical input shares and events-per-physical-input are unavailable; tentative work is pending; reset is blocked while transaction/cursor active and changes only collector generation. |
| ownership | Report snapshot owns cells after collector reset; SupportRuntime owns support graph/cursor until release. |
| failure | Expected busy paths require runtime_busy; other errors propagate. |
| cost | One epoch with two staged actions and a small number of snapshots/reset/barrier checks. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0010

[Lines 181–210](../../../../../tests/unit/workload_statistics_test.cpp#L181); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void direct_noop_census_and_sampling() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare direct SupportRuntime no-op/changed census with deterministic period-1 and period-3 sampling. |
| inputs / outputs | Applies eight fixed native updates, including duplicate insert/absent erase, under period 1 and period 3 offset 1. |
| invariants | Sequence advances for all accepted attempts; no-op epochs have zero work/no journal; all eight logical inputs remain denominator while selected detail complete count is census or selected sample count. |
| ownership | SupportRuntime owns state; each workload snapshot owns its cells and stamp. |
| failure | Unexpected update/configuration errors propagate; no faults injected. |
| cost | Two eight-update runs and fixed descriptor aggregation. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0011

[Lines 211–246](../../../../../tests/unit/workload_statistics_test.cpp#L211); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void native_touched_event_multiset() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify native touched-degree counters are an event multiset including zero and repeated bucket degrees. |
| inputs / outputs | Builds R(x,y), T(y,z), S(z) tree with three parent keys; applies child updates to keys 10/11/12; compares each touched degree to a literal parent-key map, then repeats skewed key events. |
| invariants | Counts each touched child event, including zero degree and repeated hot-key update/erase; reports sum 3 across degrees 2,1,0 with one zero, distinct from the uniform mean over nonempty keys. |
| ownership | Literal degree map and runtime snapshots are independently owned. |
| failure | Any missing edge/descriptor or event mismatch fails the test; no expected error. |
| cost | Scans the small parent table per touched key and computes a finite histogram; not a sampled population scan or benchmark. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0012

[Lines 247–287](../../../../../tests/unit/workload_statistics_test.cpp#L247); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sampled_rate_denominators_and_overflow() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check sampled event means and input shares use different denominators, with truncation, aborts, and saturation. |
| inputs / outputs | Creates seven parent rows across keys with degrees 1/3/3, selects every second attempt, uses detail budget 8, commits seven child inputs, aborts two attempts, and seeds saturated counters. |
| invariants | Physical share uses all 7 committed physical inputs; degree mean uses 3 complete selected detail inputs and is incomplete after one selected truncation; aborted selected work is excluded; saturated numerator/denominator ratios are unavailable. |
| ownership | Snapshots own values through move/copy assignments; test-only State access mutates a separate collector after copied reports exist. |
| failure | Configuration/update errors are not expected here; saturation becomes unavailable fractions rather than thrown arithmetic errors. |
| cost | Runs a fixed trace, move/copy snapshots, and scans fraction descriptors; no timing or probability estimator. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0013

[Lines 288–319](../../../../../tests/unit/workload_statistics_test.cpp#L288); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sample_retry_and_truncation() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check selected aborted retry ordinals, all-or-nothing detail truncation, and invalid option rollback. |
| inputs / outputs | Selected attempt is drained then rolled back; retry commits at next ordinal; reconfigures with budgets 0 and 1, tests invalid period/cell capacity, then disables. |
| invariants | Abort consumes sampling ordinal; selected abort publishes no detail; truncated detail clears all nonphysical cells while exact input changed counter remains; failed configure preserves current cells/generation; disable releases collector payload; retained prior Snapshot stays immutable. |
| ownership | Retained Snapshot owns cells/descriptors across reconfiguration and disable; runtime owns active collector. |
| failure | Expected period/cell validation throws invalid_argument/length_error; update allocation not injected. |
| cost | Finite traces with two detail budgets and option reconfiguration; repeated snapshot copies. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0014

[Lines 320–320](../../../../../tests/unit/workload_statistics_test.cpp#L320); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t clock_calls=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count test-clock invocations while workload statistics are enabled and runtime modes are changed. |
| inputs / outputs | The adjacent \`clock()\` returns \`++clock_calls\`; \`modes_initialization_and_parity()\` installs it, applies two rows, changes delta modes, exercises a failed mode change and rebuilds, and asserts the counter remains zero before restoring the default clock. |
| invariants | The tested workload collector exposes counters only; this assertion is limited to those exact scenarios. The unsynchronized counter is test state, not a thread-safe clock service. |
| ownership | The scalar counter is owned by the test process; the test callback receives no runtime state and retains nothing. |
| failure | The callback has no explicit overflow/failure handling; the exercised call count is expected to remain zero. Runtime mode-change errors are asserted by the surrounding test helper. |
| cost | The injected callback would perform one integer increment per call; the test proves none of these tested operations invoke it. It measures neither CPU nor elapsed time. |
| Design | [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [include/crown/runtime/workload_statistics.hpp §Mode and Snapshot](../../../../../include/crown/runtime/workload_statistics.hpp), [include/crown/runtime/observation.hpp §test clock hook](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp §read_observation_clock](../../../../../src/runtime/observation.cpp), [tests/unit/workload_statistics_test.cpp §modes_initialization_and_parity](../../../../../tests/unit/workload_statistics_test.cpp) |

## B0015

[Lines 321–321](../../../../../tests/unit/workload_statistics_test.cpp#L321); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t clock() noexcept { return ++clock_calls; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide a deterministic monotonic test clock callback with an observable read counter. |
| inputs / outputs | No input; increments and returns clock_calls. |
| invariants | C01 counter/off test uses the callback only to prove zero calls; it does not measure arrival or duration. |
| ownership | Only the test global counter is mutated. |
| failure | No expected failure; noexcept callback. |
| cost | One increment/read per call. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0016

[Lines 322–362](../../../../../tests/unit/workload_statistics_test.cpp#L322); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void modes_initialization_and_parity() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check off/counters output parity, zero C01 clock reads, mode segmentation, and initialization/rebuild stamps. |
| inputs / outputs | Installs test clock, runs same inserts with collector off/on, rotates delta/maintenance segments, tests a failed maintenance bootstrap, direct/replay initialization and rebuild. |
| invariants | Signed outputs and canonical states match with counters enabled; C01 reads no clock; no-op set_mode keeps segment; real mode changes rotate one previous segment and preserve old caller snapshot; failed mode change keeps old segment; new/rebuilt owner starts with no historical counters. |
| ownership | Old/current Snapshot values own their cells and mode fields; runtimes own collector and plan. |
| failure | Failed mode bootstrap expects resource_limit; other errors fail; test clock is restored to null at end. |
| cost | Two fixed event runs, segment rotations and two build methods; no timing run. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0017

[Lines 363–381](../../../../../tests/unit/workload_statistics_test.cpp#L363); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void late_abort_and_output_barrier() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check late spool abort does not publish detail and output barriers block collector mutation. |
| inputs / outputs | Uses spool_row_limit=0 to fail after detail staging; separately prepares/drains pending output, attempts reset/configure while busy, commits/discards, then resets. |
| invariants | Late abort preserves committed cells and sequence while abort/detail-action metadata advances; pending output keeps committed count unchanged until commit and blocks configure/reset until discarded. |
| ownership | Runtime owns pending transaction/output until commit/discard; prior Snapshot is an owning value. |
| failure | Expected late spool failure is resource_limit; busy operations are runtime_busy. |
| cost | Runs two fixed updates and one failed plus one committed pending update; no output enumeration benchmark. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0018

[Lines 382–433](../../../../../tests/unit/workload_statistics_test.cpp#L382); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sessions_and_owning_lifetime() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise QuerySession thread ownership, pending/stopped/dropped snapshots, window metadata-only work, and reentrant stream protection. |
| inputs / outputs | Queues two updates, drives session epochs, captures stats, rejects reset during pending; separately uses window watermark command and a custom reentrant streambuf callback. |
| invariants | Session thread affinity is enforced; pending work is private; stop rolls back but keeps committed snapshot readable; drop releases live collector while saved Snapshot remains owning; watermark command is pending without physical update; reentrant session query during stream read fails session_busy. |
| ownership | Session owns runtime/collector/stream; copied Snapshot survives session drop; streambuf is test-owned and calls a borrowed session pointer only while live. |
| failure | Expected codes include session_pending_epoch, runtime_busy, session_wrong_thread, and session_busy; no code is swallowed. |
| cost | Performs fixed queue/update/window operations, one worker thread call, and stream parse; verifies no output-time estimate. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0019

[Lines 434–443](../../../../../tests/unit/workload_statistics_test.cpp#L434); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void delayed_root_admission() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Ensure an outer collector admission delays all nested physical/support publication until root success. |
| inputs / outputs | Configures a two-descriptor Collector; admits outer, physical, and nested support ticket; records facts; finishes children then aborts root. |
| invariants | Cells remain zero after child success and are discarded when outer finishes false; aborted count increments once. |
| ownership | Collector owns descriptors/slabs; local ticket tokens cannot outlive this test. |
| failure | Protocol is expressed through false return values; no exception expected. |
| cost | One fixed three-level ticket sequence and two numeric updates. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0020

[Lines 444–446](../../../../../tests/unit/workload_statistics_test.cpp#L444); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static_assert(!std::is_default_constructible_v<ws::Snapshot>);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce that workload snapshots are factory-produced owning handles and expose cells through a read-only span. |
| inputs / outputs | \`Snapshot\` cannot be default-constructed; \`cells()\` on \`const Snapshot&\` must have type \`std::span&lt;const ws::Cell&gt;\`. |
| invariants | The span is read-only and borrows snapshot-owned Data; callers must retain a Snapshot handle while using it. The assertions do not prove all snapshot fields or capture behavior. |
| ownership | Snapshot copies share their immutable Data handle; Data owns copied numeric arrays and plan metadata rather than runtime rows. The returned span does not own those cells. |
| failure | These assertions fail compilation if the API shape changes. Runtime snapshot capture allocates separately and may throw on account or upstream allocation failure; no capture operation runs in this block. |
| cost | Compile-time only. Snapshot capture and its account-funded arrays are separate runtime work; the \`memory()\` report distinguishes reported collector payload from snapshot allocation. |
| Design | [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [include/crown/runtime/workload_statistics.hpp §Snapshot](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp §Snapshot::Data and snapshot capture](../../../../../src/runtime/workload_statistics.cpp) |

## B0021

[Lines 447–453](../../../../../tests/unit/workload_statistics_test.cpp#L447); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the ten workload-statistics integration groups. |
| inputs / outputs | No input; invokes literal hand trace, aliases/generalized, lower-scope barriers, no-op sampling, touched-degree multiset, retry/truncation, modes, late abort, sampled ratios, sessions/lifetime, and delayed root admission. |
| invariants | Snapshot type is non-default-constructible and exposes const Cell span; individual groups verify transactional observations, exact denominator scope, explicit unknown/saturated availability, and owner lifetime. |
| ownership | All owners, models, sessions, and snapshots are local values; snapshots deliberately outlive resets/session drop in called groups. |
| failure | Unexpected assertion/native failures fail main; expected error codes are checked in helpers. |
| cost | Runs finite deterministic traces and repeated descriptor/cell comparisons; not a benchmark or generic update-cost theorem. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |
