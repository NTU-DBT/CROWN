# `tests/unit/weighted_cursor_limits_test.cpp` — block usage map

[Source](../../../../../tests/unit/weighted_cursor_limits_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `15a5b4a3725815f5c977bd675d80559b48ed7e38a1236c4332bf2c8dc88ba896`. 161 lines partitioned into 17 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 10–14](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L10) | Callable definition: template&lt;class Action&gt; void error(Action action, std::string_view code) | calls action, check, code, std::runtime_error; guard catch (const Error& failure) {check(failure.code()==code,"unexpected weighted error: "+failure.code… · [reviewed contract](#b0002) |
| [B0003 · 15–17](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L15) | Explanatory comments or spacing. | source comment (unverified): // Allocation injection is outside the reference/checking work. Startup must · [reviewed contract](#b0003) |
| [B0004 · 18–51](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L18) | Callable definition: void allocation_cuts(bool indexed, bool startup, bool later) | calls baseline, typed_bag, typed_inputs, results; guard check(allocations&gt;0,"empty cursor allocation sweep");; 1 loop sites; source comment (unverified): // Allocation injection is outside the reference/checking work. Startup must · [reviewed contract](#b0004) |
| [B0005 · 52–52](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L52) | Explanatory comments or spacing. |  |
| [B0006 · 53–70](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L53) | Callable definition: void work_limit(bool indexed) | calls model, typed_bag, typed_inputs, results; guard check(exact.metrics().work==budget,"cursor exact cumulative work differs"); · [reviewed contract](#b0006) |
| [B0007 · 71–74](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L71) | Explanatory comments or spacing. | source comment (unverified): // Many compressed outputs with small maintained inputs make the complete · [reviewed contract](#b0007) |
| [B0008 · 75–94](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L75) | Callable definition: std::uint64_t native_grant(std::optional&lt;std::uint64_t&gt; limit, bool reject) | calls runtime, disconnected_bag, apply, n; guard check(row-&gt;multiplicity.value==1,"disconnected output multiplicity");++rows;; returns cursor.metrics().native_grant_consumed.structural_steps; 3 loop sites; source comment (unverified): // Many compressed outputs with small maintained inputs make the complete · [reviewed contract](#b0008) |
| [B0009 · 95–95](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L95) | Explanatory comments or spacing. |  |
| [B0010 · 96–103](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L96) | Callable definition: std::uint64_t heap_scenario(bool indexed, std::uint64_t limit) | calls model, typed_bag, typed_inputs, results; guard check(retained.size()==48,"heap fixture compressed output size");; returns model.runtime.accounted_memory_statistics().peak_requested_bytes; growth push_back; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 104–111](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L104) | Callable definition: void heap_limit(bool indexed) | calls heap_scenario, check, fault; guard check(heap_scenario(indexed,peak)==peak,"cursor exact requested-byte heap"); · [reviewed contract](#b0011) |
| [B0012 · 112–112](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L112) | Explanatory comments or spacing. |  |
| [B0013 · 113–122](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L113) | Callable definition: void rollback_factors(bool indexed) | calls model, counted_path, set, n; guard check(!pending.active() && model.runtime.sequence()==2,"factor epoch overflow published state"); · [reviewed contract](#b0013) |
| [B0014 · 123–123](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L123) | Explanatory comments or spacing. |  |
| [B0015 · 124–148](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L124) | Callable definition: void release_and_churn(bool indexed) | calls model, typed_bag, typed_inputs, structural_program; guard check(calls==0,"cursor cancel allocated");}; growth emplace; 1 loop sites · [reviewed contract](#b0015) |
| [B0016 · 149–150](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L149) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0016) |
| [B0017 · 151–161](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L151) | Callable definition: int main() | calls allocation_cuts, work_limit, heap_limit, rollback_factors; guard check(native_grant(work,false)==work,"exact native cursor grant differs");; returns 1; 1 loop sites · [reviewed contract](#b0017) |

## B0001

[Lines 1–9](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:0807897b42d6d47736a6a7d3f4d2e6327f5ce9a6abd1b9c255d91567df92ff1b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare weighted_cursor_limits_test.cpp: include "weighted_bag_fixture.hpp", "index_allocation.hpp", "crown/api/error.hpp", &lt;iostream&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/weighted_cursor_limits_test.cpp](../../../../../tests/unit/weighted_cursor_limits_test.cpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 10–14](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void error(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that one weighted-runtime operation throws crown::Error with the requested diagnostic code. |
| inputs / outputs | An Action value and expected code view enter; the action is invoked and a matching code returns normally. |
| invariants | Only crown::Error is caught and compared; no wider error taxonomy is asserted by this helper. |
| ownership | The action is stored by value for the helper call; no runtime/cursor is retained after return. |
| failure | A mismatched code fails through fixture check(); if no Error is thrown the helper throws std::runtime_error; other exception types propagate. |
| cost | Invokes the action once and compares a code only on Error; callable cost is not bounded here. |
| Design | [tests/unit/weighted_cursor_limits_test.cpp § L10-L14](../../../../../tests/unit/weighted_cursor_limits_test.cpp), [tests/unit/weighted_cursor_limits_test.cpp § L53-L70](../../../../../tests/unit/weighted_cursor_limits_test.cpp) |

## B0003

[Lines 15–17](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L15); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L17:sha256:ef085757464100fecd8c82a1a3137642d0a95208d2fb9da7c9ef1e6650862241
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Allocation injection is outside the reference/checking work. Startup must publish no reader on failure; next failure must release every borrowed row. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/weighted_cursor_limits_test.cpp](../../../../../tests/unit/weighted_cursor_limits_test.cpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 18–51](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void allocation_cuts(bool indexed
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep injected allocation failures at weighted cursor startup, first next(), and a later next() for each backend. |
| inputs / outputs | Indexed/startup/later flags select typed_bag setup and the operation at which allocations are counted; each measured cut is replayed in a fresh Model. |
| invariants | The counted operation must have at least one allocation. Every injected cut must trigger std::bad_alloc, leave runtime ready and bag comparable; failed next() leaves cursor failed/inactive and a second next() expects invalid_cursor. A previously returned result remains exportable, and a subsequent set is accepted by the fixture. |
| ownership | Model owns runtime/input state; ResultCursor owns the active reader; the optional prior Result retains its tuple until the iteration ends. |
| failure | Only std::bad_alloc is caught during injected operations; the invalid follow-up cursor code is invalid_cursor. Other exceptions propagate. |
| cost | Measures one operation’s allocation count then repeats setup and one injected cut for every count below it; test cost is proportional to that measured finite sweep, not a bound on production allocation count. |
| Design | [tests/unit/weighted_cursor_limits_test.cpp § L18-L51](../../../../../tests/unit/weighted_cursor_limits_test.cpp) |

## B0006

[Lines 53–70](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void work_limit(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare exact, one-under, zero-startup, and cumulative weighted cursor work limits. |
| inputs / outputs | A baseline cursor created with default CursorOptions supplies total/startup/max-result work; the current default work_limit is 1,000,000. New cursors run with the measured explicit finite limits for the selected backend. |
| invariants | Exact total work succeeds with equal reported work. Total-minus-one drain raises resource_limit, leaves that cursor failed and the runtime ready; zero-budget startup also raises resource_limit without retaining a reader. A startup_work+max_result_work prefix budget yields one row, then a later drain raises resource_limit and the runtime becomes ready. This is budget failure rather than normal exhaustion, and the sequence tests that later next calls do not refill the budget. |
| ownership | Each cursor owns its reader lease for the call; runtime and bag oracle remain owned by Model. |
| failure | The checked diagnostic code for below-budget/startup/next failures is resource_limit; other failures use check(). |
| cost | Drains the measured and exact cursors and a later limited cursor over the finite typed fixture; this tests those budgets only. |
| Design | [tests/unit/weighted_cursor_limits_test.cpp § L53-L70](../../../../../tests/unit/weighted_cursor_limits_test.cpp), [include/crown/runtime/weighted.hpp § L180-L186](../../../../../include/crown/runtime/weighted.hpp), [include/crown/runtime/weighted.hpp § L287-L290](../../../../../include/crown/runtime/weighted.hpp) |

## B0007

[Lines 71–74](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L71); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L71-L74:sha256:98f62a1db240d38817bb10d3f460de57f46a3a6c392027884371efd08ee5362f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Many compressed outputs with small maintained inputs make the complete cursor grant larger than plan admission/update growth, so exact/one-under tests isolate one retained cursor grant rather than an earlier setup limit. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/weighted_cursor_limits_test.cpp](../../../../../tests/unit/weighted_cursor_limits_test.cpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 75–94](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t native_grant(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure and optionally reject a weighted cursor while sharing one native indexed-work grant across its outputs. |
| inputs / outputs | Optional uint64 limit and reject flag enter; the helper builds a disconnected indexed bag, inserts 64 values at each of two nodes, drains results, and returns consumed structural steps. |
| invariants | Every emitted multiplicity is 1 and structural grant consumption increases between rows; the caught IndexFailure must have code storage_work_limit when rejection is expected. Runtime is ready afterward, root weight remains 4096, and success yields 4096 rows. |
| ownership | WeightedRuntime owns maintained state; cursor retains its lease during enumeration; each returned row is consumed locally. |
| failure | The only caught native failure category is storage::IndexFailure with code storage_work_limit; check() records mismatched threshold/state. |
| cost | Applies 128 input events and visits up to the fixture’s 4096 compressed results; the exact/one-under thresholds are checked by caller, not a general grant formula. |
| Design | [tests/unit/weighted_cursor_limits_test.cpp § L75-L94](../../../../../tests/unit/weighted_cursor_limits_test.cpp) |

## B0010

[Lines 96–103](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t heap_scenario(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run a finite typed weighted cursor under one requested-byte memory limit while retaining all outputs. |
| inputs / outputs | Backend flag and byte limit enter; typed_inputs(model,24) supplies 24 r(name,y,day) rows plus the two s(y,flag) rows. The cursor retains 48 compressed Results in a standard vector&lt;w::Result&gt; and returns runtime-account peak_requested_bytes. |
| invariants | The 48 count is compressed result objects, not expanded multiplicity. The returned figure is the runtime account peak of requested bytes; it is not total C++ heap, malloc or RSS measurement. |
| ownership | Model owns runtime/account state; the vector retains each returned Result until the function exits. |
| failure | No exception is caught locally; account failures propagate to the caller. |
| cost | Retains the finite 48 compressed output objects and reads the runtime account peak once. The standard vector and reference fixture workspace are not turned into a total-heap bound by this observation. |
| Design | [tests/unit/weighted_cursor_limits_test.cpp § L96-L103](../../../../../tests/unit/weighted_cursor_limits_test.cpp), [tests/support/weighted_bag_fixture.hpp § L45-L49](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0011

[Lines 104–111](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void heap_limit(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact and one-byte-under requested-memory admission for a weighted cursor scenario. |
| inputs / outputs | Backend flag enters; a generous run supplies peak requested bytes, then scenarios rerun at peak and peak−1. |
| invariants | The exact-limit run must report the same peak; peak−1 must reject with MemoryFailure whose fault is MemoryFault::limit. |
| ownership | Each scenario creates and destroys its own Model; no memory account is shared between runs. |
| failure | Only resource::MemoryFailure with fault limit is caught; no Error code is asserted. |
| cost | Runs the same finite heap scenario three times and compares requested-byte peaks; it does not estimate OS process memory. |
| Design | [tests/unit/weighted_cursor_limits_test.cpp § L104-L111](../../../../../tests/unit/weighted_cursor_limits_test.cpp) |

## B0013

[Lines 113–122](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L113); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void rollback_factors(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that a second-stage multiplicity overflow aborts a weighted factor epoch without publishing its staged prefix. |
| inputs / outputs | A counted_path BagModel with multiplicity limit 100 receives two initial rows; epoch 3 stages the first row’s new count then attempts the second row’s overflowing count. |
| invariants | The second stage expects annotation_overflow; afterward the epoch is inactive, committed sequence remains 2, and compare_bag checks runtime against fixture inputs. |
| ownership | BagModel owns weighted runtime and input oracle; pending epoch owns staged work until failure. |
| failure | The expected diagnostic is Error code annotation_overflow; no other failure category is asserted. |
| cost | Two initial sets and two stages precede one bag comparison; this is a finite rollback fixture. |
| Design | [tests/unit/weighted_cursor_limits_test.cpp § L113-L122](../../../../../tests/unit/weighted_cursor_limits_test.cpp) |

## B0015

[Lines 124–148](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void release_and_churn(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check cancel allocation behavior, cursor churn accounting, facade-independent cursor/result ownership, and cross-owner move assignment. |
| inputs / outputs | A retained account and optional cursor/result outlive a Model scope; 64 transient cursors are opened, advanced, cancelled under allocation cut 0, and checked against baseline bytes. |
| invariants | Cancel must make zero injected allocation calls and each transient close returns current bytes to baseline. A cursor can produce a row after the facade dies; cancelling/resetting cursor does not invalidate the returned row. Releasing row returns account to control bytes. Move assignment from a second runtime makes the first runtime ready, second busy, and cursor owner equal to second; cancel restores second readiness. |
| ownership | Account copy retains the controller; cursor and Result own/retain their leases/payloads across Model destruction until reset. |
| failure | This function asserts no product error code; failed conditions throw through check(). |
| cost | Runs 64 one-row transient cursors plus two cross-owner cursors, checking counters at each iteration; only these finite churn counts are covered. |
| Design | [tests/unit/weighted_cursor_limits_test.cpp § L124-L148](../../../../../tests/unit/weighted_cursor_limits_test.cpp) |

## B0016

[Lines 149–150](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L149); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L149-L150:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in weighted_cursor_limits_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/weighted_cursor_limits_test.cpp](../../../../../tests/unit/weighted_cursor_limits_test.cpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 151–161](../../../../../tests/unit/weighted_cursor_limits_test.cpp#L151); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run weighted cursor allocation/work/heap/rollback/lifetime cases for ordered and indexed backends, then exact and one-under native grant checks. |
| inputs / outputs | No inputs enter; success returns normally and a caught std::exception prints and exits 1. |
| invariants | For each backend, allocation_cuts runs three modes: startup, first next and later next. work_limit, heap_limit, rollback_factors and release_and_churn each run once per backend. After that loop, the indexed native grant runs once to measure, once at the measured threshold, and once at one less. |
| ownership | Fixture/runtime objects are scoped inside the invoked helpers. |
| failure | The harness catches std::exception; it does not assert a general error taxonomy. |
| cost | Runs fourteen backend-level helper calls (seven per backend) plus three native_grant calls; nested setup/drain/sweep work remains described by those helpers. This is finite source coverage only. |
| Design | [tests/unit/weighted_cursor_limits_test.cpp § L151-L161](../../../../../tests/unit/weighted_cursor_limits_test.cpp) |
