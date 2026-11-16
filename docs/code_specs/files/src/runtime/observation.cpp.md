# `src/runtime/observation.cpp` — block usage map

[Source](../../../../../src/runtime/observation.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Collect optional counters/traces/clocks while preserving measured-zero versus unavailable fields.

Snapshot SHA-256: `2bb0f90b401c46f1cdc2eb8be2947fd68ba73a3747377d956c876d20e1c696f4`. 269 lines partitioned into 32 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–19](../../../../../src/runtime/observation.cpp#L1) | Imports dependencies; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_trivially_copyable_v&lt;DeltaOptions&gt;);; source comment (unverified): // These inline diagnostic values remain nonallocating through copy, unwind, · [reviewed contract](#b0001) |
| [B0002 · 20–41](../../../../../src/runtime/observation.cpp#L20) | Callable definition: ObservationConfiguration ObservationConfiguration::capture(const DeltaOptions& options, DeltaMode resolved,DeltaCompletion comple… | calls ; returns result · [reviewed contract](#b0002) |
| [B0003 · 42–58](../../../../../src/runtime/observation.cpp#L42) | Callable definition: DeltaOptions ObservationConfiguration::requested_options() const noexcept | calls ; returns result · [reviewed contract](#b0003) |
| [B0004 · 59–94](../../../../../src/runtime/observation.cpp#L59) | declares namespace scope; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0004) |
| [B0005 · 95–119](../../../../../src/runtime/observation.cpp#L95) | Member/declaration region. |  · [reviewed contract](#b0005) |
| [B0006 · 120–124](../../../../../src/runtime/observation.cpp#L120) | Callable definition: void increment(std::uint64_t& value,std::uint64_t amount,bool& saturated) noexcept | calls max · [reviewed contract](#b0006) |
| [B0007 · 125–129](../../../../../src/runtime/observation.cpp#L125) | controls preprocessing; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0007) |
| [B0008 · 130–130](../../../../../src/runtime/observation.cpp#L130) | Callable definition: std::span&lt;const MetricDescriptor&gt; observation_registry() noexcept | calls ; returns registry · [reviewed contract](#b0008) |
| [B0009 · 131–131](../../../../../src/runtime/observation.cpp#L131) | declares namespace scope. |  · [reviewed contract](#b0009) |
| [B0010 · 132–141](../../../../../src/runtime/observation.cpp#L132) | Callable definition: std::shared_ptr&lt;ObservationState&gt; ObservationState::create(const resource::MemoryAccount& account,ObservationOptions options) | calls Error; returns {}; resource::make_accounted_shared&lt;ObservationState&gt;(observation_memory_owner,account,; growth make_accounted_shared · [reviewed contract](#b0010) |
| [B0011 · 142–147](../../../../../src/runtime/observation.cpp#L142) | Callable definition: ObservationState::ObservationState(const resource::MemoryAccount& account,ObservationOptions options) :options_(options),buffer_(… | calls options_, buffer_, resize; growth resize · [reviewed contract](#b0011) |
| [B0012 · 148–151](../../../../../src/runtime/observation.cpp#L148) | Callable definition: ObservationSummary* ObservationState::target() noexcept | calls ; returns &*snapshot_.current; snapshot_.last?&*snapshot_.last:nullptr · [reviewed contract](#b0012) |
| [B0013 · 152–182](../../../../../src/runtime/observation.cpp#L152) | Callable definition: ObservationTicket ObservationState::begin(ObservationLayer layer,std::uint64_t sequence) noexcept | calls increment, emplace, event, clocks_enabled; returns {snapshot_.current-&gt;attempt,owns}; growth emplace; 1 loop sites; source comment (unverified): // Nested layers share the outer attempt. Trace sampling uses physical · [reviewed contract](#b0013) |
| [B0014 · 183–191](../../../../../src/runtime/observation.cpp#L183) | Callable definition: void ObservationState::finish(ObservationTicket ticket,ObservationOutcome outcome) noexcept | calls event, increment, reset · [reviewed contract](#b0014) |
| [B0015 · 192–201](../../../../../src/runtime/observation.cpp#L192) | Callable definition: void ObservationState::set(MetricId id,std::uint64_t amount) noexcept | calls target · [reviewed contract](#b0015) |
| [B0016 · 202–204](../../../../../src/runtime/observation.cpp#L202) | Callable definition: void ObservationState::unavailable(MetricId id) noexcept | calls target · [reviewed contract](#b0016) |
| [B0017 · 205–210](../../../../../src/runtime/observation.cpp#L205) | Callable definition: void ObservationState::add(MetricId id,std::uint64_t amount) noexcept | calls target, increment · [reviewed contract](#b0017) |
| [B0018 · 211–222](../../../../../src/runtime/observation.cpp#L211) | Callable definition: void ObservationState::event(TraceKind kind,std::uint64_t event_id,std::uint64_t cause, std::uint64_t node,std::uint64_t occurren… | calls size, increment; source comment (unverified): // Numeric records only, in the admitted fixed buffer. Full traces report · [reviewed contract](#b0018) |
| [B0019 · 223–225](../../../../../src/runtime/observation.cpp#L223) | Callable definition: bool ObservationState::clocks_enabled() const noexcept | calls ; returns options_.mode==ObservationMode::timed \|\| (options_.mode==ObservationMode::trace && options_.trace_t… · [reviewed contract](#b0019) |
| [B0020 · 226–229](../../../../../src/runtime/observation.cpp#L226) | Callable definition: std::uint64_t ObservationState::now() noexcept | calls add, read_observation_clock; returns read_observation_clock() · [reviewed contract](#b0020) |
| [B0021 · 230–236](../../../../../src/runtime/observation.cpp#L230) | Callable definition: std::uint64_t read_observation_clock() noexcept | calls test_clock, std::chrono::steady_clock::now, time_since_epoch, count; returns test_clock(); tick&gt;0?static_cast&lt;std::uint64_t&gt;(tick):0 · [reviewed contract](#b0021) |
| [B0022 · 237–237](../../../../../src/runtime/observation.cpp#L237) | Callable definition: ObservationSnapshot ObservationState::snapshot() const noexcept | calls ; returns snapshot_ · [reviewed contract](#b0022) |
| [B0023 · 238–242](../../../../../src/runtime/observation.cpp#L238) | Callable definition: ObservationTrace ObservationState::trace() const | calls assign, begin; returns result · [reviewed contract](#b0023) |
| [B0024 · 243–249](../../../../../src/runtime/observation.cpp#L243) | Callable definition: CapturedObservationTrace ObservationState::capture_trace() const | calls result, get_allocator, account, assign; returns result; source comment (unverified): // Explicit owning diagnostic copy on the live buffer account; hot event · [reviewed contract](#b0024) |
| [B0025 · 250–253](../../../../../src/runtime/observation.cpp#L250) | Callable definition: ObservationSnapshot observation_snapshot(const std::shared_ptr&lt;ObservationState&gt;& state,ObservationOptions options) noexcept | calls snapshot; returns state-&gt;snapshot(); result · [reviewed contract](#b0025) |
| [B0026 · 254–257](../../../../../src/runtime/observation.cpp#L254) | Callable definition: ObservationTrace observation_trace(const std::shared_ptr&lt;ObservationState&gt;& state,ObservationOptions options) | calls trace, observation_snapshot; returns state-&gt;trace(); {observation_snapshot(state,options),{}} · [reviewed contract](#b0026) |
| [B0027 · 258–262](../../../../../src/runtime/observation.cpp#L258) | Callable definition: CapturedObservationTrace capture_observation_trace(const std::shared_ptr&lt;ObservationState&gt;& state, ObservationOptions options,con… | calls capture_trace, result, observation_snapshot; returns state-&gt;capture_trace(); result · [reviewed contract](#b0027) |
| [B0028 · 263–263](../../../../../src/runtime/observation.cpp#L263) | controls preprocessing. |  · [reviewed contract](#b0028) |
| [B0029 · 264–264](../../../../../src/runtime/observation.cpp#L264) | Callable definition: void set_observation_clock_for_testing(ObservationClock clock) noexcept | calls  · [reviewed contract](#b0029) |
| [B0030 · 265–265](../../../../../src/runtime/observation.cpp#L265) | Callable definition: void set_observation_initial_generation_for_testing(std::uint64_t value) noexcept | calls  · [reviewed contract](#b0030) |
| [B0031 · 266–266](../../../../../src/runtime/observation.cpp#L266) | Callable definition: std::uint64_t observation_initial_generation_for_testing() noexcept | calls ; returns test_initial_generation · [reviewed contract](#b0031) |
| [B0032 · 267–269](../../../../../src/runtime/observation.cpp#L267) | controls preprocessing. | source comment (unverified): // namespace detail · [reviewed contract](#b0032) |

## B0001

[Lines 1–19](../../../../../src/runtime/observation.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/runtime/observation.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep diagnostic configuration/value copies nonallocating as observation metadata evolves. |
| inputs / outputs | Includes observation/native Delta types and ownership; static_assert checks trivial DeltaOptions/configuration and noexcept Snapshot copy/assignment. |
| invariants | Shared immutable admission/session/benchmark metadata handles may release owned graphs on destruction; nonallocating copies do not imply constant-time last-owner teardown. |
| ownership | Declarations/assertions allocate no runtime storage; later ObservationState holds original-account buffer and shared metadata. |
| failure | Compile failure exposes a future violation rather than adding a runtime guard/catch. |
| cost | Compile-time checks only. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 20–41](../../../../../src/runtime/observation.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ObservationConfiguration ObservationConfiguration::capture(const DeltaOptions& options,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze requested Delta options and resolved runtime configuration into inline diagnostic metadata. |
| inputs / outputs | Options,resolved mode/completion,owner,generation/saturation and factor count copy all support/physical/delta/cursor/spool/observation policies into ObservationConfiguration. |
| invariants | Requested and resolved values remain distinct; owner/generation are process-local descriptive identity,not proof/durable authority. Saturated generation is capped diagnostic only. |
| ownership | Fixed scalars/optionals, no runtime,row,account or lookup pointer retained. |
| failure | noexcept,no validation/allocation or configuration change. |
| cost | Fixed field copy independent of data size. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp), [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp) |

## B0003

[Lines 42–58](../../../../../src/runtime/observation.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaOptions ObservationConfiguration::requested_options() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconstruct the exact requested DeltaOptions values from a captured configuration. |
| inputs / outputs | Readable ObservationConfiguration returns copied requested options,not resolved overrides. |
| invariants | Does not restore/reconfigure a runtime or import/refill a captured budget; resolved mode/completion remain separate getters. |
| ownership | Inline options value, no owned graph. |
| failure | noexcept,no allocation or live owner access. |
| cost | Fixed field assignments. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0004

[Lines 59–94](../../../../../src/runtime/observation.cpp#L59); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
namespace {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define immutable support/physical/early-Delta metric descriptors in enum index order. |
| inputs / outputs | Static registry entries name ID,unit,provenance,attempt scope,layer,kind and inclusion notes for mandatory support/physical and initial Delta counters. |
| invariants | Registry IDs are the direct array indexes used by hooks. Attempted/aborted work is not committed state change; physical inclusive/exclusive scope and nested work overlap remain explicit. |
| ownership | Static literal strings/array storage,returned views need no account. |
| failure | No runtime lookup construction,allocation or registration failure. |
| cost | Static table; begin scans complete registry for one layer,individual hooks index directly. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0005

[Lines 95–119](../../../../../src/runtime/observation.cpp#L95); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
{MetricId::delta_replay_preparation_work, "delta.replay_preparation_work", "abstract_actions", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::delta, MetricKind::counter, "subset of layer work; not additive with total"},
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe remaining Delta replay/output/timing/clock metric scopes without double-counting. |
| inputs / outputs | Registry continuation records replay subwork,spool peaks,mapped/transferred/discarded/serialization/sink/ack counts and disjoint timing/clock fields. |
| invariants | Replay phase work is a subset of layer work. Nested cursor clock reads exclude later current-result reads and must not be added to per-cursor totals twice. Timing fields can be disabled independently of mandatory counters. |
| ownership | Static literal metadata only. |
| failure | No runtime action or handler. |
| cost | Static bounded descriptors,not instrumentation allocations. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0006

[Lines 120–124](../../../../../src/runtime/observation.cpp#L120); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void increment(std::uint64_t& value,std::uint64_t amount,bool& saturated) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Saturate observation counts without wrapping exact diagnostic values. |
| inputs / outputs | U64 reference,amount and sticky flag add if representable,otherwise cap MAX and set saturated. |
| invariants | Exactly reaching MAX without overflow stays exact unless caller treats a timing MAX as a cap sentinel. Later overflow never clears saturation. |
| ownership | Mutates fixed numeric fields only. |
| failure | noexcept,no query failure/allocation. |
| cost | Constant bound/add. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0007

[Lines 125–129](../../../../../src/runtime/observation.cpp#L125); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#ifdef CROWN_RUNTIME_TESTING
detail::ObservationClock test_clock=nullptr;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide testing-only deterministic clock and initial-generation seeds. |
| inputs / outputs | CROWN_RUNTIME_TESTING defines private test_clock=null and test_initial_generation=0. |
| invariants | Exclusive test ownership is required; no production mutable configuration or budget-import seam. |
| ownership | Static test callback pointer/scalar; callback lifetime belongs to test. |
| failure | No runtime allocation or callback invocation here. |
| cost | Testing storage only,absent from ordinary production. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0008

[Lines 130–130](../../../../../src/runtime/observation.cpp#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::span<const MetricDescriptor> observation_registry() noexcept { return registry; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the immutable ordered observation registry. |
| inputs / outputs | Returns span&lt;const MetricDescriptor&gt; over static registry. |
| invariants | Descriptor strings/static entries do not grant metric values or authority. |
| ownership | Borrows static lifetime, no owner handle needed. |
| failure | noexcept,allocation-free. |
| cost | Constant span construction. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0009

[Lines 131–131](../../../../../src/runtime/observation.cpp#L131); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L131-L131:sha256:5535809b42b9d97cdfea935b5d84662804aaab9873ce9d79d846ab3ec8a625cb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/observation.cpp: opens namespace \`detail\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0010

[Lines 132–141](../../../../../src/runtime/observation.cpp#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<ObservationState> ObservationState::create(const resource::MemoryAccount& account,ObservationOptions options) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate observation policy and fund enabled state only at admission. |
| inputs / outputs | Readable account and options require known mode,positive sample period and offset&lt;period; off returns null state,otherwise accounted shared ObservationState. |
| invariants | Off still validates options but leaves mandatory native budget accounting enabled elsewhere. No per-event account creation; caller uses original account. |
| ownership | Enabled shared holder/buffer belongs to supplied account observation/0. Off retains no optional state allocation. |
| failure | Invalid options throw existing Error before state allocation; account/buffer failure unwinds private construction. |
| cost | Fixed checks and enabled holder plus trace-capacity allocation in constructor. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0011

[Lines 142–147](../../../../../src/runtime/observation.cpp#L142); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ObservationState::ObservationState(const resource::MemoryAccount& account,ObservationOptions options)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preallocate the only live causal trace buffer before maintenance hooks execute. |
| inputs / outputs | Options copied into snapshot and account-funded TraceRecord vector resized to trace_capacity only in trace mode. |
| invariants | Fixed numeric records contain no rows/strings/pins/callbacks. Timed/counter modes keep empty buffer; later event never grows it. |
| ownership | Original account MemoryAllocator uses observation purpose/attribution; source options borrowed only during copy. |
| failure | Resize/account failure before state publication; no rollback framework. |
| cost | O(trace_capacity) fixed-record initialization/storage in trace mode; constant otherwise. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0012

[Lines 148–151](../../../../../src/runtime/observation.cpp#L148); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ObservationSummary* ObservationState::target() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the active attempt summary or the last summary for post-attempt output diagnostics. |
| inputs / outputs | Returns current summary pointer if present,else last,else null. |
| invariants | Last summary can receive later output/serialization/sink metrics under caller ticket/owner protocol; no new native attempt implied. |
| ownership | Pointer borrows ObservationState snapshot,not stable through next begin/finish/destruction. |
| failure | noexcept,no allocation. |
| cost | Constant optional tests. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0013

[Lines 152–182](../../../../../src/runtime/observation.cpp#L152); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ObservationTicket ObservationState::begin(ObservationLayer layer,std::uint64_t sequence) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Begin an outer observation attempt or join its nested runtime layer. |
| inputs / outputs | Layer/physical sequence create new current summary only when none exists; increment attempt counter,bind initialization and Delta config/benchmark/output,choose sequence-based trace sample,reset trace counters,emit begin,initialize metrics for requested layer and return ticket(attempt,owns). |
| invariants | Only outer ticket owns finish. Nested support/physical layers share one current attempt and preserve its metrics. Trace sampling is sequence%period,not C01 attempt-ordinal sampling; retries at same sequence keep same selection. Lifetime-count saturation disables trace selection and remains explicit. |
| ownership | Summary/config handles copy without allocation; buffer already funded. Caller serializes nested ticket use; diagnostic attempt IDs are not durable authority. |
| failure | noexcept,saturating counters rather than query exceptions; known private layer and valid admitted options assumed. |
| cost | One bounded registry scan plus fixed summary initialization and one trace write; no heap. Copying fixed metric array is proportional to fixed registry size. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp) |

```text
selected_=options_.mode==ObservationMode::trace && !snapshot_.lifetime_counts_saturated &&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind causal sampling to the admitted physical sequence and exact attempt identity. |
| inputs / outputs | Outer begin selects sequence%period==offset only for trace mode with unsaturated lifetime counts; reset count/dropped/disposition for this attempt. |
| invariants | Retries at same sequence may select again; this differs from C01 attempt-ordinal sampling and grants no statistical confidence. Saturation prevents pretending trace attempt IDs stay unique. |
| ownership | Fixed flags/counters and preallocated buffer prefix length,not a new buffer. |
| failure | noexcept; buffer may truncate later without query failure. |
| cost | Constant modulo/branches; no random generator or allocation. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0014

[Lines 183–191](../../../../../src/runtime/observation.cpp#L183); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ObservationState::finish(ObservationTicket ticket,ObservationOutcome outcome) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close only the owning matching observation attempt. |
| inputs / outputs | Matching owns=true ticket emits commit/abort,sets outcome,increments lifetime commit/abort counts,sets selected trace disposition,moves summary to last and clears current. |
| invariants | Nested/stale/nonowning tickets no-op. Attempted metrics survive abort; they are not committed change counts. Pure diagnostics do not commit or roll back native state. |
| ownership | Nonallocating inline/shared-handle copy; trace buffer retained. Caller must obey current outer-ticket protocol,including capped diagnostic IDs. |
| failure | noexcept,saturation explicit; no handler/inverse actions. |
| cost | Fixed summary copy and counters plus one trace event,possible last-metadata release. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0015

[Lines 192–201](../../../../../src/runtime/observation.cpp#L192); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ObservationState::set(MetricId id,std::uint64_t amount) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assign an available metric without overriding a saturated prior measurement. |
| inputs / outputs | Valid private MetricId indexes current-or-last summary; available,unsaturated value becomes amount. Timing amount MAX marks cap saturation. |
| invariants | Does not compute maxima automatically for high-water descriptors; caller supplies correct amount. Unavailable/disabled values are not fabricated by assignment. |
| ownership | Fixed target/array slot; no payload retained. |
| failure | noexcept,known enum index is caller precondition; no diagnostic string. |
| cost | Constant lookup/branches/write. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0016

[Lines 202–204](../../../../../src/runtime/observation.cpp#L202); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ObservationState::unavailable(MetricId id) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mark one metric unavailable while preserving raw attempted numeric storage. |
| inputs / outputs | Valid private MetricId sets target summary availability to unavailable if a target exists. |
| invariants | Does not zero raw value/saturation or imply disabled collection. Consumers must consult availability. |
| ownership | Fixed array slot only. |
| failure | noexcept,no allocation. |
| cost | Constant target/index write. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0017

[Lines 205–210](../../../../../src/runtime/observation.cpp#L205); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ObservationState::add(MetricId id,std::uint64_t amount) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accumulate an available optional metric with sticky overflow status. |
| inputs / outputs | Valid MetricId+amount add to current-or-last metric only when available. |
| invariants | Disabled/unavailable values remain so. Exactly observed counts and capped overflow remain distinct via saturated flag. |
| ownership | Numeric fields only. |
| failure | noexcept,saturating helper does not reject native maintenance. |
| cost | Constant index/add; no heap/clock. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0018

[Lines 211–222](../../../../../src/runtime/observation.cpp#L211); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ObservationState::event(TraceKind kind,std::uint64_t event_id,std::uint64_t cause,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one numeric causal event into the already funded sampled trace. |
| inputs / outputs | Selected attempt records event/cause/node/occurrence/prefix/before/after/role/tuple IDs; missing occurrence/prefix use current route defaults. |
| invariants | No selection means no-op. Full fixed buffer increments capped dropped count and truncated flag,never reallocates or exports tuple contents. Prefix0 means use route default in this private protocol. |
| ownership | Copies fixed numeric TraceRecord; buffer capacity owned by ObservationState original account. |
| failure | noexcept,trace loss explicit instead of query failure. Caller supplies valid route IDs; no lifetime authority. |
| cost | Constant bounds/counter or one record write,with no allocation. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp) |

```text
if (snapshot_.trace_records==buffer_.size()) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound causal event retention without reallocating on a hot hook. |
| inputs / outputs | Full buffer increments capped dropped count/marks truncation,returns before indexed write; otherwise record count stays within size. |
| invariants | Zero capacity legitimately drops begin/terminal/events and reports truncated; no fallback unbounded trace. |
| ownership | Only fixed numeric fields/pre-funded buffer. |
| failure | noexcept,native results unchanged by observation loss. |
| cost | Constant bounds/counters,no heap or row serialization. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0019

[Lines 223–225](../../../../../src/runtime/observation.cpp#L223); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool ObservationState::clocks_enabled() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decide whether this optional observation policy requests clock reads. |
| inputs / outputs | True for timed or trace with trace_timings; counter/off false. |
| invariants | This helper gates callers. now()/read_observation_clock themselves do read when called; no false claim that their bodies enforce policy. |
| ownership | Options scalar read only. |
| failure | noexcept,no clock/allocation in predicate. |
| cost | Constant mode/flag checks. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0020

[Lines 226–229](../../../../../src/runtime/observation.cpp#L226); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t ObservationState::now() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record a direct Delta clock read and return the shared observation clock. |
| inputs / outputs | Adds delta_clock_reads when that metric is available,then calls read_observation_clock. |
| invariants | Caller must check clocks_enabled if policy should suppress clocks; this method unconditionally reads. Nested cursor clocks have separate attribution API to avoid double charge. |
| ownership | No timer object or row owner retained. |
| failure | noexcept,saturates diagnostic count; clock hook must be noexcept. |
| cost | One clock call plus optional metric increment. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0021

[Lines 230–236](../../../../../src/runtime/observation.cpp#L230); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t read_observation_clock() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a real or testing observation clock without assigning a layer counter. |
| inputs / outputs | Testing hook if installed,else steady_clock nanoseconds since epoch clamped to0 for nonpositive ticks. |
| invariants | Layer/cursor callers account their own read; no hidden delta increment here. Value is diagnostic timing,not wall-time deadline authority. |
| ownership | No allocation/owned callback; testing lifetime external. |
| failure | noexcept for admitted hook/type; no conversion string. |
| cost | One test/steady clock read and fixed conversion. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0022

[Lines 237–237](../../../../../src/runtime/observation.cpp#L237); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ObservationSnapshot ObservationState::snapshot() const noexcept { return snapshot_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy fixed observation summary/configuration and owning metadata handles. |
| inputs / outputs | snapshot() returns ObservationSnapshot by value. |
| invariants | No causal-record vector copied. Captured values are as-of this serialized call; later runtime changes do not mutate the copy. |
| ownership | Fixed arrays/optionals and shared immutable metadata; may retain plan/session/benchmark context after runtime release. |
| failure | noexcept copy enforced by static assertions; destruction may release shared graphs. |
| cost | Fixed-size snapshot copy/refcount operations,no new allocation. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0023

[Lines 238–242](../../../../../src/runtime/observation.cpp#L238); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ObservationTrace ObservationState::trace() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export live trace records into ordinary caller-owned diagnostic storage. |
| inputs / outputs | Returns ObservationTrace with snapshot copy and first trace_records entries assigned to ordinary std::vector. |
| invariants | Explicit diagnostic,not called by event hooks; captures only actual retained prefix with truncation/drop metadata. |
| ownership | Ordinary vector owns record copy outside query account. Snapshot shared metadata lifetimes remain owned. |
| failure | Allocation failure propagates,drops local export,preserves state/buffer/counters. |
| cost | O(retained trace records) copy/allocation plus fixed snapshot; not allocation-free capture. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0024

[Lines 243–249](../../../../../src/runtime/observation.cpp#L243); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CapturedObservationTrace ObservationState::capture_trace() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture trace records directly into original-account owning report storage. |
| inputs / outputs | Returns CapturedObservationTrace constructed from live buffer allocator account,with snapshot and retained-record copy. |
| invariants | Distinct from ordinary export; no temporary ordinary vector or new account grant. |
| ownership | OwnerAllocator records use capture/3 and original account; returned record payload survives runtime destruction. |
| failure | Account/allocation failure drops local captured value and preserves live buffer/snapshot. |
| cost | O(retained trace records) account allocation/copy plus fixed snapshot. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0025

[Lines 250–253](../../../../../src/runtime/observation.cpp#L250); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ObservationSnapshot observation_snapshot(const std::shared_ptr<ObservationState>& state,ObservationOptions options) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return live or default-off observation snapshot without optional state allocation. |
| inputs / outputs | Existing shared state forwards snapshot(); null state returns default Snapshot with supplied options. |
| invariants | Null optional observation does not disable mandatory native budget accounting; no fake current/last attempt created. |
| ownership | Returned fixed values/owned handles only; no runtime pointer. |
| failure | noexcept,no allocation. |
| cost | Constant dispatch+fixed snapshot copy. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0026

[Lines 254–257](../../../../../src/runtime/observation.cpp#L254); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ObservationTrace observation_trace(const std::shared_ptr<ObservationState>& state,ObservationOptions options) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export optional live trace or an empty explicit caller trace. |
| inputs / outputs | Existing state forwards ordinary trace(); null state returns default snapshot plus empty vector. |
| invariants | Empty/disabled trace is not an unsampled successful attempt; disposition stays explicit. |
| ownership | Live path owns ordinary record vector; null path retains no state. |
| failure | Only live export allocation can throw; state remains unchanged. |
| cost | Constant null path,otherwise O(records) ordinary copy. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0027

[Lines 258–262](../../../../../src/runtime/observation.cpp#L258); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CapturedObservationTrace capture_observation_trace(const std::shared_ptr<ObservationState>& state,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture optional live trace with its real account or create empty funded-handle result. |
| inputs / outputs | Live state uses its own buffer account through capture_trace; null uses explicit account for empty CapturedObservationTrace and default snapshot. |
| invariants | No cross-account silent deep clone on live path or fresh allowance. Native retained reports use original live account. |
| ownership | Returned vector allocator retains chosen existing account,with records copied only if live. |
| failure | Live capture allocation may fail; empty result normally allocates no record payload. |
| cost | Constant null case,otherwise O(records) account-owned copy. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0028

[Lines 263–263](../../../../../src/runtime/observation.cpp#L263); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L263-L263:sha256:c4b9c3fab52d74ef772a80090ef4a35760b5a3b41ee88be876eed0db22a2fcbd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/observation.cpp: opens/branches compile-time guard \`#ifdef CROWN_RUNTIME_TESTING\`. |
| inputs / outputs | Preprocessor definitions select which tokens compile; any members or declarations in this span are those explicitly listed in its source lines. |
| invariants | The preprocessor guard pairs with its matching directive; it is a compile-time boundary, not a runtime mode. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0029

[Lines 264–264](../../../../../src/runtime/observation.cpp#L264); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void set_observation_clock_for_testing(ObservationClock clock) noexcept { test_clock=clock; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set testing-only observation clock callback. |
| inputs / outputs | ObservationClock replaces private test_clock; nullptr restores real steady clock; no callback is invoked here. |
| invariants | Exclusive test ownership; no production option/source/budget authority. |
| ownership | Fixed callback pointer or scalar,external callback context/lifetime. |
| failure | noexcept,no allocation or clock invocation by these accessors. |
| cost | Constant read/write,absent ordinary production entrypoint. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0030

[Lines 265–265](../../../../../src/runtime/observation.cpp#L265); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void set_observation_initial_generation_for_testing(std::uint64_t value) noexcept { test_initial_generation=value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set testing-only observation initial generation seed. |
| inputs / outputs | U64 value replaces private test_initial_generation; no clock read or runtime configuration is performed. |
| invariants | Exclusive test ownership; no production option/source/budget authority. |
| ownership | Fixed callback pointer or scalar,external callback context/lifetime. |
| failure | noexcept,no allocation or clock invocation by these accessors. |
| cost | Constant read/write,absent ordinary production entrypoint. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0031

[Lines 266–266](../../../../../src/runtime/observation.cpp#L266); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t observation_initial_generation_for_testing() noexcept { return test_initial_generation; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read testing-only observation initial generation seed. |
| inputs / outputs | Returns private test_initial_generation as U64; does not read a clock or mutate a runtime. |
| invariants | Exclusive test ownership; no production option/source/budget authority. |
| ownership | Fixed callback pointer or scalar,external callback context/lifetime. |
| failure | noexcept,no allocation or clock invocation by these accessors. |
| cost | Constant read/write,absent ordinary production entrypoint. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0032

[Lines 267–269](../../../../../src/runtime/observation.cpp#L267); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L267-L269:sha256:8995d5166eb16084f1540083a440d8af2be09996018d587b2b0241b8a371f390
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/observation.cpp: closes the matching compile-time guard; closes \`namespace detail\`, \`namespace crown::runtime\`. Source comment: namespace detail namespace crown::runtime |
| inputs / outputs | Preprocessor definitions select which tokens compile; any members or declarations in this span are those explicitly listed in its source lines. |
| invariants | The preprocessor guard pairs with its matching directive; it is a compile-time boundary, not a runtime mode. Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. The source note says: namespace detail namespace crown::runtime Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
