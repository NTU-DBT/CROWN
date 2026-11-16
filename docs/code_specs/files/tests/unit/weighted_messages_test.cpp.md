# `tests/unit/weighted_messages_test.cpp` — block usage map

[Source](../../../../../tests/unit/weighted_messages_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `8505efa5441991f8c1adcaa692fd64545aeb2c17f4c0fbd95e8a8db7d3b0e7ad`. 291 lines partitioned into 26 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../tests/unit/weighted_messages_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 10–16](../../../../../tests/unit/weighted_messages_test.cpp#L10) | Callable definition: template&lt;class Action&gt; void error(Action action, std::string_view code) | calls action, check, code, std::runtime_error; guard catch (const Error& failure) {check(failure.code()==code,"unexpected error: "+failure.code());retur… · [reviewed contract](#b0002) |
| [B0003 · 17–17](../../../../../tests/unit/weighted_messages_test.cpp#L17) | Explanatory comments or spacing. |  |
| [B0004 · 18–35](../../../../../tests/unit/weighted_messages_test.cpp#L18) | Callable definition: void native_numeric(bool indexed) | calls model, path, set, n; guard check(model.runtime.root_weight().value==797,"native hidden-witness sum/product"); · [reviewed contract](#b0004) |
| [B0005 · 36–36](../../../../../tests/unit/weighted_messages_test.cpp#L36) | Explanatory comments or spacing. |  |
| [B0006 · 37–53](../../../../../tests/unit/weighted_messages_test.cpp#L37) | Callable definition: void generalized_sums(bool indexed) | calls model, generalized, set, n; guard check(model.runtime.root_weight().value==341,"G(x,z) did not sum products before projecting to x"); · [reviewed contract](#b0006) |
| [B0007 · 54–54](../../../../../tests/unit/weighted_messages_test.cpp#L54) | Explanatory comments or spacing. |  |
| [B0008 · 55–75](../../../../../tests/unit/weighted_messages_test.cpp#L55) | Callable definition: void causal_fifo(bool indexed) | calls model, fanout, set, n; guard check(creation.journal && !creation.journal-&gt;events.empty(),"event capture missing");; 2 loop sites; source comment (unverified): // No B key yet: the first Q event creates G after the actual Q message has · [reviewed contract](#b0008) |
| [B0009 · 76–76](../../../../../tests/unit/weighted_messages_test.cpp#L76) | Explanatory comments or spacing. |  |
| [B0010 · 77–86](../../../../../tests/unit/weighted_messages_test.cpp#L77) | Callable definition: void random_model(bool indexed) | calls model, generalized, random, set; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 87–87](../../../../../tests/unit/weighted_messages_test.cpp#L87) | Explanatory comments or spacing. |  |
| [B0012 · 88–110](../../../../../tests/unit/weighted_messages_test.cpp#L88) | Callable definition: void private_epochs(bool indexed) | calls runtime, unary, apply, n; guard check(pending.stage({NodeId{0},{n(1)},{2},{5}}),"private replacement"); · [reviewed contract](#b0012) |
| [B0013 · 111–113](../../../../../tests/unit/weighted_messages_test.cpp#L111) | Explanatory comments or spacing. | source comment (unverified): // Distinct physical rows can project to the same native tuple. The adapter · [reviewed contract](#b0013) |
| [B0014 · 114–142](../../../../../tests/unit/weighted_messages_test.cpp#L114) | Callable definition: void contributions(bool indexed) | calls model, path, set, n; guard check(pending.stage_contribution(NodeId{0},values,{2},{5}),"first source contribution");; growth emplace_back; 1 loop sites; source comment (unverified): // Distinct physical rows can project to the same native tuple. The adapter · [reviewed contract](#b0014) |
| [B0015 · 143–145](../../../../../tests/unit/weighted_messages_test.cpp#L143) | Explanatory comments or spacing. | source comment (unverified): // Import compiler artifacts into one caller-owned account. Retained native · [reviewed contract](#b0015) |
| [B0016 · 146–177](../../../../../tests/unit/weighted_messages_test.cpp#L146) | Callable definition: void receiving_account(bool indexed) | calls unary, CompiledProgram::standalone, account, statistics; guard check(runtime.owner()==account.statistics().owner &&; returns runtime::WeightedRuntime::create_into(account,temporary); 1 loop sites; source comment (unverified): // Import compiler artifacts into one caller-owned account. Retained native · [reviewed contract](#b0016) |
| [B0017 · 178–180](../../../../../tests/unit/weighted_messages_test.cpp#L178) | Explanatory comments or spacing. | source comment (unverified): // Only the call borrows native cells/string bytes. Mutating the caller's · [reviewed contract](#b0017) |
| [B0018 · 181–207](../../../../../tests/unit/weighted_messages_test.cpp#L181) | Callable definition: void typed_contribution(bool indexed) | calls runtime, planner::lower_tree, options, text; guard check(pending.stage_contribution(NodeId{0},; source comment (unverified): // Only the call borrows native cells/string bytes. Mutating the caller's · [reviewed contract](#b0018) |
| [B0019 · 208–208](../../../../../tests/unit/weighted_messages_test.cpp#L208) | Explanatory comments or spacing. |  |
| [B0020 · 209–228](../../../../../tests/unit/weighted_messages_test.cpp#L209) | Callable definition: void boundaries(bool indexed) | calls model, unary, n, set; guard check(model.runtime.root_weight().value==UINT64_C(9007199254740993),"lost integer precision above 2…; 2 loop sites · [reviewed contract](#b0020) |
| [B0021 · 229–231](../../../../../tests/unit/weighted_messages_test.cpp#L229) | Explanatory comments or spacing. | source comment (unverified): // Empty generalized scope represents the product of three disconnected · [reviewed contract](#b0021) |
| [B0022 · 232–253](../../../../../tests/unit/weighted_messages_test.cpp#L232) | Callable definition: void disconnected_three(bool indexed) | calls model, planner::lower_tree, options, set; guard check(model.runtime.root_weight().value==385,"three-component empty-key product");; source comment (unverified): // Empty generalized scope represents the product of three disconnected · [reviewed contract](#b0022) |
| [B0023 · 254–256](../../../../../tests/unit/weighted_messages_test.cpp#L254) | Explanatory comments or spacing. | source comment (unverified): // Runtime propagation is iterative in tree depth. Use unit native factors to · [reviewed contract](#b0023) |
| [B0024 · 257–278](../../../../../tests/unit/weighted_messages_test.cpp#L257) | Callable definition: void deep_chain() | calls std::to_string, push_back, model, planner::lower_tree; guard check(changed.metrics.events_applied==length && changed.after.value==2,"deep numeric queue");; growth push_back; 2 loop sites; source comment (unverified): // Runtime propagation is iterative in tree depth. Use unit native factors to · [reviewed contract](#b0024) |
| [B0025 · 279–280](../../../../../tests/unit/weighted_messages_test.cpp#L279) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0025) |
| [B0026 · 281–291](../../../../../tests/unit/weighted_messages_test.cpp#L281) | Callable definition: int main() | calls native_numeric, generalized_sums, causal_fifo, random_model; returns 1; 1 loop sites · [reviewed contract](#b0026) |

## B0001

[Lines 1–9](../../../../../tests/unit/weighted_messages_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "weighted_fixture.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Connect weighted semantic tests to the independent full-assignment fixture. |
| inputs / outputs | Fixture/API error/random/output dependencies and local namespaces. |
| invariants | The reference joins assignments rather than reproducing native incremental contribution arithmetic. |
| ownership | Test fixtures own caller inputs outside native accounting; runtime metadata uses its own selected account. |
| failure | Compilation/test harness failure is separate from product error behavior. |
| cost | Test-only includes/aliases; no production overhead. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0002

[Lines 10–16](../../../../../tests/unit/weighted_messages_test.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void error(Action action,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require the expected public error code in a negative fixture. |
| inputs / outputs | Execute Action; accept crown::Error or fixed TupleValidationFailure with matching code. |
| invariants | No exception or wrong code fails the test; do not hide other exception types. |
| ownership | Callable borrowed by value for one synchronous check. |
| failure | Unexpected/missing exception raises test runtime_error. |
| cost | Test-only action and error presentation cost. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0004

[Lines 18–35](../../../../../tests/unit/weighted_messages_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void native_numeric(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check native hidden-witness sums/products and numeric changes without membership changes. |
| inputs / outputs | Deterministic path updates for ordered and indexed storage. |
| invariants | 797→1055 reference count, no diagnostic copies by default, zero deletes, absent zero is a no-op. |
| ownership | Model owns inputs/runtime and independently recomputes committed snapshots. |
| failure | Any count/cache/metric mismatch fails. |
| cost | Small fixture reference recomputation; no claimed production update bound. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0006

[Lines 37–53](../../../../../tests/unit/weighted_messages_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void generalized_sums(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify generalized complete-scope products before separator summation and candidate reclamation. |
| inputs / outputs | Two z assignments with native weights produce exact 341/451 root totals. |
| invariants | Retain partially supported zero-product candidates, remove after last support. |
| ownership | Local model/snapshots own diagnostic state. |
| failure | Wrong sum/candidate count fails. |
| cost | Bounded independent fixture work on both backends. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0008

[Lines 55–75](../../../../../tests/unit/weighted_messages_test.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void causal_fifo(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check same-key causal child totals and owning committed traces. |
| inputs / outputs | Fanout updates capture event IDs/ordinals and root totals 210/490. |
| invariants | Cause precedes effect; committed execution ordinals are consecutive. New generalized row seeds causing value. |
| ownership | Retained journal and snapshot remain owning across later mutations. |
| failure | FIFO/value/lifetime mismatch fails. |
| cost | Optional capture/reference work is test overhead and charged native diagnostic work. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0010

[Lines 77–86](../../../../../tests/unit/weighted_messages_test.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void random_model(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise deterministic generalized-tree update sequences against independent state. |
| inputs / outputs | Seed 0x7202 generates 350 small weight changes for each backend. |
| invariants | Reference compares every maintained row/cache/message through Model::set. |
| ownership | Model owns generated inputs/runtime; no native reference-state mirror is introduced. |
| failure | First mismatch fails reproducibly. |
| cost | Bounded test recomputation, not a performance benchmark. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0012

[Lines 88–110](../../../../../tests/unit/weighted_messages_test.cpp#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void private_epochs(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify existing multi-stage atomicity, move/abandonment, exclusivity and validation failures. |
| inputs / outputs | Tentative 2→5 then stale stage, owner/token moves, destructor rollback and bad scope/type/snapshot cases. |
| invariants | Committed sequence/state survive abort; tentative owning copies retain their captured values. |
| ownership | Token retains actual owner across facade movement; snapshots independently own data. |
| failure | Wrong rejection/rollback/lifetime fails. |
| cost | Small native/reference/capture fixture; no new production path. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0013

[Lines 111–113](../../../../../tests/unit/weighted_messages_test.cpp#L111); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Distinct physical rows can project
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the semantic separation exercised by the contribution test. |
| inputs / outputs | Adapter identity is external; native port changes combined logical weight. |
| invariants | Test must not infer identity authentication from arithmetic acceptance. |
| ownership | Comment only; fixture supplies borrowed cells and trusted share values. |
| failure | No runtime error handling in this comment. |
| cost | No executable cost. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0014

[Lines 114–142](../../../../../tests/unit/weighted_messages_test.cpp#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void contributions(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify shared-key contribution totals, mixed absolute stages, no-ops, underflow abort and final removal. |
| inputs / outputs | Initial local 9; shares 2→5, 7→0, 4→4 then absolute 5→11 capture totals {9,12},{12,5},{5,5},{5,11}. |
| invariants | Existing descendant factors propagate first result to 72. Rejected later share18 rolls back earlier successful private work. This test checks committed event totals but does not retain/assert the raw failing aborted capture. |
| ownership | Borrowed int cells remain live through stages; model records only committed totals. |
| failure | Underflow must close token/preserve sequence4 and exact reference snapshot; wrong totals fail. |
| cost | Both backends, small deterministic direct reference; no count mirror in product. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0015

[Lines 143–145](../../../../../tests/unit/weighted_messages_test.cpp#L143); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Import compiler artifacts into one caller-owned account.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain receiving authority and imported metadata lifetime test intent. |
| inputs / outputs | Compiler artifact may be destroyed after create_into returns. |
| invariants | Retained native metadata belongs to receiver. |
| ownership | Comment only; receiving_account supplies concrete owning accounts. |
| failure | Does not authorize source-account mutation or hidden fallback. |
| cost | No executable work. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0016

[Lines 146–177](../../../../../tests/unit/weighted_messages_test.cpp#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void receiving_account(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check both receiving factories, cap authority, imported lifetime and shared source/receiver ownership. |
| inputs / outputs | 8 MiB receiver overrides requested 1-byte options; plan/artifact imports execute weights7/8. |
| invariants | Foreign compiler statistics stay equal; account current returns to control baseline after releases. Same-account compile/import is intentional and returns to its own baseline. |
| ownership | Temporary compiler destruction cannot invalidate runtime. Receiver and shared artifact keep their correct owners. |
| failure | Wrong owner/cap, leaked bytes or borrowed compiler state fails. |
| cost | Small admission/execution/release fixtures; statistics copies outside measured production updates. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0017

[Lines 178–180](../../../../../tests/unit/weighted_messages_test.cpp#L178); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Only the call borrows native cells/string bytes.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Specify input-buffer mutation as a lifetime adversary. |
| inputs / outputs | Caller cells/string may change immediately after a synchronous stage returns. |
| invariants | Retained keys/results must preserve original admitted values. |
| ownership | Comment only; runtime must copy original-account payload. |
| failure | Detects dangling/retained caller borrow rather than enforcing caller buffer ownership. |
| cost | No executable work. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0018

[Lines 181–207](../../../../../tests/unit/weighted_messages_test.cpp#L181); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void typed_contribution(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify borrowed heterogeneous inputs become owning native keys/results. |
| inputs / outputs | One native tuple contains 192-byte NUL string, bool, leap Date and 38-digit InlineDecimal at weight13. |
| invariants | After staging, mutate string and bool before commit. Cursor must return original four typed values exactly once. |
| ownership | Caller buffers live through stage; returned tuple owns retained values after mutation. |
| failure | Borrow leak, type/value corruption, duplicate/missing cursor result fails. |
| cost | Copies actual string bytes once into native input key; bounded test cursor work. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0020

[Lines 209–228](../../../../../tests/unit/weighted_messages_test.cpp#L209); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void boundaries(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact counts beyond 2^53, empty scopes/constants, native-only writes and identity versioning. |
| inputs / outputs | Nullary/non-nullary rows, contradiction/empty conjunction and different multiplicity limits. |
| invariants | No floating rounding; counter bound changes weighted digest but not structural digest. |
| ownership | Local fixtures own plan/runtime state. |
| failure | Generalized external write rejects; mismatches fail. |
| cost | Small fixed boundary fixtures, both backends. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0021

[Lines 229–231](../../../../../tests/unit/weighted_messages_test.cpp#L229); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Empty generalized scope represents
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the disconnected empty-key and typed-hidden-key adversary. |
| inputs / outputs | Three disconnected components form one empty generalized root scope. |
| invariants | Empty key summarizes product, not concatenated absent keys. |
| ownership | Comment only; fixture values retain concrete typed keys. |
| failure | Does not change admission semantics. |
| cost | No executable work. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0022

[Lines 232–253](../../../../../tests/unit/weighted_messages_test.cpp#L232); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void disconnected_three(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify three disconnected typed components multiply through an empty generalized candidate. |
| inputs / outputs | Int/string/bool hidden keys produce 385 then zero after removals. |
| invariants | Partial candidate remains until final support disappears; typed keys survive storage/snapshot. |
| ownership | Model and snapshots own their respective inputs/captures. |
| failure | Wrong root/candidate lifecycle fails. |
| cost | Bounded direct-join reference work for both backends. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0023

[Lines 254–256](../../../../../tests/unit/weighted_messages_test.cpp#L254); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Runtime propagation is iterative in tree depth.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain why the deep fixture uses unit factors and a bounded exhaustive reference. |
| inputs / outputs | Depth256 stresses event traversal without exploding weight combinations. |
| invariants | Fixture targets iterative traversal, not arbitrary-depth resource admission. |
| ownership | Comment only; owning model holds all tree nodes. |
| failure | No error handler or product guarantee is added. |
| cost | No executable work. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0024

[Lines 257–278](../../../../../tests/unit/weighted_messages_test.cpp#L257); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void deep_chain()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check iterative numeric propagation through depth256. |
| inputs / outputs | Stage all unit native inputs in one epoch; change terminal factor to2 then remove. |
| invariants | The numeric update applies256 events and root becomes2; compare final staged state to independent reference. |
| ownership | Model owns deep plan/input maps; pending token owns transaction. |
| failure | Recursion/event/count/reference mismatch fails. |
| cost | Explicit depth-dependent test work; no constant-time maintenance claim. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0025

[Lines 279–280](../../../../../tests/unit/weighted_messages_test.cpp#L279); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L279-L280:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in weighted_messages_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/weighted_messages_test.cpp](../../../../../tests/unit/weighted_messages_test.cpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/code_review.md](../../../../code_review.md) |

## B0026

[Lines 281–291](../../../../../tests/unit/weighted_messages_test.cpp#L281); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the semantic weighted suite for ordered and indexed storage. |
| inputs / outputs | Existing fixtures plus contributions, receiving_account and typed_contribution; deep chain once. |
| invariants | Both old absolute tests and new composition tests remain in the same executable. |
| ownership | Automatic fixtures release their accounts; no global product state. |
| failure | Top-level std::exception prints diagnostic and returns1. |
| cost | Test orchestration only; no production runtime overhead. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |
