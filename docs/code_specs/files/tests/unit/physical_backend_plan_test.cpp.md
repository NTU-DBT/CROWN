# `tests/unit/physical_backend_plan_test.cpp` — block usage map

[Source](../../../../../tests/unit/physical_backend_plan_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `4bbd656575984220638442d5f783dd77aeeebdb301f9f6c5f0ec173fa588c67c`. 281 lines partitioned into 13 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../../tests/unit/physical_backend_plan_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 21–21](../../../../../tests/unit/physical_backend_plan_test.cpp#L21) | Callable definition: void check(bool value,const char* message) | calls std::runtime_error; guard void check(bool value,const char* message) { if (!value) throw std::runtime_error(message); } · [reviewed contract](#b0002) |
| [B0003 · 22–25](../../../../../tests/unit/physical_backend_plan_test.cpp#L22) | Callable definition: template&lt;class F&gt; void error(F&& operation) | calls operation, std::runtime_error · [reviewed contract](#b0003) |
| [B0004 · 26–29](../../../../../tests/unit/physical_backend_plan_test.cpp#L26) | Callable definition: std::string read(const std::filesystem::path& path) | calls input, check, bool; guard std::ifstream input(path);check(bool(input),"fixture unavailable");; returns {std::istreambuf_iterator&lt;char&gt;(input),std::istreambuf_iterator&lt;char&gt;()} · [reviewed contract](#b0004) |
| [B0005 · 30–35](../../../../../tests/unit/physical_backend_plan_test.cpp#L30) | Callable definition: PhysicalOptions indexed_options() | calls ; returns options · [reviewed contract](#b0005) |
| [B0006 · 36–45](../../../../../tests/unit/physical_backend_plan_test.cpp#L36) | Callable definition: Value sample(ScalarType type,std::size_t variation) | calls std::string, push_back, Date::parse, Decimal::parse; returns std::int64_t{9'007'199'254'740'992LL+static_cast&lt;std::int64_t&gt;(variation)}; text; growth push_back · [reviewed contract](#b0006) |
| [B0007 · 46–56](../../../../../tests/unit/physical_backend_plan_test.cpp#L46) | Callable definition: void reference_binding(const PhysicalPlan& plan) | calls identity, sha256, io::write_physical_source, catalog; guard check(plan.physical_sha256()==sha256(expected.dump()),"reference v1 physical binding changed"); · [reviewed contract](#b0007) |
| [B0008 · 57–127](../../../../../tests/unit/physical_backend_plan_test.cpp#L57) | Callable definition: void accounted_binding(const PhysicalPlan& plan) | calls resource::MemoryAccount::create, options, work, oracle_work; guard check(stored.physical_identity()==plan.physical_sha256() && stored.route()==plan.route() &&; growth insert, push_back; 10 loop sites · [reviewed contract](#b0008) |
| [B0009 · 128–182](../../../../../tests/unit/physical_backend_plan_test.cpp#L128) | Callable definition: void populate_and_copy(const PhysicalPlan& plan) | calls storage::IndexWorkAllowance, options, stored, check; guard storage::PlanStorage stored(plan,&work);check(stored.backend()==storage::StorageBackend::indexed_ch…; growth insert, push_back; 12 loop sites; source comment (unverified): // Create sparse identities before copying, including reused arena metadata. · [reviewed contract](#b0009) |
| [B0010 · 183–215](../../../../../tests/unit/physical_backend_plan_test.cpp#L183) | Callable definition: void binding_edges(const Catalog& catalog,const Query& query,const FreeConnexTree& tree) | calls indexed_options, planner::lower_tree, io::write_physical, check; guard const auto revised=planner::lower_tree(catalog,query,tree,changed);check(revised.physical_sha256()!…; 3 loop sites · [reviewed contract](#b0010) |
| [B0011 · 216–257](../../../../../tests/unit/physical_backend_plan_test.cpp#L216) | Callable definition: void normalized_backend() | calls frontend::bind_sql, check, frontend::normalize_sql, planner::lower_normalized; guard check(std::holds_alternative&lt;frontend::BoundSql&gt;(bound),"normalized backend fixture did not bind");; growth emplace_back, push_back; 2 loop sites · [reviewed contract](#b0011) |
| [B0012 · 258–258](../../../../../tests/unit/physical_backend_plan_test.cpp#L258) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0012) |
| [B0013 · 259–281](../../../../../tests/unit/physical_backend_plan_test.cpp#L259) | Callable definition: int main(int argc,char** argv) | calls check, io::Json::parse, read, at; guard check(argc==2,"expected source root");const std::filesystem::path root=argv\[1\];; 2 loop sites · [reviewed contract](#b0013) |

## B0001

[Lines 1–20](../../../../../tests/unit/physical_backend_plan_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L20:sha256:cacd1ebce695fc4d21f2424872765d26bfaa5102e58187225366defd253f430f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare physical_backend_plan_test.cpp: include "crown/io/physical.hpp", "crown/io/tree.hpp", "crown/ir/digest.hpp", "crown/frontend/bind.hpp", "crown/frontend/normalize.hpp", "crown/storage/plan.hpp", "crown/storage/physical.hpp", &lt;algorithm&gt;, &lt;array&gt;, &lt;filesystem&gt;, &lt;fstream&gt;, &lt;iostream&gt;, &lt;iterator&gt;, &lt;map&gt;, &lt;set&gt;, &lt;stdexcept&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/physical_backend_plan_test.cpp](../../../../../tests/unit/physical_backend_plan_test.cpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 21–21](../../../../../tests/unit/physical_backend_plan_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,const char* message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raises a physical-plan test failure on a false predicate. |
| inputs / outputs | Accepts bool and C string message. |
| invariants | Successful branch does not inspect message contents; callers may still build message beforehand. |
| ownership | The literal/pointer is borrowed during the call. |
| failure | False throws std::runtime_error. |
| cost | One branch; no account or runtime work. |
| Design | [tests/unit/physical_backend_plan_test.cpp](../../../../../tests/unit/physical_backend_plan_test.cpp) |

## B0003

[Lines 22–25](../../../../../tests/unit/physical_backend_plan_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class F> void error(F&& operation)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Asserts that a physical operation throws some CROWN Error. |
| inputs / outputs | Takes a forwarding-reference callable but invokes the named parameter as an lvalue with operation(). |
| invariants | Only Error type is checked; error code is deliberately not constrained by this helper. |
| ownership | Callable lifetime follows the caller; the function does not store or forward it. |
| failure | No CROWN Error throws runtime_error; other exception types propagate. |
| cost | One operation invocation; no zero-allocation assertion. |
| Design | [tests/unit/physical_backend_plan_test.cpp](../../../../../tests/unit/physical_backend_plan_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0004

[Lines 26–29](../../../../../tests/unit/physical_backend_plan_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string read(const std::filesystem::path& path)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reads one structural fixture file into an owning string. |
| inputs / outputs | Accepts filesystem path, checks stream open, and returns all file bytes. |
| invariants | The helper does not validate encoding or newline convention. |
| ownership | Returned string owns bytes copied from the input stream. |
| failure | Open/read failure becomes runtime_error; stream/allocation errors propagate. |
| cost | One full-file read into ordinary string storage; size depends on fixture. |
| Design | [tests/unit/physical_backend_plan_test.cpp](../../../../../tests/unit/physical_backend_plan_test.cpp) |

## B0005

[Lines 30–35](../../../../../tests/unit/physical_backend_plan_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalOptions indexed_options()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Builds fixed indexed-storage options for the plan comparison. |
| inputs / outputs | Returns v2 indexed options with nine per-table ceilings and five operation-work dimensions each set to one billion. |
| invariants | Component limits and aggregate work grant are distinct fields; these values are fixture policy, not measured memory. |
| ownership | PhysicalOptions owns the optional IndexedBackendSpec value. |
| failure | No invalid options are generated by this helper. |
| cost | Fixed small option construction; no plan/storage allocation occurs here. |
| Design | [tests/unit/physical_backend_plan_test.cpp](../../../../../tests/unit/physical_backend_plan_test.cpp), [include/crown/storage/plan.hpp](../../../../../include/crown/storage/plan.hpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp) |

## B0006

[Lines 36–45](../../../../../tests/unit/physical_backend_plan_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value sample(ScalarType type,std::size_t variation)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Produces typed fixture values for each supported scalar domain. |
| inputs / outputs | Accepts ScalarType and variation; returns int64 values around 2^53, 128-byte strings with embedded NUL, booleans, endpoint dates, or decimals. |
| invariants | The fixture includes exact large integers and binary string content; unsupported scalar type throws. |
| ownership | Returned Value owns string/decimal payloads. |
| failure | Unsupported type raises runtime_error; scalar construction/allocation errors propagate. |
| cost | One fixture Value per call; 128-byte string payload when string type is selected. |
| Design | [tests/unit/physical_backend_plan_test.cpp](../../../../../tests/unit/physical_backend_plan_test.cpp), [include/crown/ir/scalar.hpp](../../../../../include/crown/ir/scalar.hpp), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp) |

## B0007

[Lines 46–56](../../../../../tests/unit/physical_backend_plan_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reference_binding(const PhysicalPlan& plan)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checks the reference backend physical artifact contract. |
| inputs / outputs | Serializes the supplied PhysicalPlan, checks its exact v1 JSON fields/digests/order/tree, and verifies writer output omits indexed_storage. |
| invariants | Reference artifact schema is 1 with lowerer crown-lower-v1; physical/source identity fields are compared to the fixture. |
| ownership | Plan is borrowed; produced Json owns its serialized tree. |
| failure | Any field or digest mismatch fails via check; serializer errors propagate. |
| cost | One plan serialization and structural comparisons; no storage runtime is constructed by this helper. |
| Design | [tests/unit/physical_backend_plan_test.cpp](../../../../../tests/unit/physical_backend_plan_test.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/storage/plan.hpp](../../../../../include/crown/storage/plan.hpp) |

## B0008

[Lines 57–127](../../../../../tests/unit/physical_backend_plan_test.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void accounted_binding(const PhysicalPlan& plan)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compares bound reference and accounted storage layouts, rows, cursors, and indexes. |
| inputs / outputs | Creates a finite MemoryAccount and aggregate IndexWorkAllowance, builds AccountedPlanStorage, compares plan structure/tokens, inserts variation rows, checks live cursor and index buckets against reference, erases one inserted row where possible, snapshots, and checks sparse IDs/owners. |
| invariants | Checks are fixture-scoped: up to three variations per relation; snapshot retains same layout tokens and live IDs while receiving a distinct table owner. One finite work allowance is reused for stored construction, inserts, cursor/index queries, invariant checks, and erasure; the reference storage uses its own allowance. Ordinary rows/vectors are outside account byte claims. |
| ownership | Storage owns tables/indexes and accounted allocations through account handles; local oracle Rows and expected containers own separate copies. |
| failure | Shape/value mismatches fail assertions; grant, cap, or allocation Errors propagate. |
| cost | Plan-sized table/index setup, three-row loops, cursor/index traversal and snapshot copy; the shared work balance is consumed across construction and subsequent table/index calls, with a separate balance for snapshot copy. Structural work is metered where the API provides it; this test makes no CPU or total-allocation claim. |
| Design | [tests/unit/physical_backend_plan_test.cpp](../../../../../tests/unit/physical_backend_plan_test.cpp), [include/crown/storage/physical.hpp](../../../../../include/crown/storage/physical.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/storage/accounted_plan.cpp](../../../../../src/storage/accounted_plan.cpp), [src/storage/physical.cpp](../../../../../src/storage/physical.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0009

[Lines 128–182](../../../../../tests/unit/physical_backend_plan_test.cpp#L128); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void populate_and_copy(const PhysicalPlan& plan)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checks indexed PlanStorage insertion, snapshots, index membership, and sparse-handle behavior. |
| inputs / outputs | Builds expected indexed PlanStorage, rejects reference/wrong-grant construction, inserts three distinct rows per relation, compares cursor and exact index buckets, erases one handle when possible, snapshots, then checks old/new owners and invalid handles. |
| invariants | Insertion success is compared with set insertion; snapshot rows are also collected into a set, so set equality alone would hide duplicate raw cursor rows, while per-insert success and index member checks add separate assertions. |
| ownership | Snapshots own copied table state with a distinct owner; handles from old tables are not valid in the new owner. Exported Rows and maps/sets are ordinary allocations. |
| failure | Wrong backend/grant, out-of-range IDs, duplicate/invalid handles, or invariant mismatch must throw/assert as specified. |
| cost | Three generated row variants per relation; one finite work allowance is shared across construction, inserts, cursor/index scans, checks and erasure, with a separate allowance for snapshot copy; no CPU or unaccounted allocator benchmark is asserted. |
| Design | [tests/unit/physical_backend_plan_test.cpp](../../../../../tests/unit/physical_backend_plan_test.cpp), [include/crown/storage/physical.hpp](../../../../../include/crown/storage/physical.hpp), [src/storage/physical.cpp](../../../../../src/storage/physical.cpp), [src/storage/accounted_plan.cpp](../../../../../src/storage/accounted_plan.cpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0010

[Lines 183–215](../../../../../tests/unit/physical_backend_plan_test.cpp#L183); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void binding_edges(const Catalog& catalog,const Query& query,const FreeConnexTree& tree)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Probes serialized binding sensitivity and indexed work/cap rejection boundaries. |
| inputs / outputs | Changes each of nine per-table caps and five work dimensions, tampers four indexed specification keys plus guarantee/version fields, then checks zero/over-cap construction boundaries and conditional empty-index behavior. |
| invariants | Physical digest changes for each option perturbation; semantic cache identity is not substituted for physical digest; each work field is separately exercised. |
| ownership | Catalog/query/tree are borrowed; each altered PhysicalOptions and serialized artifact is a local value. |
| failure | Expected errors are accepted by type only through error helper; unexpected successful construction fails. |
| cost | Nine cap mutations, five work mutations, four specification-key mutations, fixed guarantee/version/limit cases, with index-zero probe only for nonempty indexes. |
| Design | [tests/unit/physical_backend_plan_test.cpp](../../../../../tests/unit/physical_backend_plan_test.cpp), [include/crown/storage/physical.hpp](../../../../../include/crown/storage/physical.hpp), [include/crown/storage/plan.hpp](../../../../../include/crown/storage/plan.hpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [src/storage/physical.cpp](../../../../../src/storage/physical.cpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0011

[Lines 216–257](../../../../../tests/unit/physical_backend_plan_test.cpp#L216); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void normalized_backend()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Builds normalized SQL plans for reference and indexed backends and checks replay/storage integration. |
| inputs / outputs | Binds/normalizes one self-join SQL program, lowers both backends, verifies source/cache/physical identity distinctions, roundtrips the indexed artifact, then exercises adapters, enumeration assignments, population/copy, and accounted binding. |
| invariants | Normalized source metadata and semantic cache identity match while indexed physical digest differs; schema-2 artifact and lowerer v2 roundtrip; repeated output positions preserve head order. |
| ownership | NormalizedSql and plan own their bindings; temporary enumerated assignments/Rows are fixture values; storage copies have distinct owners. |
| failure | Lowering, serialization/replay, adapter, assignment, and storage mismatches fail the test. |
| cost | One normalized fixture through both lowerers, one artifact replay, finite adapter/enumeration steps, and storage copies; no wall-clock or CPU cost measurement. |
| Design | [tests/unit/physical_backend_plan_test.cpp](../../../../../tests/unit/physical_backend_plan_test.cpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [src/storage/physical.cpp](../../../../../src/storage/physical.cpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0012

[Lines 258–258](../../../../../tests/unit/physical_backend_plan_test.cpp#L258); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L258-L258:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in physical_backend_plan_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/physical_backend_plan_test.cpp](../../../../../tests/unit/physical_backend_plan_test.cpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 259–281](../../../../../tests/unit/physical_backend_plan_test.cpp#L259); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Loads structural lowering cases and checks both physical backends from the test entry point. |
| inputs / outputs | Requires one source-root argument, reads the manifest and valid case documents/trees, checks reference and indexed lowerings/replay/storage for each, runs binding_edges once after first nonempty index, then normalized_backend. |
| invariants | The loop requires at least ten valid cases and an indexed-edge case; manifest case count is runtime input, not hard-coded as exactly ten. Main has no outer catch, so an uncaught exception terminates rather than producing a custom failure line. |
| ownership | Manifest and fixture JSON are ordinary file/string/Json values; plan/storage objects release at each iteration. |
| failure | Argument errors use check; thrown file/parse/plan failures escape this main. |
| cost | One traversal of each valid manifest case plus one binding_edges and one normalized_backend; no test was run and no runtime timing is claimed. |
| Design | [tests/unit/physical_backend_plan_test.cpp](../../../../../tests/unit/physical_backend_plan_test.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [src/storage/physical.cpp](../../../../../src/storage/physical.cpp), [docs/physical_plans.md](../../../../physical_plans.md) |
