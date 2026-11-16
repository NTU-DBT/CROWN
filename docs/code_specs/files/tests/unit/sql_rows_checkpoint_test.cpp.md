# `tests/unit/sql_rows_checkpoint_test.cpp` — block usage map

[Source](../../../../../tests/unit/sql_rows_checkpoint_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `4c55f934a292bcb680018edd83ec62de10b08676f9e7b89ca3072b26593a9e4b`. 140 lines partitioned into 16 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 17–17](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L17) | Callable definition: Cell n(std::int64_t x) | calls ; returns storage::ScalarView{x} · [reviewed contract](#b0002) |
| [B0003 · 18–18](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L18) | Callable definition: Cell text(std::string_view x) | calls ; returns storage::ScalarView{x} · [reviewed contract](#b0003) |
| [B0004 · 19–19](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L19) | Callable definition: Cell flag(bool x) | calls ; returns storage::ScalarView{x} · [reviewed contract](#b0004) |
| [B0005 · 20–24](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L20) | Callable definition: frontend::SqlRowsProgram bind(std::string_view sql,const Catalog& catalog) | calls frontend::bind_sql_rows, assert, std::move; guard auto result=frontend::bind_sql_rows(sql,catalog,options);assert(std::holds_alternative&lt;frontend::Sq…; returns std::get&lt;frontend::SqlRowsProgram&gt;(std::move(result)) · [reviewed contract](#b0005) |
| [B0006 · 25–28](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L25) | Callable definition: FreeConnexTree tree(const frontend::SqlRowsProgram& program) | calls export_core, contradiction, empty, planner::minimum_tree; guard const auto chosen=planner::minimum_tree(core.catalog,core.query);assert(chosen.tree);return *chosen…; returns {}; *chosen.tree · [reviewed contract](#b0006) |
| [B0007 · 29–36](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L29) | Callable definition: Bag rows(runtime::SqlRowsRuntime& runtime) | calls results, next, io::Json::array, view; guard assert(result.emplace(values.dump(),next-&gt;multiplicity).second);; returns result; growth emplace, push_back; 2 loop sites · [reviewed contract](#b0007) |
| [B0008 · 37–40](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L37) | Callable definition: rr::CheckpointMetadata metadata(const rr::Descriptor& descriptor,std::uint64_t c,std::uint64_t i) | calls fill, sha256; returns {{query,descriptor.sha256()},2,c,i,{sink,c,1,hash}} · [reviewed contract](#b0008) |
| [B0009 · 41–45](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L41) | Callable definition: runtime::sql_rows::RebuildLimits build(bool indexed) | calls ; returns limits · [reviewed contract](#b0009) |
| [B0010 · 46–48](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L46) | Callable definition: template&lt;class Action&gt; void rejected(Action action) | calls action, assert; guard bool failed=false;try{action();}catch(const recovery::ImageFailure&){failed=true;}assert(failed); · [reviewed contract](#b0010) |
| [B0011 · 49–51](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L49) | Callable definition: template&lt;class Action&gt; void refused(Action action) | calls action, assert; guard bool failed=false;try{action();}catch(const std::exception&){failed=true;}assert(failed); · [reviewed contract](#b0011) |
| [B0012 · 52–106](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L52) | Callable definition: void round_trip(bool indexed) | calls bind, resource::MemoryAccount::create, rr::admit_into, tree; guard const Bag expected{{"\[1,null,7\]",10},{"\[2,\"\",7\]",4}};assert(rows(live.runtime)==expected);; growth push_back; 4 loop sites; source comment (unverified): // All restored TEXT and rows now have independent receiving ownership. · [reviewed contract](#b0012) |
| [B0013 · 107–120](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L107) | Callable definition: void static_and_terminal() | calls bind, resource::MemoryAccount::create, rr::admit_into, progress; guard assert(rows(restored.runtime)==(truth?Bag{{"\[null,true\]",1}}:Bag{}));; 1 loop sites · [reviewed contract](#b0013) |
| [B0014 · 121–134](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L121) | Callable definition: void semantic_rows() | calls push_back, bind, resource::MemoryAccount::create, rr::admit_into; guard assert(receiver.statistics().current.allocations==1);receiver.check_invariants();; growth copy_of, push_back · [reviewed contract](#b0014) |
| [B0015 · 135–135](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L135) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0015) |
| [B0016 · 136–140](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L136) | Callable definition: int main() | calls round_trip, static_and_terminal, semantic_rows, what; returns 1; 1 loop sites · [reviewed contract](#b0016) |

## B0001

[Lines 1–16](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L16:sha256:160edd5bc9f8db50526e51efdbb08ed916ce6dc9645fa55d9bf39cb3013af18e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare finite checkpoint-test dependencies, aliases and memory cap. |
| inputs / outputs | Include checkpoint/document/planner and test storage/allocation/assertion/map helpers; define Bag/Cell/rr aliases and 64MiB fixture cap. |
| invariants | Declarations are test setup only; no assertion receipt or runtime action is produced. |
| ownership | No new runtime backing storage from declarations; actual declared views/handles obey their named type lifetimes. |
| failure | Compile-time checking only in this span; invoked member/helper operations have separately specified failures. |
| cost | Include/type/signature/constant declarations only; no executed codec/binder/hash/sort/native work or backing allocation. |
| Design | [tests/unit/sql_rows_checkpoint_test.cpp](../../../../../tests/unit/sql_rows_checkpoint_test.cpp) |

## B0002

[Lines 17–17](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L17:sha256:331b85b0edb403e9173638c1c48b020b4eccbf7ab2f1ce958dddc9a7ae9b6cc8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one inline int64 test Cell. |
| inputs / outputs | The int64_t argument becomes an engaged optional ScalarView Cell. |
| invariants | The helper performs no schema admission or owning tuple conversion. |
| ownership | Returned inline int64 value is copied; no borrowed payload or account owner. |
| failure | No intentional validation/failure for int64 input. |
| cost | Fixed optional/variant construction; no allocation. |
| Design | [tests/unit/sql_rows_checkpoint_test.cpp](../../../../../tests/unit/sql_rows_checkpoint_test.cpp) |

## B0003

[Lines 18–18](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L18:sha256:b7f9bc53123a302b3ace96c96332946f3606f984acc207c8b25c2c0aebc470e4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a test string; production ownership is tested separately. |
| inputs / outputs | The string_view argument becomes an engaged optional ScalarView Cell. |
| invariants | No UTF8/schema/ownership validation occurs. |
| ownership | Returned string_view borrows caller backing; no text copy or owner. |
| failure | No intentional validation/failure for a live string_view. |
| cost | Fixed pointer/length optional/variant construction; no byte traversal or allocation. |
| Design | [tests/unit/sql_rows_checkpoint_test.cpp](../../../../../tests/unit/sql_rows_checkpoint_test.cpp) |

## B0004

[Lines 19–19](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L19:sha256:a5469713576c93d157f5c8d0e1c2f87d0723b119910ac4d3513d02791f2c483a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one inline Boolean test Cell. |
| inputs / outputs | The bool argument becomes an engaged optional ScalarView Cell. |
| invariants | The helper performs no schema admission or owning tuple conversion. |
| ownership | Returned inline Boolean is copied; no borrowed payload or account owner. |
| failure | No intentional failure. |
| cost | Fixed optional/variant construction; no allocation. |
| Design | [tests/unit/sql_rows_checkpoint_test.cpp](../../../../../tests/unit/sql_rows_checkpoint_test.cpp) |

## B0005

[Lines 20–24](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L24:sha256:a1b099a3bd743f40b9fb07d36f548e7c3a21ae3609a7ca44116ccf4ae3e1e72f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require genuine original nonaggregate SQL factory admission for the test query. |
| inputs / outputs | Fixture SQL/catalog -&gt; genuine SqlRowsProgram through bind_sql_rows with retain_binding_image=true. |
| invariants | Asserts this fixture is admitted and requests retained metadata for Descriptor construction. No universal binder-equivalence assertion follows. |
| ownership | Factory program owns immutable metadata through its account; fixture strings/catalog are ordinary caller values. |
| failure | A diagnostic fails assert; parser/allocation exceptions propagate to main. |
| cost | Actual cold SQL parsing/binding/normalization and metadata allocation. |
| Design | [tests/unit/sql_rows_checkpoint_test.cpp](../../../../../tests/unit/sql_rows_checkpoint_test.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp) |

## B0006

[Lines 25–28](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L28:sha256:c68b285988dc30eb5ecd91e2e57cc43d5d4d5cc51595189bf213b35da72f0118
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return an empty constant/contradictory tree or the exact planner tree for this fixture. |
| inputs / outputs | Genuine fixture Program -&gt; empty FreeConnexTree for contradiction/zero core atoms, otherwise planner::minimum_tree(...).tree. |
| invariants | On nonconstant path asserts only chosen.tree is present; no certificate replay or status assertion is performed here. |
| ownership | Core/tree DTOs own ordinary metadata; the immutable program is borrowed. |
| failure | Failed fixture assertions or planner/resource exceptions stop the test. |
| cost | Cold core export and actual finite exact search; may allocate and is not a per-update operation. |
| Design | [tests/unit/sql_rows_checkpoint_test.cpp](../../../../../tests/unit/sql_rows_checkpoint_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp) |

## B0007

[Lines 29–36](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L36:sha256:648b1cf7489b5eaeffb491c8d6233cb56f6ce3ce58b9f84497065e479d80eada
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the real public compressed SQL cursor into typed JSON keys, rejecting duplicate output records. |
| inputs / outputs | A mutable SqlRowsRuntime opens/drains results() and returns JSON-key→multiplicity std::map. |
| invariants | Asserts no duplicate compressed output keys; the cursor is drained to terminal next. |
| ownership | Cursor temporarily leases runtime. Returned map/JSON strings own ordinary test output; tuples are read while live. |
| failure | Duplicate insertion fails assert; cursor/serialization/allocation failures propagate. |
| cost | Enumerate all returned compressed rows, encode fields/bytes and allocate/logarithmically insert ordinary map entries. |
| Design | [tests/unit/sql_rows_checkpoint_test.cpp](../../../../../tests/unit/sql_rows_checkpoint_test.cpp) |

## B0008

[Lines 37–40](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L40:sha256:79d9e09505438ee966ecc9ab0b760408d23922a882737ffc139a6fce0c9f764b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build explicit C/I/delivery fixture DTOs; these do not claim actual file receipt authority. |
| inputs / outputs | Descriptor and C/I numbers produce the stated fixed query/sink/hash/generation delivery DTO. |
| invariants | No actual sink receipt, source state or durable selection is validated. |
| ownership | Returned fixed arrays/scalars own their values. |
| failure | No intentional failure for the fixture arguments. |
| cost | Fixed array fill/copies; no native/account allocation. |
| Design | [tests/unit/sql_rows_checkpoint_test.cpp](../../../../../tests/unit/sql_rows_checkpoint_test.cpp) |

## B0009

[Lines 41–45](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L45:sha256:9b125cd02c216e9c16c7d54070b485cf3b3c1c9852022cd16d6fd6f2a282502f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Supply a separate finite cold indexed grant only for the indexed backend. |
| inputs / outputs | Indexed flag selects default RebuildLimits plus the explicit five-domain indexed work tuple. |
| invariants | Only a limits DTO is created; no work grant is consumed/refilled or runtime constructed. |
| ownership | Returned limits are plain values. |
| failure | No intentional failure. |
| cost | Fixed construction/branch; no allocation. |
| Design | [tests/unit/sql_rows_checkpoint_test.cpp](../../../../../tests/unit/sql_rows_checkpoint_test.cpp) |

## B0010

[Lines 46–48](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L46-L48:sha256:7363eaa4615067276b5902688ffd70f74c98eb1d6bc241cc5a34a2a20fd9ca0a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require the fixed image rejection carrier for this deliberate invalid input. |
| inputs / outputs | Invoke the supplied Action; assert that it throws ImageFailure. |
| invariants | Only the asserted exception occurrence is established; the action’s semantic state is checked by its caller. |
| ownership | The helper owns no runtime/output data. |
| failure | A missing expected exception fails assert; exceptions outside the caught type propagate. |
| cost | One action call and fixed exception/assert logic, plus the action’s own costs. |
| Design | [tests/unit/sql_rows_checkpoint_test.cpp](../../../../../tests/unit/sql_rows_checkpoint_test.cpp) |

## B0011

[Lines 49–51](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L49-L51:sha256:01898462e902183a11d5062c82822ab41cd6f38355030d519cd7fe29e2ea7166
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require refusal of this finite semantic/terminal native operation; following assertions test retained state. |
| inputs / outputs | Invoke the supplied Action; assert that it throws std::exception. |
| invariants | Only the asserted exception occurrence is established; the action’s semantic state is checked by its caller. |
| ownership | The helper owns no runtime/output data. |
| failure | A missing expected exception fails assert; exceptions outside the caught type propagate. |
| cost | One action call and fixed exception/assert logic, plus the action’s own costs. |
| Design | [tests/unit/sql_rows_checkpoint_test.cpp](../../../../../tests/unit/sql_rows_checkpoint_test.cpp) |

## B0012

[Lines 52–106](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L52-L106:sha256:68428ee7c05af58edaa20d752e3112798ee30b9451e64075b7bbe0ac4925d7ff
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert this9-physical-row bag fixture, C2/I5/progress/reader restoration, canonical reorder/duplicate behavior, independent expected current rows, next encoded delta and corruption/limit refusal. |
| inputs / outputs | Indexed backend flag -&gt; void after full physical checkpoint round-trip/current/next-delta and refusal assertions. |
| invariants | This is a finite test helper/assertion body, not an execution receipt or proof for other inputs. |
| ownership | Fixture DTOs/expected bytes/maps use ordinary test storage; actual programs/runtimes/codecs use the explicitly created accounts and local owners. |
| failure | The exact catches/assertions in this body check expected refusals; all unhandled failures reach main. No production catch or recovery action is introduced. |
| cost | Cold compile/tree/admission, two source batches, physical captures, canonical checkpoint encode/restore and hostile controls, current result cursor→JSON-map oracles, two next-output updates/encodes/commits, six cap checks and all truncation/bit loops. Real runtime/source/codec owners and ordinary maps/strings allocate. |
| Design | [tests/unit/sql_rows_checkpoint_test.cpp](../../../../../tests/unit/sql_rows_checkpoint_test.cpp) |

## B0013

[Lines 107–120](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L107-L120:sha256:633a6058b9a7cb35284e205b4333acf74e6f415f4bcc5fe929fe3d62abd394bb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the two stated zero-source SQL routes at C0 and UINT64_MAX restoration/refusal of wrapping next sequence. |
| inputs / outputs | No arguments -&gt; void after both fixed truth/false constant-query C0 and terminal-sequence assertions. |
| invariants | This is a finite test helper/assertion body, not an execution receipt or proof for other inputs. |
| ownership | Fixture DTOs/expected bytes/maps use ordinary test storage; actual programs/runtimes/codecs use the explicitly created accounts and local owners. |
| failure | The exact catches/assertions in this body check expected refusals; all unhandled failures reach main. No production catch or recovery action is introduced. |
| cost | Two constant SQL compiles; each uses one genuine admission, two physical checkpoint encodes/restores, one current result cursor and one wrapping-prepare refusal. Zero source rows avoid physical key data; real metadata/runtime/frames and ordinary expected maps allocate. |
| Design | [tests/unit/sql_rows_checkpoint_test.cpp](../../../../../tests/unit/sql_rows_checkpoint_test.cpp) |

## B0014

[Lines 121–134](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L121-L134:sha256:472db9bea99f4c7de5fb50de0d7a192f67c65c6bf557213f106101ebb5ab3461
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode/inspect two well-typed but UNIQUE-conflicting physical rows, then assert genuine cold restore refuses and releases the receiving account. |
| inputs / outputs | No arguments -&gt; void after typed UNIQUE-conflicting source image cold-restore refusal. |
| invariants | This is a finite test helper/assertion body, not an execution receipt or proof for other inputs. |
| ownership | Fixture DTOs/expected bytes/maps use ordinary test storage; actual programs/runtimes/codecs use the explicitly created accounts and local owners. |
| failure | The exact catches/assertions in this body check expected refusals; all unhandled failures reach main. No production catch or recovery action is introduced. |
| cost | Cold UNIQUE fixture compile/tree/admission, two receiving Tuple copies into editable source DTO, checkpoint encode/inspection and one genuine cold-restore denial with account cleanup. No committed source update or result cursor. |
| Design | [tests/unit/sql_rows_checkpoint_test.cpp](../../../../../tests/unit/sql_rows_checkpoint_test.cpp) |

## B0015

[Lines 135–135](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L135); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L135-L135:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the stated namespace/type scope. |
| inputs / outputs | No runtime input or output. |
| invariants | No new checks or state transitions. |
| ownership | No ownership operation. |
| failure | No executable failure path. |
| cost | No runtime work/allocation. |
| Design | [tests/unit/sql_rows_checkpoint_test.cpp](../../../../../tests/unit/sql_rows_checkpoint_test.cpp) |

## B0016

[Lines 136–140](../../../../../tests/unit/sql_rows_checkpoint_test.cpp#L136); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L136-L140:sha256:389d142dc7276b8430b7edf716e4f3eb6199feabb9f089c4e4fa20369779968c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run both-backend physical round-trip and the single static/terminal/semantic-row assertion families. |
| inputs / outputs | No arguments; invokes exactly the assertion families listed here and returns0, or1 for an unexpected std::exception. |
| invariants | Passing this body establishes only those finite assertions when run with asserts enabled. |
| ownership | Local test fixtures unwind normally; the harness owns stdout/stderr. |
| failure | Expected helper catches are local; main prints unexpected exceptions and returns failure. |
| cost | Sum of called finite tests and report output; not a benchmark or production operation. |
| Design | [tests/unit/sql_rows_checkpoint_test.cpp](../../../../../tests/unit/sql_rows_checkpoint_test.cpp) |
