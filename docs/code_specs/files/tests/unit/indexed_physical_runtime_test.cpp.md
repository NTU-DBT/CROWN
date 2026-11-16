# `tests/unit/indexed_physical_runtime_test.cpp` — block usage map

[Source](../../../../../tests/unit/indexed_physical_runtime_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `6abda3218341f55bb4b3250ed8b701cbdd865e73b19257d6a62986281b1508ef`. 366 lines partitioned into 30 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–25](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 26–26](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L26) | Callable definition: void check(bool condition,const std::string& message) | calls std::runtime_error; guard void check(bool condition,const std::string& message) { if (!condition) throw std::runtime_error(me… · [reviewed contract](#b0002) |
| [B0003 · 27–27](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L27) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0003) |
| [B0004 · 28–32](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L28) | Callable definition: template&lt;class Action&gt; void error(Action&& action,std::string_view code) | calls action, check, code, std::string; guard catch (const Error& failure) { check(failure.code()==code,"expected "+std::string(code)+", got "+fa… · [reviewed contract](#b0004) |
| [B0005 · 33–35](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L33) | Callable definition: Row project(const Assignment& assignment,const auto& variables) | calls push_back, at; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 36–40](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L36) | Callable definition: Assignment assignment(const Row& row,const auto& variables) | calls check, size, emplace; guard check(row.size()==variables.size(),"assignment shape"); Assignment result;; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 41–43](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L41) | Callable definition: Relation project(const Assignments& source,const auto& variables) | calls insert; returns result; growth insert; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 44–55](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L44) | Callable definition: Assignments join(const Assignments& left,const Assignments& right) | calls emplace, insert, std::move; returns result; growth emplace, insert; 3 loop sites · [reviewed contract](#b0008) |
| [B0009 · 56–65](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L56) | Callable definition: std::optional&lt;Assignment&gt; raw_atom(const auto& atom,const Row& row) | calls size, emplace, reference::input::scalar; returns {}; {}; growth emplace; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 66–73](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L66) | Callable definition: std::vector&lt;VariableId&gt; separator(const auto& plan,const auto& node) | calls nodes, std::set_intersection, begin, end; returns result · [reviewed contract](#b0010) |
| [B0011 · 74–76](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L74) | Callable definition: Counts projected_counts(const Relation& rows,const auto& scope,const auto& key) | calls project, assignment; returns result; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 77–79](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L77) | Callable definition: Counts keys(const std::vector&lt;ProjectionKeySnapshot&gt;& input) | calls check, emplace, crown::storage::export_row, values; guard Counts result; for (const auto& item : input) check(result.emplace(crown::storage::export_row(item.…; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 80–82](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L80) | Explanatory comments or spacing. | source comment (unverified): // Full assignment joins from physical rows, independent of routing, support · [reviewed contract](#b0013) |
| [B0014 · 83–151](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L83) | Callable definition: void verify(const PhysicalRuntime& runtime,const Database& database,const Adapter& adapter={}) | calls plan, snapshot, check, sequence; guard check(state.sequence==runtime.sequence() && state.support.sequence==state.sequence,"coordinated seq…; growth emplace, insert, push_back; 15 loop sites; source comment (unverified): // Full assignment joins from physical rows, independent of routing, support · [reviewed contract](#b0014) |
| [B0015 · 152–162](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L152) | Callable definition: PhysicalPlan loop_plan(bool boolean=false) | calls s04_runtime::lower_tree; returns s04_runtime::lower_tree(catalog,query,tree) · [reviewed contract](#b0015) |
| [B0016 · 163–163](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L163) | Callable definition: Row edge(std::int64_t x,std::int64_t y,std::string payload="a") | calls n, std::move; returns {n(x),n(y),Value{std::move(payload)}} · [reviewed contract](#b0016) |
| [B0017 · 164–166](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L164) | Callable definition: PhysicalRuntimeOptions options(PropagationOrder order=PropagationOrder::fifo) | calls ; returns result · [reviewed contract](#b0017) |
| [B0018 · 167–192](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L167) | Callable definition: void generated_aliases() | calls runtime, loop_plan, options, resize; guard check(epoch.input.physical_changed==changed && epoch.input.sequence==sequence && epoch.support.sequ…; growth insert, resize; 4 loop sites · [reviewed contract](#b0018) |
| [B0019 · 193–199](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L193) | Type/record definition: struct Image |  · [reviewed contract](#b0019) |
| [B0020 · 200–204](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L200) | Callable definition: Image image(const PhysicalRuntime& runtime) | calls snapshot, std::move, io::write_support_snapshot, plan; returns result; growth emplace, push_back; 2 loop sites · [reviewed contract](#b0020) |
| [B0021 · 205–217](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L205) | Callable definition: void busy(PhysicalRuntime& runtime,TupleHandle source,SupportHandle support) | calls error, has_answer, snapshot, derivation_count; growth insert · [reviewed contract](#b0021) |
| [B0022 · 218–243](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L218) | Callable definition: void publication_and_derivations() | calls runtime, loop_plan, options, apply; guard check(!runtime.ready() && runtime.sequence()==1 && runtime.owner()==owner && &runtime.plan()==plan …; growth insert · [reviewed contract](#b0022) |
| [B0023 · 244–257](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L244) | Callable definition: void active_facade_moves() | calls original, loop_plan, options, apply; guard check(!moved.ready() && moved.owner()==owner && moved.sequence()==1,"active facade move lost its id…; growth insert · [reviewed contract](#b0023) |
| [B0024 · 258–269](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L258) | Callable definition: PhysicalPlan filtered_plan() | calls frontend::bind_sql, check, frontend::normalize_sql, std::move; guard check(std::holds_alternative&lt;frontend::BoundSql&gt;(binding),"SQL binding failed");; returns s04_runtime::lower_normalized(program,tree) · [reviewed contract](#b0024) |
| [B0025 · 270–287](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L270) | Callable definition: void sql_filters_and_later_alias_failure() | calls filtered_plan, n, runtime, options; guard if (row==edge(1,2)) check(epoch.input.metrics.aliases_filtered==1 && epoch.input.derivations.size()…; returns {}; Assignment{{VariableId{0},row\[0\]}}; growth insert, resize; 1 loop sites · [reviewed contract](#b0025) |
| [B0026 · 288–305](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L288) | Callable definition: void raw_guards_and_nullary_derivations() | calls std::string, runtime, s04_runtime::lower_tree, resize; guard check(epoch.input.metrics.aliases_filtered==(row==edge(1,1,"ok")?0U:1U),"constant/repeated-variable…; growth insert, resize; 1 loop sites · [reviewed contract](#b0026) |
| [B0027 · 306–336](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L306) | Callable definition: void constraints_and_unrouted_tables() | calls runtime, s04_runtime::lower_tree, image, error; guard check(image(runtime)==empty,"FK rejection changed empty state");; growth insert · [reviewed contract](#b0027) |
| [B0028 · 337–355](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L337) | Callable definition: void constants_and_resource_caps() | calls runtime, s04_runtime::lower_tree, resize, verify; guard check(runtime.source_layout(TableId{0}).origin()-&gt;table==TableId{0},"private constant-route source …; growth insert, resize; 1 loop sites · [reviewed contract](#b0028) |
| [B0029 · 356–356](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L356) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0029) |
| [B0030 · 357–366](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L357) | Callable definition: int main() | calls static_assert, generated_aliases, publication_and_derivations, active_facade_moves; guard static_assert(std::is_nothrow_move_constructible_v&lt;PhysicalEpoch&gt;);; returns 1 · [reviewed contract](#b0030) |

## B0001

[Lines 1–25](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L25:sha256:fb759154ebec2d1eab8ea8a5ffed9c791dc5d39089ac7477c6639f6cdefcbd3e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare indexed_physical_runtime_test.cpp: include "indexed_runtime_fixture.hpp", "crown/runtime/physical.hpp", "crown/planner/lower.hpp", "crown/io/support.hpp", "crown/api/error.hpp", "evaluator.hpp", "native_input.hpp", &lt;algorithm&gt;, &lt;functional&gt;, &lt;iostream&gt;, &lt;iterator&gt;, &lt;map&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;utility&gt;, &lt;type_traits&gt;; bind local aliases/name imports; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 26–26](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition,const std::string& message) { if (!condition) throw std::runtime_error(message); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide a throwing assertion helper for this test translation unit. |
| inputs / outputs | Boolean condition and diagnostic string in; no value out. A false condition throws std::runtime_error with the supplied message. |
| invariants | A true condition returns normally. This helper is test scaffolding; it does not add a production runtime check. |
| ownership | The message is borrowed for the call. The thrown exception owns its diagnostic representation. |
| failure | False conditions stop the current test path by throwing std::runtime_error. |
| cost | The caller evaluates and constructs the \`std::string\` message argument before entering this function, even when \`condition\` is true; dynamic expressions may allocate depending on their contents. The helper itself takes one branch and constructs/throws \`std::runtime_error\` from the message only when false. These assertion allocations are test-side, not query metrics. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0003

[Lines 27–27](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap an int64 fixture value in the IR Value variant. |
| inputs / outputs | std::int64_t in; Value holding that integer alternative out. |
| invariants | The helper performs no range, schema, or nullability validation and changes no numeric value. |
| ownership | Returns a scalar value by value; there is no borrowed row or runtime handle. |
| failure | No explicit failure path. |
| cost | Fixed-size variant construction and integer copy; it does not traverse a row or payload. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0004

[Lines 28–32](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void error(Action&& action,std::string_view code) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that an action throws a CROWN Error with a particular code. |
| inputs / outputs | Forwarding-reference callable and expected code \`string_view\` in; no result out. The named \`action\` parameter is invoked once as an lvalue; this function does not use \`std::forward\` and does not preserve an rvalue-only call operator. |
| invariants | Invokes the action once and catches only \`crown::Error\`. A matching code returns; a mismatching code fails through \`check\`; other exception types propagate. The expected/got diagnostic concatenation passed to \`check\` is evaluated for every caught \`Error\`, including when its code matches. |
| ownership | The callable is invoked through the named lvalue reference for the duration of the call; \`code\` is borrowed. Mismatch and missing-error diagnostic expressions create temporary strings; the caught-error concatenation is built before \`check\` even on a match. |
| failure | If no \`crown::Error\` is caught, throws \`std::runtime_error\` with the missing-code diagnostic. A wrong code throws through \`check\`; non-CROWN exception types propagate. A matching error returns after its diagnostic argument has already been evaluated. |
| cost | Invokes the action once as an lvalue, then performs exception dispatch and a code comparison. Every caught CROWN \`Error\` eagerly builds \`"expected " + std::string(code) + ", got " + failure.code()\` before \`check\`, even on a match; normal action return builds the missing-error string before throwing. No \`std::forward\` or product runtime metric is involved. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0005

[Lines 33–35](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row project(const Assignment& assignment,const auto& variables) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project a variable assignment into an ordered Row for comparison in the independent test interpreter. |
| inputs / outputs | Assignment map and variable sequence in; a Row containing values in the sequence order out. |
| invariants | Every requested variable must exist in the map; order comes from the supplied sequence, not map iteration. |
| ownership | The returned Row owns copied Value scalars. Inputs are read only. |
| failure | Assignment::at throws std::out_of_range for a missing variable. |
| cost | For k requested variables and m assignment entries, performs k ordered-map lookups (O(k log m)), copies k Values, and grows a Row buffer; string alternatives can copy payload bytes. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0006

[Lines 36–40](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Assignment assignment(const Row& row,const auto& variables) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rebuild a variable assignment from a Row and its variable order for the independent test interpreter. |
| inputs / outputs | Row and variable sequence in; ordered map from each variable to the corresponding Value out. |
| invariants | Requires row.size() to equal variables.size(). Call sites use the plan scope order; map emplace keeps the first value if an unexpected duplicate variable is supplied. |
| ownership | The output map owns copied Values; the source Row is only read. |
| failure | A shape mismatch throws std::runtime_error through check. Allocation failures and other standard-library exceptions propagate. |
| cost | One shape check, then k map insertions and Value copies (ordered-map work is O(k log k)); string alternatives can copy payload bytes and map nodes allocate. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0007

[Lines 41–43](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation project(const Assignments& source,const auto& variables) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project each assignment in a set into a relation of ordered Rows. |
| inputs / outputs | Set of assignments and variable sequence in; deduplicated ordered Relation out. |
| invariants | Each source assignment is projected independently. Relation set membership collapses equal projected rows. |
| ownership | Output rows and relation nodes own their copied values; source assignments are unchanged. |
| failure | Lookup or allocation exceptions propagate; there is no local error conversion. |
| cost | Visits every source assignment, performs B0005 projection, then ordered-set insertion and comparisons. Work and allocations scale with input assignments and distinct projected rows; string comparisons depend on payload lengths. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0008

[Lines 44–55](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Assignments join(const Assignments& left,const Assignments& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute a simple natural join of two assignment sets as a test oracle, without using runtime routing. |
| inputs / outputs | Two ordered sets of variable/value maps in; set of compatible merged maps out. |
| invariants | Enumerates every left/right pair. Shared variables must have equal Values; compatible merged assignments are deduplicated by the result set. |
| ownership | Each candidate starts as a copy of the left map; result maps own their copied Values. |
| failure | Map/set allocation or comparison exceptions propagate; no partial result is returned to the caller if construction throws. |
| cost | Nested Cartesian enumeration of \|left\|×\|right\| pairs, with a map copy, RHS binding checks/inserts, and ordered result-set comparisons per compatible pair. Intermediate map/set nodes allocate; this can grow with the full join result. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0009

[Lines 56–65](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<Assignment> raw_atom(const auto& atom,const Row& row) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Interpret one raw query atom against a physical Row for the independent full-assignment verifier. |
| inputs / outputs | Atom-like terms and physical Row in; optional Assignment of bound variables out. Empty optional means a repeated variable or fixed scalar did not match. |
| invariants | Scans terms by physical column position. Variable terms bind \`row\[i\]\`; repeated variables must agree. Fixed \`Value\` terms compare through \`reference::input::scalar\`; ignored columns are skipped. The caller must supply a row with catalog-arity shape: this helper performs no arity check and \`row\[i\]\` is unchecked. |
| ownership | The resulting Assignment owns copied Values. Input terms and row are borrowed. An ignored payload is not copied into the assignment. |
| failure | Returns an empty optional for repeated-variable or fixed-value mismatch. An out-of-range \`row\[i\]\` violates \`vector::operator\[\]\` preconditions and is not a specified exception path (it can be undefined behavior); allocation failures propagate. These fixtures use ordinary \`Value\` scalars, with no SQL NULL alternative. |
| cost | Scans each atom term, does ordered-map insertion/comparison for variable bindings, and compares fixed values; string scalar comparison may inspect payload bytes. Assignment nodes and copied string values can allocate. This is a test-side row interpreter, not the runtime route. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0010

[Lines 66–73](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<VariableId> separator(const auto& plan,const auto& node) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute the sorted variable intersection between a node scope and its parent scope for the verifier. |
| inputs / outputs | Plan and node in; ordered vector of shared VariableIds out. |
| invariants | A root with no parent yields an empty vector. Otherwise the caller must supply valid node/parent IDs and both scope vectors must be sorted; the function uses \`plan.nodes()\[node.parent-&gt;value\]\` and \`std::set_intersection\` without validating those preconditions. |
| ownership | Returns a new vector; the plan and node are only read and must remain valid during the call. |
| failure | No explicit node or parent range check is performed; out-of-range \`plan.nodes()\[...\]\` access is not a guaranteed exception path. Vector allocation failures propagate for valid plan inputs. |
| cost | Linear merge over the two scope lengths plus storage for each shared variable; it does not scan relation rows or runtime indexes. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0011

[Lines 74–76](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Counts projected_counts(const Relation& rows,const auto& scope,const auto& key) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute support multiplicities by projecting materialized Rows through a scope and key scope. |
| inputs / outputs | Relation rows, row scope, and count key variables in; ordered map from projected Row keys to uint64 counts out. |
| invariants | Every row must match the supplied scope width, and requested key variables must be present in the temporary assignment. Equal keys increment one count. |
| ownership | The result map owns its Row keys; temporary assignments and projected rows are local copies. |
| failure | Shape/missing-variable checks or allocation exceptions propagate; count increment overflow is not checked here. |
| cost | Visits all input rows; each row is rebuilt as an assignment, projected again, and inserted/incremented in an ordered map. Cost includes map lookup/comparison, Row/vector growth, and copied string payloads. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0012

[Lines 77–79](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Counts keys(const std::vector<ProjectionKeySnapshot>& input) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert a support snapshot vector into the verifier’s ordered Row-to-count map. |
| inputs / outputs | ProjectionKeySnapshot vector in; owning Row keys and support values in a Counts map out. |
| invariants | Each exported key must be unique in the input; duplicate insertion fails through check. Stored values are copied from item.support.value. |
| ownership | storage::export_row makes owning Row keys; the returned std::map owns them independently of the snapshot. |
| failure | Duplicate snapshot keys throw std::runtime_error. Export and map allocation failures propagate. |
| cost | Visits each snapshot entry, exports its full key row, and performs an ordered-map insert with row comparisons. String key export copies payload bytes; this is diagnostic oracle work outside the runtime account. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0013

[Lines 80–82](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L80); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L80-L82:sha256:51189b431e3aaf275fa6397acf56d89673d972aff497cf6105083fa541cec34c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Full assignment joins from physical rows, independent of routing, support propagation, numeric adapters and the runtime's own invariant checker. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 83–151](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify(const PhysicalRuntime& runtime,const Database& database,const Adapter& adapter={}) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently recompute a small runtime snapshot from physical rows and compare derivations, tree support records, visible outputs, truth, and runtime invariants. |
| inputs / outputs | Committed PhysicalRuntime, matching external Database, and optional occurrence/row adapter in; no value out. Increments the local verified counter only after all assertions pass. |
| invariants | First checks sequence agreement and exact physical tables. Constant routes check their truth bit and empty logical ports. Tree routes recompute per-occurrence assignments/counts, build root-to-leaf order, join subtrees bottom-up, compare survivor/record memberships and child flags/satisfied/survives, recompute parent and visible-key counts, and compare full head results and has_answer. Without an adapter it also compares reference::evaluate. Finally calls runtime.check_invariants. The adapter represents this test’s SQL row filtering; this is bounded fixture evidence, not a general runtime theorem. |
| ownership | The snapshot exports \`physical.tables\` as owning \`Database\` Rows. Its support and derivation entries hold owning \`storage::Tuple\` values with account-backed native payload ownership; copies of those native Tuple holders share the immutable payload owner rather than deep-copying each string again. Local verifier vectors, maps, sets, exported Rows, and joined assignments own their own data; runtime, database, and adapter are borrowed. |
| failure | The first failed check throws \`std::runtime_error\`; snapshot, export, evaluator, invariant, and allocation failures propagate. Several plan/table/occurrence/row accesses use unchecked \`operator\[\]\`; valid compiled IDs, a matching Database, and catalog-arity adapter rows are preconditions, not error paths. It requires a readable committed runtime; pending updates make reads report \`runtime_busy\`. |
| cost | High, deliberately materializing oracle cost: scans every fixture physical row and snapshot record, exports keys, allocates vectors/maps/sets, and performs nested Cartesian assignment joins whose intermediate sizes can multiply. Work scales with the fixture’s full row sets and join intermediates. In the indexed file the same verifier still performs these STL joins; it does not count or establish index probes, scans, CPU, RSS, or account bytes. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp) |

## B0015

[Lines 152–162](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L152); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan loop_plan(bool boolean=false) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the repeated-base-alias fixture plan used for update, derivation, output, and support-limit checks. |
| inputs / outputs | Optional boolean mode in; PhysicalPlan with one edge table and a generalized root over forward/reverse native occurrences out. |
| invariants | The source has int64 x/y and string payload. Both aliases route the same TableId with x/y swapped and mark payload IgnoredColumn. The tree joins both aliases over {x,y}. Normal mode has head outputs x, y, x-as-again; boolean mode leaves the head empty. The test calls s04_runtime::lower_tree, whose tests/support/indexed_runtime_fixture.hpp passes an IndexedBackendSpec to the planner; the contract covers fixture selection and asserted semantics, not index-work behavior. The selected fixture sets per-table IndexedLimits (rows, indices, keys, memberships, nodes, directory slots, arena slots, arena pins, journal entries) to (4096, 64, 32768, 65536, 131072, 524288, 8192, 32768, 8192). Its one aggregate per-composed-operation IndexWork grant is (1,000,000,000) for each of structural steps, scalar fields, scalar bytes, pointer slots, and link actions. These are admission ceilings; the test does not measure consumption. |
| ownership | Catalog/query/tree are local values consumed by lowering; the returned plan owns its compiled representation. |
| failure | Planner validation or allocation failures propagate. This fixture does not exercise nullable SQL values. |
| cost | Constructs a tiny fixed catalog, query, and three-node tree, then runs planner lowering once per call. Setup allocations scale with this fixed metadata; the helper is not an update-cost benchmark. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [include/crown/storage/backend.hpp](../../../../../include/crown/storage/backend.hpp) |

## B0016

[Lines 163–163](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L163); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row edge(std::int64_t x,std::int64_t y,std::string payload="a") { return {n(x),n(y),Value{std::move(payload)}}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one physical edge fixture row with two integer cells and an owned string payload. |
| inputs / outputs | x, y, and payload string in; three-cell Row {int64, int64, string} out. |
| invariants | The payload is moved into the Value alternative; no schema or row-shape validation happens here. |
| ownership | Returns an owning Row. The function’s by-value string parameter is moved into Value; the caller owns the returned row. |
| failure | Allocation failures during Row or string construction propagate. |
| cost | Builds a three-element vector and two scalar Values; payload transfer may still require string allocation depending on the caller’s argument and string capacity. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0017

[Lines 164–166](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L164); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntimeOptions options(PropagationOrder order=PropagationOrder::fifo) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set support transition capture and propagation order for the runtime fixtures. |
| inputs / outputs | PropagationOrder in (FIFO by default); PhysicalRuntimeOptions out. |
| invariants | Only \`support.capture_transitions\` and \`support.order\` are assigned. The outer physical work limit remains 1,000,000 and derivation limit remains \`uint64_t\` max; nested support work limit remains 1,000,000 and its default query account remains 256 MiB. Backend selection and indexed operation grants come from the plan, not this options helper. |
| ownership | Returns an independent options value; no runtime owner is created. |
| failure | No explicit validation here; downstream runtime construction validates consumed options. |
| cost | Fixed-size options value construction/copy; no source rows or runtime storage are traversed. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0018

[Lines 167–192](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L167); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void generated_aliases() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise repeated source aliases under deterministic insert/erase traces and verify each committed epoch against the independent materializing oracle. |
| inputs / outputs | No inputs; runs four traces (FIFO/LIFO × seeds 7/91), each with 100 generated update attempts and then erases every row still in its physical set. |
| invariants | Each attempt advances the requested sequence. The external std::set is updated independently. For a changed row the test asserts two visited aliases, two derivation changes in occurrence order 0 then 1, and a source event carrying the complete input row. For a physical no-op it asserts zero reported input/support work, no source event, and no support journal. verify() runs after every attempt and cleanup erase; final derivation key count is zero and has_answer is false. A zero reported metric does not mean zero CPU: runtime apply still validates/imports/probes the row and admits the owner operation. |
| ownership | Each generated Row owns its payload through apply; PhysicalEpoch owns event data, including the retained source-row pin where present. The external relation is test-owned. |
| failure | Any metric, ordering, state, or oracle mismatch throws and aborts this test path; runtime errors propagate. |
| cost | Four deterministic traces (FIFO/LIFO × seeds 7/91) make 400 generated update attempts. The fixed 64-bit LCG and external-set fixture stream yields, for each order: seed 7 has 52 insert and 48 erase attempts (25/19 changed, 27/29 no-ops) and leaves 6 rows; seed 91 has 54 insert and 46 erase attempts (28/17 changed, 26/29 no-ops) and leaves 11. Across all four traces that is 212 insert attempts (106 changed, 106 no-ops), 188 erase attempts (72 changed, 116 no-ops), then 34 cleanup erases, for 434 update calls and one full verify() after each. Each verification materializes whole assignments and nested joins. Counts are derived from the source generator and fixture set operations; this review did not run the test binary. The row domain is bounded to x/y in 0..2 and payload a/b; this is not a timing benchmark. Indexed variant metrics do not expose a separate count of index traversals or scans. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0019

[Lines 193–199](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L193); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Image {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define an owning comparison image for the selected runtime state used by rollback assertions. |
| inputs / outputs | Fields hold sequence, copied physical Relations, serialized support JSON, and per-occurrence derivation-count maps; default equality returns a bool. |
| invariants | Equality compares every declared field. This image is a test representation, not a runtime snapshot API or durable checkpoint. |
| ownership | Vectors, Relation sets, JSON, and maps own their copied values and buffers. |
| failure | Allocation/JSON construction failures occur in producers; equality itself can invoke element comparisons. |
| cost | Memory scales with all copied physical rows, support JSON, and derivation keys; equality can compare all of those elements. No account-byte, RSS, or CPU metric is recorded. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp) |

## B0020

[Lines 200–204](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L200); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Image image(const PhysicalRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize runtime state as an Image suitable for exact before/after comparisons. |
| inputs / outputs | Readable PhysicalRuntime in; owning Image out. |
| invariants | Calls snapshot(), moves its copied physical table vector into Image, serializes the support snapshot using the runtime plan, and exports each derivation tuple to a Row paired with its count. |
| ownership | Image owns its output. The physical table vector is an exported \`Database\` of owning Rows and is moved into \`Image\`; support/derivation snapshots contain owning \`storage::Tuple\` holders with account-backed native payload ownership. Support JSON serialization and exported derivation \`Row\` keys create additional independent data. |
| failure | Runtime busy/invalid errors, row export, JSON, or allocation failures propagate. |
| cost | Visits and copies all physical/support/derivation state represented in the snapshot, serializes support to JSON, and allocates output vectors/maps. This is full diagnostic materialization, not a measurement of runtime-account bytes or process RSS. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp) |

## B0021

[Lines 205–217](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L205); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void busy(PhysicalRuntime& runtime,TupleHandle source,SupportHandle support) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that selected public reads and nested writes reject access while one PhysicalRuntime::PendingUpdate is active. |
| inputs / outputs | Busy runtime plus valid source/support handles in; no value out. |
| invariants | Expects runtime_busy from has_answer, snapshot, derivation_count, find_source, get_source, find_support, get_support, storage_statistics, check_invariants, prepare, and apply. The list is exactly the calls in this helper; it does not prove every runtime API is blocked. |
| ownership | Handles are copied values. Constructed edge/update rows are temporary owned inputs for each attempted call; the pending token remains owned by the caller. |
| failure | If any call succeeds or throws a different CROWN error, error/check throws std::runtime_error and fails the test. |
| cost | Per invocation, performs eleven rejected API attempts plus expected exception handling. Update probes construct fixture rows and may allocate diagnostic/error strings; no performance timing is collected. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0022

[Lines 218–243](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L218); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void publication_and_derivations() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check pending-update privacy, rollback, commit publication, duplicate-projection derivation counts, event pin lifetime, and invalid-input atomicity. |
| inputs / outputs | No inputs; builds a runtime, applies physical rows with equal logical projections but different payloads, and checks snapshots, handles, epochs, errors, and readiness. |
| invariants | The first row creates source/support handles. While a second row with another payload is pending, public calls in busy() must report runtime_busy; owner, plan/layout addresses, and committed sequence remain stable. Preview has physical_changed but no native support change/journal and derivation count 1→2; tentative physical snapshot has two rows and one native record. Destruction cancels and restores the prior Image. Commit raises the derivation count to 2 without changing the support handle. Erasing one of two source rows retains support; the event’s complete source tuple remains readable while its pin reports not live. Erasing the last projection removes support and answer. Invalid table, sequence, and row inputs report their specified codes and preserve Image. |
| ownership | Input Rows own their Values. Runtime preparation imports native tuple ownership before returning a PendingUpdate. Preview/snapshot are token views/copies; the committed PhysicalEpoch owns its source change and retained pin. The pin keeps erased payload readable until the epoch releases it, while is_live reflects current table membership. |
| failure | Expected Error codes are runtime_busy, invalid_physical_update, invalid_sequence, and invalid_update. Image comparisons detect partial state changes; unexpected errors propagate. |
| cost | Four source-row changes are committed (two inserts and two deletes); the second row has the same logical projection and a different payload. Its first preparation is canceled by PendingUpdate destruction; the same insertion is prepared again and committed. Three invalid apply requests are rejected (bad table, skipped sequence, malformed row). The accepted sequence advances 1→2→3→4. For occurrence 0, the source lifecycle implies counts 1→2→1→0 after its first insert, duplicate-projection insert, and two deletes; the test directly reads count 2 after commit and uses handle checks for persistence/removal rather than re-reading the count after each delete; the inspected native support handle remains present after the duplicate-projection insertion and first deletion, then disappears after the last deletion. Four full Image snapshots/comparisons plus the pending preview/snapshot are materialized. No requested-byte/account limit or process RSS/CPU measurement is asserted. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_arena.cpp](../../../../../src/storage/accounted_arena.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0023

[Lines 244–257](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L244); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void active_facade_moves() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that an active facade move preserves the runtime owner and lets its already-created PendingUpdate commit through the destination facade. |
| inputs / outputs | No explicit inputs; constructs an \`original\` runtime, commits physical row \`edge(1,1)\`, and prepares a distinct row \`edge(2,2)\`. It move-constructs a second facade from the active original, constructs an independent empty \`destination\` runtime, move-assigns the moved owner into it, then commits the already-created token. |
| invariants | The moved-from \`original\` and then \`moved\` facades report \`invalid_runtime\`. The moved owner remains busy at sequence 1 with its original owner. After the pending \`(2,2)\` insertion commits through \`destination\`, that facade is ready at sequence 2, retains the original owner and the first row’s source handle, reports a physical change, and passes invariants. The test does not assert destination contents by reading the second row. |
| ownership | Runtime facades are move-only; the pending token is retained independently and, in the implementation, shares the owner implementation needed to finish the operation. The test asserts behavior, not pointer layout or allocation count. |
| failure | Unexpected error code, changed owner/sequence/readiness, lost source, or invariant failure aborts the test. |
| cost | Constructs two runtime facades/plans, commits one source-row insertion, prepares one distinct row, moves the active facade twice, commits, and checks invariants. The destination’s initially empty runtime is replaced by move assignment. No move-allocation or runtime-memory measurement is collected. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0024

[Lines 258–269](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L258); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan filtered_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind and normalize a filtered SQL query, then lower a two-alias tree plan for filter and later-alias failure cases. |
| inputs / outputs | No inputs; returns PhysicalPlan for SELECT DISTINCT a.x, a.x AS again over two aliases of r with join a.x=b.x and predicate a.flag=1. |
| invariants | Requires successful BoundSql and NormalizedSql alternatives, then checks the normalized core has one variable and two atoms. Native leaves share visible x under a generalized root. The ordinary file calls planner::lower_normalized; the indexed file calls s04_runtime::lower_normalized and its fixture selects indexed storage. |
| ownership | The SQL text and source Catalog are local. The normalized program is moved out of the \`NormalizedSql\` variant into a local value; \`planner::lower_normalized\` (and the indexed wrapper) borrows it by \`const&\` during lowering. The returned plan owns compiled data and remains valid after the local program is destroyed. |
| failure | Unexpected binding/normalization result fails through check; planner/allocation errors propagate. |
| cost | Runs SQL bind, normalize, and plan lowering per call. Work and temporary allocations scale with query/source metadata; the test records no frontend or planner timing. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [include/crown/storage/backend.hpp](../../../../../include/crown/storage/backend.hpp) |

## B0025

[Lines 270–287](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L270); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sql_filters_and_later_alias_failure() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check per-occurrence filtering for one normalized SQL alias and rollback when a later alias exceeds the derivation cap. |
| inputs / outputs | No inputs; builds filtered plan/runtime, applies five specified edge rows, then uses a second runtime with derivation_limit=1 for a failure sequence. |
| invariants | The test adapter rejects occurrence 0 when row\[1\] is not 1 and maps accepted rows to x; occurrence 1 accepts every row. The first (1,2) row reports one filtered alias and one derivation. verify() compares the adapted physical recomputation after every row. With the cap, insertion of (1,2) succeeds, insertion of (1,1) throws derivation_overflow, readiness and Image remain at the prior state, and occurrence 0 count is zero; erase/retry then succeeds. Indexed source uses the indexed plan wrapper, but these assertions do not measure index work. |
| ownership | Rows and adapter-produced Assignments own their Value copies. Runtime owns imported physical and derivation state; Image is an owning diagnostic copy. |
| failure | Binding/verification failures or a different error code fail the helper. Later-alias overflow must leave no partial physical/derivation commit. |
| cost | The first runtime commits five distinct inserts and runs the full verifier after each. The capped runtime makes four apply attempts: one successful insert, one derivation_overflow rejection, one successful erase, and one successful insert. Across both runtimes that is nine attempts: eight committed source changes and one rejected update. Two full Images bracket the cap failure, followed by one invariant check. Each verifier materializes whole-row recomputation and joins; no timing, scan, or index-probe count is asserted. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [include/crown/storage/backend.hpp](../../../../../include/crown/storage/backend.hpp) |

## B0026

[Lines 288–305](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L288); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void raw_guards_and_nullary_derivations() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check repeated-variable and fixed-value guards, then distinguish physical derivation multiplicity from support multiplicity for a nullary projection. |
| inputs / outputs | No inputs; creates a guarded diagonal query and an all-IgnoredColumn nullary query, applying and erasing a few rows. |
| invariants | For the guarded atom, x must match both x columns and the third physical value must equal "ok"; each rejected row reports one filtered alias and the matching row reports zero. In the nullary query, all three source columns are ignored: two distinct physical rows produce derivation_count(empty)=2 while the visible empty-key support remains 1; deleting one row preserves answer and deleting the last clears it. The fixture uses ordinary Value scalars, not SQL NULLs. |
| ownership | Catalog, queries, rows, and test Database are owning local values. Ignored payload cells stay in the physical source row but do not appear in the empty assignment; runtime owns imported copies. |
| failure | Any filter count, derivation/support count, result, or independent verify mismatch fails. Runtime errors propagate. |
| cost | Three guarded updates with a verify after each, then four nullary operations with materialized verification and one support snapshot. Full physical rows are recomputed by the test; this does not imply a constant-time nullary route. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0027

[Lines 306–336](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L306); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void constraints_and_unrouted_tables() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check enforced foreign-key/unique constraints, rejected-update atomicity, non-routed table maintenance, self-reference rules, and untrusted-hint behavior. |
| inputs / outputs | No inputs; constructs constrained catalogs and one-row query plans, then performs source/target/unused-table updates. |
| invariants | An enforced FK row cannot enter before its target; rejected state equals the saved Image. Target insert changes physical storage but has no derivation/native change because target is not a query input; deleting it while referenced is rejected atomically. An unused table can change without routing. A self-FK/unique catalog accepts the shown two rows but rejects deleting a referenced parent and inserting a duplicate key, preserving Image. Replacing enforced uniqueness with an untrusted hint permits two physical rows with same projected x, counts two derivations, and causes no second native membership change. Indexed fixture selection affects storage implementation only; assertions are semantic and do not claim a scan/index strategy. |
| ownership | Catalog constraints and rows are test-owned; runtime stores copied physical/native state. Image materializes comparisons. |
| failure | Expected constraint_violation errors and image equality guard against partial commit. Any unexpected derivation or support state fails. |
| cost | Across three runtime instances there are eleven apply attempts: seven successful inserts and four constraint_violation rejections. The first constrained runtime commits target, routed-row, and unused-table inserts; the self-reference runtime commits two rows and rejects a referenced-row deletion plus duplicate unique key; the untrusted-hint runtime commits two rows, with the second adding a derivation but no new native support membership. Images guard each rejected mutation, and invariant checks run on the shown successful states. Reference and indexed backends can use different validation/storage work; the test neither counts scanned rows nor reports index work, account bytes, RSS, or CPU. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [include/crown/storage/backend.hpp](../../../../../include/crown/storage/backend.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0028

[Lines 337–355](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L337); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void constants_and_resource_caps() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check constant-route source layouts and rollback at coordinator-work and logical-support caps. |
| inputs / outputs | No inputs; constructs constant true/false empty queries, a work-probe plan, a work-limited plan, and a support-limited boolean plan. |
| invariants | Both constant modes accept an update to their unused source table and retain the table origin in source_layout. Work is sampled from one probe insertion; a second runtime capped at work−1 must throw resource_limit and retain its pre-update Image. An absent erase then commits and invariants hold. A support_limit of 1 allows the first boolean-loop insertion; the next distinct row throws support_overflow and leaves Image unchanged. PhysicalRuntimeOptions.work_limit and SupportOptions.support_limit are distinct asserted caps; indexed fixture per-operation IndexWork ceilings are configured separately and are not measured by these checks. |
| ownership | Plans and update Rows are value-owned; Image copies committed state. Runtime owns source/support state and pending rollback tokens. |
| failure | Expected resource_limit and support_overflow errors must leave state unchanged. Planner/runtime/invariant failures propagate. |
| cost | Seven apply calls span five runtimes: four changed inserts (two constant-route, one work probe, one support-limited), one accepted absent-row erase no-op, one resource_limit rejection, and one support_overflow rejection. The work cap is the probe's measured PhysicalMetrics::work minus one; support_limit is exactly 1. The test captures pre/post Images around both failures and verifies each constant-route state before and after its insert. These are abstract coordinator/support checks, not CPU time, requested bytes, RSS, or an index scan count; indexed operation grants are separately configured and not measured here. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/storage/backend.hpp](../../../../../include/crown/storage/backend.hpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0029

[Lines 356–356](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L356); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L356-L356:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in indexed_physical_runtime_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0030

[Lines 357–366](../../../../../tests/unit/indexed_physical_runtime_test.cpp#L357); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serve as the standalone test executable’s compile-time checks, ordered test runner, and error-to-exit adapter. |
| inputs / outputs | No command-line inputs; invokes seven fixture groups, prints the successful verify count on success, and returns 0; a caught std::exception prints its message and returns 1. |
| invariants | Static assertions require nothrow move construction for PhysicalEpoch and nothrow move construction/assignment for PendingUpdate. Test groups run sequentially; later groups are skipped on the first exception. |
| ownership | All runtime fixtures are local to their test helpers. Output is written to standard streams; no persisted artifact is produced. |
| failure | Any caught std::exception reports failure and returns 1; non-std exceptions are not caught by this handler. |
| cost | Runs the aggregate fixture workload, including 400 generated attempts, data-dependent cleanup, per-event whole-state recomputation, and lifecycle/constraint/error cases. This is test execution cost, not a production latency or resource bound. This review did not execute the test. |
| Design | [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |
