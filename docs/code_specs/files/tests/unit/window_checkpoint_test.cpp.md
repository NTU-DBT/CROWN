# `tests/unit/window_checkpoint_test.cpp` — block usage map

[Source](../../../../../tests/unit/window_checkpoint_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `3bb5c556a820ffa54c3b3a55bfdcc565559d06be9a790af41fede7350b604ba7`. 255 lines partitioned into 21 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../tests/unit/window_checkpoint_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 15–15](../../../../../tests/unit/window_checkpoint_test.cpp#L15) | Callable definition: void check(bool value,const char* message) | calls std::runtime_error; guard void check(bool value,const char* message){if(!value)throw std::runtime_error(message);} · [reviewed contract](#b0002) |
| [B0003 · 16–24](../../../../../tests/unit/window_checkpoint_test.cpp#L16) | Callable definition: PhysicalPlan plan(bool indexed) | calls push_back, planner::lower_tree, s04_runtime::options; returns planner::lower_tree(catalog,query,tree,indexed?s04_runtime::options():PhysicalOptions{}); growth push_back; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 25–27](../../../../../tests/unit/window_checkpoint_test.cpp#L25) | Callable definition: WindowOptions options(WindowFifoPolicy fifo) | calls reserve; returns result; growth reserve · [reviewed contract](#b0004) |
| [B0005 · 28–29](../../../../../tests/unit/window_checkpoint_test.cpp#L28) | Callable definition: Row row(std::int64_t id) | calls std::string, Date::parse, Decimal::parse; returns {id,std::string(8192,@ )+std::string(@ ,2),true,Date::parse(@ ), · [reviewed contract](#b0005) |
| [B0006 · 30–30](../../../../../tests/unit/window_checkpoint_test.cpp#L30) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0006) |
| [B0007 · 31–42](../../../../../tests/unit/window_checkpoint_test.cpp#L31) | Callable definition: Output accept(DeltaRuntime& runtime,WindowController& window,const io::WindowCommand& command) | calls prepare, sequence, update, begin_view; guard while(auto value=epoch.next())check(result.emplace(value-&gt;operation,storage::export_row(value-&gt;tupl…; returns result; growth emplace; 3 loop sites · [reviewed contract](#b0007) |
| [B0008 · 43–45](../../../../../tests/unit/window_checkpoint_test.cpp#L43) | Callable definition: io::WindowCommand insert(std::uint64_t sequence,std::uint64_t label,TableId table,std::uint64_t timestamp) | calls row; returns {sequence,io::WindowInsert{label,table,row(table.value?2:1),timestamp},{}}; growth insert · [reviewed contract](#b0008) |
| [B0009 · 46–49](../../../../../tests/unit/window_checkpoint_test.cpp#L46) | Callable definition: template&lt;class Action&gt; void rejected(Action action) | calls action, check; guard check(failed,"invalid window checkpoint accepted"); · [reviewed contract](#b0009) |
| [B0010 · 50–124](../../../../../tests/unit/window_checkpoint_test.cpp#L50) | Callable definition: void scenario(bool indexed,WindowFifoPolicy fifo) | calls plan, CompiledProgram::standalone, source, account; guard check(canonical.counts.at(0).id==1 && canonical.labels.at(0).label==2,"orphaned original count-ID f…; growth clone, emplace, insert; 5 loop sites; source comment (unverified): // Bring both sides through the same remaining watermark, preserving its · [reviewed contract](#b0010) |
| [B0011 · 125–128](../../../../../tests/unit/window_checkpoint_test.cpp#L125) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Independent full-state reference: physical births are an insertion-order · [reviewed contract](#b0011) |
| [B0012 · 129–129](../../../../../tests/unit/window_checkpoint_test.cpp#L129) | Type/record definition: struct Label |  · [reviewed contract](#b0012) |
| [B0013 · 130–134](../../../../../tests/unit/window_checkpoint_test.cpp#L130) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0013) |
| [B0014 · 135–145](../../../../../tests/unit/window_checkpoint_test.cpp#L135) | Callable definition: bool remove(std::uint64_t id) | calls find, at, std::find_if, begin; returns !per_relation \|\| live.first==key.first; false · [reviewed contract](#b0014) |
| [B0015 · 146–159](../../../../../tests/unit/window_checkpoint_test.cpp#L146) | Callable definition: bool apply(const io::WindowCommand& command) | calls push_back, emplace, remove, emplace_back; returns true; remove(value-&gt;label); growth emplace, emplace_back, push_back; 2 loop sites · [reviewed contract](#b0015) |
| [B0016 · 160–160](../../../../../tests/unit/window_checkpoint_test.cpp#L160) | Closes surrounding scope/type. |  · [reviewed contract](#b0016) |
| [B0017 · 161–178](../../../../../tests/unit/window_checkpoint_test.cpp#L161) | Callable definition: void compare_lifetimes(const LifetimeReference& expected,DeltaRuntime& runtime,const WindowController& window) | calls canonical_state, check, size, at; guard check(actual.labels.size()==expected.labels.size() && actual.counts.size()==expected.counts.size(),…; growth insert; 4 loop sites · [reviewed contract](#b0017) |
| [B0018 · 179–206](../../../../../tests/unit/window_checkpoint_test.cpp#L179) | Callable definition: void lifetime_reference(bool indexed,WindowFifoPolicy fifo) | calls runtime, plan, window, account; guard check(failed,"physical FIFO reference rejection was accepted");; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 207–247](../../../../../tests/unit/window_checkpoint_test.cpp#L207) | Callable definition: void lifetime_preflight(bool indexed,WindowFifoPolicy fifo) | calls runtime, plan, window, account; guard check(failed && window.canonical_state()==before && runtime.canonical_state()==state,"physical FIFO…; 2 loop sites; source comment (unverified): // A1 expires before B2, but A3 retains the older physical row. Rejection must · [reviewed contract](#b0019) |
| [B0020 · 248–248](../../../../../tests/unit/window_checkpoint_test.cpp#L248) | Closes surrounding scope/type. |  · [reviewed contract](#b0020) |
| [B0021 · 249–255](../../../../../tests/unit/window_checkpoint_test.cpp#L249) | Callable definition: int main() | calls scenario, lifetime_reference, lifetime_preflight, what; returns 1; 3 loop sites · [reviewed contract](#b0021) |

## B0001

[Lines 1–14](../../../../../tests/unit/window_checkpoint_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:9e3470d93b7adde0ecc7445cd137caf8b614599f5dc81e0a4094b98518029c68
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import window checkpoint, error, map and random-generator fixture dependencies and open local test scope. |
| inputs / outputs | Headers expose native window/delta APIs, typed Error checks, allocation seam, ordinary reference maps/sets and deterministic test PRNG declarations. No fixture object is instantiated in this preamble. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0002

[Lines 15–15](../../../../../tests/unit/window_checkpoint_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,const char* message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail one native window-state assertion with its recovery-specific error. |
| inputs / outputs | False throws std::runtime_error; true returns. |
| invariants | The helper catches no ImageFailure; malformed snapshot tests treat native recovery rejection distinctly. |
| ownership | Diagnostic is borrowed until exception construction. |
| failure | False fails the local test. |
| cost | One predicate branch; no native owner changes. |
| Design | [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [docs/checkpoints.md § Native source and window state components](../../../../checkpoints.md), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0003

[Lines 16–24](../../../../../tests/unit/window_checkpoint_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan plan(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a two-table full-row plan for indexed or reference runtime state. |
| inputs / outputs | Takes indexed flag and returns a one-occurrence plan over int64, long binary string, bool, date, and decimal fields. |
| invariants | Managed-table identity and complete rows remain relevant even though the query projects only x. |
| ownership | Returned PhysicalPlan owns admitted program state; Catalog/Query/tree construction values are setup inputs. |
| failure | Planner validation errors stop the fixture before the window controller is created. |
| cost | Fixed two-table plan; row values are allocated separately in the native-accounted runtime/controller when inserted. |
| Design | [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [docs/checkpoints.md § Native source and window state components](../../../../checkpoints.md), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0004

[Lines 25–27](../../../../../tests/unit/window_checkpoint_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WindowOptions options(WindowFifoPolicy fifo)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure two managed tables, a reserved managed-table capacity, width 10, and requested FIFO policy. |
| inputs / outputs | Returns WindowOptions with capacity 9 and managed IDs 0/1. |
| invariants | Reserved vector capacity is intentionally retained as checkpoint/accounting state; policy choice changes only FIFO rule. |
| ownership | Options value owns its vector; WindowController later copies managed tables into AccountedWindowOptions on the query account. |
| failure | Invalid table IDs or policy are rejected by controller construction, not normalized by this helper. |
| cost | One small standard vector reservation and two IDs; later native capacity is a separate account-funded request. |
| Design | [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [docs/checkpoints.md § Native source and window state components](../../../../checkpoints.md), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0005

[Lines 28–29](../../../../../tests/unit/window_checkpoint_test.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row row(std::int64_t id)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a full-width test row that exposes binary/string/date/decimal ownership in window snapshots. |
| inputs / outputs | Returns an owning Row for an integer identifier and fixed 8 KiB string plus bool/date/decimal values. |
| invariants | The unused columns are part of physical identity and should distinguish full rows even where query output projects only x. |
| ownership | Caller owns the ordinary Row; window/runtime admission clones its values into their native account-owned representation. |
| failure | Date/decimal parse failure or ordinary Row allocation failure aborts fixture construction. |
| cost | One bounded long string and scalar-vector copy per call; native row allocations occur later in actual query account. |
| Design | [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [docs/checkpoints.md § Native source and window state components](../../../../checkpoints.md), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0006

[Lines 30–30](../../../../../tests/unit/window_checkpoint_test.cpp#L30); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L30-L30:sha256:0ac89d782deaeb853b315d4191d6a97d0d2cf9bf8bbdabfb653b56b27e2d4974
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare window_checkpoint_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 31–42](../../../../../tests/unit/window_checkpoint_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Output accept(DeltaRuntime& runtime,WindowController& window,const io::WindowCommand& command)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit each prepared window command's physical update before publishing its metadata and collect signed output. |
| inputs / outputs | Repeatedly prepares one command, uses DeltaRuntime begin/drain/commit when an update exists, publishes under test replacement-new denial, and returns exported signed rows. |
| invariants | Every physical step commits before its no-allocation window publish; metadata-only steps publish without a runtime epoch; command loops until no active watermark remains. |
| ownership | Window Prepared owns unpublished controller state; DeltaRuntime owns pending epoch/output; return set owns ordinary exported Row copies. |
| failure | Duplicate signed output or native/controller error aborts before later steps. |
| cost | A multi-step watermark may execute several finite physical transitions; actual native allocations are account-funded during prepare/runtime work, but publish is specifically observed under test replacement-new denial; output export/set copies use test memory. |
| Design | [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [docs/checkpoints.md § Native source and window state components](../../../../checkpoints.md), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0008

[Lines 43–45](../../../../../tests/unit/window_checkpoint_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::WindowCommand insert(std::uint64_t sequence,std::uint64_t label,TableId table,std::uint64_t timestamp)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an insertion command with deterministic table-specific row, label, sequence, and timestamp. |
| inputs / outputs | Returns WindowCommand carrying WindowInsert; table 0 uses row id 1 and table 1 uses row id 2. |
| invariants | Timestamp is caller-supplied and width/deadline checks remain controller responsibilities. |
| ownership | The command owns its ordinary row payload until WindowController imports it. |
| failure | No semantic validation is done by the helper; invalid sequence/label/table is rejected by prepare. |
| cost | One bounded command and full Row copy outside the query account; native import cost occurs in prepare. |
| Design | [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [docs/checkpoints.md § Native source and window state components](../../../../checkpoints.md), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0009

[Lines 46–49](../../../../../tests/unit/window_checkpoint_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void rejected(Action action)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a malformed or nonquiescent WindowCheckpoint action to reject with ImageFailure. |
| inputs / outputs | Invokes an action; only recovery::ImageFailure counts as expected rejection. |
| invariants | The test uses this for metadata/work/cap and active-state barriers; arbitrary exceptions cannot masquerade as codec validation. |
| ownership | Input state remains caller-owned; action manages any temporary controller/runtime object. |
| failure | Acceptance or a different exception fails. |
| cost | One bounded action and local catch; actual restore allocation may be prevented by zero-work preflight. |
| Design | [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [docs/checkpoints.md § Native source and window state components](../../../../checkpoints.md), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0010

[Lines 50–124](../../../../../tests/unit/window_checkpoint_test.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scenario(bool indexed,WindowFifoPolicy fifo)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture and rebuild native WindowController state independently from a separately restored physical runtime. |
| inputs / outputs | Exercises two FIFO policies/backends after duplicate full-row labels, withdrawal, a second table and a partial watermark; then mutates metadata, fault-injects capture/restore, tests caps, and continues both sides. |
| invariants | Count IDs remain stable when an earlier label is withdrawn; native standalone window validity is checked separately from QuerySession's managed-base join; partial watermark checkpoint rejects even after a physical step commits; snapshots preserve stopped state. |
| ownership | Source runtime and window share the source account; restored runtime owns a new account and restored WindowController imports into that account; snapshots clone native rows; canonical_state and output use full ordinary Row copies. |
| failure | Corrupt multiplicities/references/deadlines/catalog/progress reject without changing an existing target; zero/under work, measured replacement-new bad_alloc cuts, and one-under MemoryAccount bytes reject; later output/state must still match. |
| cost | Finite eight command sequence, twenty repeated captures, nine field mutations, and measured replacement-new cuts; physical/window native graphs use their accounts; canonical diagnostics and expected long rows are exported test copies. |
| Design | [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [docs/checkpoints.md § Native source and window state components](../../../../checkpoints.md), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0011

[Lines 125–128](../../../../../tests/unit/window_checkpoint_test.cpp#L125); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L125-L128:sha256:2aa45408109c1ee2a9bd6c0a594c5299ff06a83a96b73a874cacc6ea3cc41d45
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the independent fixture model in terms of physical births. |
| inputs / outputs | Open LifetimeReference and define Key as (TableId, int64 row value). The following members implement an insertion-order list reference for these deterministic full-row fixtures. |
| invariants | The fixture row(value) deterministically fixes every other column, so this key uniquely identifies its complete physical row. This model is not a general SQL/variable-width row evaluator and does not use native birth count IDs. |
| ownership | The alias contains scalar identities only. Actual owning maps/list are declared in the next block; this opening creates no runtime owner. |
| failure | Declaration/type errors fail compilation; model lookups have their own fixture preconditions. |
| cost | Compile-time declaration and fixed scalar key representation; no model instance or native update here. |
| Design | [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [docs/update_patterns.md](../../../../update_patterns.md), [docs/batches_windows.md](../../../../batches_windows.md) |

## B0012

[Lines 129–129](../../../../../tests/unit/window_checkpoint_test.cpp#L129); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L129-L129:sha256:f13bfbefb71fd6e95e74fbb0bf4dcbfdd5fd5999a27b7cee9ad464800adb4ccd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store one reference-model label payload. |
| inputs / outputs | Label contains the fixture row key and uint64 insertion timestamp; its enclosing map supplies the label ID. |
| invariants | Row identity includes physical table and fixture value. Timestamp is used only for the fixed width-10 expiration reference, not lifetime birth order. |
| ownership | Inline scalar/key values own no query storage and borrow no native row. |
| failure | This declaration performs no admission or runtime validation. |
| cost | Fixed-size ordinary test value; no allocation or algorithm invocation. |
| Design | [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [docs/update_patterns.md](../../../../update_patterns.md), [docs/batches_windows.md](../../../../batches_windows.md) |

## B0013

[Lines 130–134](../../../../../tests/unit/window_checkpoint_test.cpp#L130); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L130-L134:sha256:b9271ce7ad4c81a9abd5650899d4e0d83f7c138b597221620e8212bad94f7553
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain independent full-state test expectations. |
| inputs / outputs | Ordinary maps record labels and per-row reference counts; births is a vector in first-presence order. watermark starts at zero; aggregate construction supplies per_relation. |
| invariants | Counts and births describe the same live fixture rows. The generated commands provide valid label/table/type/time inputs; only physical FIFO admissibility is modeled here. |
| ownership | std::map/std::vector own test-side elements through ordinary allocators. These expectations and their proposal copies are outside the native query account; no production state is retained. |
| failure | Test container growth/copy can allocate and throw. Fixture exceptions propagate; no transactional promise is supplied by field declarations. |
| cost | Empty-container/scalar initialization at object construction, then O(labels+distinct fixture rows) state and explicit full-copy costs per proposal. No production memory or update cost. |
| Design | [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [docs/update_patterns.md](../../../../update_patterns.md), [docs/batches_windows.md](../../../../batches_windows.md) |

## B0014

[Lines 135–145](../../../../../tests/unit/window_checkpoint_test.cpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L135-L145:sha256:f27aadd5a3d993ab9ea6001bb221d7c77b962d47403829b797683398a460cff3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove one known label in the independent birth-list reference. |
| inputs / outputs | An existing label ID selects a fixture row. Return false before this removal if its final reference would skip the first live birth globally/per table; otherwise decrement/remove count, birth and label and return true. |
| invariants | Caller provides a present label and consistent positive reference count. Metadata-only removals do not advance births. Earlier removals in a copied watermark proposal may already have occurred; the caller discards that proposal on a later false result. |
| ownership | Mutates only the caller-owned reference maps/vector, freeing erased test entries. No native count IDs, rows or windows are touched. |
| failure | False denotes the selected FIFO violation. Invalid fixture lookups or C++ failures are test failures; the function supplies no generic recovery layer. |
| cost | Ordered-map lookups/erase plus O(D) birth-list search and shifting on final removal; intentionally a slow independent test reference. |
| Design | [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [docs/update_patterns.md](../../../../update_patterns.md), [docs/batches_windows.md](../../../../batches_windows.md) |

## B0015

[Lines 146–159](../../../../../tests/unit/window_checkpoint_test.cpp#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L146-L159:sha256:b221b53f642c4afe64eecf85a2145fd0c1fe9eafef8b51946499ef6b787ad3e0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply a generated command to a private full-state reference proposal. |
| inputs / outputs | The fixed-width fixture command is an insertion, known-label withdrawal or monotone watermark. Insertions decode the int64 first column; watermarks sort all eligible (deadline,label) pairs and remove them in that order. |
| invariants | The generator ensures schema-valid deterministic rows, increasing labels and nonlate timestamps. A false watermark may have mutated this proposal; caller compares native rejection and discards the proposal. Successful application defines the expected full-row presence state. |
| ownership | Owns ordinary expiration-vector scratch and mutates the copied reference state. It neither prepares nor publishes native state. |
| failure | False is the modeled FIFO rejection; invalid fixture variant/type/map access or allocation raises a test exception. The helper does not claim to validate every window-input error. |
| cost | Full label scan, O(E log E) expiration sorting and deliberately linear birth-list removals, plus ordinary map work. Proposal copying is charged as test setup, not hidden in the production algorithm. |
| Design | [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [docs/update_patterns.md](../../../../update_patterns.md), [docs/batches_windows.md](../../../../batches_windows.md) |

## B0016

[Lines 160–160](../../../../../tests/unit/window_checkpoint_test.cpp#L160); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L160-L160:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the reference model type. |
| inputs / outputs | Ends LifetimeReference after its members and model operations. |
| invariants | The type delimiter does not execute any removal, publish a native command or destroy a model object. |
| ownership | Constructed reference objects later own their maps/vector and release them at their actual object lifetime boundary. |
| failure | Syntax/type errors are compile failures; no runtime failure handling is defined here. |
| cost | Declaration syntax only; eventual model destruction visits owned test entries. |
| Design | [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [docs/update_patterns.md](../../../../update_patterns.md), [docs/batches_windows.md](../../../../batches_windows.md) |

## B0017

[Lines 161–178](../../../../../tests/unit/window_checkpoint_test.cpp#L161); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L161-L178:sha256:a3df0fd41860c70f2d619b889c0eff585a0857a5c52453d8944cbc080ccde4f6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the physical monitor and unary native query with the independent model. |
| inputs / outputs | Read expected label/count/watermark state, WindowController canonical export and current DeltaRuntime results. Compare every fixture label/count and exact projected rows of table 0. |
| invariants | Table 1 still participates in window ordering/count checks; only table 0 belongs to this unary query. The reference never compares or derives native birth IDs. This is current-result/monitor equality, not a general pattern-bound proof. |
| ownership | Borrows runtime/controller/reference. Owns explicit exported rows, sets and the bounded result cursor for this inspection call; native immutable row handles follow normal account lifetime. |
| failure | Mismatch, duplicate/unexpected fixture lookup or native cursor failure propagates as a test failure. No state is committed by comparison. |
| cost | Complete labels/counts/output scans and test-side row/set allocation, including large fixed fixture payloads. It is not a hot update hook. |
| Design | [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [docs/update_patterns.md](../../../../update_patterns.md), [docs/batches_windows.md](../../../../batches_windows.md) |

## B0018

[Lines 179–206](../../../../../tests/unit/window_checkpoint_test.cpp#L179); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L179-L206:sha256:92e2895f0daff51b4ab53d0eb9f820ffa0ec6e35a861566329300dfac13e2f68
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise both accepted and rejected physical-lifetime commands against a full-state oracle. |
| inputs / outputs | Backend and physical policy create matching empty runtime/controller and seed-731 deterministic model. Run 120 proposals over two tables/five fixture values with insert/withdraw/watermark choices. |
| invariants | On acceptance, apply the complete native command and adopt the private model. On rejection, require window/native canonical states and current query-account memory unchanged. Compare every resulting prefix, including rejected proposals; require both outcomes occur. |
| ownership | Each case owns runtime/window/model. Full proposal and canonical copies are test-side storage; prepared native resources stay on the original query account. |
| failure | Wrong success/error, state drift, scratch leak or result mismatch throws to the test main. Expected FIFO failures are observed through the existing typed Error code. |
| cost | 120 bounded generated proposals per combination, with full-state copies and inspections; two backends/two modes give 480. This is a finite semantic/resource control, not measured complexity or throughput. |
| Design | [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [docs/update_patterns.md](../../../../update_patterns.md), [docs/batches_windows.md](../../../../batches_windows.md) |

## B0019

[Lines 207–247](../../../../../tests/unit/window_checkpoint_test.cpp#L207); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L207-L247:sha256:7811c315fa3540226c46298ed7def5a4e1446d8afdff0c91926a36b7b49b3c4d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify atomic watermark preflight, metadata-only freedom, OOM retry and exact work admission. |
| inputs / outputs | Seed A1/B2/A3, reject watermark 11 before its first metadata effect, remove A3 without label-front restriction, then prepare/retry the valid watermark under every observed persistent allocation cut and exact/one-under command work caps. |
| invariants | Every aborted preparation preserves committed state/current memory; publication in the shared accept helper is allocation-denied. The exact work value comes from a successful command, and one less must reject before any prefix. These selected checks do not exhaust every timestamp/history pattern. |
| ownership | Owns independent test runtimes/controllers and before-state exports. The allocation seam is scoped/disarmed before comparisons; transient production counter/ID/row holders remain original-account objects. |
| failure | Expected FIFO, bad_alloc and resource_limit cases are checked specifically. An unexpected outcome escapes as test failure; no production exception policy changes. |
| cost | One counterexample and successful retry per combination, one aborted prepare per observed allocation request, and two separately seeded work-boundary runs. Counts describe requests/abstract work rather than CPU instructions or a native bound. |
| Design | [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [docs/update_patterns.md](../../../../update_patterns.md), [docs/batches_windows.md](../../../../batches_windows.md) |

## B0020

[Lines 248–248](../../../../../tests/unit/window_checkpoint_test.cpp#L248); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L248-L248:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in window_checkpoint_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0021

[Lines 249–255](../../../../../tests/unit/window_checkpoint_test.cpp#L249); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run native window checkpoint/recovery and independent physical-lifetime semantics/resource controls on both backends. |
| inputs / outputs | Eight native checkpoint scenarios cover four FIFO policies; four physical-policy/backend combinations each run 120 independent-reference proposals plus whole-watermark/OOM/retry/exact-work controls. |
| invariants | This executable restores WindowController plus DeltaRuntime independently; it is not a QuerySession or durable checkpoint file test. |
| ownership | Each scenario creates and destroys its own account/runtime/controller/image. |
| failure | Any combination failing the same-window/next-command checks returns nonzero. |
| cost | Eight checkpoint scenarios, 480 generated proposals across four physical combinations and four finite preparation-fault/exact-work groups. Native resources use query accounts; test reference maps/lists/exports are caller-owned. |
| Design | [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [docs/checkpoints.md § Native source and window state components](../../../../checkpoints.md), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/update_patterns.md](../../../../update_patterns.md) |
