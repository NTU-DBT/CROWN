# `tests/unit/sql_rows_binding_test.cpp` — block usage map

[Source](../../../../../tests/unit/sql_rows_binding_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `49e30bef6baaa13d84d1508dc4cb25232f0e8eb107fe076c5026f07c8b01c18e`. 193 lines partitioned into 12 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../tests/unit/sql_rows_binding_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 13–17](../../../../../tests/unit/sql_rows_binding_test.cpp#L13) | Callable definition: Catalog schema() | calls ; returns {1, {{@ , {{@ , ScalarType::int64, true}, {@ , ScalarType::int64, true}, · [reviewed contract](#b0002) |
| [B0003 · 18–22](../../../../../tests/unit/sql_rows_binding_test.cpp#L18) | Callable definition: SqlRowsProgram compile_rows(std::string_view sql, const Catalog& catalog = schema(), const SqlRowsBindOptions& options = {}) | calls schema, bind_sql_rows, Error, std::move; returns std::get&lt;SqlRowsProgram&gt;(std::move(result)) · [reviewed contract](#b0003) |
| [B0004 · 23–36](../../../../../tests/unit/sql_rows_binding_test.cpp#L23) | Callable definition: bool adapt(const SqlRowsProgram& program, std::size_t occurrence, std::span&lt;const SqlRowCell&gt; input, std::vector&lt;storage::ScalarV… | calls occurrences, scratch, initial_values, begin; guard assert(calls == 0);; returns admitted; growth resize; 2 loop sites · [reviewed contract](#b0004) |
| [B0005 · 37–59](../../../../../tests/unit/sql_rows_binding_test.cpp#L37) | Callable definition: void nullable_outputs() | calls compile_rows, assert, semantics, sources; guard assert(program.semantics() == SqlSemantics::bag && program.sources()\[0\].columns.size() == 4);; 2 loop sites · [reviewed contract](#b0005) |
| [B0006 · 60–80](../../../../../tests/unit/sql_rows_binding_test.cpp#L60) | Callable definition: void guards_and_grounding() | calls compile_rows, assert, export_core, empty; guard assert(local.export_core().query.variables.empty() && local.occurrences()\[0\].projection.empty()); · [reviewed contract](#b0006) |
| [B0007 · 81–102](../../../../../tests/unit/sql_rows_binding_test.cpp#L81) | Callable definition: void constants_parameters_and_receivers() | calls compile_rows, assert, occurrences, empty; guard assert(scalar.occurrences().empty() && scalar.outputs().size() == 3); · [reviewed contract](#b0007) |
| [B0008 · 103–114](../../../../../tests/unit/sql_rows_binding_test.cpp#L103) | Callable definition: void constraint_metadata() | calls schema, push_back, compile_rows, constraints; guard assert(keys.size() == 2 && !keys\[0\].parent && keys\[1\].parent == 0);; growth push_back · [reviewed contract](#b0008) |
| [B0009 · 115–164](../../../../../tests/unit/sql_rows_binding_test.cpp#L115) | Callable definition: void clone_release_and_failure_borrows() | calls resource::MemoryAccount::create, text, bind_sql_rows_into, SqlRowsProgram::freeze; guard assert(source.statistics().current.requested_bytes == resource::MemoryAccount::control_bytes());; growth clone, resize; 3 loop sites · [reviewed contract](#b0009) |
| [B0010 · 165–184](../../../../../tests/unit/sql_rows_binding_test.cpp#L165) | Callable definition: void retained_constant_memory() | calls text, resource::MemoryAccount::create, bind_sql_rows_into, initial_values; guard assert(strings == 1 && bytes == text.size() && program.export_core().query.head.empty());; 4 loop sites · [reviewed contract](#b0010) |
| [B0011 · 185–185](../../../../../tests/unit/sql_rows_binding_test.cpp#L185) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0011) |
| [B0012 · 186–193](../../../../../tests/unit/sql_rows_binding_test.cpp#L186) | Callable definition: int main() | calls nullable_outputs, guards_and_grounding, constants_parameters_and_receivers, constraint_metadata; returns 1 · [reviewed contract](#b0012) |

## B0001

[Lines 1–12](../../../../../tests/unit/sql_rows_binding_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L12:sha256:95105179a9f019dbba39952bcfd4ae819736a88caa915c89ae181eb2f3f7a51a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare sql_rows_binding_test.cpp: include "crown/frontend/sql_rows.hpp", "crown/frontend/normalize.hpp", "crown/api/error.hpp", "sql_rows_eval.hpp", "index_allocation.hpp", &lt;array&gt;, &lt;cassert&gt;, &lt;iostream&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/sql_rows_binding_test.cpp](../../../../../tests/unit/sql_rows_binding_test.cpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 13–17](../../../../../tests/unit/sql_rows_binding_test.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog schema() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide nullable fixture/compiler wrapper and direct allocation-denied adaptation helper. |
| inputs / outputs | Compile to program or throw diagnostic; initialize scratch/output outside deny scope; call adapt and check written dynamic slots empty. |
| invariants | Scope checks operator-new requests only in adapt; no work-failure path is exercised here. |
| ownership | Fixture, input and output backing remain alive through observations. |
| failure | Assertions/compile exceptions fail test; test not run in this review. |
| cost | Cold vectors allowed outside denied interval. |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_rows_eval.hpp §L19-62](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_rows_eval.hpp), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

## B0003

[Lines 18–22](../../../../../tests/unit/sql_rows_binding_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlRowsProgram compile_rows(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile trusted finite test SQL or surface its diagnostic. |
| inputs / outputs | SQL/catalog/options to program. |
| invariants | No fallback changes the requested semantics. |
| ownership | Returned program owns factory metadata. |
| failure | Unexpected rejection throws to main. |
| cost | Cold test compilation; outside allocation-denied adapter intervals. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0004

[Lines 23–36](../../../../../tests/unit/sql_rows_binding_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool adapt(const SqlRowsProgram& program,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the real adapter under denied operator-new. |
| inputs / outputs | Prevalidated finite cells to admission/projected output. |
| invariants | Scratch/output allocation occurs before Scope(0); dynamic input/operation slots must clear after success or filtering. |
| ownership | Temporary scratch borrows program/input only during the call. |
| failure | Unexpected allocation or contract failure fails the test. |
| cost | Cold vector setup plus actual adapter work; asserts zero heap requests in its observed interval. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0005

[Lines 37–59](../../../../../tests/unit/sql_rows_binding_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void nullable_outputs() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise nullable/repeated/local-expression outputs and set isolation. |
| inputs / outputs | Inspect head/decoder reuse, NULL presence flags, borrowed long text, DISTINCT semantics and unchanged old normalize rejection. |
| invariants | Current assertions do not check canonical payload values or reconstruct all output tuples. |
| ownership | Program/input text remains alive; borrowed identity checked. |
| failure | Assertion failure only; not execution evidence from this review. |
| cost | Small finite fixture. |
| Design | [build/verification/w05-sql-rows-human-review-v1/README.md §missing evidence item 1](../../../../../build/verification/w05-sql-rows-human-review-v1/README.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

## B0006

[Lines 60–80](../../../../../tests/unit/sql_rows_binding_test.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void guards_and_grounding() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise joined guards, IS NULL/constant grounding and rejection. |
| inputs / outputs | Check class count, same-occurrence equality guard, NULL/unequal filtering, empty grounded head, contradictions and cross-relation comparison diagnostic. |
| invariants | Grounded Boolean constant values are not currently asserted; F1 needs local-only equality coverage. |
| ownership | All program/input buffers live through assertions. |
| failure | Assertions/variant access can fail; no failure-budget path. |
| cost | Small finite fixture. |
| Design | [build/verification/w05-sql-rows-human-review-v1/README.md §F1 and missing evidence item 1](../../../../../build/verification/w05-sql-rows-human-review-v1/README.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

## B0007

[Lines 81–102](../../../../../tests/unit/sql_rows_binding_test.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void constants_parameters_and_receivers() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise constant/EXISTS/parameter and receiving-account paths. |
| inputs / outputs | Check output descriptors, clone owner/key, source statistics, same-owner no-allocation and missing parameter diagnostic. |
| invariants | Source remains alive during clone assertions; text clone lifetime is not established; key comparison changes SQL too. |
| ownership | Independent receiver created explicitly; same-owner clone shares. |
| failure | Exceptions/assertions fail test; not run in review. |
| cost | Cold allocations except same-owner deny scope. |
| Design | [build/verification/w05-sql-rows-human-review-v1/README.md §missing evidence items 3 and 5](../../../../../build/verification/w05-sql-rows-human-review-v1/README.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

## B0008

[Lines 103–114](../../../../../tests/unit/sql_rows_binding_test.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void constraint_metadata() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check sorted UNIQUE and aligned FK metadata across an unused source. |
| inputs / outputs | Enforced composite key/FK compile to matching sorted parent order and reverse references. |
| invariants | Only descriptor shape tested; data enforcement/nullable policy/self-reference/empty keys remain runtime obligations. |
| ownership | All inspection spans borrow live program. |
| failure | Assertions fail on shape mismatch. |
| cost | Small two-table fixture. |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/src/catalog/catalog.cpp §L89-110](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/catalog/catalog.cpp), [build/verification/w05-sql-rows-human-review-v1/README.md §constraint item 1](../../../../../build/verification/w05-sql-rows-human-review-v1/README.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

## B0009

[Lines 115–164](../../../../../tests/unit/sql_rows_binding_test.cpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void clone_release_and_failure_borrows()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify clone ownership, cleanup and exact-key sensitivity. |
| inputs / outputs | Long text/typed parameters and a failing source allowance. |
| invariants | The original account returns to controller-only storage; cloned names/constants remain valid; work failure clears dynamic slots; same SQL changes key only with changed values/metadata. |
| ownership | Receiver owns cloned bytes after source program/options die. |
| failure | Expected fixed work failure allocates nothing; assertions expose violations. |
| cost | Finite cold compiler/clone cases plus one allocation-denied failing adapter call; not a latency measurement. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0010

[Lines 165–184](../../../../../tests/unit/sql_rows_binding_test.cpp#L165); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void retained_constant_memory()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify measured parameter amplification is removed. |
| inputs / outputs | One 1 MiB string parameter, four grounded aliases and four outputs under a 3 MiB receiver. |
| invariants | Exactly one retained string slot owns 1 MiB; outputs and guards share it; head is nullary; peak stays below 2 MiB. The pre-fix probe retained sixteen copies and exceeded 16 MiB. |
| ownership | Receiver owns metadata; caller text/options stay outside its retained-byte account. |
| failure | Any binding/account/alias/liveness regression fails the actual factory test. |
| cost | One finite cold-memory regression, not a total compiler workspace or elapsed-time benchmark. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [Refactor.md §W05](../../../../../Refactor.md), [build/verification/w05-rows-constant-retention-probe-v1/README.md](../../../../../build/verification/w05-rows-constant-retention-probe-v1/README.md) |

## B0011

[Lines 185–185](../../../../../tests/unit/sql_rows_binding_test.cpp#L185); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L185-L185:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in sql_rows_binding_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/sql_rows_binding_test.cpp](../../../../../tests/unit/sql_rows_binding_test.cpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 186–193](../../../../../tests/unit/sql_rows_binding_test.cpp#L186); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run finite test cases and report failures at executable boundary. |
| inputs / outputs | Calls four fixtures; one top-level std::exception handler prints failure and exits nonzero. |
| invariants | Success text is broader than current alias/identity/lifetime assertions; it is not proof of complete W05 semantics. Includes the measured 1 MiB/four-alias constant-retention cap regression. |
| ownership | Process-local test resources release normally. |
| failure | Narrow test-run presentation handler; no production handling introduced. |
| cost | Finite tests only; no timing claim. |
| Design | [build/verification/w05-sql-rows-human-review-v1/README.md §missing focused evidence](../../../../../build/verification/w05-sql-rows-human-review-v1/README.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |
