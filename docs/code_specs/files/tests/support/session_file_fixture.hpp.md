# `tests/support/session_file_fixture.hpp` — block usage map

[Source](../../../../../tests/support/session_file_fixture.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `eda6323595b18a2eed3e1a3892e103a3a939ba0aaefb3e5c5445b6f9803a9a95`. 54 lines partitioned into 9 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../tests/support/session_file_fixture.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Uncopied lexical test owner; recursive cleanup is best effort, not an OOM guarantee. · [reviewed contract](#b0001) |
| [B0002 · 16–25](../../../../../tests/support/session_file_fixture.hpp#L16) | Type/record definition: struct Directory | guard check(path!=nullptr,"temporary checkpoint directory creation failed");name=path;; returns name+@ +std::string(leaf); source comment (unverified): // Uncopied lexical test owner; recursive cleanup is best effort, not an OOM guarantee. · [reviewed contract](#b0002) |
| [B0003 · 26–28](../../../../../tests/support/session_file_fixture.hpp#L26) | Callable definition: inline std::string contents(const std::string& path) | calls input; returns {std::istreambuf_iterator&lt;char&gt;(input),std::istreambuf_iterator&lt;char&gt;()} · [reviewed contract](#b0003) |
| [B0004 · 29–31](../../../../../tests/support/session_file_fixture.hpp#L29) | Callable definition: inline std::size_t descriptors() | calls std::filesystem::directory_iterator; returns count; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 32–36](../../../../../tests/support/session_file_fixture.hpp#L32) | Callable definition: inline std::size_t temporaries(const Directory& directory) | calls std::filesystem::directory_iterator, path, filename, native; returns count; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 37–40](../../../../../tests/support/session_file_fixture.hpp#L37) | Callable definition: inline void remove_temporaries(const Directory& directory) | calls std::filesystem::directory_iterator, path, filename, native; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 41–41](../../../../../tests/support/session_file_fixture.hpp#L41) | Explanatory comments or spacing. | source comment (unverified): // Images own funded byte vectors; copying images can allocate and duplicate bytes. · [reviewed contract](#b0007) |
| [B0008 · 42–53](../../../../../tests/support/session_file_fixture.hpp#L42) | Type/record definition: struct Pair | growth resize; source comment (unverified): // Images own funded byte vectors; copying images can allocate and duplicate bytes. · [reviewed contract](#b0008) |
| [B0009 · 54–54](../../../../../tests/support/session_file_fixture.hpp#L54) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::session_file_test · [reviewed contract](#b0009) |

## B0001

[Lines 1–15](../../../../../tests/support/session_file_fixture.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:4bdccc5058968f3b466b6e8d53963edc1466f5275d6f74e85e295c0368a19ed8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare session_file_fixture.hpp: include "crown/recovery/session_file.hpp", "session_checkpoint_test_fixture.hpp", "window_checkpoint_test_fixture.hpp", &lt;array&gt;, &lt;filesystem&gt;, &lt;fstream&gt;, &lt;unistd.h&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 16–25](../../../../../tests/support/session_file_fixture.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Directory
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a temporary test-directory pathname and schedule best-effort recursive cleanup. |
| inputs / outputs | Constructor calls mkdtemp with a mutable template, checks success, then copies the returned path; file builds owning child path strings. |
| invariants | Actual callers use an uncopied lexical Directory. Implicit copy duplicates the path/cleanup responsibility; the user destructor suppresses implicit move. This is test setup, not a durable directory owner protocol. |
| ownership | String owns pathname only, not an open descriptor. Destructor removes filesystem entries; sessions in enclosing fixtures die before the Directory. |
| failure | mkdtemp/check or subsequent string allocation can fail; allocation after creation can leave a directory. remove_all(error_code) ignores filesystem error reporting but is not an allocation-free/no-terminate OOM guarantee. |
| cost | One real directory creation, pathname copy, and teardown proportional to remaining directory contents; ordinary filesystem/string allocations lie outside native query-account accounting. |
| Design | [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [tests/unit/session_file_test.cpp](../../../../../tests/unit/session_file_test.cpp), [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

```text
Directory() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the fixture's unique filesystem directory. |
| inputs / outputs | Passes a writable XXXXXX template to mkdtemp; copies the resulting path after a non-null check. |
| invariants | Template buffer remains live for the synchronous call and has a terminating NUL; no user pathname is interpreted. |
| ownership | On success the Directory string retains the path. Raw created directory precedes string ownership and is not guarded during failed string assignment. |
| failure | OS failure is asserted with runtime_error; ordinary allocation may throw after mkdir succeeded. Current callers create fixtures before injected failures. |
| cost | Fixed template preparation, one mkdtemp operation, and one ordinary pathname copy/allocation. |
| Design | [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [tests/unit/session_file_test.cpp](../../../../../tests/unit/session_file_test.cpp), [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

```text
~Directory()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attempt to remove this test directory and its remaining files on scope exit. |
| inputs / outputs | Calls filesystem::remove_all(name,error_code) and ignores the returned count and error code. |
| invariants | Use one uncopied lexical instance; copies would attempt cleanup of the same path. This is cleanup convenience rather than a durability or descriptor-release assertion. |
| ownership | Destroys filesystem entries named by an owned string; does not close arbitrary session descriptors itself. |
| failure | Reported filesystem errors are deliberately ignored. The destructor is implicitly noexcept, and general allocation failure is not guaranteed impossible by error_code. |
| cost | Filesystem traversal/deletion proportional to remaining entries; library/path allocation may occur. |
| Design | [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [tests/unit/session_file_test.cpp](../../../../../tests/unit/session_file_test.cpp), [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

```text
std::string file(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an owning path beneath the temporary directory for trusted test leaf names. |
| inputs / outputs | Concatenates name, slash and leaf; default is state.crown. |
| invariants | Trusted leaf is not sanitized against slashes or traversal; this is not an untrusted path admission function. |
| ownership | Return owns independent ordinary string bytes; leaf/name are not retained as views. |
| failure | String/length allocation failures propagate; no filesystem operation is attempted. |
| cost | O(directory path + leaf bytes) copying and possible ordinary allocation. |
| Design | [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [tests/unit/session_file_test.cpp](../../../../../tests/unit/session_file_test.cpp), [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 26–28](../../../../../tests/support/session_file_fixture.hpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::string contents(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read fixture file contents into an ordinary owning byte string. |
| inputs / outputs | Opens binary ifstream and constructs string from streambuf iterators. |
| invariants | Default stream state is not checked here: unreadable input may yield empty/partial text. Callers must assert/inspect resulting content; this is not the checked production reader. |
| ownership | Local stream closes on exit; returned string owns bytes after the file/stream disappear. |
| failure | Ordinary allocations and exceptional stream/library failures propagate; default failbit/badbit alone are not translated. |
| cost | Real file read plus O(bytes) string construction/growth, with no native MemoryAccount or durable snapshot guarantee. |
| Design | [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [tests/unit/session_file_test.cpp](../../../../../tests/unit/session_file_test.cpp), [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 29–31](../../../../../tests/support/session_file_fixture.hpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::size_t descriptors()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe a Linux process descriptor count for relative leak assertions. |
| inputs / outputs | Iterates /proc/self/fd and returns number of entries observed. |
| invariants | Includes iterator's own descriptor and concurrent process changes; relative tests control their environment. This is not a native account or whole-process resource proof. |
| ownership | Iterator/path objects are local and owned; return is a scalar count. |
| failure | Filesystem iteration/open/allocation errors propagate; counter has no saturation guard for arbitrary unbounded input. |
| cost | O(open descriptors) directory traversal with actual filesystem/library allocation work. |
| Design | [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [tests/unit/session_file_test.cpp](../../../../../tests/unit/session_file_test.cpp), [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 32–36](../../../../../tests/support/session_file_fixture.hpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::size_t temporaries(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count the owner-specific temporary filename prefix in the test directory. |
| inputs / outputs | Scans entries whose filename begins .crown-checkpoint-. |
| invariants | Matches only this prefix, not all temporary files or every leaked resource; caller supplies the live Directory. |
| ownership | Borrows Directory during scan and returns numeric count; iteration paths are transient owned objects. |
| failure | Filesystem/path allocation errors propagate; no cleanup or recovery is attempted. |
| cost | O(entries and inspected filename bytes) filesystem scan; not query operation/byte accounting. |
| Design | [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [tests/unit/session_file_test.cpp](../../../../../tests/unit/session_file_test.cpp), [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 37–40](../../../../../tests/support/session_file_fixture.hpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void remove_temporaries(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove only checkpoint-owner temporary files during test recovery setup. |
| inputs / outputs | Scans live Directory and deletes filenames beginning .crown-checkpoint-. |
| invariants | Deliberately mutates real fixture filesystem; does not remove journals, selected checkpoints or other prefixes and supplies no durable cleanup protocol. |
| ownership | Borrows Directory; iterator owns transient path/descriptor resources. |
| failure | Filesystem/path allocation/deletion errors propagate after any earlier deletions; no rollback. |
| cost | O(directory entries and matching file deletion) real I/O plus ordinary path allocation. |
| Design | [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [tests/unit/session_file_test.cpp](../../../../../tests/unit/session_file_test.cpp), [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 41–41](../../../../../tests/support/session_file_fixture.hpp#L41); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L41:sha256:220eddda6a873411f4f164972416624581cd88304200fa35fefa5961ebe488be
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Images own funded byte vectors; copying images can allocate and duplicate bytes. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 42–53](../../../../../tests/support/session_file_fixture.hpp#L42); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Pair
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one source session and two account-funded checkpoint images at different epochs. |
| inputs / outputs | Builds kind1 self-join, standalone compiler and typed session; applies first update/captures old image, then second/captures new. |
| invariants | Standalone program has a separate admission account from session. Images contain owning funded bytes; manifest metadata alone is not runtime or durable publication authority. |
| ownership | Session Owner is move-only. Program copies share immutable control; Database deep-copies; SessionImage byte-vector copy can allocate and duplicate funded bytes, while moves follow allocator/account rules. |
| failure | Construction/capture/export/assertion failures unwind completed members; Directory survives until session/image members die. |
| cost | Real lowering/two native commits plus independent oracle checks and two complete session image captures/checksums; images remain retained simultaneously. |
| Design | [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [tests/unit/session_file_test.cpp](../../../../../tests/unit/session_file_test.cpp), [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

```text
explicit Pair(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create old/new checkpoint states from two committed self-join events. |
| inputs / outputs | Sizes one source table, starts native session, invokes typed::step twice around checkpoint_image captures. |
| invariants | First edge alone and second joining edge produce distinct state images; capture is native, not reconstruction from editable manifest fields. |
| ownership | Owns source and both image buffers; standalone compiler is retained for separate restore admission. |
| failure | Any failure aborts fixture construction; no transactional filesystem promise or source/model rollback is supplied. |
| cost | Compiler setup, full snapshot/oracle exports for two updates and two image allocations/serialized passes. |
| Design | [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [tests/unit/session_file_test.cpp](../../../../../tests/unit/session_file_test.cpp), [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 54–54](../../../../../tests/support/session_file_fixture.hpp#L54); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L54-L54:sha256:98a01e8bf46dc6bc28095169db0c32790105070443a347c6bb974144db9d9cc9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in session_file_fixture.hpp: namespace crown::session_file_test. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |
