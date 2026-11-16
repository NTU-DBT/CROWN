# `tests/unit/delta_live_test.cpp` — block usage map

[Source](../../../../../tests/unit/delta_live_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `6964e4829bb5173c3161b65f0982a8af86ef1bc4b35cade0bbbfe4a6eb3d6117`. 700 lines partitioned into 81 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–22](../../../../../tests/unit/delta_live_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 23–25](../../../../../tests/unit/delta_live_test.cpp#L23) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 26–26](../../../../../tests/unit/delta_live_test.cpp#L26) | Explanatory comments or spacing. |  |
| [B0004 · 27–27](../../../../../tests/unit/delta_live_test.cpp#L27) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0004) |
| [B0005 · 28–28](../../../../../tests/unit/delta_live_test.cpp#L28) | Explanatory comments or spacing. |  |
| [B0006 · 29–33](../../../../../tests/unit/delta_live_test.cpp#L29) | Callable definition: VariableSet variables(std::initializer_list&lt;std::size_t&gt; values) | calls insert; returns result; growth insert; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 34–34](../../../../../tests/unit/delta_live_test.cpp#L34) | Explanatory comments or spacing. |  |
| [B0008 · 35–41](../../../../../tests/unit/delta_live_test.cpp#L35) | Callable definition: DeltaOptions options(LiveMaintenance maintenance) | calls ; returns result · [reviewed contract](#b0008) |
| [B0009 · 42–42](../../../../../tests/unit/delta_live_test.cpp#L42) | Explanatory comments or spacing. |  |
| [B0010 · 43–45](../../../../../tests/unit/delta_live_test.cpp#L43) | Callable definition: Relation a04(const auto& plan, const Database& database) | calls reference::evaluate, reference::input::catalog, catalog, reference::input::query; returns reference::evaluate(reference::input::catalog(plan.catalog()), reference::input::query(plan.query()… · [reviewed contract](#b0010) |
| [B0011 · 46–46](../../../../../tests/unit/delta_live_test.cpp#L46) | Explanatory comments or spacing. |  |
| [B0012 · 47–54](../../../../../tests/unit/delta_live_test.cpp#L47) | Callable definition: std::set&lt;SignedKey&gt; difference(const Relation& before, const Relation& after) | calls contains, emplace; returns result; growth emplace, insert; 2 loop sites · [reviewed contract](#b0012) |
| [B0013 · 55–55](../../../../../tests/unit/delta_live_test.cpp#L55) | Explanatory comments or spacing. |  |
| [B0014 · 56–66](../../../../../tests/unit/delta_live_test.cpp#L56) | Callable definition: std::set&lt;SignedKey&gt; drain(DeltaRuntime::Epoch& epoch) | calls next, check, emplace, crown::storage::export_row; guard check(rows.emplace(record-&gt;operation, crown::storage::export_row(record-&gt;tuple.values())).second,; returns rows; growth emplace; 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 67–67](../../../../../tests/unit/delta_live_test.cpp#L67) | Explanatory comments or spacing. |  |
| [B0016 · 68–93](../../../../../tests/unit/delta_live_test.cpp#L68) | Callable definition: std::vector&lt;Relation&gt; a04_live(const auto& plan, const Relation& answer) | calls query, size, try_emplace, reserve; guard check(position != head_positions.end(),; returns result; growth insert, push_back, reserve; 4 loop sites · [reviewed contract](#b0016) |
| [B0017 · 94–94](../../../../../tests/unit/delta_live_test.cpp#L94) | Explanatory comments or spacing. |  |
| [B0018 · 95–99](../../../../../tests/unit/delta_live_test.cpp#L95) | Callable definition: std::size_t rows(const std::vector&lt;Relation&gt;& factors) | calls size; returns result; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 100–100](../../../../../tests/unit/delta_live_test.cpp#L100) | Explanatory comments or spacing. |  |
| [B0020 · 101–110](../../../../../tests/unit/delta_live_test.cpp#L101) | Callable definition: void check_live(const DeltaRuntime& runtime, const Database& database, const std::string& label) | calls live_snapshot, check, has_value, sequence; guard check(snapshot.has_value(), label + ": delta mode has no live snapshot"); · [reviewed contract](#b0020) |
| [B0021 · 111–111](../../../../../tests/unit/delta_live_test.cpp#L111) | Explanatory comments or spacing. |  |
| [B0022 · 112–129](../../../../../tests/unit/delta_live_test.cpp#L112) | Callable definition: void check_stage_signatures(const std::vector&lt;DeltaStage&gt;& left, const std::vector&lt;DeltaStage&gt;& right, const std::string& label) | calls check, size, std::to_string; guard check(left.size() == right.size(), label + ": route stage count differs");; 1 loop sites · [reviewed contract](#b0022) |
| [B0023 · 130–130](../../../../../tests/unit/delta_live_test.cpp#L130) | Explanatory comments or spacing. |  |
| [B0024 · 131–147](../../../../../tests/unit/delta_live_test.cpp#L131) | Callable definition: void check_on_output_metrics(const DeltaMetrics& incremental, const DeltaMetrics& on_output, const std::string& label) | calls check; guard check(on_output.live_bucket_opens == 0 && on_output.live_bucket_rows == 0, · [reviewed contract](#b0024) |
| [B0025 · 148–148](../../../../../tests/unit/delta_live_test.cpp#L148) | Explanatory comments or spacing. |  |
| [B0026 · 149–161](../../../../../tests/unit/delta_live_test.cpp#L149) | Callable definition: PhysicalPlan root_child_plan() | calls variables, planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0026) |
| [B0027 · 162–162](../../../../../tests/unit/delta_live_test.cpp#L162) | Explanatory comments or spacing. |  |
| [B0028 · 163–176](../../../../../tests/unit/delta_live_test.cpp#L163) | Callable definition: PhysicalPlan shared_separator_plan() | calls variables, planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0028) |
| [B0029 · 177–177](../../../../../tests/unit/delta_live_test.cpp#L177) | Explanatory comments or spacing. |  |
| [B0030 · 178–199](../../../../../tests/unit/delta_live_test.cpp#L178) | Callable definition: PhysicalPlan deep_chain_plan() | calls variables, planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0030) |
| [B0031 · 200–200](../../../../../tests/unit/delta_live_test.cpp#L200) | Explanatory comments or spacing. |  |
| [B0032 · 201–223](../../../../../tests/unit/delta_live_test.cpp#L201) | Callable definition: PhysicalPlan delayed_child_cleanup_plan() | calls variables, planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0032) |
| [B0033 · 224–224](../../../../../tests/unit/delta_live_test.cpp#L224) | Explanatory comments or spacing. |  |
| [B0034 · 225–238](../../../../../tests/unit/delta_live_test.cpp#L225) | Callable definition: PhysicalPlan coalesced_plan() | calls variables, planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0034) |
| [B0035 · 239–239](../../../../../tests/unit/delta_live_test.cpp#L239) | Explanatory comments or spacing. |  |
| [B0036 · 240–260](../../../../../tests/unit/delta_live_test.cpp#L240) | Callable definition: PhysicalPlan product_plan(std::size_t arity) | calls push_back, std::to_string, variables, planner::lower_tree; returns planner::lower_tree(catalog, query, tree); growth push_back; 2 loop sites · [reviewed contract](#b0036) |
| [B0037 · 261–261](../../../../../tests/unit/delta_live_test.cpp#L261) | Explanatory comments or spacing. |  |
| [B0038 · 262–274](../../../../../tests/unit/delta_live_test.cpp#L262) | Callable definition: PhysicalPlan same_scope_alias_plan() | calls variables, planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0038) |
| [B0039 · 275–275](../../../../../tests/unit/delta_live_test.cpp#L275) | Explanatory comments or spacing. |  |
| [B0040 · 276–283](../../../../../tests/unit/delta_live_test.cpp#L276) | Type/record definition: struct EpochPairResult |  · [reviewed contract](#b0040) |
| [B0041 · 284–285](../../../../../tests/unit/delta_live_test.cpp#L284) | declares types or opens a type body. |  · [reviewed contract](#b0041) |
| [B0042 · 286–293](../../../../../tests/unit/delta_live_test.cpp#L286) | Callable definition: public: RuntimePair(PhysicalPlan incremental_plan, PhysicalPlan eager_plan, PhysicalPlan on_output_plan, std::size_t table_count)… | calls incremental_, std::move, options, eager_; growth resize · [reviewed contract](#b0042) |
| [B0043 · 294–294](../../../../../tests/unit/delta_live_test.cpp#L294) | Explanatory comments or spacing. |  |
| [B0044 · 295–305](../../../../../tests/unit/delta_live_test.cpp#L295) | Callable definition: void seed(TableId table, Row row) | calls apply, check, drain, empty; guard check(drain(incremental_epoch).empty() && drain(eager_epoch).empty() &&; growth insert · [reviewed contract](#b0044) |
| [B0045 · 306–306](../../../../../tests/unit/delta_live_test.cpp#L306) | Explanatory comments or spacing. |  |
| [B0046 · 307–319](../../../../../tests/unit/delta_live_test.cpp#L307) | Callable definition: std::tuple&lt;DeltaMetrics, DeltaMetrics, DeltaMetrics&gt; bootstrap() | calls set_mode, check_live, check, live_snapshot; guard check(incremental_.live_snapshot()-&gt;factors == eager_.live_snapshot()-&gt;factors,; returns {incremental_metrics, eager_metrics, on_output_metrics} · [reviewed contract](#b0046) |
| [B0047 · 320–320](../../../../../tests/unit/delta_live_test.cpp#L320) | Explanatory comments or spacing. |  |
| [B0048 · 321–328](../../../../../tests/unit/delta_live_test.cpp#L321) | Callable definition: void maintenance() | calls set_mode, check, live_snapshot; guard check(!incremental_.live_snapshot() && !eager_.live_snapshot() && · [reviewed contract](#b0048) |
| [B0049 · 329–329](../../../../../tests/unit/delta_live_test.cpp#L329) | Explanatory comments or spacing. |  |
| [B0050 · 330–382](../../../../../tests/unit/delta_live_test.cpp#L330) | Callable definition: EpochPairResult apply(TableId table, SetOperation operation, Row row, const std::string& label) | calls a04, plan, at, insert; guard check(changed, label + ": fixture update did not cross physical set membership");; returns result; growth insert · [reviewed contract](#b0050) |
| [B0051 · 383–383](../../../../../tests/unit/delta_live_test.cpp#L383) | Explanatory comments or spacing. |  |
| [B0052 · 384–384](../../../../../tests/unit/delta_live_test.cpp#L384) | Callable definition: \[\[nodiscard\]\] const Database& database() const | calls ; returns database_ · [reviewed contract](#b0052) |
| [B0053 · 385–385](../../../../../tests/unit/delta_live_test.cpp#L385) | Callable definition: \[\[nodiscard\]\] const DeltaRuntime& incremental() const | calls ; returns incremental_ · [reviewed contract](#b0053) |
| [B0054 · 386–386](../../../../../tests/unit/delta_live_test.cpp#L386) | Callable definition: \[\[nodiscard\]\] const DeltaRuntime& eager() const | calls ; returns eager_ · [reviewed contract](#b0054) |
| [B0055 · 387–387](../../../../../tests/unit/delta_live_test.cpp#L387) | Callable definition: \[\[nodiscard\]\] const DeltaRuntime& on_output() const | calls ; returns on_output_ · [reviewed contract](#b0055) |
| [B0056 · 388–401](../../../../../tests/unit/delta_live_test.cpp#L388) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0056) |
| [B0057 · 402–407](../../../../../tests/unit/delta_live_test.cpp#L402) | Callable definition: LiveWork live_work(const DeltaMetrics& metrics) | calls ; returns {metrics.live_probes, metrics.live_changes, metrics.live_inserts, · [reviewed contract](#b0057) |
| [B0058 · 408–408](../../../../../tests/unit/delta_live_test.cpp#L408) | Explanatory comments or spacing. |  |
| [B0059 · 409–437](../../../../../tests/unit/delta_live_test.cpp#L409) | Callable definition: DeltaMetrics empty_delta_work(std::size_t dead_rows) | calls pair, root_child_plan, seed, n; guard check(incremental_bootstrap.e_rows_scanned == dead_rows &&; returns empty.incremental; growth insert; 1 loop sites · [reviewed contract](#b0059) |
| [B0060 · 438–438](../../../../../tests/unit/delta_live_test.cpp#L438) | Explanatory comments or spacing. |  |
| [B0061 · 439–450](../../../../../tests/unit/delta_live_test.cpp#L439) | Callable definition: void unrelated_e_growth_is_not_scanned() | calls empty_delta_work, check, live_work; guard check(live_work(small) == live_work(large), · [reviewed contract](#b0061) |
| [B0062 · 451–451](../../../../../tests/unit/delta_live_test.cpp#L451) | Explanatory comments or spacing. |  |
| [B0063 · 452–470](../../../../../tests/unit/delta_live_test.cpp#L452) | Callable definition: void unchanged_e_becomes_live_and_unlive() | calls pair, root_child_plan, seed, n; guard check(activated.incremental.live_bucket_rows == 1 &&; growth insert · [reviewed contract](#b0063) |
| [B0064 · 471–471](../../../../../tests/unit/delta_live_test.cpp#L471) | Explanatory comments or spacing. |  |
| [B0065 · 472–497](../../../../../tests/unit/delta_live_test.cpp#L472) | Callable definition: void shared_separator_count_crossings() | calls pair, shared_separator_plan, seed, n; guard check(one_parent.incremental.live_separator_updates == 1 && · [reviewed contract](#b0065) |
| [B0066 · 498–498](../../../../../tests/unit/delta_live_test.cpp#L498) | Explanatory comments or spacing. |  |
| [B0067 · 499–527](../../../../../tests/unit/delta_live_test.cpp#L499) | Callable definition: DeltaMetrics anchored_child_insertion_work(std::size_t root_rows) | calls pair, shared_separator_plan, n, seed; guard check(result.on_output.changed_keys == 1 && result.on_output.accepted == 1,; returns result.on_output; growth insert; 1 loop sites · [reviewed contract](#b0067) |
| [B0068 · 528–528](../../../../../tests/unit/delta_live_test.cpp#L528) | Explanatory comments or spacing. |  |
| [B0069 · 529–542](../../../../../tests/unit/delta_live_test.cpp#L529) | Callable definition: void anchored_completion_avoids_unrelated_root_scan() | calls anchored_child_insertion_work, check, live_work; guard check(live_work(one_root_row) == live_work(many_root_rows), · [reviewed contract](#b0069) |
| [B0070 · 543–543](../../../../../tests/unit/delta_live_test.cpp#L543) | Explanatory comments or spacing. |  |
| [B0071 · 544–561](../../../../../tests/unit/delta_live_test.cpp#L544) | Callable definition: void deep_descendant_cascade() | calls pair, deep_chain_plan, seed, n; guard check(activation.incremental.live_inserts == 4 &&; growth insert · [reviewed contract](#b0071) |
| [B0072 · 562–562](../../../../../tests/unit/delta_live_test.cpp#L562) | Explanatory comments or spacing. |  |
| [B0073 · 563–602](../../../../../tests/unit/delta_live_test.cpp#L563) | Callable definition: void shared_separator_later_completion_cleans_child() | calls pair, delayed_child_cleanup_plan, seed, n; guard check(deleted.incremental.accepted == 8 &&; growth insert · [reviewed contract](#b0073) |
| [B0074 · 603–603](../../../../../tests/unit/delta_live_test.cpp#L603) | Explanatory comments or spacing. |  |
| [B0075 · 604–624](../../../../../tests/unit/delta_live_test.cpp#L604) | Callable definition: void simultaneous_parent_and_child_e_changes_are_idempotent() | calls pair, coalesced_plan, seed, n; guard check(inserted.incremental.changed_keys &gt;= 2,; growth insert · [reviewed contract](#b0075) |
| [B0076 · 625–625](../../../../../tests/unit/delta_live_test.cpp#L625) | Explanatory comments or spacing. |  |
| [B0077 · 626–647](../../../../../tests/unit/delta_live_test.cpp#L626) | Callable definition: void nullary_product_activation() | calls pair, product_plan, seed, n; guard check(first_product.incremental.accepted == 4,; growth insert · [reviewed contract](#b0077) |
| [B0078 · 648–648](../../../../../tests/unit/delta_live_test.cpp#L648) | Explanatory comments or spacing. |  |
| [B0079 · 649–680](../../../../../tests/unit/delta_live_test.cpp#L649) | Callable definition: void aliases_and_mode_rebootstrap() | calls pair, same_scope_alias_plan, seed, n; guard check(alias_insert.incremental_stages.size() == 2 &&; growth insert · [reviewed contract](#b0079) |
| [B0080 · 681–683](../../../../../tests/unit/delta_live_test.cpp#L681) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0080) |
| [B0081 · 684–700](../../../../../tests/unit/delta_live_test.cpp#L684) | Callable definition: int main() | calls unrelated_e_growth_is_not_scanned, unchanged_e_becomes_live_and_unlive, shared_separator_count_crossings, anchored_completion_avoids_unrelated_root_scan; returns 1 · [reviewed contract](#b0081) |

## B0001

[Lines 1–22](../../../../../tests/unit/delta_live_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L22:sha256:1fc612cec09109b90bc983d6097e4d19f2878fe5bc076e9fa813b90cb9c90691
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare delta_live_test.cpp: include "crown/planner/lower.hpp", "crown/runtime/delta.hpp", "evaluator.hpp", "native_input.hpp", &lt;algorithm&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;initializer_list&gt;, &lt;map&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;tuple&gt;, &lt;utility&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp), [docs/incremental_live.md](../../../../incremental_live.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 23–25](../../../../../tests/unit/delta_live_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a live-maintenance test predicate. |
| inputs / outputs | Takes condition and diagnostic string by const reference; returns on true. |
| invariants | Does not catch or translate runtime errors. |
| ownership | String is borrowed for the check. |
| failure | False throws std::runtime_error. |
| cost | One conditional branch. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp) |

## B0004

[Lines 27–27](../../../../../tests/unit/delta_live_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an int64 fixture Value. |
| inputs / outputs | Takes signed integer; returns Value by value. |
| invariants | Preserves the integer. |
| ownership | No external state retained. |
| failure | Variant construction failures propagate. |
| cost | Scalar conversion. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp) |

## B0006

[Lines 29–33](../../../../../tests/unit/delta_live_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
VariableSet variables(std::initializer_list<std::size_t> values) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a VariableSet from zero-based indices. |
| inputs / outputs | Takes initializer list; returns a set of VariableId. |
| invariants | Repeated indices collapse through set insertion. |
| ownership | Returned set owns its IDs. |
| failure | Allocation failures propagate. |
| cost | Inserts each listed index. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp) |

## B0008

[Lines 35–41](../../../../../tests/unit/delta_live_test.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaOptions options(LiveMaintenance maintenance) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure maintenance-first DeltaOptions for one live-maintenance policy. |
| inputs / outputs | Takes LiveMaintenance; returns options by value. |
| invariants | Sets mode=maintenance and completion=anchored; caller-supplied policy selects incremental, eager, or on_output. |
| ownership | Returned options own scalar settings. |
| failure | No custom error handling. |
| cost | Constant-size option construction. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0010

[Lines 43–45](../../../../../tests/unit/delta_live_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation a04(const auto& plan, const Database& database) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize the plan’s independent A04 query answer. |
| inputs / outputs | Takes plan and physical database by const reference; returns Relation. |
| invariants | Uses reference evaluator, not DeltaRuntime’s maintained answer. |
| ownership | Inputs borrowed; returned row set owns values. |
| failure | Evaluator/allocation failures propagate. |
| cost | One finite reference evaluation. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp) |

## B0012

[Lines 47–54](../../../../../tests/unit/delta_live_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::set<SignedKey> difference(const Relation& before, const Relation& after) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute set-valued insert/erase difference between two query answers. |
| inputs / outputs | Takes before/after Relations by const reference; returns SignedKey set. |
| invariants | Rows only after become inserts; rows only before become erases; common rows vanish. |
| ownership | Inputs borrowed; output copies row values. |
| failure | Allocation failures propagate. |
| cost | Scans both finite relations. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp) |

## B0014

[Lines 56–66](../../../../../tests/unit/delta_live_test.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::set<SignedKey> drain(DeltaRuntime::Epoch& epoch) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain one output epoch into a duplicate-free signed row set. |
| inputs / outputs | Takes Epoch by mutable reference; returns owning set of operation/Row pairs. |
| invariants | Exports tuple values before retaining them; requires exhausted epoch to have remaining()==0 and inactive; a later next() is empty. |
| ownership | Epoch borrowed; exported rows copied into result; exhaustion releases this epoch’s output lease. |
| failure | Duplicate output or unreleased epoch is a test failure; runtime errors propagate. |
| cost | Visits every emitted row and inserts it into an ordered set. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0016

[Lines 68–93](../../../../../tests/unit/delta_live_test.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Relation> a04_live(const auto& plan,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project an A04 head answer into each enumeration-step visible E scope. |
| inputs / outputs | Takes plan and answer by const reference; returns factor vector. |
| invariants | Uses first head position for each variable; emits each factor from answer rows and each node visible_scope. |
| ownership | Inputs borrowed; result factors own copied keys. |
| failure | Missing head variable/index or allocation failure propagates. |
| cost | Visits each answer row for each enumeration step. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/incremental_live.md § Maintained state](../../../../incremental_live.md) |

## B0018

[Lines 95–99](../../../../../tests/unit/delta_live_test.cpp#L95); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t rows(const std::vector<Relation>& factors) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sum cardinalities of projected factor relations. |
| inputs / outputs | Takes factors by const reference; returns size_t. |
| invariants | Counts a nullary Row{} as one row if present. |
| ownership | Factors borrowed. |
| failure | No custom failure handling. |
| cost | One pass over factors. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp) |

## B0020

[Lines 101–110](../../../../../tests/unit/delta_live_test.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_live(const DeltaRuntime& runtime, const Database& database,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare runtime live snapshot and invariants with independent A04 projections. |
| inputs / outputs | Takes runtime/database by const reference and label; returns void. |
| invariants | Requires a snapshot at runtime sequence, exact projected factors, and successful check_invariants. |
| ownership | Runtime/database borrowed; expected A04 and factors local. |
| failure | Absent/stale/different snapshot or invariant failure fails the test; evaluator/runtime exceptions propagate. |
| cost | One full finite A04 evaluation and projection plus invariant check. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/incremental_live.md § Maintained state](../../../../incremental_live.md) |

## B0022

[Lines 112–129](../../../../../tests/unit/delta_live_test.cpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_stage_signatures(const std::vector<DeltaStage>& left,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare selected DeltaStage route signatures between policies. |
| inputs / outputs | Takes two stage vectors and label by const reference; returns void. |
| invariants | Requires equality of occurrence, prefix, before/after answers, changed keys, candidate/accepted/rejected counts, output interval and live_rows at every index. |
| ownership | Vectors borrowed. |
| failure | Any size/field mismatch throws std::runtime_error. |
| cost | Linear scan of both stage vectors. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp) |

## B0024

[Lines 131–147](../../../../../tests/unit/delta_live_test.cpp#L131); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_on_output_metrics(const DeltaMetrics& incremental,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that on-output maintenance avoids selected L bucket/rebuild actions and matches selected mutations. |
| inputs / outputs | Takes incremental/on_output metrics and label by const reference; returns void. |
| invariants | Checks on-output bucket opens/rows, E scans and parent rows are zero; live changes/inserts/erases and separator updates/crossings match incremental. It does not compare CPU time or all fields. |
| ownership | Metrics borrowed value objects. |
| failure | Any asserted metric mismatch fails. |
| cost | Constant number of metric comparisons. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp), [docs/incremental_live.md § Cost claim for this component](../../../../incremental_live.md) |

## B0026

[Lines 149–161](../../../../../tests/unit/delta_live_test.cpp#L149); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan root_child_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build root-to-child plan r(x), s(x,y). |
| inputs / outputs | No args; returns lowered PhysicalPlan. |
| invariants | Root separator is x; child E has x,y; head is x,y. |
| ownership | Returned plan owns metadata. |
| failure | Lowering errors propagate. |
| cost | Constructs and lowers one fixed fixture plan. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0028

[Lines 163–176](../../../../../tests/unit/delta_live_test.cpp#L163); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan shared_separator_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a two-node plan with shared separator x and child z. |
| inputs / outputs | No args; returns lowered PhysicalPlan. |
| invariants | Parent exposes a,x and child exposes x,z; x is the live separator. |
| ownership | Returned plan owns metadata. |
| failure | Lowering errors propagate. |
| cost | One fixed plan lowering. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0030

[Lines 178–199](../../../../../tests/unit/delta_live_test.cpp#L178); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan deep_chain_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a four-node chain r(x,y)-s(y,z)-t(z,w)-u(w,q). |
| inputs / outputs | No args; returns lowered PhysicalPlan. |
| invariants | Each next child shares the preceding separator; head carries all five variables. |
| ownership | Returned plan owns metadata. |
| failure | Lowering errors propagate. |
| cost | One fixed chain lowering. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0032

[Lines 201–223](../../../../../tests/unit/delta_live_test.cpp#L201); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan delayed_child_cleanup_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a delayed-cleanup tree with two p parents sharing x and descendants s(x,y), t(y,z). |
| inputs / outputs | No args; returns lowered PhysicalPlan. |
| invariants | Deleting the sole root can enumerate eight completions while descendant L cleanup crosses shared supports. |
| ownership | Returned plan owns metadata. |
| failure | Lowering errors propagate. |
| cost | One fixed plan lowering. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0034

[Lines 225–238](../../../../../tests/unit/delta_live_test.cpp#L225); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan coalesced_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a fixture where one physical update changes both parent and child E membership. |
| inputs / outputs | No args; returns lowered PhysicalPlan. |
| invariants | Parent and child share x; child row also exposes y. |
| ownership | Returned plan owns metadata. |
| failure | Lowering errors propagate. |
| cost | One fixed plan lowering. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0036

[Lines 240–260](../../../../../tests/unit/delta_live_test.cpp#L240); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan product_plan(std::size_t arity) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a nullary generalized root over arity unary native factors. |
| inputs / outputs | Takes arity; returns lowered plan. |
| invariants | Each child has one distinct variable and one physical table; empty-separator root gates the product. |
| ownership | Returned plan owns metadata. |
| failure | Lowering errors propagate. |
| cost | Plan size grows with arity; no query execution. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0038

[Lines 262–274](../../../../../tests/unit/delta_live_test.cpp#L262); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan same_scope_alias_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a same-scope two-occurrence alias plan over one physical table. |
| inputs / outputs | No args; returns lowered PhysicalPlan. |
| invariants | Two native occurrences share visible scope x,y and table identity; route prefix ownership is tested elsewhere. |
| ownership | Returned plan owns metadata. |
| failure | Lowering errors propagate. |
| cost | One fixed plan lowering. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0040

[Lines 276–283](../../../../../tests/unit/delta_live_test.cpp#L276); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct EpochPairResult {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry per-policy event metrics and stage snapshots. |
| inputs / outputs | Aggregate contains incremental/eager/on_output DeltaMetrics and copied stage vectors. |
| invariants | Metrics/stages are captured from their completed epochs to compare policy behavior. |
| ownership | Owns copied metric values and stage records. |
| failure | No custom behavior. |
| cost | Plain result aggregate. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0041

[Lines 284–285](../../../../../tests/unit/delta_live_test.cpp#L284); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L284-L285:sha256:db505c0d8b67cb9337b08b633c3c5d55cf6a2ee399610b342280c74c99e3b4e5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare delta_live_test.cpp: open the test/reference type declaration. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp), [docs/incremental_live.md](../../../../incremental_live.md), [docs/code_review.md](../../../../code_review.md) |

## B0042

[Lines 286–293](../../../../../tests/unit/delta_live_test.cpp#L286); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
 public:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own three runtimes for incremental, eager and on-output live-maintenance comparison. |
| inputs / outputs | Takes three plans and table count by value; constructs runtimes with options() and sizes mirror database. |
| invariants | All three options use maintenance-first mode and anchored completion; only LiveMaintenance differs. |
| ownership | Owns three DeltaRuntime facades, physical database and next sequence. |
| failure | Construction errors propagate. |
| cost | Constructs three fixed runtimes and empty table slots. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0044

[Lines 295–305](../../../../../tests/unit/delta_live_test.cpp#L295); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void seed(TableId table, Row row) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seed one physical set row into all three runtimes while in maintenance mode. |
| inputs / outputs | Takes table and Row; returns void. |
| invariants | Uses same next sequence for all; drains three empty output epochs before mirroring physical row; rejects duplicate fixture row. |
| ownership | Runtime/database own their stored copies; input Row moved to mirror after updates. |
| failure | Duplicate or unexpected maintenance output fails; runtime errors propagate. |
| cost | Three runtime applications and empty-epoch drains. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp) |

## B0046

[Lines 307–319](../../../../../tests/unit/delta_live_test.cpp#L307); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::tuple<DeltaMetrics, DeltaMetrics, DeltaMetrics> bootstrap() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Switch all runtimes to delta mode and compare their current L snapshots. |
| inputs / outputs | No args; returns tuple of three bootstrap metrics. |
| invariants | Calls check_live against A04 for each and requires the three factor sets equal. |
| ownership | Pair owns runtimes/database; returned metric values copied. |
| failure | Any live/A04 mismatch fails. |
| cost | Three mode transitions, three A04 evaluations and snapshot comparisons. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp) |

## B0048

[Lines 321–328](../../../../../tests/unit/delta_live_test.cpp#L321); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void maintenance() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return all three runtimes to maintenance mode and require no live snapshots remain. |
| inputs / outputs | No args; returns void. |
| invariants | Discards each live snapshot by mode transition and checks absence. |
| ownership | Pair retains runtime facades and physical database. |
| failure | Transition failure or retained snapshot fails. |
| cost | Three mode changes and checks. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp) |

## B0050

[Lines 330–382](../../../../../tests/unit/delta_live_test.cpp#L330); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  EpochPairResult apply(TableId table, SetOperation operation, Row row,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply a genuine physical set crossing to all three runtimes and compare output, live state, stage signatures and selected metrics. |
| inputs / outputs | Takes table, operation, Row and label; returns copied metrics/stages. |
| invariants | Builds A04 before/after expected answer; requires physical membership change; applies common sequence, drains all epochs, copies metrics/stages, commits mirror database only after output drain, then checks A04 L, live cardinalities, matching stages and selected on-output counters. |
| ownership | Runtimes own engine state; local after_database is copied then moved into pair after drains; result owns copied stages/metrics. |
| failure | Non-crossing fixture update, output/state/stage/metric mismatch fails; no allocation fault injection. |
| cost | Three runtime events, A04 before/after plus three current A04/live checks and stage/metric comparisons. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/delta_runtime.md § One physical input](../../../../delta_runtime.md), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0052

[Lines 384–384](../../../../../tests/unit/delta_live_test.cpp#L384); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] const Database& database() const { return database_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the fixture’s mirrored physical Database by const reference. |
| inputs / outputs | No args; returns const Database&. |
| invariants | Does not copy or mutate physical state. |
| ownership | Borrowed reference lifetime is bounded by RuntimePair. |
| failure | No custom failure handling. |
| cost | Constant-time accessor. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp) |

## B0053

[Lines 385–385](../../../../../tests/unit/delta_live_test.cpp#L385); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] const DeltaRuntime& incremental() const { return incremental_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the incremental runtime by const reference. |
| inputs / outputs | No args; returns const DeltaRuntime&. |
| invariants | Read-only facade access only. |
| ownership | Borrowed reference lifetime is bounded by RuntimePair. |
| failure | No custom failure handling. |
| cost | Constant-time accessor. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp) |

## B0054

[Lines 386–386](../../../../../tests/unit/delta_live_test.cpp#L386); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] const DeltaRuntime& eager() const { return eager_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the eager runtime by const reference. |
| inputs / outputs | No args; returns const DeltaRuntime&. |
| invariants | Read-only facade access only. |
| ownership | Borrowed reference lifetime is bounded by RuntimePair. |
| failure | No custom failure handling. |
| cost | Constant-time accessor. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp) |

## B0055

[Lines 387–387](../../../../../tests/unit/delta_live_test.cpp#L387); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] const DeltaRuntime& on_output() const { return on_output_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the on-output runtime by const reference. |
| inputs / outputs | No args; returns const DeltaRuntime&. |
| invariants | Read-only facade access only. |
| ownership | Borrowed reference lifetime is bounded by RuntimePair. |
| failure | No custom failure handling. |
| cost | Constant-time accessor. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp) |

## B0056

[Lines 388–401](../../../../../tests/unit/delta_live_test.cpp#L388); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L388-L401:sha256:19d9c3c7a8b2862c47f24c764c431b1b35652fe828f9054697038874162bb5ce
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare delta_live_test.cpp: bind local aliases/name imports; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp), [docs/incremental_live.md](../../../../incremental_live.md), [docs/code_review.md](../../../../code_review.md) |

## B0057

[Lines 402–407](../../../../../tests/unit/delta_live_test.cpp#L402); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
LiveWork live_work(const DeltaMetrics& metrics) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project the live-work counter subset used for growth comparisons. |
| inputs / outputs | Takes metrics by const reference; returns tuple of selected probes, mutations, bucket/support, queue and journal fields. |
| invariants | Omits other DeltaMetrics fields and all elapsed-time measurements. |
| ownership | Metrics borrowed; tuple owns copied scalar values. |
| failure | No custom failure handling. |
| cost | Copies ten selected counters. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp), [docs/delta_runtime.md § Work and space accounting](../../../../delta_runtime.md) |

## B0059

[Lines 409–437](../../../../../tests/unit/delta_live_test.cpp#L409); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaMetrics empty_delta_work(std::size_t dead_rows) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure empty-delta work after bootstrapping a root-child plan with dead child E rows. |
| inputs / outputs | Takes dead-row count; returns incremental metrics. |
| invariants | Seeds child E rows without root matches; each bootstrap scans seeded E once; a root insert has zero answer delta and checks incremental/on-output selected scans/copies/buckets are zero while eager rescans dead E. |
| ownership | Local RuntimePair owns runtimes and database. |
| failure | Any metric/state mismatch fails; no allocation or system-call injection. |
| cost | Seeds N rows, three bootstraps, one three-runtime event and A04 checks. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp), [docs/incremental_live.md § Cost claim for this component](../../../../incremental_live.md) |

## B0061

[Lines 439–450](../../../../../tests/unit/delta_live_test.cpp#L439); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void unrelated_e_growth_is_not_scanned() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare empty-delta selected work for one versus 64 unrelated child E rows. |
| inputs / outputs | No args; calls empty_delta_work twice and returns void. |
| invariants | Requires equal live_work tuple, aggregate work, and zero bucket rows at both sizes. |
| ownership | Each fixture call owns its local RuntimePair. |
| failure | Any count change fails; this is not a CPU-time bound. |
| cost | Two bounded fixture runs, N=1 and N=64. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp) |

## B0063

[Lines 452–470](../../../../../tests/unit/delta_live_test.cpp#L452); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void unchanged_e_becomes_live_and_unlive() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check an unchanged child E key enters and leaves L when its root support toggles. |
| inputs / outputs | No args; returns void. |
| invariants | After bootstrap, root insert visits one child bucket row and inserts two L keys; erase visits once and removes two; child E membership itself is unchanged. |
| ownership | RuntimePair owns fixture state. |
| failure | Expected counters or A04 state mismatch fails. |
| cost | Two root events and A04/stage checks. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp) |

## B0065

[Lines 472–497](../../../../../tests/unit/delta_live_test.cpp#L472); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void shared_separator_count_crossings() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check shared child support updates at 2-to-1 and 1-to-0 crossings. |
| inputs / outputs | No args; returns void. |
| invariants | First parent erase updates separator support without crossing/scanning bucket and preserves child L; final parent erase crosses to zero, visits one row and removes child L. |
| ownership | Pair owns runtimes/database. |
| failure | Metric or factor mismatch fails. |
| cost | Three seeds/bootstrap and two parent erases. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp), [docs/incremental_live.md § Bucket policy](../../../../incremental_live.md) |

## B0067

[Lines 499–527](../../../../../tests/unit/delta_live_test.cpp#L499); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaMetrics anchored_child_insertion_work(std::size_t root_rows) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure a child insertion under a populated shared-separator parent set. |
| inputs / outputs | Seeds the shared-separator fixture, bootstraps, inserts a child row under the final key and returns on_output metrics. RuntimePair options fix completion=anchored; the corrected event label is “on-output live child insertion with anchored completion.” |
| invariants | Seeds root and child for each key, bootstraps, then inserts a child row under the final key; on_output runtime has anchored completion (options() fixes it). Requires one changed E key/accepted answer and J=1,U=0 with no E/parent/bucket scans. The event diagnostic currently incorrectly says root-first. |
| ownership | RuntimePair owns three runtimes and database; returned metrics are copied before pair destruction. |
| failure | Any transition/output/metric mismatch fails. No fault injection. |
| cost | Seeds 2N rows, three bootstraps and one event with A04 checks; counters are deterministic work, not elapsed time. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp), [docs/anchored_delta.md § Work and remaining obligations](../../../../anchored_delta.md), [docs/delta_runtime.md § Work and space accounting](../../../../delta_runtime.md) |

## B0069

[Lines 529–542](../../../../../tests/unit/delta_live_test.cpp#L529); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void anchored_completion_avoids_unrelated_root_scan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare anchored on-output insertion work for 1 versus 64 unrelated root rows. |
| inputs / outputs | No args; runs anchored_child_insertion_work twice. |
| invariants | Compares selected live-work tuple and cursor startup/result/termination work, with J=1,U=0, one accepted result checked in called helper; these are work counters, not CPU time. |
| ownership | Each helper call owns a fresh RuntimePair. |
| failure | Counter differences fail. |
| cost | Two fixtures with 1 and 64 root rows. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp), [docs/anchored_delta.md § Work and remaining obligations](../../../../anchored_delta.md) |

## B0071

[Lines 544–561](../../../../../tests/unit/delta_live_test.cpp#L544); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void deep_descendant_cascade() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise a four-level descendant activation cascade. |
| inputs / outputs | No args; returns void. |
| invariants | After seeding descendants while root is absent, root insertion must activate four L entries, visit three descendant bucket rows, queue work and emit one full assignment. |
| ownership | Pair owns all state. |
| failure | Any accepted/live/action count mismatch fails. |
| cost | Three descendant seeds, bootstrap, one root event. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp) |

## B0073

[Lines 563–602](../../../../../tests/unit/delta_live_test.cpp#L563); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void shared_separator_later_completion_cleans_child() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise delayed descendant cleanup and later reactivation after shared support disappears. |
| inputs / outputs | No args; returns void. |
| invariants | Deleting root enumerates eight answers, erases nine L keys across five support updates/four crossings and empties projections; reinserting restores eight answers/nine L keys. |
| ownership | Pair owns runtimes/database; fixture rows and outputs are values. |
| failure | Answer, support, L count mismatch fails. |
| cost | Eight seeds, bootstrap and two events with full policy/A04 comparisons. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp) |

## B0075

[Lines 604–624](../../../../../tests/unit/delta_live_test.cpp#L604); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void simultaneous_parent_and_child_e_changes_are_idempotent() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise simultaneous parent and child E changes for idempotent L updates. |
| inputs / outputs | No args; returns void. |
| invariants | One child insert changes at least two E memberships but inserts exactly three L keys once; deletion erases exactly three once, with two child bucket rows on activation. |
| ownership | Pair owns runtime state. |
| failure | Membership/action mismatch fails. |
| cost | Bootstrap and two events. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp) |

## B0077

[Lines 626–647](../../../../../tests/unit/delta_live_test.cpp#L626); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void nullary_product_activation() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Activate a nullary product root after seeding three unary tables. |
| inputs / outputs | No args; returns void. |
| invariants | Third table insertion produces four answers; live projections contain nullary root Row{}, two keys in first factors and one inserted key in third; six L insertions include five bucket visits. |
| ownership | Pair owns state and copied snapshots. |
| failure | Answer/projection/action mismatch fails. |
| cost | Four seeds, bootstrap and one event. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp), [docs/delta_runtime.md § Views and prefix identity](../../../../delta_runtime.md) |

## B0079

[Lines 649–680](../../../../../tests/unit/delta_live_test.cpp#L649); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void aliases_and_mode_rebootstrap() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check alias route ownership and live-state rebootstrap after maintenance. |
| inputs / outputs | No args; returns void. |
| invariants | Two same-scope aliases emit an answer only at second route; after maintenance plus another seed, fresh bootstrap scans current E, and a later insertion again emits only at completing prefix. |
| ownership | Pair owns database and runtimes. |
| failure | Stage ordering or bootstrap/L mismatch fails. |
| cost | Three events around two mode transitions, with A04 and stage checks. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp) |

## B0080

[Lines 681–683](../../../../../tests/unit/delta_live_test.cpp#L681); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L681-L683:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in delta_live_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp), [docs/incremental_live.md](../../../../incremental_live.md), [docs/code_review.md](../../../../code_review.md) |

## B0081

[Lines 684–700](../../../../../tests/unit/delta_live_test.cpp#L684); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the finite live-maintenance policy fixtures. |
| inputs / outputs | No args; returns 0 after invoking each fixture. |
| invariants | Calls empty-delta growth, support crossings, anchored completion work, cascades, simultaneous changes, nullary product and aliases. No native run is claimed by this card. |
| ownership | Fixtures own local state; stdout reports selected work counts. |
| failure | Caught std::exception is printed and returns 1. |
| cost | Fixed finite fixture set, including N=1/64 comparisons. |
| Design | [tests/unit/delta_live_test.cpp](../../../../../tests/unit/delta_live_test.cpp), [docs/incremental_live.md](../../../../incremental_live.md), [docs/anchored_delta.md](../../../../anchored_delta.md) |
