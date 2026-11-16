# `tests/unit/support_journal_test.cpp` — block usage map

[Source](../../../../../tests/unit/support_journal_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `15210ea4610083f231f0cde3316264b093daa1d81b7d951bbee171e8aa781205`. 724 lines partitioned into 70 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../tests/unit/support_journal_test.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 19–22](../../../../../tests/unit/support_journal_test.cpp#L19) | Callable definition: template&lt;class Layout&gt; auto readable(const Layout& layout) | calls constexpr, descriptor; returns layout.descriptor(); layout · [reviewed contract](#b0002) |
| [B0003 · 23–28](../../../../../tests/unit/support_journal_test.cpp#L23) | declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_move_constructible_v&lt;SupportEpoch&gt;); · [reviewed contract](#b0003) |
| [B0004 · 29–31](../../../../../tests/unit/support_journal_test.cpp#L29) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0004) |
| [B0005 · 32–32](../../../../../tests/unit/support_journal_test.cpp#L32) | Explanatory comments or spacing. |  |
| [B0006 · 33–33](../../../../../tests/unit/support_journal_test.cpp#L33) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0006) |
| [B0007 · 34–34](../../../../../tests/unit/support_journal_test.cpp#L34) | Explanatory comments or spacing. |  |
| [B0008 · 35–43](../../../../../tests/unit/support_journal_test.cpp#L35) | Callable definition: PhysicalPlan unary_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0008) |
| [B0009 · 44–44](../../../../../tests/unit/support_journal_test.cpp#L44) | Explanatory comments or spacing. |  |
| [B0010 · 45–62](../../../../../tests/unit/support_journal_test.cpp#L45) | Callable definition: PhysicalPlan generalized_three_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0010) |
| [B0011 · 63–63](../../../../../tests/unit/support_journal_test.cpp#L63) | Explanatory comments or spacing. |  |
| [B0012 · 64–80](../../../../../tests/unit/support_journal_test.cpp#L64) | Callable definition: PhysicalPlan nested_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0012) |
| [B0013 · 81–81](../../../../../tests/unit/support_journal_test.cpp#L81) | Explanatory comments or spacing. |  |
| [B0014 · 82–89](../../../../../tests/unit/support_journal_test.cpp#L82) | Callable definition: PhysicalPlan boolean_root_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0014) |
| [B0015 · 90–90](../../../../../tests/unit/support_journal_test.cpp#L90) | Explanatory comments or spacing. |  |
| [B0016 · 91–97](../../../../../tests/unit/support_journal_test.cpp#L91) | Callable definition: PhysicalPlan nullary_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0016) |
| [B0017 · 98–98](../../../../../tests/unit/support_journal_test.cpp#L98) | Explanatory comments or spacing. |  |
| [B0018 · 99–107](../../../../../tests/unit/support_journal_test.cpp#L99) | Callable definition: PhysicalPlan projected_count_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0018) |
| [B0019 · 108–108](../../../../../tests/unit/support_journal_test.cpp#L108) | Explanatory comments or spacing. |  |
| [B0020 · 109–124](../../../../../tests/unit/support_journal_test.cpp#L109) | Callable definition: PhysicalPlan deep_chain_plan(std::size_t length) | calls std::to_string, push_back, planner::lower_tree; returns planner::lower_tree(catalog, query, tree); growth push_back; 1 loop sites · [reviewed contract](#b0020) |
| [B0021 · 125–125](../../../../../tests/unit/support_journal_test.cpp#L125) | Explanatory comments or spacing. |  |
| [B0022 · 126–131](../../../../../tests/unit/support_journal_test.cpp#L126) | Type/record definition: struct ReferenceValueState |  · [reviewed contract](#b0022) |
| [B0023 · 132–134](../../../../../tests/unit/support_journal_test.cpp#L132) | Callable definition: ReferenceValueState export_state(const SupportValueState& value) | calls begin, end; returns {value.member,value.satisfied,{value.child_present.begin(),value.child_present.end()},value.support} · [reviewed contract](#b0023) |
| [B0024 · 135–138](../../../../../tests/unit/support_journal_test.cpp#L135) | Callable definition: template&lt;class Left,class Right&gt;bool same_value_state(const Left& left, const Right& right) | calls std::ranges::equal; returns left.member == right.member && left.satisfied == right.satisfied && · [reviewed contract](#b0024) |
| [B0025 · 139–139](../../../../../tests/unit/support_journal_test.cpp#L139) | Explanatory comments or spacing. |  |
| [B0026 · 140–143](../../../../../tests/unit/support_journal_test.cpp#L140) | Type/record definition: struct RoleValue |  · [reviewed contract](#b0026) |
| [B0027 · 144–145](../../../../../tests/unit/support_journal_test.cpp#L144) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0027) |
| [B0028 · 146–156](../../../../../tests/unit/support_journal_test.cpp#L146) | Callable definition: RelationId role_relation(const auto& node, SupportRole role) | calls check, has_value, std::runtime_error; guard check(node.visible_relation.has_value(), "visible journal record has no visible relation");; returns node.records; node.survivors · [reviewed contract](#b0028) |
| [B0029 · 157–157](../../../../../tests/unit/support_journal_test.cpp#L157) | Explanatory comments or spacing. |  |
| [B0030 · 158–181](../../../../../tests/unit/support_journal_test.cpp#L158) | Callable definition: void check_role_state_shape(const auto& plan, const SupportHandle& handle, const auto& state) | calls check, nodes, size, has_value; guard check(handle.node.value &lt; plan.nodes().size(), "journal handle refers to an unknown node"); · [reviewed contract](#b0030) |
| [B0031 · 182–182](../../../../../tests/unit/support_journal_test.cpp#L182) | Explanatory comments or spacing. |  |
| [B0032 · 183–192](../../../../../tests/unit/support_journal_test.cpp#L183) | Callable definition: void add_role_value(StateMap& result, const SupportRuntime& runtime, SupportHandle handle, const storage::Tuple& tuple, Reference… | calls check, owner, get, layout; guard check(handle.owner == runtime.owner(), "snapshot exposes a foreign support handle");; growth emplace · [reviewed contract](#b0032) |
| [B0033 · 193–193](../../../../../tests/unit/support_journal_test.cpp#L193) | Explanatory comments or spacing. |  |
| [B0034 · 194–227](../../../../../tests/unit/support_journal_test.cpp#L194) | Callable definition: StateMap snapshot_state(const SupportRuntime& runtime, const SupportSnapshot& snapshot) | calls add_role_value, std::move, find, crown::storage::export_row; guard check(handle.has_value(), "snapshot survivor is absent from the committed membership table");; returns result; 5 loop sites · [reviewed contract](#b0034) |
| [B0035 · 228–228](../../../../../tests/unit/support_journal_test.cpp#L228) | Explanatory comments or spacing. |  |
| [B0036 · 229–231](../../../../../tests/unit/support_journal_test.cpp#L229) | Callable definition: bool same_tuple(const storage::Tuple& left, const storage::Tuple& right) | calls layout, same_token, values; returns left.layout().same_token(right.layout()) && left.values() == right.values() · [reviewed contract](#b0036) |
| [B0037 · 232–232](../../../../../tests/unit/support_journal_test.cpp#L232) | Explanatory comments or spacing. |  |
| [B0038 · 233–235](../../../../../tests/unit/support_journal_test.cpp#L233) | Callable definition: bool same_tuple(const storage::AccountedTuple& left, const storage::AccountedTuple& right) | calls layout, same_token, values; returns left.layout().same_token(right.layout()) && left.values() == right.values() · [reviewed contract](#b0038) |
| [B0039 · 236–236](../../../../../tests/unit/support_journal_test.cpp#L236) | Explanatory comments or spacing. |  |
| [B0040 · 237–242](../../../../../tests/unit/support_journal_test.cpp#L237) | Callable definition: storage::Tuple exported_tuple(const auto& plan, const storage::AccountedTuple& tuple) | calls layout, descriptor, check, same_descriptor; guard check(layout.same_descriptor(readable(plan.layouts().at(tuple.layout().id().value))),; returns layout.tuple(storage::export_row(tuple.values())) · [reviewed contract](#b0040) |
| [B0041 · 243–243](../../../../../tests/unit/support_journal_test.cpp#L243) | Explanatory comments or spacing. |  |
| [B0042 · 244–252](../../../../../tests/unit/support_journal_test.cpp#L244) | Callable definition: void compare_state_maps(const StateMap& left, const StateMap& right, const std::string& message) | calls check, size, begin, end; guard check(left.size() == right.size(), message + ": membership cardinality differs");; 1 loop sites · [reviewed contract](#b0042) |
| [B0043 · 253–256](../../../../../tests/unit/support_journal_test.cpp#L253) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0043) |
| [B0044 · 257–263](../../../../../tests/unit/support_journal_test.cpp#L257) | Callable definition: SemanticStateMap semantic_state_map(const StateMap& state) | calls check, emplace, crown::storage::export_row, values; guard check(result.emplace(SemanticKey{handle.node, handle.role, crown::storage::export_row(value.tuple.v…; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0044) |
| [B0045 · 264–264](../../../../../tests/unit/support_journal_test.cpp#L264) | Explanatory comments or spacing. |  |
| [B0046 · 265–274](../../../../../tests/unit/support_journal_test.cpp#L265) | Callable definition: void compare_semantic_state_maps(const StateMap& left, const StateMap& right, const std::string& message) | calls semantic_state_map, check, size, begin; guard check(a.size() == b.size(), message + ": membership cardinality differs");; 1 loop sites · [reviewed contract](#b0046) |
| [B0047 · 275–275](../../../../../tests/unit/support_journal_test.cpp#L275) | Explanatory comments or spacing. |  |
| [B0048 · 276–349](../../../../../tests/unit/support_journal_test.cpp#L276) | Callable definition: void replay_journal(const SupportRuntime& runtime, const SupportEpoch& epoch, const StateMap& before, const StateMap& after) | calls check, size, empty, owner; guard check(epoch.journal != nullptr, "a real update omitted its journal");; returns record.handle == transition.handle && record.cause == transition.cause &&; growth insert; 3 loop sites · [reviewed contract](#b0048) |
| [B0049 · 350–350](../../../../../tests/unit/support_journal_test.cpp#L350) | Explanatory comments or spacing. |  |
| [B0050 · 351–358](../../../../../tests/unit/support_journal_test.cpp#L351) | Callable definition: auto metrics_view(const SupportMetrics& m) | calls ; returns std::tuple{m.work, m.copied_rows, m.copied_index_memberships, · [reviewed contract](#b0050) |
| [B0051 · 359–359](../../../../../tests/unit/support_journal_test.cpp#L359) | Explanatory comments or spacing. |  |
| [B0052 · 360–365](../../../../../tests/unit/support_journal_test.cpp#L360) | Callable definition: auto state_view(const auto& state) | calls begin, end; returns std::tuple{state.member, · [reviewed contract](#b0052) |
| [B0053 · 366–366](../../../../../tests/unit/support_journal_test.cpp#L366) | Explanatory comments or spacing. |  |
| [B0054 · 367–444](../../../../../tests/unit/support_journal_test.cpp#L367) | Callable definition: void check_event_trace(const SupportRuntime& runtime, const NativeSetUpdate& update, const SupportEpoch& epoch, const StateMap& b… | calls check, empty, size, emplace; guard check(epoch.journal != nullptr, "event validation requires the real-update journal");; returns record.handle == event.source && record.cause == event.cause &&; growth emplace, insert; 6 loop sites · [reviewed contract](#b0054) |
| [B0055 · 445–445](../../../../../tests/unit/support_journal_test.cpp#L445) | Explanatory comments or spacing. |  |
| [B0056 · 446–469](../../../../../tests/unit/support_journal_test.cpp#L446) | Callable definition: SupportEpoch apply_checked(SupportRuntime& runtime, const NativeSetUpdate& update) | calls snapshot, snapshot_state, apply, check; guard check(epoch.native_changed && epoch.sequence == update.sequence,; returns entry.first.node == handle.node && entry.first.role == handle.role &&; epoch; 1 loop sites; source comment (unverified): // Every membership that survives this update must retain its public identity. · [reviewed contract](#b0056) |
| [B0057 · 470–470](../../../../../tests/unit/support_journal_test.cpp#L470) | Explanatory comments or spacing. |  |
| [B0058 · 471–517](../../../../../tests/unit/support_journal_test.cpp#L471) | Callable definition: void trace_on_and_off_have_identical_accounting() | calls nested_plan, traced, quiet, n; guard check(a.has_answer == b.has_answer && a.native_changed == b.native_changed &&; growth insert; 2 loop sites · [reviewed contract](#b0058) |
| [B0059 · 518–518](../../../../../tests/unit/support_journal_test.cpp#L518) | Explanatory comments or spacing. |  |
| [B0060 · 519–570](../../../../../tests/unit/support_journal_test.cpp#L519) | Callable definition: void model_native_generalized_boolean_nullary_and_projection_counts() | calls runtime, unary_plan, apply_checked, n; guard check(insert.has_answer && !erase.has_answer, "native root journal replay missed answer crossings");; returns value.key.values() == Row{n(1)}; growth insert · [reviewed contract](#b0060) |
| [B0061 · 571–571](../../../../../tests/unit/support_journal_test.cpp#L571) | Explanatory comments or spacing. |  |
| [B0062 · 572–615](../../../../../tests/unit/support_journal_test.cpp#L572) | Callable definition: void nested_event_chain_and_deep_cascade() | calls runtime, nested_plan, apply_checked, n; guard check(cascade.metrics.events_enqueued == 3 && cascade.metrics.events_applied == 3 &&; returns event.id == 1; event.id == 2; growth insert; 1 loop sites · [reviewed contract](#b0062) |
| [B0063 · 616–616](../../../../../tests/unit/support_journal_test.cpp#L616) | Explanatory comments or spacing. |  |
| [B0064 · 617–625](../../../../../tests/unit/support_journal_test.cpp#L617) | Callable definition: const JournalRecord& record_for(const SupportJournal& journal, SupportRole role, const Row& values, bool after_member) | calls std::find_if, begin, end, tuple; returns record.handle.role == role && record.tuple().values() == values &&; *found · [reviewed contract](#b0064) |
| [B0065 · 626–626](../../../../../tests/unit/support_journal_test.cpp#L626) | Explanatory comments or spacing. |  |
| [B0066 · 627–672](../../../../../tests/unit/support_journal_test.cpp#L627) | Callable definition: void retained_pins_outlive_updates_move_and_destruction() | calls n, runtime, unary_plan, owner; guard check(insertion_journal && insertion_journal-&gt;events.empty(),; growth insert · [reviewed contract](#b0066) |
| [B0067 · 673–673](../../../../../tests/unit/support_journal_test.cpp#L673) | Explanatory comments or spacing. |  |
| [B0068 · 674–708](../../../../../tests/unit/support_journal_test.cpp#L674) | Callable definition: void unrelated_rows_are_not_copied_or_logged() | calls runtime, unary_plan, apply, sequence; guard check(before.nodes\[0\].records.size() == static_cast&lt;std::size_t&gt;(unrelated),; growth insert; 4 loop sites · [reviewed contract](#b0068) |
| [B0069 · 709–711](../../../../../tests/unit/support_journal_test.cpp#L709) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0069) |
| [B0070 · 712–724](../../../../../tests/unit/support_journal_test.cpp#L712) | Callable definition: int main() | calls model_native_generalized_boolean_nullary_and_projection_counts, trace_on_and_off_have_identical_accounting, nested_event_chain_and_deep_cascade, retained_pins_outlive_updates_move_and_destruction; returns 1; 0 · [reviewed contract](#b0070) |

## B0001

[Lines 1–18](../../../../../tests/unit/support_journal_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L18:sha256:05a9b53dbc98a2dac58cae2d619a507505fef9b2433ccaff89e4e57ef2a3c6d1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare support_journal_test.cpp: include "crown/api/error.hpp", "crown/planner/lower.hpp", "crown/runtime/support.hpp", &lt;algorithm&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;map&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;tuple&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;vector&gt;. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 19–22](../../../../../tests/unit/support_journal_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Layout> auto readable(const Layout& layout){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose an owning layout descriptor when available, otherwise pass through the supplied layout object. |
| inputs / outputs | Declaration: \`template&lt;class Layout&gt; auto readable(const Layout& layout)\`. Inputs/outputs in this selected body: Choose an owning layout descriptor when available, otherwise pass through the supplied layout object. |
| invariants | Uses a compile-time requires branch; returned descriptor/layout is an owning value or type-provided view as selected. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0003

[Lines 23–28](../../../../../tests/unit/support_journal_test.cpp#L23); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L28:sha256:94b2fcf89d4340b6241a85e14830790a8ba4063d1d786d60b537739abadc920c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare support_journal_test.cpp: bind local aliases/name imports; require 2 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 29–31](../../../../../tests/unit/support_journal_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn a failed journal fixture assertion into std::runtime_error. |
| inputs / outputs | Declaration: \`void check(bool condition, const std::string& message)\`. Inputs/outputs in this selected body: Turn a failed journal fixture assertion into std::runtime_error. |
| invariants | False check throws runtime_error; no CROWN Error translation. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | A failed fixture assertion raises std::runtime_error; no production error translation. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0006

[Lines 33–33](../../../../../tests/unit/support_journal_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one int64 Value for support rows. |
| inputs / outputs | Declaration: \`Value n(std::int64_t value)\`. Inputs/outputs in this selected body: Construct one int64 Value for support rows. |
| invariants | Value owns one scalar. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0008

[Lines 35–43](../../../../../tests/unit/support_journal_test.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan unary_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a one-node unary query with output x. |
| inputs / outputs | Declaration: \`PhysicalPlan unary_plan()\`. Inputs/outputs in this selected body: Lower a one-node unary query with output x. |
| invariants | Returned PhysicalPlan owns its lowered metadata; table/query/tree are local fixture values. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0010

[Lines 45–62](../../../../../tests/unit/support_journal_test.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan generalized_three_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a generalized root intersecting three native unary children. |
| inputs / outputs | Declaration: \`PhysicalPlan generalized_three_plan()\`. Inputs/outputs in this selected body: Lower a generalized root intersecting three native unary children. |
| invariants | Every child relation contains the same x key; generalized root is satisfied only after all three child flags. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0012

[Lines 64–80](../../../../../tests/unit/support_journal_test.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan nested_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a generalized root over a native b(x,y) child, native c(y) child under b, and g(x) sibling. |
| inputs / outputs | Declaration: \`PhysicalPlan nested_plan()\`. Inputs/outputs in this selected body: Lower a generalized root over a native b(x,y) child, native c(y) child under b, and g(x) sibling. |
| invariants | Nested b→c propagation and sibling g meet at generalized root; query output is x. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0014

[Lines 82–89](../../../../../tests/unit/support_journal_test.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan boolean_root_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a Boolean query with a hidden unary source and empty head. |
| inputs / outputs | Declaration: \`PhysicalPlan boolean_root_plan()\`. Inputs/outputs in this selected body: Lower a Boolean query with a hidden unary source and empty head. |
| invariants | Empty head means answer is Boolean/nullary membership, not returned hidden x. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0016

[Lines 91–97](../../../../../tests/unit/support_journal_test.cpp#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan nullary_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a zero-column nullary source query. |
| inputs / outputs | Declaration: \`PhysicalPlan nullary_plan()\`. Inputs/outputs in this selected body: Lower a zero-column nullary source query. |
| invariants | Zero-column source row represents empty tuple; membership controls Boolean result. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0018

[Lines 99–107](../../../../../tests/unit/support_journal_test.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan projected_count_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a pair source projected to x so two source tuples can share a visible key. |
| inputs / outputs | Declaration: \`PhysicalPlan projected_count_plan()\`. Inputs/outputs in this selected body: Lower a pair source projected to x so two source tuples can share a visible key. |
| invariants | Visible key x has support count that can change while membership stays present. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0020

[Lines 109–124](../../../../../tests/unit/support_journal_test.cpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan deep_chain_plan(std::size_t length) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a native unary chain of caller-selected length with each node sharing x. |
| inputs / outputs | Declaration: \`PhysicalPlan deep_chain_plan(std::size_t length)\`. Inputs/outputs in this selected body: Build a native unary chain of caller-selected length with each node sharing x. |
| invariants | Plan and copied query/tree own length-sized vectors; test uses length 128 only for its cascade fixture. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Builds a length-node plan; the cascade fixture uses 128 nodes. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0022

[Lines 126–131](../../../../../tests/unit/support_journal_test.cpp#L126); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ReferenceValueState {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold model membership, optional satisfied-child count, child flags and projection support count. |
| inputs / outputs | Declaration: \`struct ReferenceValueState\`. Inputs/outputs in this selected body: Hold model membership, optional satisfied-child count, child flags and projection support count. |
| invariants | Plain model fields represent only journal-relevant support metadata. |
| ownership | Plain local fixture value type; declared containers and scalar values are owned by the record. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Plain fixture data declaration; no runtime work. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0023

[Lines 132–134](../../../../../tests/unit/support_journal_test.cpp#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReferenceValueState export_state(const SupportValueState& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export one runtime SupportValueState into the model state value. |
| inputs / outputs | Declaration: \`ReferenceValueState export_state(const SupportValueState& value)\`. Inputs/outputs in this selected body: Export one runtime SupportValueState into the model state value. |
| invariants | Copies member/count/flags/support; does not expose internal storage iterator. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0024

[Lines 135–138](../../../../../tests/unit/support_journal_test.cpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Left,class Right>bool same_value_state(const Left& left, const Right& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the four model-state fields across value types. |
| inputs / outputs | Declaration: \`template&lt;class Left,class Right&gt;bool same_value_state(const Left& left, const Right& right)\`. Inputs/outputs in this selected body: Compare the four model-state fields across value types. |
| invariants | Compares member, optional count, ordered child flags and optional support only. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0026

[Lines 140–143](../../../../../tests/unit/support_journal_test.cpp#L140); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct RoleValue {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold a tuple and its independently modeled support-value state. |
| inputs / outputs | Declaration: \`struct RoleValue\`. Inputs/outputs in this selected body: Hold a tuple and its independently modeled support-value state. |
| invariants | RoleValue owns copied tuple and value state. |
| ownership | Plain local fixture value type; declared containers and scalar values are owned by the record. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Plain fixture data declaration; no runtime work. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0027

[Lines 144–145](../../../../../tests/unit/support_journal_test.cpp#L144); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L144-L145:sha256:2a60d813b9f0b9b2acf7b0cfd51b765d9b0d14b8405d2cef8974d37d42d541e6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare support_journal_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0028

[Lines 146–156](../../../../../tests/unit/support_journal_test.cpp#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RelationId role_relation(const auto& node, SupportRole role) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map a runtime node and SupportRole to the corresponding records/survivor/parent/visible relation ID. |
| inputs / outputs | Declaration: \`RelationId role_relation(const auto& node, SupportRole role)\`. Inputs/outputs in this selected body: Map a runtime node and SupportRole to the corresponding records/survivor/parent/visible relation ID. |
| invariants | Visible role requires a compiled visible relation; other roles select plan relation IDs. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0030

[Lines 158–181](../../../../../tests/unit/support_journal_test.cpp#L158); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_role_state_shape(const auto& plan, const SupportHandle& handle,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the state shape allowed for one handle role against node child count and support metadata. |
| inputs / outputs | Declaration: \`void check_role_state_shape(const auto& plan, const SupportHandle& handle, const auto& state)\`. Inputs/outputs in this selected body: Check the state shape allowed for one handle role against node child count and support metadata. |
| invariants | For member records, child flag count and satisfied count must match; projection roles require positive support and no child metadata. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0032

[Lines 183–192](../../../../../tests/unit/support_journal_test.cpp#L183); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void add_role_value(StateMap& result, const SupportRuntime& runtime, SupportHandle handle,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add one state to the map after checking runtime owner, live handle, exact tuple/layout, role shape and uniqueness. |
| inputs / outputs | Declaration: \`void add_role_value(StateMap& result, const SupportRuntime& runtime, SupportHandle handle, const storage::Tuple& tuple, ReferenceValueState state)\`. Inputs/outputs in this selected body: Add one state to the map after checking runtime owner, live handle, exact tuple/layout, role shape and uniqueness. |
| invariants | Committed runtime lookup and role layout must match; duplicate public handles fail. |
| ownership | Mutates output StateMap; stored RoleValue owns tuple/state copies. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0034

[Lines 194–227](../../../../../tests/unit/support_journal_test.cpp#L194); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StateMap snapshot_state(const SupportRuntime& runtime, const SupportSnapshot& snapshot) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a model StateMap from the committed SupportSnapshot and resolve public handles for survivors. |
| inputs / outputs | Declaration: \`StateMap snapshot_state(const SupportRuntime& runtime, const SupportSnapshot& snapshot)\`. Inputs/outputs in this selected body: Build a model StateMap from the committed SupportSnapshot and resolve public handles for survivors. |
| invariants | Includes records, survivors, parent keys and visible keys; snapshots are committed owning diagnostics, while map stores copied tuples/state. |
| ownership | Returns StateMap owning exported tuples and metadata copied from snapshot. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0036

[Lines 229–231](../../../../../tests/unit/support_journal_test.cpp#L229); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_tuple(const storage::Tuple& left, const storage::Tuple& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare tuple layout token identity and tuple values. |
| inputs / outputs | Declaration: \`bool same_tuple(const storage::Tuple& left, const storage::Tuple& right)\`. Inputs/outputs in this selected body: Compare tuple layout token identity and tuple values. |
| invariants | Tuple values are equal only if layout token and values both agree. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0038

[Lines 233–235](../../../../../tests/unit/support_journal_test.cpp#L233); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_tuple(const storage::AccountedTuple& left, const storage::AccountedTuple& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare AccountedTuple layout token identity and values. |
| inputs / outputs | Declaration: \`bool same_tuple(const storage::AccountedTuple& left, const storage::AccountedTuple& right)\`. Inputs/outputs in this selected body: Compare AccountedTuple layout token identity and values. |
| invariants | Checks corresponding native-accounted tuple identity/value, not an independently allocated storage account. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0040

[Lines 237–242](../../../../../tests/unit/support_journal_test.cpp#L237); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::Tuple exported_tuple(const auto& plan, const storage::AccountedTuple& tuple) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export an AccountedTuple through its plan-defined layout descriptor into an owning regular Tuple. |
| inputs / outputs | Declaration: \`storage::Tuple exported_tuple(const auto& plan, const storage::AccountedTuple& tuple)\`. Inputs/outputs in this selected body: Export an AccountedTuple through its plan-defined layout descriptor into an owning regular Tuple. |
| invariants | Checks plan definition then exports values into a tuple owning copied row values. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0042

[Lines 244–252](../../../../../tests/unit/support_journal_test.cpp#L244); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compare_state_maps(const StateMap& left, const StateMap& right, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare exact handle-keyed maps, tuple identity/value and state metadata. |
| inputs / outputs | Declaration: \`void compare_state_maps(const StateMap& left, const StateMap& right, const std::string& message)\`. Inputs/outputs in this selected body: Compare exact handle-keyed maps, tuple identity/value and state metadata. |
| invariants | Handle identity is part of exact replay map equality; model fields are checked separately. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0043

[Lines 253–256](../../../../../tests/unit/support_journal_test.cpp#L253); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L253-L256:sha256:b479186be2e5e691133be489daf7b31fc9357794000b27374cc889fcbc54b88d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare support_journal_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0044

[Lines 257–263](../../../../../tests/unit/support_journal_test.cpp#L257); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SemanticStateMap semantic_state_map(const StateMap& state) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert a handle-keyed state map to logical node/role/row keys, requiring unique logical values. |
| inputs / outputs | Declaration: \`SemanticStateMap semantic_state_map(const StateMap& state)\`. Inputs/outputs in this selected body: Convert a handle-keyed state map to logical node/role/row keys, requiring unique logical values. |
| invariants | Logical map intentionally removes owner/tuple ID; duplicate same logical role row fails. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0046

[Lines 265–274](../../../../../tests/unit/support_journal_test.cpp#L265); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compare_semantic_state_maps(const StateMap& left, const StateMap& right, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare state maps after erasing owner/tuple identity and retaining logical role state. |
| inputs / outputs | Declaration: \`void compare_semantic_state_maps(const StateMap& left, const StateMap& right, const std::string& message)\`. Inputs/outputs in this selected body: Compare state maps after erasing owner/tuple identity and retaining logical role state. |
| invariants | Compares only logical role key/state, not handle-generation identity. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0048

[Lines 276–349](../../../../../tests/unit/support_journal_test.cpp#L276); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void replay_journal(const SupportRuntime& runtime, const SupportEpoch& epoch,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replay each affected-record journal over the before StateMap, validate pins/order/causes/transitions, and require exact after-state. |
| inputs / outputs | Declaration: \`void replay_journal(const SupportRuntime& runtime, const SupportEpoch& epoch, const StateMap& before, const StateMap& after)\`. Inputs/outputs in this selected body: Replay each affected-record journal over the before StateMap, validate pins/order/causes/transitions, and require exact after-state. |
| invariants | For real updates, journal ordinals are one-based; each record before-state must match replay prefix; after-state is applied in order; transitions must match membership crossings and causes. |
| ownership | Replayed map is local and owns tuple/state copies; journal is borrowed from epoch. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Applies ordered journal records and scans finite events/transitions/maps. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0050

[Lines 351–358](../../../../../tests/unit/support_journal_test.cpp#L351); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto metrics_view(const SupportMetrics& m) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project all SupportMetrics fields into a comparable tuple. |
| inputs / outputs | Declaration: \`auto metrics_view(const SupportMetrics& m)\`. Inputs/outputs in this selected body: Project all SupportMetrics fields into a comparable tuple. |
| invariants | Includes mandatory/optional counters in the listed SupportMetrics projection; equality is test-specific. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0052

[Lines 360–365](../../../../../tests/unit/support_journal_test.cpp#L360); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto state_view(const auto& state) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project optional SupportValueState metadata into a comparable tuple. |
| inputs / outputs | Declaration: \`auto state_view(const auto& state)\`. Inputs/outputs in this selected body: Project optional SupportValueState metadata into a comparable tuple. |
| invariants | Compares member/count/flags/support optional values. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0054

[Lines 367–444](../../../../../tests/unit/support_journal_test.cpp#L367); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_event_trace(const SupportRuntime& runtime, const NativeSetUpdate& update,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate enabled propagation event IDs, causes, source/target slots, enqueue/application order and journal linkage; require no event vector when capture is off. |
| inputs / outputs | Declaration: \`void check_event_trace(const SupportRuntime& runtime, const NativeSetUpdate& update, const SupportEpoch& epoch, const StateMap& before, const StateMap& after, bool trace_enabled)\`. Inputs/outputs in this selected body: Validate enabled propagation event IDs, causes, source/target slots, enqueue/application order and journal linkage; require no event vector when capture is off. |
| invariants | When enabled, event IDs and applied ordinals are contiguous but causal ID order may differ from applied order; when disabled event vector is empty while journal remains. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Scans one update’s finite event/journal/transition trace. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0056

[Lines 446–469](../../../../../tests/unit/support_journal_test.cpp#L446); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportEpoch apply_checked(SupportRuntime& runtime, const NativeSetUpdate& update) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one changed native update, capture before/after snapshots, validate stable handles, journal replay and event trace. |
| inputs / outputs | Declaration: \`SupportEpoch apply_checked(SupportRuntime& runtime, const NativeSetUpdate& update)\`. Inputs/outputs in this selected body: Apply one changed native update, capture before/after snapshots, validate stable handles, journal replay and event trace. |
| invariants | Requires native set change and exact sequence; reads before/after full snapshot and validates public journal; does not inject failure. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0058

[Lines 471–517](../../../../../tests/unit/support_journal_test.cpp#L471); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void trace_on_and_off_have_identical_accounting() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare trace capture on/off answers, work metrics and journal record identities over nested fixture updates plus a no-op. |
| inputs / outputs | Declaration: \`void trace_on_and_off_have_identical_accounting()\`. Inputs/outputs in this selected body: Compare trace capture on/off answers, work metrics and journal record identities over nested fixture updates plus a no-op. |
| invariants | Capture mode changes retained events/transitions only; affected-record journal and metrics remain equal for the same updates; no-op yields no journal. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0060

[Lines 519–570](../../../../../tests/unit/support_journal_test.cpp#L519); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void model_native_generalized_boolean_nullary_and_projection_counts() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Model native, three-child generalized, Boolean, nullary and projected-count support journals. |
| inputs / outputs | Declaration: \`void model_native_generalized_boolean_nullary_and_projection_counts()\`. Inputs/outputs in this selected body: Model native, three-child generalized, Boolean, nullary and projected-count support journals. |
| invariants | Finite fixture families check answer crossings, all child flags, nullary membership and positive support count without visible crossing. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0062

[Lines 572–615](../../../../../tests/unit/support_journal_test.cpp#L572); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void nested_event_chain_and_deep_cascade() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check nested native-to-native-to-generalized event causality and insertion/deletion cascades on a 128-node chain. |
| inputs / outputs | Declaration: \`void nested_event_chain_and_deep_cascade()\`. Inputs/outputs in this selected body: Check nested native-to-native-to-generalized event causality and insertion/deletion cascades on a 128-node chain. |
| invariants | Nested fixture expects 3 event chain; deep fixture expects 128 insert and erase propagation events, not a general complexity benchmark. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Nested fixture plus 128-node insertion/deletion cascade; no asymptotic claim. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0064

[Lines 617–625](../../../../../tests/unit/support_journal_test.cpp#L617); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const JournalRecord& record_for(const SupportJournal& journal, SupportRole role,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find one retained journal record by role, tuple values and selected membership side. |
| inputs / outputs | Declaration: \`const JournalRecord& record_for(const SupportJournal& journal, SupportRole role, const Row& values, bool after_member)\`. Inputs/outputs in this selected body: Find one retained journal record by role, tuple values and selected membership side. |
| invariants | Return is a borrowed const reference into caller-owned SupportJournal; it dangles if the journal is released. |
| ownership | Reference aliases a record owned by caller-held SupportJournal. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0066

[Lines 627–672](../../../../../tests/unit/support_journal_test.cpp#L627); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void retained_pins_outlive_updates_move_and_destruction() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep insertion/deletion journal tuple pins and owner identity readable across another update, runtime move and runtime destruction. |
| inputs / outputs | Declaration: \`void retained_pins_outlive_updates_move_and_destruction()\`. Inputs/outputs in this selected body: Keep insertion/deletion journal tuple pins and owner identity readable across another update, runtime move and runtime destruction. |
| invariants | Caller-held shared journal owns pins and before/after values beyond live membership removal and runtime destruction; runtime move preserves owner identity. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0068

[Lines 674–708](../../../../../tests/unit/support_journal_test.cpp#L674); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void unrelated_rows_are_not_copied_or_logged() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check a one-row update in a 32-row state logs only relevant tuple rows and one retained journal does not keep the whole history alive. |
| inputs / outputs | Declaration: \`void unrelated_rows_are_not_copied_or_logged()\`. Inputs/outputs in this selected body: Check a one-row update in a 32-row state logs only relevant tuple rows and one retained journal does not keep the whole history alive. |
| invariants | One added row among 32 preexisting rows must produce fewer than 32 journal records; one retained epoch remains a partial history only. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | Local \`check\` failures throw std::runtime_error; support API/allocation exceptions otherwise propagate. No allocation-fault injector is defined in this test. |
| cost | 32-row baseline and one update; count bounds are not memory-byte or timing bounds. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |

## B0069

[Lines 709–711](../../../../../tests/unit/support_journal_test.cpp#L709); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L709-L711:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in support_journal_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0070

[Lines 712–724](../../../../../tests/unit/support_journal_test.cpp#L712); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run all support-journal fixtures and report exceptions as a process status. |
| inputs / outputs | Declaration: \`int main()\`. Inputs/outputs in this selected body: Run all support-journal fixtures and report exceptions as a process status. |
| invariants | No allocation fault injection or timing benchmark is run by this executable source; main only invokes finite fixture groups. |
| ownership | Fixture/runtime/report objects are local to the test call; no runtime owner escapes the scenario. |
| failure | The driver catches documented exceptions, prints a diagnostic and returns a nonzero status. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/support_journal_test.cpp](../../../../../tests/unit/support_journal_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [docs/runtime_support.md § Propagation and transition capture](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md § Revisions and allocation metadata](../../../../storage_journal.md), [docs/decisions/0013-support-journals.md § Decision](../../../../decisions/0013-support-journals.md), [docs/decisions/0013-support-journals.md § Consequences and limits](../../../../decisions/0013-support-journals.md) |
