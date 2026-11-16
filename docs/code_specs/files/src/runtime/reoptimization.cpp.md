# `src/runtime/reoptimization.cpp` — block usage map

[Source](../../../../../src/runtime/reoptimization.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Coordinate input, window control, native epoch preparation, output delivery and durable recovery at one session lifecycle boundary.

Snapshot SHA-256: `448e836fd4ad2cea02f4f1d9563c6045495cf967261e206385817188b1b47057`. 251 lines partitioned into 28 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [session](../../../subsystem_contracts.md#session). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/session-journal.md](../../../../session-journal.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/reoptimization.md](../../../../reoptimization.md), [docs/native-replay.md](../../../../native-replay.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../src/runtime/reoptimization.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 8–44](../../../../../src/runtime/reoptimization.cpp#L8) | Callable definition: PolicyDecision evaluate(const Policy& policy,const std::optional&lt;Forecast&gt;& forecast, std::uint64_t current_epoch,std::optional&lt;s… | calls max, add; returns result; result; source comment (unverified): // ceil(current * basis_points / 10000), without an overflowing product. · [reviewed contract](#b0002) |
| [B0003 · 45–47](../../../../../src/runtime/reoptimization.cpp#L45) | declares namespace scope. | source comment (unverified): // namespace crown::runtime::reoptimization · [reviewed contract](#b0003) |
| [B0004 · 48–50](../../../../../src/runtime/reoptimization.cpp#L48) | Callable definition: bool Access::same_sources(const DeltaRuntime& left,const DeltaRuntime& right,Budget& budget) | calls same_sources; returns left.same_sources(right,budget) · [reviewed contract](#b0004) |
| [B0005 · 51–68](../../../../../src/runtime/reoptimization.cpp#L51) | Callable definition: State::State(const DeltaRuntime& source,const planner::MinimumHeightCandidate& candidate,Options options, std::optional&lt;std::uint… | calls account_, plan, account, options_; growth emplace; source comment (unverified): // Cold rebuild retains both native owners and compiler/snapshot overlap on · [reviewed contract](#b0005) |
| [B0006 · 69–69](../../../../../src/runtime/reoptimization.cpp#L69) | Callable definition: State::~State() | calls cancel · [reviewed contract](#b0006) |
| [B0007 · 70–70](../../../../../src/runtime/reoptimization.cpp#L70) | Callable definition: Status State::status() const | calls statistics; returns result · [reviewed contract](#b0007) |
| [B0008 · 71–74](../../../../../src/runtime/reoptimization.cpp#L71) | Callable definition: State::Clock::time_point State::time() noexcept | calls cancel, Clock::now; returns Clock::now(); Clock::now() · [reviewed contract](#b0008) |
| [B0009 · 75–78](../../../../../src/runtime/reoptimization.cpp#L75) | Callable definition: bool State::increment(std::uint64_t& value,std::uint64_t amount) noexcept | calls cancel; returns false; true · [reviewed contract](#b0009) |
| [B0010 · 79–83](../../../../../src/runtime/reoptimization.cpp#L79) | Callable definition: void State::elapsed(Clock::time_point start,std::uint64_t& value) noexcept | calls time, cancel, count, increment · [reviewed contract](#b0010) |
| [B0011 · 84–84](../../../../../src/runtime/reoptimization.cpp#L84) | Callable definition: void State::old_drain_elapsed(Clock::time_point start) noexcept | calls elapsed · [reviewed contract](#b0011) |
| [B0012 · 85–88](../../../../../src/runtime/reoptimization.cpp#L85) | Callable definition: DeltaRuntime& State::target() | calls verified, Error; returns *target_ · [reviewed contract](#b0012) |
| [B0013 · 89–96](../../../../../src/runtime/reoptimization.cpp#L89) | Callable definition: void State::charge_artifact(std::uint64_t ns,const resource::MemoryStatistics& memory,const std::array&lt;char,64&gt;& hash) | calls Error · [reviewed contract](#b0013) |
| [B0014 · 97–102](../../../../../src/runtime/reoptimization.cpp#L97) | Callable definition: bool State::publication_prepared(Clock::time_point started) noexcept | calls elapsed, active, evaluate, cancel; returns false; active() · [reviewed contract](#b0014) |
| [B0015 · 103–105](../../../../../src/runtime/reoptimization.cpp#L103) | Callable definition: DeltaRuntime State::take_target() noexcept | calls std::move, reset; returns result · [reviewed contract](#b0015) |
| [B0016 · 106–114](../../../../../src/runtime/reoptimization.cpp#L106) | Callable definition: void State::complete_publication(Clock::time_point started,Clock::time_point selected,Clock::time_point cleaned) noexcept | calls count · [reviewed contract](#b0016) |
| [B0017 · 115–118](../../../../../src/runtime/reoptimization.cpp#L115) | Callable definition: void State::request_barrier() noexcept | calls active, verified · [reviewed contract](#b0017) |
| [B0018 · 119–119](../../../../../src/runtime/reoptimization.cpp#L119) | Callable definition: void State::waiting_output() noexcept | calls active · [reviewed contract](#b0018) |
| [B0019 · 120–120](../../../../../src/runtime/reoptimization.cpp#L120) | Callable definition: void State::barrier_progress() noexcept | calls active, frozen, verified · [reviewed contract](#b0019) |
| [B0020 · 121–124](../../../../../src/runtime/reoptimization.cpp#L121) | Callable definition: void State::clear_entries() noexcept | calls reset, std::move; 1 loop sites · [reviewed contract](#b0020) |
| [B0021 · 125–127](../../../../../src/runtime/reoptimization.cpp#L125) | Callable definition: void State::cancel(Phase phase,Stop stop) noexcept | calls reset, clear_entries · [reviewed contract](#b0021) |
| [B0022 · 128–131](../../../../../src/runtime/reoptimization.cpp#L128) | Callable definition: void State::rollback_stage() noexcept | calls reset · [reviewed contract](#b0022) |
| [B0023 · 132–169](../../../../../src/runtime/reoptimization.cpp#L132) | Callable definition: void State::stage(const DeltaRuntime& source,const PhysicalUpdateView& update) noexcept | calls active, time, verified, owner; growth make_accounted_unique; 1 loop sites; source comment (unverified): // A failed candidate must not block the ordinary writer. The staged record · [reviewed contract](#b0023) |
| [B0024 · 170–176](../../../../../src/runtime/reoptimization.cpp#L170) | Callable definition: void State::committed(std::uint64_t sequence) noexcept | calls active, cancel, get, std::move · [reviewed contract](#b0024) |
| [B0025 · 177–181](../../../../../src/runtime/reoptimization.cpp#L177) | Callable definition: void State::pop() noexcept | calls std::move, reset · [reviewed contract](#b0025) |
| [B0026 · 182–206](../../../../../src/runtime/reoptimization.cpp#L182) | Callable definition: void State::advance(std::uint64_t quantum) noexcept | calls active, verified, time, emplace; growth emplace; 1 loop sites · [reviewed contract](#b0026) |
| [B0027 · 207–250](../../../../../src/runtime/reoptimization.cpp#L207) | Callable definition: void State::verify(const DeltaRuntime& source) noexcept | calls active, verified, frozen, caught_up; growth copy_of, emplace, insert; 1 loop sites; source comment (unverified): // Compare complete source and result sets at the frozen same-epoch barrier. · [reviewed contract](#b0027) |
| [B0028 · 251–251](../../../../../src/runtime/reoptimization.cpp#L251) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime::reoptimization::detail · [reviewed contract](#b0028) |

## B0001

[Lines 1–7](../../../../../src/runtime/reoptimization.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/runtime/reoptimization.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble explicit candidate migration and pure payback policy. |
| inputs / outputs | Reoptimization public/private state,Error and arithmetic helpers. |
| invariants | C06 operates on typed checked candidates and native set state; caller time forecasts,observed costs and height proof remain separate authorities. |
| ownership | Declarations own no candidate/account or source row. |
| failure | No runtime handler here. |
| cost | Compile-time includes/namespaces. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 8–44](../../../../../src/runtime/reoptimization.cpp#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PolicyDecision evaluate(const Policy& policy,const std::optional<Forecast>& forecast,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate exact hysteresis/saving/payback arithmetic without granting switch authority. |
| inputs / outputs | Policy,optional caller Forecast,current/last epoch and measured PreparationCosts return PolicyDecision with explicit invalid/unavailable/threshold/overflow/payback stop. |
| invariants | Requires valid basis points&lt;=10000,nonfuture switch epoch,gap,positive horizon and target&lt;current. Uses ceil saving threshold and quotient/remainder payback without horizon products. Eligibility is only an assumption/model decision, not source/equivalence/memory/durable proof. |
| ownership | Pure inline inputs/result; no owner,account,clock or allocation. |
| failure | noexcept; errors are value stops. Checked cost addition may leave partial diagnostic sum on overflow. |
| cost | Fixed U64 comparisons/divisions/adds, allocation-free; not a measured future performance guarantee. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp) |

## B0003

[Lines 45–47](../../../../../src/runtime/reoptimization.cpp#L45); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L47:sha256:a2af52afd8dbb568c0eb3bee1d19126b1d2df77d4b3e9ebe73806c5410656e5e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/reoptimization.cpp: opens namespace \`crown::runtime::reoptimization::detail\`; closes \`namespace crown::runtime::reoptimization\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. The source note says: namespace crown::runtime::reoptimization Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0004

[Lines 48–50](../../../../../src/runtime/reoptimization.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool Access::same_sources(const DeltaRuntime& left,const DeltaRuntime& right,Budget& budget) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare exact source state through native runtime ownership and equivalence budget. |
| inputs / outputs | Actual DeltaRuntime source/target plus shared Budget forward private same_sources. |
| invariants | Requires native writer-ready owners,same epoch and source-set equality; source catalogs/plans were bound during target rebuild. No public snapshot/import authority. |
| ownership | Borrows owners; delegated account-funded row-set scratch uses original account and ordinary native indexed grants. |
| failure | Budget/native/allocation failures propagate to verify cancellation boundary. |
| cost | Full source-table scans and ordered native row comparisons/copies, not a constant hash-only check. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp) |

## B0005

[Lines 51–68](../../../../../src/runtime/reoptimization.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
State::State(const DeltaRuntime& source,const planner::MinimumHeightCandidate& candidate,Options options,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Privately rebuild an admitted candidate at the exact actual-source epoch on the original account. |
| inputs / outputs | Source,typed MinimumHeightCandidate,Options,optional last switch,start time/selection cost verify expected owner/epoch then source.rebuilt_for,record identities/lowering/build work and elapsed snapshot/rebuild phase. |
| invariants | Original source remains intact; target gets fresh owner with same admitted source/options/output meaning. Minimum-height authority belongs to candidate,not forecast. Source must be writer-ready; caller started clock before State allocation. |
| ownership | Account retains original source plan account; target/compiler/runtime/snapshot overlap all share it. Options/status fixed; no ordinary source/program DTO export. |
| failure | Stale binding/rebuild/work/account exception destroys private State/target and leaves old runtime available. Timing counter/regression cancellation can leave inactive failed state without throwing. |
| cost | Explicit cold replan,snapshot/rebuild/live bootstrap and dual-owner peak; starts before funded State allocation. Separate compiler/build grants and native account apply. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0006

[Lines 69–69](../../../../../src/runtime/reoptimization.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
State::~State() {cancel();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release any private candidate migration resources on State destruction. |
| inputs / outputs | Destructor calls cancel() with default cancelled phase. |
| invariants | Does not alter installed source runtime or roll back an authoritative durable root; caller session retains those gates/locks. |
| ownership | Drops pending target epoch,staged/backlog entries,target runtime,then member handles. |
| failure | No throwing cleanup; account/node/native destructors own unwind. |
| cost | O(backlog entries+target resident state) teardown with bounded iterative ledger stack. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp) |

## B0007

[Lines 70–70](../../../../../src/runtime/reoptimization.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Status State::status() const {auto result=status_;result.query_memory=account_.statistics();return result;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report candidate progress together with cumulative original-account memory. |
| inputs / outputs | Copies Status then samples account.statistics() into query_memory. |
| invariants | Current/peak include old+target+ledger/scratch across query lifetime; not a phase-local peak. Compiler input memory is separately captured field. |
| ownership | Fixed report values, no source row/target pointer exposed. |
| failure | Account diagnostic failures can propagate; no status mutation or new memory grant. |
| cost | Fixed report copy+actual account statistics query; no source/result scan. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp) |

## B0008

[Lines 71–74](../../../../../src/runtime/reoptimization.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
State::Clock::time_point State::time() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read candidate-only steady clock while enforcing clock-read counter. |
| inputs / outputs | When below MAX increment status.clock_reads and return Clock::now; at MAX cancel candidate with counter_overflow and still return a clock value. |
| invariants | Cancellation clears target/pending/ledger. Stage and verify recheck active immediately after this read; advance skips a cleared head. Other callers either guard target access or continue only the still-authoritative old owner. |
| ownership | Mutates fixed status and may release candidate state; no source/runtime mutation. |
| failure | noexcept; overflow cancels rather than wraps. Clock return alone does not certify candidate remains active. |
| cost | One clock read/counter on normal path; overflow includes full cancel teardown, no new allocation. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp) |

## B0009

[Lines 75–78](../../../../../src/runtime/reoptimization.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool State::increment(std::uint64_t& value,std::uint64_t amount) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accumulate a candidate diagnostic counter or cancel on overflow. |
| inputs / outputs | U64 reference and amount checked against MAX; success adds,true,otherwise cancels failed/counter_overflow and returns false. |
| invariants | Counters never wrap; cancel can invalidate target/ledger,so callers stop dependent work on false. |
| ownership | Reference points into stable State status,which remains alive after cancellation. |
| failure | noexcept cancellation, no new diagnostic allocation. |
| cost | Constant arithmetic on success; overflow cleanup proportional to retained candidate/backlog. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp) |

## B0010

[Lines 79–83](../../../../../src/runtime/reoptimization.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void State::elapsed(Clock::time_point start,std::uint64_t& value) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge elapsed candidate phase time with regression/overflow reporting. |
| inputs / outputs | start timestamp and status counter read end via time(),reject end&lt;start,cast elapsed nanoseconds and checked-add. |
| invariants | Clocks are explicit candidate diagnostics,independent of optional ordinary observation mode. Failure can cancel candidate; no latency guarantee. |
| ownership | Status counters remain stable through cancel; no new timer owner. |
| failure | noexcept; regression/counter overflow changes phase/stop and releases candidate resources. |
| cost | One clock plus fixed arithmetic normally; cancellation teardown on failure. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp) |

## B0011

[Lines 84–84](../../../../../src/runtime/reoptimization.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void State::old_drain_elapsed(Clock::time_point start) noexcept {elapsed(start,status_.old_drain_ns);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record baseline old-plan drain time separately from candidate payback costs. |
| inputs / outputs | Start timestamp forwards elapsed into status.old_drain_ns. |
| invariants | Old maintenance is not charged again as candidate catch-up cost; this field remains observed diagnostic. |
| ownership | Fixed counter,borrows timestamp. |
| failure | noexcept; inherited clock/counter failure cancellation. |
| cost | Constant forwarding plus one clock read. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp) |

## B0012

[Lines 85–88](../../../../../src/runtime/reoptimization.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime& State::target() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the target only at the verified unpublished barrier. |
| inputs / outputs | Requires verified phase and engaged target_,then returns DeltaRuntime&. |
| invariants | Verified equality/payback does not publish/install runtime or waive source/output/durable guards; caller must prepare publication separately. |
| ownership | Reference borrows State-owned target; cannot outlive State,cancel,take_target or publication transfer. |
| failure | Existing Error reoptimization_not_verified if unavailable; diagnostic construction may allocate. |
| cost | Constant checks/reference access. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp) |

## B0013

[Lines 89–96](../../../../../src/runtime/reoptimization.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void State::charge_artifact(std::uint64_t ns,const resource::MemoryStatistics& memory,const std::array<char,64>& hash) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind measured compiler-artifact preparation exactly once for publication retries. |
| inputs / outputs | Nanoseconds,compiler-account statistics and artifact SHA first set charged state; subsequent calls require exact same triple. |
| invariants | No recharging/fabricated zero or switching immutable compiler input on retry. Compiler memory is separate from original query account. |
| ownership | Copies fixed metrics/hash,does not retain/replay artifact bytes or compiler DTO. |
| failure | Mismatch throws Error and leaves original binding unchanged; first call has only fixed assignments. |
| cost | Constant fixed-array/counter comparisons/copies. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp) |

## B0014

[Lines 97–102](../../../../../src/runtime/reoptimization.cpp#L97); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool State::publication_prepared(Clock::time_point started) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Include publication preparation time and re-evaluate payback before irreversible selection. |
| inputs / outputs | elapsed preparation cost,if active,evaluate policy at current source epoch and cancel rejected if not eligible. |
| invariants | Must run before durable root commitment. A rejected candidate may leave unselected prepared files,not permission to undo selected authority. |
| ownership | Updates fixed costs/decision; cancel releases only candidate resources. |
| failure | noexcept; timing/counter failure cancels; pure policy rejection marks rejected. |
| cost | One clock,policy arithmetic and potential target/ledger teardown. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp) |

## B0015

[Lines 103–105](../../../../../src/runtime/reoptimization.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime State::take_target() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer the verified funded target into the session at the final publication barrier. |
| inputs / outputs | Private caller guarantees engaged target_; move runtime out,reset optional and return. |
| invariants | Used only after all source/equivalence/output/durable preparation has passed. Does not itself decide authority or validate target presence. |
| ownership | Moves sole native target owner without row copy; old owner remains held separately by session until complete switch. |
| failure | noexcept on valid private precondition; no rollback/allocation. |
| cost | Constant runtime handle move/reset. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp) |

## B0016

[Lines 106–114](../../../../../src/runtime/reoptimization.cpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void State::complete_publication(Clock::time_point started,Clock::time_point selected,Clock::time_point cleaned) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Complete diagnostics after an already irreversible successful installation. |
| inputs / outputs | Start/selected/cleaned timestamps mark phase complete,unfreeze,and if counter/order valid report publication/cleanup durations,otherwise timings_complete=false. |
| invariants | Clock diagnostic failure after durable selection cannot cancel/undo installed target. Three supplied external clock reads counted explicitly. |
| ownership | Only fixed status fields; runtime ownership already transferred. |
| failure | noexcept; invalid clock order/read count disables timing completeness rather than reverting authority. |
| cost | Fixed checks/duration arithmetic,no clock syscall in this method. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp) |

## B0017

[Lines 115–118](../../../../../src/runtime/reoptimization.cpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void State::request_barrier() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze new input admission for an active unverified candidate barrier. |
| inputs / outputs | active&&!verified sets admission_frozen and barrier_requested. |
| invariants | Does not discard already admitted input/output/window substeps. Session drains them normally before verify/publication. |
| ownership | Scalar flags only. |
| failure | noexcept; inactive/verified no-op. |
| cost | Constant predicates/writes. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp) |

## B0018

[Lines 119–119](../../../../../src/runtime/reoptimization.cpp#L119); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void State::waiting_output() noexcept {if(active())status_.phase=Phase::waiting_output;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report that normal old-owner output blocks barrier progress. |
| inputs / outputs | Active candidate phase becomes waiting_output. |
| invariants | No output discard/acknowledgment or source advancement; normal consumer/sink obligations remain. |
| ownership | Scalar phase only. |
| failure | noexcept,inactive no-op. |
| cost | Constant write. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp) |

## B0019

[Lines 120–120](../../../../../src/runtime/reoptimization.cpp#L120); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void State::barrier_progress() noexcept {if(active() && frozen() && !verified())status_.phase=Phase::barrier_requested;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resume barrier-requested status while frozen and not yet verified. |
| inputs / outputs | Active,frozen,unverified candidate updates phase barrier_requested. |
| invariants | Status transition does not alter backlog/owner/source or bypass delivery gates. |
| ownership | Scalar phase only. |
| failure | noexcept,no allocation. |
| cost | Constant tests/write. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp) |

## B0020

[Lines 121–124](../../../../../src/runtime/reoptimization.cpp#L121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void State::clear_entries() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release staged/committed replay ledger iteratively without recursive chain teardown. |
| inputs / outputs | Reset staged_,move each head.next out before destroying head,set tail=null and live backlog counters0. |
| invariants | Historic staging/replay/work/peak metrics remain for report; no source rollback or grant refill. |
| ownership | Each Entry and native row uses original account; explicit loop releases owned nodes/payload. |
| failure | noexcept cleanup; no allocation/handler. |
| cost | O(backlog records) releases,bounded call stack,not O(1) cancellation. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp) |

## B0021

[Lines 125–127](../../../../../src/runtime/reoptimization.cpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void State::cancel(Phase phase,Stop stop) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Cancel only the private migration and unfreeze ordinary admission. |
| inputs / outputs | Reset pending target epoch,clear ledger,target_,set phase/stop and admission_frozen=false. |
| invariants | Old writer keeps its own commit/recovery rules; session passes recovery_required phase when durable authority requires it. This method cannot revoke root/WAL commitment. |
| ownership | Releases original-account candidate state and views/leases in safe order. |
| failure | noexcept; pending destructor aborts its private native attempt; no second rollback framework. |
| cost | O(candidate resident state+ledger) teardown,without new allocation. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp) |

## B0022

[Lines 128–131](../../../../../src/runtime/reoptimization.cpp#L128); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void State::rollback_stage() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Abandon a staged old-owner input that did not commit. |
| inputs / outputs | If staged exists,decrement live backlog record/byte totals and reset node; otherwise no-op. |
| invariants | Only pre-commit staged slot removed. Committed ledger,source epoch and historical work/staged count remain. |
| ownership | Frees original-account staged row/Entry; caller old native epoch owns its own rollback. |
| failure | noexcept with private count invariant; no underflow when slot absent. |
| cost | Constant node release/counters,scalar payload deallocation. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0023

[Lines 132–169](../../../../../src/runtime/reoptimization.cpp#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void State::stage(const DeltaRuntime& source,const PhysicalUpdateView& update) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund a candidate replay record before the old owner begins one physical input. |
| inputs / outputs | Active source owner/epoch,next contiguous update verify no duplicate stage/verified state; debit staging descriptor/string visits,preflight real row+Entry requested bytes,admit backlog cap,copy native row/create staged Entry and update counters/peaks. |
| invariants | Physical noops still have sequence entries; window metadata does not. A post-clock activity check returns before descriptor work or allocation if time cancelled. Later failure cancels only migration and leaves cumulative staging work spent. |
| ownership | Original account owns one packed row and linked Entry; input view borrowed only during copy. Staged slot joins committed chain only after old commit marker. |
| failure | Typed staging/sequence/backlog/counter,allocation and other native errors cancel with explicit stop; source rows/progress are not changed. Candidate time records staging separately and adds it to catch_up cost. |
| cost | O(row fields+string bytes) preflight/copy plus2native allocations,constant ledger slots; actual framing is in backlog bytes and simultaneous query peak. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp) |

```text
const auto payload=storage::AccountedRow::allocation_usage_for(update.values).requested_bytes;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit real replay-ledger requests before row/Entry allocation. |
| inputs / outputs | Packed row requested bytes plus MemoryAccount allocation_bytes(sizeof Entry) checked for overflow and live backlog caps. |
| invariants | Includes framing/control,not only payload estimates; simultaneous whole-query account still governs both owners and all scratch. |
| ownership | Native row and Entry created only after limits pass,owned privately in staged slot. |
| failure | Limit/allocation failure cancels candidate while ordinary source writer proceeds under its own rules. |
| cost | O(row metadata/string sizing) preflight plus fixed checked accounting and2allocations. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp), [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp) |

## B0024

[Lines 170–176](../../../../../src/runtime/reoptimization.cpp#L170); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void State::committed(std::uint64_t sequence) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish the staged physical record after successful old-owner commit. |
| inputs / outputs | Active candidate requires staged sequence matching committed input,links unique node to tail/head,moves slot and advances source_epoch. |
| invariants | No allocation after old commit; missing/mismatched stage cancels candidate instead of harming ordinary source progress. |
| ownership | Moves original-account node into committed backlog; raw tail points into owned chain. |
| failure | noexcept; mismatch causes candidate cancellation,never source rollback. |
| cost | Constant pointer/owner moves and scalar writes on success; cancel teardown on mismatch. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp) |

## B0025

[Lines 177–181](../../../../../src/runtime/reoptimization.cpp#L177); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void State::pop() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release one successfully replayed committed ledger head. |
| inputs / outputs | Private nonempty head moves next out,destroys current,updates tail when empty and subtracts live bytes/record. |
| invariants | Native target epoch already committed and output discarded before pop. Historical work/peak counters are retained. |
| ownership | Frees original-account Entry/row,no recursive suffix destruction. |
| failure | noexcept on private nonempty/count invariant. |
| cost | One node/payload release and fixed pointer/counter work. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp) |

## B0026

[Lines 182–206](../../../../../src/runtime/reoptimization.cpp#L182); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void State::advance(std::uint64_t quantum) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance private ordered target catch-up under a finite begin/step quantum. |
| inputs / outputs | Active unverified candidate and nonzero quantum process committed heads: contiguous sequence begins a target epoch/start_drain,subsequent steps prepare/commit/discard output,update completed native/replay counters then pop. |
| invariants | Quantum/catch_up_steps count begin/step calls,not CPU/whole native epoch cost. Pending target epoch persists across calls. Only committed old records replay; source remains unchanged. Failed private work may lack completed-epoch work metrics. |
| ownership | Target/pending/ledger all share original account; no public target output/delivery. Native begin/step use original target grants. |
| failure | Typed step/sequence/counter,allocation/other native failure cancels only migration. Timed catch_up cost persists; output discarded before advancing report target epoch. |
| cost | One native begin/step per quantum unit plus bounded ledger/metric cleanup; native field/bucket/fanout/account costs remain separate. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp) |

## B0027

[Lines 207–250](../../../../../src/runtime/reoptimization.cpp#L207); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void State::verify(const DeltaRuntime& source) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify exact source and output equality at the frozen caught-up boundary before payback eligibility. |
| inputs / outputs | Active unverified,frozen,caught-up State checks actual old owner/sequence,target epoch,compares full physical sources then bounded result cursors via original-account ordered row set,marks verified and evaluates measured-cost/caller forecast policy. |
| invariants | A post-clock activity check precedes every target use. Exact source and SQL/set result comparison, not key/hash/model score alone, authorizes this private verified barrier. Cursor/equivalence/native work domains remain distinct; publication is separate. |
| ownership | Scratch set owns copied source result rows and target probes; native cursors own leases and are scoped. Both owners+scratch overlap on one account. |
| failure | Startup catch records missing cursor metrics; scan catch records spent native cursor work before propagation. Outer typed/allocation/Error/catchall cancel candidate; Error resource_limit maps equivalence_limit. Timing/policy failure can cancel/reject after equality; old owner unchanged. |
| cost | Full source scans plus result enumeration,ordered set insert/find/erase and scalar-byte copies/comparisons; finite equivalence rows/work and two cursor grants. Not constant-time or an update hot path. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [tests/unit/reoptimization_session_test.cpp](../../../../../tests/unit/reoptimization_session_test.cpp) |

```text
catch(...) {static_cast<void>(increment(status_.equivalence_unobserved_startups));throw;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record failed result-cursor construction when no mandatory-work metrics survive. |
| inputs / outputs | Exception creating native cursor increments unobserved_startups then rethrows to outer candidate cancellation. |
| invariants | Does not invent zero native work or convert failure into equality success. Counter overflow may also cancel candidate. |
| ownership | No live cursor exists on failed emplacement; outer scratch/target owners unwind. |
| failure | Preserves original exception unless private diagnostic counter failure has already cancelled; no retry. |
| cost | Failure-only fixed counter/cleanup; no added success-path capture. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp) |

```text
}catch(...) {record();throw;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain observed native cursor work when row copy/comparison/iteration fails. |
| inputs / outputs | Scan failure calls record() before propagating; successful scan also records once after loop. |
| invariants | Metric accounting is distinct from equivalence row/byte work. Counter overflow can supersede failure with explicit counter-overflow cancellation. |
| ownership | Cursor remains in scope while metrics read; its owning lease releases on unwind. |
| failure | Required accounting boundary; no query/source rollback and no catch-removal proposal. |
| cost | One metrics accumulation per scan exit,plus scoped cursor/set cleanup. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp) |

```text
scan(source,true);scan(*target_,false);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare complete actual set results without relying on cardinality/hash/order alone. |
| inputs / outputs | Source rows insert uniquely into funded ordered set; target rows find/erase exact typed values; leftover/missing/duplicate source rows reject. |
| invariants | Both cursors use separate finite native work caps while one equivalence budget counts source/result visits and scalar comparisons. Private target output never delivered. |
| ownership | Original account owns scratch result rows/probes while both native owners remain alive. |
| failure | The entry activity recheck rules out saturated-clock target cancellation before this scan. Later mismatch/work/account/cursor errors cancel only the candidate. |
| cost | O(results log results +typed-byte comparisons/copies) plus actual cursor enumeration/startup costs. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp) |

## B0028

[Lines 251–251](../../../../../src/runtime/reoptimization.cpp#L251); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L251-L251:sha256:a0cca8d108a05d2f29a8e466f1953b899273cc67823b1adaa98bcb0a04a652d2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime::reoptimization::detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime::reoptimization::detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime::reoptimization::detail\` at its lexical source position in src/runtime/reoptimization.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime::reoptimization::detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
