# `tests/support/runtime_probe.hpp` — block usage map

[Source](../../../../../tests/support/runtime_probe.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `7f7def57b182fbb54163b3d7a14e1d1fa55943dfd1ff86fdde937fb588bc24cc`. 40 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../tests/support/runtime_probe.hpp#L1) | Imports dependencies; guards repeated header inclusion; controls preprocessing; declares namespace scope; declares types or opens a type body. |  · [reviewed contract](#b0001) |
| [B0002 · 12–15](../../../../../tests/support/runtime_probe.hpp#L12) | Type/record definition: struct RuntimeStorageWork |  · [reviewed contract](#b0002) |
| [B0003 · 16–18](../../../../../tests/support/runtime_probe.hpp#L16) | Explanatory comments or spacing. | source comment (unverified): // Defined only beside actual private owners in the testing runtime variant. · [reviewed contract](#b0003) |
| [B0004 · 19–39](../../../../../tests/support/runtime_probe.hpp#L19) | Type/record definition: class RuntimeTestProbe | source comment (unverified): // Defined only beside actual private owners in the testing runtime variant. · [reviewed contract](#b0004) |
| [B0005 · 40–40](../../../../../tests/support/runtime_probe.hpp#L40) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0005) |

## B0001

[Lines 1–11](../../../../../tests/support/runtime_probe.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:1270f5428b7db7a693c0b89e394124111aab52b56de12b8f716427c2fd44d640
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare runtime_probe.hpp: include "crown/runtime/delta.hpp"; select the recorded test ABI/preprocessor branch; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 12–15](../../../../../tests/support/runtime_probe.hpp#L12); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct RuntimeStorageWork {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy testing-only native grant observations without retaining a live allowance. |
| inputs / outputs | limit and consumed are five-domain IndexWork values, fresh_operations counts newly admitted outer grants. |
| invariants | Values describe canonical native admission, not logical tuple/capture work, CPU/time, account bytes or every allocation. Fresh counter saturates in context; this aggregate contains no authority to refill/resume/commit. |
| ownership | Plain inline aggregate; copies/moves copy numbers and do not retain a grant/account/runtime. |
| failure | No intrinsic failure path; optional return disengages for reference backend/dropped session as actual probe permits. |
| cost | Fixed numeric copy, no field/key/allocation ledger scan. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/window_sequence_test.cpp](../../../../../tests/unit/window_sequence_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 16–18](../../../../../tests/support/runtime_probe.hpp#L16); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L16-L18:sha256:e05bf76fcd18887672824b81ae95d34abdcaf78dc226704da1f29dfa26305edf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Defined only beside actual private owners in the testing runtime variant. Some probes fund operations/copy flags; mutators deliberately bypass propagation and require explicit restoration. Numeric readings are not CPU/byte measurements. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 19–39](../../../../../tests/support/runtime_probe.hpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class RuntimeTestProbe {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose deliberate private-owner test seams only in the separate testing runtime build. |
| inputs / outputs | Declarations are implemented beside actual Support/Physical/Delta/Session/Window private owners under CROWN_RUNTIME_TESTING; header hard-errors without that macro. |
| invariants | Read probes observe actual owners; mutation probes intentionally alter counters/totals/sequences without normal propagation/journal/commit invariants and must be explicitly restored or used only for boundary injection. They are not production mutation/recovery/source-proof APIs. |
| ownership | References borrow nested runtime ownership; returned MemoryAccount retains original account; record metadata can own a funded child-flag copy. Numeric observations own no rows. |
| failure | Actual owner readiness/identity/range/key checks and native storage work/account failures remain. Probe declarations add no catch or general recovery layer. |
| cost | Costs differ: numeric read is fixed; record flag capture allocates/copies; keyed mutation can fund StorageOperation and build/lookup keys; no universal allocation-free test-probe claim. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/window_sequence_test.cpp](../../../../../tests/unit/window_sequence_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/code_review.md](../../../../code_review.md) |

```text
  static SupportRuntime& support(PhysicalRuntime& runtime);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow an embedded actual runtime for deliberate testing-only composition. |
| inputs / outputs | Returns runtime.impl().kernel from actual Physical owner. |
| invariants | Caller retains valid testing owner and follows its synchronous readiness/lifetime rules; this seam does not open a new runtime/account or change proof/source authority. |
| ownership | Reference borrows PhysicalRuntime implementation; it is not an independent Support owner or lifetime extension. |
| failure | Invalid/moved parent owner access can reject through impl(); no fallback allocation. |
| cost | Fixed implementation/member reference access on success; no row copy or grant allocation. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/window_sequence_test.cpp](../../../../../tests/unit/window_sequence_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/code_review.md](../../../../code_review.md) |

```text
  static PhysicalRuntime& physical(DeltaRuntime& runtime);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow an embedded actual runtime for deliberate testing-only composition. |
| inputs / outputs | Returns runtime.impl().physical from actual Delta owner. |
| invariants | Caller retains valid testing owner and follows its synchronous readiness/lifetime rules; this seam does not open a new runtime/account or change proof/source authority. |
| ownership | Reference borrows DeltaRuntime implementation; replacing/closing it invalidates nested reference. |
| failure | Invalid/moved parent owner access can reject through impl(); no fallback allocation. |
| cost | Fixed implementation/member reference access on success; no row copy or grant allocation. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/window_sequence_test.cpp](../../../../../tests/unit/window_sequence_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/code_review.md](../../../../code_review.md) |

```text
  static std::optional<RuntimeStorageWork> index_work(const SupportRuntime&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe canonical native storage allowance usage for actual SupportRuntime in tests. |
| inputs / outputs | Support reads context limit/observed_work/fresh_operations, returning empty when null/reference. |
| invariants | Observation does not open/refill a native grant; active balance or last completed consumption is read. Per-domain values are not a lexicographic multi-domain limit test or CPU/allocator counter. |
| ownership | Returns independent inline numeric optional; no live allowance or account handle is retained. Actual parent owner must remain valid during read. |
| failure | Owner/guard errors propagate; reference backend or dropped session is unavailable, not zero indexed work. No handler/retry. |
| cost | Fixed context/member checks and five-domain arithmetic; Session adds fixed thread/busy guard, no successful population/ledger scan or allocation. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/window_sequence_test.cpp](../../../../../tests/unit/window_sequence_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/code_review.md](../../../../code_review.md) |

```text
  static std::optional<RuntimeStorageWork> index_work(const PhysicalRuntime&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe canonical native storage allowance usage for actual PhysicalRuntime in tests. |
| inputs / outputs | Physical/Delta forward to their embedded actual owner context. |
| invariants | Observation does not open/refill a native grant; active balance or last completed consumption is read. Per-domain values are not a lexicographic multi-domain limit test or CPU/allocator counter. |
| ownership | Returns independent inline numeric optional; no live allowance or account handle is retained. Actual parent owner must remain valid during read. |
| failure | Owner/guard errors propagate; reference backend or dropped session is unavailable, not zero indexed work. No handler/retry. |
| cost | Fixed context/member checks and five-domain arithmetic; Session adds fixed thread/busy guard, no successful population/ledger scan or allocation. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/window_sequence_test.cpp](../../../../../tests/unit/window_sequence_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/code_review.md](../../../../code_review.md) |

```text
  static std::optional<RuntimeStorageWork> index_work(const DeltaRuntime&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe canonical native storage allowance usage for actual DeltaRuntime in tests. |
| inputs / outputs | Physical/Delta forward to their embedded actual owner context. |
| invariants | Observation does not open/refill a native grant; active balance or last completed consumption is read. Per-domain values are not a lexicographic multi-domain limit test or CPU/allocator counter. |
| ownership | Returns independent inline numeric optional; no live allowance or account handle is retained. Actual parent owner must remain valid during read. |
| failure | Owner/guard errors propagate; reference backend or dropped session is unavailable, not zero indexed work. No handler/retry. |
| cost | Fixed context/member checks and five-domain arithmetic; Session adds fixed thread/busy guard, no successful population/ledger scan or allocation. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/window_sequence_test.cpp](../../../../../tests/unit/window_sequence_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/code_review.md](../../../../code_review.md) |

```text
  static std::optional<RuntimeStorageWork> index_work(const QuerySession&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe canonical native storage allowance usage for actual QuerySession in tests. |
| inputs / outputs | Session enters its writer-thread/nonreentrant Guard and forwards to retained runtime, or returns nullopt when runtime dropped. |
| invariants | Observation does not open/refill a native grant; active balance or last completed consumption is read. Per-domain values are not a lexicographic multi-domain limit test or CPU/allocator counter. |
| ownership | Returns independent inline numeric optional; no live allowance or account handle is retained. Actual parent owner must remain valid during read. |
| failure | Owner/guard errors propagate; reference backend or dropped session is unavailable, not zero indexed work. No handler/retry. |
| cost | Fixed context/member checks and five-domain arithmetic; Session adds fixed thread/busy guard, no successful population/ledger scan or allocation. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/window_sequence_test.cpp](../../../../../tests/unit/window_sequence_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/code_review.md](../../../../code_review.md) |

```text
  static resource::MemoryAccount memory_account(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the actual Support owner's original query account for funding/lifetime assertions. |
| inputs / outputs | Returns runtime.impl().storage_context-&gt;memory() by value. |
| invariants | Handle retains the identical account/ceiling; it never creates an unlimited replacement or forces an allocation-ledger snapshot. |
| ownership | Owning MemoryAccount copy shares actual control. Runtime rows need not survive for retained account statistics to remain readable. |
| failure | Invalid runtime/context is outside normal admitted test owner precondition; no local fallback/catch. |
| cost | Fixed account-handle copy, no ledger scan or new account allocation. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/window_sequence_test.cpp](../../../../../tests/unit/window_sequence_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/code_review.md](../../../../code_review.md) |

```text
  static SupportValueState record_metadata(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture exact actual record membership/satisfied count and owning child flags for a test handle. |
| inputs / outputs | Requires readable Support owner, matching owner/records role and present record tuple; returns member=true, satisfied and retained_flags copy. |
| invariants | SupportHandle role/owner/node/tuple are validated. Returned flags are a value capture, not a borrowed bit view; no engine counter is changed. |
| ownership | Child-present vector uses OwnerAllocator on record's original account, journal_undo purpose and original attribution. Copies can allocate; output owns them independently. |
| failure | Wrong/missing handle rejects invalid_probe; actual flag allocation/account failures propagate. No broad diagnostic recovery. |
| cost | Node/map lookup plus O(child count) bit copying and actual funded vector request; not a constant no-allocation observation. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/window_sequence_test.cpp](../../../../../tests/unit/window_sequence_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/code_review.md](../../../../code_review.md) |

```text
  static std::size_t set_satisfied(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deliberately change one existing support record's satisfied count for invariant tests. |
| inputs / outputs | Opens StorageOperation, requires writable owner/node/existing row, finds tuple, exchanges count and returns old size_t. |
| invariants | Only count changes: child flags/survivors/projection/sequence/revision are not coherently updated. Caller saves old value and restores explicitly; this is intentional corruption, not a legal native update. |
| ownership | Borrows actual runtime and caller row/key during lookup; returns inline previous value, not a rollback owner. No proof/source authority is created. |
| failure | Readiness/range/missing-key/native work/account/key-construction failures propagate; after successful exchange caller owns restoration. No transaction/retry/handler added. |
| cost | Actual fresh indexed operation/control admission when needed, compiler layout tuple(row) construction/copy, native keyed lookup/work and metadata map access; return exchange itself is fixed. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/window_sequence_test.cpp](../../../../../tests/unit/window_sequence_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/code_review.md](../../../../code_review.md) |

```text
  static std::uint64_t set_projection(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deliberately change an existing actual parent/visible support counter. |
| inputs / outputs | Opens StorageOperation, requires writable owner, selects exact parent or visible relation, finds row/tuple, exchanges stored count and returns old uint64. |
| invariants | Caller supplies applicable relation and existing key. This bypasses zero-crossing propagation and can invalidate support invariants; explicit restore required. |
| ownership | Borrows actual runtime and caller row/key during lookup; returns inline previous value, not a rollback owner. No proof/source authority is created. |
| failure | Readiness/range/missing-key/native work/account/key-construction failures propagate; after successful exchange caller owns restoration. No transaction/retry/handler added. |
| cost | Actual grant admission/key tuple copy/native lookup and count map access plus fixed exchange, with field/text comparisons and possible allocation. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/window_sequence_test.cpp](../../../../../tests/unit/window_sequence_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/code_review.md](../../../../code_review.md) |

```text
  static std::uint64_t set_derivation(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deliberately replace one existing physical occurrence derivation multiplicity. |
| inputs / outputs | Requires readable Physical owner and valid input occurrence, finds key in actual counts map, exchanges count and returns old value. |
| invariants | No physical source/native membership/sequence/workload update accompanies it. Caller uses existing key and restores or destroys intentionally corrupted owner. |
| ownership | Borrows actual runtime and caller row/key during lookup; returns inline previous value, not a rollback owner. No proof/source authority is created. |
| failure | Readiness/range/missing-key/native work/account/key-construction failures propagate; after successful exchange caller owns restoration. No transaction/retry/handler added. |
| cost | Ordered native key lookup/comparison and fixed exchange; no generic cost based only on integer width because compared keys can contain text. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/window_sequence_test.cpp](../../../../../tests/unit/window_sequence_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/code_review.md](../../../../code_review.md) |

```text
  static std::uint64_t set_live_bucket(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deliberately replace one existing Delta live parent/child bucket count. |
| inputs / outputs | Requires writable owner and live image/node rank, selects actual child_index or parents bucket, at(key) exchanges bucket.value. |
| invariants | Requires currently materialized factor/key. No corresponding row/other totals/sequence propagation occurs; this is isolated invariant corruption. |
| ownership | Borrows actual runtime and caller row/key during lookup; returns inline previous value, not a rollback owner. No proof/source authority is created. |
| failure | Readiness/range/missing-key/native work/account/key-construction failures propagate; after successful exchange caller owns restoration. No transaction/retry/handler added. |
| cost | Rank/bucket lookup and key comparisons plus fixed count exchange; missing key/rank checks and actual owner gates remain. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/window_sequence_test.cpp](../../../../../tests/unit/window_sequence_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/code_review.md](../../../../code_review.md) |

```text
  static std::size_t set_live_total(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deliberately replace one named aggregate Delta live total. |
| inputs / outputs | Requires writable owner/live image, supports live_factor/live_parent/live_child and exchanges rows/parent_rows/child_rows. |
| invariants | Other InvariantComponent tags reject; stored buckets/rows are not rebuilt. Caller explicitly restores the old total. |
| ownership | Borrows actual runtime and caller row/key during lookup; returns inline previous value, not a rollback owner. No proof/source authority is created. |
| failure | Readiness/range/missing-key/native work/account/key-construction failures propagate; after successful exchange caller owns restoration. No transaction/retry/handler added. |
| cost | Fixed owner/component checks and scalar exchange on success; no table scan, new grant or array allocation. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/window_sequence_test.cpp](../../../../../tests/unit/window_sequence_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/code_review.md](../../../../code_review.md) |

```text
  static void seed_physical_sequence(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject a coordinated physical/support sequence label for boundary tests. |
| inputs / outputs | Requires writable Physical owner, seeds kernel sequence then physical sequence. |
| invariants | Does not apply input, update source rows or observations, or establish accepted external source progress. |
| ownership | Only borrowed actual runtime/controller/session; inline numeric fields change, no payload owner or fallback account. |
| failure | Owner readiness/thread/busy/absence errors propagate before intended writes. These test seeds are not a public atomic recovery API. |
| cost | Sequence seeds are fixed checks/stores; saturation seed traverses committed collector Cells plus fixed flags. No row import or system allocation failure simulation. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/window_sequence_test.cpp](../../../../../tests/unit/window_sequence_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/code_review.md](../../../../code_review.md) |

```text
  static void seed_delta_sequence(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject a matching Delta physical/live sequence boundary. |
| inputs / outputs | Requires writable Delta owner, delegates physical seed and updates live_sequence only when live image exists. |
| invariants | No rows or live factors are rebuilt; this numeric boundary does not imply a historical input transcript. |
| ownership | Only borrowed actual runtime/controller/session; inline numeric fields change, no payload owner or fallback account. |
| failure | Owner readiness/thread/busy/absence errors propagate before intended writes. These test seeds are not a public atomic recovery API. |
| cost | Sequence seeds are fixed checks/stores; saturation seed traverses committed collector Cells plus fixed flags. No row import or system allocation failure simulation. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/window_sequence_test.cpp](../../../../../tests/unit/window_sequence_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/code_review.md](../../../../code_review.md) |

```text
  static void seed_c01_report_saturation(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject C01 numeric observation saturation in a writable Delta owner. |
| inputs / outputs | Calls actual workload State.seed_report_saturation after writable check. |
| invariants | No row/source/epoch/proof authority is manufactured; only testing numeric report fields/generation flags change. |
| ownership | Only borrowed actual runtime/controller/session; inline numeric fields change, no payload owner or fallback account. |
| failure | Owner readiness/thread/busy/absence errors propagate before intended writes. These test seeds are not a public atomic recovery API. |
| cost | Sequence seeds are fixed checks/stores; saturation seed traverses committed collector Cells plus fixed flags. No row import or system allocation failure simulation. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/window_sequence_test.cpp](../../../../../tests/unit/window_sequence_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/code_review.md](../../../../code_review.md) |

```text
  static void seed_window_sequence(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject physical sequence in a ready window controller for overflow tests. |
| inputs / outputs | Requires no prepared operation and not stopped, then sets its physical sequence counter. |
| invariants | Labels/counts/queue/source progress/command/watermark are not changed; this is deliberate numeric test setup. |
| ownership | Only borrowed actual runtime/controller/session; inline numeric fields change, no payload owner or fallback account. |
| failure | Owner readiness/thread/busy/absence errors propagate before intended writes. These test seeds are not a public atomic recovery API. |
| cost | Sequence seeds are fixed checks/stores; saturation seed traverses committed collector Cells plus fixed flags. No row import or system allocation failure simulation. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/window_sequence_test.cpp](../../../../../tests/unit/window_sequence_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/code_review.md](../../../../code_review.md) |

```text
  static void seed_session_physical_sequence(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject matching runtime/window/session sequence labels in a ready window session. |
| inputs / outputs | Takes Session Guard, requires window and no private/output state, seeds Delta+Window physical sequence and committed_sequence. |
| invariants | Requires actual valid testing session runtime; no input decoding/acknowledgement, row replay or durable checkpoint proof is created. |
| ownership | Only borrowed actual runtime/controller/session; inline numeric fields change, no payload owner or fallback account. |
| failure | Owner readiness/thread/busy/absence errors propagate before intended writes. These test seeds are not a public atomic recovery API. |
| cost | Sequence seeds are fixed checks/stores; saturation seed traverses committed collector Cells plus fixed flags. No row import or system allocation failure simulation. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/window_sequence_test.cpp](../../../../../tests/unit/window_sequence_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 40–40](../../../../../tests/support/runtime_probe.hpp#L40); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L40-L40:sha256:97734ee3ed73fbf0bd112ff8fee5fae528737ea20327081d48b1efcf3f9b9a5a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in runtime_probe.hpp: namespace crown::runtime. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |
