# `tests/unit/weighted_bag_test.cpp` — block usage map

[Source](../../../../../tests/unit/weighted_bag_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `aa4f1891f205e1069a8b311b6e0e70934b70b531a8f8de8eee54d7ed8900482d`. 157 lines partitioned into 18 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../tests/unit/weighted_bag_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 10–14](../../../../../tests/unit/weighted_bag_test.cpp#L10) | Callable definition: template&lt;class Action&gt; void error(Action action, std::string_view code) | calls action, check, code, std::runtime_error; guard catch (const Error& failure) {check(failure.code()==code,"unexpected weighted error: "+failure.code… · [reviewed contract](#b0002) |
| [B0003 · 15–15](../../../../../tests/unit/weighted_bag_test.cpp#L15) | Explanatory comments or spacing. |  |
| [B0004 · 16–35](../../../../../tests/unit/weighted_bag_test.cpp#L16) | Callable definition: void counted_path_case(bool indexed, bool hidden, bool repeated) | calls model, counted_path, set, n; guard check(model.runtime.root_weight().value==expected,"mandatory counted path hand result"); · [reviewed contract](#b0004) |
| [B0005 · 36–36](../../../../../tests/unit/weighted_bag_test.cpp#L36) | Explanatory comments or spacing. |  |
| [B0006 · 37–49](../../../../../tests/unit/weighted_bag_test.cpp#L37) | Callable definition: void generalized_case(bool indexed) | calls model, generalized, set, n; guard check(snapshot.nodes\[0\].factors\[0\].value.value==1,"generalized connector must be a unit factor"); · [reviewed contract](#b0006) |
| [B0007 · 50–50](../../../../../tests/unit/weighted_bag_test.cpp#L50) | Explanatory comments or spacing. |  |
| [B0008 · 51–65](../../../../../tests/unit/weighted_bag_test.cpp#L51) | Callable definition: void random_cases(bool indexed) | calls model, counted_path, random, n; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 66–66](../../../../../tests/unit/weighted_bag_test.cpp#L66) | Explanatory comments or spacing. |  |
| [B0010 · 67–87](../../../../../tests/unit/weighted_bag_test.cpp#L67) | Callable definition: void duplicate_bags_and_self_join(bool indexed) | calls model, planner::lower_tree, options, n; guard check(drain(cursor)==Counts{{Row{n(1)},9},{Row{n(2)},4}},"duplicate native bag occurrences were ded…; 3 loop sites; source comment (unverified): // Fold raw duplicates into native logical weights; no physical bag router or · [reviewed contract](#b0010) |
| [B0011 · 88–88](../../../../../tests/unit/weighted_bag_test.cpp#L88) | Explanatory comments or spacing. |  |
| [B0012 · 89–108](../../../../../tests/unit/weighted_bag_test.cpp#L89) | Callable definition: void lifetime(bool indexed) | calls model, unary, set, n; guard check(!model.runtime.ready(),"weighted cursor did not lease writer"); · [reviewed contract](#b0012) |
| [B0013 · 109–109](../../../../../tests/unit/weighted_bag_test.cpp#L109) | Explanatory comments or spacing. |  |
| [B0014 · 110–121](../../../../../tests/unit/weighted_bag_test.cpp#L110) | Callable definition: void constants_and_large(bool indexed) | calls model, unary, set, n; 2 loop sites · [reviewed contract](#b0014) |
| [B0015 · 122–122](../../../../../tests/unit/weighted_bag_test.cpp#L122) | Explanatory comments or spacing. |  |
| [B0016 · 123–144](../../../../../tests/unit/weighted_bag_test.cpp#L123) | Callable definition: void typed_and_deep(bool indexed) | calls typed, typed_bag, typed_inputs, compare_bag; guard check(actual==(hidden?Counts{{Row{n(1)},26},{Row{n(2)},39}}:Counts{{Row{n(7)},26}}),"deep visible/h…; 2 loop sites · [reviewed contract](#b0016) |
| [B0017 · 145–146](../../../../../tests/unit/weighted_bag_test.cpp#L145) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0017) |
| [B0018 · 147–157](../../../../../tests/unit/weighted_bag_test.cpp#L147) | Callable definition: int main() | calls counted_path_case, generalized_case, random_cases, duplicate_bags_and_self_join; returns 1; 1 loop sites · [reviewed contract](#b0018) |

## B0001

[Lines 1–9](../../../../../tests/unit/weighted_bag_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:0a6188f410bb7d71aa673bb0ce97bfb8d65b50c001b9d3472d47da96ade30429
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare weighted_bag_test.cpp: include "weighted_bag_fixture.hpp", "crown/api/error.hpp", &lt;iostream&gt;, &lt;random&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/weighted_bag_test.cpp](../../../../../tests/unit/weighted_bag_test.cpp), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 10–14](../../../../../tests/unit/weighted_bag_test.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void error(Action action, std::string_view code)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert an expected weighted runtime Error code. |
| inputs / outputs | Accepts Action by value and expected code; invokes action() and returns on matching crown::Error. |
| invariants | The named action parameter is an lvalue; only crown::Error is considered an expected rejection. |
| ownership | Callable is owned by the helper for the invocation; code is borrowed. |
| failure | Wrong code fails via check; no Error throws runtime_error; unrelated exceptions propagate. |
| cost | Invokes the action once; in the Error path it constructs the dynamic diagnostic string before checking the expected code, even when the code matches. No-error and wrong-code paths construct runtime_error diagnostics. |
| Design | [tests/unit/weighted_bag_test.cpp](../../../../../tests/unit/weighted_bag_test.cpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [tests/integration/weighted_bag.py](../../../../../tests/integration/weighted_bag.py), [Refactor.md §10.2](../../../../../Refactor.md), [tests/unit/weighted_bag_test.cpp](../../../../../tests/unit/weighted_bag_test.cpp) |

## B0004

[Lines 16–35](../../../../../tests/unit/weighted_bag_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void counted_path_case(bool indexed, bool hidden, bool repeated)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check counted path factors with optional hidden tail and repeated output alias. |
| inputs / outputs | Seeds small weighted rows, checks root totals/factor replacement, then removes and re-adds support. |
| invariants | Child witness weight is not multiplied into the parent factor twice; numeric replacement can preserve membership. |
| ownership | Model, snapshots, and epoch values are local. |
| failure | Assertions fail through check; model/runtime Errors propagate. |
| cost | Runs 10 updates without the hidden tail and 12 with it. Each BagModel::set rechecks a runtime snapshot against full-subtree joins, then checks factors and projected results with exhaustive component joins and a cursor drain; these are fixture-oracle costs. |
| Design | [tests/unit/weighted_bag_test.cpp](../../../../../tests/unit/weighted_bag_test.cpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [tests/integration/weighted_bag.py](../../../../../tests/integration/weighted_bag.py), [Refactor.md §10.2](../../../../../Refactor.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0006

[Lines 37–49](../../../../../tests/unit/weighted_bag_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void generalized_case(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check projected sums through nested generalized connectors. |
| inputs / outputs | Seeds one parent and two native children, checks factors/root total, then changes and removes child rows. |
| invariants | Generalized connectors contribute unit local factor; hidden scope values are summed into visible keys. |
| ownership | Model/snapshot values are local. |
| failure | Mismatch throws runtime_error via check. |
| cost | Nine updates on the five-node fixture. After each update, BagModel rechecks snapshot/full-subtree state and exhaustively recomputes component factors and projected cursor results. |
| Design | [tests/unit/weighted_bag_test.cpp](../../../../../tests/unit/weighted_bag_test.cpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [tests/integration/weighted_bag.py](../../../../../tests/integration/weighted_bag.py), [Refactor.md §10.2](../../../../../Refactor.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0008

[Lines 51–65](../../../../../tests/unit/weighted_bag_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void random_cases(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise deterministic random updates against the exhaustive bag model. |
| inputs / outputs | Uses mt19937_64 seed 0x7303 for 400 updates, then checks a separate path fixture with six fixed inserts. |
| invariants | Generated values and weights are bounded by small modulo ranges; this is a finite regression campaign. |
| ownership | RNG and both BagModels are local. |
| failure | Any differential mismatch throws runtime_error. |
| cost | Runs 400 generated updates plus six fixed path inserts. Every BagModel update also recomputes the full reference state and projected bag/factor oracle, so this is a finite differential campaign, not an update-cost measurement. |
| Design | [tests/unit/weighted_bag_test.cpp](../../../../../tests/unit/weighted_bag_test.cpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [tests/integration/weighted_bag.py](../../../../../tests/integration/weighted_bag.py), [Refactor.md §10.2](../../../../../Refactor.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0010

[Lines 67–87](../../../../../tests/unit/weighted_bag_test.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void duplicate_bags_and_self_join(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check duplicate source bags and repeated self-join occurrences. |
| inputs / outputs | Folds five raw values into weights 3 and 2, stages each logical row into two native occurrences, then checks projected counts. |
| invariants | The test models raw duplicate bags as one logical weight per tuple; it does not test a physical bag router or SQL admission. drain rejects duplicate projected cursor rows before map equality. |
| ownership | Pending epoch, raw counts, cursor, and runtime state are local. |
| failure | A duplicate cursor tuple or wrong count fails through check; commit errors propagate. |
| cost | Folds five raw values into two tuple counts, stages both tuples at both native occurrences in one epoch (four stage calls), commits, runs full bag/factor comparison, and drains another cursor for the explicit count assertion. |
| Design | [tests/unit/weighted_bag_test.cpp](../../../../../tests/unit/weighted_bag_test.cpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [tests/integration/weighted_bag.py](../../../../../tests/integration/weighted_bag.py), [Refactor.md §10.2](../../../../../Refactor.md), [tests/integration/weighted_bag.py](../../../../../tests/integration/weighted_bag.py) |

## B0012

[Lines 89–108](../../../../../tests/unit/weighted_bag_test.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void lifetime(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check cursor leases, owning emitted rows, cancellation, and moves. |
| inputs / outputs | Opens two readers, attempts writes, retains one row, cancels, retries, moves cursor and runtime facade. |
| invariants | One reader cancellation does not release another lease; a retained tuple survives source mutation; closed next performs no additional work. |
| ownership | Emitted row owns its tuple; cursor and facade hold their runtime leases through moves. |
| failure | Expected runtime_busy/invalid_cursor codes are checked; assertion mismatches throw runtime_error. |
| cost | Opens two readers, checks a write rejection while leased, retains one row, cancels readers separately, deletes a row, checks cursor rejection inside a pending epoch, then moves a cursor and runtime facade. The successful model mutations also run full oracle comparisons. |
| Design | [tests/unit/weighted_bag_test.cpp](../../../../../tests/unit/weighted_bag_test.cpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [tests/integration/weighted_bag.py](../../../../../tests/integration/weighted_bag.py), [Refactor.md §10.2](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp) |

## B0014

[Lines 110–121](../../../../../tests/unit/weighted_bag_test.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void constants_and_large(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check nullary, contradiction, and counts beyond binary64 precision. |
| inputs / outputs | Runs unary/nullary fixtures with 9007199254740993 then UINT64_MAX; checks both contradiction routes. |
| invariants | The test covers finite u64 values and constant routes; it makes no arbitrary-precision runtime claim. |
| ownership | Models and outputs are local. |
| failure | Overflow or comparison mismatch fails via model/check. |
| cost | Per backend, runs one unary and one nullary fixture with two count replacements each, then checks constant_true and constant_false routes. The exact counts include 2^53+1 and UINT64_MAX. |
| Design | [tests/unit/weighted_bag_test.cpp](../../../../../tests/unit/weighted_bag_test.cpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [tests/integration/weighted_bag.py](../../../../../tests/integration/weighted_bag.py), [Refactor.md §10.2](../../../../../Refactor.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0016

[Lines 123–144](../../../../../tests/unit/weighted_bag_test.cpp#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void typed_and_deep(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check typed rows and deep visible/hidden factorization. |
| inputs / outputs | Compares a typed bag fixture, updates an int/bool row, checks decimal rows, then tests depth 96 with/without hidden variables. |
| invariants | The hidden-variable depth case visits one frame; the visible case checks frame initialization equals depth. |
| ownership | Cursors return owning rows; models and snapshots are local. |
| failure | Assertion or differential mismatches fail through check; runtime API errors propagate unless asserted by a helper. |
| cost | Per invocation, performs six typed-bag updates and two decimal-row updates, then tests 96-node visible and hidden chains with 98 and 99 updates respectively. Each BagModel update reruns full assignment/factor/result comparisons; each chain is drained for its frame-count assertion. |
| Design | [tests/unit/weighted_bag_test.cpp](../../../../../tests/unit/weighted_bag_test.cpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [tests/integration/weighted_bag.py](../../../../../tests/integration/weighted_bag.py), [Refactor.md §10.2](../../../../../Refactor.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0017

[Lines 145–146](../../../../../tests/unit/weighted_bag_test.cpp#L145); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L145-L146:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in weighted_bag_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/weighted_bag_test.cpp](../../../../../tests/unit/weighted_bag_test.cpp), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 147–157](../../../../../tests/unit/weighted_bag_test.cpp#L147); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run weighted bag tests for indexed and non-indexed backends. |
| inputs / outputs | For each backend, calls three counted-path flag variants, then generalized, random, duplicate/self-join, lifetime, constants/large, and typed/deep groups. |
| invariants | Each group is invoked under both backend choices; fixture comparisons use exhaustive native joins. |
| ownership | All group state is local and destroyed on return. |
| failure | Catches std::exception, prints diagnostic, returns 1. |
| cost | Nine helper invocations per backend (18 total); random_cases contributes 400 generated plus six fixed path updates per backend. Mutation-heavy groups also repeat the exhaustive model checks described at their call sites. |
| Design | [tests/unit/weighted_bag_test.cpp](../../../../../tests/unit/weighted_bag_test.cpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [tests/integration/weighted_bag.py](../../../../../tests/integration/weighted_bag.py), [Refactor.md §10.2](../../../../../Refactor.md), [tests/integration/weighted_bag.py](../../../../../tests/integration/weighted_bag.py) |
