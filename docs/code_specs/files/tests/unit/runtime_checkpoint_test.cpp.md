# `tests/unit/runtime_checkpoint_test.cpp` — block usage map

[Source](../../../../../tests/unit/runtime_checkpoint_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `a67602f29b5881362e3e9c52bafe0da2574aca90809583ef39ec01a1a5bdc292`. 185 lines partitioned into 13 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../tests/unit/runtime_checkpoint_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 13–13](../../../../../tests/unit/runtime_checkpoint_test.cpp#L13) | Callable definition: void check(bool condition,const char* message) | calls std::runtime_error; guard void check(bool condition,const char* message){if(!condition)throw std::runtime_error(message);} · [reviewed contract](#b0002) |
| [B0003 · 14–14](../../../../../tests/unit/runtime_checkpoint_test.cpp#L14) | Callable definition: std::string_view bytes(const recovery::EncodedImage& image) | calls data, size; returns {image.bytes.data(),image.bytes.size()} · [reviewed contract](#b0003) |
| [B0004 · 15–24](../../../../../tests/unit/runtime_checkpoint_test.cpp#L15) | Callable definition: PhysicalPlan plan(bool indexed,std::optional&lt;storage::IndexWork&gt; work={}) | calls s04_runtime::options, planner::lower_tree; returns planner::lower_tree(catalog,query,tree,options) · [reviewed contract](#b0004) |
| [B0005 · 25–25](../../../../../tests/unit/runtime_checkpoint_test.cpp#L25) | Callable definition: Row left(std::int64_t key) | calls std::string; returns {std::string(4096,@ )+std::string(@ ,2),key} · [reviewed contract](#b0005) |
| [B0006 · 26–28](../../../../../tests/unit/runtime_checkpoint_test.cpp#L26) | Callable definition: resource::MemoryAccount account(DeltaRuntime& value) | calls RuntimeTestProbe::memory_account, RuntimeTestProbe::support, RuntimeTestProbe::physical; returns RuntimeTestProbe::memory_account(RuntimeTestProbe::support(RuntimeTestProbe::physical(value))) · [reviewed contract](#b0006) |
| [B0007 · 29–29](../../../../../tests/unit/runtime_checkpoint_test.cpp#L29) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0007) |
| [B0008 · 30–34](../../../../../tests/unit/runtime_checkpoint_test.cpp#L30) | Callable definition: Output apply(DeltaRuntime& value,const PhysicalSetUpdate& update) | calls next, check, emplace, storage::export_row; guard while(auto row=epoch.next())check(result.emplace(row-&gt;operation,storage::export_row(row-&gt;tuple.valu…; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 35–38](../../../../../tests/unit/runtime_checkpoint_test.cpp#L35) | Callable definition: void barrier(DeltaRuntime& value) | calls checkpoint_image, code, check; guard check(failed,"nonquiescent checkpoint accepted"); · [reviewed contract](#b0009) |
| [B0010 · 39–154](../../../../../tests/unit/runtime_checkpoint_test.cpp#L39) | Callable definition: void scenario(bool indexed,LiveMaintenance maintenance,DeltaCompletion completion,DeltaMode mode,BuildMethod method,bool faults) | calls plan, CompiledProgram::standalone, original, apply; guard check(captures&gt;0 && captures==memory.statistics().successful_allocations-before.successful_allocati…; growth copy_of, insert; 5 loop sites · [reviewed contract](#b0010) |
| [B0011 · 155–170](../../../../../tests/unit/runtime_checkpoint_test.cpp#L155) | Callable definition: void released_source(bool indexed) | calls plan, CompiledProgram::standalone, source, account; guard check(source_account.statistics().current.allocations==2,"image retained original runtime graph aft…; growth insert · [reviewed contract](#b0011) |
| [B0012 · 171–171](../../../../../tests/unit/runtime_checkpoint_test.cpp#L171) | Closes surrounding scope/type. |  · [reviewed contract](#b0012) |
| [B0013 · 172–185](../../../../../tests/unit/runtime_checkpoint_test.cpp#L172) | Callable definition: int main() | calls released_source, scenario, what; returns 1; 3 loop sites · [reviewed contract](#b0013) |

## B0001

[Lines 1–12](../../../../../tests/unit/runtime_checkpoint_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L12:sha256:e561b30cd5b8591c9ccad5be24ae45a4ef4353c0b6023de3a776f359bbffece9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare runtime_checkpoint_test.cpp: include "indexed_runtime_fixture.hpp", "runtime_probe.hpp", "index_allocation.hpp", "crown/runtime/delta.hpp", "crown/runtime/memory_report.hpp", &lt;iostream&gt;, &lt;optional&gt;, &lt;stdexcept&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/runtime_checkpoint_test.cpp](../../../../../tests/unit/runtime_checkpoint_test.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 13–13](../../../../../tests/unit/runtime_checkpoint_test.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition,const char* message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail one runtime checkpoint assertion with its diagnostic. |
| inputs / outputs | Takes a predicate and borrowed literal; false throws std::runtime_error. |
| invariants | It does not catch public CROWN Error or recovery ImageFailure categories. |
| ownership | The diagnostic is caller-owned until a failure exception is built. |
| failure | Only assertion failure raises. |
| cost | One predicate; literal diagnostic avoids fixture data copies. |
| Design | [tests/unit/runtime_checkpoint_test.cpp](../../../../../tests/unit/runtime_checkpoint_test.cpp), [docs/checkpoints.md § Native runtime component](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0003

[Lines 14–14](../../../../../tests/unit/runtime_checkpoint_test.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view bytes(const recovery::EncodedImage& image)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the bytes from an owning EncodedImage for restore and mutation probes. |
| inputs / outputs | Returns a string_view over the image's vector without copying. |
| invariants | The view is valid only while the same image remains alive and unchanged. |
| ownership | EncodedImage owns bytes on the source query account; restore borrows them synchronously. |
| failure | A moved-from/empty image is rejected by the codec rather than repaired here. |
| cost | Constant-time view construction; no native allocation or byte copy. |
| Design | [tests/unit/runtime_checkpoint_test.cpp](../../../../../tests/unit/runtime_checkpoint_test.cpp), [docs/checkpoints.md § Native runtime component](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0004

[Lines 15–24](../../../../../tests/unit/runtime_checkpoint_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan plan(bool indexed,std::optional<storage::IndexWork> work={})
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a two-relation join plan and optionally constrain the indexed backend's per-operation grant. |
| inputs / outputs | Takes indexed selection plus optional IndexWork; returns a lower-tree PhysicalPlan over string/int rows. |
| invariants | Only the backend and optional per-operation work limit vary; source/query identity remains deterministic for each selection. |
| ownership | Catalog/query/tree and planner-owned plan state are constructed locally; the eventual runtime account is distinct. |
| failure | Planner rejection or invalid backend work propagates before test execution. |
| cost | Fixed two-table plan construction; source strings/plan metadata are ordinary fixture inputs before runtime account admission. |
| Design | [tests/unit/runtime_checkpoint_test.cpp](../../../../../tests/unit/runtime_checkpoint_test.cpp), [docs/checkpoints.md § Native runtime component](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0005

[Lines 25–25](../../../../../tests/unit/runtime_checkpoint_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row left(std::int64_t key)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a full native/test Row with a 4 KiB binary string and requested integer key. |
| inputs / outputs | Returns an owning Row by value. |
| invariants | The string contains embedded NUL and 0xff bytes, so later image comparison covers byte-preserving scalar handling. |
| ownership | The caller owns the ordinary Row; runtime ingestion later creates its native account-owned representation. |
| failure | Standard Row/string allocation can fail before the runtime API is entered. |
| cost | One bounded string allocation and row copy; not charged to the runtime until native admission copies it. |
| Design | [tests/unit/runtime_checkpoint_test.cpp](../../../../../tests/unit/runtime_checkpoint_test.cpp), [docs/checkpoints.md § Native runtime component](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0006

[Lines 26–28](../../../../../tests/unit/runtime_checkpoint_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryAccount account(DeltaRuntime& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the physical runtime's original query MemoryAccount through test-only owner probes. |
| inputs / outputs | Takes DeltaRuntime& and returns its shared resource account by value. |
| invariants | This depends on CROWN_RUNTIME_TESTING probes and is not a public production accounting API. |
| ownership | Returned account shares the underlying controller with the runtime; the probe does not create another budget. |
| failure | Probe misuse or a moved-from runtime is a test failure/exception. |
| cost | Fixed shared-account handle; no row graph or new memory grant is created. |
| Design | [tests/unit/runtime_checkpoint_test.cpp](../../../../../tests/unit/runtime_checkpoint_test.cpp), [docs/checkpoints.md § Native runtime component](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0007

[Lines 29–29](../../../../../tests/unit/runtime_checkpoint_test.cpp#L29); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L29:sha256:0ac89d782deaeb853b315d4191d6a97d0d2cf9bf8bbdabfb653b56b27e2d4974
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare runtime_checkpoint_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/runtime_checkpoint_test.cpp](../../../../../tests/unit/runtime_checkpoint_test.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 30–34](../../../../../tests/unit/runtime_checkpoint_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Output apply(DeltaRuntime& value,const PhysicalSetUpdate& update)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one update and export its delta rows into an ordinary set for source/restored comparison. |
| inputs / outputs | Begins and commits one DeltaRuntime epoch, consumes the output cursor, and returns sign/full-row pairs. |
| invariants | Duplicate signed rows fail; the result is a set oracle, so it does not assert output ordinal ordering. |
| ownership | DeltaRuntime owns native output until consumed; each exported Row and set node is ordinary test memory. |
| failure | Duplicate output fails immediately; engine/resource errors propagate as public errors. |
| cost | Processes one update's native derivations and output; exported full-row copies are outside the runtime account. |
| Design | [tests/unit/runtime_checkpoint_test.cpp](../../../../../tests/unit/runtime_checkpoint_test.cpp), [docs/checkpoints.md § Native runtime component](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0009

[Lines 35–38](../../../../../tests/unit/runtime_checkpoint_test.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void barrier(DeltaRuntime& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require checkpoint capture to reject a nonquiescent DeltaRuntime. |
| inputs / outputs | Tries checkpoint_image and accepts only an Error with code runtime_busy. |
| invariants | A private pending epoch, active result cursor, or unread output must remain a barrier; unrelated errors do not satisfy the test. |
| ownership | Temporary image/result lives only inside the failed attempt; source runtime remains test-owned. |
| failure | Normal return or a different Error code fails the assertion. |
| cost | One expected barrier attempt; no image payload should be retained or materialized. |
| Design | [tests/unit/runtime_checkpoint_test.cpp](../../../../../tests/unit/runtime_checkpoint_test.cpp), [docs/checkpoints.md § Native runtime component](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0010

[Lines 39–154](../../../../../tests/unit/runtime_checkpoint_test.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scenario(bool indexed,LiveMaintenance maintenance,DeltaCompletion completion,DeltaMode mode,BuildMethod method,bool faults)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare complete runtime checkpoint/restore across the selected policy matrix and next-update behavior. |
| inputs / outputs | Parameters select backend, live maintenance, completion strategy, Delta mode, rebuild method, and whether fail-after probes run. |
| invariants | Restoration must reproduce canonical logical/source/support/live state and one indexed grant; histories/owner IDs may restart. Only direct/on-output has exhaustive allocator cuts here. |
| ownership | Original runtime and held image use original account; restored graph uses a fresh receiving account; reports and next-delta sets are exported test values. |
| failure | Rejects policy/program mismatch, zero indexed admission work, checksum-valid duplicate/schema-invalid bases, query cap and rebuild work failures without changing source state. |
| cost | Fixed small join with four updates and twenty repeated captures; native table/index/support rebuild allocations use each runtime account; canonical reports and exported rows allocate ordinary test memory. |
| Design | [tests/unit/runtime_checkpoint_test.cpp](../../../../../tests/unit/runtime_checkpoint_test.cpp), [docs/checkpoints.md § Native runtime component](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0011

[Lines 155–170](../../../../../tests/unit/runtime_checkpoint_test.cpp#L155); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void released_source(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep a held checkpoint image usable after its source runtime is destroyed, then release only the image payload. |
| inputs / outputs | Captures an image in a local DeltaRuntime, retains it beyond source scope, restores it, and drops the held image under test replacement-new denial. |
| invariants | The source account must no longer retain the runtime graph; one image owner keeps encoded bytes until explicit release; restored next delta still works afterward. |
| ownership | Optional EncodedImage is the only source-account payload intentionally outliving DeltaRuntime; receiving runtime owns its rebuilt graph. |
| failure | A source graph retained by the image or a throwing replacement-new allocation during image destruction fails. |
| cost | Two fixture updates and one restore; actual image and native rebuild allocations use their respective accounts; the held image is one account-owned byte vector, not a test-side duplicate. |
| Design | [tests/unit/runtime_checkpoint_test.cpp](../../../../../tests/unit/runtime_checkpoint_test.cpp), [docs/checkpoints.md § Native runtime component](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0012

[Lines 171–171](../../../../../tests/unit/runtime_checkpoint_test.cpp#L171); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L171-L171:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in runtime_checkpoint_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/runtime_checkpoint_test.cpp](../../../../../tests/unit/runtime_checkpoint_test.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 172–185](../../../../../tests/unit/runtime_checkpoint_test.cpp#L172); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run release-after-capture lifetime coverage on reference and indexed plans. |
| inputs / outputs | Calls released_source(false) and released_source(true). |
| invariants | Both configurations exercise source destruction and later continuation from the image. |
| ownership | Each subcase owns a separate runtime/image/account lifecycle. |
| failure | Any lifetime assertion from either backend fails the executable. |
| cost | Two bounded cases; each uses two updates and one restore. |
| Design | [tests/unit/runtime_checkpoint_test.cpp](../../../../../tests/unit/runtime_checkpoint_test.cpp), [docs/checkpoints.md § Native runtime component](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |
