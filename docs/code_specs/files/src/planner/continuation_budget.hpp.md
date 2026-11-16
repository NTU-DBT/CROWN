# `src/planner/continuation_budget.hpp` — block usage map

[Source](../../../../../src/planner/continuation_budget.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Search the finite canonical tree space and retain resumable evidence for exact minimum-height claims.

Snapshot SHA-256: `9e571b8ee9f9c38993faacf4c9838fac97fcf992718e7f110f76437b7beae410`. 74 lines partitioned into 14 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [search](../../../subsystem_contracts.md#search). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../src/planner/continuation_budget.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 9–11](../../../../../src/planner/continuation_budget.hpp#L9) | Callable definition: inline bool valid_ceiling(const PhaseCeiling& limit) noexcept | calls count; returns !limit.active_time \|\| limit.active_time-&gt;count() &gt;= 0 · [reviewed contract](#b0002) |
| [B0003 · 12–17](../../../../../src/planner/continuation_budget.hpp#L12) | Callable definition: template &lt;class T&gt; bool monotone_ceiling(const std::optional&lt;T&gt;& old_value, const std::optional&lt;T&gt;& new_value) noexcept | calls ; returns !new_value; !new_value \|\| *new_value &gt;= *old_value · [reviewed contract](#b0003) |
| [B0004 · 18–22](../../../../../src/planner/continuation_budget.hpp#L18) | Callable definition: inline bool monotone_phase(const PhaseCeiling& old_value, const PhaseCeiling& new_value) noexcept | calls monotone_ceiling; returns monotone_ceiling(old_value.work, new_value.work) && · [reviewed contract](#b0004) |
| [B0005 · 23–26](../../../../../src/planner/continuation_budget.hpp#L23) | Callable definition: inline void saturating_add(std::uint64_t& target, std::uint64_t amount) noexcept | calls max · [reviewed contract](#b0005) |
| [B0006 · 27–32](../../../../../src/planner/continuation_budget.hpp#L27) | declares types or opens a type body. | source comment (unverified): // Producer/replay ceilings count attempted transitions and active nanoseconds · [reviewed contract](#b0006) |
| [B0007 · 33–33](../../../../../src/planner/continuation_budget.hpp#L33) | Callable definition: explicit ResourceLedger(PhaseCeiling value) noexcept : limit(value) | calls limit · [reviewed contract](#b0007) |
| [B0008 · 34–41](../../../../../src/planner/continuation_budget.hpp#L34) | Callable definition: StopReason check() const noexcept | calls count, max; guard StopReason check() const noexcept {; returns StopReason::total_work; StopReason::total_time · [reviewed contract](#b0008) |
| [B0009 · 42–45](../../../../../src/planner/continuation_budget.hpp#L42) | Callable definition: void active(std::chrono::steady_clock::duration elapsed) noexcept | calls count, saturating_add · [reviewed contract](#b0009) |
| [B0010 · 46–49](../../../../../src/planner/continuation_budget.hpp#L46) | Callable definition: void depth(std::size_t current) noexcept | calls std::max · [reviewed contract](#b0010) |
| [B0011 · 50–54](../../../../../src/planner/continuation_budget.hpp#L50) | Callable definition: bool below_consumed(const PhaseCeiling& value) const noexcept | calls count; returns (value.work && *value.work &lt; counters.attempted) \|\| · [reviewed contract](#b0011) |
| [B0012 · 55–58](../../../../../src/planner/continuation_budget.hpp#L55) | Closes surrounding scope/type. | source comment (unverified): // Clock samples cover active advance execution only. Admission, caller pauses, · [reviewed contract](#b0012) |
| [B0013 · 59–73](../../../../../src/planner/continuation_budget.hpp#L59) | Type/record definition: class ActiveMeter | source comment (unverified): // Clock samples cover active advance execution only. Admission, caller pauses, · [reviewed contract](#b0013) |
| [B0014 · 74–74](../../../../../src/planner/continuation_budget.hpp#L74) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::continuation_detail · [reviewed contract](#b0014) |

## B0001

[Lines 1–8](../../../../../src/planner/continuation_budget.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:aa0211e1e2bf1eaa6c8c78b42d2149e4cb5527b42ad789a68dcd1ce5639c35c5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use #pragma once to suppress repeated header processing within a translation unit. Make #include "crown/planner/search.hpp", #include &lt;algorithm&gt;, #include &lt;limits&gt; available to src/planner/continuation_budget.hpp; open crown::planner::continuation_detail. |
| inputs / outputs | Preprocessor directives resolve compile-time declarations. This block has no runtime call inputs or result. |
| invariants | Includes, namespace openings, aliases, and forward declarations determine C++ name visibility and type availability; they do not validate planner data or grant proof authority. |
| ownership | No runtime object is owned by the include or scope directives. Any state belongs to the types and functions declared after them. |
| failure | A missing header, incompatible declaration, or ill-formed type use fails during compilation; runtime failures remain in the called code. |
| cost | Adds preprocessing, parsing, and any later template-instantiation work in this translation unit. It adds no runtime timer, counter, branch, or allocation. |
| Design | [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0002

[Lines 9–11](../../../../../src/planner/continuation_budget.hpp#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline bool valid_ceiling(const PhaseCeiling& limit) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check optional active time is nonnegative before conversion to nanoseconds. |
| inputs / outputs | True if active_time absent or its count is nonnegative. |
| invariants | Work is unsigned; this does not compare ceiling to consumed counters. |
| ownership | Reads input for the call. |
| failure | No exception; stale nonnegative limits pass. |
| cost | Constant scalar check. |
| Design | [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp) |

## B0003

[Lines 12–17](../../../../../src/planner/continuation_budget.hpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool monotone_ceiling(const std::optional<T>& old_value,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decide if one scalar ceiling extends without reducing allowance. |
| inputs / outputs | Unbounded old accepts only unbounded new; finite old accepts greater/equal finite or unbounded. |
| invariants | nullopt denotes infinity; time sign validation is separate. |
| ownership | Reads both values only. |
| failure | No exception; caller validates domains. |
| cost | Constant comparison. |
| Design | [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp) |

## B0004

[Lines 18–22](../../../../../src/planner/continuation_budget.hpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline bool monotone_phase(const PhaseCeiling& old_value,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require work and active-time ceilings to extend together for one phase. |
| inputs / outputs | Conjoins monotone_ceiling for work and active_time. |
| invariants | Extending one field does not permit reducing the other; finite-to-unbounded is allowed. |
| ownership | Reads phase values only. |
| failure | No exception; caller separately rejects negative time. |
| cost | Two scalar comparisons. |
| Design | [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp) |

## B0005

[Lines 23–26](../../../../../src/planner/continuation_budget.hpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void saturating_add(std::uint64_t& target, std::uint64_t amount) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accumulate diagnostic counters without unsigned wraparound. |
| inputs / outputs | Adds amount or stores uint64 maximum if it would overflow. |
| invariants | Saturation is monotone but not separately reported. |
| ownership | Mutates caller-owned counter. |
| failure | No exception or diagnostic on saturation. |
| cost | Constant integer arithmetic. |
| Design | [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp) |

## B0006

[Lines 27–32](../../../../../src/planner/continuation_budget.hpp#L27); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L32:sha256:e6723d2a52b4a1d8d60c263d35fb2f3127c44aa9a8fbae9b80c1c075dd48a68c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain limit, counters in ResourceLedger across its lifetime. Attached note: Producer/replay ceilings count attempted transitions and active nanoseconds separately. They do not account allocator bytes or all work within a transition. |
| inputs / outputs | These are stored fields for ResourceLedger, not callable parameters or results; constructors and later methods set or consume them. |
| invariants | The fields preserve the named machine or owner state between calls; counters, cursors, and stored claims remain data until adjacent methods update or validate them. |
| ownership | remaining enum, scalar, and value members are stored by value. |
| failure | The declarations add no exception path by themselves. Constructing owner/container members or growing them later can fail through the surrounding object-creation or update path. |
| cost | Adds fixed per-instance storage for the listed values and owner/container handles; no planner traversal occurs at declaration time. |
| Design | [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0007

[Lines 33–33](../../../../../src/planner/continuation_budget.hpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit ResourceLedger(PhaseCeiling value) noexcept : limit(value) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize a phase ledger with copied ceiling and default counters. |
| inputs / outputs | Copies PhaseCeiling; WorkCounters uses declared defaults. |
| invariants | Producer/replay ledgers are separate. Tracks attempted work and active time, not allocator bytes. |
| ownership | Owns limit/counters; no clock/facade borrow. |
| failure | Noexcept constructor does not validate active_time; callers run valid_ceiling. |
| cost | Fixed-size initialization. |
| Design | [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp) |

## B0008

[Lines 34–41](../../../../../src/planner/continuation_budget.hpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StopReason check() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return first reached phase ceiling or counter-overflow stop. |
| inputs / outputs | Checks attempted/work, active_nanoseconds/time, then attempted uint64 overflow. |
| invariants | Explicit reached limit takes precedence over overflow; stop applies before next transition. |
| ownership | Reads ledger only. |
| failure | No exception; expects valid nonnegative time. |
| cost | Constant scalar checks. |
| Design | [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp) |

## B0009

[Lines 42–45](../../../../../src/planner/continuation_budget.hpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void active(std::chrono::steady_clock::duration elapsed) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accumulate a positive interval as saturated active nanoseconds. |
| inputs / outputs | Converts to ns, ignores nonpositive values and saturates additions. |
| invariants | Caller defines scope; facades meter nonzero advance only, excluding caller pauses/admission/serialization/cancel/destruction. |
| ownership | Mutates counters only. |
| failure | No exception; saturation not reported. |
| cost | Constant conversion/update. |
| Design | [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp) |

## B0010

[Lines 46–49](../../../../../src/planner/continuation_budget.hpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void depth(std::size_t current) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record current logical frame depth and the peak. |
| inputs / outputs | Assigns current_depth and maxes peak_depth. |
| invariants | Peak is monotone; current can return zero. These counters describe logical frames, not heap bytes. |
| ownership | Mutates counters only. |
| failure | No exception. |
| cost | Constant assignments/comparison. |
| Design | [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp) |

## B0011

[Lines 50–54](../../../../../src/planner/continuation_budget.hpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool below_consumed(const PhaseCeiling& value) const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detect a finite proposed ceiling below consumed work or time. |
| inputs / outputs | True if finite work &lt; attempted or finite active time ns &lt; active_nanoseconds. |
| invariants | Equality is allowed; unbounded does not fall below consumption. Validation/monotonicity checks are separate. |
| ownership | Reads ledger/proposal. |
| failure | No exception; caller rejects negative duration earlier. |
| cost | Constant scalar checks. |
| Design | [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp) |

## B0012

[Lines 55–58](../../../../../src/planner/continuation_budget.hpp#L55); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L55-L58:sha256:ad18e5e9ebf7e894311fd778076f331b1467bd5506bd089dc7c9f929a020ab8d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close the current class or struct and its enclosing lexical scope. Its attached note introduces nearby behavior: Clock samples cover active advance execution only. Admission, caller pauses, serialization and cancellation/destruction are separate explicit costs. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0013

[Lines 59–73](../../../../../src/planner/continuation_budget.hpp#L59); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class ActiveMeter {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure caller-defined time into a borrowed phase ledger and support explicit phase switch. |
| inputs / outputs | Captures steady_clock; sample accumulates since last sample; switch samples old ledger then redirects; destructor samples. |
| invariants | Only a scope inside nonzero advance is active time. Ledger must outlive meter; outside phases remain excluded. |
| ownership | Borrows raw ResourceLedger pointer; owns no ledger/clock service. |
| failure | Noexcept recorder; it does not enforce ceiling. |
| cost | Each sample reads clock and updates counters. |
| Design | [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp) |

## B0014

[Lines 74–74](../../../../../src/planner/continuation_budget.hpp#L74); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L74-L74:sha256:1123fc5908e02d7bbfbdec2c7b0d816c8016869dd57b2906f553a96fa4a43a59
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace crown::planner::continuation_detail. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |
