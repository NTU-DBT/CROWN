# `tests/unit/native_program_test.cpp` — block usage map

[Source](../../../../../tests/unit/native_program_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `d16039a75caf104caba59ae2e987540847582115b674c6d49a6710839bc71d73`. 258 lines partitioned into 12 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../tests/unit/native_program_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(sizeof(storage::TupleLayout)==sizeof(storage::AccountedLayout)); · [reviewed contract](#b0001) |
| [B0002 · 16–16](../../../../../tests/unit/native_program_test.cpp#L16) | Callable definition: void check(bool value,std::string_view message) | calls std::runtime_error, std::string; guard void check(bool value,std::string_view message) {if(!value)throw std::runtime_error(std::string(mes… · [reviewed contract](#b0002) |
| [B0003 · 17–38](../../../../../tests/unit/native_program_test.cpp#L17) | Callable definition: PhysicalPlan source_plan(bool indexed,bool sql) | calls planner::lower_tree, s04_runtime::options, frontend::bind_sql, check; guard check(std::holds_alternative&lt;frontend::BoundSql&gt;(bound),"SQL metadata fixture did not bind");; returns planner::lower_tree(catalog,query,tree,indexed?s04_runtime::options():PhysicalOptions{}); planner::…; growth insert; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 39–52](../../../../../tests/unit/native_program_test.cpp#L39) | Callable definition: io::Json copied(program::JsonView value) | calls kind, boolean, integer, unsigned_integer; returns nullptr; value.boolean(); growth push_back; 2 loop sites · [reviewed contract](#b0004) |
| [B0005 · 53–61](../../../../../tests/unit/native_program_test.cpp#L53) | Callable definition: std::vector&lt;const storage::Projection*&gt; projections(const PhysicalPlan& plan) | calls indexes, push_back, inputs, nodes; returns result; growth push_back; 5 loop sites · [reviewed contract](#b0005) |
| [B0006 · 62–70](../../../../../tests/unit/native_program_test.cpp#L62) | Callable definition: std::vector&lt;const storage::AccountedProjection*&gt; projections(const CompiledProgram& plan) | calls indexes, push_back, inputs, nodes; returns result; growth push_back; 5 loop sites · [reviewed contract](#b0006) |
| [B0007 · 71–142](../../../../../tests/unit/native_program_test.cpp#L71) | Callable definition: void complete_copy(bool indexed,bool sql) | calls resource::MemoryAccount::create, std::string, append, push_back; guard check(native.physical_sha256()==physical_hash && copied(native.identity().canonical)==identity,"nat…; growth emplace, push_back; 7 loop sites · [reviewed contract](#b0007) |
| [B0008 · 143–163](../../../../../tests/unit/native_program_test.cpp#L143) | Callable definition: void failure_cleanup(bool indexed) | calls source_plan, resource::MemoryAccount::create, storage::AccountedIndexWork::create, options; guard account.check_invariants();check(account.statistics().current==before,"failed native program constr…; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 164–214](../../../../../tests/unit/native_program_test.cpp#L164) | Callable definition: void native_catalog_io(bool sql) | calls resource::MemoryAccount::create, std::string, source_plan, io::input_catalog_sha256; guard check(!allocated && account.statistics().current==before,; growth insert; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 215–253](../../../../../tests/unit/native_program_test.cpp#L215) | Callable definition: void direct_layout_lifetime() | calls resource::MemoryAccount::create, statistics, binding, emplace; guard check(layout-&gt;context().binding==expected && layout-&gt;origin()==storage::LayoutOrigin{TableId{3},4},; growth emplace · [reviewed contract](#b0010) |
| [B0011 · 254–254](../../../../../tests/unit/native_program_test.cpp#L254) | Closes surrounding scope/type. |  · [reviewed contract](#b0011) |
| [B0012 · 255–258](../../../../../tests/unit/native_program_test.cpp#L255) | Callable definition: int main() | calls direct_layout_lifetime, native_catalog_io, complete_copy, failure_cleanup; returns 0; 1; 1 loop sites · [reviewed contract](#b0012) |

## B0001

[Lines 1–15](../../../../../tests/unit/native_program_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:db22d460ba477ca1a5b13ecd137b0c6798098fda9a743c4c8335e236aa7ff50f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare native_program_test.cpp: include "crown/runtime/program.hpp", "crown/io/batch.hpp", "indexed_runtime_fixture.hpp", "index_allocation.hpp", &lt;array&gt;, &lt;iostream&gt;, &lt;optional&gt;, &lt;sstream&gt;, &lt;stdexcept&gt;; bind local aliases/name imports; require 2 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 16–16](../../../../../tests/unit/native_program_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the native-program fixture’s local assertion gate. |
| inputs / outputs | A bool and string_view message enter; no value is returned. |
| invariants | Only false selects the failure branch. |
| ownership | The string view is borrowed during the call; the helper retains no state. |
| failure | False constructs std::string(message) and throws std::runtime_error. |
| cost | One condition branch; message copying and exception storage occur on failure. |
| Design | [tests/unit/native_program_test.cpp § L16-L16](../../../../../tests/unit/native_program_test.cpp) |

## B0003

[Lines 17–38](../../../../../tests/unit/native_program_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan source_plan(bool indexed
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build either the core source plan or a bound/normalized SQL source plan, optionally with indexed options. |
| inputs / outputs | Two booleans select SQL versus core and indexed versus reference options; the helper returns a lowered PhysicalPlan. |
| invariants | SQL mode binds the shown SELECT DISTINCT fixture, normalizes parameter minimum=5, asserts one core atom, and derives the native scope from its variable terms. Core mode declares r(x,y) and one native node. |
| ownership | Catalog, bind/normalize results, query/tree, and options are local; the returned plan owns its representation. |
| failure | The fixture’s bind, normalize, and one-atom checks use check(); failures from frontend/planner operations propagate without an asserted code. |
| cost | Core builds fixed descriptors; SQL additionally binds and normalizes one fixed statement. No parser cost bound is claimed. |
| Design | [tests/unit/native_program_test.cpp § L17-L38](../../../../../tests/unit/native_program_test.cpp) |

## B0004

[Lines 39–52](../../../../../tests/unit/native_program_test.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::Json copied(program::JsonView value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert a native JSON view recursively into an owning io::Json value for equality comparison. |
| inputs / outputs | A borrowed JsonView enters; a new io::Json scalar, string, array, or object is returned. |
| invariants | The switch handles each listed JsonKind; arrays recurse by index, objects recurse by member and copy each key. |
| ownership | Input view is borrowed during conversion; returned Json owns copied values, strings, and containers. |
| failure | An unrecognized kind falls through to std::runtime_error("unknown native JSON kind"); no JSON text is parsed or synthesized. |
| cost | Visits the JSON tree and creates corresponding output values/keys; work and storage follow the finite input tree. |
| Design | [tests/unit/native_program_test.cpp § L39-L52](../../../../../tests/unit/native_program_test.cpp) |

## B0005

[Lines 53–61](../../../../../tests/unit/native_program_test.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<const storage::Projection*> projections(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect borrowed projection addresses from the public PhysicalPlan descriptor collections for token-identity comparison. |
| inputs / outputs | A borrowed PhysicalPlan enters; the returned vector lists projections from indexes, inputs, node parent/optional-visible descriptors, edges, and enumeration optional parent keys. |
| invariants | The vector is an inventory of the listed collections only; it does not copy descriptors or establish their validity beyond the plan lifetime. |
| ownership | Returned pointers borrow from the supplied plan and cannot outlive its descriptors; the vector owns only pointer values. |
| failure | No test-local failure branch is present; malformed plan access would propagate its ordinary failure. |
| cost | Traverses each listed descriptor collection once and stores one pointer per present projection. |
| Design | [tests/unit/native_program_test.cpp § L53-L61](../../../../../tests/unit/native_program_test.cpp) |

## B0006

[Lines 62–70](../../../../../tests/unit/native_program_test.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<const storage::AccountedProjection*> projections(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect borrowed AccountedProjection addresses from a CompiledProgram using the same inventory order as the source plan helper. |
| inputs / outputs | A borrowed CompiledProgram enters; returned pointers cover indexes, inputs, node parent/optional-visible descriptors, edges, and enumeration optional parent keys. |
| invariants | This helper records the listed descriptor objects only; equality/token relationships are checked by its caller. |
| ownership | Pointers borrow from the CompiledProgram and cannot outlive it; returned vector owns only pointer values. |
| failure | No test-local failure branch is present. |
| cost | Traverses listed collections once and appends a pointer for each present descriptor. |
| Design | [tests/unit/native_program_test.cpp § L62-L70](../../../../../tests/unit/native_program_test.cpp) |

## B0007

[Lines 71–142](../../../../../tests/unit/native_program_test.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void complete_copy(bool indexed
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare selected source-plan metadata, identity, adapter outputs, descriptor tokens, mutable storage layouts, and account release with a frozen CompiledProgram. |
| inputs / outputs | Indexed/SQL switches choose the source; four rows (including an 8192-byte binary string plus NUL/0xff) are adapted, then CompiledProgram::freeze and its native-backed descriptors/storage are exercised. |
| invariants | The assertions compare physical hash and copied canonical identity, selected catalog/query/SQL metadata, unused source layout fields/origin/context, SQL output arity 4 versus core arity 2, repeated-variable validation, pairwise projection-token aliases, and each adapter result against values captured from the source plan. They also check descriptor no-allocation/token identity and final backing-account release. |
| ownership | CompiledProgram and AccountedPlanStorage retain accounted native objects; readable descriptors and grant are reset before the final control-byte assertion; pointer inventories borrow their owners. |
| failure | Only check() failures are asserted in this function; no product error code is specified. |
| cost | Compares four finite rows across source/native adapters and the collected projection inventories pairwise, constructs storage from native.make_storage and again from its retained binding, and reads account counters. No universal copy-cost or allocation-free guarantee is inferred. |
| Design | [tests/unit/native_program_test.cpp § L71-L142](../../../../../tests/unit/native_program_test.cpp) |

## B0008

[Lines 143–163](../../../../../tests/unit/native_program_test.cpp#L143); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void failure_cleanup(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep injected allocation cut positions around CompiledProgram::freeze and check failed construction cleanup plus retry. |
| inputs / outputs | Indexed flag selects one SQL source plan constructed before the sweep. Each cut creates a fresh 8 MiB account and optional indexed work grant, attempts freeze under s04_alloc::Scope, and retries after a triggered bad_alloc. |
| invariants | After each attempt account invariants hold and current account usage equals its baseline. A triggered cut must throw std::bad_alloc and a valid retry must restore baseline usage. The first untriggered cut must not report failure and ends the loop; the sweep-incomplete runtime_error at cut 3999 occurs only if that cut still triggered a failure. |
| ownership | The immutable source plan lives across the entire sweep. Each cut owns its new account/grant and native attempts; failed construction must retain no metadata body according to the account-usage assertion. |
| failure | The only caught product-construction failure is std::bad_alloc; no crown::Error code is tested. |
| cost | Builds the source plan once, then iterates cuts from zero to the first untriggered position, with fail&lt;4000 and one retry per triggered cut. |
| Design | [tests/unit/native_program_test.cpp § L143-L163](../../../../../tests/unit/native_program_test.cpp) |

## B0009

[Lines 164–214](../../../../../tests/unit/native_program_test.cpp#L164); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void native_catalog_io(bool sql)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that a retained native catalog alias survives compiler/program destruction and supports JSON, binary, CSV readers and a typed queue. |
| inputs / outputs | A core or SQL source plan produces a catalog fingerprint and JSON/binary encodings for one insert event; a retained CatalogSource is then used after CompiledProgram leaves scope. |
| invariants | Alias acquisition under allocation fault cut 0 must neither allocate nor change account bytes; fingerprints/encodings remain equal; readers expose a shared native catalog, the decoded update equals the event, non-CSV source positions match, acknowledgements do not fabricate input, and close/enqueue/queue-close preserve sequence 1. |
| ownership | The \`retained\` CatalogSource owns/retains the source binding across native destruction; streams/readers/queue are local, and resetting retained releases backing to account control bytes. |
| failure | Assertions use check() only; no reader/queue error code or failure path is asserted. |
| cost | Serializes one event to two formats, decodes three single-event reader formats, and enqueues one batch; no throughput or memory bound is claimed. |
| Design | [tests/unit/native_program_test.cpp § L164-L214](../../../../../tests/unit/native_program_test.cpp) |

## B0010

[Lines 215–253](../../../../../tests/unit/native_program_test.cpp#L215); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void direct_layout_lifetime()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check direct AccountedLayout creation, copied context/origin lifetime, descriptor validation, invalid-layout cleanup, and final release. |
| inputs / outputs | A one-megabyte account funds two string fields with the same VariableId, context catalog_version 9 and eight binary binding bytes, plus origin TableId 3/source_schema_version 4. A readable descriptor survives resetting the AccountedLayout handle. |
| invariants | Before resetting the layout handle, its copied binding bytes and origin are compared with the supplied values after caller buffers leave scope. After reset, descriptor validation accepts equal repeated-variable values and requires invalid_tuple for unequal values; descriptor context/origin are not re-read there. Five malformed constructors cover wrong scalar kind, decimal precision 39, mixed types for one repeated variable, context catalog_version 0, and origin source_schema_version 0 (with context catalog_version 1). Each requires invalid_layout and unchanged retained account usage. A valid empty layout accepts an empty row. |
| ownership | AccountedLayout owns funded descriptor/context data; the copied readable descriptor retains backing after layout reset; final scope exit must restore baseline bytes. |
| failure | The repeated-variable mismatch checks Error code invalid_tuple; malformed constructors are checked only for TupleValidationFailure issue invalid_layout. No other code is asserted. |
| cost | Uses two initial fields and five malformed-layout attempts, then checks account counters; costs are bounded only by these listed fixture descriptors. |
| Design | [tests/unit/native_program_test.cpp § L215-L253](../../../../../tests/unit/native_program_test.cpp), [include/crown/storage/layout.hpp § L18-L34](../../../../../include/crown/storage/layout.hpp) |

## B0011

[Lines 254–254](../../../../../tests/unit/native_program_test.cpp#L254); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L254-L254:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in native_program_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 255–258](../../../../../tests/unit/native_program_test.cpp#L255); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the direct layout, catalog I/O, and core/SQL indexed/reference copy and allocation-cleanup cases. |
| inputs / outputs | No inputs enter; success returns 0 and a caught std::exception is printed before return 1. |
| invariants | The source call sequence covers direct layout; core and SQL catalog I/O; then both indexed settings for core/SQL complete-copy and failure-cleanup. |
| ownership | Fixture objects are scoped within called functions; the exception is borrowed while printed. |
| failure | Only std::exception is caught at the harness; no product diagnostic code is asserted here. |
| cost | Calls the finite bool matrix shown in main; it does not itself record a test result. |
| Design | [tests/unit/native_program_test.cpp § L255-L258](../../../../../tests/unit/native_program_test.cpp) |
