# `tests/unit/result_cursor_test.cpp` — block usage map

[Source](../../../../../tests/unit/result_cursor_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `5843f4097bb7056757f265c90e0a228f6abcec5645a3ad29eb241b42d81c9aed`. 594 lines partitioned into 51 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–26](../../../../../tests/unit/result_cursor_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 27–29](../../../../../tests/unit/result_cursor_test.cpp#L27) | Callable definition: void check(bool condition,const std::string& message) | calls std::runtime_error; guard void check(bool condition,const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 30–37](../../../../../tests/unit/result_cursor_test.cpp#L30) | Callable definition: template&lt;class Action&gt; void error(Action&& action,std::string_view code) | calls action, check, code, std::string; guard check(failure.code()==code,"expected "+std::string(code)+", got "+failure.code()); · [reviewed contract](#b0003) |
| [B0004 · 38–38](../../../../../tests/unit/result_cursor_test.cpp#L38) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0004) |
| [B0005 · 39–39](../../../../../tests/unit/result_cursor_test.cpp#L39) | Callable definition: Value s(std::string value) | calls ; returns value · [reviewed contract](#b0005) |
| [B0006 · 40–40](../../../../../tests/unit/result_cursor_test.cpp#L40) | Explanatory comments or spacing. |  |
| [B0007 · 41–50](../../../../../tests/unit/result_cursor_test.cpp#L41) | Callable definition: Relation drain_unique(SupportRuntime::ResultCursor& cursor) | calls next, check, layout, same_token; guard check(row-&gt;layout().same_token(cursor.layout()),"returned row does not retain the cursor output lay…; returns result; growth insert; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 51–51](../../../../../tests/unit/result_cursor_test.cpp#L51) | Explanatory comments or spacing. |  |
| [B0009 · 52–56](../../../../../tests/unit/result_cursor_test.cpp#L52) | Callable definition: void insert(PhysicalRuntime& runtime,Database& database,std::uint64_t& sequence,TableId table,Row row) | calls apply, check, at, std::move; guard check(result.input.physical_changed,"fixture source row was not inserted");; growth insert · [reviewed contract](#b0009) |
| [B0010 · 57–57](../../../../../tests/unit/result_cursor_test.cpp#L57) | Explanatory comments or spacing. |  |
| [B0011 · 58–65](../../../../../tests/unit/result_cursor_test.cpp#L58) | Callable definition: PhysicalPlan one_column_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog,query,tree) · [reviewed contract](#b0011) |
| [B0012 · 66–66](../../../../../tests/unit/result_cursor_test.cpp#L66) | Explanatory comments or spacing. |  |
| [B0013 · 67–93](../../../../../tests/unit/result_cursor_test.cpp#L67) | Callable definition: PhysicalPlan shared_key_plan(std::size_t arity) | calls check, push_back, std::to_string, planner::lower_tree; guard check(arity&gt;=2,"shared-key plan needs at least two children");; returns planner::lower_tree(catalog,query,tree); growth push_back; 5 loop sites · [reviewed contract](#b0013) |
| [B0014 · 94–94](../../../../../tests/unit/result_cursor_test.cpp#L94) | Explanatory comments or spacing. |  |
| [B0015 · 95–110](../../../../../tests/unit/result_cursor_test.cpp#L95) | Callable definition: PhysicalPlan disconnected_plan(std::vector&lt;Output&gt; head) | calls std::move, planner::lower_tree; returns planner::lower_tree(catalog,query,tree) · [reviewed contract](#b0015) |
| [B0016 · 111–111](../../../../../tests/unit/result_cursor_test.cpp#L111) | Explanatory comments or spacing. |  |
| [B0017 · 112–128](../../../../../tests/unit/result_cursor_test.cpp#L112) | Callable definition: PhysicalPlan native_chain_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog,query,tree) · [reviewed contract](#b0017) |
| [B0018 · 129–129](../../../../../tests/unit/result_cursor_test.cpp#L129) | Explanatory comments or spacing. |  |
| [B0019 · 130–135](../../../../../tests/unit/result_cursor_test.cpp#L130) | Callable definition: PhysicalPlan nullary_atom_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog,query,tree) · [reviewed contract](#b0019) |
| [B0020 · 136–136](../../../../../tests/unit/result_cursor_test.cpp#L136) | Explanatory comments or spacing. |  |
| [B0021 · 137–141](../../../../../tests/unit/result_cursor_test.cpp#L137) | Callable definition: PhysicalPlan constant_plan(bool contradiction) | calls planner::lower_tree; returns planner::lower_tree(catalog,query,FreeConnexTree{}) · [reviewed contract](#b0021) |
| [B0022 · 142–142](../../../../../tests/unit/result_cursor_test.cpp#L142) | Explanatory comments or spacing. |  |
| [B0023 · 143–146](../../../../../tests/unit/result_cursor_test.cpp#L143) | Callable definition: std::optional&lt;VariableId&gt; variable_term(const Term& term) | calls ; returns *variable; {} · [reviewed contract](#b0023) |
| [B0024 · 147–175](../../../../../tests/unit/result_cursor_test.cpp#L147) | Callable definition: FreeConnexTree sql_tree(const Query& query) | calls empty, scopes, size, variable_term; returns tree; tree; growth insert, push_back; 5 loop sites · [reviewed contract](#b0024) |
| [B0025 · 176–186](../../../../../tests/unit/result_cursor_test.cpp#L176) | Callable definition: PhysicalPlan normalized_plan(std::string_view sql,const Catalog& catalog) | calls frontend::bind_sql, std::runtime_error, frontend::normalize_sql, std::move; returns planner::lower_normalized(program,tree) · [reviewed contract](#b0025) |
| [B0026 · 187–187](../../../../../tests/unit/result_cursor_test.cpp#L187) | Explanatory comments or spacing. |  |
| [B0027 · 188–200](../../../../../tests/unit/result_cursor_test.cpp#L188) | Callable definition: Relation normalized_core_reference(const auto& plan,const Database& physical) | calls reference::input::normalized, normalized, resize, size; returns reference::evaluate(program.core_catalog,program.core,logical); growth insert, resize; 2 loop sites · [reviewed contract](#b0027) |
| [B0028 · 201–201](../../../../../tests/unit/result_cursor_test.cpp#L201) | Explanatory comments or spacing. |  |
| [B0029 · 202–209](../../../../../tests/unit/result_cursor_test.cpp#L202) | Callable definition: Relation cursor_matches_reference(PhysicalRuntime& runtime,const Database& database) | calls reference::evaluate, reference::input::catalog, plan, catalog; guard check(cursor.sequence()==runtime.sequence() && cursor.owner()==runtime.owner(),"core cursor did not…; returns actual · [reviewed contract](#b0029) |
| [B0030 · 210–210](../../../../../tests/unit/result_cursor_test.cpp#L210) | Explanatory comments or spacing. |  |
| [B0031 · 211–235](../../../../../tests/unit/result_cursor_test.cpp#L211) | Callable definition: void shared_key_and_product_differential(std::size_t arity) | calls shared_key_plan, runtime, std::move, resize; guard check(step_count&gt;=arity+1,"N-ary product plan did not include the root and each child frame");; growth insert, resize; 4 loop sites · [reviewed contract](#b0031) |
| [B0032 · 236–236](../../../../../tests/unit/result_cursor_test.cpp#L236) | Explanatory comments or spacing. |  |
| [B0033 · 237–243](../../../../../tests/unit/result_cursor_test.cpp#L237) | Callable definition: Database disconnected_database() | calls resize, n, s; returns database; growth resize · [reviewed contract](#b0033) |
| [B0034 · 244–250](../../../../../tests/unit/result_cursor_test.cpp#L244) | Callable definition: void fill_disconnected(PhysicalRuntime& runtime,const Database& database,std::uint64_t& sequence) | calls size, apply, check; guard check(result.input.physical_changed,"disconnected fixture row was not inserted");; growth insert; 2 loop sites · [reviewed contract](#b0034) |
| [B0035 · 251–268](../../../../../tests/unit/result_cursor_test.cpp#L251) | Callable definition: void disconnected_products_and_projections() | calls disconnected_database, disconnected_plan, runtime, std::move; guard check(actual.size()==12,"disconnected product cardinality did not multiply its three distinct proje… · [reviewed contract](#b0035) |
| [B0036 · 269–269](../../../../../tests/unit/result_cursor_test.cpp#L269) | Explanatory comments or spacing. |  |
| [B0037 · 270–302](../../../../../tests/unit/result_cursor_test.cpp#L270) | Callable definition: void native_chain_differential() | calls runtime, native_chain_plan, resize, n; guard check(steps.size()==3 && steps\[1\].parent_step==0 && steps\[2\].parent_step==1,; growth insert, resize; 3 loop sites · [reviewed contract](#b0037) |
| [B0038 · 303–303](../../../../../tests/unit/result_cursor_test.cpp#L303) | Explanatory comments or spacing. |  |
| [B0039 · 304–319](../../../../../tests/unit/result_cursor_test.cpp#L304) | Callable definition: void nullary_and_constant_routes() | calls runtime, nullary_atom_plan, resize, check; guard check(cursor_matches_reference(runtime,database).empty(),"empty nullary atom emitted an empty tuple…; growth insert, resize; 1 loop sites · [reviewed contract](#b0039) |
| [B0040 · 320–320](../../../../../tests/unit/result_cursor_test.cpp#L320) | Explanatory comments or spacing. |  |
| [B0041 · 321–355](../../../../../tests/unit/result_cursor_test.cpp#L321) | Callable definition: void lease_reads_writes_and_pending_creation() | calls runtime, one_column_plan, resize, insert; guard check(first.active() && second.active() && first.state()==ResultCursorState::active &&; growth insert, resize · [reviewed contract](#b0041) |
| [B0042 · 356–356](../../../../../tests/unit/result_cursor_test.cpp#L356) | Explanatory comments or spacing. |  |
| [B0043 · 357–406](../../../../../tests/unit/result_cursor_test.cpp#L357) | Callable definition: void cursor_moves_and_facade_lifetime() | calls original, one_column_plan, apply, n; guard check(!cursor.active() && moved_cursor.active() && moved_cursor.owner()==owner,; growth emplace, insert, make_unique · [reviewed contract](#b0043) |
| [B0044 · 407–407](../../../../../tests/unit/result_cursor_test.cpp#L407) | Explanatory comments or spacing. |  |
| [B0045 · 408–451](../../../../../tests/unit/result_cursor_test.cpp#L408) | Callable definition: void work_metrics_handtrace_and_cap() | calls runtime, one_column_plan, apply, n; guard check(startup.work==1+steps && startup.route_checks==1 && startup.frame_initializations==steps,; growth insert · [reviewed contract](#b0045) |
| [B0046 · 452–452](../../../../../tests/unit/result_cursor_test.cpp#L452) | Explanatory comments or spacing. |  |
| [B0047 · 453–505](../../../../../tests/unit/result_cursor_test.cpp#L453) | Callable definition: void sql_results_and_exists_mapping() | calls normalized_plan, runtime, std::move, resize; guard check(first.layout().fields().size()==4 && first.layout().same_token(second.layout()),; growth insert, resize · [reviewed contract](#b0047) |
| [B0048 · 506–506](../../../../../tests/unit/result_cursor_test.cpp#L506) | Explanatory comments or spacing. |  |
| [B0049 · 507–570](../../../../../tests/unit/result_cursor_test.cpp#L507) | Callable definition: void sql_constant_only_rows() | calls normalized_plan, check, route, query; guard check(source_plan.route()==PhysicalRoute::tree && source_plan.query().atoms.size()==1 &&; growth insert, resize · [reviewed contract](#b0049) |
| [B0050 · 571–573](../../../../../tests/unit/result_cursor_test.cpp#L571) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0050) |
| [B0051 · 574–594](../../../../../tests/unit/result_cursor_test.cpp#L574) | Callable definition: int main() | calls static_assert, shared_key_and_product_differential, disconnected_products_and_projections, native_chain_differential; guard static_assert(!std::is_copy_constructible_v&lt;SupportRuntime::ResultCursor&gt;);; returns 1 · [reviewed contract](#b0051) |

## B0001

[Lines 1–26](../../../../../tests/unit/result_cursor_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L26:sha256:1e17ca426dd502f7e3cd750b7a38d9adaffa321413598a6fd4c284f9be1c5775
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare result_cursor_test.cpp: include "crown/api/error.hpp", "crown/frontend/bind.hpp", "crown/frontend/normalize.hpp", "crown/planner/lower.hpp", "crown/runtime/physical.hpp", "evaluator.hpp", "native_input.hpp", &lt;cstdint&gt;, &lt;iterator&gt;, &lt;iostream&gt;, &lt;memory&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;variant&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/result_cursor_test.cpp](../../../../../tests/unit/result_cursor_test.cpp), [docs/result_cursors.md](../../../../result_cursors.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 27–29](../../../../../tests/unit/result_cursor_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition,const std::string& message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise a labeled result cursor test failure when a Boolean expectation is false. |
| inputs / outputs | Callable: void check(bool condition,const std::string& message). Inputs: condition and owning message. Output: none on success; false throws std::runtime_error. |
| invariants | The check remains active regardless of assertion build settings. |
| ownership | The fixture owns its PhysicalRuntime, Database, and plans. An active result cursor retains the logical runtime lease; each returned storage::Tuple owns its row, while reference Relations are test-owned materializations. |
| failure | A failed check throws std::runtime_error; error accepts only the requested crown::Error. Other runtime, allocation, and standard exceptions propagate to main and fail the executable. |
| cost | Uses finite synthetic plans and materialized reference relations; the cursor's abstract work counters are distinct from elapsed time and total fixture memory. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/result_cursors.md §Traversal and output rows](../../../../result_cursors.md), [docs/result_cursors.md §Read lease and runtime lifetime](../../../../result_cursors.md), [docs/result_cursors.md §Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md §Work accounting](../../../../result_cursors.md) |

## B0003

[Lines 30–37](../../../../../tests/unit/result_cursor_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void error(Action&& action,std::string_view code)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a callable to throw the selected public runtime Error code. |
| inputs / outputs | Callable: template&lt;class Action&gt; void error(Action&& action,std::string_view code). Inputs: action and expected code. Output: none for matching crown::Error; wrong/no error throws std::runtime_error. |
| invariants | Only crown::Error is caught; other exception types propagate to main. |
| ownership | The fixture owns its PhysicalRuntime, Database, and plans. An active result cursor retains the logical runtime lease; each returned storage::Tuple owns its row, while reference Relations are test-owned materializations. |
| failure | A failed check throws std::runtime_error; error accepts only the requested crown::Error. Other runtime, allocation, and standard exceptions propagate to main and fail the executable. |
| cost | Uses finite synthetic plans and materialized reference relations; the cursor's abstract work counters are distinct from elapsed time and total fixture memory. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/result_cursors.md §Traversal and output rows](../../../../result_cursors.md), [docs/result_cursors.md §Read lease and runtime lifetime](../../../../result_cursors.md), [docs/result_cursors.md §Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md §Work accounting](../../../../result_cursors.md) |

## B0004

[Lines 38–38](../../../../../tests/unit/result_cursor_test.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an int64 Value used by physical and SQL cursor fixtures. |
| inputs / outputs | Callable: Value n(std::int64_t value). Input: signed 64-bit integer. Output: Value containing the same integer. |
| invariants | No numeric coercion or range policy is added by the helper. |
| ownership | The fixture owns its PhysicalRuntime, Database, and plans. An active result cursor retains the logical runtime lease; each returned storage::Tuple owns its row, while reference Relations are test-owned materializations. |
| failure | A failed check throws std::runtime_error; error accepts only the requested crown::Error. Other runtime, allocation, and standard exceptions propagate to main and fail the executable. |
| cost | Uses finite synthetic plans and materialized reference relations; the cursor's abstract work counters are distinct from elapsed time and total fixture memory. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/result_cursors.md §Traversal and output rows](../../../../result_cursors.md), [docs/result_cursors.md §Read lease and runtime lifetime](../../../../result_cursors.md), [docs/result_cursors.md §Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md §Work accounting](../../../../result_cursors.md) |

## B0005

[Lines 39–39](../../../../../tests/unit/result_cursor_test.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value s(std::string value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a string Value used by cursor fixture rows. |
| inputs / outputs | Callable: Value s(std::string value). Input: owning string. Output: Value containing the moved text. |
| invariants | Returned storage owns its bytes independently of the input variable. |
| ownership | The fixture owns its PhysicalRuntime, Database, and plans. An active result cursor retains the logical runtime lease; each returned storage::Tuple owns its row, while reference Relations are test-owned materializations. |
| failure | A failed check throws std::runtime_error; error accepts only the requested crown::Error. Other runtime, allocation, and standard exceptions propagate to main and fail the executable. |
| cost | Uses finite synthetic plans and materialized reference relations; the cursor's abstract work counters are distinct from elapsed time and total fixture memory. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/result_cursors.md §Traversal and output rows](../../../../result_cursors.md), [docs/result_cursors.md §Read lease and runtime lifetime](../../../../result_cursors.md), [docs/result_cursors.md §Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md §Work accounting](../../../../result_cursors.md) |

## B0007

[Lines 41–50](../../../../../tests/unit/result_cursor_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation drain_unique(SupportRuntime::ResultCursor& cursor)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume a result cursor to terminal null and collect its owning rows into a set relation. |
| inputs / outputs | Callable: Relation drain_unique(SupportRuntime::ResultCursor& cursor). Input: active ResultCursor reference. Output: test-owned Relation of unique exported rows. |
| invariants | Each returned tuple must share the cursor's output layout token; duplicate projected rows fail, and exhaustion must close the cursor. |
| ownership | The Relation owns exported copies of every emitted row; cursor remains borrowed through the reference and closes on terminal null. |
| failure | A failed check throws std::runtime_error; error accepts only the requested crown::Error. Other runtime, allocation, and standard exceptions propagate to main and fail the executable. |
| cost | Calls next once per emitted tuple plus terminal checks and stores O(emitted fixture rows) in a test Relation. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/result_cursors.md §Traversal and output rows](../../../../result_cursors.md), [docs/result_cursors.md §Read lease and runtime lifetime](../../../../result_cursors.md), [docs/result_cursors.md §Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md §Work accounting](../../../../result_cursors.md) |

## B0009

[Lines 52–56](../../../../../tests/unit/result_cursor_test.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void insert(PhysicalRuntime& runtime,Database& database,std::uint64_t& sequence,TableId table,Row row)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one physical source-row insertion and mirror it into the independent test Database. |
| inputs / outputs | Callable: void insert(PhysicalRuntime& runtime,Database& database,std::uint64_t& sequence,TableId table,Row row). Inputs: PhysicalRuntime, database, sequence counter, table ID, and row. Output: none. |
| invariants | The sequence increments once; both runtime physical membership and the reference database set must report a new row. |
| ownership | The fixture owns its PhysicalRuntime, Database, and plans. An active result cursor retains the logical runtime lease; each returned storage::Tuple owns its row, while reference Relations are test-owned materializations. |
| failure | A failed check throws std::runtime_error; error accepts only the requested crown::Error. Other runtime, allocation, and standard exceptions propagate to main and fail the executable. |
| cost | Uses finite synthetic plans and materialized reference relations; the cursor's abstract work counters are distinct from elapsed time and total fixture memory. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/result_cursors.md §Traversal and output rows](../../../../result_cursors.md), [docs/result_cursors.md §Read lease and runtime lifetime](../../../../result_cursors.md), [docs/result_cursors.md §Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md §Work accounting](../../../../result_cursors.md) |

## B0011

[Lines 58–65](../../../../../tests/unit/result_cursor_test.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan one_column_plan()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a single native relation query projecting x while ignoring a witness column. |
| inputs / outputs | Callable: PhysicalPlan one_column_plan(). Input: none. Output: lowered PhysicalPlan with one root frame and one output field. |
| invariants | Witness strings do not appear in the head and duplicate source rows with the same x project to one result. |
| ownership | The fixture owns its PhysicalRuntime, Database, and plans. An active result cursor retains the logical runtime lease; each returned storage::Tuple owns its row, while reference Relations are test-owned materializations. |
| failure | A failed check throws std::runtime_error; error accepts only the requested crown::Error. Other runtime, allocation, and standard exceptions propagate to main and fail the executable. |
| cost | Uses finite synthetic plans and materialized reference relations; the cursor's abstract work counters are distinct from elapsed time and total fixture memory. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/result_cursors.md §Traversal and output rows](../../../../result_cursors.md) |

## B0013

[Lines 67–93](../../../../../tests/unit/result_cursor_test.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan shared_key_plan(std::size_t arity)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an N-child tree whose native factors share x and expose separate z/hidden variables. |
| inputs / outputs | Callable: PhysicalPlan shared_key_plan(std::size_t arity). Input: arity. Output: lowered plan with a generalized x root, one native child per factor, and reordered/repeated z head columns. |
| invariants | Arity must be at least two; each child has a distinct z and hidden witness while all children join on x. |
| ownership | The fixture owns its PhysicalRuntime, Database, and plans. An active result cursor retains the logical runtime lease; each returned storage::Tuple owns its row, while reference Relations are test-owned materializations. |
| failure | A failed check throws std::runtime_error; error accepts only the requested crown::Error. Other runtime, allocation, and standard exceptions propagate to main and fail the executable. |
| cost | Constructs O(arity) variables, factors, child IDs, and tree nodes for the supplied arity; the caller test uses only 3 and 8. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_plans.md §Enumeration and result assembly](../../../../physical_plans.md), [docs/result_cursors.md §Traversal and output rows](../../../../result_cursors.md) |

## B0015

[Lines 95–110](../../../../../tests/unit/result_cursor_test.cpp#L95); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan disconnected_plan(std::vector<Output> head)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a three-factor product tree with an empty-scope generalized root and caller-selected head projection. |
| inputs / outputs | Callable: PhysicalPlan disconnected_plan(std::vector&lt;Output&gt; head). Input: head output list. Output: lowered PhysicalPlan. |
| invariants | The factors have disjoint query variables; ignored witness columns do not enter the logical result. |
| ownership | The fixture owns its PhysicalRuntime, Database, and plans. An active result cursor retains the logical runtime lease; each returned storage::Tuple owns its row, while reference Relations are test-owned materializations. |
| failure | A failed check throws std::runtime_error; error accepts only the requested crown::Error. Other runtime, allocation, and standard exceptions propagate to main and fail the executable. |
| cost | Uses finite synthetic plans and materialized reference relations; the cursor's abstract work counters are distinct from elapsed time and total fixture memory. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_plans.md §Enumeration and result assembly](../../../../physical_plans.md) |

## B0017

[Lines 112–128](../../../../../tests/unit/result_cursor_test.cpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan native_chain_plan()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the fixed depth-three native chain r(x,y), s(y,z), t(z,w). |
| inputs / outputs | Callable: PhysicalPlan native_chain_plan(). Input: none. Output: lowered plan with two one-field parent separators and repeated/reordered w outputs. |
| invariants | The second and third relation steps use parent positions 1 for y and z respectively. |
| ownership | The fixture owns its PhysicalRuntime, Database, and plans. An active result cursor retains the logical runtime lease; each returned storage::Tuple owns its row, while reference Relations are test-owned materializations. |
| failure | A failed check throws std::runtime_error; error accepts only the requested crown::Error. Other runtime, allocation, and standard exceptions propagate to main and fail the executable. |
| cost | Uses finite synthetic plans and materialized reference relations; the cursor's abstract work counters are distinct from elapsed time and total fixture memory. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_plans.md §Enumeration and result assembly](../../../../physical_plans.md) |

## B0019

[Lines 130–135](../../../../../tests/unit/result_cursor_test.cpp#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan nullary_atom_plan()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one atom with no logical variables and an ignored physical tag. |
| inputs / outputs | Callable: PhysicalPlan nullary_atom_plan(). Input: none. Output: lowered plan whose native relation is nullary. |
| invariants | An empty source yields no empty tuple; any nonempty set of physical rows yields one nullary set member. |
| ownership | The fixture owns its PhysicalRuntime, Database, and plans. An active result cursor retains the logical runtime lease; each returned storage::Tuple owns its row, while reference Relations are test-owned materializations. |
| failure | A failed check throws std::runtime_error; error accepts only the requested crown::Error. Other runtime, allocation, and standard exceptions propagate to main and fail the executable. |
| cost | Uses finite synthetic plans and materialized reference relations; the cursor's abstract work counters are distinct from elapsed time and total fixture memory. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/result_cursors.md §Traversal and output rows](../../../../result_cursors.md) |

## B0021

[Lines 137–141](../../../../../tests/unit/result_cursor_test.cpp#L137); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan constant_plan(bool contradiction)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a source-free constant truth or contradiction plan. |
| inputs / outputs | Callable: PhysicalPlan constant_plan(bool contradiction). Input: contradiction Boolean. Output: lowered plan from an empty tree. |
| invariants | The flag selects constant_false versus constant_true route behavior without any native source relation. |
| ownership | The fixture owns its PhysicalRuntime, Database, and plans. An active result cursor retains the logical runtime lease; each returned storage::Tuple owns its row, while reference Relations are test-owned materializations. |
| failure | A failed check throws std::runtime_error; error accepts only the requested crown::Error. Other runtime, allocation, and standard exceptions propagate to main and fail the executable. |
| cost | Uses finite synthetic plans and materialized reference relations; the cursor's abstract work counters are distinct from elapsed time and total fixture memory. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/result_cursors.md §Traversal and output rows](../../../../result_cursors.md) |

## B0023

[Lines 143–146](../../../../../tests/unit/result_cursor_test.cpp#L143); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<VariableId> variable_term(const Term& term)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract a VariableId only when one SQL core term uses that variant. |
| inputs / outputs | Callable: std::optional&lt;VariableId&gt; variable_term(const Term& term). Input: Term. Output: optional VariableId, empty for constants. |
| invariants | It does not resolve, normalize, or validate the variable against a catalog. |
| ownership | The fixture owns its PhysicalRuntime, Database, and plans. An active result cursor retains the logical runtime lease; each returned storage::Tuple owns its row, while reference Relations are test-owned materializations. |
| failure | A failed check throws std::runtime_error; error accepts only the requested crown::Error. Other runtime, allocation, and standard exceptions propagate to main and fail the executable. |
| cost | Uses finite synthetic plans and materialized reference relations; the cursor's abstract work counters are distinct from elapsed time and total fixture memory. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/result_cursors.md §Traversal and output rows](../../../../result_cursors.md), [docs/result_cursors.md §Read lease and runtime lifetime](../../../../result_cursors.md), [docs/result_cursors.md §Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md §Work accounting](../../../../result_cursors.md) |

## B0024

[Lines 147–175](../../../../../tests/unit/result_cursor_test.cpp#L147); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
FreeConnexTree sql_tree(const Query& query)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a simple tree for the bound SQL core using the intersection shared by all atom scopes. |
| inputs / outputs | Callable: FreeConnexTree sql_tree(const Query& query). Input: normalized Query. Output: empty tree for contradiction/no atoms, one native node for one atom, otherwise a generalized product root plus native leaves. |
| invariants | This fixture builder is used for the tests' admitted SQL queries; it is not a general tree recognition or optimality procedure. |
| ownership | The fixture owns its PhysicalRuntime, Database, and plans. An active result cursor retains the logical runtime lease; each returned storage::Tuple owns its row, while reference Relations are test-owned materializations. |
| failure | A failed check throws std::runtime_error; error accepts only the requested crown::Error. Other runtime, allocation, and standard exceptions propagate to main and fail the executable. |
| cost | Scans each atom term and computes common variable scopes across the finite query atoms; no minimum-tree search is performed. |
| Design | [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/physical_plans.md §Enumeration and result assembly](../../../../physical_plans.md) |

## B0025

[Lines 176–186](../../../../../tests/unit/result_cursor_test.cpp#L176); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan normalized_plan(std::string_view sql,const Catalog& catalog)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind and normalize one SQL fixture, construct its local tree, and lower it. |
| inputs / outputs | Callable: PhysicalPlan normalized_plan(std::string_view sql,const Catalog& catalog). Inputs: SQL view and Catalog. Output: normalized PhysicalPlan or std::runtime_error containing a binding diagnostic. |
| invariants | Binder and normalizer diagnostics are checked before extraction; the returned plan is built from actual normalized output. |
| ownership | The fixture owns its PhysicalRuntime, Database, and plans. An active result cursor retains the logical runtime lease; each returned storage::Tuple owns its row, while reference Relations are test-owned materializations. |
| failure | A failed check throws std::runtime_error; error accepts only the requested crown::Error. Other runtime, allocation, and standard exceptions propagate to main and fail the executable. |
| cost | Uses finite synthetic plans and materialized reference relations; the cursor's abstract work counters are distinct from elapsed time and total fixture memory. |
| Design | [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0027

[Lines 188–200](../../../../../tests/unit/result_cursor_test.cpp#L188); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation normalized_core_reference(const auto& plan,const Database& physical)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt each physical source row into normalized core tables and materialize the test reference relation. |
| inputs / outputs | Callable: Relation normalized_core_reference(const auto& plan,const Database& physical). Inputs: normalized physical plan and test Database. Output: owning Relation from reference::evaluate. |
| invariants | Every adapter is applied to the complete source row; rejected mappings are skipped and each target table uses set membership. |
| ownership | The Database and resulting Relation own copies; plan adapter spans and each input row are borrowed only during evaluation. |
| failure | A failed check throws std::runtime_error; error accepts only the requested crown::Error. Other runtime, allocation, and standard exceptions propagate to main and fail the executable. |
| cost | Visits every adapter and supplied physical row and materializes mapped core rows in test-owned sets. |
| Design | [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [src/frontend/adapter.cpp](../../../../../src/frontend/adapter.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md](../../../../physical_runtime.md) |

## B0029

[Lines 202–209](../../../../../tests/unit/result_cursor_test.cpp#L202); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation cursor_matches_reference(PhysicalRuntime& runtime,const Database& database)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare a PhysicalRuntime core cursor with the finite materializing reference evaluator. |
| inputs / outputs | Callable: Relation cursor_matches_reference(PhysicalRuntime& runtime,const Database& database). Inputs: runtime and test Database. Output: drained Relation. |
| invariants | Cursor owner and sequence must equal the runtime's committed identity; this comparison materializes only the supplied fixture answer. |
| ownership | The runtime and database are borrowed; the returned Relation owns the materialized reference/cursor rows. |
| failure | A failed check throws std::runtime_error; error accepts only the requested crown::Error. Other runtime, allocation, and standard exceptions propagate to main and fail the executable. |
| cost | Materializes one full reference result and drains one cursor over the same finite database. |
| Design | [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/result_cursors.md §Traversal and output rows](../../../../result_cursors.md) |

## B0031

[Lines 211–235](../../../../../tests/unit/result_cursor_test.cpp#L211); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void shared_key_and_product_differential(std::size_t arity)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare N-ary shared-key cursor output with the reference relation at arities three and eight. |
| inputs / outputs | Callable: void shared_key_and_product_differential(std::size_t arity). Input: arity. Output: none after cursor rows equal the reference and expose 2^arity distinct projected combinations. |
| invariants | Each of arity factors has two visible choices and two hidden duplicate witnesses for x=7 plus one unmatched key row; reordered/repeated head values must agree. |
| ownership | The fixture owns its PhysicalRuntime, Database, and plans. An active result cursor retains the logical runtime lease; each returned storage::Tuple owns its row, while reference Relations are test-owned materializations. |
| failure | A failed check throws std::runtime_error; error accepts only the requested crown::Error. Other runtime, allocation, and standard exceptions propagate to main and fail the executable. |
| cost | Runs the explicit arities 3 and 8; each factor has four shared-key rows plus one unmatched row, and expected projected output cardinality is 2^arity. |
| Design | [tests/unit/result_cursor_test.cpp](../../../../../tests/unit/result_cursor_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/result_cursors.md §Traversal and output rows](../../../../result_cursors.md) |

## B0033

[Lines 237–243](../../../../../tests/unit/result_cursor_test.cpp#L237); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Database disconnected_database()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return three finite physical tables with duplicate logical projections for disconnected product tests. |
| inputs / outputs | Callable: Database disconnected_database(). Input: none. Output: Database containing 3 x-rows, 4 y-rows, and 3 z-rows. |
| invariants | Repeated y and z values differ only in ignored witness strings, so set results collapse those duplicates. |
| ownership | The fixture owns its PhysicalRuntime, Database, and plans. An active result cursor retains the logical runtime lease; each returned storage::Tuple owns its row, while reference Relations are test-owned materializations. |
| failure | A failed check throws std::runtime_error; error accepts only the requested crown::Error. Other runtime, allocation, and standard exceptions propagate to main and fail the executable. |
| cost | Creates exactly 10 physical rows across three tables. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/result_cursors.md §Traversal and output rows](../../../../result_cursors.md), [docs/result_cursors.md §Read lease and runtime lifetime](../../../../result_cursors.md), [docs/result_cursors.md §Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md §Work accounting](../../../../result_cursors.md) |

## B0034

[Lines 244–250](../../../../../tests/unit/result_cursor_test.cpp#L244); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void fill_disconnected(PhysicalRuntime& runtime,const Database& database,std::uint64_t& sequence)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Insert every supplied disconnected database row into its matching runtime table. |
| inputs / outputs | Callable: void fill_disconnected(PhysicalRuntime& runtime,const Database& database,std::uint64_t& sequence). Inputs: runtime, const database, and sequence counter. Output: none. |
| invariants | Each fixture insertion consumes one increasing physical sequence and must report physical_changed. |
| ownership | The fixture owns its PhysicalRuntime, Database, and plans. An active result cursor retains the logical runtime lease; each returned storage::Tuple owns its row, while reference Relations are test-owned materializations. |
| failure | A failed check throws std::runtime_error; error accepts only the requested crown::Error. Other runtime, allocation, and standard exceptions propagate to main and fail the executable. |
| cost | Uses finite synthetic plans and materialized reference relations; the cursor's abstract work counters are distinct from elapsed time and total fixture memory. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/result_cursors.md §Traversal and output rows](../../../../result_cursors.md), [docs/result_cursors.md §Read lease and runtime lifetime](../../../../result_cursors.md), [docs/result_cursors.md §Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md §Work accounting](../../../../result_cursors.md) |

## B0035

[Lines 251–268](../../../../../tests/unit/result_cursor_test.cpp#L251); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void disconnected_products_and_projections()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the three-factor product, reordered/repeated head mapping, and projection deduplication. |
| inputs / outputs | Callable: void disconnected_products_and_projections(). Input: none. Output: none after two lowered plans match the finite reference evaluator. |
| invariants | The full projection has 12 distinct rows; projecting only x collapses hidden y/z combinations to {1,2}. |
| ownership | The fixture owns its PhysicalRuntime, Database, and plans. An active result cursor retains the logical runtime lease; each returned storage::Tuple owns its row, while reference Relations are test-owned materializations. |
| failure | A failed check throws std::runtime_error; error accepts only the requested crown::Error. Other runtime, allocation, and standard exceptions propagate to main and fail the executable. |
| cost | Runs the finite 3 x 4 x 3 input fixture twice; the full head has 12 distinct rows and x-only projection has two. |
| Design | [tests/unit/result_cursor_test.cpp](../../../../../tests/unit/result_cursor_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/result_cursors.md §Traversal and output rows](../../../../result_cursors.md) |

## B0037

[Lines 270–302](../../../../../tests/unit/result_cursor_test.cpp#L270); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void native_chain_differential()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check depth-three parent separators and cursor output against the materializing evaluator. |
| inputs / outputs | Callable: void native_chain_differential(). Input: none. Output: none after 2 r, 3 s, and 5 t rows yield five distinct repeated-head results. |
| invariants | The test checks parent step indexes and selected separator field positions before draining the cursor. |
| ownership | The fixture owns its PhysicalRuntime, Database, and plans. An active result cursor retains the logical runtime lease; each returned storage::Tuple owns its row, while reference Relations are test-owned materializations. |
| failure | A failed check throws std::runtime_error; error accepts only the requested crown::Error. Other runtime, allocation, and standard exceptions propagate to main and fail the executable. |
| cost | Loads exactly 2, 3, and 5 rows in its three relations and checks five output tuples. |
| Design | [tests/unit/result_cursor_test.cpp](../../../../../tests/unit/result_cursor_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/result_cursors.md §Traversal and output rows](../../../../result_cursors.md) |

## B0039

[Lines 304–319](../../../../../tests/unit/result_cursor_test.cpp#L304); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void nullary_and_constant_routes()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare nullary native, constant-true, and constant-false cursor results with the reference evaluator. |
| inputs / outputs | Callable: void nullary_and_constant_routes(). Input: none. Output: none after empty/nonempty source and both contradiction flags. |
| invariants | The nonempty nullary source returns one empty tuple regardless of two distinct physical tags; contradiction returns no tuple. |
| ownership | The fixture owns its PhysicalRuntime, Database, and plans. An active result cursor retains the logical runtime lease; each returned storage::Tuple owns its row, while reference Relations are test-owned materializations. |
| failure | A failed check throws std::runtime_error; error accepts only the requested crown::Error. Other runtime, allocation, and standard exceptions propagate to main and fail the executable. |
| cost | Uses finite synthetic plans and materialized reference relations; the cursor's abstract work counters are distinct from elapsed time and total fixture memory. |
| Design | [tests/unit/result_cursor_test.cpp](../../../../../tests/unit/result_cursor_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/result_cursors.md §Traversal and output rows](../../../../result_cursors.md) |

## B0041

[Lines 321–355](../../../../../tests/unit/result_cursor_test.cpp#L321); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void lease_reads_writes_and_pending_creation()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check simultaneous core cursors, read APIs, writer exclusion, pending-writer exclusion, cancellation, and row ownership. |
| inputs / outputs | Callable: void lease_reads_writes_and_pending_creation(). Input: none. Output: none after two cursors share one committed epoch and the next sequence commits after leases close. |
| invariants | Cancelling one cursor leaves the other lease active; prepared update destruction restores readiness without consuming its sequence. |
| ownership | Each active cursor owns a lease to logical runtime state; the first returned Tuple owns its row after cursor cancel and later update. |
| failure | A failed check throws std::runtime_error; error accepts only the requested crown::Error. Other runtime, allocation, and standard exceptions propagate to main and fail the executable. |
| cost | Uses one source row, two simultaneous cursors, one cancelled prepared input, and one committed input. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/result_cursors.md §Read lease and runtime lifetime](../../../../result_cursors.md), [docs/result_cursors.md §Cursor states and close behavior](../../../../result_cursors.md) |

## B0043

[Lines 357–406](../../../../../tests/unit/result_cursor_test.cpp#L357); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cursor_moves_and_facade_lifetime()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check cursor move construction/assignment, runtime facade moves/destruction, and destructor lease release. |
| inputs / outputs | Callable: void cursor_moves_and_facade_lifetime(). Input: none. Output: none after three finite lifecycle scenarios. |
| invariants | A live cursor retains the logical support owner; a returned Tuple owns its row after cursor/runtime closure. |
| ownership | Cursor moves transfer the lease. A returned Tuple owns its row independently; facade destruction does not invalidate the cursor's retained logical owner. |
| failure | A failed check throws std::runtime_error; error accepts only the requested crown::Error. Other runtime, allocation, and standard exceptions propagate to main and fail the executable. |
| cost | Exercises three bounded cursor/runtime lifetime scenarios with one row each. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/result_cursors.md §Read lease and runtime lifetime](../../../../result_cursors.md), [docs/result_cursors.md §Cursor states and close behavior](../../../../result_cursors.md) |

## B0045

[Lines 408–451](../../../../../tests/unit/result_cursor_test.cpp#L408); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void work_metrics_handtrace_and_cap()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check a one-row cursor's startup/result/termination work hand trace and failure under a cumulative cap of four. |
| inputs / outputs | Callable: void work_metrics_handtrace_and_cap(). Input: none. Output: none after exact counters match startup 1+steps, result work 7, terminal work 3, and failed next work 2. |
| invariants | The test's exact values are for the fixed one-column plan; a failed next closes the lease and later next reports invalid_cursor. |
| ownership | The fixture owns its PhysicalRuntime, Database, and plans. An active result cursor retains the logical runtime lease; each returned storage::Tuple owns its row, while reference Relations are test-owned materializations. |
| failure | A failed check throws std::runtime_error; error accepts only the requested crown::Error. Other runtime, allocation, and standard exceptions propagate to main and fail the executable. |
| cost | Checks one row-producing call, one terminal call, and one work-limited failure on a one-step plan. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/result_cursors.md §Work accounting](../../../../result_cursors.md), [docs/result_cursors.md §Cursor states and close behavior](../../../../result_cursors.md) |

## B0047

[Lines 453–505](../../../../../tests/unit/result_cursor_test.cpp#L453); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sql_results_and_exists_mapping()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare normalized SQL output cursors with frontend::map_sql_result for repeated columns, constants, epochs, and EXISTS. |
| inputs / outputs | Callable: void sql_results_and_exists_mapping(). Input: none. Output: none after the finite two-table and one-table SQL fixtures. |
| invariants | Core results remain separately comparable to the normalized core relation; EXISTS maps an empty/nonempty core to one Boolean row. |
| ownership | SQL/core cursors own logical read leases; retained output Tuples own mapped values and the shared output layout token. |
| failure | A failed check throws std::runtime_error; error accepts only the requested crown::Error. Other runtime, allocation, and standard exceptions propagate to main and fail the executable. |
| cost | Uses six left/right source rows, one extra update row, and a one-row EXISTS source; reference mapping materializes only these fixtures. |
| Design | [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/result_cursors.md §Traversal and output rows](../../../../result_cursors.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0049

[Lines 507–570](../../../../../tests/unit/result_cursor_test.cpp#L507); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sql_constant_only_rows()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check SQL constant projection over a nullary source, a source-free true route, and a contradiction route. |
| inputs / outputs | Callable: void sql_constant_only_rows(). Input: none. Output: none after empty/nonempty source cases and cursor layout-token checks. |
| invariants | Two source derivations collapse to one nullary core row and one constant SQL row; source-free true emits one, false emits none. |
| ownership | Returned SQL Tuples own constant values and retain the shared immutable output layout identity after cursor completion. |
| failure | A failed check throws std::runtime_error; error accepts only the requested crown::Error. Other runtime, allocation, and standard exceptions propagate to main and fail the executable. |
| cost | Uses two physical rows for a nullary source plus source-free true and contradiction plans; answer sizes are at most one. |
| Design | [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/result_cursors.md §Traversal and output rows](../../../../result_cursors.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0050

[Lines 571–573](../../../../../tests/unit/result_cursor_test.cpp#L571); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L571-L573:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in result_cursor_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/result_cursor_test.cpp](../../../../../tests/unit/result_cursor_test.cpp), [docs/result_cursors.md](../../../../result_cursors.md), [docs/code_review.md](../../../../code_review.md) |

## B0051

[Lines 574–594](../../../../../tests/unit/result_cursor_test.cpp#L574); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the cursor differential, lifecycle, work-accounting, and SQL mapping cases. |
| inputs / outputs | Callable: int main(). Input: none. Output: zero after printing PASS, or one after reporting the first exception. |
| invariants | The executable invokes the fixed arity, database, lifecycle, and SQL fixtures listed in its nine test calls. |
| ownership | The fixture owns its PhysicalRuntime, Database, and plans. An active result cursor retains the logical runtime lease; each returned storage::Tuple owns its row, while reference Relations are test-owned materializations. |
| failure | A failed check throws std::runtime_error; error accepts only the requested crown::Error. Other runtime, allocation, and standard exceptions propagate to main and fail the executable. |
| cost | Invokes nine fixed differential/lifecycle/SQL cases; all reference relations are bounded fixture outputs, and no wall-clock or delay claim is measured. |
| Design | [tests/unit/result_cursor_test.cpp](../../../../../tests/unit/result_cursor_test.cpp), [docs/result_cursors.md §Work accounting](../../../../result_cursors.md), [docs/result_cursors.md §Read lease and runtime lifetime](../../../../result_cursors.md) |
