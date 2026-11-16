# `tests/support/history_retirement_fixture.hpp` — block usage map

[Source](../../../../../tests/support/history_retirement_fixture.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `2155328bffe98c4ac668420c6fc0bcfab5fffd290aa4f34688d2370433d44606`. 42 lines partitioned into 13 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../tests/support/history_retirement_fixture.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body. |  · [reviewed contract](#b0001) |
| [B0002 · 14–20](../../../../../tests/support/history_retirement_fixture.hpp#L14) | Callable definition: explicit RetirementFixture(bool indexed=false,unsigned kind=1):test(typed::fixture(indexed,kind)),program(runtime::CompiledProgra… | calls test, typed::fixture, program, runtime::CompiledProgram::standalone; growth resize; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 21–21](../../../../../tests/support/history_retirement_fixture.hpp#L21) | Callable definition: void commit(std::size_t index) | calls typed::enqueue, check, begin_next, finish; guard void commit(std::size_t index){typed::enqueue(*session,io::InputEvent{test.updates\[index\],io::Sourc… · [reviewed contract](#b0003) |
| [B0004 · 22–22](../../../../../tests/support/history_retirement_fixture.hpp#L22) | Callable definition: runtime::QuerySession::Owner restore(const runtime::SessionGenerationRecoveryOptions& recovery=generation_test::recovery_options(… | calls generation_test::recovery_options, runtime::QuerySession::restore_generation_with_local_sink, options; returns runtime::QuerySession::restore_generation_with_local_sink(program,root,recovery,sink,options()) · [reviewed contract](#b0004) |
| [B0005 · 23–23](../../../../../tests/support/history_retirement_fixture.hpp#L23) | Callable definition: std::string path(std::uint64_t generation,std::string_view suffix) const | calls generation_test::path; returns generation_test::path(root,generation,suffix) · [reviewed contract](#b0005) |
| [B0006 · 24–27](../../../../../tests/support/history_retirement_fixture.hpp#L24) | Callable definition: void history(bool retained) const | calls check, std::filesystem::exists, path; guard for(std::uint64_t generation=1;generation&lt;3;++generation)for(const auto suffix:{".ckpt",".wal"})che…; 2 loop sites · [reviewed contract](#b0006) |
| [B0007 · 28–34](../../../../../tests/support/history_retirement_fixture.hpp#L28) | Callable definition: void verify() | calls reset, restore, check, status; guard session.reset();auto value=restore();check(value-&gt;status().committed_sequence==3 && value-&gt;progress…; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 35–35](../../../../../tests/support/history_retirement_fixture.hpp#L35) | Closes surrounding scope/type. |  · [reviewed contract](#b0008) |
| [B0009 · 36–36](../../../../../tests/support/history_retirement_fixture.hpp#L36) | Callable definition: inline std::string wire(const recovery::detail::RetirementIntent& intent) | calls recovery::detail::encode_retirement_intent, data, size; returns {bytes.data(),bytes.size()} · [reviewed contract](#b0009) |
| [B0010 · 37–39](../../../../../tests/support/history_retirement_fixture.hpp#L37) | Callable definition: inline recovery::detail::RetirementIntent intent(const RetirementFixture& fixture) | calls local_sink_state, generation_state; returns {fixture.session-&gt;generation_state().selected,sink.persisted.header,sink.persisted.generation,sink.… · [reviewed contract](#b0010) |
| [B0011 · 40–40](../../../../../tests/support/history_retirement_fixture.hpp#L40) | Explanatory comments or spacing. | source comment (unverified): // Requires a complete encoded intent; recomputed integrity does not grant authority. · [reviewed contract](#b0011) |
| [B0012 · 41–41](../../../../../tests/support/history_retirement_fixture.hpp#L41) | Callable definition: inline void checksum(std::string& bytes) | calls sha256_fixed, std::string_view, substr, size; source comment (unverified): // Requires a complete encoded intent; recomputed integrity does not grant authority. · [reviewed contract](#b0012) |
| [B0013 · 42–42](../../../../../tests/support/history_retirement_fixture.hpp#L42) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::history_retirement_test · [reviewed contract](#b0013) |

## B0001

[Lines 1–13](../../../../../tests/support/history_retirement_fixture.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct RetirementFixture
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own three real retained generations and local delivery history with an independent ordinary model. |
| inputs / outputs | Directory, typed case, standalone compiler, live move-only session, root/sink paths, Database and three expected signed sets. |
| invariants | Three generation pairs exist, selected generation3 retains first_generation1 until retirement; ordinary expected data is not a retirement receipt capability. |
| ownership | Session descriptors die before Directory cleanup. Compiler has separate account/control; Rows/strings/expected sets deep-own ordinary bytes. |
| failure | Constructor and later methods propagate real native/filesystem/allocation errors without fixture-wide rollback. |
| cost | Three commits/deliveries and two rotations plus independent oracle scans and real file history retention. |
| Design | [tests/support/history_retirement_fixture.hpp](../../../../../tests/support/history_retirement_fixture.hpp), [tests/unit/history_retirement_test.cpp](../../../../../tests/unit/history_retirement_test.cpp), [tests/unit/history_retirement_fault_test.cpp](../../../../../tests/unit/history_retirement_fault_test.cpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/history-retirement.md](../../../../history-retirement.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 14–20](../../../../../tests/support/history_retirement_fixture.hpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit RetirementFixture(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a source with three retained generation pairs and delivered epochs. |
| inputs / outputs | Sets retained_generations3, enables generation/sink, independently computes deltas, commits/delivers each first-three update and rotates after first two. |
| invariants | Kind2 uses maintenance silence; rotations are real native operations, not filename-only fixture fabrication. |
| ownership | All native owners remain held for later fault/retirement tests; ordinary model/expected rows own independent copies. |
| failure | Failure may leave earlier generations/output until Directory cleanup; input/oracle assertion failures do not undo prior commits. |
| cost | Full source setup, three independent query recomputations/transitions, actual delivery and two checkpoint/journal rotations. |
| Design | [tests/support/history_retirement_fixture.hpp](../../../../../tests/support/history_retirement_fixture.hpp), [tests/unit/history_retirement_test.cpp](../../../../../tests/unit/history_retirement_test.cpp), [tests/unit/history_retirement_fault_test.cpp](../../../../../tests/unit/history_retirement_fault_test.cpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/history-retirement.md](../../../../history-retirement.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 21–21](../../../../../tests/support/history_retirement_fixture.hpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void commit(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit one trusted trace input into the current generation/outbox. |
| inputs / outputs | Enqueues feed sequence*10, requires begin_next then local_sink_test::finish. |
| invariants | Does not deliver or update the independent Database; constructor/caller does those explicitly. |
| ownership | Session retains actual state/outbox; update row/source copied during admission. |
| failure | Native/allocation/assertion failures propagate after any admitted work. |
| cost | Real queue/epoch commit/persistence costs; no standalone oracle/delivery work. |
| Design | [tests/support/history_retirement_fixture.hpp](../../../../../tests/support/history_retirement_fixture.hpp), [tests/unit/history_retirement_test.cpp](../../../../../tests/unit/history_retirement_test.cpp), [tests/unit/history_retirement_fault_test.cpp](../../../../../tests/unit/history_retirement_fault_test.cpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/history-retirement.md](../../../../history-retirement.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 22–22](../../../../../tests/support/history_retirement_fixture.hpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
runtime::QuerySession::Owner restore(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore selected native generation together with its actual local sink. |
| inputs / outputs | Calls restore_generation_with_local_sink(program,root,recovery,sink,options). |
| invariants | Inspected DTO fields alone do not authorize retirement; actual validated file/receipt state controls the API. |
| ownership | Returns independent move-only native Owner; standalone compiler persists in this fixture. |
| failure | All native file/binding/replay/grant failures propagate. |
| cost | Full root/sink inspection, restore/replay/rebuild and filesystem acquisition, not a fixed metadata copy. |
| Design | [tests/support/history_retirement_fixture.hpp](../../../../../tests/support/history_retirement_fixture.hpp), [tests/unit/history_retirement_test.cpp](../../../../../tests/unit/history_retirement_test.cpp), [tests/unit/history_retirement_fault_test.cpp](../../../../../tests/unit/history_retirement_fault_test.cpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/history-retirement.md](../../../../history-retirement.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 23–23](../../../../../tests/support/history_retirement_fixture.hpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string path(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Produce a component pathname for fixture assertions. |
| inputs / outputs | Delegates root,generation,suffix to generation_test::path. |
| invariants | Trusted generation/suffix formatting only; no filesystem existence or authority check. |
| ownership | Returns owning ordinary string. |
| failure | Formatting/allocation errors propagate. |
| cost | O(root+suffix bytes) stream/string formatting and copy. |
| Design | [tests/support/history_retirement_fixture.hpp](../../../../../tests/support/history_retirement_fixture.hpp), [tests/unit/history_retirement_test.cpp](../../../../../tests/unit/history_retirement_test.cpp), [tests/unit/history_retirement_fault_test.cpp](../../../../../tests/unit/history_retirement_fault_test.cpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/history-retirement.md](../../../../history-retirement.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 24–27](../../../../../tests/support/history_retirement_fixture.hpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void history(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check only the expected retained/deleted generation file range. |
| inputs / outputs | Asserts generations1/2 .ckpt/.wal existence equals retained and selected generation3 pair still exists. |
| invariants | Existence checks are test observations, not validation of file contents/durability or a locking protocol. |
| ownership | Borrows owned root; temporary path strings/FS observations do not retain files. |
| failure | Filesystem/path allocation/assertion errors propagate; no cleanup performed here. |
| cost | Six pathname constructions/existence checks with real filesystem work. |
| Design | [tests/support/history_retirement_fixture.hpp](../../../../../tests/support/history_retirement_fixture.hpp), [tests/unit/history_retirement_test.cpp](../../../../../tests/unit/history_retirement_test.cpp), [tests/unit/history_retirement_fault_test.cpp](../../../../../tests/unit/history_retirement_fault_test.cpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/history-retirement.md](../../../../history-retirement.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 28–34](../../../../../tests/support/history_retirement_fixture.hpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise real history retirement and continued processing after restart. |
| inputs / outputs | Closes source, restores state/receipt3, retires history, checks old pairs gone/selected intact/intent cleared, compares three epochs, then commits/delivers fourth update. |
| invariants | Checks selected.first_generation3 and !retirement_pending after actual API; wire edits or checksum recomputation alone cannot establish those states. |
| ownership | Local restored Owner and independent next Database own data; no borrowing across destroyed source session. |
| failure | Each stage may persist before a later assertion/allocation failure; no broad recovery catch. |
| cost | Complete restore/retire filesystem work, history scans, epoch reads and native update plus independent oracle export. |
| Design | [tests/support/history_retirement_fixture.hpp](../../../../../tests/support/history_retirement_fixture.hpp), [tests/unit/history_retirement_test.cpp](../../../../../tests/unit/history_retirement_test.cpp), [tests/unit/history_retirement_fault_test.cpp](../../../../../tests/unit/history_retirement_fault_test.cpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/history-retirement.md](../../../../history-retirement.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 35–35](../../../../../tests/support/history_retirement_fixture.hpp#L35); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L35:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in history_retirement_fixture.hpp: struct RetirementFixture. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/history_retirement_fixture.hpp](../../../../../tests/support/history_retirement_fixture.hpp), [docs/history-retirement.md](../../../../history-retirement.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 36–36](../../../../../tests/support/history_retirement_fixture.hpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::string wire(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make editable test bytes of a private retirement intent. |
| inputs / outputs | Calls encode_retirement_intent then copies its fixed byte array into std::string. |
| invariants | Serialization/integrity is not accepted retirement authority; actual session/root/sink gates must still validate. |
| ownership | Returned ordinary string owns independent bytes after local array dies. |
| failure | Ordinary string allocation can throw; native state is not changed. |
| cost | Fixed intent encoding/checksum work plus one ordinary byte copy/allocation. |
| Design | [tests/support/history_retirement_fixture.hpp](../../../../../tests/support/history_retirement_fixture.hpp), [tests/unit/history_retirement_test.cpp](../../../../../tests/unit/history_retirement_test.cpp), [tests/unit/history_retirement_fault_test.cpp](../../../../../tests/unit/history_retirement_fault_test.cpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/history-retirement.md](../../../../history-retirement.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 37–39](../../../../../tests/support/history_retirement_fixture.hpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline recovery::detail::RetirementIntent intent(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Snapshot the private selected-generation and verified delivery fields for tamper fixtures. |
| inputs / outputs | Reads live session local_sink_state and generation_state and returns selected/header/generation/verified_sequence. |
| invariants | Caller supplies initialized stable session with real sink/generation state. Returned editable DTO is not a receipt or operation authorization. |
| ownership | Fixed returned fields are owned copies; no session pointer or byte view is retained. |
| failure | Native state accessor precondition failures propagate; no locking/concurrent synchronization is introduced. |
| cost | Fixed native metadata reads/copies; not a full sink/history verification. |
| Design | [tests/support/history_retirement_fixture.hpp](../../../../../tests/support/history_retirement_fixture.hpp), [tests/unit/history_retirement_test.cpp](../../../../../tests/unit/history_retirement_test.cpp), [tests/unit/history_retirement_fault_test.cpp](../../../../../tests/unit/history_retirement_fault_test.cpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/history-retirement.md](../../../../history-retirement.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 40–40](../../../../../tests/support/history_retirement_fixture.hpp#L40); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L40-L40:sha256:835ebc552350abcb9eb43f06a20b21686f353c4ea3c5b3d6370bf1a545bd58a6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Requires a complete encoded intent; recomputed integrity does not grant authority. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/history_retirement_fixture.hpp](../../../../../tests/support/history_retirement_fixture.hpp), [docs/history-retirement.md](../../../../history-retirement.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 41–41](../../../../../tests/support/history_retirement_fixture.hpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void checksum(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute the final64 digest bytes after a trusted full intent fixture edit. |
| inputs / outputs | Hashes prefix bytes.size()-64 and overwrites the final64 characters. |
| invariants | Requires a complete encoded intent with at least64 bytes; no arbitrary-short input check. Correct checksum proves integrity only and does not bypass semantic/root/delivery checks. |
| ownership | Mutates caller-owned ordinary string in place without retaining its view. |
| failure | Short/wrong-sized caller input violates precondition; digest primitive supplies actual fixed-output behavior. |
| cost | O(intent body bytes) hash scan plus64-byte copy; no new native receipt/state is created. |
| Design | [tests/support/history_retirement_fixture.hpp](../../../../../tests/support/history_retirement_fixture.hpp), [tests/unit/history_retirement_test.cpp](../../../../../tests/unit/history_retirement_test.cpp), [tests/unit/history_retirement_fault_test.cpp](../../../../../tests/unit/history_retirement_fault_test.cpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/history-retirement.md](../../../../history-retirement.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 42–42](../../../../../tests/support/history_retirement_fixture.hpp#L42); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L42-L42:sha256:c7e2254bf0f36f3add98bfd3eda1f5eae04168753ae287cbf4183b0a8fc63383
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in history_retirement_fixture.hpp: namespace crown::history_retirement_test. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/history_retirement_fixture.hpp](../../../../../tests/support/history_retirement_fixture.hpp), [docs/history-retirement.md](../../../../history-retirement.md), [docs/code_review.md](../../../../code_review.md) |
