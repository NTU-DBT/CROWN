# `tests/support/sql_aggregate_file_probe.hpp` — block usage map

[Source](../../../../../tests/support/sql_aggregate_file_probe.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `7c2e5956a555b3d347512049367e7899f80dde42a12b66be89a953023563b6a4`. 20 lines partitioned into 4 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../tests/support/sql_aggregate_file_probe.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Test-only syscall seam. Real POSIX I/O runs unless denied; this does not count · [reviewed contract](#b0001) |
| [B0002 · 8–11](../../../../../tests/support/sql_aggregate_file_probe.hpp#L8) | Type/record definition: struct FileEvent | source comment (unverified): // Test-only syscall seam. Real POSIX I/O runs unless denied; this does not count · [reviewed contract](#b0002) |
| [B0003 · 12–16](../../../../../tests/support/sql_aggregate_file_probe.hpp#L12) | Type/record definition: struct FileDecision |  · [reviewed contract](#b0003) |
| [B0004 · 17–20](../../../../../tests/support/sql_aggregate_file_probe.hpp#L17) | declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Borrow callback/context on this thread until replaced; installations do not stack. · [reviewed contract](#b0004) |

## B0001

[Lines 1–7](../../../../../tests/support/sql_aggregate_file_probe.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:92caa103e44ee3057b9ca92ff97ee161606cb5d5dfeb3211239873aea4a9a927
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare sql_aggregate_file_probe.hpp: include "crown/recovery/sql_aggregate_files.hpp", &lt;limits&gt;. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/sql_aggregate_file_probe.hpp](../../../../../tests/support/sql_aggregate_file_probe.hpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 8–11](../../../../../tests/support/sql_aggregate_file_probe.hpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FileEvent {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one before/after observation delivered by the R2 test-only syscall hook. |
| inputs / outputs | The event carries stage, phase, operation ordinal, original requested count, returned result and native errno. |
| invariants | Requested is the original call size rather than the hook-clamped transfer size; after-events report actual call result or injected error metadata. |
| ownership | Events are passed by const reference only during a callback; the hook owns any copied observation it chooses to retain. |
| failure | The type performs no I/O or error handling, and a consumer can truncate its own trace without changing the file owner's operation count. |
| cost | The event is a fixed aggregate with no dynamic storage; hook-side trace arrays are separate test-owned memory. |
| Design | tests/support/sql_aggregate_file_probe.hpp:8-11, include/crown/recovery/sql_aggregate_files.hpp:10-19, src/recovery/sql_aggregate_file_detail.cpp:112-166, tests/unit/sql_aggregate_files_fault_test.cpp:14-34 |

## B0003

[Lines 12–16](../../../../../tests/support/sql_aggregate_file_probe.hpp#L12); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FileDecision {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set deterministic pre-call errors, post-call errors, transfer caps, or zero entropy in the file probe. |
| inputs / outputs | A default decision requests unlimited transfer and no errors; a test callback may set either errno phase, a maximum count or entropy replacement. |
| invariants | The probe is compiled only for the testing seam, and its transfer cap changes actual POSIX call size without replacing the filesystem. |
| ownership | The value is returned by the hook for one event; set_file_hook separately borrows a thread-local function/context pair until replaced. |
| failure | An error-before decision skips most actual calls; an error-after decision reports failure after the operation, with acquisition stages normalized before open to avoid leaking FDs. |
| cost | The decision is a small fixed value; it does not count or inject C++ allocations and creates no syscall queue. |
| Design | tests/support/sql_aggregate_file_probe.hpp:12-16, src/recovery/sql_aggregate_file_detail.cpp:16-20, src/recovery/sql_aggregate_file_detail.cpp:119-165, docs/sql_aggregate_files.md:123-136 |

## B0004

[Lines 17–20](../../../../../tests/support/sql_aggregate_file_probe.hpp#L17); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L20:sha256:7a516a7602dc4b4fb27196097422d82ac4559487a60e8a34ca35829444ce0df2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare sql_aggregate_file_probe.hpp: bind local aliases/name imports; declare helper function signatures without invoking them. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. Function prototypes declare the shown reference/helper API; invocation and any default-argument evaluation occur at the caller. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/sql_aggregate_file_probe.hpp](../../../../../tests/support/sql_aggregate_file_probe.hpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |
