# `tests/unit/sql_rows_batch_test.cpp` — block usage map

[Source](../../../../../tests/unit/sql_rows_batch_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `c845ed745cfae5db54d9fd67c3e8acdc7ca6de471ec2da28639c6671f27b2c63`. 736 lines partitioned into 66 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–29](../../../../../tests/unit/sql_rows_batch_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // negative, magnitude · [reviewed contract](#b0001) |
| [B0002 · 30–30](../../../../../tests/unit/sql_rows_batch_test.cpp#L30) | Callable definition: Cell n(std::int64_t value) | calls ; returns storage::ScalarView{value} · [reviewed contract](#b0002) |
| [B0003 · 31–31](../../../../../tests/unit/sql_rows_batch_test.cpp#L31) | Callable definition: Cell s(std::string_view value) | calls ; returns storage::ScalarView{value} · [reviewed contract](#b0003) |
| [B0004 · 32–32](../../../../../tests/unit/sql_rows_batch_test.cpp#L32) | Callable definition: Value v(std::int64_t value) | calls ; returns value · [reviewed contract](#b0004) |
| [B0005 · 33–33](../../../../../tests/unit/sql_rows_batch_test.cpp#L33) | Explanatory comments or spacing. |  |
| [B0006 · 34–39](../../../../../tests/unit/sql_rows_batch_test.cpp#L34) | Callable definition: frontend::SqlRowsProgram compile_rows(std::string_view sql, const Catalog& catalog) | calls frontend::bind_sql_rows, Error, std::move; returns std::get&lt;frontend::SqlRowsProgram&gt;(std::move(result)) · [reviewed contract](#b0006) |
| [B0007 · 40–40](../../../../../tests/unit/sql_rows_batch_test.cpp#L40) | Explanatory comments or spacing. |  |
| [B0008 · 41–47](../../../../../tests/unit/sql_rows_batch_test.cpp#L41) | Callable definition: FreeConnexTree tree_for(const frontend::SqlRowsProgram& program) | calls contradiction, export_core, planner::minimum_tree, assert; guard assert(result.status==planner::OracleStatus::proven_minimum && result.tree);; returns {}; *result.tree · [reviewed contract](#b0008) |
| [B0009 · 48–48](../../../../../tests/unit/sql_rows_batch_test.cpp#L48) | Explanatory comments or spacing. |  |
| [B0010 · 49–53](../../../../../tests/unit/sql_rows_batch_test.cpp#L49) | Callable definition: SqlRowsRuntime create(const frontend::SqlRowsProgram& program, bool indexed, sql_rows::Options options={}) | calls SqlRowsRuntime, tree_for, s04_runtime::options; returns SqlRowsRuntime(program,tree_for(program), · [reviewed contract](#b0010) |
| [B0011 · 54–54](../../../../../tests/unit/sql_rows_batch_test.cpp#L54) | Explanatory comments or spacing. |  |
| [B0012 · 55–62](../../../../../tests/unit/sql_rows_batch_test.cpp#L55) | Callable definition: Bag drain(SqlRowsRuntime::ResultCursor& cursor) | calls next, emplace, export_values, assert; guard static_cast&lt;void&gt;(position);assert(inserted);; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 63–63](../../../../../tests/unit/sql_rows_batch_test.cpp#L63) | Explanatory comments or spacing. |  |
| [B0014 · 64–66](../../../../../tests/unit/sql_rows_batch_test.cpp#L64) | Callable definition: Bag results(const SqlRowsRuntime& runtime) | calls drain; returns drain(cursor) · [reviewed contract](#b0014) |
| [B0015 · 67–67](../../../../../tests/unit/sql_rows_batch_test.cpp#L67) | Explanatory comments or spacing. |  |
| [B0016 · 68–72](../../../../../tests/unit/sql_rows_batch_test.cpp#L68) | Callable definition: template&lt;class Action&gt; void error(Action action, std::string_view expected) | calls action, assert, code; guard catch (const Error& failure) { assert(failure.code()==expected);return; } · [reviewed contract](#b0016) |
| [B0017 · 73–73](../../../../../tests/unit/sql_rows_batch_test.cpp#L73) | Explanatory comments or spacing. |  |
| [B0018 · 74–77](../../../../../tests/unit/sql_rows_batch_test.cpp#L74) | Callable definition: sql_rows::SourceReplacement edit(std::size_t source, const Cells& row, std::uint64_t before, std::uint64_t after) | calls ; returns {TableId{source},std::span&lt;const Cell&gt;(row),before,after} · [reviewed contract](#b0018) |
| [B0019 · 78–78](../../../../../tests/unit/sql_rows_batch_test.cpp#L78) | Explanatory comments or spacing. |  |
| [B0020 · 79–83](../../../../../tests/unit/sql_rows_batch_test.cpp#L79) | Callable definition: template&lt;std::size_t N&gt; SqlRowsRuntime::PreparedBatch prepare_at(SqlRowsRuntime& runtime, std::uint64_t sequence, const std::arra… | calls prepare_batch; returns runtime.prepare_batch({sequence,std::span&lt;const sql_rows::SourceReplacement&gt;(edits)},capture) · [reviewed contract](#b0020) |
| [B0021 · 84–84](../../../../../tests/unit/sql_rows_batch_test.cpp#L84) | Explanatory comments or spacing. |  |
| [B0022 · 85–89](../../../../../tests/unit/sql_rows_batch_test.cpp#L85) | Callable definition: template&lt;std::size_t N&gt; SqlRowsRuntime::PreparedBatch prepare(SqlRowsRuntime& runtime, const std::array&lt;sql_rows::SourceReplaceme… | calls prepare_at, sequence; returns prepare_at(runtime,runtime.sequence()+1,edits,capture) · [reviewed contract](#b0022) |
| [B0023 · 90–90](../../../../../tests/unit/sql_rows_batch_test.cpp#L90) | Explanatory comments or spacing. |  |
| [B0024 · 91–94](../../../../../tests/unit/sql_rows_batch_test.cpp#L91) | Callable definition: sql_rows::Epoch replace(SqlRowsRuntime& runtime, std::size_t source, const Cells& row, std::uint64_t before, std::uint64_t after) | calls apply, sequence; returns runtime.apply({runtime.sequence()+1,TableId{source},row,before,after}) · [reviewed contract](#b0024) |
| [B0025 · 95–95](../../../../../tests/unit/sql_rows_batch_test.cpp#L95) | Explanatory comments or spacing. |  |
| [B0026 · 96–107](../../../../../tests/unit/sql_rows_batch_test.cpp#L96) | Callable definition: CoreDelta read_core_delta(std::span&lt;const weighted::BagDelta&gt; entries, std::optional&lt;std::uint64_t&gt; expected_owner={}) | calls assert, present, storage::export_row, values; guard assert(entry.change.magnitude.present());; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0026) |
| [B0027 · 108–108](../../../../../tests/unit/sql_rows_batch_test.cpp#L108) | Explanatory comments or spacing. |  |
| [B0028 · 109–114](../../../../../tests/unit/sql_rows_batch_test.cpp#L109) | Callable definition: CoreDelta preview_core_delta(const SqlRowsRuntime::PreparedBatch& batch, std::uint64_t expected_owner) | calls native_bag_delta_preview, assert, has_value, read_core_delta; guard assert(preview.has_value());; returns read_core_delta(*preview,expected_owner); source comment (unverified): // Copy the borrowed span now. · [reviewed contract](#b0028) |
| [B0029 · 115–115](../../../../../tests/unit/sql_rows_batch_test.cpp#L115) | Explanatory comments or spacing. |  |
| [B0030 · 116–120](../../../../../tests/unit/sql_rows_batch_test.cpp#L116) | Callable definition: void assert_committed_core_delta(const sql_rows::Epoch& epoch, const CoreDelta& expected, std::uint64_t expected_owner) | calls assert, read_core_delta, entries; guard assert(epoch.native.bag_deltas); · [reviewed contract](#b0030) |
| [B0031 · 121–121](../../../../../tests/unit/sql_rows_batch_test.cpp#L121) | Explanatory comments or spacing. |  |
| [B0032 · 122–124](../../../../../tests/unit/sql_rows_batch_test.cpp#L122) | Callable definition: Catalog nonnull_rows_schema() | calls ; returns {1,{{@ ,{{@ ,ScalarType::int64,false},{@ ,ScalarType::string,false}}}}} · [reviewed contract](#b0032) |
| [B0033 · 125–125](../../../../../tests/unit/sql_rows_batch_test.cpp#L125) | Explanatory comments or spacing. |  |
| [B0034 · 126–131](../../../../../tests/unit/sql_rows_batch_test.cpp#L126) | Callable definition: Catalog unique_schema() | calls push_back; returns catalog; growth push_back · [reviewed contract](#b0034) |
| [B0035 · 132–132](../../../../../tests/unit/sql_rows_batch_test.cpp#L132) | Explanatory comments or spacing. |  |
| [B0036 · 133–175](../../../../../tests/unit/sql_rows_batch_test.cpp#L133) | Callable definition: void exact_chains_noops_and_cancellation(bool indexed) | calls compile_rows, nonnull_rows_schema, create, n; guard assert(prepared.active() && prepared.sequence()==1); · [reviewed contract](#b0036) |
| [B0037 · 176–176](../../../../../tests/unit/sql_rows_batch_test.cpp#L176) | Explanatory comments or spacing. |  |
| [B0038 · 177–194](../../../../../tests/unit/sql_rows_batch_test.cpp#L177) | Callable definition: void wrong_chain_rolls_back_and_reuses_sequence(bool indexed) | calls compile_rows, nonnull_rows_schema, create, n; guard assert(runtime.ready() && runtime.sequence()==0 && runtime.root_weight().value==0); · [reviewed contract](#b0038) |
| [B0039 · 195–195](../../../../../tests/unit/sql_rows_batch_test.cpp#L195) | Explanatory comments or spacing. |  |
| [B0040 · 196–228](../../../../../tests/unit/sql_rows_batch_test.cpp#L196) | Callable definition: void final_unique_swap_and_violations(bool indexed) | calls compile_rows, unique_schema, create, n; guard assert(preview_core_delta(prepared,owner)==expected);; source comment (unverified): // Both additions precede both removals in the input span; only final keys · [reviewed contract](#b0040) |
| [B0041 · 229–229](../../../../../tests/unit/sql_rows_batch_test.cpp#L229) | Explanatory comments or spacing. |  |
| [B0042 · 230–269](../../../../../tests/unit/sql_rows_batch_test.cpp#L230) | Callable definition: void foreign_key_final_order_and_untouched_child(bool indexed) | calls push_back, compile_rows, create, n; guard assert(added.changed && runtime.source_weight(TableId{0},parent)==1);; growth push_back · [reviewed contract](#b0042) |
| [B0043 · 270–270](../../../../../tests/unit/sql_rows_batch_test.cpp#L270) | Explanatory comments or spacing. |  |
| [B0044 · 271–320](../../../../../tests/unit/sql_rows_batch_test.cpp#L271) | Callable definition: void self_reference_and_two_table_cycles(bool indexed) | calls create, compile_rows, n, edit; guard assert(self_added.changed && self_runtime.source_weight(TableId{0},loop)==1);; source comment (unverified): // b is an unused catalog source. · [reviewed contract](#b0044) |
| [B0045 · 321–321](../../../../../tests/unit/sql_rows_batch_test.cpp#L321) | Explanatory comments or spacing. |  |
| [B0046 · 322–383](../../../../../tests/unit/sql_rows_batch_test.cpp#L322) | Callable definition: void nullable_composite_keys_and_empty_keys(bool indexed) | calls push_back, create, compile_rows, n; guard assert(runtime.source_weight(TableId{0},null_flag_a)==1 && runtime.source_weight(TableId{0},null_fl…; growth push_back; source comment (unverified): // The child physical order is (a,flag); FK key order is (flag,a), matching · [reviewed contract](#b0046) |
| [B0047 · 384–384](../../../../../tests/unit/sql_rows_batch_test.cpp#L384) | Explanatory comments or spacing. |  |
| [B0048 · 385–404](../../../../../tests/unit/sql_rows_batch_test.cpp#L385) | Callable definition: void cap_safe_decrease_before_increase(bool indexed) | calls compile_rows, nonnull_rows_schema, create, n; guard assert(runtime.root_weight().value==2 && (results(runtime)==Bag{{SqlRow{v(7)},2}}));; source comment (unverified): // The replacement order adds first. Staging that increase against the old · [reviewed contract](#b0048) |
| [B0049 · 405–405](../../../../../tests/unit/sql_rows_batch_test.cpp#L405) | Explanatory comments or spacing. |  |
| [B0050 · 406–420](../../../../../tests/unit/sql_rows_batch_test.cpp#L406) | Callable definition: void unsigned_delta_magnitude(bool indexed) | calls compile_rows, nonnull_rows_schema, create, n; guard assert(preview_core_delta(prepared,owner)==expected);; growth insert · [reviewed contract](#b0050) |
| [B0051 · 421–421](../../../../../tests/unit/sql_rows_batch_test.cpp#L421) | Explanatory comments or spacing. |  |
| [B0052 · 422–447](../../../../../tests/unit/sql_rows_batch_test.cpp#L422) | Callable definition: void filtered_and_contradictory_sources(bool indexed) | calls nonnull_rows_schema, n, s, create; guard assert(filtered_pending.native_preview().metrics.native_inputs==0);; source comment (unverified): // Equality to NULL is an existing binder contradiction. Its unused source · [reviewed contract](#b0052) |
| [B0053 · 448–448](../../../../../tests/unit/sql_rows_batch_test.cpp#L448) | Explanatory comments or spacing. |  |
| [B0054 · 449–499](../../../../../tests/unit/sql_rows_batch_test.cpp#L449) | Callable definition: void aliases_single_native_epoch_and_delta_wrappers(bool indexed) | calls nonnull_rows_schema, compile_rows, create, n; guard assert((results(runtime)==Bag{{SqlRow{v(7)},25}}));; source comment (unverified): // Increase is first in the borrowed input, but every alias decrease is · [reviewed contract](#b0054) |
| [B0055 · 500–500](../../../../../tests/unit/sql_rows_batch_test.cpp#L500) | Explanatory comments or spacing. |  |
| [B0056 · 501–541](../../../../../tests/unit/sql_rows_batch_test.cpp#L501) | Callable definition: void one_source_allowance_and_retry(bool indexed) | calls compile_rows, nonnull_rows_schema, n, s; guard assert(measured.source_work.structural_steps==full_work.structural_steps && · [reviewed contract](#b0056) |
| [B0057 · 542–542](../../../../../tests/unit/sql_rows_batch_test.cpp#L542) | Explanatory comments or spacing. |  |
| [B0058 · 543–559](../../../../../tests/unit/sql_rows_batch_test.cpp#L543) | Callable definition: void native_overflow_rolls_back_then_retries(bool indexed) | calls compile_rows, nonnull_rows_schema, create, n; guard assert(runtime.root_weight().value==4 && runtime.sequence()==1); · [reviewed contract](#b0058) |
| [B0059 · 560–560](../../../../../tests/unit/sql_rows_batch_test.cpp#L560) | Explanatory comments or spacing. |  |
| [B0060 · 561–597](../../../../../tests/unit/sql_rows_batch_test.cpp#L561) | Callable definition: void preparation_allocation_cuts_rollback_and_retry(bool indexed) | calls compile_rows, nonnull_rows_schema, n, s; guard assert(allocations&gt;0);; 1 loop sites · [reviewed contract](#b0060) |
| [B0061 · 598–598](../../../../../tests/unit/sql_rows_batch_test.cpp#L598) | Explanatory comments or spacing. |  |
| [B0062 · 599–636](../../../../../tests/unit/sql_rows_batch_test.cpp#L599) | Callable definition: void close_releases_prepared_workspace_without_new(bool indexed) | calls compile_rows, nonnull_rows_schema, n, s; guard assert(prepared.active() && pending&gt;resident);; growth emplace; source comment (unverified): // Drop returned delta payloads before measuring closed-token residency. · [reviewed contract](#b0062) |
| [B0063 · 637–637](../../../../../tests/unit/sql_rows_batch_test.cpp#L637) | Explanatory comments or spacing. |  |
| [B0064 · 638–711](../../../../../tests/unit/sql_rows_batch_test.cpp#L638) | Callable definition: void prepared_owner_busy_abandonment_and_move_assignment(bool indexed) | calls compile_rows, nonnull_rows_schema, expected_text, create; guard assert(token.active() && token.sequence()==1 && token.program().source_sha256()==program.source_sha…; returns token; growth emplace; source comment (unverified): // Both caller string and Cell storage die after prepare_batch returns. · [reviewed contract](#b0064) |
| [B0065 · 712–714](../../../../../tests/unit/sql_rows_batch_test.cpp#L712) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0065) |
| [B0066 · 715–736](../../../../../tests/unit/sql_rows_batch_test.cpp#L715) | Callable definition: int main() | calls exact_chains_noops_and_cancellation, wrong_chain_rolls_back_and_reuses_sequence, final_unique_swap_and_violations, foreign_key_final_order_and_untouched_child; returns 1; 1 loop sites · [reviewed contract](#b0066) |

## B0001

[Lines 1–29](../../../../../tests/unit/sql_rows_batch_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L29:sha256:ba5d7519302fb6798d8fdc7cb54f12c699d6f7c086cfc3886f82903d8b466502
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare sql_rows_batch_test.cpp: include "crown/api/error.hpp", "crown/runtime/sql_rows.hpp", "crown/planner/oracle.hpp", "indexed_runtime_fixture.hpp", "index_allocation.hpp", &lt;array&gt;, &lt;cassert&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;map&gt;, &lt;optional&gt;, &lt;span&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;utility&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 30–30](../../../../../tests/unit/sql_rows_batch_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Cell n(std::int64_t value) { return storage::ScalarView{value}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make integer input Cell. |
| inputs / outputs | int64 → ScalarView Cell. |
| invariants | Preserves scalar/type; selects no column/source. |
| ownership | Owns scalar; no backing borrow. |
| failure | No app failure expected. |
| cost | Fixed variant construction. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/sql_rows_runtime.md §Representation and SQL semantics](../../../../sql_rows_runtime.md) |

## B0003

[Lines 31–31](../../../../../tests/unit/sql_rows_batch_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Cell s(std::string_view value) { return storage::ScalarView{value}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make string input Cell. |
| inputs / outputs | Borrowed string_view → ScalarView Cell. |
| invariants | Bytes live through synchronous row consumption. |
| ownership | Cell does not own/copy; prepare freezes before returning. |
| failure | No conversion check; stale view is caller misuse. |
| cost | View wrapper; later freeze may copy bytes. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/sql_rows_batches.md §Usage and visibility](../../../../sql_rows_batches.md) |

## B0004

[Lines 32–32](../../../../../tests/unit/sql_rows_batch_test.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value v(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make core Value expectation. |
| inputs / outputs | int64 → Value. |
| invariants | Core expected fact differs from input Cell view. |
| ownership | Owning scalar. |
| failure | No app failure expected. |
| cost | Fixed scalar; caller maps may allocate. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/weighted_deltas.md §Calling contract](../../../../weighted_deltas.md) |

## B0006

[Lines 34–39](../../../../../tests/unit/sql_rows_batch_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
frontend::SqlRowsProgram compile_rows(std::string_view sql, const Catalog& catalog) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind query; translate binding diagnostic. |
| inputs / outputs | SQL+Catalog → SqlRowsProgram. |
| invariants | BindingDiagnostic becomes Error preserving code/message. |
| ownership | Program owns compiled state. |
| failure | Binding error translated; other exceptions propagate. |
| cost | Normal binder compile/move, outside batch checks. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/sql_rows_runtime.md §Start at the two public boundaries](../../../../sql_rows_runtime.md) |

## B0008

[Lines 41–47](../../../../../tests/unit/sql_rows_batch_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
FreeConnexTree tree_for(const frontend::SqlRowsProgram& program) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build fixture physical tree. |
| inputs / outputs | Program → empty contradiction tree or proven-minimum tree. |
| invariants | Non-contradiction requires proven_minimum and a tree. |
| ownership | Core export/tree are setup values. |
| failure | Oracle failure asserts; exceptions propagate. |
| cost | Core export+planner call per runtime. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/sql_rows_runtime.md §Start at the two public boundaries](../../../../sql_rows_runtime.md) |

## B0010

[Lines 49–53](../../../../../tests/unit/sql_rows_batch_test.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlRowsRuntime create(const frontend::SqlRowsProgram& program, bool indexed,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create runtime with selected backend fixture. |
| inputs / outputs | Program/backend/options → runtime. |
| invariants | Indexed uses s04_runtime::options; ordered uses default PhysicalOptions. |
| ownership | Runtime owns its state/account links. |
| failure | Construction errors propagate. |
| cost | Plan/runtime setup outside allocation sweep. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [docs/sql_rows_runtime.md §Physical replacement and constraints](../../../../sql_rows_runtime.md) |

## B0012

[Lines 55–62](../../../../../tests/unit/sql_rows_batch_test.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Bag drain(SqlRowsRuntime::ResultCursor& cursor) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy cursor to independent result Bag. |
| inputs / outputs | Cursor → map of exported rows/weights. |
| invariants | Duplicate output keys assert rather than merge. |
| ownership | Map owns copies after cursor ends. |
| failure | Cursor/allocation errors propagate; duplicate asserts. |
| cost | Full drain+test-map allocation; not production cost. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/sql_rows_runtime.md §Representation and SQL semantics](../../../../sql_rows_runtime.md) |

## B0014

[Lines 64–66](../../../../../tests/unit/sql_rows_batch_test.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Bag results(const SqlRowsRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read public result bag. |
| inputs / outputs | Runtime → copied Bag via cursor/drain. |
| invariants | Uses public result stream, not private indexes. |
| ownership | Map owns copies; cursor local. |
| failure | Cursor/allocation errors propagate. |
| cost | Creates and drains cursor per call. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/sql_rows_runtime.md §Start at the two public boundaries](../../../../sql_rows_runtime.md) |

## B0016

[Lines 68–72](../../../../../tests/unit/sql_rows_batch_test.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void error(Action action, std::string_view expected) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require exact public Error code. |
| inputs / outputs | Action+expected code → assertion. |
| invariants | Catches only Error; wrong/missing code fails. |
| ownership | Captures borrow through check. |
| failure | Expected error caught; other errors propagate; missing/wrong asserts. |
| cost | One action; exception allocations unmeasured. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/sql_rows_runtime.md §Ownership, costs and failure boundaries](../../../../sql_rows_runtime.md) |

## B0018

[Lines 74–77](../../../../../tests/unit/sql_rows_batch_test.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
sql_rows::SourceReplacement edit(std::size_t source, const Cells& row,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make borrowed full-row SourceReplacement. |
| inputs / outputs | Source,row,before/after → TableId+span. |
| invariants | Weights are chain links; row is borrowed. |
| ownership | No row/string copy; caller data survives prepare. |
| failure | No validation here; runtime reports failures. |
| cost | Fixed descriptor/span. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/sql_rows_batches.md §Expected chains and final constraints](../../../../sql_rows_batches.md) |

## B0020

[Lines 79–83](../../../../../tests/unit/sql_rows_batch_test.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<std::size_t N> SqlRowsRuntime::PreparedBatch prepare_at(SqlRowsRuntime& runtime,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare array at explicit sequence. |
| inputs / outputs | Runtime/sequence/edits/capture → token/error. |
| invariants | Public prepare_batch does sequence/source/resource/final checks. |
| ownership | Inputs borrow through call; token owns pending state. |
| failure | Errors propagate; active token closes by commit/rollback/destruction. |
| cost | Span wrapper plus runtime work. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/sql_rows_batches.md §Usage and visibility](../../../../sql_rows_batches.md) |

## B0022

[Lines 85–89](../../../../../tests/unit/sql_rows_batch_test.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<std::size_t N> SqlRowsRuntime::PreparedBatch prepare(SqlRowsRuntime& runtime,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare at next sequence. |
| inputs / outputs | Runtime/edits/capture → token. |
| invariants | Reads sequence+1 then delegates; busy tests call prepare_at. |
| ownership | Input ends at return; token owns state. |
| failure | Busy/sequence/validation/work/native errors propagate. |
| cost | Sequence read plus batch work. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/sql_rows_batches.md §Usage and visibility](../../../../sql_rows_batches.md), [docs/sql_rows_batches.md §Actual cost and scope](../../../../sql_rows_batches.md) |

## B0024

[Lines 91–94](../../../../../tests/unit/sql_rows_batch_test.cpp#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
sql_rows::Epoch replace(SqlRowsRuntime& runtime, std::size_t source, const Cells& row,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply single-row replacement for baseline. |
| inputs / outputs | Runtime/source/row/weights → Epoch. |
| invariants | Uses public apply at next sequence. |
| ownership | Row borrowed synchronously; Epoch owns delta. |
| failure | Single-row errors propagate. |
| cost | One apply; backend/aliases affect work. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/sql_rows_runtime.md §Physical replacement and constraints](../../../../sql_rows_runtime.md), [docs/weighted_deltas.md §Calling contract](../../../../weighted_deltas.md) |

## B0026

[Lines 96–107](../../../../../tests/unit/sql_rows_batch_test.cpp#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CoreDelta read_core_delta(std::span<const weighted::BagDelta> entries,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy native entries into signed core map. |
| inputs / outputs | BagDelta span/optional owner → CoreDelta. |
| invariants | Magnitude present, rows unique; owner via tuple layout stats. |
| ownership | Span used only during copy; map owns facts. |
| failure | Invalid entries assert; conversion/allocation errors propagate. |
| cost | Exports rows/builds map; oracle only. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/weighted_deltas.md §Calling contract](../../../../weighted_deltas.md) |

## B0028

[Lines 109–114](../../../../../tests/unit/sql_rows_batch_test.cpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CoreDelta preview_core_delta(const SqlRowsRuntime::PreparedBatch& batch,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy enabled preview while token is active. |
| inputs / outputs | Token+owner → CoreDelta. |
| invariants | Preview engaged; no borrowed span escapes close. |
| ownership | Preview borrows token; map owns copy. |
| failure | Missing capture asserts; invalid access propagates. |
| cost | Core copy, no SQL wrapper conversion. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/sql_rows_batches.md §Native staging and publication](../../../../sql_rows_batches.md), [docs/weighted_deltas.md §Calling contract](../../../../weighted_deltas.md) |

## B0030

[Lines 116–120](../../../../../tests/unit/sql_rows_batch_test.cpp#L116); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void assert_committed_core_delta(const sql_rows::Epoch& epoch, const CoreDelta& expected,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare committed Epoch native delta. |
| inputs / outputs | Epoch+expected map+owner → assertion. |
| invariants | Requires engaged capture and checks tuple/owner facts. |
| ownership | Epoch retained during read; map test-owned. |
| failure | Missing/mismatch asserts; conversion errors propagate. |
| cost | Copies/compares; Epoch/account owns payload. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/weighted_deltas.md §Calling contract](../../../../weighted_deltas.md) |

## B0032

[Lines 122–124](../../../../../tests/unit/sql_rows_batch_test.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog nonnull_rows_schema() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build common \`(x,s)\` source schema. |
| inputs / outputs | None → owning Catalog. |
| invariants | Column order/types/nullability match row helpers and source 0. |
| ownership | Catalog owns descriptors. |
| failure | Setup allocations propagate. |
| cost | Two-column fixture. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/sql_rows_runtime.md §Representation and SQL semantics](../../../../sql_rows_runtime.md) |

## B0034

[Lines 126–131](../../../../../tests/unit/sql_rows_batch_test.cpp#L126); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog unique_schema() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build enforced UNIQUE(u) schema. |
| inputs / outputs | None → Catalog with id/u, key ColumnId{1}. |
| invariants | Row order \`(id,u)\`; constraint points to u. |
| ownership | Catalog owns descriptor. |
| failure | Setup errors propagate; later validation is normal runtime path. |
| cost | One table+constraint. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/sql_rows_runtime.md §Physical replacement and constraints](../../../../sql_rows_runtime.md) |

## B0036

[Lines 133–175](../../../../../tests/unit/sql_rows_batch_test.cpp#L133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void exact_chains_noops_and_cancellation(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Chain authentication, final-only source cap, no-op handling, committed sequence and empty native delta behavior. |
| inputs / outputs | One \`r(x,s)\` source, query \`SELECT x FROM r\`, native tuple cap 3. Action: Submit duplicate full-row chain \`0→5→5→2\`, then source no-ops, a zero-length batch, and canceling chains on an existing and absent row. |
| invariants | Compare source weights and final cursor bag \`{7:2}\`; inspect the single captured core change \`+2\`, then engaged empty captures for unchanged epochs. Check \`changed\` independently from sequence advancement. |
| ownership | The intermediate 5 remains only a chain endpoint; it must not allocate native tuple state. Empty edits still commit their contiguous logical sequence. |
| failure | The first chain proves an intermediate weight above 3 is not staged; the separate stale-chain card verifies failure rollback. |
| cost | Cap 3, four small commits and explicit maps; no timing/allocation bound. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/sql_rows_batches.md §Expected chains and final constraints](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md §Physical replacement and constraints](../../../../sql_rows_runtime.md) |

## B0038

[Lines 177–194](../../../../../tests/unit/sql_rows_batch_test.cpp#L177); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void wrong_chain_rolls_back_and_reuses_sequence(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expected-before authentication and disabled capture opt-out. |
| inputs / outputs | Empty source ledger, cap 3, one physical row. Action: Submit \`0→5\` followed by stale \`4→2\`; then retry \`0→2\` with capture disabled. |
| invariants | Verify empty SQL bag and unchanged source/root/sequence after rejection; verify final bag \`{7:2}\` after retry. |
| ownership | Failed preparation must destroy its pending native token before returning; no borrowed row data survives the call. |
| failure | Expect \`sql_rows_weight_mismatch\`; the retry commits at sequence 1. Disabled \`native_bag_delta_preview()\` and pending \`Epoch::bag_deltas\` must both be empty/null. |
| cost | One stale and one valid batch. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/sql_rows_batches.md §Expected chains and final constraints](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md §Physical replacement and constraints](../../../../sql_rows_runtime.md) |

## B0040

[Lines 196–228](../../../../../tests/unit/sql_rows_batch_test.cpp#L196); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void final_unique_swap_and_violations(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Final-state UNIQUE validation and decreases-before-increases. |
| inputs / outputs | One table with enforced UNIQUE \`u\`; two committed distinct rows. Action: Add both replacement rows before deleting both old rows in the borrowed list. Follow with a duplicate-key insert and weight-2 update. |
| invariants | Check all four signed native core facts for the accepted swap, final source weights, and explicit cursor bag containing the two swapped rows. |
| ownership | Private key counters may see the complete proposed state; only final key counts are published. No source/key update is visible after either failed prepare. |
| failure | Duplicate new key and a non-null UNIQUE row with weight 2 reject; committed state and sequence stay at the swap result. |
| cost | Two baselines, four-link swap, two invalid proposals; no key comparison count. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/sql_rows_batches.md §Expected chains and final constraints](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md §Physical replacement and constraints](../../../../sql_rows_runtime.md) |

## B0042

[Lines 230–269](../../../../../tests/unit/sql_rows_batch_test.cpp#L230); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void foreign_key_final_order_and_untouched_child(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | FK parent/child ordering, reverse presence counters, and untouched child enforcement. |
| inputs / outputs | Enforced unique parent ID and nullable child FK with a hidden non-null label, allowing distinct full child rows to share one FK value. Action: Create parent plus two children in reverse input order; grow one child weight \`1→100\`; try deleting parent and that child while its sibling remains; then remove parent and both children together. A second trace uses the existing one-row apply API to install an untouched child, reject parent deletion, and retry with the child included. |
| invariants | Explicit result bags have multiplicities 2, then 101, then empty; source weights record the distinct child shares and final removal. |
| ownership | FK reverse shares count presence of each distinct full child row; weight changes do not create extra shares. All final key proposals precede validation. |
| failure | Parent removal with a remaining committed child rejects as \`foreign_key_violation\` and leaves sequence/source/output intact. |
| cost | Small parent/child fixture, weights through 100; not benchmark. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/sql_rows_batches.md §Expected chains and final constraints](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md §Physical replacement and constraints](../../../../sql_rows_runtime.md) |

## B0044

[Lines 271–320](../../../../../tests/unit/sql_rows_batch_test.cpp#L271); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void self_reference_and_two_table_cycles(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Final-view validation for self references, cross-table cycles, unused source tables, and missing final parents. |
| inputs / outputs | A self-FK node table and two mutually referencing unique-key tables; compile the query over \`a\` while retaining catalog source \`b\`. Action: Insert/delete a self-loop; create and delete a two-row cycle with the child edit first; update only unused \`b\`; submit an invalid one-sided \`a\` row. |
| invariants | Compare source weights and explicit \`id\` result bags. For the unused source, assert \`changed=true\`, native inputs zero, and an empty captured core delta. |
| ownership | Touched parent/child counters are resolved against the same private final view, independent of edit order. Unused sources still own ledger state but cause no native adapter work. |
| failure | The missing final parent rejects without advancing the sequence; cyclic and self-referential final states are accepted. |
| cost | Two tiny catalogs and bounded edits; no graph complexity claim. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/sql_rows_batches.md §Expected chains and final constraints](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md §Physical replacement and constraints](../../../../sql_rows_runtime.md) |

## B0046

[Lines 322–383](../../../../../tests/unit/sql_rows_batch_test.cpp#L322); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void nullable_composite_keys_and_empty_keys(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Ordered composite FK projections, NULLS DISTINCT, MATCH SIMPLE, and present empty keys. |
| inputs / outputs | A \`(flag,a)\` UNIQUE target, child physical order \`(a,flag)\` with reordered FK mapping, plus empty-key parent/child constraints over nullable non-key columns. Action: Insert a valid reordered composite key, two target rows whose composite keys contain NULL, and child rows with NULL in each FK position. Then test duplicate non-NULL UNIQUE, absent empty-key parent, a second zero-column-constraint parent, parent weight 2, untouched child on parent removal, and final removal of parent/all children. |
| invariants | Compare nullable SQL rows including bool/int order, source weights, and constant-select bag multiplicities 1 then 2 then empty. |
| ownership | NULL-containing composite keys are omitted from UNIQUE/FK maps under the existing policies; empty lists are present keys. Nullable non-key columns remain part of full-row identity. |
| failure | Expect UNIQUE for repeated non-null and weight-2 empty keys; expect FK when empty-key parent is absent or still has children. |
| cost | Small nullable composite/empty-key fixtures, not exhaustive generation. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/sql_rows_batches.md §Expected chains and final constraints](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md §Physical replacement and constraints](../../../../sql_rows_runtime.md) |

## B0048

[Lines 385–404](../../../../../tests/unit/sql_rows_batch_test.cpp#L385); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cap_safe_decrease_before_increase(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prevent false native overflow from caller-order increases when the final projected tuple remains within cap. |
| inputs / outputs | \`SELECT x FROM r\`, native tuple cap 3, old hidden row weight 2. Action: Input the new hidden row \`0→3\` before old row \`2→0\`. |
| invariants | Require native preview root \`2→3\`, captured core delta \`+1\`, old source weight 0, new source weight 3, and final bag \`{7:3}\`. |
| ownership | The token stages all aliases of decreases first, then increases; no extra result mirror is involved. |
| failure | No rejection is expected; this is the final-valid counterexample to naive input-order staging. |
| cost | Two rows at cap 3; no timing/allocation measurement. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/sql_rows_batches.md §Native staging and publication](../../../../sql_rows_batches.md), [docs/weighted_deltas.md §Arithmetic, failure and ownership](../../../../weighted_deltas.md) |

## B0050

[Lines 406–420](../../../../../tests/unit/sql_rows_batch_test.cpp#L406); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void unsigned_delta_magnitude(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve unsigned native delta magnitude beyond signed 64-bit. |
| inputs / outputs | Simple projected bag row with default uint64 multiplicity policy. Action: Insert one row at \`(1ULL&lt;&lt;63)+17\` under enabled capture. |
| invariants | Compare source weight, root weight, SQL bag and exact positive core delta magnitude to that uint64 value. |
| ownership | The preview is copied while active; committed \`AccountedTuple\` is checked against the receiving account. |
| failure | No failure expected; arithmetic remains within UINT64_MAX. |
| cost | One row at large logical uint64 weight, not large payload bytes. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/weighted_deltas.md §Calling contract](../../../../weighted_deltas.md), [docs/weighted_deltas.md §Arithmetic, failure and ownership](../../../../weighted_deltas.md) |

## B0052

[Lines 422–447](../../../../../tests/unit/sql_rows_batch_test.cpp#L422); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void filtered_and_contradictory_sources(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Separate physical source change from native output change. |
| inputs / outputs | A two-alias self-join whose predicates reject the changed row, plus a binder contradiction (\`x = NULL\`). Action: Prepare and commit source rows through the all-filtered plan and the contradiction plan with capture enabled. |
| invariants | For each, assert changed source weight and sequence but zero native inputs, empty core preview, \`native.changed=false\`, and empty SQL bag. |
| ownership | Full physical rows remain in the source ledger even if every alias filters them; no native bag facts means an engaged empty span under enabled capture. |
| failure | No failure expected; this confirms no-native preparation remains commit-capable. |
| cost | One edit per plan; source/native/output distinctions only. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/sql_rows_batches.md §Native staging and publication](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md §Physical replacement and constraints](../../../../sql_rows_runtime.md) |

## B0054

[Lines 449–499](../../../../../tests/unit/sql_rows_batch_test.cpp#L449); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void aliases_single_native_epoch_and_delta_wrappers(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Every self-join alias stages in one native epoch; native preview is encoded core, not SQL wrapper output. |
| inputs / outputs | Self-join with two full rows sharing selected \`x\`; also DISTINCT and EXISTS programs over the same source schema. Action: Change both rows in one batch, with an increase first in input; separately insert rows into DISTINCT and EXISTS. |
| invariants | Check native inputs = four and root \`25→36\` with core delta \`+11\`; compare final SQL bag \`{7:36}\`. For DISTINCT compare native \`+5\` to SQL output \`{7:1}\`. For EXISTS compare empty-tuple native \`+3\` to SQL Boolean output \`{TRUE:1}\` (initially \`{FALSE:1}\`). |
| ownership | Preview spans are read before commit; committed entries are checked under the receiving account. SQL wrapper differences are intentional and never inferred from native counts. |
| failure | No failure expected; all token stages use one sequence. |
| cost | Few rows, three query forms; no scaling bound. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/sql_rows_batches.md §Native staging and publication](../../../../sql_rows_batches.md), [docs/weighted_deltas.md §Calling contract](../../../../weighted_deltas.md) |

## B0056

[Lines 501–541](../../../../../tests/unit/sql_rows_batch_test.cpp#L501); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void one_source_allowance_and_retry(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | One logical source-work allowance spans all edits and aliases. |
| inputs / outputs | Two-alias join with two source rows; measure a full batch and a single-row batch through public \`source_work()\`. Action: Admit the full batch at its measured work limit; reject at one structural step less; retry a single-row batch under that smaller limit. |
| invariants | Compare spent counters before/after commit and explicit output bags \`{7:25}\` for full batch, \`{7:4}\` for the retry. |
| ownership | \`source_work()\` returns a value. The test does not infer wall-clock bounds or charge every map comparison. |
| failure | One-under must throw \`storage_work_limit\`, preserve ready/sequence/source/root/output, and allow same-sequence retry. |
| cost | Five selected work counters, not wall-time/map-comparison/all-instruction bound. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/sql_rows_batches.md §Actual cost and scope](../../../../sql_rows_batches.md) |

## B0058

[Lines 543–559](../../../../../tests/unit/sql_rows_batch_test.cpp#L543); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void native_overflow_rolls_back_then_retries(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Failure during final native arithmetic must leave source, keys, native root, and committed sequence unchanged. |
| inputs / outputs | One source row feeds both aliases of a self-join; initial weight 2. Action: Try replacement to UINT64_MAX, then retry to weight 3. |
| invariants | Before failure and after retry, compare root and explicit SQL bags (\`{7:4}\` then \`{7:9}\`) plus source weight. |
| ownership | Native RAII undo is the only query inverse; SQL source/key proposals are unpublished on throw. |
| failure | Expect \`annotation_overflow\`; assert token was not published, sequence remains 1, ready returns true, and retry commits at 2. |
| cost | One overflow and one valid retry; not throughput. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/sql_rows_batches.md §Native staging and publication](../../../../sql_rows_batches.md), [docs/weighted_deltas.md §Arithmetic, failure and ownership](../../../../weighted_deltas.md) |

## B0060

[Lines 561–597](../../../../../tests/unit/sql_rows_batch_test.cpp#L561); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void preparation_allocation_cuts_rollback_and_retry(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Covered C++ allocation failures at each observed preparation allocation for one two-alias string-row replacement. |
| inputs / outputs | \`index_allocation.hpp\` single-TU \`s04_alloc::Scope\`; committed old string row and a new string row on the same join key. Action: Count allocations in a successful prepared token, then repeat with a failure at every measured \`operator new\` position per backend. |
| invariants | Each failed attempt retains old row output \`{old:4}\`; retry commits both output rows \`{old:10,new:15}\` and source weights 2/3. |
| ownership | The sweep observes covered C++ \`new\` only; it does not claim coverage of libc allocation or all allocation shapes. New string payload and alias staging are exercised. |
| failure | Require both caught \`bad_alloc\` and the fixture's \`triggered\` flag. Each failure must restore ready state and same sequence. |
| cost | Every observed new position for one two-alias string-row shape per backend; not exhaustive/no-heap proof. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_rows_batches.md §Actual cost and scope](../../../../sql_rows_batches.md) |

## B0062

[Lines 599–636](../../../../../tests/unit/sql_rows_batch_test.cpp#L599); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void close_releases_prepared_workspace_without_new(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check commit/rollback close without covered C++ allocation and release workspace before destruction of the closed handle. |
| inputs / outputs | Measure account bytes resident and active; close under zero-budget new denial; reset returned Epoch before closed sample; compare after destroying closed PreparedBatch. |
| invariants | Both paths make zero covered new calls; state matches; closed bytes lower than active; handle destruction frees no further requested bytes. |
| ownership | Closed token stays alive during sample, runtime remains alive, and returned Epoch is reset first; account bytes are not RSS. |
| failure | Any covered allocation or incorrect state/count fails an assertion; results checked after close. |
| cost | C++ new denial differs from account bytes; neither measures RSS/libc/syscalls. Epoch reset before sample. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_rows_batches.md §Usage and visibility](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md §Ownership, costs and failure boundaries](../../../../sql_rows_runtime.md) |

## B0064

[Lines 638–711](../../../../../tests/unit/sql_rows_batch_test.cpp#L638); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void prepared_owner_busy_abandonment_and_move_assignment(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Active/closed token diagnostics, caller-span lifetime, facade move/destruction, abandoned-token rollback, and cross-owner move assignment. |
| inputs / outputs | Public runtime and memory-account constructors; long string cell; two separately created SQL owners for move-assignment control. Action: Prepare in a scope where cell/string storage dies; query allowed immutable diagnostics and all busy facade operations; move/destroy facade, then commit detached token. Move-assign tokens from different accounts, rollback twice, and destroy one final active token. |
| invariants | Copied text/core survives input/facade teardown; busy calls report runtime_busy; closed access reports invalid_sql_rows_batch; cross-owner assignment rolls back old owner; abandonment preserves state. |
| ownership | Cells/string expire after prepare; token owns frozen state/account link; preview copied while active; Epoch owns output; token outlives moved/destroyed facade. |
| failure | Exact runtime_busy/invalid_sql_rows_batch codes; destruction and repeated rollback harmless. |
| cost | Two owners and one 300-byte string; fixed control/deleter references may remain. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/sql_rows_batches.md §Usage and visibility](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md §Ownership, costs and failure boundaries](../../../../sql_rows_runtime.md), [docs/weighted_deltas.md §Calling contract](../../../../weighted_deltas.md) |

## B0065

[Lines 712–714](../../../../../tests/unit/sql_rows_batch_test.cpp#L712); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L712-L714:sha256:ca577cbc6a8d67316fef9a0d7f55d33179b8f6889d41ade799bac8ac78469ed5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in sql_rows_batch_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/code_review.md](../../../../code_review.md) |

## B0066

[Lines 715–736](../../../../../tests/unit/sql_rows_batch_test.cpp#L715); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run all 15 cases on ordered/indexed backends and report failures to CTest. |
| inputs / outputs | No args; invokes each case with false/true; prints success and returns 0 or prints std::exception and returns 1. |
| invariants | Both backends share explicit bag/core checks; errors cannot be skipped. |
| ownership | Fixtures/tokens/cursors/epochs remain case-local. |
| failure | Assertion abort is nonzero; caught exception returns 1. |
| cost | Fixed cases twice; no benchmark/full-suite claim. |
| Design | [tests/unit/sql_rows_batch_test.cpp](../../../../../tests/unit/sql_rows_batch_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/sql_rows_batches.md §Actual cost and scope](../../../../sql_rows_batches.md) |
