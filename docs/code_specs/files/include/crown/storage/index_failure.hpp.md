# `include/crown/storage/index_failure.hpp` — block usage map

[Source](../../../../../../include/crown/storage/index_failure.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `0676ffdf91d833f962a163a96ebb2b5a4238f7bbd1d498c7172d0e93c76096fc`. 46 lines partitioned into 10 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/storage.md](../../../../../storage.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../../include/crown/storage/index_failure.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 8–9](../../../../../../include/crown/storage/index_failure.hpp#L8) | Type/record definition: enum class IndexFault |  · [reviewed contract](#b0002) |
| [B0003 · 10–12](../../../../../../include/crown/storage/index_failure.hpp#L10) | declares types or opens a type body. | source comment (unverified): // The carrier owns no dynamic diagnostic text; throwing still uses the · [reviewed contract](#b0003) |
| [B0004 · 13–14](../../../../../../include/crown/storage/index_failure.hpp#L13) | Callable definition: public: explicit IndexFailure(IndexFault fault) noexcept : fault_(fault) | calls fault_ · [reviewed contract](#b0004) |
| [B0005 · 15–31](../../../../../../include/crown/storage/index_failure.hpp#L15) | Callable definition: \[\[nodiscard\]\] std::string_view code() const noexcept | calls ; returns @; @ · [reviewed contract](#b0005) |
| [B0006 · 32–32](../../../../../../include/crown/storage/index_failure.hpp#L32) | Callable definition: \[\[nodiscard\]\] const char* what() const noexcept override | calls code, data; returns code().data() · [reviewed contract](#b0006) |
| [B0007 · 33–36](../../../../../../include/crown/storage/index_failure.hpp#L33) | declares namespace scope. |  · [reviewed contract](#b0007) |
| [B0008 · 37–41](../../../../../../include/crown/storage/index_failure.hpp#L37) | Type/record definition: struct LegacyIndexErrors |  · [reviewed contract](#b0008) |
| [B0009 · 42–44](../../../../../../include/crown/storage/index_failure.hpp#L42) | Type/record definition: struct FixedIndexErrors |  · [reviewed contract](#b0009) |
| [B0010 · 45–46](../../../../../../include/crown/storage/index_failure.hpp#L45) | Closes surrounding scope/type. |  · [reviewed contract](#b0010) |

## B0001

[Lines 1–7](../../../../../../include/crown/storage/index_failure.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:a2d6668e83bdaa90df2edf9df1fb8887d023984c39c56ca713eda1286f071211
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in include/crown/storage/index_failure.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/api/error.hpp"\`, \`&lt;exception&gt;\`, \`&lt;string_view&gt;\` for compilation; opens namespace \`crown::storage\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0002

[Lines 8–9](../../../../../../include/crown/storage/index_failure.hpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class IndexFault { contract, capacity, overflow, work_limit, layout_mismatch,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name fixed native index/storage failure categories. |
| inputs / outputs | Tags cover contract/capacity/overflow/work/token/owner/index/handle/busy/storage/journal/cursor failures. |
| invariants | A fault category describes rejection, not whether a caller may retry or publish partially prepared state. |
| ownership | The scalar/metadata result retains no row, account or runtime ownership; plain record declarations here own only their shown inline fields. |
| failure | The enum declaration has no runtime effect. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/index_failure.hpp](../../../../../../include/crown/storage/index_failure.hpp), [include/crown/api/error.hpp](../../../../../../include/crown/api/error.hpp), [src/storage/accounted_indexed.cpp](../../../../../../src/storage/accounted_indexed.cpp), [src/storage/indexed.cpp](../../../../../../src/storage/indexed.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 10–12](../../../../../../include/crown/storage/index_failure.hpp#L10); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class IndexFailure final
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose fixed native index faults as stable static diagnostic codes. |
| inputs / outputs | Constructor takes IndexFault; code returns string_view and what returns the same literal bytes as const char*. |
| invariants | The fallback for invalid tag casts is storage_contract; code conversion does not construct/catch a legacy Error. |
| ownership | Only the fault enum is carried; diagnostic text has static program lifetime. |
| failure | The carrier/accessors are noexcept; throwing it remains subject to exception-runtime behavior. |
| cost | Fixed carrier and bounded switch; no owned diagnostic string or dynamic formatting. |
| Design | [include/crown/storage/index_failure.hpp](../../../../../../include/crown/storage/index_failure.hpp), [include/crown/api/error.hpp](../../../../../../include/crown/api/error.hpp), [src/storage/accounted_indexed.cpp](../../../../../../src/storage/accounted_indexed.cpp), [src/storage/indexed.cpp](../../../../../../src/storage/indexed.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0004

[Lines 13–14](../../../../../../include/crown/storage/index_failure.hpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit IndexFailure(IndexFault fault) noexcept : fault_(fault) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a native exception carrier containing only a fault tag. |
| inputs / outputs | IndexFailure stores the supplied IndexFault and initializes its standard exception base. |
| invariants | No formatted message, owning std::string or recovery state is embedded in the carrier. |
| ownership | The carrier owns its enum; code()/what() later return static literals. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size carrier construction; throwing the carrier can still use exception-runtime storage, which is not an ordinary-new-free theorem. |
| Design | [include/crown/storage/index_failure.hpp](../../../../../../include/crown/storage/index_failure.hpp), [include/crown/api/error.hpp](../../../../../../include/crown/api/error.hpp), [src/storage/accounted_indexed.cpp](../../../../../../src/storage/accounted_indexed.cpp), [src/storage/indexed.cpp](../../../../../../src/storage/indexed.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 15–31](../../../../../../include/crown/storage/index_failure.hpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::string_view code() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map native fault tags directly to stable diagnostic codes. |
| inputs / outputs | The switch returns a static string_view for every declared fault; an unknown cast falls back to storage_contract. |
| invariants | Mapping must preserve legacy external code spellings without constructing Error to recover its code. |
| ownership | Returned text is a static literal with program lifetime. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | A bounded switch over twelve cases; no owning string, heap allocation or traversal. |
| Design | [include/crown/storage/index_failure.hpp](../../../../../../include/crown/storage/index_failure.hpp), [include/crown/api/error.hpp](../../../../../../include/crown/api/error.hpp), [src/storage/accounted_indexed.cpp](../../../../../../src/storage/accounted_indexed.cpp), [src/storage/indexed.cpp](../../../../../../src/storage/indexed.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0006

[Lines 32–32](../../../../../../include/crown/storage/index_failure.hpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] const char* what() const noexcept override { return code().data(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the fixed diagnostic code as exception what(). |
| inputs / outputs | Returns code().data(), whose literal is null terminated. |
| invariants | The returned message is the code, not an allocation-rich contextual diagnostic. |
| ownership | Static literal bytes remain valid independently of carrier lifetime. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Bounded code mapping and pointer return; no allocation. |
| Design | [include/crown/storage/index_failure.hpp](../../../../../../include/crown/storage/index_failure.hpp), [include/crown/api/error.hpp](../../../../../../include/crown/api/error.hpp), [src/storage/accounted_indexed.cpp](../../../../../../src/storage/accounted_indexed.cpp), [src/storage/indexed.cpp](../../../../../../src/storage/indexed.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0007

[Lines 33–36](../../../../../../include/crown/storage/index_failure.hpp#L33); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexFault fault_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store the fixed IndexFault discriminator in IndexFailure. |
| inputs / outputs | A fault enum enters the constructor; code()/what() expose its mapped static diagnostic. |
| invariants | The carrier stores no dynamic text. |
| ownership | The enum is stored by value; returned diagnostic bytes are string literals. |
| failure | The field itself cannot fail; throwing the exception can use implementation exception-runtime storage. |
| cost | Enum storage and code lookup only; no message string allocation is performed by this carrier. |
| Design | [include/crown/storage/index_failure.hpp §IndexFailure](../../../../../../include/crown/storage/index_failure.hpp), [src/storage/accounted_indexed.cpp §fixed IndexFailure use](../../../../../../src/storage/accounted_indexed.cpp), [docs/memory_accounts.md §Optimized table work and ownership](../../../../../memory_accounts.md) |

## B0008

[Lines 37–41](../../../../../../include/crown/storage/index_failure.hpp#L37); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct LegacyIndexErrors {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve formatted Error diagnostics for standalone index boundaries. |
| inputs / outputs | fail(fault,message) converts the fixed code to std::string and throws crown::Error with the supplied message. |
| invariants | This deliberate policy differs from FixedIndexErrors; it must not be used to promise native failure paths with no owning diagnostic. |
| ownership | The thrown Error owns copied code/message text; the supplied message is consumed synchronously. |
| failure | Always throws Error on successful formatting; string/exception allocation itself may fail. There is no catch/translation retry. |
| cost | Error code/message construction costs their byte lengths and can allocate, in addition to exception-runtime cost. |
| Design | [include/crown/storage/index_failure.hpp](../../../../../../include/crown/storage/index_failure.hpp), [include/crown/api/error.hpp](../../../../../../include/crown/api/error.hpp), [src/storage/accounted_indexed.cpp](../../../../../../src/storage/accounted_indexed.cpp), [src/storage/indexed.cpp](../../../../../../src/storage/indexed.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0009

[Lines 42–44](../../../../../../include/crown/storage/index_failure.hpp#L42); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FixedIndexErrors {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Throw a fixed carrier at native index rejection points. |
| inputs / outputs | fail(fault,const char*) discards contextual text and throws IndexFailure(fault). |
| invariants | Stable enum-to-code mapping replaces dynamic message ownership; no fallback formatting is performed. |
| ownership | The carrier retains only its fault tag. |
| failure | Always throws IndexFailure; no handler or retry is hidden. The exception runtime may allocate outside ordinary operator new. |
| cost | Fixed carrier construction; no owned diagnostic string or message scan. |
| Design | [include/crown/storage/index_failure.hpp](../../../../../../include/crown/storage/index_failure.hpp), [include/crown/api/error.hpp](../../../../../../include/crown/api/error.hpp), [src/storage/accounted_indexed.cpp](../../../../../../src/storage/accounted_indexed.cpp), [src/storage/indexed.cpp](../../../../../../src/storage/indexed.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0010

[Lines 45–46](../../../../../../include/crown/storage/index_failure.hpp#L45); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L46:sha256:285577568ac35d60830cf925beb22babfffdf80c35bfd45a12e88fdba305694d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in include/crown/storage/index_failure.hpp: closes \`namespace detail\`, \`namespace crown::storage\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |
