# `tests/support/sql_aggregate_session_probe.hpp` — block usage map

[Source](../../../../../tests/support/sql_aggregate_session_probe.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `716e8121a699673eb2f849a50aaf4ddd568a98e0eff0e8418166570423bf4018`. 54 lines partitioned into 10 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../tests/support/sql_aggregate_session_probe.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares values/defaults or compile-time conditions. | source comment (unverified): // Fixed, test-only observers shared by the baseline and mixed-transaction · [reviewed contract](#b0001) |
| [B0002 · 15–19](../../../../../tests/support/sql_aggregate_session_probe.hpp#L15) | Type/record definition: struct Event | source comment (unverified): // Fixed test observations join the two existing file seams without changing · [reviewed contract](#b0002) |
| [B0003 · 20–23](../../../../../tests/support/sql_aggregate_session_probe.hpp#L20) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 24–30](../../../../../tests/support/sql_aggregate_session_probe.hpp#L24) | Callable definition: void observe(bool generation,bool done,ar::FileStage file,recovery::GenerationStage root, recovery::GenerationTarget target,std::… | calls assert, size, _exit; guard assert(size&lt;events.size());events\[size++\]={point,generation,done,file,root,target,result}; · [reviewed contract](#b0004) |
| [B0005 · 31–36](../../../../../tests/support/sql_aggregate_session_probe.hpp#L31) | Callable definition: static ar::testing::FileDecision file(const ar::testing::FileEvent& event,void* context) noexcept | calls observe; returns result · [reviewed contract](#b0005) |
| [B0006 · 37–42](../../../../../tests/support/sql_aggregate_session_probe.hpp#L37) | Callable definition: static gt::GenerationDecision root(const gt::GenerationEvent& event,void* context) noexcept | calls observe; returns result · [reviewed contract](#b0006) |
| [B0007 · 43–43](../../../../../tests/support/sql_aggregate_session_probe.hpp#L43) | Closes surrounding scope/type. |  · [reviewed contract](#b0007) |
| [B0008 · 44–47](../../../../../tests/support/sql_aggregate_session_probe.hpp#L44) | Type/record definition: struct Installed |  · [reviewed contract](#b0008) |
| [B0009 · 48–53](../../../../../tests/support/sql_aggregate_session_probe.hpp#L48) | Callable definition: inline bool durability(const Event& event) | calls ; returns event.file==ar::FileStage::write_data \|\| event.file==ar::FileStage::sync_file \|\|; event.root==recov… · [reviewed contract](#b0009) |
| [B0010 · 54–54](../../../../../tests/support/sql_aggregate_session_probe.hpp#L54) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::sql_aggregate_session_test · [reviewed contract](#b0010) |

## B0001

[Lines 1–14](../../../../../tests/support/sql_aggregate_session_probe.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:606846cc3e2f4dd7b181839bfe85d10cb5dda2bbdc31e6af80c23d520dc3903b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare sql_aggregate_session_probe.hpp: include "sql_aggregate_session_fixture.hpp", "sql_aggregate_file_probe.hpp", "generation_file_probe.hpp", "index_allocation.hpp", &lt;cerrno&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/sql_aggregate_session_probe.hpp](../../../../../tests/support/sql_aggregate_session_probe.hpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 15–19](../../../../../tests/support/sql_aggregate_session_probe.hpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Event
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store one joined observation from either test-only file seam without allocating during callbacks. |
| inputs / outputs | Shared point ordinal, seam kind, before/after state, file/root stage, target and syscall result in each fixed event. |
| invariants | This is test trace data only; the ordinal assigned by Hook is common across the WAL/sink and generation-root callbacks, not a production protocol sequence. |
| ownership | Hook owns a fixed-size array of 4096 Event values. |
| failure | Trace overflow is an assertion failure in the owning Hook. |
| cost | Fixed-size storage and scalar writes per observed attempt. |
| Design | [tests/unit/sql_aggregate_session_fault_test.cpp](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp), [tests/support/sql_aggregate_file_probe.hpp](../../../../../tests/support/sql_aggregate_file_probe.hpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [tests/support/sql_aggregate_session_probe.hpp](../../../../../tests/support/sql_aggregate_session_probe.hpp), [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp) |

## B0003

[Lines 20–23](../../../../../tests/support/sql_aggregate_session_probe.hpp#L20); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Hook
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Combine the two test-only syscall callbacks, a shared ordinal and fixed event storage for one fault scenario. |
| inputs / outputs | Optional before/after failure, process-exit or allocation-denial target in; observations and seam decisions out. |
| invariants | One point is counted at each before observation and reused for its after observation. This hook does not replace production file owners or turn allocation counting into syscall counting. |
| ownership | Owns the fixed Event array and scalar control state; callback context is borrowed by the installed test seams. |
| failure | Test assertions catch trace overflow; injected failures are returned through the relevant seam decision. |
| cost | O(1) per event, with no dynamic trace growth. |
| Design | [tests/unit/sql_aggregate_session_fault_test.cpp](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp), [tests/support/sql_aggregate_file_probe.hpp](../../../../../tests/support/sql_aggregate_file_probe.hpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [tests/support/sql_aggregate_session_probe.hpp](../../../../../tests/support/sql_aggregate_session_probe.hpp), [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp) |

## B0004

[Lines 24–30](../../../../../tests/support/sql_aggregate_session_probe.hpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void observe(bool generation,bool done,ar::FileStage file,recovery::GenerationStage root,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record one seam observation and trigger the selected child exit or post-I/O C++-new denial. |
| inputs / outputs | Seam kind, before/after marker, stages, target and syscall result in; fixed event append, optional \`_exit(77)\` or allocation-counter reset out. |
| invariants | \`point\` advances only on a before event; the matching after event reuses that point. A crash cut exits at the requested observation; allocation denial starts only at a selected after observation. |
| ownership | Uses the parent Hook's fixed array and scalar fields; callback does not retain event arguments. |
| failure | An observation beyond the fixed array asserts; \`_exit(77)\` deliberately ends the child at the selected point. |
| cost | Fixed scalar work and one fixed-array write per before/after event. |
| Design | [tests/unit/sql_aggregate_session_fault_test.cpp](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [tests/support/sql_aggregate_session_probe.hpp](../../../../../tests/support/sql_aggregate_session_probe.hpp), [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp) |

## B0005

[Lines 31–36](../../../../../tests/support/sql_aggregate_session_probe.hpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static ar::testing::FileDecision file(const ar::testing::FileEvent& event,void* context) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject a selected before/after EIO through the actual aggregate WAL/sink file test seam. |
| inputs / outputs | Actual FileEvent and Hook context in; FileDecision with the chosen error side out. |
| invariants | The implementation calls POSIX I/O unless the hook denies the attempt. For ordinary stages, error_after follows a successful real call and changes its reported result to EIO. Descriptor-acquisition after-errors are normalized to before the call so an acquired FD cannot be hidden; the after callback itself is observational. |
| ownership | Borrows the stack Hook context only while Installed is alive. |
| failure | The actual owner reports its normal FileFailure path; this callback is noexcept and does not translate it. |
| cost | Fixed event forwarding and decision construction per seam callback. |
| Design | [tests/unit/sql_aggregate_session_fault_test.cpp](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp), [tests/support/sql_aggregate_file_probe.hpp](../../../../../tests/support/sql_aggregate_file_probe.hpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [tests/support/sql_aggregate_session_probe.hpp](../../../../../tests/support/sql_aggregate_session_probe.hpp), [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp) |

## B0006

[Lines 37–42](../../../../../tests/support/sql_aggregate_session_probe.hpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static gt::GenerationDecision root(const gt::GenerationEvent& event,void* context) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject a selected before/after EIO through the actual generation-root file test seam. |
| inputs / outputs | Actual GenerationEvent and Hook context in; GenerationDecision with the chosen error side out. |
| invariants | The implementation calls POSIX I/O unless the hook denies the attempt. For ordinary stages, error_after follows a successful real call and changes its reported result to EIO. Descriptor-acquisition after-errors are normalized to before the call so an acquired FD cannot be hidden; the after callback itself is observational. |
| ownership | Borrows the stack Hook context only while Installed is alive. |
| failure | The actual owner reports its normal GenerationFailure path; this callback is noexcept and does not translate it. |
| cost | Fixed event forwarding and decision construction per seam callback. |
| Design | [tests/unit/sql_aggregate_session_fault_test.cpp](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [tests/support/sql_aggregate_session_probe.hpp](../../../../../tests/support/sql_aggregate_session_probe.hpp), [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp) |

## B0007

[Lines 43–43](../../../../../tests/support/sql_aggregate_session_probe.hpp#L43); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L43-L43:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in sql_aggregate_session_probe.hpp: struct Hook. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/sql_aggregate_session_probe.hpp](../../../../../tests/support/sql_aggregate_session_probe.hpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 44–47](../../../../../tests/support/sql_aggregate_session_probe.hpp#L44); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Installed
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install both seam callbacks for a test scope and clear them before their borrowed Hook context dies. |
| inputs / outputs | Hook reference in; callbacks active until scope exit. |
| invariants | The setters replace thread-local callbacks and do not stack; the destructor clears both to null rather than restoring a prior installation. |
| ownership | Hook remains owned by caller and outlives Installed. |
| failure | Setters are noexcept; actual I/O failures arise from operations performed inside the scope. |
| cost | Two callback/context assignments at install and two at clear. |
| Design | [tests/unit/sql_aggregate_session_fault_test.cpp](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp), [tests/support/sql_aggregate_file_probe.hpp](../../../../../tests/support/sql_aggregate_file_probe.hpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [tests/support/sql_aggregate_session_probe.hpp](../../../../../tests/support/sql_aggregate_session_probe.hpp), [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp) |

## B0009

[Lines 48–53](../../../../../tests/support/sql_aggregate_session_probe.hpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline bool durability(const Event& event)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the actual file stages at which the child-cut matrix tests process exit around writes, synchronization, namespace publication and tail truncation. |
| inputs / outputs | One observed file/root event in; whether its stage is in the configured cut set out. |
| invariants | The selected stages are concrete syscall boundaries. A later \`_exit\` in a child on the same filesystem is not a power-loss or hardware durability experiment. |
| ownership | Reads one fixed Event value. |
| failure | No failure conversion; unknown/nonselected stages return false. |
| cost | Fixed enum comparisons. |
| Design | [tests/unit/sql_aggregate_session_fault_test.cpp](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp), [tests/support/sql_aggregate_file_probe.hpp](../../../../../tests/support/sql_aggregate_file_probe.hpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [tests/support/sql_aggregate_session_probe.hpp](../../../../../tests/support/sql_aggregate_session_probe.hpp), [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp) |

## B0010

[Lines 54–54](../../../../../tests/support/sql_aggregate_session_probe.hpp#L54); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L54-L54:sha256:0f51d2659db00bf65eab7675fffa3044b854e9a8a6b1c716ab512242848ee9cf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in sql_aggregate_session_probe.hpp: namespace crown::sql_aggregate_session_test. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/sql_aggregate_session_probe.hpp](../../../../../tests/support/sql_aggregate_session_probe.hpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |
