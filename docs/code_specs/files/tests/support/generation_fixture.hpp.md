# `tests/support/generation_fixture.hpp` — block usage map

[Source](../../../../../tests/support/generation_fixture.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `622dba4b95bca76bebb4bc9a2ec6b8478280d0dc52d6fbbdfc49996ecf177669`. 42 lines partitioned into 9 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../tests/support/generation_fixture.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 14–16](../../../../../tests/support/generation_fixture.hpp#L14) | Callable definition: inline runtime::SessionGenerationOptions options() | calls session_journal_test::options; returns result · [reviewed contract](#b0002) |
| [B0003 · 17–19](../../../../../tests/support/generation_fixture.hpp#L17) | Callable definition: inline runtime::SessionGenerationRecoveryOptions recovery_options() | calls session_journal_test::options; returns result · [reviewed contract](#b0003) |
| [B0004 · 20–22](../../../../../tests/support/generation_fixture.hpp#L20) | Callable definition: inline std::string path(const std::string& root,std::uint64_t generation,std::string_view suffix) | calls std::setw, std::setfill, str; returns out.str() · [reviewed contract](#b0004) |
| [B0005 · 23–25](../../../../../tests/support/generation_fixture.hpp#L23) | Callable definition: inline void put(const std::string& name,std::string_view bytes) | calls out, write, data, size; guard std::ofstream out(name,std::ios::binary\|std::ios::trunc);out.write(bytes.data(),static_cast&lt;std::st… · [reviewed contract](#b0005) |
| [B0006 · 26–26](../../../../../tests/support/generation_fixture.hpp#L26) | Explanatory comments or spacing. | source comment (unverified): // Inspected fixed metadata is not a native owner or retirement/publication receipt. · [reviewed contract](#b0006) |
| [B0007 · 27–27](../../../../../tests/support/generation_fixture.hpp#L27) | Callable definition: inline recovery::GenerationRoot root(const std::string& name) | calls recovery::inspect_generation_root, contents; returns recovery::inspect_generation_root(contents(name)); source comment (unverified): // Inspected fixed metadata is not a native owner or retirement/publication receipt. · [reviewed contract](#b0007) |
| [B0008 · 28–41](../../../../../tests/support/generation_fixture.hpp#L28) | Type/record definition: struct Fixture | guard check(session-&gt;begin_next(),"generation event missing");static_cast&lt;void&gt;(typed::finish(*session)); · [reviewed contract](#b0008) |
| [B0009 · 42–42](../../../../../tests/support/generation_fixture.hpp#L42) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::generation_test · [reviewed contract](#b0009) |

## B0001

[Lines 1–13](../../../../../tests/support/generation_fixture.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:4c748c4f6d8e166a06626e3be9fe197e4baf277ef316833daede642f90bab54e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare generation_fixture.hpp: include "crown/runtime/session_generation.hpp", "session_journal_fixture.hpp", &lt;iomanip&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/generation_fixture.hpp](../../../../../tests/support/generation_fixture.hpp), [docs/generations.md](../../../../generations.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 14–16](../../../../../tests/support/generation_fixture.hpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline runtime::SessionGenerationOptions options(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare fixed generation writer options. |
| inputs / outputs | Starts defaults and assigns session_journal_test::options to journal. |
| invariants | Deterministic query ID and default finite limits are metadata, not accepted root/file authority. |
| ownership | Returns owning option value; no source/owner borrow is stored. |
| failure | No explicit rejection in setup; real enable/restore later checks options/files. |
| cost | Fixed option copy/construction; native admission and I/O costs occur later. |
| Design | [tests/support/generation_fixture.hpp](../../../../../tests/support/generation_fixture.hpp), [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/generations.md](../../../../generations.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 17–19](../../../../../tests/support/generation_fixture.hpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline runtime::SessionGenerationRecoveryOptions recovery_options(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare matching generation replay options. |
| inputs / outputs | Starts defaults and assigns the same journal options under replay.journal. |
| invariants | Deterministic query ID and default finite limits are metadata, not accepted root/file authority. |
| ownership | Returns owning option value; no source/owner borrow is stored. |
| failure | No explicit rejection in setup; real enable/restore later checks options/files. |
| cost | Fixed option copy/construction; native admission and I/O costs occur later. |
| Design | [tests/support/generation_fixture.hpp](../../../../../tests/support/generation_fixture.hpp), [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/generations.md](../../../../generations.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 20–22](../../../../../tests/support/generation_fixture.hpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::string path(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Format a trusted generation component pathname. |
| inputs / outputs | Returns root + .g + sixteen lowercase zero-padded hex digits + suffix. |
| invariants | uint64 generation fits 16 hex digits; suffix/root are trusted fixture strings, with no path sanitization or file access. |
| ownership | ostringstream and returned string own ordinary bytes; no retained views. |
| failure | Stream/string allocations propagate; stream error flags are not explicitly asserted. |
| cost | O(root + suffix bytes) formatting/copy with ordinary stream allocations. |
| Design | [tests/support/generation_fixture.hpp](../../../../../tests/support/generation_fixture.hpp), [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/generations.md](../../../../generations.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 23–25](../../../../../tests/support/generation_fixture.hpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void put(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Overwrite a generation fixture component for corruption/tail tests. |
| inputs / outputs | Binary truncates/writes bytes and checks stream state before stream destruction. |
| invariants | No fsync/atomic publication/close-error guarantee; this intentionally bypasses valid native publication. |
| ownership | Borrowed byte view through synchronous write; stream owns descriptor locally. |
| failure | Flag/assertion or allocation failure can leave partial/truncated file; no rollback. |
| cost | O(bytes) actual file write plus ordinary stream/path storage. |
| Design | [tests/support/generation_fixture.hpp](../../../../../tests/support/generation_fixture.hpp), [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/generations.md](../../../../generations.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 26–26](../../../../../tests/support/generation_fixture.hpp#L26); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L26:sha256:650bf0b1ca5483f59dd42d67abb930ef9b69f1e320a79252ac12fb47ab83d492
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Inspected fixed metadata is not a native owner or retirement/publication receipt. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/generation_fixture.hpp](../../../../../tests/support/generation_fixture.hpp), [docs/generations.md](../../../../generations.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 27–27](../../../../../tests/support/generation_fixture.hpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline recovery::GenerationRoot root(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect actual root file bytes for test assertions. |
| inputs / outputs | Reads an ordinary temporary string then calls inspect_generation_root and returns its fixed metadata. |
| invariants | Inspection validates root wire structure/integrity; returned editable metadata alone is not native source, lock or publication authority. |
| ownership | Return owns fixed metadata; input temporary dies after inspection with no dangling views. |
| failure | Read helper flags are unchecked; resulting missing/corrupt bytes are rejected by actual inspector; allocation/inspection failure propagates. |
| cost | Full root-file read and checksum/format scan; no query runtime restore. |
| Design | [tests/support/generation_fixture.hpp](../../../../../tests/support/generation_fixture.hpp), [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/generations.md](../../../../generations.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 28–41](../../../../../tests/support/generation_fixture.hpp#L28); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fixture
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a real typed session and optional enabled generation family in a temporary directory. |
| inputs / outputs | Members retain Directory, typed Case, move-only session and owning root pathname. |
| invariants | enable=false intentionally leaves generation unenabled for negative tests; true performs actual enable_generation after start. |
| ownership | Session dies before Directory; source DTOs/paths own ordinary copies and native admission owns actual runtime state. |
| failure | Construction/native/file failures propagate; earlier real file effects are not rolled back by the helper. |
| cost | Real compiler/session/generation setup plus ordinary trace/path allocations; file durability follows production APIs. |
| Design | [tests/support/generation_fixture.hpp](../../../../../tests/support/generation_fixture.hpp), [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/generations.md](../../../../generations.md), [docs/code_review.md](../../../../code_review.md) |

```text
explicit Fixture(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Start a typed fixture session and optionally enable generations. |
| inputs / outputs | Creates plan/session using kind-sensitive mode, constructs query.root and calls start/enable_generation. |
| invariants | Supported typed kinds remain0..5; optional enable controls actual API call rather than a private proof flag. |
| ownership | Session Owner is move-only; copied plan handle retains compiler control; directory/path outlive live descriptors. |
| failure | Member initialization and native start/enable errors propagate with completed members unwound. |
| cost | Actual lowering/native admission and optional root/checkpoint/journal creation, checksumming and I/O. |
| Design | [tests/support/generation_fixture.hpp](../../../../../tests/support/generation_fixture.hpp), [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/generations.md](../../../../generations.md), [docs/code_review.md](../../../../code_review.md) |

```text
void update(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit one real generation-backed update and drain its public signed result. |
| inputs / outputs | Uses updates\[index\], feed offset sequence*10, accepted batch, begin_next and typed::finish. |
| invariants | Trusted index/finite sequence required. Does not independently verify mathematical rows here; typed::finish checks ordinal/duplicates. |
| ownership | Session owns admitted input/state; ordinary temporary output is discarded only after drain. |
| failure | Enqueue/engine/export/assertion failure propagates and may follow commit. |
| cost | Actual update/persistence work plus complete signed output export/set construction. |
| Design | [tests/support/generation_fixture.hpp](../../../../../tests/support/generation_fixture.hpp), [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/generations.md](../../../../generations.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 42–42](../../../../../tests/support/generation_fixture.hpp#L42); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L42-L42:sha256:751abf1ceaf2a2837eba1d41c5ec6a68d4c91b8cb90d2e39c07c6baf679ff774
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in generation_fixture.hpp: namespace crown::generation_test. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/generation_fixture.hpp](../../../../../tests/support/generation_fixture.hpp), [docs/generations.md](../../../../generations.md), [docs/code_review.md](../../../../code_review.md) |
