# `tests/support/generation_file_probe.hpp` — block usage map

[Source](../../../../../tests/support/generation_file_probe.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `ebd4b45f178de1550a96458198ca1b231abebb1d8249b11f76c75b7738bf4d21`. 18 lines partitioned into 4 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../tests/support/generation_file_probe.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Same ordinal before/after one admitted syscall; requested is the original size. · [reviewed contract](#b0001) |
| [B0002 · 6–9](../../../../../tests/support/generation_file_probe.hpp#L6) | Type/record definition: struct GenerationEvent | source comment (unverified): // Same ordinal before/after one admitted syscall; requested is the original size. · [reviewed contract](#b0002) |
| [B0003 · 10–14](../../../../../tests/support/generation_file_probe.hpp#L10) | Type/record definition: struct GenerationDecision |  · [reviewed contract](#b0003) |
| [B0004 · 15–18](../../../../../tests/support/generation_file_probe.hpp#L15) | declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Only the before decision is applied; context is borrowed until explicitly cleared. · [reviewed contract](#b0004) |

## B0001

[Lines 1–5](../../../../../tests/support/generation_file_probe.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L5:sha256:13267341ec240ca9c9037b9ebeea308d3291bca2876e0f44bc8de7f14d52d2ed
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare generation_file_probe.hpp: include "crown/recovery/generation.hpp", &lt;limits&gt;. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [docs/generations.md](../../../../generations.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 6–9](../../../../../tests/support/generation_file_probe.hpp#L6); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct GenerationEvent
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one before/after observation of an admitted real syscall attempt in the testing runtime. |
| inputs / outputs | Stage, after flag, one-based operation ordinal, original requested transfer, result and errno are fixed event values; before result/errno are placeholders. GenerationTarget also identifies the file role. |
| invariants | Before/after share an ordinal; retries consume new attempts. Counts exclude refused operation-limit entries and are not bytes, elapsed time, query allocations or every host syscall. |
| ownership | Callback borrows this temporary event only for the call; retain copies of scalar fields if needed, not references. |
| failure | The event itself does not throw or authorize recovery; public file/generation outcomes govern publication uncertainty. |
| cost | Fixed scalar construction per hook notification; callback work and actual filesystem operations remain additional costs. |
| Design | [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [tests/unit/history_retirement_fault_test.cpp](../../../../../tests/unit/history_retirement_fault_test.cpp), [docs/generations.md](../../../../generations.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 10–14](../../../../../tests/support/generation_file_probe.hpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct GenerationDecision
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select a deterministic syscall fault/short-transfer scenario for a test. |
| inputs / outputs | Default permits the real syscall. error_before suppresses a non-close attempt; error_after replaces a successful outcome; maximum_transfer caps transfers; zero_entropy replaces returned entropy bytes with zero. |
| invariants | The before decision controls execution; after-callback return is discarded. Open/create after-errors are normalized before acquisition; close still really releases the descriptor. Injected mutation errors can retain conservative unknown publication state. |
| ownership | Fixed owning scalar DTO. No file descriptor, error message, account or automatic restoration responsibility. |
| failure | Models selected syscall errno/partial transfer paths, not C++ new denial, system malloc failure, device durability or all process-crash behaviors. |
| cost | Fixed selection/clamping, plus successful entropy-byte overwrite when requested; real I/O and user callback work remain. |
| Design | [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [tests/unit/history_retirement_fault_test.cpp](../../../../../tests/unit/history_retirement_fault_test.cpp), [docs/generations.md](../../../../generations.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 15–18](../../../../../tests/support/generation_file_probe.hpp#L15); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using GenerationHook=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Specify a nonthrowing private syscall hook with an explicit borrowed context. |
| inputs / outputs | Function pointer receives const event reference and void* context and returns a decision; tests pass a live Hook object address. |
| invariants | Callback must satisfy noexcept and avoid reentering the instrumented owner unexpectedly. Before/after notifications are synchronous on the caller thread; process-exit crash callbacks intentionally do not return. |
| ownership | Neither pointer owns its callback or context. Event/context borrows must end before caller destroys or clears the installation. |
| failure | A thrown exception crossing noexcept terminates; this is deliberately not an exception translation or retry layer. |
| cost | One indirect call for each installed notification; unset hook bypasses callbacks in the testing implementation. |
| Design | [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [tests/unit/history_retirement_fault_test.cpp](../../../../../tests/unit/history_retirement_fault_test.cpp), [docs/generations.md](../../../../generations.md), [docs/code_review.md](../../../../code_review.md) |

```text
void set_generation_hook(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install or clear the current thread's private testing hook. |
| inputs / outputs | Stores a function pointer and context; nullptr/nullptr clears. Definitions live beside the actual owner under CROWN_RUNTIME_TESTING. |
| invariants | Installation is thread_local, replaces any prior pair, and supplies no nesting stack or automatic restoration. Normal Installed scopes clear before Hook destruction; manual setter callers must also clear on any continuing path. |
| ownership | Borrows callback/context without allocation or lifetime extension; caller owns lexical installation discipline. |
| failure | Declared noexcept; no hook validation, public capability or cross-thread propagation. |
| cost | Two thread-local pointer stores; only testing builds consult these seams, with real owner operation/transfer limits still active. |
| Design | [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [tests/unit/history_retirement_fault_test.cpp](../../../../../tests/unit/history_retirement_fault_test.cpp), [docs/generations.md](../../../../generations.md), [docs/code_review.md](../../../../code_review.md) |
