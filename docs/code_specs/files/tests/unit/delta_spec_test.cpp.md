# `tests/unit/delta_spec_test.cpp` — block usage map

[Source](../../../../../tests/unit/delta_spec_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `03ba740907bd3ed3d5ef8910c55a4a431ad5b1e444f71f3a3a0b9c6182e75590`. 1232 lines partitioned into 54 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–23](../../../../../tests/unit/delta_spec_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 24–26](../../../../../tests/unit/delta_spec_test.cpp#L24) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 27–27](../../../../../tests/unit/delta_spec_test.cpp#L27) | Explanatory comments or spacing. |  |
| [B0004 · 28–38](../../../../../tests/unit/delta_spec_test.cpp#L28) | Callable definition: template &lt;class Action&gt; void expect_error(Action&& action, std::string_view code) | calls action, check, code, std::string; guard check(error.code() == code, · [reviewed contract](#b0004) |
| [B0005 · 39–39](../../../../../tests/unit/delta_spec_test.cpp#L39) | Explanatory comments or spacing. |  |
| [B0006 · 40–40](../../../../../tests/unit/delta_spec_test.cpp#L40) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0006) |
| [B0007 · 41–41](../../../../../tests/unit/delta_spec_test.cpp#L41) | Callable definition: Value s(std::string value) | calls ; returns value · [reviewed contract](#b0007) |
| [B0008 · 42–42](../../../../../tests/unit/delta_spec_test.cpp#L42) | Callable definition: Value b(bool value) | calls ; returns value · [reviewed contract](#b0008) |
| [B0009 · 43–43](../../../../../tests/unit/delta_spec_test.cpp#L43) | Explanatory comments or spacing. |  |
| [B0010 · 44–49](../../../../../tests/unit/delta_spec_test.cpp#L44) | Type/record definition: struct Fixture |  · [reviewed contract](#b0010) |
| [B0011 · 50–50](../../../../../tests/unit/delta_spec_test.cpp#L50) | Explanatory comments or spacing. |  |
| [B0012 · 51–55](../../../../../tests/unit/delta_spec_test.cpp#L51) | Callable definition: VariableSet variable_set(std::initializer_list&lt;std::size_t&gt; values) | calls insert; returns result; growth insert; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 56–59](../../../../../tests/unit/delta_spec_test.cpp#L56) | Explanatory comments or spacing. | source comment (unverified): // Convert one physical table row to the exact, set-valued occurrence row the · [reviewed contract](#b0013) |
| [B0014 · 60–78](../../../../../tests/unit/delta_spec_test.cpp#L60) | Callable definition: std::optional&lt;Row&gt; occurrence_row(const Atom& atom, const Row& physical) | calls size, emplace, reserve, push_back; returns std::nullopt; std::nullopt; growth emplace, push_back, reserve; 2 loop sites; source comment (unverified): // Convert one physical table row to the exact, set-valued occurrence row the · [reviewed contract](#b0014) |
| [B0015 · 79–79](../../../../../tests/unit/delta_spec_test.cpp#L79) | Explanatory comments or spacing. |  |
| [B0016 · 80–100](../../../../../tests/unit/delta_spec_test.cpp#L80) | Callable definition: std::vector&lt;Relation&gt; native_inputs(const Fixture& fixture) | calls result, size, seen, check; guard check(node.occurrence.has_value(), "native tree node has no occurrence");; returns value; result; growth insert; 2 loop sites · [reviewed contract](#b0016) |
| [B0017 · 101–101](../../../../../tests/unit/delta_spec_test.cpp#L101) | Explanatory comments or spacing. |  |
| [B0018 · 102–107](../../../../../tests/unit/delta_spec_test.cpp#L102) | Callable definition: Snapshot snapshot(const Fixture& fixture) | calls planner::validate_tree, check, recompute, native_inputs; guard check(checked.valid, "fixture has an invalid free-connex tree");; returns recompute(fixture.catalog, fixture.query, fixture.tree, · [reviewed contract](#b0018) |
| [B0019 · 108–111](../../../../../tests/unit/delta_spec_test.cpp#L108) | Explanatory comments or spacing. | source comment (unverified): // Make an alias-prefix database: each query occurrence gets a fresh table, · [reviewed contract](#b0019) |
| [B0020 · 112–128](../../../../../tests/unit/delta_spec_test.cpp#L112) | Callable definition: std::pair&lt;std::pair&lt;Catalog, Query&gt;, Database&gt; occurrence_expansion( const Fixture& fixture) | calls size, at, std::to_string, push_back; returns {{std::move(catalog), std::move(query)}, std::move(database)}; growth push_back; 1 loop sites; source comment (unverified): // Make an alias-prefix database: each query occurrence gets a fresh table, · [reviewed contract](#b0020) |
| [B0021 · 129–129](../../../../../tests/unit/delta_spec_test.cpp#L129) | Explanatory comments or spacing. |  |
| [B0022 · 130–141](../../../../../tests/unit/delta_spec_test.cpp#L130) | Callable definition: Relation exact_delta(const Relation& before, const Relation& after, SetOperation operation) | calls std::set_difference, begin, end, std::inserter; returns result; growth insert · [reviewed contract](#b0022) |
| [B0023 · 142–142](../../../../../tests/unit/delta_spec_test.cpp#L142) | Explanatory comments or spacing. |  |
| [B0024 · 143–145](../../../../../tests/unit/delta_spec_test.cpp#L143) | Callable definition: Relation as_set(const std::vector&lt;Row&gt;& rows) | calls Relation, begin, end; returns Relation(rows.begin(), rows.end()) · [reviewed contract](#b0024) |
| [B0025 · 146–146](../../../../../tests/unit/delta_spec_test.cpp#L146) | Explanatory comments or spacing. |  |
| [B0026 · 147–168](../../../../../tests/unit/delta_spec_test.cpp#L147) | Callable definition: Relation project_answer_to_scope(const Relation& answer, const Snapshot& query_snapshot, const std::vector&lt;VariableId&gt;& scope) | calls size, emplace, reserve, find; guard check(found != assignment.end(), "visible factor variable is absent from answer head");; returns result; growth emplace, insert, push_back, reserve; 4 loop sites · [reviewed contract](#b0026) |
| [B0027 · 169–169](../../../../../tests/unit/delta_spec_test.cpp#L169) | Explanatory comments or spacing. |  |
| [B0028 · 170–184](../../../../../tests/unit/delta_spec_test.cpp#L170) | Callable definition: std::string show(const Row& row) | calls size, std::visit, constexpr, to_string; returns @ + value + @; value ? @ : @; 1 loop sites · [reviewed contract](#b0028) |
| [B0029 · 185–185](../../../../../tests/unit/delta_spec_test.cpp#L185) | Explanatory comments or spacing. |  |
| [B0030 · 186–191](../../../../../tests/unit/delta_spec_test.cpp#L186) | Type/record definition: struct CheckedTransition |  · [reviewed contract](#b0030) |
| [B0031 · 192–192](../../../../../tests/unit/delta_spec_test.cpp#L192) | Explanatory comments or spacing. |  |
| [B0032 · 193–271](../../../../../tests/unit/delta_spec_test.cpp#L193) | Callable definition: CheckedTransition check_step(const Fixture& before_fixture, const Fixture& after_fixture, SetOperation operation, const std::stri… | calls check, size, snapshot, reference::evaluate; guard check(before_fixture.catalog.tables.size() == after_fixture.catalog.tables.size() &&; returns {std::move(transition), before_answer, after_answer, expected}; 1 loop sites · [reviewed contract](#b0032) |
| [B0033 · 272–272](../../../../../tests/unit/delta_spec_test.cpp#L272) | Explanatory comments or spacing. |  |
| [B0034 · 273–279](../../../../../tests/unit/delta_spec_test.cpp#L273) | Callable definition: Fixture one_table_fixture(std::string name, std::vector&lt;Column&gt; columns, Query query, FreeConnexTree tree, Relation rows) | calls std::move; returns {std::move(catalog), std::move(query), std::move(tree), · [reviewed contract](#b0034) |
| [B0035 · 280–280](../../../../../tests/unit/delta_spec_test.cpp#L280) | Explanatory comments or spacing. |  |
| [B0036 · 281–335](../../../../../tests/unit/delta_spec_test.cpp#L281) | Callable definition: void hidden_projection_and_physical_counts() | calls one_table_fixture, n, insert, std::move; guard check(step.before_answer == step.after_answer &&; growth insert · [reviewed contract](#b0036) |
| [B0037 · 336–336](../../../../../tests/unit/delta_spec_test.cpp#L336) | Explanatory comments or spacing. |  |
| [B0038 · 337–419](../../../../../tests/unit/delta_spec_test.cpp#L337) | Callable definition: void root_and_ancestor_partitions() | calls n, clear, std::move, check_step; guard check(removed.expected_delta == Relation{{n(1), n(10)}} &&; growth insert; source comment (unverified): // The child has an empty separator to the root. Its first key can become · [reviewed contract](#b0038) |
| [B0039 · 420–420](../../../../../tests/unit/delta_spec_test.cpp#L420) | Explanatory comments or spacing. |  |
| [B0040 · 421–481](../../../../../tests/unit/delta_spec_test.cpp#L421) | Callable definition: void deep_and_dead_witnesses() | calls n, insert, std::move, check_step; guard check(old_snapshot.factors.front().rows == new_snapshot.factors.front().rows &&; growth insert · [reviewed contract](#b0040) |
| [B0041 · 482–482](../../../../../tests/unit/delta_spec_test.cpp#L482) | Explanatory comments or spacing. |  |
| [B0042 · 483–577](../../../../../tests/unit/delta_spec_test.cpp#L483) | Callable definition: void root_activation_boolean_and_constants() | calls n, insert, std::move, check_step; guard check(activation.expected_delta == Relation{{n(3), n(30)}} &&; growth insert; 1 loop sites · [reviewed contract](#b0042) |
| [B0043 · 578–578](../../../../../tests/unit/delta_spec_test.cpp#L578) | Explanatory comments or spacing. |  |
| [B0044 · 579–716](../../../../../tests/unit/delta_spec_test.cpp#L579) | Callable definition: void alias_predicate_count_only_routes() | calls n, occurrence_expansion, check, reference::evaluate; guard check(reference::evaluate(prefix0.catalog, prefix0.query,; growth insert; source comment (unverified): // Insert status 2: alias A is filtered; alias B creates the first answer. · [reviewed contract](#b0044) |
| [B0045 · 717–717](../../../../../tests/unit/delta_spec_test.cpp#L717) | Explanatory comments or spacing. |  |
| [B0046 · 718–959](../../../../../tests/unit/delta_spec_test.cpp#L718) | Callable definition: void products_aliases_and_heads() | calls push_back, std::to_string, n, variable_set; guard check(step.expected_delta.size() == expected_size &&; growth insert, push_back; 3 loop sites; source comment (unverified): // Two aliases of one base table have the same scope and change together. · [reviewed contract](#b0046) |
| [B0047 · 960–960](../../../../../tests/unit/delta_spec_test.cpp#L960) | Explanatory comments or spacing. |  |
| [B0048 · 961–1110](../../../../../tests/unit/delta_spec_test.cpp#L961) | Callable definition: void exhaustive_tiny_domains() | calls n, size, insert, one_table_fixture; growth insert; 16 loop sites; source comment (unverified): // Projected R(x,z) -&gt; S(z,y), head x. The z separator stays hidden, so · [reviewed contract](#b0048) |
| [B0049 · 1111–1111](../../../../../tests/unit/delta_spec_test.cpp#L1111) | Explanatory comments or spacing. |  |
| [B0050 · 1112–1144](../../../../../tests/unit/delta_spec_test.cpp#L1112) | Callable definition: void simultaneous_projection_collision() | calls n, insert, std::move, check_step; guard check(inserted.expected_delta == Relation{{n(4)}} &&; growth insert · [reviewed contract](#b0050) |
| [B0051 · 1145–1145](../../../../../tests/unit/delta_spec_test.cpp#L1145) | Explanatory comments or spacing. |  |
| [B0052 · 1146–1211](../../../../../tests/unit/delta_spec_test.cpp#L1146) | Callable definition: void rejects_invalid_inputs() | calls insert, n, std::move, snapshot; guard check(valid_insert.rows == std::vector&lt;Row&gt;{{n(1)}},; growth insert, push_back · [reviewed contract](#b0052) |
| [B0053 · 1212–1214](../../../../../tests/unit/delta_spec_test.cpp#L1212) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0053) |
| [B0054 · 1215–1232](../../../../../tests/unit/delta_spec_test.cpp#L1215) | Callable definition: int main() | calls hidden_projection_and_physical_counts, root_and_ancestor_partitions, deep_and_dead_witnesses, root_activation_boolean_and_constants; returns 0; 1 · [reviewed contract](#b0054) |

## B0001

[Lines 1–23](../../../../../tests/unit/delta_spec_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L23:sha256:b37abf4ad5af3137a682724d8b895372d6f1e410ee55aa366b24cb221e000bf2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare delta_spec_test.cpp: include "crown/api/error.hpp", "crown/planner/verify.hpp", "delta_model.hpp", "evaluator.hpp", &lt;algorithm&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;iterator&gt;, &lt;map&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 24–26](../../../../../tests/unit/delta_spec_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn a failed specification assertion into a test exception. |
| inputs / outputs | Accepts a Boolean and const std::string diagnostic; returns on true and throws runtime_error with the diagnostic on false. |
| invariants | The helper body only branches on the Boolean. Diagnostic expressions and any temporary std::string are formed before entry, even when the assertion succeeds. |
| ownership | Borrows the already materialized message for the call; an exception owns its error text. |
| failure | False throws; message/exception allocation may fail; no condition is caught. |
| cost | One condition branch. Caller-side diagnostic concatenation or literal-to-string materialization is separate test-harness work and can allocate on passing assertions. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp) |

## B0004

[Lines 28–38](../../../../../tests/unit/delta_spec_test.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action> void expect_error(Action&& action, std::string_view code)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one operation to throw the expected CROWN Error code. |
| inputs / outputs | Binds the callable through Action&& but invokes the named parameter with action(), an lvalue call expression; it does not forward the parameter. Catches crown::Error, compares error.code() with the requested string_view, then returns on a match. |
| invariants | Only crown::Error is expected; a wrong code throws from check inside the catch, absence of an error throws runtime_error, and other exception types propagate. |
| ownership | Borrows callable and code view; caught exception/message are local to the helper. |
| failure | Wrong code or no CROWN Error fails; unrelated exceptions propagate. |
| cost | One action invocation and catch/compare. Diagnostic string concatenation for mismatch/no-error paths is built eagerly at the corresponding call expression; errors are not swallowed. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp), [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp) |

## B0006

[Lines 40–40](../../../../../tests/unit/delta_spec_test.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an int64 model Value. |
| inputs / outputs | Returns the signed integer wrapped as Value. |
| invariants | No range conversion beyond the declared int64 input. |
| ownership | Returns an owning variant value. |
| failure | No helper-level error handling. |
| cost | Fixed variant construction; no relation/runtime work. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp) |

## B0007

[Lines 41–41](../../../../../tests/unit/delta_spec_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value s(std::string value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a string model Value by moving a string. |
| inputs / outputs | Moves its string argument into Value and returns it. |
| invariants | The resulting alternative is string, with exact input text. |
| ownership | The returned Value owns string content; the parameter is consumed by move. |
| failure | String/variant allocation exceptions propagate. |
| cost | One move into the variant; payload allocation depends on input length and string capacity. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp), [exact paper reference](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p2266r3.html), [exact paper reference](https://isocpp.org/files/papers/N4971.pdf) |

## B0008

[Lines 42–42](../../../../../tests/unit/delta_spec_test.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value b(bool value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a Boolean model Value. |
| inputs / outputs | Returns the Boolean wrapped as Value. |
| invariants | Keeps bool distinct from numeric alternatives in exact type comparisons. |
| ownership | Returns a value object. |
| failure | No helper-level error handling. |
| cost | Fixed variant construction. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp) |

## B0010

[Lines 44–49](../../../../../tests/unit/delta_spec_test.cpp#L44); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fixture
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bundle one small relational fixture for the test-only transition model. |
| inputs / outputs | Stores Catalog, Query, FreeConnexTree, and Database by value. |
| invariants | The snapshot/model helpers read this fixture; it is not a maintained runtime or native session. |
| ownership | The aggregate owns its catalog/query/tree/database containers and values. |
| failure | Member construction/copy/move failures propagate. |
| cost | Container copy/move cost depends on fixture size; no incremental runtime data structure is stored here. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp), [tests/reference/delta_model.hpp](../../../../../tests/reference/delta_model.hpp) |

## B0012

[Lines 51–55](../../../../../tests/unit/delta_spec_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
VariableSet variable_set(std::initializer_list<std::size_t> values)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a sorted set of VariableIds from numeric indices. |
| inputs / outputs | Inserts each initializer-list value as VariableId into VariableSet and returns it. |
| invariants | VariableSet de-duplicates repeated IDs and exposes its ordered-set iteration order. |
| ownership | Returned set owns nodes; initializer list is borrowed during the call. |
| failure | Allocator failures propagate. |
| cost | One ordered-set insertion per supplied index; allocation and comparison work depend on set size. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp) |

## B0013

[Lines 56–59](../../../../../tests/unit/delta_spec_test.cpp#L56); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L56-L59:sha256:b3e94505a5c1bc9ab21978836f15c4854493b465a921fa9003c5a2471c83850c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Convert one physical table row to the exact, set-valued occurrence row the model receives. Repeated variables and constants are handled like the A04 evaluator; ignored columns never enter a native E factor. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 60–78](../../../../../tests/unit/delta_spec_test.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<Row> occurrence_row(const Atom& atom, const Row& physical)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project one physical row to the occurrence variables that satisfy its repeated-variable and literal terms. |
| inputs / outputs | Walks atom terms by physical column, records variable assignments in a map, returns nullopt on a repeated-variable conflict or literal mismatch, otherwise returns values in sorted VariableId map order. Ignored columns are omitted. |
| invariants | The implementation assumes the physical row is aligned to atom terms and uses unchecked physical\[column\] indexing. A repeated variable must agree within the row; a constant must equal its field. The output is a set-valued occurrence tuple, not the original physical row. |
| ownership | Reads atom/row by reference; result Row owns copied Value fields and the temporary ordered assignment owns its nodes. |
| failure | Mismatch is represented as nullopt. Width and scalar-type validation are not performed here: a short row can cause out-of-bounds vector access, while extra columns are ignored; allocation failures propagate. |
| cost | Visits each atom term, uses ordered-map assignment/lookups and copies matched visible values; cost depends on term count, distinct variables, and scalar payloads. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp) |

## B0016

[Lines 80–100](../../../../../tests/unit/delta_spec_test.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Relation> native_inputs(const Fixture& fixture)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct per-native-node occurrence inputs from the fixture database. |
| inputs / outputs | Allocates one Relation per tree node, validates each native occurrence ID is present and unique, scans its physical base-table rows, applies occurrence_row, and inserts matching projected tuples. Finally requires every query occurrence was covered. |
| invariants | Generalized nodes have no external input rows; all query atoms must map exactly once to native nodes. Physical duplicates collapse in each Relation. |
| ownership | Returned vector and relations own projected rows. The fixture database and tree are borrowed. |
| failure | Missing/repeated/out-of-range occurrences fail via check; malformed DB indexing/allocation errors propagate. |
| cost | Scans each native occurrence’s entire physical table and performs map/set projections and deduplication; repeated aliases rescan/copy their base rows independently. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp), [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp), [docs/delta_transition_spec.md](../../../../delta_transition_spec.md) |

## B0018

[Lines 102–107](../../../../../tests/unit/delta_spec_test.cpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Snapshot snapshot(const Fixture& fixture)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate the fixture tree and recompute a test-only E snapshot from native inputs. |
| inputs / outputs | Calls planner::validate_tree, builds native input relations, then calls reference::delta::recompute and returns Snapshot. |
| invariants | The validation routine is shared planner validation; subtree assignment joins and factor reconstruction are the separate materializing test model, not production DeltaRuntime. |
| ownership | Returned snapshot owns factor schemas/rows; fixture is borrowed. |
| failure | Invalid tree fails the assertion; model error/allocation exceptions propagate. |
| cost | Each call validates the tree twice: snapshot calls planner::validate_tree directly, then reference::delta::recompute calls it again. It also scans native rows and performs full subtree assignment joins; intermediate assignment sets and projected factor rows are materialized. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp), [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/delta_transition_spec.md](../../../../delta_transition_spec.md) |

## B0019

[Lines 108–111](../../../../../tests/unit/delta_spec_test.cpp#L108); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L108-L111:sha256:a2aaa7e94aed8af394f6988e6a0470991cc2bd84aea803dd75c4f268d5d9579c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Make an alias-prefix database: each query occurrence gets a fresh table, with the same physical rows as its original base table. This lets the independent A04 evaluator check alias-local occurrence expansion directly. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0020

[Lines 112–128](../../../../../tests/unit/delta_spec_test.cpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::pair<std::pair<Catalog, Query>, Database> occurrence_expansion( const Fixture& fixture)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create occurrence-local catalog/database aliases for an A04 comparison. |
| inputs / outputs | For every query atom, appends a copied base-table definition under a suffixed name, copies that physical table’s rows, remaps the atom table ID, and returns the new catalog/query and database. |
| invariants | Each occurrence gets a distinct table ID even when source aliases shared one physical table. Logical occurrence predicates remain in the copied query. |
| ownership | Returned catalog/query/database own copied table metadata, atoms, and row sets; fixture is borrowed. |
| failure | Copy/string/container allocation failures propagate. |
| cost | Loops over all occurrences and copies each referenced physical table’s entire relation; repeated aliases multiply copied rows and storage. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0022

[Lines 130–141](../../../../../tests/unit/delta_spec_test.cpp#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation exact_delta(const Relation& before, const Relation& after, SetOperation operation)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute exact before/after result-set difference for one declared sign. |
| inputs / outputs | For insert uses ordered set_difference(after,before); for erase uses set_difference(before,after), returning a Relation. |
| invariants | Inputs are sorted Relations. Caller chooses insert/erase consistently with the endpoint transition; the helper does not validate monotonicity. |
| ownership | Returned Relation owns copied output rows; inputs are borrowed. |
| failure | Unknown SetOperation falls through to the erase branch; callers constrain sign. Allocations propagate. |
| cost | Linear merge-style traversal over the ordered input sets plus output relation node/value allocation for emitted tuples. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp) |

## B0024

[Lines 143–145](../../../../../tests/unit/delta_spec_test.cpp#L143); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation as_set(const std::vector<Row>& rows)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert an output-row vector into a set-valued Relation. |
| inputs / outputs | Constructs Relation from the vector’s begin/end iterators. |
| invariants | Repeated rows collapse because Relation is a set; other code separately checks vector cardinality when duplicates matter. |
| ownership | Returned Relation owns its row values. |
| failure | Allocation/copy exceptions propagate. |
| cost | Inserts each vector row into the ordered set; performs copies and de-duplication work. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp) |

## B0026

[Lines 147–168](../../../../../tests/unit/delta_spec_test.cpp#L147); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation project_answer_to_scope(const Relation& answer, const Snapshot& query_snapshot, const std::vector<VariableId>& scope)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project whole-query answers onto one visible factor scope. |
| inputs / outputs | Maps query head variables to output positions, reconstructs each answer’s variable assignment, projects the requested variables, and inserts each projected row into a Relation. |
| invariants | Each scope variable must occur in query_snapshot.head. Duplicate head fields map to the first position; query answers must have matching head width. |
| ownership | Returned Relation owns projected rows; per-answer assignment maps and projected rows are temporary. |
| failure | Missing variable fails via check; malformed answer width or allocation errors propagate. |
| cost | Builds a head-position map, then for every answer allocates/populates an assignment and projected row and inserts into a set; work grows with answer count, head width, scope width, and output size. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp), [tests/reference/delta_model.hpp](../../../../../tests/reference/delta_model.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/delta_transition_spec.md](../../../../delta_transition_spec.md) |

## B0028

[Lines 170–184](../../../../../tests/unit/delta_spec_test.cpp#L170); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string show(const Row& row)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Format a Row for diagnostic trace output. |
| inputs / outputs | Returns bracketed comma-separated values using a scalar-type visitor; strings are surrounded with quotes, dates/decimals use their text conversion, and numeric/bool values use standard formatting. |
| invariants | This is diagnostic formatting, not an escaped or round-trippable serialization format. |
| ownership | Returned std::string owns formatted bytes; input row is borrowed. |
| failure | Formatting/string allocation failures propagate. |
| cost | Visits and formats every scalar and appends to a growing string; payload width and row arity determine work. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp) |

## B0030

[Lines 186–191](../../../../../tests/unit/delta_spec_test.cpp#L186); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CheckedTransition
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the complete outputs and oracle deltas for one checked model transition. |
| inputs / outputs | Stores Transition, before-answer, after-answer, and expected-delta Relations by value. |
| invariants | The struct preserves both model transition detail and whole-query oracle endpoints for caller assertions. |
| ownership | All relation/transition containers are owned values; construction can copy relation data. |
| failure | Member copy/move allocation failures propagate. |
| cost | Holding before/after/expected result sets alongside transition fragments can duplicate substantial fixture rows. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp), [tests/reference/delta_model.hpp](../../../../../tests/reference/delta_model.hpp) |

## B0032

[Lines 193–271](../../../../../tests/unit/delta_spec_test.cpp#L193); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CheckedTransition check_step(const Fixture& before_fixture, const Fixture& after_fixture, SetOperation operation, const std::string& label)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Cross-check one same-sign model partition against independent whole-query A04 answers and live projections. |
| inputs / outputs | Validates unchanged fixture shape; computes before/after snapshots, whole-query reference answers, occurrence-expanded A04 answers, model enumerations, model bootstrapped live sets, exact signed difference, then calls partition and checks exact rows, uniqueness, empty-delta live stability, and counter relationships. |
| invariants | This is a test-only materializing check for one insert-only or delete-only endpoint pair. It does not validate input history or mixed batches. Delta model recomputation shares planner tree validation but does not use maintained DeltaRuntime; reference::evaluate performs occurrence joins independently. Candidate/live witness counts must be ≤ factor_count×exact output count, live witnesses ≤ changed keys, and accepted+rejected=candidates. |
| ownership | Owns snapshots, expanded catalogs/databases, A04 answer sets, enumerated rows, live relations, expected difference, and returned CheckedTransition. Input fixtures are borrowed. |
| failure | Any oracle/model/partition mismatch throws through check or propagates typed model/evaluator errors; allocation failure propagates. |
| cost | Per call, computes before/after snapshots; each snapshot validates the tree directly and again inside recompute, for four validate_tree calls total. It evaluates four whole-query A04 endpoints (original and occurrence-expanded before/after); enumerates both model answers; bootstraps live sets and projects A04 answers per factor; then partitions. Maps, Cartesian assignment joins, Relations, row copies, eager diagnostic strings, and returned endpoint sets are test costs, not runtime work counters or CPU bounds. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp), [tests/reference/delta_model.hpp](../../../../../tests/reference/delta_model.hpp), [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/delta_transition_spec.md](../../../../delta_transition_spec.md) |

## B0034

[Lines 273–279](../../../../../tests/unit/delta_spec_test.cpp#L273); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture one_table_fixture(std::string name, std::vector<Column> columns, Query query, FreeConnexTree tree, Relation rows)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a one-table test fixture from supplied owned query/tree/rows. |
| inputs / outputs | Constructs version-1 single-table Catalog and returns Catalog, Query, Tree, and Database with supplied relation. |
| invariants | Used only for deliberately small fixtures with one table; does not perform validation itself. |
| ownership | Moves name, columns, query, tree, and rows into a Fixture aggregate. |
| failure | Construction/allocation failures propagate. |
| cost | One catalog/table/database construction; row/container cost follows supplied fixture. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp) |

## B0036

[Lines 281–335](../../../../../tests/unit/delta_spec_test.cpp#L281); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void hidden_projection_and_physical_counts()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check hidden projections and physical rows that collide on the same occurrence key. |
| inputs / outputs | Runs four check_step transitions: an ignored payload-only row insertion, a new hidden z under an already-live x and its reverse erase, and deletion of the last hidden witness. Checks no E/Q change until the final support disappears, then one visible x is removed. |
| invariants | Ignored columns do not enter occurrence E. Positive-to-positive hidden support changes produce no changed key/output; last witness removal emits exactly one visible tuple. |
| ownership | Each before/after Fixture and CheckedTransition owns copied row/result/model state. |
| failure | Failed physical-projection, collision, reverse, or last-witness assertion throws. |
| cost | Builds multiple full model/oracle checks; each check_step performs repeated full joins and result copying on tiny one-table relations. The cases test concrete support boundaries, not all hidden schemas. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp), [tests/reference/delta_model.hpp](../../../../../tests/reference/delta_model.hpp), [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/delta_transition_spec.md](../../../../delta_transition_spec.md) |

## B0038

[Lines 337–419](../../../../../tests/unit/delta_spec_test.cpp#L337); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void root_and_ancestor_partitions()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact fragment ownership for root/child changes and empty-separator cases. |
| inputs / outputs | Runs three transitions: deleting the S physical row so both R/S visible E factors lose their keys while the physical R row remains; inserting a full-key row at a one-factor root; and activating a disconnected child under two existing root rows. Prints the root owner factor/key/output for deletion. |
| invariants | Root rank 0 accepts the deleted joined row and child rank 1 rejects it, preventing duplicate output. Empty root separator still binds the full root E key. A child with empty separator can enumerate each full root witness. Expected rows are compared to A04. |
| ownership | Fixtures, traces, transitions, and output rows are test-owned values. |
| failure | Incorrect owner, completion set, acceptance/rejection fragment, or duplicate causes failure. |
| cost | Three check_step model/oracle passes plus trace formatting and temporary relations; work depends on each enumerated completion count. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp), [tests/reference/delta_model.hpp](../../../../../tests/reference/delta_model.hpp), [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/delta_transition_spec.md](../../../../delta_transition_spec.md) |

## B0040

[Lines 421–481](../../../../../tests/unit/delta_spec_test.cpp#L421); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void deep_and_dead_witnesses()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check a deep child E change that activates lower live state, plus an E change with no live parent completion. |
| inputs / outputs | In a three-node R-S-T path, inserts S(1,20) while root E and T E rows stay fixed; checks T live state gains z=20 and S factor emits one answer. A second R-empty fixture inserts S(a,b) and expects dead_witnesses with zero candidates/output. |
| invariants | Change below the root can affect descendants’ L even if their E is unchanged. A changed child key with no globally live parent completion is dead and emits nothing. |
| ownership | Before/after fixtures, snapshots, live relations, and transition details are owned temporaries. |
| failure | Wrong factor ownership, missed descendant live change, or productive enumeration of an unlive key fails. |
| cost | Two complete snapshot/model/A04 checks plus explicit live bootstrap and relation comparisons; all joins/projections are materialized. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp), [tests/reference/delta_model.hpp](../../../../../tests/reference/delta_model.hpp), [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/delta_transition_spec.md](../../../../delta_transition_spec.md) |

## B0042

[Lines 483–577](../../../../../tests/unit/delta_spec_test.cpp#L483); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void root_activation_boolean_and_constants()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check root activation, Boolean/nullary answers, constant filtering, and source-free constant routes. |
| inputs / outputs | Runs five same-sign check_step cases: root R activates an existing S row; Boolean row insertion; deletion of the last Boolean witness; constant-7 match activation; and nonmatching constant-filtered row insertion. Also checks empty-body true/contradictory constant snapshots, enumeration/bootstrap shape, and unchanged partitions for both signs. |
| invariants | A nullary true Boolean answer is one empty tuple; deleting its last witness emits one empty tuple with erase sign. Constant-filtered physical rows do not change E; no-factor constant true/false routes have no live factors and no delta when unchanged. |
| ownership | Fixtures/model snapshots/results are local values; no runtime state is retained. |
| failure | Any wrong nullary cardinality, filter behavior, constant answer, or partition output fails. |
| cost | Five full check_step passes plus several constant-route enumerations/partitions; materialized query/model work is fixture-sized. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp), [tests/reference/delta_model.hpp](../../../../../tests/reference/delta_model.hpp), [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/delta_transition_spec.md](../../../../delta_transition_spec.md) |

## B0044

[Lines 579–716](../../../../../tests/unit/delta_spec_test.cpp#L579); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void alias_predicate_count_only_routes()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check predicate-filtered aliases and count-only support changes across ordered occurrence prefixes. |
| inputs / outputs | Builds two alias-local tables from one physical base table, verifies A04 endpoint equivalence, then checks six occurrence-route transitions for inserting status 2, deleting one of two status-1 derivations, and deleting the last status-1 derivation. Staged alias outputs are compared with the exact physical endpoint difference. |
| invariants | Status constants route the new physical row only to alias B; first status-1 deletion stays positive-to-positive with zero changed E keys/output; last A support deletion emits x once in route A, while filtered route B emits none. Ordered route outputs telescope without duplicates to same-table A04. |
| ownership | Each prefix owns a copied Database/Catalog/Query; transitions and staged vectors own rows; original physical fixtures remain separate. |
| failure | Alias endpoint mismatch, wrong per-route delta count, duplicate output, or failure to telescope to physical difference fails. |
| cost | Six check_step calls, additional full A04 endpoint evaluations/occurrence expansions, and copies several alias tables and relations; all costs are finite fixture/test-oracle work. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp), [tests/reference/delta_model.hpp](../../../../../tests/reference/delta_model.hpp), [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/delta_transition_spec.md](../../../../delta_transition_spec.md) |

## B0046

[Lines 718–959](../../../../../tests/unit/delta_spec_test.cpp#L718); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void products_aliases_and_heads()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise product fan-out, same-scope aliases, self-join new-new terms, and repeated/reordered heads. |
| inputs / outputs | For generalized products with arity 3 and 8, adds one row to the last child and expects 2^(arity-1) sibling combinations. Then checks one simultaneous same-base alias insertion; four ordered prefix transitions for same-scope alias insert/delete; four ordered edge-loop self-join transitions; and one reordered repeated-head transition. |
| invariants | Same-scope outputs are emitted once. In the edge self-join, insertion route 1 emits (1,1,2), route 2 emits (1,1,1) and (2,1,1); deletion routes emit the exact reverse partition. Repeated head order yields (4,7,4). All endpoints/staged unions are checked against A04. |
| ownership | Catalogs, per-occurrence databases, transition fragments, and output vectors are materialized and owned by the fixture/test. |
| failure | Any output count, factor route, endpoint, uniqueness, or head-order mismatch fails. |
| cost | Runs 12 check_step calls plus full product enumeration; arity-8 case emits 128 tuples and materializes intermediate assignment joins and oracle outputs. This is an explicit finite fan-out case, not a constant-output bound. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp), [tests/reference/delta_model.hpp](../../../../../tests/reference/delta_model.hpp), [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/delta_transition_spec.md](../../../../delta_transition_spec.md) |

## B0048

[Lines 961–1110](../../../../../tests/unit/delta_spec_test.cpp#L961); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void exhaustive_tiny_domains()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exhaustively check one-tuple toggles over several finite tiny relation domains. |
| inputs / outputs | Iterates all 16 subsets of a four-row hidden-projection domain and four toggles each (64); all 4×16 path R/S mask pairs and six possible tuple toggles (384); all 16×16 projected-chain mask pairs and eight toggles (2,048); and four subsets of a two-row Boolean relation with two toggles each (8). Prints source-derived total 2,504 transitions. |
| invariants | Each transition toggles one tuple according to current membership and uses check_step for same-sign partition/A04 exactness. The finite domains do not establish correctness for arbitrary databases/trees. |
| ownership | Each iteration constructs new Fixture/Database/Relation values; transitions are discarded after verification. |
| failure | Any one of 2,504 oracle/model mismatches fails immediately. |
| cost | Thousands of full subtree recomputations, four A04 evaluations per check_step, relation copies and joins run in one test invocation. 2,504 is source-derived workload count, not native-run output or a runtime/CPU bound. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp), [tests/reference/delta_model.hpp](../../../../../tests/reference/delta_model.hpp), [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/delta_transition_spec.md](../../../../delta_transition_spec.md) |

## B0050

[Lines 1112–1144](../../../../../tests/unit/delta_spec_test.cpp#L1112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void simultaneous_projection_collision()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check simultaneous activation of two hidden witnesses still changes one projected output key. |
| inputs / outputs | With R(4,1,10), R(4,1,11) and empty S, inserts S(1), checks one expected x=4 insertion and one changed E key; checks reverse deletion likewise emits x once. |
| invariants | Two hidden R rows share one visible projection; the query answer is set-valued, so simultaneous witness activation/removal cannot duplicate x. |
| ownership | Fixtures and transition/oracle relations are value-owned. |
| failure | Wrong output or changed-key count fails. |
| cost | Two full check_step evaluations and their materialized joins/projections on three input rows. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp), [tests/reference/delta_model.hpp](../../../../../tests/reference/delta_model.hpp), [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/delta_transition_spec.md](../../../../delta_transition_spec.md) |

## B0052

[Lines 1146–1211](../../../../../tests/unit/delta_spec_test.cpp#L1146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void rejects_invalid_inputs()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject invalid signs, schemas, scopes, scalar types, totality, and native input shapes. |
| inputs / outputs | First proves one valid insert control. It expects invalid_delta_transition for five cases: wrong erase sign, unknown operation enum, mixed factor polarity under insert, the same mixed endpoints under erase, and an incompatible duplicate-head schema. It expects invalid_delta_model for five cases: out-of-head scope, wrong factor scalar type, failed downward totality, wrong native-row type, and per-node native-input vector length mismatch. |
| invariants | Error categories are asserted distinctly through expect_error; invalid fabricated snapshots never enter production runtime. |
| ownership | All crafted snapshots and malformed row sets are local owned values. |
| failure | Expected CROWN Error code mismatch or acceptance fails; non-CROWN exceptions propagate. |
| cost | Constructs small invalid relations and invokes validation/partition/bootstrap/recompute repeatedly; catch helper only catches CROWN Error. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp), [tests/reference/delta_model.hpp](../../../../../tests/reference/delta_model.hpp), [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/delta_transition_spec.md](../../../../delta_transition_spec.md) |

## B0053

[Lines 1212–1214](../../../../../tests/unit/delta_spec_test.cpp#L1212); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1212-L1214:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in delta_spec_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0054

[Lines 1215–1232](../../../../../tests/unit/delta_spec_test.cpp#L1215); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run all nine test-only specification groups in fixed source order. |
| inputs / outputs | No arguments are read. Calls projection/count, root/ancestor, deep/dead, root/Boolean/constants, predicate aliases, products/heads, exhaustive domains, simultaneous collision, and invalid-input checks; prints success if all return. |
| invariants | The exhaustive counter is generated only by the finite loops; main does not invoke maintained DeltaRuntime or a native update benchmark. |
| ownership | Each group owns and releases local model/evaluator values before the next group. |
| failure | std::exception is printed and returns 1; otherwise returns 0. |
| cost | Sequentially runs all fixture joins and the 2,504 source-derived tiny-domain transitions. No native build/test result or performance measurement is produced by this source description. |
| Design | [tests/unit/delta_spec_test.cpp](../../../../../tests/unit/delta_spec_test.cpp) |
