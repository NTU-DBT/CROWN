# `tests/unit/session_file_test.cpp` — block usage map

[Source](../../../../../tests/unit/session_file_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `0bd290a141874bb2d0b0957f333d55020dec923f8b3c67384da7c4956c9d4c21`. 97 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../tests/unit/session_file_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 8–50](../../../../../tests/unit/session_file_test.cpp#L8) | Callable definition: void typed_case(bool indexed,unsigned kind,SessionState control) | calls file, typed::fixture, CompiledProgram::standalone, QuerySession::create_typed; guard check(saved.publication==recovery::PublicationState::durable && saved.manifest.committed_sequence==…; growth resize; 4 loop sites · [reviewed contract](#b0002) |
| [B0003 · 51–68](../../../../../tests/unit/session_file_test.cpp#L51) | Callable definition: void windows_and_stream(bool indexed) | calls file, window::plan, CompiledProgram::standalone, QuerySession::create_windowed; guard check(target-&gt;window_state()==expected && target-&gt;progress().sequence==5 && target-&gt;status().commit…; growth make_unique; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 69–88](../../../../../tests/unit/session_file_test.cpp#L69) | Callable definition: void rejected_files() | calls file, typed::fixture, CompiledProgram::standalone, QuerySession::create_typed; guard check(failed,"truncated checkpoint file accepted");; 2 loop sites · [reviewed contract](#b0004) |
| [B0005 · 89–89](../../../../../tests/unit/session_file_test.cpp#L89) | Closes surrounding scope/type. |  · [reviewed contract](#b0005) |
| [B0006 · 90–97](../../../../../tests/unit/session_file_test.cpp#L90) | Callable definition: int main() | calls rejected_files, typed_case, windows_and_stream, what; returns 1; 3 loop sites · [reviewed contract](#b0006) |

## B0001

[Lines 1–7](../../../../../tests/unit/session_file_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:a40a6ac2d8216029209a99ded9a7495ddf0d14147b5992ed5eb9a3d6c7699e0e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare session_file_test.cpp: include "session_file_fixture.hpp", &lt;sys/stat.h&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/session_file_test.cpp](../../../../../tests/unit/session_file_test.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 8–50](../../../../../tests/unit/session_file_test.cpp#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void typed_case(bool indexed,unsigned kind,SessionState control)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Round-trip one typed native session through durable checkpoint_file/restore_file for a selected query, backend, and control state. |
| inputs / outputs | Builds a temporary directory/session, saves and verifies durable manifest, restores with a matching CompiledProgram, then compares control/progress/rows and optionally continues updates. |
| invariants | Coverage includes six fixture query shapes and created/running/paused/stopped states; measured replacement-new fault cuts and query-cap boundary are limited to kind 1 running. |
| ownership | Directory owns path cleanup; source/target sessions own separate query accounts; Pair images and row/oracle snapshots are test-owned values. |
| failure | File publication must report durable; restored data must retain one indexed grant; each measured replacement-new bad_alloc cannot change source/file or leak descriptors/temp names. |
| cost | Four repeat saves plus finite measured replacement-new loops for one case; actual file image/native state use source/receiving account; independent DB/Row exports and read-back are separate copies. |
| Design | [tests/unit/session_file_test.cpp](../../../../../tests/unit/session_file_test.cpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0003

[Lines 51–68](../../../../../tests/unit/session_file_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void windows_and_stream(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Round-trip window files and continue a caller-owned CSV stream from its next unread byte. |
| inputs / outputs | For both FIFO policies saves/destroys/restores a seeded window session, then saves a paused semicolon CSV self-join and restores with the caller's tail stream. |
| invariants | The window checkpoint keeps five command positions separate from two physical commits; CSV continuation starts after the first line already consumed and retains original source/configuration. |
| ownership | Source is destroyed before the window restore; the CSV continuation stream is supplied by caller; restored session owns its query account and file descriptor only for load. |
| failure | Wrong window counters/expiration, missing continuation, or incorrect next CSV projection/source state fails. |
| cost | Two FIFO cases and one two-record stream; native file buffers and rebuilt query state are account-funded; fixture stream/rows are ordinary caller-owned memory. |
| Design | [tests/unit/session_file_test.cpp](../../../../../tests/unit/session_file_test.cpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0004

[Lines 69–88](../../../../../tests/unit/session_file_test.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void rejected_files()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject malformed, truncated, symlink, special-file, and invalid-path checkpoint operations while retaining the prior artifact. |
| inputs / outputs | Saves a valid state, overwrites it with three truncations or a checksum flip, tests leaf symlink/FIFO loading and four invalid save paths. |
| invariants | No rejected operation may replace the prior complete checkpoint or leave a private temporary; FIFO open must not block and leaf links are not followed. |
| ownership | Directory owns the temporary namespace and path strings; source session owns the old valid image state. |
| failure | FileFailure or ImageFailure is required for each invalid input; accepting any path/object/corrupt image or changing the original artifact fails. |
| cost | Seven malformed-file loads, four invalid paths, one symlink and one FIFO; I/O/file buffers belong to API, expected artifact content is a bounded ordinary string copy. |
| Design | [tests/unit/session_file_test.cpp](../../../../../tests/unit/session_file_test.cpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0005

[Lines 89–89](../../../../../tests/unit/session_file_test.cpp#L89); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L89-L89:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in session_file_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/session_file_test.cpp](../../../../../tests/unit/session_file_test.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 90–97](../../../../../tests/unit/session_file_test.cpp#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run typed session file cases across both backends and run separate window/CSV continuation cases. |
| inputs / outputs | First tests public file rejection once, then loops six query kinds × four controls × two backends; calls window_and_stream once per backend. |
| invariants | This is user-facing durable checkpoint API coverage, separate from direct syscall-fault instrumentation and journal recovery. |
| ownership | Main itself owns no session; each callee's lexical Directory, source/target, and file close before return. |
| failure | Any case failure reaches the top-level handler and returns nonzero. |
| cost | 48 typed combinations plus two combined window/stream cases and one rejection suite; allocation fault loops are intentionally concentrated to one state/query to bound runtime. |
| Design | [tests/unit/session_file_test.cpp](../../../../../tests/unit/session_file_test.cpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |
