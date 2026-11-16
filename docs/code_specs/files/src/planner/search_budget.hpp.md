# `src/planner/search_budget.hpp` — block usage map

[Source](../../../../../src/planner/search_budget.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Search the finite canonical tree space and retain resumable evidence for exact minimum-height claims.

Snapshot SHA-256: `5927bfd4f0427449f421e158fb08f649d37538b947fe4888106410e19a2c279c`. 49 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [search](../../../subsystem_contracts.md#search). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../src/planner/search_budget.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 10–14](../../../../../src/planner/search_budget.hpp#L10) | Type/record definition: struct SearchStopped : std::exception | returns reason.c_str() · [reviewed contract](#b0002) |
| [B0003 · 15–18](../../../../../src/planner/search_budget.hpp#L15) | declares types or opens a type body. | source comment (unverified): // Legacy checkpoint budget for the literal reference oracle. Its work counter · [reviewed contract](#b0003) |
| [B0004 · 19–22](../../../../../src/planner/search_budget.hpp#L19) | Callable definition: public: explicit WorkBudget(const SearchLimits& limits) : limits_(limits), start_(std::chrono::steady_clock::now()) | calls limits_, start_, std::chrono::steady_clock::now, count · [reviewed contract](#b0004) |
| [B0005 · 23–28](../../../../../src/planner/search_budget.hpp#L23) | Callable definition: void charge() | calls SearchStopped, std::chrono::steady_clock::now, max · [reviewed contract](#b0005) |
| [B0006 · 29–41](../../../../../src/planner/search_budget.hpp#L29) | Type/record definition: class Frame |  · [reviewed contract](#b0006) |
| [B0007 · 42–42](../../../../../src/planner/search_budget.hpp#L42) | Callable definition: \[\[nodiscard\]\] Frame frame() | calls Frame; returns Frame(*this) · [reviewed contract](#b0007) |
| [B0008 · 43–49](../../../../../src/planner/search_budget.hpp#L43) | declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::planner::detail · [reviewed contract](#b0008) |

## B0001

[Lines 1–9](../../../../../src/planner/search_budget.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:15e7710de274e3caa4e9df89e10c022c052b7500a773f820dfe38c4359df1673
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use #pragma once to suppress repeated header processing within a translation unit. Make #include "crown/api/error.hpp", #include "crown/planner/oracle.hpp", #include &lt;exception&gt;, #include &lt;limits&gt;, #include &lt;utility&gt; available to src/planner/search_budget.hpp; open crown::planner::detail. |
| inputs / outputs | Preprocessor directives resolve compile-time declarations. This block has no runtime call inputs or result. |
| invariants | Includes, namespace openings, aliases, and forward declarations determine C++ name visibility and type availability; they do not validate planner data or grant proof authority. |
| ownership | No runtime object is owned by the include or scope directives. Any state belongs to the types and functions declared after them. |
| failure | A missing header, incompatible declaration, or ill-formed type use fails during compilation; runtime failures remain in the called code. |
| cost | Adds preprocessing, parsing, and any later template-instantiation work in this translation unit. It adds no runtime timer, counter, branch, or allocation. |
| Design | [src/planner/search_budget.hpp](../../../../../src/planner/search_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0002

[Lines 10–14](../../../../../src/planner/search_budget.hpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SearchStopped : std::exception {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry an internal stop reason for literal exhaustive reference search. |
| inputs / outputs | Owns a reason string exposed by what(). |
| invariants | Exception means incomplete search; oracle catch clears any tree/minimum and reports resource_limit. |
| ownership | Owns bytes; what() borrows them through exception lifetime. |
| failure | Message allocation may throw; conversion is the oracle catch site's job. |
| cost | Construction/unwind includes message and exception cost. |
| Design | [src/planner/search_budget.hpp](../../../../../src/planner/search_budget.hpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp) |

## B0003

[Lines 15–18](../../../../../src/planner/search_budget.hpp#L15); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L18:sha256:c6e8fec02362ee7c49f27254612ee84b0bb02a40472a7b8ff2e2587a23f39daa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Begin the definition of WorkBudget in src/planner/search_budget.hpp; retained fields and operations are declared in the following spans. Attached note: Legacy checkpoint budget for the literal reference oracle. Its work counter charges selected checkpoints and its time limit is sampled there; neither ceiling bounds complete CPU time or allocator bytes. |
| inputs / outputs | This type opener has no callable inputs or outputs; it establishes the C++ type whose later members define state and operations. |
| invariants | The declaration establishes type identity and scope only; proof authority or runtime behavior comes from initialized state and methods. |
| ownership | The opener itself owns no runtime storage. Object layout and member lifetimes come from the following field declarations. |
| failure | Ill-formed or incomplete type definitions fail compilation; construction failures arise only when the completed type is instantiated. |
| cost | Compile-time parsing only at this span; runtime object size and construction cost are determined by its completed members. |
| Design | [src/planner/search_budget.hpp](../../../../../src/planner/search_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0004

[Lines 19–22](../../../../../src/planner/search_budget.hpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit WorkBudget(const SearchLimits& limits) : limits_(limits), start_(std::chrono::steady_clock::now()) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize selected-checkpoint limits for literal normal-form enumeration. |
| inputs / outputs | Copies SearchLimits and captures a steady-clock start; negative time_limit throws invalid_search_limits. |
| invariants | Current direct use is tests/reference/tree_oracle.cpp, not production continuation. Work counts explicit charges; time sampled there. Neither caps all CPU or bytes. |
| ownership | Owns copied limits/statistics/start, not caller object. |
| failure | Negative time throws crown::Error; surrounding allocation errors are untranslated. |
| cost | Constant-size init plus one clock sample. |
| Design | [src/planner/search_budget.hpp](../../../../../src/planner/search_budget.hpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp) |

## B0005

[Lines 23–28](../../../../../src/planner/search_budget.hpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void charge() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Account for an explicit reference-search checkpoint when limits permit. |
| inputs / outputs | Checks work limit, elapsed milliseconds, uint64 exhaustion in order, then increments statistics.work. |
| invariants | Time is cooperative and may be exceeded between charges. Frame charges before depth check, so depth-rejected entry can consume work. |
| ownership | Mutates scalar work statistic. |
| failure | Throws SearchStopped for limit/counter conditions; catches nothing else. |
| cost | Scalar checks and clock read when time limit is set. |
| Design | [src/planner/search_budget.hpp](../../../../../src/planner/search_budget.hpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp) |

## B0006

[Lines 29–41](../../../../../src/planner/search_budget.hpp#L29); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Frame {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Track one recursive call and enforce the recursion ceiling with RAII. |
| inputs / outputs | Constructor charges, checks depth, then increments; destructor decrements only after successful construction. |
| invariants | Copying is deleted for one acquisition/one decrement. A rejected depth entry may still charge work. |
| ownership | Borrows WorkBudget; budget must outlive Frame. |
| failure | Constructor may throw SearchStopped; destructor restores acquired depth. |
| cost | O(1), no owned dynamic data. |
| Design | [src/planner/search_budget.hpp](../../../../../src/planner/search_budget.hpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp) |

## B0007

[Lines 42–42](../../../../../src/planner/search_budget.hpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Frame frame() { return Frame(*this); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a scoped recursion-depth guard for the current budget. |
| inputs / outputs | Returns a noncopyable Frame to span one recursive call. |
| invariants | Budget must outlive guard; failed acquisition returns no Frame. |
| ownership | Frame borrows WorkBudget. |
| failure | Propagates SearchStopped from charge/depth checks. |
| cost | Constant factory; Frame performs checks. |
| Design | [src/planner/search_budget.hpp](../../../../../src/planner/search_budget.hpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp) |

## B0008

[Lines 43–49](../../../../../src/planner/search_budget.hpp#L43); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L43-L49:sha256:3c66a661e0780010d9e4296bc6d97f45236ec8d174e6f6f4d90f9ea3723bce66
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain SearchStatistics statistics, SearchLimits limits_, the steady-clock start time, and recursion depth in WorkBudget; close the class and detail namespace. |
| inputs / outputs | These are WorkBudget value fields, not call parameters or results. charge() and Frame read or update them in later declarations. |
| invariants | The fields preserve the named machine or owner state between calls; counters, cursors, and stored claims remain data until adjacent methods update or validate them. |
| ownership | SearchLimits, SearchStatistics, time_point, and depth are stored by value; no shared or unique owner is introduced by these fields. |
| failure | The fields do not throw during declaration. WorkBudget construction validates negative time limits; charge/frame raise SearchStopped at their checkpoints. |
| cost | Fixed per-instance value storage. Clock reads and checkpoint comparisons occur in constructor/charge calls, not when these fields are declared. |
| Design | [src/planner/search_budget.hpp](../../../../../src/planner/search_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |
