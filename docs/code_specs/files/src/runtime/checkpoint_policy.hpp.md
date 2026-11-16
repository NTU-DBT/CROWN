# `src/runtime/checkpoint_policy.hpp` — block usage map

[Source](../../../../../src/runtime/checkpoint_policy.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Turn private physical/support prefixes into exact duplicate-free query answer additions/deletions with explicit producer and delivery policies.

Snapshot SHA-256: `66867c7b8d5a863e36bedd579fc2fdb82fd9875d2fa5657ca65f1adf6ee098ac`. 44 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [delta](../../../subsystem_contracts.md#delta). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/delta_transition_spec.md](../../../../delta_transition_spec.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/anchored_delta.md](../../../../anchored_delta.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../src/runtime/checkpoint_policy.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Fixed policy words describe options, not account, source or committed-state authority. · [reviewed contract](#b0001) |
| [B0002 · 7–20](../../../../../src/runtime/checkpoint_policy.hpp#L7) | Callable definition: inline std::array&lt;std::uint64_t,26&gt; checkpoint_policy(const DeltaOptions& options,DeltaMode mode) | calls at, word, has_value, value_or; returns result; source comment (unverified): // Fixed policy words describe options, not account, source or committed-state authority. · [reviewed contract](#b0002) |
| [B0003 · 21–21](../../../../../src/runtime/checkpoint_policy.hpp#L21) | Explanatory comments or spacing. | source comment (unverified): // Encoding checks precede runtime admission; receiving memory replaces the old ceiling. · [reviewed contract](#b0003) |
| [B0004 · 22–43](../../../../../src/runtime/checkpoint_policy.hpp#L22) | Callable definition: inline DeltaOptions checkpoint_options(const std::array&lt;std::uint64_t,26&gt;& words,std::uint64_t memory) | calls recovery::ImageFailure, at, word, check; guard const auto host=\[&\]{const auto value=word();check(value&lt;=SIZE_MAX);return static_cast&lt;std::size_t&gt;(…; returns words.at(position++); static_cast&lt;std::size_t&gt;(value); source comment (unverified): // Encoding checks precede runtime admission; receiving memory replaces the old ceiling. · [reviewed contract](#b0004) |
| [B0005 · 44–44](../../../../../src/runtime/checkpoint_policy.hpp#L44) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime::detail · [reviewed contract](#b0005) |

## B0001

[Lines 1–6](../../../../../src/runtime/checkpoint_policy.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L6:sha256:527375f2e730ba3df0c43ddac21ae969e977c6f10eb801dfb864d60dff18bc87
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/checkpoint_policy.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/runtime/delta.hpp"\` for compilation; opens namespace \`crown::runtime::detail\`. Source comment: Fixed policy words describe options, not account, source or committed-state authority. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The source note says: Fixed policy words describe options, not account, source or committed-state authority. Prose alone does not enforce the rule. |
| ownership | The source comment describes this adjacent lifetime/account boundary: Fixed policy words describe options, not account, source or committed-state authority. The comment creates no owner; member types and callers determine actual retention. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/session-journal.md](../../../../session-journal.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 7–20](../../../../../src/runtime/checkpoint_policy.hpp#L7); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::array<std::uint64_t,26> checkpoint_policy(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pack the exact fixed-width Delta policy portion of a checkpoint. |
| inputs / outputs | Reads valid producer options and explicit actual mode into 26 uint64 words; each optional work cap occupies canonical presence/value words, absent encoded as 0/0. |
| invariants | Order is support work(2), support cap/order/transition(3), observation mode/cap/period/offset/timing/reserved(6), physical work(2)/derivation(1), actual mode/view/live/completion(4), Delta/cursor/epoch-view work(6), spool row/byte(2). Reserved word stays zero. Query account/memory cap, source identity and committed state are not serialized here. |
| ownership | Borrows options only during the call; returned array owns inline words and no grant, row or runtime owner. |
| failure | Valid 26-word implementation fills in bounds; array::at would expose an internal layout mismatch rather than silently writing beyond the array. No error translation. |
| cost | Fixed 26-word writes and optional/enum conversions, with no input traversal, heap graph or runtime execution. |
| Design | [src/runtime/checkpoint_policy.hpp](../../../../../src/runtime/checkpoint_policy.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

```text
  const auto optional=[&](std::optional<std::uint64_t> value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode optional policy work with explicit presence rather than an overloaded zero. |
| inputs / outputs | Invokes word twice: presence then value_or(0). |
| invariants | Present zero remains a finite zero cap; absent means unspecified and has canonical zero payload. |
| ownership | Captures the local array writer by reference only until checkpoint_policy returns. |
| failure | Only the enclosing bounds-checked writer can reject an internal width error. |
| cost | Two inline word stores per optional, no grant admission or allocation. |
| Design | [src/runtime/checkpoint_policy.hpp](../../../../../src/runtime/checkpoint_policy.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 21–21](../../../../../src/runtime/checkpoint_policy.hpp#L21); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L21:sha256:3c6ea59ed4e3b155c165d6b096b7d234364e9a185dc3d56c5813493f0f9831ad
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`inline DeltaOptions checkpoint_options(const std::array&lt;std::uint64_t,26&gt;& words,std::uint64_t memory)\`: Encoding checks precede runtime admission; receiving memory replaces the old ceiling. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/checkpoint_policy.hpp:L22; use that declaration for the actual input/output shape. |
| invariants | The source note states: Encoding checks precede runtime admission; receiving memory replaces the old ceiling. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/session-journal.md](../../../../session-journal.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0004

[Lines 22–43](../../../../../src/runtime/checkpoint_policy.hpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline DeltaOptions checkpoint_options(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode the fixed policy words while binding recovery to the receiving memory ceiling. |
| inputs / outputs | Reads the 26 words in matching order, returning DeltaOptions with support.memory_limit_bytes set from the explicit receiving memory argument. |
| invariants | Boolean values are 0/1; absent optional values must be zero; reserved word is zero; enum values fit the source-defined contiguous domains; host-sized capacities must fit SIZE_MAX. This validates encoding, not all semantic runtime options or checkpoint source/plan authority. |
| ownership | Result owns inline options only; it neither retains the image array nor creates/replaces a MemoryAccount or consumed work allowance. |
| failure | Noncanonical words throw recovery::ImageFailure(corrupt); at() remains an internal width guard. Later runtime/recovery admission performs plan, option and image binding checks; no catch/fallback. |
| cost | Fixed-word decoding/range checks and assignments; no row, source or plan traversal and no successful heap allocation. |
| Design | [src/runtime/checkpoint_policy.hpp](../../../../../src/runtime/checkpoint_policy.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

```text
  const auto optional=[&]() -> std::optional<std::uint64_t> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate optional policy presence and its canonical absent payload. |
| inputs / outputs | Reads a canonical boolean then value and returns present(value) or nullopt. |
| invariants | Rejects absent/nonzero pairs; present zero is preserved. |
| ownership | Only local decoder cursor/word values are captured; no image lifetime is extended. |
| failure | Noncanonical pairs throw ImageFailure(corrupt) before options are returned. |
| cost | Two fixed reads/checks per optional, without heap work. |
| Design | [src/runtime/checkpoint_policy.hpp](../../../../../src/runtime/checkpoint_policy.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

```text
  const auto enumeration=[&]<class T>(T maximum) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound an image enum word before casting it to the supported policy enum. |
| inputs / outputs | Accepts only values at most the supplied last enumerator; each actual call uses a zero-based contiguous enum. |
| invariants | This upper-bound scheme depends on those currently contiguous definitions; it is not a general sparse-enum validator. |
| ownership | Returns an inline enum, retaining no input reference. |
| failure | Unsupported value throws ImageFailure(corrupt). |
| cost | One fixed word read and unsigned comparison/cast. |
| Design | [src/runtime/checkpoint_policy.hpp](../../../../../src/runtime/checkpoint_policy.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 44–44](../../../../../src/runtime/checkpoint_policy.hpp#L44); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L44-L44:sha256:e39c39ee7071fa62eb75df66509c0b467a6749ca8a3a61a663367890341483eb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime::detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime::detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime::detail\` at its lexical source position in src/runtime/checkpoint_policy.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime::detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/session-journal.md](../../../../session-journal.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
