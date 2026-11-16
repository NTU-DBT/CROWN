# `tests/unit/weighted_limits_test.cpp` — block usage map

[Source](../../../../../tests/unit/weighted_limits_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `77dcbbd43921c8d646f685ad809515956ab3ef40112d8c711b0409db25ffc8fb`. 291 lines partitioned into 26 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../tests/unit/weighted_limits_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 10–15](../../../../../tests/unit/weighted_limits_test.cpp#L10) | Callable definition: template&lt;class Action&gt; void error(Action action, std::string_view code) | calls action, check, code, std::runtime_error; guard catch (const Error& failure) {check(failure.code()==code,"unexpected error: "+failure.code());retur… · [reviewed contract](#b0002) |
| [B0003 · 16–18](../../../../../tests/unit/weighted_limits_test.cpp#L16) | Explanatory comments or spacing. | source comment (unverified): // The configured maximum applies to stored sums and products. Failed arithmetic · [reviewed contract](#b0003) |
| [B0004 · 19–41](../../../../../tests/unit/weighted_limits_test.cpp#L19) | Callable definition: void overflow(bool indexed) | calls model, path, set, n; guard check(model.runtime.ready() && model.runtime.sequence()==3,"overflow published sequence");; source comment (unverified): // The configured maximum applies to stored sums and products. Failed arithmetic · [reviewed contract](#b0004) |
| [B0005 · 42–42](../../../../../tests/unit/weighted_limits_test.cpp#L42) | Explanatory comments or spacing. |  |
| [B0006 · 43–46](../../../../../tests/unit/weighted_limits_test.cpp#L43) | Callable definition: void setup(Model& model) | calls set, n; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 47–47](../../../../../tests/unit/weighted_limits_test.cpp#L47) | Explanatory comments or spacing. |  |
| [B0008 · 48–52](../../../../../tests/unit/weighted_limits_test.cpp#L48) | Callable definition: bool stage_input(runtime::WeightedRuntime::PendingEpoch& pending, const w::Replacement& input, bool contribution) | calls stage_contribution, storage::TupleValuesView::borrow, stage; returns pending.stage_contribution(input.node,; pending.stage(input) · [reviewed contract](#b0008) |
| [B0009 · 53–55](../../../../../tests/unit/weighted_limits_test.cpp#L53) | Explanatory comments or spacing. | source comment (unverified): // One work budget funds the whole private logical epoch. The threshold is · [reviewed contract](#b0009) |
| [B0010 · 56–83](../../../../../tests/unit/weighted_limits_test.cpp#L56) | Callable definition: void work_limit(bool indexed, bool contribution) | calls measured, fanout, setup, begin_epoch; guard check(work&gt;0,"empty measured work");; source comment (unverified): // One work budget funds the whole private logical epoch. The threshold is · [reviewed contract](#b0010) |
| [B0011 · 84–86](../../../../../tests/unit/weighted_limits_test.cpp#L84) | Explanatory comments or spacing. | source comment (unverified): // Use a private multi-stage epoch to make its live peak exceed initial runtime · [reviewed contract](#b0011) |
| [B0012 · 87–95](../../../../../tests/unit/weighted_limits_test.cpp#L87) | Callable definition: std::uint64_t heap_scenario(bool indexed, std::uint64_t cap) | calls runtime, unary, begin_epoch, stage; returns runtime.accounted_memory_statistics().peak_requested_bytes; 1 loop sites; source comment (unverified): // Use a private multi-stage epoch to make its live peak exceed initial runtime · [reviewed contract](#b0012) |
| [B0013 · 96–103](../../../../../tests/unit/weighted_limits_test.cpp#L96) | Callable definition: void heap_limit(bool indexed) | calls heap_scenario, check, fault; guard check(heap_scenario(indexed,peak)==peak,"exact requested-byte heap threshold"); · [reviewed contract](#b0013) |
| [B0014 · 104–104](../../../../../tests/unit/weighted_limits_test.cpp#L104) | Explanatory comments or spacing. |  |
| [B0015 · 105–118](../../../../../tests/unit/weighted_limits_test.cpp#L105) | Callable definition: std::uint64_t receiving_peak(const CompiledProgram& source, std::uint64_t cap) | calls resource::MemoryAccount::create, allocate, runtime::WeightedRuntime::create_into, begin_epoch; returns account.statistics().peak_requested_bytes; growth allocate; 1 loop sites · [reviewed contract](#b0015) |
| [B0016 · 119–121](../../../../../tests/unit/weighted_limits_test.cpp#L119) | Explanatory comments or spacing. | source comment (unverified): // The receiver's existing bytes consume the same cap as imported metadata and · [reviewed contract](#b0016) |
| [B0017 · 122–166](../../../../../tests/unit/weighted_limits_test.cpp#L122) | Callable definition: void receiving_limits(bool indexed) | calls unary, CompiledProgram::standalone, account, statistics; guard check(rejected && calls==0,"empty receiver minted an account or allocated");; growth allocate; 2 loop sites; source comment (unverified): // The receiver's existing bytes consume the same cap as imported metadata and · [reviewed contract](#b0017) |
| [B0018 · 167–170](../../../../../tests/unit/weighted_limits_test.cpp#L167) | Explanatory comments or spacing. | source comment (unverified): // Inject at every allocation in a real transaction. Each failure must preserve · [reviewed contract](#b0018) |
| [B0019 · 171–219](../../../../../tests/unit/weighted_limits_test.cpp#L171) | Callable definition: void allocation_cuts(bool indexed, bool capture, bool creation, bool contribution) | calls setup, set, n, baseline; guard check(allocations&gt;0,"empty allocation-cut scenario");; 2 loop sites; source comment (unverified): // Inject at every allocation in a real transaction. Each failure must preserve · [reviewed contract](#b0019) |
| [B0020 · 220–220](../../../../../tests/unit/weighted_limits_test.cpp#L220) | Explanatory comments or spacing. |  |
| [B0021 · 221–240](../../../../../tests/unit/weighted_limits_test.cpp#L221) | Callable definition: void retention_and_churn(bool indexed) | calls runtime, unary, structural_program, account; guard check(runtime.accounted_memory_statistics().current.requested_bytes==baseline,"numeric churn retain…; 1 loop sites · [reviewed contract](#b0021) |
| [B0022 · 241–243](../../../../../tests/unit/weighted_limits_test.cpp#L241) | Explanatory comments or spacing. | source comment (unverified): // Establish an actual native structural-work threshold over many resumed · [reviewed contract](#b0022) |
| [B0023 · 244–268](../../../../../tests/unit/weighted_limits_test.cpp#L244) | Callable definition: std::uint64_t native_grant_scenario(std::optional&lt;std::uint64_t&gt; limit, bool reject, bool contribution) | calls model, fanout, setup, recompute; guard check(spent&gt;previous,"resumed stage refilled native grant");previous=spent;; returns 0; epoch.metrics.native_grant_consumed.structural_steps; 1 loop sites; source comment (unverified): // Establish an actual native structural-work threshold over many resumed · [reviewed contract](#b0023) |
| [B0024 · 269–275](../../../../../tests/unit/weighted_limits_test.cpp#L269) | Callable definition: void native_grant() | calls native_grant_scenario, check; guard check(native_grant_scenario(work,false,contribution)==work,"exact native structural grant threshold…; 1 loop sites · [reviewed contract](#b0024) |
| [B0025 · 276–277](../../../../../tests/unit/weighted_limits_test.cpp#L276) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0025) |
| [B0026 · 278–291](../../../../../tests/unit/weighted_limits_test.cpp#L278) | Callable definition: int main() | calls overflow, heap_limit, receiving_limits, work_limit; returns 1; 4 loop sites · [reviewed contract](#b0026) |

## B0001

[Lines 1–9](../../../../../tests/unit/weighted_limits_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "weighted_bag_fixture.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Connect resource fixtures to independent state/bag checks and allocation injection. |
| inputs / outputs | Weighted bag fixture, replacement-new injector, API errors and output. |
| invariants | Reference recomputation runs outside injected native allocation scopes. |
| ownership | Caller/reference fixtures remain separate from measured query allocation authority. |
| failure | Test harness failures do not translate production failures. |
| cost | Test-only declarations; no production cost. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0002

[Lines 10–15](../../../../../tests/unit/weighted_limits_test.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void error(Action action,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an exact crown::Error code in resource/arithmetic negative cases. |
| inputs / outputs | Action plus expected code; return only on matching Error. |
| invariants | Different exception types propagate; missing/wrong errors fail. |
| ownership | Synchronous callable/value views only. |
| failure | Test runtime_error on mismatch. |
| cost | Negative-test formatting only. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0003

[Lines 16–18](../../../../../tests/unit/weighted_limits_test.cpp#L16); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// The configured maximum applies
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State arithmetic rollback coverage scope. |
| inputs / outputs | Stored sums/products and committed sequence must survive a failed bound check. |
| invariants | Known missing support must short-circuit overflow-prone products. |
| ownership | Comment only; fixtures own concrete rows. |
| failure | No production recovery/transaction extension is claimed. |
| cost | No executable work. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0004

[Lines 19–41](../../../../../tests/unit/weighted_limits_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void overflow(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise existing configured arithmetic maximum and known-zero short circuit. |
| inputs / outputs | Limit100 path/unary sum/product/native-input cases. |
| invariants | Overflow records aborted attempt and preserves exact reference state; unsupported products return zero without spurious overflow. |
| ownership | Models own old committed inputs and runtime independently. |
| failure | Wrong overflow or rollback behavior fails. |
| cost | Small reference fixtures on both backends; no performance measurement. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0006

[Lines 43–46](../../../../../tests/unit/weighted_limits_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void setup(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a repeatable fanout state for measured resource scenarios. |
| inputs / outputs | Four Q rows, one A and one B row establish committed sequence6. |
| invariants | Setup runs before each measured/injected epoch. |
| ownership | Caller Model owns runtime and trusted reference inputs. |
| failure | Model::set validates each committed state. |
| cost | Fixed fixture preparation excluded from subsequent update injection scopes. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0008

[Lines 48–52](../../../../../tests/unit/weighted_limits_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool stage_input(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reuse the exact resource fixture through either absolute or contribution port. |
| inputs / outputs | Pending token, Replacement and selector; shares equal the fixture's full local weights. |
| invariants | Contribution=true does not test overlapping identities; semantic overlap is covered separately. |
| ownership | Borrow input Row until the synchronous stage returns. |
| failure | Preserve original stage failure type; add no catch. |
| cost | Fixed forwarding and borrowed-view construction. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0009

[Lines 53–55](../../../../../tests/unit/weighted_limits_test.cpp#L53); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// One work budget funds
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain empirical exact and one-under work admission fixtures. |
| inputs / outputs | Measure actual abstract operations, then replay at measured threshold and one below. |
| invariants | Budget spans a private logical epoch across stages. |
| ownership | Comment only; no fresh grant implied by resumption. |
| failure | Failure must restore old state. |
| cost | No executable work. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0010

[Lines 56–83](../../../../../tests/unit/weighted_limits_test.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void work_limit(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check cumulative abstract work limits for both staging ports. |
| inputs / outputs | Measure two fanout stages, exact cap replay, one-under abort, and third-stage exhaustion. |
| invariants | Each selected port measures its own work (contributions include extra normalization charge). No per-stage refill; abort restores prior committed snapshots. |
| ownership | Models own independent measured/exact/below accounts and reference inputs. |
| failure | Require resource_limit and unchanged committed sequence/state on rejection. |
| cost | Small deterministic measured update/reference work; thresholds are runtime-dependent receipts when executed. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0011

[Lines 84–86](../../../../../tests/unit/weighted_limits_test.cpp#L84); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Use a private multi-stage epoch
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain why a multi-stage fixture creates a live heap peak above admission. |
| inputs / outputs | Private inserts and explicit captures retain native requested allocations. |
| invariants | Requested bytes include allocator/controller/headers/alignment, not just tuple payload. |
| ownership | Comment only; original query cap remains authority. |
| failure | No process-RSS claim. |
| cost | No executable work. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0012

[Lines 87–95](../../../../../tests/unit/weighted_limits_test.cpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t heap_scenario(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure actual standalone native heap peak for a captured multi-stage epoch. |
| inputs / outputs | Backend/cap; insert40 distinct rows and return peak_requested_bytes. |
| invariants | All private/diagnostic/native retained state shares the configured standalone account. |
| ownership | Local runtime/pending release by RAII after peak read. |
| failure | MemoryFailure propagates for an insufficient cap. |
| cost | Test-only40-row update/capture workload. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0013

[Lines 96–103](../../../../../tests/unit/weighted_limits_test.cpp#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void heap_limit(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replay standalone requested-byte peak at exact and one-under caps. |
| inputs / outputs | Measure at256MiB, require identical peak under exact cap, reject peak-1. |
| invariants | Tests real requested allocations rather than a modeled row count. |
| ownership | Each scenario owns independent account; no inherited capacity. |
| failure | One-under must be MemoryFailure(limit). |
| cost | Three bounded scenario executions, not a throughput benchmark. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0015

[Lines 105–118](../../../../../tests/unit/weighted_limits_test.cpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t receiving_peak(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure one receiving account shared by existing caller resident, imported program and contribution updates. |
| inputs / outputs | Compiled source/cap; keep128-byte sentinel, request UINT64_MAX option, import then insert20 rows by contribution. |
| invariants | Actual receiver cap includes sentinel/controller plus all new state; option cannot enlarge it. |
| ownership | Sentinel remains live through runtime destruction; native source is borrowed only during import. |
| failure | Finite receiver MemoryFailure propagates. |
| cost | Actual receiver peak from a bounded import/update fixture. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0016

[Lines 119–121](../../../../../tests/unit/weighted_limits_test.cpp#L119); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// The receiver's existing bytes consume
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State receiving-account authority and empty-receiver allocation rejection intent. |
| inputs / outputs | Existing sentinel bytes compete with native import/update allocations. |
| invariants | Empty supplied account must reject before any replacement-new request. |
| ownership | Comment only; receiver retains all authority. |
| failure | A new fallback account would violate the test. |
| cost | No executable work. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0017

[Lines 122–166](../../../../../tests/unit/weighted_limits_test.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void receiving_limits(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check empty factories, true receiver heap threshold and every compiled-import allocation cut. |
| inputs / outputs | Both empty overloads execute under fail-at-zero; measured exact/one-under peak; enumerate successful import allocation requests then fail each. |
| invariants | Empty rejection is contract with0 allocation requests. Failed imports preserve sentinel/current residents; foreign compiler statistics stay unchanged. Allocation cuts cover compiled import; both factories have empty/success coverage elsewhere. |
| ownership | Source artifact and receiver/sentinel own separate authority; temporary imports release all new current storage. |
| failure | Require actual injected bad_alloc at every cut, MemoryFailure(limit) below cap, and exact baseline restoration. |
| cost | Test-only repeated admission/injection; historical allocation counters can legitimately record successfully allocated partial work. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0018

[Lines 167–170](../../../../../tests/unit/weighted_limits_test.cpp#L167); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Inject at every allocation in a real transaction.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document resource-failure checks independent of reference execution. |
| inputs / outputs | Native transaction injection excludes direct state/bag reference recomputation. |
| invariants | Every failed cut preserves committed state and releases private ownership. |
| ownership | Comment only; explicit captures remain part of measured native work. |
| failure | Does not claim new transaction/recovery support beyond the local pending epoch. |
| cost | No executable work. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0019

[Lines 171–219](../../../../../tests/unit/weighted_limits_test.cpp#L171); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void allocation_cuts(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate allocation failures for creation/deletion, capture on/off and either staging port. |
| inputs / outputs | Measure begin/two stages, inject each allocation cut, compare full state and projected bag, then retry updates. |
| invariants | Every cut triggers bad_alloc, restores committed sequence and allows retry. Stage uses shares equal to whole row. Final commit/explicit rollback under fail0 must issue no allocation. |
| ownership | Each model owns fresh account/input state; references run after injection scopes. |
| failure | Missing injected failure, leaked state/ownership, wrong bag or allocating publication fails. |
| cost | Exhaustive finite allocation-request enumeration, not a production error-wrapper design. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0021

[Lines 221–240](../../../../../tests/unit/weighted_limits_test.cpp#L221); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void retention_and_churn(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check existing numeric churn does not accumulate live metadata and snapshots retain/release original authority. |
| inputs / outputs | 128 absolute numeric updates, retain snapshot through runtime destruction, then release it. |
| invariants | Current bytes stay constant during scalar churn; final capture release restores control baseline. |
| ownership | Owning Snapshot and MemoryAccount outlive facade intentionally. |
| failure | Byte-growth, missing ownership or retained-allocation leak fails. |
| cost | Test-only repeated native updates and one explicit snapshot. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0022

[Lines 241–243](../../../../../tests/unit/weighted_limits_test.cpp#L241); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Establish an actual native structural-work threshold
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain finite indexed grant reuse over resumed stages and a private snapshot. |
| inputs / outputs | Measure original grant consumption, replay exact/one-under. |
| invariants | Snapshot and staging share the retained indexed grant; abstract work is separate. |
| ownership | Comment only; no fresh stage/capture allowance. |
| failure | Grant exhaustion must restore valid committed state when epoch is abandoned. |
| cost | No executable work. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0023

[Lines 244–268](../../../../../tests/unit/weighted_limits_test.cpp#L244); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t native_grant_scenario(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure/replay one indexed structural allowance over64 resumed stages and private capture. |
| inputs / outputs | Optional native limit, expected rejection and staging-port selector; return consumed structural steps on success. |
| invariants | Grant spent increases every stage and capture. IndexFailure may come from stage (already auto-aborted) or snapshot (explicit rollback here). Verify committed reference after rejection/success. |
| ownership | One pending token retains original lease; captured snapshot is scoped before publication. |
| failure | Require storage_work_limit only; rollback is explicit/idempotent and preserves sequence6. |
| cost | 64 updates plus requested capture; native steps exclude the extra abstract contribution arithmetic charge. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0024

[Lines 269–275](../../../../../tests/unit/weighted_limits_test.cpp#L269); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void native_grant()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert contribution and absolute ports use the same indexed structural-work footprint. |
| inputs / outputs | Measure absolute unlimited scenario; replay both ports at exact native threshold and one below. |
| invariants | One extra arithmetic charge must not create native index work or a second row lookup. |
| ownership | Each scenario owns fresh runtime/lease. |
| failure | Threshold disagreement or missing expected rejection fails. |
| cost | Five bounded resource scenarios; static review here does not claim they executed. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0025

[Lines 276–277](../../../../../tests/unit/weighted_limits_test.cpp#L276); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L276-L277:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in weighted_limits_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/weighted_limits_test.cpp](../../../../../tests/unit/weighted_limits_test.cpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/code_review.md](../../../../code_review.md) |

## B0026

[Lines 278–291](../../../../../tests/unit/weighted_limits_test.cpp#L278); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run resource controls across both backends and all new composition combinations. |
| inputs / outputs | Arithmetic/heap/receiving, per-port work and allocation cuts, churn, then indexed native grant replay. |
| invariants | Retain old absolute resource coverage while adding contribution/create_into coverage. |
| ownership | Fixtures release their own accounts; no production global state. |
| failure | Top-level exception prints diagnostic and returns1. |
| cost | Test-only orchestration; runtime gate receipts remain parent-owned. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |
