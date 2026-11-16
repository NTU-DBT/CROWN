# `tests/unit/weighted_support_test.cpp` — block usage map

[Source](../../../../../tests/unit/weighted_support_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `93927b815a13b4710d7085b7dfe2d69d5ac2fc8111cae51ecb7ac87bb7e2294c`. 334 lines partitioned into 28 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–24](../../../../../tests/unit/weighted_support_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Independent full-assignment joins and SQL source loops check endpoint output; · [reviewed contract](#b0001) |
| [B0002 · 25–34](../../../../../tests/unit/weighted_support_test.cpp#L25) | Callable definition: Deltas read(std::span&lt;const w::BagDelta&gt; rows,bool support) | calls check, present, emplace, storage::export_row; guard check(row.change.magnitude.present(),"zero captured change");; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 35–46](../../../../../tests/unit/weighted_support_test.cpp#L35) | Callable definition: Deltas support_difference(const Counts& before,const Counts& after) | calls check, contains, emplace; guard check(count!=0,"oracle retained zero");; returns result; growth emplace; 2 loop sites · [reviewed contract](#b0003) |
| [B0004 · 47–51](../../../../../tests/unit/weighted_support_test.cpp#L47) | Callable definition: std::uint64_t total(const Counts& rows) | calls add; returns result; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 52–52](../../../../../tests/unit/weighted_support_test.cpp#L52) | Type/record definition: struct Edit |  · [reviewed contract](#b0005) |
| [B0006 · 53–82](../../../../../tests/unit/weighted_support_test.cpp#L53) | Callable definition: w::Epoch transaction(Model& model,const std::vector&lt;Edit&gt;& edits) | calls bag_oracle, structural_program, accounted_memory_statistics, begin_epoch; guard check(pending.support_delta_preview().has_value() && !pending.bag_delta_preview(),"capture meanings…; returns epoch; 2 loop sites · [reviewed contract](#b0006) |
| [B0007 · 83–83](../../../../../tests/unit/weighted_support_test.cpp#L83) | Explanatory comments or spacing. |  |
| [B0008 · 84–104](../../../../../tests/unit/weighted_support_test.cpp#L84) | Callable definition: void basic_and_private_stages(bool indexed) | calls one, unary, transaction, n; guard check(read(inserted.support_deltas.entries(),true)==Deltas{{Row{n(7)},{false,1}}},"insert unit"); · [reviewed contract](#b0008) |
| [B0009 · 105–107](../../../../../tests/unit/weighted_support_test.cpp#L105) | Explanatory comments or spacing. | source comment (unverified): // Four mutable unary atoms under a genuine generalized node exercise arbitrary · [reviewed contract](#b0009) |
| [B0010 · 108–117](../../../../../tests/unit/weighted_support_test.cpp#L108) | Callable definition: PhysicalPlan four_children(bool indexed) | calls push_back, std::to_string, planner::lower_tree, options; returns planner::lower_tree(catalog,query,tree,options(indexed)); growth push_back; 1 loop sites; source comment (unverified): // Four mutable unary atoms under a genuine generalized node exercise arbitrary · [reviewed contract](#b0010) |
| [B0011 · 118–139](../../../../../tests/unit/weighted_support_test.cpp#L118) | Callable definition: void hidden_nary_and_disconnected(bool indexed) | calls hidden, counted_path, transaction, n · [reviewed contract](#b0011) |
| [B0012 · 140–140](../../../../../tests/unit/weighted_support_test.cpp#L140) | Explanatory comments or spacing. |  |
| [B0013 · 141–153](../../../../../tests/unit/weighted_support_test.cpp#L141) | Callable definition: void random_hidden(bool indexed) | calls model, counted_path, random, n; growth push_back; 2 loop sites · [reviewed contract](#b0013) |
| [B0014 · 154–154](../../../../../tests/unit/weighted_support_test.cpp#L154) | Explanatory comments or spacing. |  |
| [B0015 · 155–178](../../../../../tests/unit/weighted_support_test.cpp#L155) | Callable definition: void numeric_wide_and_lifetime(bool indexed) | calls model, unary, begin_epoch, check; guard check(!numeric.support_delta_preview() && numeric.bag_delta_preview().has_value(),"old numeric prev…; 1 loop sites · [reviewed contract](#b0015) |
| [B0016 · 179–179](../../../../../tests/unit/weighted_support_test.cpp#L179) | Explanatory comments or spacing. |  |
| [B0017 · 180–195](../../../../../tests/unit/weighted_support_test.cpp#L180) | Callable definition: std::uint64_t work_scenario(bool indexed,std::optional&lt;std::uint64_t&gt; cap,bool fail) | calls model, counted_path, begin_epoch, stage; guard } catch(const Error& error) {check(error.code()=="resource_limit","unexpected budget failure");fail…; returns work · [reviewed contract](#b0017) |
| [B0018 · 196–213](../../../../../tests/unit/weighted_support_test.cpp#L196) | Callable definition: void budgets_rollback_and_publication(bool indexed) | calls work_scenario, check, model, unary; guard check(work_scenario(indexed,used,false)==used,"exact support work changed"); · [reviewed contract](#b0018) |
| [B0019 · 214–216](../../../../../tests/unit/weighted_support_test.cpp#L214) | Explanatory comments or spacing. | source comment (unverified): // Repeated private support crossings spend one original indexed allowance. · [reviewed contract](#b0019) |
| [B0020 · 217–237](../../../../../tests/unit/weighted_support_test.cpp#L217) | Callable definition: std::uint64_t indexed_grant(std::optional&lt;std::uint64_t&gt; cap,bool expect_failure) | calls counted_path, options, model, planner::lower_tree; guard check(used&gt;previous,"support stages refilled the indexed grant");previous=used;; returns previous; 1 loop sites; source comment (unverified): // Repeated private support crossings spend one original indexed allowance. · [reviewed contract](#b0020) |
| [B0021 · 238–241](../../../../../tests/unit/weighted_support_test.cpp#L238) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0021) |
| [B0022 · 242–246](../../../../../tests/unit/weighted_support_test.cpp#L242) | Callable definition: SqlBag sql_results(const runtime::SqlRowsRuntime& owner) | calls results, next, check, emplace; guard while(auto row=cursor.next())check(result.emplace(row-&gt;tuple.export_values(),row-&gt;multiplicity).sec…; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0022) |
| [B0023 · 247–257](../../../../../tests/unit/weighted_support_test.cpp#L247) | Callable definition: SqlBag sql_oracle(const std::map&lt;SqlRow,std::uint64_t&gt;& source,bool selfjoin) | calls ; returns result; 2 loop sites · [reviewed contract](#b0023) |
| [B0024 · 258–263](../../../../../tests/unit/weighted_support_test.cpp#L258) | Callable definition: SqlDelta sql_difference(const SqlBag& before,const SqlBag& after) | calls contains, emplace; returns result; growth emplace; 2 loop sites · [reviewed contract](#b0024) |
| [B0025 · 264–279](../../../../../tests/unit/weighted_support_test.cpp#L264) | Callable definition: SqlDelta sql_decode(const frontend::SqlRowsProgram& program,const w::SupportDeltas& deltas) | calls entries, outputs, values, initial_values; guard check(delta.change.magnitude.value==1,"SQL DISTINCT support was nonunit");; returns result; growth emplace, emplace_back; 2 loop sites · [reviewed contract](#b0025) |
| [B0026 · 280–319](../../../../../tests/unit/weighted_support_test.cpp#L280) | Callable definition: void sql_distinct_mapping(bool indexed,bool selfjoin) | calls frontend::bind_sql_rows, check, std::move, export_core; guard check(std::holds_alternative&lt;frontend::SqlRowsProgram&gt;(bound),"support SQL did not bind");; returns runtime::sql_rows::Cell{storage::ScalarView{n}}; runtime::sql_rows::Cell{storage::ScalarView{s}}; growth emplace_back, push_back; 2 loop sites · [reviewed contract](#b0026) |
| [B0027 · 320–320](../../../../../tests/unit/weighted_support_test.cpp#L320) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0027) |
| [B0028 · 321–334](../../../../../tests/unit/weighted_support_test.cpp#L321) | Callable definition: int main() | calls basic_and_private_stages, hidden_nary_and_disconnected, random_hidden, numeric_wide_and_lifetime; guard check(indexed_grant(grant,false)==grant,"exact indexed support grant changed work");; returns 1; 1 loop sites · [reviewed contract](#b0028) |

## B0001

[Lines 1–24](../../../../../tests/unit/weighted_support_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L24:sha256:a53421183b589c5afd6c63ffdd0caf6fbc027b06316e12d3636f6ebdbe48a3f7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare isolated test imports, exact ordinary-heap oracle maps and counters; no query execution occurs in declarations. |
| inputs / outputs | Bounded prototype fixtures/captured views in; owning oracle maps, assertions or one retained epoch/plan out as declared. |
| invariants | No production runtime graph/account is created merely by these aliases/scaffolding. |
| ownership | Test Row/map values own deep payloads; native captures keep their original receiving account. Borrowed views are consumed before owner/token teardown; denied-allocation checks end before diagnostic string construction. |
| failure | Unexpected mismatch/error escapes to main, prints its original diagnostic and returns 1. Expected resource failures are checked at their explicit boundary; no production error suppression. |
| cost | Declarations have no per-query runtime cost; helper bodies state their test work. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0002

[Lines 25–34](../../../../../tests/unit/weighted_support_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L34:sha256:bc9878c9dea8c03449cdc508c8d7b3f3b3d97038f557c2387de9b487620bd8e6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy captured facts into an independent owning map and reject zero, duplicate or nonunit support changes. |
| inputs / outputs | Bounded prototype fixtures/captured views in; owning oracle maps, assertions or one retained epoch/plan out as declared. |
| invariants | Inputs are bounded fixture rows/options; comparisons use complete independent endpoint maps. Snapshot/account inspections are test observations, not production update mirrors. Failures do not imply release acceptance. |
| ownership | Test Row/map values own deep payloads; native captures keep their original receiving account. Borrowed views are consumed before owner/token teardown; denied-allocation checks end before diagnostic string construction. |
| failure | Unexpected mismatch/error escapes to main, prints its original diagnostic and returns 1. Expected resource failures are checked at their explicit boundary; no production error suppression. |
| cost | Test-only ordinary maps, source copies, exhaustive small joins and result enumeration are explicit verification work; no timing/complexity qualification is inferred. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0003

[Lines 35–46](../../../../../tests/unit/weighted_support_test.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L46:sha256:9574c367d32745d219abfb992f549fcfd55387ae07d092f34b6ed3622960a406
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute DISTINCT endpoint changes from independently enumerated bag keys, retaining explicit unit retractions. |
| inputs / outputs | Bounded prototype fixtures/captured views in; owning oracle maps, assertions or one retained epoch/plan out as declared. |
| invariants | Inputs are bounded fixture rows/options; comparisons use complete independent endpoint maps. Snapshot/account inspections are test observations, not production update mirrors. Failures do not imply release acceptance. |
| ownership | Test Row/map values own deep payloads; native captures keep their original receiving account. Borrowed views are consumed before owner/token teardown; denied-allocation checks end before diagnostic string construction. |
| failure | Unexpected mismatch/error escapes to main, prints its original diagnostic and returns 1. Expected resource failures are checked at their explicit boundary; no production error suppression. |
| cost | Test-only ordinary maps, source copies, exhaustive small joins and result enumeration are explicit verification work; no timing/complexity qualification is inferred. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0004

[Lines 47–51](../../../../../tests/unit/weighted_support_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L47-L51:sha256:f9441988356f843f71182ccc044a971459f16d0e1fa611681e63385b75a2cba9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add independently computed projected bag weights with the test oracle checked uint64 addition. |
| inputs / outputs | Bounded prototype fixtures/captured views in; owning oracle maps, assertions or one retained epoch/plan out as declared. |
| invariants | Inputs are bounded fixture rows/options; comparisons use complete independent endpoint maps. Snapshot/account inspections are test observations, not production update mirrors. Failures do not imply release acceptance. |
| ownership | Test Row/map values own deep payloads; native captures keep their original receiving account. Borrowed views are consumed before owner/token teardown; denied-allocation checks end before diagnostic string construction. |
| failure | Unexpected mismatch/error escapes to main, prints its original diagnostic and returns 1. Expected resource failures are checked at their explicit boundary; no production error suppression. |
| cost | Test-only ordinary maps, source copies, exhaustive small joins and result enumeration are explicit verification work; no timing/complexity qualification is inferred. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0005

[Lines 52–52](../../../../../tests/unit/weighted_support_test.cpp#L52); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L52-L52:sha256:bfe32da075d33d59533a083921a7877058724628ff6a78b63115db47b819c961
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name one test-only native row replacement; it owns its ordinary deep Row and final weight. |
| inputs / outputs | Bounded prototype fixtures/captured views in; owning oracle maps, assertions or one retained epoch/plan out as declared. |
| invariants | No production runtime graph/account is created merely by these aliases/scaffolding. |
| ownership | Test Row/map values own deep payloads; native captures keep their original receiving account. Borrowed views are consumed before owner/token teardown; denied-allocation checks end before diagnostic string construction. |
| failure | Unexpected mismatch/error escapes to main, prints its original diagnostic and returns 1. Expected resource failures are checked at their explicit boundary; no production error suppression. |
| cost | Declarations have no per-query runtime cost; helper bodies state their test work. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0006

[Lines 53–82](../../../../../tests/unit/weighted_support_test.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L53-L82:sha256:5639b2d570b5098946b19e1766719ba9ba79eecebb6b66adc554362250e44ffa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stage every requested native replacement, compare each prepared support preview and numeric root endpoints to exhaustive joins, then verify committed capture/cursor/account boundaries. |
| inputs / outputs | Bounded prototype fixtures/captured views in; owning oracle maps, assertions or one retained epoch/plan out as declared. |
| invariants | Inputs are bounded fixture rows/options; comparisons use complete independent endpoint maps. Snapshot/account inspections are test observations, not production update mirrors. Failures do not imply release acceptance. |
| ownership | Test Row/map values own deep payloads; native captures keep their original receiving account. Borrowed views are consumed before owner/token teardown; denied-allocation checks end before diagnostic string construction. |
| failure | Unexpected mismatch/error escapes to main, prints its original diagnostic and returns 1. Expected resource failures are checked at their explicit boundary; no production error suppression. |
| cost | Test-only ordinary maps, source copies, exhaustive small joins and result enumeration are explicit verification work; no timing/complexity qualification is inferred. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0008

[Lines 84–104](../../../../../tests/unit/weighted_support_test.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L84-L104:sha256:e99b59d8c1f890e9557a1a5dd40bbeb1d40d856adae8911cee6fa8d53f843254
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify unit insertion/deletion, positive-to-positive capture skipping with real numeric maintenance, private cancellation and unchanged default opt-out behavior. |
| inputs / outputs | Bounded prototype fixtures/captured views in; owning oracle maps, assertions or one retained epoch/plan out as declared. |
| invariants | Inputs are bounded fixture rows/options; comparisons use complete independent endpoint maps. Snapshot/account inspections are test observations, not production update mirrors. Failures do not imply release acceptance. |
| ownership | Test Row/map values own deep payloads; native captures keep their original receiving account. Borrowed views are consumed before owner/token teardown; denied-allocation checks end before diagnostic string construction. |
| failure | Unexpected mismatch/error escapes to main, prints its original diagnostic and returns 1. Expected resource failures are checked at their explicit boundary; no production error suppression. |
| cost | Test-only ordinary maps, source copies, exhaustive small joins and result enumeration are explicit verification work; no timing/complexity qualification is inferred. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0009

[Lines 105–107](../../../../../tests/unit/weighted_support_test.cpp#L105); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L105-L107:sha256:dd06d478e3b2c163ed24004ac125316dd3dac07055d1d66e7ac949296ce77d0d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare isolated test imports, exact ordinary-heap oracle maps and counters; no query execution occurs in declarations. |
| inputs / outputs | Bounded prototype fixtures/captured views in; owning oracle maps, assertions or one retained epoch/plan out as declared. |
| invariants | No production runtime graph/account is created merely by these aliases/scaffolding. |
| ownership | Test Row/map values own deep payloads; native captures keep their original receiving account. Borrowed views are consumed before owner/token teardown; denied-allocation checks end before diagnostic string construction. |
| failure | Unexpected mismatch/error escapes to main, prints its original diagnostic and returns 1. Expected resource failures are checked at their explicit boundary; no production error suppression. |
| cost | Declarations have no per-query runtime cost; helper bodies state their test work. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0010

[Lines 108–117](../../../../../tests/unit/weighted_support_test.cpp#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L108-L117:sha256:fa49d53635703355253ef0db6c76f1f0a6e3e8f21ba12fc309724400f892fd15
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an admitted generalized root with four mutable native unary children; no specialized runtime implementation is registered. |
| inputs / outputs | Bounded prototype fixtures/captured views in; owning oracle maps, assertions or one retained epoch/plan out as declared. |
| invariants | Inputs are bounded fixture rows/options; comparisons use complete independent endpoint maps. Snapshot/account inspections are test observations, not production update mirrors. Failures do not imply release acceptance. |
| ownership | Test Row/map values own deep payloads; native captures keep their original receiving account. Borrowed views are consumed before owner/token teardown; denied-allocation checks end before diagnostic string construction. |
| failure | Unexpected mismatch/error escapes to main, prints its original diagnostic and returns 1. Expected resource failures are checked at their explicit boundary; no production error suppression. |
| cost | Test-only ordinary maps, source copies, exhaustive small joins and result enumeration are explicit verification work; no timing/complexity qualification is inferred. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0011

[Lines 118–139](../../../../../tests/unit/weighted_support_test.cpp#L118); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L118-L139:sha256:7b652334cb072008c442f29e91fd3aeca8db2f75a16948fc8ea733be0024b71c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise hidden projected witnesses, repeated heads, four-child generalized fan-out, queued fan-out, disconnected bodies and empty output under independent full joins. |
| inputs / outputs | Bounded prototype fixtures/captured views in; owning oracle maps, assertions or one retained epoch/plan out as declared. |
| invariants | Inputs are bounded fixture rows/options; comparisons use complete independent endpoint maps. Snapshot/account inspections are test observations, not production update mirrors. Failures do not imply release acceptance. |
| ownership | Test Row/map values own deep payloads; native captures keep their original receiving account. Borrowed views are consumed before owner/token teardown; denied-allocation checks end before diagnostic string construction. |
| failure | Unexpected mismatch/error escapes to main, prints its original diagnostic and returns 1. Expected resource failures are checked at their explicit boundary; no production error suppression. |
| cost | Test-only ordinary maps, source copies, exhaustive small joins and result enumeration are explicit verification work; no timing/complexity qualification is inferred. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0013

[Lines 141–153](../../../../../tests/unit/weighted_support_test.cpp#L141); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L141-L153:sha256:3a2e62e5d55e2585c2580bcf68bd61c40e00f9478f82f57edaf697f888fa0d71
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run 96 deterministic tiny hidden-projection transactions with 1–3 private stages against exhaustive assignment joins. |
| inputs / outputs | Bounded prototype fixtures/captured views in; owning oracle maps, assertions or one retained epoch/plan out as declared. |
| invariants | Inputs are bounded fixture rows/options; comparisons use complete independent endpoint maps. Snapshot/account inspections are test observations, not production update mirrors. Failures do not imply release acceptance. |
| ownership | Test Row/map values own deep payloads; native captures keep their original receiving account. Borrowed views are consumed before owner/token teardown; denied-allocation checks end before diagnostic string construction. |
| failure | Unexpected mismatch/error escapes to main, prints its original diagnostic and returns 1. Expected resource failures are checked at their explicit boundary; no production error suppression. |
| cost | Test-only ordinary maps, source copies, exhaustive small joins and result enumeration are explicit verification work; no timing/complexity qualification is inferred. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0015

[Lines 155–178](../../../../../tests/unit/weighted_support_test.cpp#L155); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L155-L178:sha256:e03f2adb75680bf91f391824e9b3b6e419186dfcc6ca7408c2994f05560145b3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve original numeric capture for 2**63+1 insertion/retraction and verify support strings/account lifetime after runtime destruction. |
| inputs / outputs | Bounded prototype fixtures/captured views in; owning oracle maps, assertions or one retained epoch/plan out as declared. |
| invariants | Inputs are bounded fixture rows/options; comparisons use complete independent endpoint maps. Snapshot/account inspections are test observations, not production update mirrors. Failures do not imply release acceptance. |
| ownership | Test Row/map values own deep payloads; native captures keep their original receiving account. Borrowed views are consumed before owner/token teardown; denied-allocation checks end before diagnostic string construction. |
| failure | Unexpected mismatch/error escapes to main, prints its original diagnostic and returns 1. Expected resource failures are checked at their explicit boundary; no production error suppression. |
| cost | Test-only ordinary maps, source copies, exhaustive small joins and result enumeration are explicit verification work; no timing/complexity qualification is inferred. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0017

[Lines 180–195](../../../../../tests/unit/weighted_support_test.cpp#L180); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L180-L195:sha256:4df3dff1125ab7c48ed4f24d9936ecbdc4b07f7169d2f2c8b7d0d6cce2534976
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one fixed support transaction with a selected logical work grant and verify atomic rollback at its exact/one-under boundary. |
| inputs / outputs | Bounded prototype fixtures/captured views in; owning oracle maps, assertions or one retained epoch/plan out as declared. |
| invariants | Inputs are bounded fixture rows/options; comparisons use complete independent endpoint maps. Snapshot/account inspections are test observations, not production update mirrors. Failures do not imply release acceptance. |
| ownership | Test Row/map values own deep payloads; native captures keep their original receiving account. Borrowed views are consumed before owner/token teardown; denied-allocation checks end before diagnostic string construction. |
| failure | Unexpected mismatch/error escapes to main, prints its original diagnostic and returns 1. Expected resource failures are checked at their explicit boundary; no production error suppression. |
| cost | Test-only ordinary maps, source copies, exhaustive small joins and result enumeration are explicit verification work; no timing/complexity qualification is inferred. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0018

[Lines 196–213](../../../../../tests/unit/weighted_support_test.cpp#L196); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L196-L213:sha256:5c7ecf48cfab5542235fe4979b40e23793475d9798112dd2926c72f4690f049a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check measured logical-work boundaries, RAII rollback/reused sequence and allocation-free publication of a fully prepared support epoch. |
| inputs / outputs | Bounded prototype fixtures/captured views in; owning oracle maps, assertions or one retained epoch/plan out as declared. |
| invariants | Inputs are bounded fixture rows/options; comparisons use complete independent endpoint maps. Snapshot/account inspections are test observations, not production update mirrors. Failures do not imply release acceptance. |
| ownership | Test Row/map values own deep payloads; native captures keep their original receiving account. Borrowed views are consumed before owner/token teardown; denied-allocation checks end before diagnostic string construction. |
| failure | Unexpected mismatch/error escapes to main, prints its original diagnostic and returns 1. Expected resource failures are checked at their explicit boundary; no production error suppression. |
| cost | Test-only ordinary maps, source copies, exhaustive small joins and result enumeration are explicit verification work; no timing/complexity qualification is inferred. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0019

[Lines 214–216](../../../../../tests/unit/weighted_support_test.cpp#L214); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L214-L216:sha256:ae6c96f300880bfeaaea1fdd9af3c520c39e108d43be6a02a63717b8050f41c9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare isolated test imports, exact ordinary-heap oracle maps and counters; no query execution occurs in declarations. |
| inputs / outputs | Bounded prototype fixtures/captured views in; owning oracle maps, assertions or one retained epoch/plan out as declared. |
| invariants | No production runtime graph/account is created merely by these aliases/scaffolding. |
| ownership | Test Row/map values own deep payloads; native captures keep their original receiving account. Borrowed views are consumed before owner/token teardown; denied-allocation checks end before diagnostic string construction. |
| failure | Unexpected mismatch/error escapes to main, prints its original diagnostic and returns 1. Expected resource failures are checked at their explicit boundary; no production error suppression. |
| cost | Declarations have no per-query runtime cost; helper bodies state their test work. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0020

[Lines 217–237](../../../../../tests/unit/weighted_support_test.cpp#L217); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L217-L237:sha256:2e122583cc84c0ac12b6d229ddccfb60032543ff0c589d6f71037fc6355be588
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spend one indexed structural allowance across 64 private zero crossings, then check exact/one-under capture cancellation and preserved committed results. |
| inputs / outputs | Bounded prototype fixtures/captured views in; owning oracle maps, assertions or one retained epoch/plan out as declared. |
| invariants | Inputs are bounded fixture rows/options; comparisons use complete independent endpoint maps. Snapshot/account inspections are test observations, not production update mirrors. Failures do not imply release acceptance. |
| ownership | Test Row/map values own deep payloads; native captures keep their original receiving account. Borrowed views are consumed before owner/token teardown; denied-allocation checks end before diagnostic string construction. |
| failure | Unexpected mismatch/error escapes to main, prints its original diagnostic and returns 1. Expected resource failures are checked at their explicit boundary; no production error suppression. |
| cost | Test-only ordinary maps, source copies, exhaustive small joins and result enumeration are explicit verification work; no timing/complexity qualification is inferred. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0021

[Lines 238–241](../../../../../tests/unit/weighted_support_test.cpp#L238); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L238-L241:sha256:0bf9de8eac3837b33bf7e2f9ae8753b81d120bf11b34e94eca82525d52e2d79b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare isolated test imports, exact ordinary-heap oracle maps and counters; no query execution occurs in declarations. |
| inputs / outputs | Bounded prototype fixtures/captured views in; owning oracle maps, assertions or one retained epoch/plan out as declared. |
| invariants | No production runtime graph/account is created merely by these aliases/scaffolding. |
| ownership | Test Row/map values own deep payloads; native captures keep their original receiving account. Borrowed views are consumed before owner/token teardown; denied-allocation checks end before diagnostic string construction. |
| failure | Unexpected mismatch/error escapes to main, prints its original diagnostic and returns 1. Expected resource failures are checked at their explicit boundary; no production error suppression. |
| cost | Declarations have no per-query runtime cost; helper bodies state their test work. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0022

[Lines 242–246](../../../../../tests/unit/weighted_support_test.cpp#L242); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L242-L246:sha256:897141190c6ab4481d23f663be52e237521ce25c6de0b0906427e84f82cf0c62
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain the genuine committed SQL cursor into owning test rows, rejecting duplicate SQL tuples. |
| inputs / outputs | Bounded prototype fixtures/captured views in; owning oracle maps, assertions or one retained epoch/plan out as declared. |
| invariants | Inputs are bounded fixture rows/options; comparisons use complete independent endpoint maps. Snapshot/account inspections are test observations, not production update mirrors. Failures do not imply release acceptance. |
| ownership | Test Row/map values own deep payloads; native captures keep their original receiving account. Borrowed views are consumed before owner/token teardown; denied-allocation checks end before diagnostic string construction. |
| failure | Unexpected mismatch/error escapes to main, prints its original diagnostic and returns 1. Expected resource failures are checked at their explicit boundary; no production error suppression. |
| cost | Test-only ordinary maps, source copies, exhaustive small joins and result enumeration are explicit verification work; no timing/complexity qualification is inferred. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0023

[Lines 247–257](../../../../../tests/unit/weighted_support_test.cpp#L247); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L247-L257:sha256:fbccf4b181133081c3edbf37778f7d2b2fcd49efd1d1f973572ee486fda69fe0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate the fixed plain/self-join SQL directly from complete physical source rows, with NULL identity, filter, constants and DISTINCT support independent of native factors. |
| inputs / outputs | Bounded prototype fixtures/captured views in; owning oracle maps, assertions or one retained epoch/plan out as declared. |
| invariants | Inputs are bounded fixture rows/options; comparisons use complete independent endpoint maps. Snapshot/account inspections are test observations, not production update mirrors. Failures do not imply release acceptance. |
| ownership | Test Row/map values own deep payloads; native captures keep their original receiving account. Borrowed views are consumed before owner/token teardown; denied-allocation checks end before diagnostic string construction. |
| failure | Unexpected mismatch/error escapes to main, prints its original diagnostic and returns 1. Expected resource failures are checked at their explicit boundary; no production error suppression. |
| cost | Test-only ordinary maps, source copies, exhaustive small joins and result enumeration are explicit verification work; no timing/complexity qualification is inferred. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0024

[Lines 258–263](../../../../../tests/unit/weighted_support_test.cpp#L258); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L258-L263:sha256:57f6fa728cbfdef14dd92e780611d114518eb8144a7ef037c1d46d7105312e15
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Derive exact unit SQL membership retractions/insertions over before/after row keys without losing negative output. |
| inputs / outputs | Bounded prototype fixtures/captured views in; owning oracle maps, assertions or one retained epoch/plan out as declared. |
| invariants | Inputs are bounded fixture rows/options; comparisons use complete independent endpoint maps. Snapshot/account inspections are test observations, not production update mirrors. Failures do not imply release acceptance. |
| ownership | Test Row/map values own deep payloads; native captures keep their original receiving account. Borrowed views are consumed before owner/token teardown; denied-allocation checks end before diagnostic string construction. |
| failure | Unexpected mismatch/error escapes to main, prints its original diagnostic and returns 1. Expected resource failures are checked at their explicit boundary; no production error suppression. |
| cost | Test-only ordinary maps, source copies, exhaustive small joins and result enumeration are explicit verification work; no timing/complexity qualification is inferred. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0025

[Lines 264–279](../../../../../tests/unit/weighted_support_test.cpp#L264); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L264-L279:sha256:a0535364f8a44a5daf3d8d1c906d09b3338af024f427afecc2cff85ef6449ab2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode genuine native support facts through bound SQL payload/presence/constant output metadata and verify unit/injective SQL output identity. |
| inputs / outputs | Bounded prototype fixtures/captured views in; owning oracle maps, assertions or one retained epoch/plan out as declared. |
| invariants | Inputs are bounded fixture rows/options; comparisons use complete independent endpoint maps. Snapshot/account inspections are test observations, not production update mirrors. Failures do not imply release acceptance. |
| ownership | Test Row/map values own deep payloads; native captures keep their original receiving account. Borrowed views are consumed before owner/token teardown; denied-allocation checks end before diagnostic string construction. |
| failure | Unexpected mismatch/error escapes to main, prints its original diagnostic and returns 1. Expected resource failures are checked at their explicit boundary; no production error suppression. |
| cost | Test-only ordinary maps, source copies, exhaustive small joins and result enumeration are explicit verification work; no timing/complexity qualification is inferred. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0026

[Lines 280–319](../../../../../tests/unit/weighted_support_test.cpp#L280); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L280-L319:sha256:6087588211fd4889fe395a286d3c17a068a49d5ad4a40a70286370b7312e78d7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain reviewed direct physical SQL DISTINCT/self-join oracle checks after the prototype test is renamed for maintenance. |
| inputs / outputs | Bounded declared fixtures/public views in; owning ordinary test values, checked expectations or the declared test object out. |
| invariants | Reference models use full assignment joins or direct physical SQL rows, not incremental factor/output code. Tests keep source/full-group/SQL tuple identities and signed uint64 output units distinct. Assertions require maintained -UNDEBUG. |
| ownership | Test snapshots/maps/source copies are explicit verification workspace. Public output borrows are consumed within token/scratch lifetime; allocation-denial checks avoid owning diagnostics inside the denied scope. |
| failure | Unexpected diagnostics or assertion failures fail the test. Expected contract/resource errors are checked at exact boundaries and original state/account preservation is inspected. |
| cost | Finite test oracle/JSON/deep export costs belong to verification, not the production update path or a performance qualification. No release completeness claim follows from finite tests. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0027

[Lines 320–320](../../../../../tests/unit/weighted_support_test.cpp#L320); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L320-L320:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the isolated test-only anonymous namespace; no operation or allocation occurs. |
| inputs / outputs | No runtime input or output; subsequent main is outside this private namespace. |
| invariants | This lexical closure carries no algorithm or rollback authority. |
| ownership | Closing the namespace does not destroy any runtime object. |
| failure | No runtime failure path exists in a lexical namespace closure. |
| cost | No execution or per-query cost. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0028

[Lines 321–334](../../../../../tests/unit/weighted_support_test.cpp#L321); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L321-L334:sha256:c99b4b376ee786fda9255cc5b11737e8e0caa19db67ad6b55296ae814ac0a7c7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the named finite both-backend SQL-output/support cases and report actual checked counters only after success. |
| inputs / outputs | Bounded declared fixtures/public views in; owning ordinary test values, checked expectations or the declared test object out. |
| invariants | Reference models use full assignment joins or direct physical SQL rows, not incremental factor/output code. Tests keep source/full-group/SQL tuple identities and signed uint64 output units distinct. Assertions require maintained -UNDEBUG. |
| ownership | Test snapshots/maps/source copies are explicit verification workspace. Public output borrows are consumed within token/scratch lifetime; allocation-denial checks avoid owning diagnostics inside the denied scope. |
| failure | Unexpected diagnostics or assertion failures fail the test. Expected contract/resource errors are checked at exact boundaries and original state/account preservation is inspected. |
| cost | Finite test oracle/JSON/deep export costs belong to verification, not the production update path or a performance qualification. No release completeness claim follows from finite tests. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |
