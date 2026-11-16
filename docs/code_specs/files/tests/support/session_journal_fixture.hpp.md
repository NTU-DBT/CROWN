# `tests/support/session_journal_fixture.hpp` — block usage map

[Source](../../../../../tests/support/session_journal_fixture.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `9d4dc91b4778de13dfdda3dbd6e2f0bc0812ecf4390415ee4657fecd6ec157c2`. 41 lines partitioned into 7 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../tests/support/session_journal_fixture.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 13–16](../../../../../tests/support/session_journal_fixture.hpp#L13) | Callable definition: inline runtime::SessionJournalOptions options() | calls std::copy, begin, end; returns result · [reviewed contract](#b0002) |
| [B0003 · 17–17](../../../../../tests/support/session_journal_fixture.hpp#L17) | Explanatory comments or spacing. | source comment (unverified): // Trusted complete fixture frames only; views borrow bytes and do not validate checksums. · [reviewed contract](#b0003) |
| [B0004 · 18–26](../../../../../tests/support/session_journal_fixture.hpp#L18) | Callable definition: inline std::vector&lt;std::string_view&gt; frames(const std::string& bytes) | calls size, check, std::uint64_t, emplace_back; guard check(bytes.size()-offset&gt;=jp::frame_header_size,"truncated test log frame");std::uint64_t size=0;; returns result; growth emplace_back; 2 loop sites; source comment (unverified): // Trusted complete fixture frames only; views borrow bytes and do not validate checksums. · [reviewed contract](#b0004) |
| [B0005 · 27–27](../../../../../tests/support/session_journal_fixture.hpp#L27) | Callable definition: inline runtime::SessionOptions session_options(unsigned kind) | calls ; returns result · [reviewed contract](#b0005) |
| [B0006 · 28–40](../../../../../tests/support/session_journal_fixture.hpp#L28) | Type/record definition: struct Fixture | guard void prepare() {check(session-&gt;begin_next(),"journal fixture missing head");while(session-&gt;step()!=…; 1 loop sites; source comment (unverified): // Intentionally leaves the actual epoch prepared, without committing. · [reviewed contract](#b0006) |
| [B0007 · 41–41](../../../../../tests/support/session_journal_fixture.hpp#L41) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::session_journal_test · [reviewed contract](#b0007) |

## B0001

[Lines 1–12](../../../../../tests/support/session_journal_fixture.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L12:sha256:0acead2b0b84c7028a43b624399bd1159248114e08a9c40c5d17ac9094872e28
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare session_journal_fixture.hpp: include "crown/runtime/session_journal.hpp", "session_file_fixture.hpp", "crown/ir/digest.hpp"; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/session_journal_fixture.hpp](../../../../../tests/support/session_journal_fixture.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 13–16](../../../../../tests/support/session_journal_fixture.hpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline runtime::SessionJournalOptions options(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create deterministic journal query identity for test files. |
| inputs / outputs | Copies 32 literal ASCII hex bytes into query_id and leaves other option defaults. |
| invariants | ID is fixed test binding metadata, not random entropy or authorization; actual checkpoint/journal admission checks it. |
| ownership | Returns owning fixed-array/options value with no borrowed literal retained. |
| failure | No explicit failure path in fixed scalar copy; downstream admission may reject incompatible files. |
| cost | Fixed 32-byte copy and default option construction. |
| Design | [tests/support/session_journal_fixture.hpp](../../../../../tests/support/session_journal_fixture.hpp), [tests/unit/session_journal_test.cpp](../../../../../tests/unit/session_journal_test.cpp), [tests/unit/session_journal_fault_test.cpp](../../../../../tests/unit/session_journal_fault_test.cpp), [include/crown/runtime/session_journal.hpp](../../../../../include/crown/runtime/session_journal.hpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 17–17](../../../../../tests/support/session_journal_fixture.hpp#L17); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L17:sha256:0e7755a9dc1d89f72a9cc29046665219a96d2e147b9f9d97d48c2946b8be0f85
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Trusted complete fixture frames only; views borrow bytes and do not validate checksums. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/session_journal_fixture.hpp](../../../../../tests/support/session_journal_fixture.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 18–26](../../../../../tests/support/session_journal_fixture.hpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::vector<std::string_view> frames(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Split already valid fixture logs into borrowed frames for deterministic cutting/tampering. |
| inputs / outputs | Reads little-endian uint64 body length at offset12, adds frame_header_size, checks remaining length and appends a view. |
| invariants | Trusted complete fixture input is required: no type/checksum/sequence validation and header addition is not protected against arbitrary malformed uint64 overflow. Callers inspect real codec validity elsewhere. |
| ownership | Views borrow the input string and become invalid on its destruction/reallocation; vector owns only views. |
| failure | Short header/body assertions or vector allocation propagate; this is not an untrusted wire parser or bounded hostile-input loop. |
| cost | O(frame count) fixed length reads plus view-vector growth; no frame-byte copy or hash scan. |
| Design | [tests/support/session_journal_fixture.hpp](../../../../../tests/support/session_journal_fixture.hpp), [tests/unit/session_journal_test.cpp](../../../../../tests/unit/session_journal_test.cpp), [tests/unit/session_journal_fault_test.cpp](../../../../../tests/unit/session_journal_fault_test.cpp), [include/crown/runtime/session_journal.hpp](../../../../../include/crown/runtime/session_journal.hpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 27–27](../../../../../tests/support/session_journal_fixture.hpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline runtime::SessionOptions session_options(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose journal fixture delivery mode. |
| inputs / outputs | Kind2 selects maintenance; all other trusted fixture kinds keep default delta options. |
| invariants | This does not choose plan shape or validate kind; typed::fixture supplies matching scenario. |
| ownership | Returns owning scalar/options DTO; any default owning members follow their real types. |
| failure | No explicit rejection here; invalid overall configuration is rejected by session admission. |
| cost | Fixed option setup; real native admission occurs later. |
| Design | [tests/support/session_journal_fixture.hpp](../../../../../tests/support/session_journal_fixture.hpp), [tests/unit/session_journal_test.cpp](../../../../../tests/unit/session_journal_test.cpp), [tests/unit/session_journal_fault_test.cpp](../../../../../tests/unit/session_journal_fault_test.cpp), [include/crown/runtime/session_journal.hpp](../../../../../include/crown/runtime/session_journal.hpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 28–40](../../../../../tests/support/session_journal_fixture.hpp#L28); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fixture
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a typed live session with a real base checkpoint and enabled journal. |
| inputs / outputs | Directory, typed Case, move-only Session Owner and owning checkpoint/log paths retain all recovery inputs. |
| invariants | Constructor checkpoints a started empty source before enabling journal. Holding editable paths or Case does not substitute for checkpoint/journal validation. |
| ownership | Member destruction closes session before Directory removes files. Case rows/paths are ordinary owners; native session owns separate admitted data. |
| failure | Constructor/filesystem/native admission failures propagate with normal member unwinding; no all-files rollback guarantee. |
| cost | Real lowering/session setup, checkpoint image/file publication and journal setup, plus ordinary fixture path/data copies. |
| Design | [tests/support/session_journal_fixture.hpp](../../../../../tests/support/session_journal_fixture.hpp), [tests/unit/session_journal_test.cpp](../../../../../tests/unit/session_journal_test.cpp), [tests/unit/session_journal_fault_test.cpp](../../../../../tests/unit/session_journal_fault_test.cpp), [include/crown/runtime/session_journal.hpp](../../../../../include/crown/runtime/session_journal.hpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

```text
explicit Fixture(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish an initial typed checkpoint and enable its matching journal. |
| inputs / outputs | Creates typed plan/session with session_options(kind), starts, checkpoint_file then enable_journal(base,log,options). |
| invariants | Checkpoint file publication and journal binding are actual native APIs; fixture constructor is not a fake receipt builder. |
| ownership | Owns source session and file paths in lexical Directory. |
| failure | Any step can fail after earlier real file publication; Directory cleanup is separate best effort. |
| cost | Compiler/session admission plus full initial checkpoint serialization/I/O and journal creation/sync paths. |
| Design | [tests/support/session_journal_fixture.hpp](../../../../../tests/support/session_journal_fixture.hpp), [tests/unit/session_journal_test.cpp](../../../../../tests/unit/session_journal_test.cpp), [tests/unit/session_journal_fault_test.cpp](../../../../../tests/unit/session_journal_fault_test.cpp), [include/crown/runtime/session_journal.hpp](../../../../../include/crown/runtime/session_journal.hpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

```text
void offer(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Queue one trusted trace update without executing it. |
| inputs / outputs | Uses updates\[index\] with source test offset100+index and typed::enqueue. |
| invariants | Caller supplies index within the four-update fixture; source validation occurs in session queue admission. |
| ownership | Copies ordinary event into batch then actual session ownership; no retained reference to vector row. |
| failure | Invalid caller index is outside contract; admission/copy/assertion failures propagate. |
| cost | Event/Row/source copy plus actual queue validation/allocation; no epoch commit yet. |
| Design | [tests/support/session_journal_fixture.hpp](../../../../../tests/support/session_journal_fixture.hpp), [tests/unit/session_journal_test.cpp](../../../../../tests/unit/session_journal_test.cpp), [tests/unit/session_journal_fault_test.cpp](../../../../../tests/unit/session_journal_fault_test.cpp), [include/crown/runtime/session_journal.hpp](../../../../../include/crown/runtime/session_journal.hpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

```text
void prepare()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance the queued journal epoch to prepared without committing. |
| inputs / outputs | Requires begin_next then steps until DeltaStep::prepared. |
| invariants | Intentionally leaves pending prepared state for precommit/fault tests; no output drain or commit. |
| ownership | Borrows session already owned by Fixture; pending native state stays with it. |
| failure | Native begin/step failures or assertion propagate; no separate time/step limit. |
| cost | All admitted engine preparation work; not a fixed-cost metadata toggle. |
| Design | [tests/support/session_journal_fixture.hpp](../../../../../tests/support/session_journal_fixture.hpp), [tests/unit/session_journal_test.cpp](../../../../../tests/unit/session_journal_test.cpp), [tests/unit/session_journal_fault_test.cpp](../../../../../tests/unit/session_journal_fault_test.cpp), [include/crown/runtime/session_journal.hpp](../../../../../include/crown/runtime/session_journal.hpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 41–41](../../../../../tests/support/session_journal_fixture.hpp#L41); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L41:sha256:e90fd30555149e86427d1cfec196549b7c64c60382eacd4aae977df6451d463f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in session_journal_fixture.hpp: namespace crown::session_journal_test. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/session_journal_fixture.hpp](../../../../../tests/support/session_journal_fixture.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |
