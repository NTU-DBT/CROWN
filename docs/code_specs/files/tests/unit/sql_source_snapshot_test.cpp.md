# `tests/unit/sql_source_snapshot_test.cpp` — block usage map

[Source](../../../../../tests/unit/sql_source_snapshot_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Verify complete physical-source images, actual bindings, limits and retained ownership.

Snapshot SHA-256: `6522c6800e78540ee5b9f5071fdfc6ea7a485d18c65457a767464c9a2a54c183`. 179 lines partitioned into 17 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../tests/unit/sql_source_snapshot_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 16–16](../../../../../tests/unit/sql_source_snapshot_test.cpp#L16) | Callable definition: sql_rows::Cell n(std::int64_t x) | calls ; returns storage::ScalarView{x} · [reviewed contract](#b0002) |
| [B0003 · 17–17](../../../../../tests/unit/sql_source_snapshot_test.cpp#L17) | Callable definition: sql_rows::Cell s(std::string_view x) | calls ; returns storage::ScalarView{x} · [reviewed contract](#b0003) |
| [B0004 · 18–23](../../../../../tests/unit/sql_source_snapshot_test.cpp#L18) | Callable definition: Catalog catalog() | calls ; returns {1, {{@ , {{@ , ScalarType::int64, false}, {@ , ScalarType::string, true}, · [reviewed contract](#b0004) |
| [B0005 · 24–29](../../../../../tests/unit/sql_source_snapshot_test.cpp#L24) | Callable definition: template&lt;class Program&gt; FreeConnexTree tree(const Program& program) | calls export_core, planner::minimum_tree, assert; guard assert(choice.status == planner::OracleStatus::proven_minimum && choice.tree);; returns *choice.tree · [reviewed contract](#b0005) |
| [B0006 · 30–34](../../../../../tests/unit/sql_source_snapshot_test.cpp#L30) | Callable definition: auto rows_program() | calls frontend::bind_sql_rows, catalog, assert, std::move; guard assert(std::holds_alternative&lt;frontend::SqlRowsProgram&gt;(binding));; returns std::get&lt;frontend::SqlRowsProgram&gt;(std::move(binding)) · [reviewed contract](#b0006) |
| [B0007 · 35–39](../../../../../tests/unit/sql_source_snapshot_test.cpp#L35) | Callable definition: auto aggregate_program() | calls frontend::bind_sql_aggregate, catalog, assert, std::move; guard assert(std::holds_alternative&lt;frontend::SqlAggregateProgram&gt;(binding));; returns std::get&lt;frontend::SqlAggregateProgram&gt;(std::move(binding)) · [reviewed contract](#b0007) |
| [B0008 · 40–44](../../../../../tests/unit/sql_source_snapshot_test.cpp#L40) | Callable definition: template&lt;class Action&gt; void error(Action action, std::string_view code) | calls action, assert, code; guard try { action(); } catch (const Error& failure) { assert(failure.code() == code); caught = true; } · [reviewed contract](#b0008) |
| [B0009 · 45–48](../../../../../tests/unit/sql_source_snapshot_test.cpp#L45) | Callable definition: void controller_only(const resource::MemoryAccount& account) | calls check_invariants, assert, statistics, resource::MemoryAccount::control_bytes; guard account.check_invariants(); assert(account.statistics().current.allocations == 1); · [reviewed contract](#b0009) |
| [B0010 · 49–51](../../../../../tests/unit/sql_source_snapshot_test.cpp#L49) | Explanatory comments or spacing. | source comment (unverified): // The image uses complete physical identities, including invisible columns, · [reviewed contract](#b0010) |
| [B0011 · 52–123](../../../../../tests/unit/sql_source_snapshot_test.cpp#L52) | Callable definition: void source_image(bool indexed) | calls rows_program, SqlRowsRuntime, tree, s04_runtime::options; guard assert(initial.sequence == 0 && initial.rows.empty());; 2 loop sites; source comment (unverified): // The image uses complete physical identities, including invisible columns, · [reviewed contract](#b0011) |
| [B0012 · 124–126](../../../../../tests/unit/sql_source_snapshot_test.cpp#L124) | Explanatory comments or spacing. | source comment (unverified): // Composite capture retains the original genuine binding and source recipe · [reviewed contract](#b0012) |
| [B0013 · 127–152](../../../../../tests/unit/sql_source_snapshot_test.cpp#L127) | Callable definition: void composed_lifetime(bool indexed) | calls original, aggregate_program, SqlAggregateRuntime, tree; guard assert(image-&gt;program.identity().binding == runtime.program().identity().binding);; growth emplace; source comment (unverified): // Composite capture retains the original genuine binding and source recipe · [reviewed contract](#b0013) |
| [B0014 · 153–155](../../../../../tests/unit/sql_source_snapshot_test.cpp#L153) | Explanatory comments or spacing. | source comment (unverified): // Constant zero/one native routes still retain authoritative unused physical · [reviewed contract](#b0014) |
| [B0015 · 156–174](../../../../../tests/unit/sql_source_snapshot_test.cpp#L156) | Callable definition: void constant_sources(bool indexed) | calls frontend::bind_sql_aggregate, catalog, assert, std::move; guard assert(std::holds_alternative&lt;frontend::SqlAggregateProgram&gt;(binding));; 1 loop sites; source comment (unverified): // Constant zero/one native routes still retain authoritative unused physical · [reviewed contract](#b0015) |
| [B0016 · 175–175](../../../../../tests/unit/sql_source_snapshot_test.cpp#L175) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0016) |
| [B0017 · 176–179](../../../../../tests/unit/sql_source_snapshot_test.cpp#L176) | Callable definition: int main() | calls source_image, composed_lifetime, constant_sources; 1 loop sites · [reviewed contract](#b0017) |

## B0001

[Lines 1–15](../../../../../tests/unit/sql_source_snapshot_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:68ddbbb1d6b64b1a6578a5113aa61c5d142b348e7b8ded72d24122ddebe4fc44
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare sql_source_snapshot_test.cpp: include "crown/runtime/sql_aggregate.hpp", "crown/planner/oracle.hpp", "indexed_runtime_fixture.hpp", "index_allocation.hpp", &lt;array&gt;, &lt;cassert&gt;, &lt;iostream&gt;, &lt;optional&gt;, &lt;string&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/sql_source_snapshot_test.cpp](../../../../../tests/unit/sql_source_snapshot_test.cpp), [docs/sql_source_images.md](../../../../sql_source_images.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 16–16](../../../../../tests/unit/sql_source_snapshot_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
sql_rows::Cell n(std::int64_t x)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one borrowed integer SQL cell for the physical-source fixture. |
| inputs / outputs | Signed 64-bit test input becomes a ScalarView alternative wrapped as a nullable SqlRowCell. |
| invariants | No conversion to string, weight expansion or ownership of external buffers. |
| ownership | The returned scalar value is by value; no owner is retained. |
| failure | No validation occurs here; invalid test types are rejected later by the real SQL rows runtime. |
| cost | Fixed scalar construction with no explicit dynamic allocation. |
| Design | [tests/unit/sql_source_snapshot_test.cpp](../../../../../tests/unit/sql_source_snapshot_test.cpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp) |

## B0003

[Lines 17–17](../../../../../tests/unit/sql_source_snapshot_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
sql_rows::Cell s(std::string_view x)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one borrowed string SQL cell for source-row fixtures. |
| inputs / outputs | A caller-owned string_view becomes the string ScalarView alternative in a nullable SqlRowCell. |
| invariants | The view is valid only while its backing test string lives; runtime admission copies row payload into its own immutable tuple. |
| ownership | Helper result does not own the characters; fixture locals must outlive prepare/apply. |
| failure | No validation occurs in the helper; source binding/runtime validates the complete row. |
| cost | Fixed view/scalar construction; no character copy by the helper. |
| Design | [tests/unit/sql_source_snapshot_test.cpp](../../../../../tests/unit/sql_source_snapshot_test.cpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [src/runtime/sql_rows.cpp](../../../../../src/runtime/sql_rows.cpp) |

## B0004

[Lines 18–23](../../../../../tests/unit/sql_source_snapshot_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog catalog()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide a real three-table nullable catalog for visible, hidden and unused source rows. |
| inputs / outputs | Catalog contains r(id,g,x,flag), t(id,y), and unused(text); the main SQL reads r while image assertions inspect every TableId. |
| invariants | Schema table order establishes the TableId values used in physical replacements; nullable/string/bool/int fields exercise complete-row retention. |
| ownership | Returns an owned Catalog value used by binders; no global fixture state. |
| failure | Malformed fixture schema or binder rejection aborts assertion-enabled test execution. |
| cost | Small fixed fixture construction only; no runtime image work. |
| Design | [tests/unit/sql_source_snapshot_test.cpp](../../../../../tests/unit/sql_source_snapshot_test.cpp), [include/crown/catalog/catalog.hpp](../../../../../include/crown/catalog/catalog.hpp), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp) |

## B0005

[Lines 24–29](../../../../../tests/unit/sql_source_snapshot_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Program> FreeConnexTree tree(const Program& program)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select a genuine minimum FreeConnex tree from a test program’s exported core query. |
| inputs / outputs | Bound program in; exported catalog/query are passed to planner::minimum_tree; the proven-minimum tree is returned by value. |
| invariants | Test never fabricates a native route; it asserts proven_minimum and a populated tree before constructing a runtime. |
| ownership | Owns a local exported core and planner result; returned tree is an independent value. |
| failure | Failed/no tree is an assertion failure and stops the test before runtime construction. |
| cost | One bounded fixture planner query per program; this is setup, not a source-snapshot cost measure. |
| Design | [tests/unit/sql_source_snapshot_test.cpp](../../../../../tests/unit/sql_source_snapshot_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp) |

## B0006

[Lines 30–34](../../../../../tests/unit/sql_source_snapshot_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto rows_program()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind the actual row-producing SQL fixture through the public SQL rows binder. |
| inputs / outputs | Original SELECT g,x FROM r WHERE flag and catalog in; SqlRowsProgram out only after the binder returns that variant. |
| invariants | Uses real binder identity and source catalog; filtered row is still a physical source entry in the later image. |
| ownership | Returns a copy/move-owned immutable program handle; local catalog/binder diagnostic is released after binding. |
| failure | Unexpected diagnostic/wrong variant fails an assertion before tests proceed. |
| cost | One fixture bind; no source capture cost. |
| Design | [tests/unit/sql_source_snapshot_test.cpp](../../../../../tests/unit/sql_source_snapshot_test.cpp), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp) |

## B0007

[Lines 35–39](../../../../../tests/unit/sql_source_snapshot_test.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto aggregate_program()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind the actual grouped COUNT/SUM SQL fixture through the public aggregate binder. |
| inputs / outputs | Original SELECT g,COUNT(*),SUM(x) ... GROUP BY g and catalog in; genuine SqlAggregateProgram out. |
| invariants | The composed lifetime scenario uses the program’s genuine source program and minimum tree; no logical contribution DTO is admitted. |
| ownership | Returns the immutable shared compiler handle; binding temporaries die locally. |
| failure | Unexpected diagnostic or wrong result alternative fails an assertion. |
| cost | One fixture bind, separate from source-image capture. |
| Design | [tests/unit/sql_source_snapshot_test.cpp](../../../../../tests/unit/sql_source_snapshot_test.cpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp) |

## B0008

[Lines 40–44](../../../../../tests/unit/sql_source_snapshot_test.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void error(Action action, std::string_view code)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that one fixture action raises the expected CROWN Error code. |
| inputs / outputs | Callable and expected code in; returns only after catching a matching crown::Error. |
| invariants | It intentionally does not catch storage::IndexFailure, std::bad_alloc or non-CROWN exceptions; those seams use direct typed catches in the test. |
| ownership | Action closure lifetime is scoped to the assertion; no error object escapes. |
| failure | No matching/mismatched CROWN Error is an assertion failure; another exception propagates. |
| cost | One action plus exception-path test overhead; no production instrumentation. |
| Design | [tests/unit/sql_source_snapshot_test.cpp](../../../../../tests/unit/sql_source_snapshot_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0009

[Lines 45–48](../../../../../tests/unit/sql_source_snapshot_test.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void controller_only(const resource::MemoryAccount& account)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that deleting the last image/runtime owners releases all account allocations except the account controller. |
| inputs / outputs | Account in; checks accounting invariants, exactly one current allocation and control_bytes requested. |
| invariants | Used after snapshot reset, so it proves retained image ownership is finite and tied to handles; it is not a global allocator count. |
| ownership | Borrows account for the check; does not retain it. |
| failure | Failed invariant/allocation equality aborts the test. |
| cost | Constant statistics checks only. |
| Design | [tests/unit/sql_source_snapshot_test.cpp](../../../../../tests/unit/sql_source_snapshot_test.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp) |

## B0010

[Lines 49–51](../../../../../tests/unit/sql_source_snapshot_test.cpp#L49); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L49-L51:sha256:be9157c772dee1888e98779100cef3424410eeb925b5234b5dfeceff9f0b64c6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: The image uses complete physical identities, including invisible columns, filtered rows, SQL NULLs and catalog sources absent from the query body. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_source_snapshot_test.cpp](../../../../../tests/unit/sql_source_snapshot_test.cpp), [docs/sql_source_images.md](../../../../sql_source_images.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 52–123](../../../../../tests/unit/sql_source_snapshot_test.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void source_image(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify standalone source images retain all complete physical rows, limits, immutable payloads and retry behavior on both storage profiles. |
| inputs / outputs | Creates bound rows runtime; commits four replacements across r, t and unused (including filtered/NULL data), then captures bounded source images and performs a later delete. |
| invariants | Asserts exact source order, row weights, full nullable rows, sequence, physical/native binding identity and selected work {12,11,262,0,0}. Row limit counts four entries rather than total weight. Pending epoch and active result cursor are rejected. Later runtime update leaves prior image and long string unchanged. |
| ownership | Image and retained Tuple handles survive input-string mutation and later owner operations; account statistics return to baseline after each denied capture. Source snapshot itself takes no cursor lease. |
| failure | Checks sql_rows_busy, sql_rows_source_limit, typed storage_work_limit and every C++ new-denial ordinal observed in a successful capture. Each failure leaves account current/sequence unchanged and successful retry remains possible. This is not MemoryAccount/native/upb/global malloc fault coverage. |
| cost | Fixture scans four physical entries with 11 nullable fields and 262 string-extent bytes. The allocation loop measures this operation’s C++ replacement-new calls; it is not a throughput or CPU benchmark. |
| Design | [tests/unit/sql_source_snapshot_test.cpp](../../../../../tests/unit/sql_source_snapshot_test.cpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [src/runtime/sql_rows.cpp](../../../../../src/runtime/sql_rows.cpp), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0012

[Lines 124–126](../../../../../tests/unit/sql_source_snapshot_test.cpp#L124); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L124-L126:sha256:f999240330eb0765a63513c6d5b6fb530f5405c37b7b31fc6c933bb157cbc032
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Composite capture retains the original genuine binding and source recipe independently of mutable runtime state or every facade's lifetime. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_source_snapshot_test.cpp](../../../../../tests/unit/sql_source_snapshot_test.cpp), [docs/sql_source_images.md](../../../../sql_source_images.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 127–152](../../../../../tests/unit/sql_source_snapshot_test.cpp#L127); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void composed_lifetime(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify a composed original-SQL aggregate source image owns its compiler and physical row handles past mutable facade lifetime. |
| inputs / outputs | Binds grouped COUNT/SUM, commits one three-weight physical row, then captures sql_aggregate::SourceSnapshot and checks source/outer identity and sequence. |
| invariants | Snapshot pairs the original aggregate program with the child’s complete source image; it does not capture grouped output state or prove a restore protocol. |
| ownership | Moved image keeps the 256-byte source string and program/native metadata after original program and runtime facades are destroyed; account returns to controller-only state after image reset. |
| failure | Prepared batch blocks capture with sql_aggregate_busy. Any assertion/capture failure aborts fixture; no recovery path is tested. |
| cost | Image move under the C++ allocation denial scope makes zero operator-new calls and no account allocations. Capture allocation is tested separately by source_image. |
| Design | [tests/unit/sql_source_snapshot_test.cpp](../../../../../tests/unit/sql_source_snapshot_test.cpp), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [src/runtime/sql_aggregate.cpp](../../../../../src/runtime/sql_aggregate.cpp), [src/runtime/sql_rows.cpp](../../../../../src/runtime/sql_rows.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp) |

## B0014

[Lines 153–155](../../../../../tests/unit/sql_source_snapshot_test.cpp#L153); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L153-L155:sha256:12c27a29e36b7d62ca597522f2c7254b9eaa150eb0396f796ce0271a42f7eca2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Constant zero/one native routes still retain authoritative unused physical rows. Their image cannot be reconstructed from native/group results alone. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_source_snapshot_test.cpp](../../../../../tests/unit/sql_source_snapshot_test.cpp), [docs/sql_source_images.md](../../../../sql_source_images.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 156–174](../../../../../tests/unit/sql_source_snapshot_test.cpp#L156); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void constant_sources(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Show zero/one native routes retain physical rows from catalog tables unused by the SQL result. |
| inputs / outputs | Binds SELECT COUNT(*) and SELECT COUNT(*) FROM r WHERE FALSE; applies one weight-7 row to TableId 2 (unused) and captures the source image. |
| invariants | For each backend/query, image sequence and unused-row identity/weight advance while native root weight stays unchanged. This demonstrates source rows cannot be inferred from native/group output alone. |
| ownership | Runtime and returned image own copied handles; query/program locals are ordinary test values. |
| failure | Binder/source-route/assertion failures fail the fixture; it does not test durable reconstruction. |
| cost | Two fixture queries and one source update each, on both backends; no row multiplicity expansion. |
| Design | [tests/unit/sql_source_snapshot_test.cpp](../../../../../tests/unit/sql_source_snapshot_test.cpp), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [src/runtime/sql_aggregate.cpp](../../../../../src/runtime/sql_aggregate.cpp) |

## B0016

[Lines 175–175](../../../../../tests/unit/sql_source_snapshot_test.cpp#L175); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L175-L175:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in sql_source_snapshot_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/sql_source_snapshot_test.cpp](../../../../../tests/unit/sql_source_snapshot_test.cpp), [docs/sql_source_images.md](../../../../sql_source_images.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 176–179](../../../../../tests/unit/sql_source_snapshot_test.cpp#L176); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the physical source-image fixture on ordered and indexed native storage. |
| inputs / outputs | No arguments; invokes source_image, composed_lifetime and constant_sources once for each backend and prints one success line only after assertions pass. |
| invariants | Each scenario uses real binders, planner outputs and public runtime APIs; a false route is not inferred from result rows. |
| ownership | Function-local accounts/runtimes/images are released before process completion. |
| failure | Assertion, typed limit/fault mismatch or uncaught exception makes the test nonzero. |
| cost | Six scenario/backend executions including finite work-boundary and observed C++ allocation-denial sweeps; not a benchmark. |
| Design | [tests/unit/sql_source_snapshot_test.cpp](../../../../../tests/unit/sql_source_snapshot_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |
