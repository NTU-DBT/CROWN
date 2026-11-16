# `include/crown/api/error.hpp` — block usage map

[Source](../../../../../../include/crown/api/error.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Own a public diagnostic code/message using std::runtime_error; this header carries no planner/runtime validity guarantee.

Snapshot SHA-256: `e6a055f92c2b0d624539b128ab731d9ae2cdc03b84781f7281633714ef3bf92c`. 16 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [api](../../../../subsystem_contracts.md#api). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../../include/crown/api/error.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 8–15](../../../../../../include/crown/api/error.hpp#L8) | Type/record definition: class Error : public std::runtime_error | returns code_ · [reviewed contract](#b0002) |
| [B0003 · 16–16](../../../../../../include/crown/api/error.hpp#L16) | Closes surrounding scope/type. | source comment (unverified): // namespace crown · [reviewed contract](#b0003) |

## B0001

[Lines 1–7](../../../../../../include/crown/api/error.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:f6d943ddafe34436df1471fb242e732d37f17a06e7610c98bde9bdb3ab97bdc8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Header guard, standard exception/string/move dependencies, and crown namespace opening for the public Error type. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The header guard prevents repeat inclusion in a translation unit; imported declarations determine compile-time names. The note/type comments in this span are guidance and do not add runtime validation or a capability. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path is introduced by the guard/imports; incompatible or missing declarations fail during compilation or linking. |
| cost | Preprocessor/compiler work only for these lines; the guard adds no per-operation runtime work. |
| Design | [include/crown/api/error.hpp](../../../../../../include/crown/api/error.hpp), [docs/code_specs/files/include/crown/api/error.hpp.md](error.hpp.md), [docs/code_specs/error_handling.md](../../../../error_handling.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0002

[Lines 8–15](../../../../../../include/crown/api/error.hpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Error : public std::runtime_error
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry an owning public diagnostic code and runtime_error message. |
| inputs / outputs | Constructor takes code by value and message by const string reference; code() returns a const reference to the stored code. |
| invariants | The exception is presentation data only. It establishes no query/planner/runtime validity or atomicity by itself. |
| ownership | runtime_error owns/copies its message representation; Error moves code into code_. A reference from code() expires with this exception object. |
| failure | Construction/formatting can allocate and fail. Native resource-exhaustion internals use fixed diagnostic types before optional public translation. |
| cost | Message/code construction and standard exception-runtime storage are real failure-path costs; code() is a nonallocating borrowed access. |
| Design | [docs/query_memory.md](../../../../../query_memory.md) |

## B0003

[Lines 16–16](../../../../../../include/crown/api/error.hpp#L16); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L16-L16:sha256:250c3e1595f7269cedf50435b03d999ca6184ec33c6daa9baf0e4bd97c55f07a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [include/crown/api/error.hpp](../../../../../../include/crown/api/error.hpp), [docs/code_specs/files/include/crown/api/error.hpp.md](error.hpp.md), [docs/code_specs/error_handling.md](../../../../error_handling.md), [docs/query_memory.md](../../../../../query_memory.md) |
