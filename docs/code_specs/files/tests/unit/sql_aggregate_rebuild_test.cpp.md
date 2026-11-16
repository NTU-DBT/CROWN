# `tests/unit/sql_aggregate_rebuild_test.cpp` — block usage map

[Source](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Verify whole-image reconstruction, sequences, cumulative grants, constraints and retained ownership.

Snapshot SHA-256: `f8866c8552035c220b9497a5ff9f1a78e444fae8083234f4eb7482602da362f2`. 393 lines partitioned into 34 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 19–19](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L19) | Callable definition: sql_rows::Cell n(std::int64_t value) | calls ; returns storage::ScalarView{value} · [reviewed contract](#b0002) |
| [B0003 · 20–20](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L20) | Callable definition: sql_rows::Cell text(std::string_view value) | calls ; returns storage::ScalarView{value} · [reviewed contract](#b0003) |
| [B0004 · 21–26](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L21) | Callable definition: Catalog catalog() | calls ; returns {1,{{@ ,{{@ ,ScalarType::int64,true},{@ ,ScalarType::string,true}, · [reviewed contract](#b0004) |
| [B0005 · 27–33](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L27) | Callable definition: frontend::SqlAggregateProgram bind(std::string_view sql,const Catalog& schema=catalog(), const frontend::SqlAggregateBindOptions&… | calls catalog, frontend::bind_sql_aggregate, Error, std::move; returns std::get&lt;frontend::SqlAggregateProgram&gt;(std::move(result)) · [reviewed contract](#b0005) |
| [B0006 · 34–39](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L34) | Callable definition: FreeConnexTree tree(const frontend::SqlAggregateProgram& program) | calls source_program, contradiction, export_core, planner::minimum_tree; guard assert(chosen.status==planner::OracleStatus::proven_minimum && chosen.tree);return *chosen.tree;; returns {}; *chosen.tree · [reviewed contract](#b0006) |
| [B0007 · 40–43](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L40) | Callable definition: SqlAggregateRuntime create(const frontend::SqlAggregateProgram& program,bool indexed, sql_aggregate::Options options={}) | calls SqlAggregateRuntime, tree, s04_runtime::options; returns SqlAggregateRuntime(program,tree(program),indexed?s04_runtime::options():PhysicalOptions{},options) · [reviewed contract](#b0007) |
| [B0008 · 44–50](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L44) | Callable definition: sql_aggregate::RebuildLimits limits(bool indexed) | calls ; returns result · [reviewed contract](#b0008) |
| [B0009 · 51–56](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L51) | Callable definition: Results groups(const SqlAggregateRuntime& runtime) | calls snapshot, assert, emplace, export_values; guard assert(result.emplace(group.key.export_values(),group.values.export_values()).second);; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 57–60](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L57) | Callable definition: template&lt;std::size_t N&gt; sql_aggregate::Epoch apply(SqlAggregateRuntime& runtime, const std::array&lt;sql_rows::SourceReplacement,N&gt;&… | calls prepare_batch, sequence, commit; returns runtime.prepare_batch({runtime.sequence()+1,edits}).commit() · [reviewed contract](#b0010) |
| [B0011 · 61–67](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L61) | Callable definition: template&lt;class Action&gt; void rejected(Action action,std::string_view code) | calls action, code, what, assert; guard assert(error.code()==code);return; · [reviewed contract](#b0011) |
| [B0012 · 68–71](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L68) | Callable definition: void controller_only(const resource::MemoryAccount& account) | calls check_invariants, assert, statistics, resource::MemoryAccount::control_bytes; guard account.check_invariants();assert(account.statistics().current.allocations==1); · [reviewed contract](#b0012) |
| [B0013 · 72–74](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L72) | Explanatory comments or spacing. | source comment (unverified): // Actual original SQL/planner/source image, including full hidden separator · [reviewed contract](#b0013) |
| [B0014 · 75–121](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L75) | Callable definition: void joined_round_trip(bool indexed) | calls bind, create, owned, n; guard const auto before=groups(live);assert(before.size()==3);; 1 loop sites; source comment (unverified): // Actual original SQL/planner/source image, including full hidden separator · [reviewed contract](#b0014) |
| [B0015 · 122–124](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L122) | Explanatory comments or spacing. | source comment (unverified): // Qualified/unqualified origin identity, genuine self joins, and full source · [reviewed contract](#b0015) |
| [B0016 · 125–140](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L125) | Callable definition: void alias_round_trip(bool indexed) | calls bind, create, n, text; guard assert(groups(restored)==groups(original) && restored.root_weight()==original.root_weight());; 1 loop sites; source comment (unverified): // Qualified/unqualified origin identity, genuine self joins, and full source · [reviewed contract](#b0016) |
| [B0017 · 141–141](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L141) | Explanatory comments or spacing. |  |
| [B0018 · 142–162](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L142) | Callable definition: void empty_static_and_terminal(bool indexed) | calls bind, create, source_snapshot, assert; guard auto image=original.source_snapshot();assert(image.source.sequence==0 && image.source.rows.empty());; 1 loop sites; source comment (unverified): // Decoded checkpoint C, never a live setter. · [reviewed contract](#b0018) |
| [B0019 · 163–163](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L163) | Explanatory comments or spacing. |  |
| [B0020 · 164–197](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L164) | Callable definition: void invalid_images_and_domains(bool indexed) | calls bind, create, n, text; guard assert(original.sequence()==1 && original.source_weight(TableId{0},row)==2);controller_only(receive…; growth copy_of, push_back; source comment (unverified): // The genuine lowerer rejects this foreign tree before snapshot hash checks. · [reviewed contract](#b0020) |
| [B0021 · 198–198](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L198) | Explanatory comments or spacing. |  |
| [B0022 · 199–219](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L199) | Callable definition: void final_source_constraints(bool indexed) | calls push_back, create, bind, n; guard {auto restored=SqlAggregateRuntime::rebuild_into(receiver,image,{},limits(indexed));assert(groups(r…; returns entry.source==TableId{0}; growth push_back; 1 loop sites · [reviewed contract](#b0022) |
| [B0023 · 220–220](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L220) | Explanatory comments or spacing. |  |
| [B0024 · 221–241](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L221) | Callable definition: void restores_operational_work(bool indexed) | calls create, bind, source_snapshot, resource::MemoryAccount::create; guard try {static_cast&lt;void&gt;(restored.prepare_batch({1,edit}));assert(false);}; 1 loop sites · [reviewed contract](#b0024) |
| [B0025 · 242–242](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L242) | Explanatory comments or spacing. |  |
| [B0026 · 243–273](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L243) | Callable definition: void exact_numeric_metadata(bool indexed) | calls create, bind, catalog, n; guard assert(restored.program().kernel_program().average_scale()==scale && groups(restored)==groups(origi…; 1 loop sites · [reviewed contract](#b0026) |
| [B0027 · 274–276](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L274) | Explanatory comments or spacing. | source comment (unverified): // Exact/one-under grant checks repeat the same whole image. A failed factory · [reviewed contract](#b0027) |
| [B0028 · 277–315](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L277) | Callable definition: void cold_work_and_account_limits(bool indexed) | calls create, bind, n, text; guard {auto run=SqlAggregateRuntime::rebuild_into(receiver,image,{},limits(indexed),&used);assert(run.seq…; source comment (unverified): // Exact/one-under grant checks repeat the same whole image. A failed factory · [reviewed contract](#b0028) |
| [B0029 · 316–319](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L316) | Explanatory comments or spacing. | source comment (unverified): // A genuine image built through 128 small public epochs can exceed the bound · [reviewed contract](#b0029) |
| [B0030 · 320–352](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L320) | Callable definition: void separate_indexed_build_grant() | calls bind, create, source_snapshot, resource::MemoryAccount::create; guard {auto cold=SqlAggregateRuntime::rebuild_into(receiver,zero,{},limits(true),&startup);assert(cold.se…; returns value*2+256; 1 loop sites; source comment (unverified): // A genuine image built through 128 small public epochs can exceed the bound · [reviewed contract](#b0030) |
| [B0031 · 353–356](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L353) | Explanatory comments or spacing. | source comment (unverified): // Covered C++ allocation failures include metadata imports, complete source · [reviewed contract](#b0031) |
| [B0032 · 357–382](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L357) | Callable definition: void allocation_failure_and_lifetime(bool indexed) | calls create, bind, long_name, n; guard assert(allocations && allocations&lt;8192);controller_only(receiver);; 1 loop sites; source comment (unverified): // Covered C++ allocation failures include metadata imports, complete source · [reviewed contract](#b0032) |
| [B0033 · 383–384](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L383) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0033) |
| [B0034 · 385–393](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L385) | Callable definition: int main() | calls joined_round_trip, alias_round_trip, empty_static_and_terminal, invalid_images_and_domains; 1 loop sites · [reviewed contract](#b0034) |

## B0001

[Lines 1–18](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/runtime/sql_aggregate.hpp" #include "crown/planner/oracle.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide fixture helpers for only the genuine public SQL, planner and rebuild APIs. |
| inputs / outputs | Includes aggregate runtime/binder/oracle headers, the established indexed fixture and C++ new allocation test helper; aliases Cell/Results and sets one 64 MiB test account cap. |
| invariants | Tests never include or call \`src/runtime/sql_cold_rebuild.hpp\`; reconstruction enters only through public rebuild_into. |
| ownership | Fixture rows/spans are local C++ objects; engine and receiving account lifetimes are scoped per assertion. |
| failure | Missing include/type errors fail the unit target. |
| cost | Small test-only aliases/constants; no production cost. |
| Design | [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0002

[Lines 19–19](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
sql_rows::Cell n(std::int64_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create one typed nullable int64 test cell. |
| inputs / outputs | Signed integer -&gt; \`sql_rows::Cell\` containing a borrowed ScalarView. |
| invariants | No SQL binder/runtime conversion is simulated by the helper; public factories validate the real cell type later. |
| ownership | ScalarView holds the inline scalar only. |
| failure | No helper error; later row validation can reject it for the schema. |
| cost | One inline variant/optional construction; no owning row or account allocation. |
| Design | [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp) |

## B0003

[Lines 20–20](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
sql_rows::Cell text(std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create one borrowed string test cell. |
| inputs / outputs | string_view -&gt; nullable SQL Cell; caller retains string bytes while a synchronous public source call consumes it. |
| invariants | Not a durable string owner; successful inserted runtime state must copy payload under its receiver account. |
| ownership | The string owner is the test fixture; Cell itself borrows. |
| failure | Dangling/invalid encoding is outside this wrapper and is checked by source admission when applicable. |
| cost | A view/variant only; bytes are not copied here. |
| Design | [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [src/runtime/sql_rows.cpp](../../../../../src/runtime/sql_rows.cpp) |

## B0004

[Lines 21–26](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog catalog()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the three-table SQL catalog used by physical image tests. |
| inputs / outputs | Tables r and s contain nullable typed join/group/measure columns; an \`unused\` table is also present. |
| invariants | The catalog exercises source tables regardless of query use; it has no invented native rows or constraints in this helper. |
| ownership | Catalog owns its ordinary test strings/vectors until real binder/runtime calls copy/import it. |
| failure | Allocation or malformed frontend values propagate to test setup. |
| cost | One finite small schema allocation outside query-account metrics. |
| Design | [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp) |

## B0005

[Lines 27–33](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
frontend::SqlAggregateProgram bind(std::string_view sql,const Catalog& schema=catalog(), const frontend::SqlAggregateBindOptions& options={})
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind original aggregate SQL through the real frontend factory. |
| inputs / outputs | SQL text, schema and bind options -&gt; genuine SqlAggregateProgram; a binding diagnostic is raised as the public Error type. |
| invariants | The test never constructs normalized/kernel/source descriptors directly. |
| ownership | Returned program owns its compiler-side immutable metadata; schema/SQL fixtures remain caller values. |
| failure | Binder diagnostics fail at binding phase before runtime creation. |
| cost | Actual parser/binder/compiler allocation and work; not counted as reconstruction work. |
| Design | [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0006

[Lines 34–39](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
FreeConnexTree tree(const frontend::SqlAggregateProgram& program)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select a checked actual tree for the test program. |
| inputs / outputs | Genuine program -&gt; empty tree for contradiction or proven-minimum tree from the existing planner oracle. |
| invariants | No arbitrary tree is fabricated; returned tree corresponds to the genuine source core. |
| ownership | Tree is test-owned then passed synchronously to runtime factory. |
| failure | Unexpected oracle status/tree absence fails the active assertion. |
| cost | Finite planner-oracle work outside rebuild admission. |
| Design | [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md) |

## B0007

[Lines 40–43](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlAggregateRuntime create(const frontend::SqlAggregateProgram& program,bool indexed, sql_aggregate::Options options={})
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the original live aggregate through the public runtime constructor for comparison. |
| inputs / outputs | Program, backend bool and operational options -&gt; ordered or established S04 indexed SqlAggregateRuntime. |
| invariants | Reference state comes from real APIs; indexed helper selects only backend options and does not bypass source validation. |
| ownership | Runtime owns its account/state, with caller options controlling initial account size. |
| failure | Normal factory errors fail the test setup. |
| cost | One actual runtime construction outside cold-rebuild metrics. |
| Design | [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0008

[Lines 44–50](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
sql_aggregate::RebuildLimits limits(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create generous finite cold-work grants for one selected backend. |
| inputs / outputs | Boolean backend -&gt; fixed source/native/group ceilings; only indexed case receives indexed_work. |
| invariants | Presence tracks the actual backend; values are test allowances, not claimed production defaults or CPU bounds. |
| ownership | Value-only limit object. |
| failure | An indexed presence mismatch is rejected by the factory. |
| cost | No allocation beyond optional value object. |
| Design | [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp) |

## B0009

[Lines 51–56](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Results groups(const SqlAggregateRuntime& runtime)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the public aggregate snapshot into a unique full-key test map. |
| inputs / outputs | Snapshot groups -&gt; \`map&lt;full key, values&gt;\` and assert no duplicate full key. |
| invariants | Hidden group keys stay in key identity; projected-value equality never collapses two keys. |
| ownership | Exported rows in the map are test-owned copies. |
| failure | Duplicate key assertion or snapshot failure ends the test. |
| cost | O(groups plus tuple fields/bytes) eager diagnostic copy, outside cold work grant. |
| Design | [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [docs/sql_aggregate_runtime.md §Results and changed flags](../../../../sql_aggregate_runtime.md) |

## B0010

[Lines 57–60](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<std::size_t N> sql_aggregate::Epoch apply(SqlAggregateRuntime& runtime, const std::array<sql_rows::SourceReplacement,N>& edits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one complete public physical NetBatch and commit it immediately. |
| inputs / outputs | Compile-time array of source replacements -&gt; next contiguous epoch returned by prepare_batch().commit(). |
| invariants | No source row is turned into caller logical BagDelta; the runtime performs alias fanout itself. |
| ownership | Input rows/array borrow through synchronous prepare; returned Epoch owns its output. |
| failure | Source/native/group validation errors propagate from prepare/commit. |
| cost | One real update transaction and its normal operational work. |
| Design | [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [docs/sql_rows_batches.md §Usage and visibility](../../../../sql_rows_batches.md) |

## B0011

[Lines 61–67](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void rejected(Action action,std::string_view code)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that an attempted factory/action fails with one exact public diagnostic code. |
| inputs / outputs | Action closure plus expected code -&gt; return on matching Error; wrong code is printed and asserted; unexpected success fails. |
| invariants | The helper does not translate or swallow unrelated exceptions; only selected Error matches. |
| ownership | Closure borrows fixture captures for the synchronous call. |
| failure | Mismatch is an assertion failure; non-Error exception propagates to test process. |
| cost | One try/catch on negative-test paths only. |
| Design | [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0012

[Lines 68–71](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void controller_only(const resource::MemoryAccount& account)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify receiver allocations have returned to their account-controller baseline. |
| inputs / outputs | MemoryAccount -&gt; invariant check plus exactly one current allocation and control_bytes requested. |
| invariants | Used after the rebuilt facade/locals are gone; it is an account-scope assertion, not a global allocator or RSS claim. |
| ownership | The account handle keeps its controller alive during measurement. |
| failure | Any leaked receiver-owned allocation or broken account invariant fails assertion. |
| cost | Two scalar stats checks plus invariant diagnostic; not a full CPU/allocation trace. |
| Design | [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [docs/memory_accounts.md §Account and ownership contract](../../../../memory_accounts.md) |

## B0013

[Lines 72–74](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L72); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Actual original SQL/planner/source image, including full hidden separator // keys, equal projected groups, nullable keys, filters and an unused table.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the joined round-trip scenario’s real SQL and physical edge cases. |
| inputs / outputs | The following query uses two tables, hidden grouping separator a.id, equal visible groups, nullable fields, filtered rows and an unused table. |
| invariants | The comment states fixture intent; source/runtime behavior comes from the call below. |
| ownership | No state. |
| failure | No executable failure. |
| cost | No runtime cost. |
| Design | [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [docs/sql_rows_batches.md §Expected chains and final constraints](../../../../sql_rows_batches.md) |

## B0014

[Lines 75–121](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void joined_round_trip(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rebuild a populated two-table nullable join image and compare its next committed event. |
| inputs / outputs | Runs ordered and indexed variants; seeds nine full physical entries including weighted rows, filtered/null rows, and unused-table row; snapshots at C=2; builds source-only and aggregate owners, then applies the same next delete to live/restored. |
| invariants | Full physical image retains hidden separator and unused/filtered rows; output comparison uses full key and exact before/after; cold native D facts are not retained in returned epoch. |
| ownership | Old image retains its own handles; reconstructed state is in a separate receiver. Tests receiver controller only after returned owner is destroyed. |
| failure | Any map/output/source/binding mismatch asserts; factories propagate error rather than fabricate state. |
| cost | Two source snapshots, two cold builds, one subsequent epoch; compares selected reported work only for nonzero/back-end presence. No timing theorem. |
| Design | [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [src/runtime/sql_aggregate.cpp](../../../../../src/runtime/sql_aggregate.cpp) |

## B0015

[Lines 122–124](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L122); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Qualified/unqualified origin identity, genuine self joins, and full source // aliases are admitted by their real factories, then rebuilt without row mirrors.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe alias cases that test genuine origin and self-join identity. |
| inputs / outputs | The following fixtures use a same-table self join plus a qualified/unqualified binding query. |
| invariants | Only original SQL binder outputs supply aliases/origins; no hand-authored compiled occurrence. |
| ownership | No state. |
| failure | No executable failure. |
| cost | No runtime cost. |
| Design | [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0016

[Lines 125–140](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void alias_round_trip(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Round-trip self-join and alias-bound programs without a logical row mirror. |
| inputs / outputs | For each genuine SQL query, insert two weighted full rows, snapshot and rebuild in both backends, then compare groups and root weight. |
| invariants | Self-join occurrence identity and qualified/unqualified references are bound by original SQL; every image remains complete physical rows. |
| ownership | Input tuple views live through apply; image and new receiver lifetimes are separate; receiver goes controller-only after rebuilt owner destruction. |
| failure | Any bind, rebuild, root-weight or group mismatch fails. |
| cost | Two small test programs per selected backend and one cold seed each; only a final map/snapshot comparison. |
| Design | [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp), [docs/sql_aggregate_runtime.md §Scope and provenance](../../../../sql_aggregate_runtime.md) |

## B0018

[Lines 142–162](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L142); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void empty_static_and_terminal(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check zero/one frontier, global-empty and terminal-sequence reconstruction. |
| inputs / outputs | Four real queries cover global/grouped aggregates and static constant true/false paths; inspect C=0 empty image, a committed empty C=1 epoch, then mutate the editable image sequence to UINT64_MAX and rebuild. |
| invariants | C=0 initializes authentic static 0/1/global state once; C&gt;0 seed uses C−1→C; next update at max rejects. The test mutates an in-memory image field, so it verifies accepted frontier mechanics, not provenance/authentication. |
| ownership | Each restored owner stays scoped; account should return to controller-only on exit. |
| failure | Incorrect static/group state or next-sequence handling fails exact assertions/invalid_sequence check. |
| cost | Four tiny queries per backend with empty and one empty-source epoch; no durable reader or authentication check. |
| Design | [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [src/runtime/sql_aggregate.cpp](../../../../../src/runtime/sql_aggregate.cpp), [docs/aggregates.md §Logical input and publication](../../../../aggregates.md), [docs/sql_source_images.md §Recovery boundary](../../../../sql_source_images.md) |

## B0020

[Lines 164–197](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L164); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void invalid_images_and_domains(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject malformed editable images, mismatched real programs/bindings and configured domains. |
| inputs / outputs | Mutates snapshots to include zero weight, duplicate row, nonempty C=0, out-of-range table, wrong row width/type, another genuine but invalid plan, mismatched aggregate source SQL, altered binding digest, and too-low count/multiplicity limits. |
| invariants | Failures pass through real lowerer/source/kernel authority. A different genuine tree is rejected by actual \`planner::lower_tree\` as \`invalid_plan\` before post-lowering digest comparison; no catch normalizes it. |
| ownership | Original valid image/program remain owned by caller; each failure uses a separate bad value and receiver returns to controller baseline. |
| failure | Each case checks its exact production error code, including \`invalid_plan\`, \`sql_rows_weight_mismatch\`, \`invalid_sql_aggregate_snapshot\` and arithmetic/domain codes. |
| cost | Finite mutation cases, one compile/lower per relevant attempt; no proof of foreign allocator failures. |
| Design | [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [src/runtime/sql_rows.cpp](../../../../../src/runtime/sql_rows.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/sql_source_images.md §Recovery boundary](../../../../sql_source_images.md) |

## B0022

[Lines 199–219](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L199); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void final_source_constraints(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise real final-state UNIQUE and foreign-key admission independent of image row order. |
| inputs / outputs | Creates enforced parent primary key and child FK; image rows are reversed before successful rebuild; then removing parent or duplicating its key produces failures. |
| invariants | Nullable MATCH SIMPLE FK is admitted when null; parent/child transaction validates final combined state, so an intermediate child-before-parent order does not reject a final-valid seed. |
| ownership | Source image rows borrow immutable row owners; rebuilt native/source/groups are receiver-funded. |
| failure | Missing referenced parent returns foreign_key_violation; duplicate unique key returns unique_violation; test does not translate them. |
| cost | One seed over three physical entries and two rejected replays per backend; actual constraint/index work only. |
| Design | [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [src/runtime/sql_rows.cpp](../../../../../src/runtime/sql_rows.cpp), [docs/sql_rows_batches.md §Expected chains and final constraints](../../../../sql_rows_batches.md) |

## B0024

[Lines 221–241](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L221); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void restores_operational_work(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Show cold limits restore the original operational limits after successful reconstruction. |
| inputs / outputs | Rebuild C=0 under normal cold limits while separately setting group, source or native operational limit to zero; attempt the next empty or row batch. |
| invariants | The receiving runtime retains caller operational source/native/group ceilings; a large cold grant is not left as an ordinary operation budget. |
| ownership | Returned runtime remains live/ready at C=0 after expected operation errors; no mutation publishes. |
| failure | Expected failures are aggregate_work_limit, storage_work_limit or resource_limit according to tested operation phase. |
| cost | Three option variants × ordered/indexed; tests next-operation boundary, not cold exact consumption. |
| Design | [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [docs/sql_aggregate_runtime.md §Account and work costs](../../../../sql_aggregate_runtime.md) |

## B0026

[Lines 243–273](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L243); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void exact_numeric_metadata(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve exact average-scale metadata and tested large-count arithmetic across rebuild. |
| inputs / outputs | Runs AVG scales 0..18 over nullable/negative values and weighted rows; separately tests INT64_MIN times INT64_MAX, over-limit aggregate weight, and signed-int literal SUM boundary/one-over. |
| invariants | Scale is copied from genuine original binding; null count/sum/average semantics and exact arithmetic remain kernel authority. No varying-int32 column admission is tested or implied. |
| ownership | Rows/outputs are actual runtime-owned; receiver is checked after teardown. |
| failure | Out-of-domain final sums fail \`aggregate_overflow\` without publication. |
| cost | 19 scale variants plus bounded large-weight cases per backend; no floating approximation or CPU claim. |
| Design | [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregates.md §Bounded integer sufficient statistics](../../../../aggregates.md) |

## B0027

[Lines 274–276](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L274); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Exact/one-under grant checks repeat the same whole image. A failed factory // exposes no runtime, leaves the image intact and writes no success report.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the exact/one-under grant test on the same complete image. |
| inputs / outputs | The next test first measures one accepted cold build, replays with exactly reported source/native/group/indexed work, then subtracts one selected structural step/domain. |
| invariants | All grants are cold and cumulative; the failed factory must not expose an owner or write report. This does not mean all work dimensions are independently under-tested. |
| ownership | Image and receiver stay live across attempts; each successful returned runtime is destroyed before controller baseline checks. |
| failure | Exact run succeeds; selected one-under cases require work_limit/resource errors while report sentinel remains. |
| cost | The checked domains are reported counters on one finite four-row, three-group fixture; no universal work/cpu statement. |
| Design | [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [docs/sql_source_images.md §Limits and measured work](../../../../sql_source_images.md) |

## B0028

[Lines 277–315](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L277); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cold_work_and_account_limits(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure one four-row/three-group cold image and exercise exact/one-under limits plus receiver denial. |
| inputs / outputs | Rows cover repeated group, different group, null group and filtered row; first build records metrics, exact limits replay successfully, then one-under source/native/group/indexed ceilings and a controller-only account fail at their actual phases. |
| invariants | \`source_work\`, native work, group work and indexed work are separate; indexed case supplies only the indexed ceiling. Metrics remain selected admissions. |
| ownership | All persistent work is on supplied receiver; after failure it remains controller-only; image payload owner is independent. |
| failure | Expected source/indexed \`IndexFailure(storage_work_limit)\`, native \`resource_limit\`, group \`aggregate_work_limit\`, and receiver \`MemoryFailure(limit)\` occur before publication. |
| cost | Four distinct physical entries create three groups; one measured exact replay and bounded failure attempts per backend. It does not measure CPU or all allocator bytes. |
| Design | [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [src/runtime/sql_rows.cpp](../../../../../src/runtime/sql_rows.cpp), [src/runtime/sql_aggregate.cpp](../../../../../src/runtime/sql_aggregate.cpp), [docs/sql_source_images.md §Limits and measured work](../../../../sql_source_images.md) |

## B0029

[Lines 316–319](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L316); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// A genuine image built through 128 small public epochs can exceed the bound // operation grant at cold reconstruction. The new owner must subsequently use
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the indexed-build ceiling scenario that distinguishes cold and ordinary operation grants. |
| inputs / outputs | The following test inserts 128 distinct rows using individual public one-row epochs and then reconstructs the complete image. |
| invariants | The ordinary indexed per_operation ceiling is bound to the native plan and must be restored after cold construction. |
| ownership | No state. |
| failure | No executable failure. |
| cost | 128 normal source epochs plus one cold image build and one ordinary post-build operation. |
| Design | [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [docs/memory_accounts.md §Native accounted dispatch](../../../../memory_accounts.md) |

## B0030

[Lines 320–352](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L320); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void separate_indexed_build_grant()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove one indexed cold grant can exceed the ordinary cap while the returned owner retains that cap. |
| inputs / outputs | Measures startup cold indexed work, builds an actual 128-row image through 128 one-row public updates, rebuilds with explicit large indexed_work, then compares measured build work to ordinary per_operation ceiling and applies one more update. |
| invariants | Uses actual indexed plan/binding and public APIs. No plan limit is rewritten; next ordinary grant is bounded by original five-domain ceiling. |
| ownership | Image and rebuilt owner use receiver-owned fresh state; old plan remains independent. |
| failure | If cold does not exceed any cap dimension or normal follow-up exceeds old cap, assertion fails. |
| cost | 128 separate normal epochs + one bulk cold seed; asserts some cold domain &gt; cap and each follow-up domain ≤ cap, not runtime speed. |
| Design | [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [docs/memory_accounts.md §Accounted compiled-plan storage binding](../../../../memory_accounts.md) |

## B0031

[Lines 353–356](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L353); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Covered C++ allocation failures include metadata imports, complete source // preparation, final group state and fresh normal context creation. This is
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the scoped C++ allocation-denial/lifetime control below. |
| inputs / outputs | The next helper observes C++ allocation calls around one genuine cold factory, then denies each observed call in turn. |
| invariants | This seam covers the installed test \`s04_alloc::Scope\` C++ allocation replacement only; it does not claim libc malloc, parser/native allocator, syscall or global fault coverage. |
| ownership | No state. |
| failure | Each observed denial must produce bad_alloc and trigger the scoped test seam; the factory report sentinel remains unchanged. |
| cost | Bounded by observed call count (&lt;8192) and two runtime backends; no production theorem. |
| Design | [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0032

[Lines 357–382](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L357); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void allocation_failure_and_lifetime(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise each observed C++ \`new\` failure plus post-factory ownership lifetimes. |
| inputs / outputs | For each backend, count one real factory’s s04_alloc calls (&lt;8192), deny each index, expect bad_alloc/triggered and unchanged metrics sentinel, then hold a snapshot across runtime facade move/destruction and release it. |
| invariants | This is the test’s covered C++ allocation seam; it does not include global malloc/parser/upb allocator/syscall fault denial. Successful row strings must stay owned while held output exists. |
| ownership | Source image is separately owned; snapshot owns result tuples after runtime facade closes; held snapshot reset should release receiver bytes to controller-only. |
| failure | Every denial must fail before factory return/report assignment; a missed denial or wrong retained lifetime fails assertion. |
| cost | One pass to count plus bounded cut loop and one success lifetime check per backend; not a total-allocation or CPU guarantee. |
| Design | [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/memory_accounts.md §Native public result tuples](../../../../memory_accounts.md) |

## B0033

[Lines 383–384](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L383); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L383-L384:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in sql_aggregate_rebuild_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0034

[Lines 385–393](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp#L385); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the complete cold-rebuild unit matrix on both native backends. |
| inputs / outputs | For ordered and indexed variants it invokes joined/alias/static/invalid/constraint/operational/numeric/work/account/failure lifetime scenarios; the separate indexed 128-row grant control runs once. |
| invariants | The test exercises public factory/update/snapshot outputs only and keeps failures as exact assertions; it is not a durable restore or SQL-engine oracle. |
| ownership | Each local runtime/image/receiver is destroyed in scenario scope; final message is emitted only after all assertions pass. |
| failure | Any unexpected factory error, assertion or lifetime leak exits unsuccessfully. |
| cost | Nine scenarios per backend, 19 AVG scales per backend, one 128-update indexed control; selected cost and C++ new scope only. |
| Design | [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/sql_aggregate_runtime.md §Scope and provenance](../../../../sql_aggregate_runtime.md) |
