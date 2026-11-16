# `tests/unit/generation_test.cpp` — block usage map

[Source](../../../../../tests/unit/generation_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `9eab7a8d0daa4bc82b3b9c5c3584046e6ff20205a185c5691cd372f687587890`. 155 lines partitioned into 13 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../tests/unit/generation_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 8–15](../../../../../tests/unit/generation_test.cpp#L8) | Callable definition: void replay_outputs(QuerySession& session,const typed::Output& expected,std::uint64_t generation,std::uint64_t epoch) | calls next_recovered_output, check, options, emplace; guard check(item-&gt;query_id==options().journal.query_id && item-&gt;generation==generation && item-&gt;physical_…; growth emplace; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 16–18](../../../../../tests/unit/generation_test.cpp#L16) | Callable definition: void apply(Database& database,const PhysicalSetUpdate& event) | calls insert, erase; growth insert · [reviewed contract](#b0003) |
| [B0004 · 19–41](../../../../../tests/unit/generation_test.cpp#L19) | Callable definition: void typed_case(bool indexed,unsigned kind,bool pending) | calls f, options, enable_generation, resize; guard check(selected.generation==8 && selected.first_generation==7 && selected.physical_sequence==2 && se…; growth resize; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 42–54](../../../../../tests/unit/generation_test.cpp#L42) | Callable definition: std::string third_record(const session_journal_stream_test::Case& profile,const Catalog& catalog) | calls io::write_input_json, io::write_input_binary, std::runtime_error; returns io::write_input_json(io::InputEvent{{3,TableId{0},SetOperation::insert,Row{std::int64_t{3},std::int…; growth insert · [reviewed contract](#b0005) |
| [B0006 · 55–67](../../../../../tests/unit/generation_test.cpp#L55) | Callable definition: void stream_case(bool indexed,const session_journal_stream_test::Case& profile,bool pending) | calls typed::fixture, file, third_record, size; guard auto source=QuerySession::create(test.plan,std::make_unique&lt;std::istringstream&gt;(input),policy);sour…; growth insert, make_unique · [reviewed contract](#b0006) |
| [B0007 · 68–80](../../../../../tests/unit/generation_test.cpp#L68) | Callable definition: void window_case(bool indexed,WindowFifoPolicy fifo,unsigned steps) | calls window::plan, file, QuerySession::create_windowed, window::config; guard if(steps==0)check(source-&gt;begin_next(),"generation pending window missing");; 3 loop sites · [reviewed contract](#b0007) |
| [B0008 · 81–81](../../../../../tests/unit/generation_test.cpp#L81) | Callable definition: void repair_checksum(std::string& bytes) | calls sha256_fixed, std::string_view, substr, std::copy · [reviewed contract](#b0008) |
| [B0009 · 82–97](../../../../../tests/unit/generation_test.cpp#L82) | Callable definition: void corruption() | calls update, reset, contents, path; guard check(bad && contents(log)==full,"malformed generation root repaired/accepted selected log");};; 3 loop sites · [reviewed contract](#b0009) |
| [B0010 · 98–119](../../../../../tests/unit/generation_test.cpp#L98) | Callable definition: void ownership_and_limits() | calls f, options, enable_generation, update; guard check(capped && contents(f.name)==selected && !f.session-&gt;generation_state().recovery_required,"cop…; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 120–145](../../../../../tests/unit/generation_test.cpp#L120) | Callable definition: void paths_and_golden(const char* golden) | calls contents, check, push_back, recovery::inspect_generation_root; guard const int digit=c&gt;='0' && c&lt;='9'?c-'0':c&gt;='a' && c&lt;='f'?c-'a'+10:-1;check(digit&gt;=0,"invalid indepen…; growth push_back; 3 loop sites · [reviewed contract](#b0011) |
| [B0012 · 146–146](../../../../../tests/unit/generation_test.cpp#L146) | Closes surrounding scope/type. |  · [reviewed contract](#b0012) |
| [B0013 · 147–155](../../../../../tests/unit/generation_test.cpp#L147) | Callable definition: int main(int argc,char** argv) | calls check, typed_case, session_journal_stream_test::cases, stream_case; guard check(argc==2,"expected independent root golden path");; returns 1; 7 loop sites · [reviewed contract](#b0013) |

## B0001

[Lines 1–7](../../../../../tests/unit/generation_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:8046a629ac50e8073c6ff6cb8f416837dcebf345a5c842ee5727e3874c99946e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare generation_test.cpp: include "generation_fixture.hpp", "session_journal_stream_cases.hpp", "crown/api/error.hpp"; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [docs/generations.md](../../../../generations.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 8–15](../../../../../tests/unit/generation_test.cpp#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void replay_outputs(QuerySession& session
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare all reconstructed generation output with exact expected rows and identities. |
| inputs / outputs | Drains next_recovered_output into a test-owned set and checks query ID, selected generation and physical epoch on every item. |
| invariants | Duplicate operation/row pairs reject; empty expected output requires no returned item. Reading output does not itself acknowledge an external sink or retire history. |
| ownership | Each item owns its returned row while exported values enter the independent ordinary container; session owns the replay cursor. |
| failure | Wrong identity, duplicate or set mismatch throws through the fixture check; session exceptions propagate. |
| cost | Traverses all returned items and copies complete rows into an ordered test set; comparisons depend on row widths. |
| Design | [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [docs/generations.md](../../../../generations.md), [tests/support/generation_fixture.hpp](../../../../../tests/support/generation_fixture.hpp) |

## B0003

[Lines 16–18](../../../../../tests/unit/generation_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void apply(Database& database,const PhysicalSetUpdate& event)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one physical set event to the independent reference Database. |
| inputs / outputs | Indexes the fixture table by event.table, then inserts or erases its complete owning row. |
| invariants | Fixture callers supply a valid table ID; this helper models set membership and does not implement weighted replacement or native propagation. |
| ownership | Database owns its row sets and copied Value payload; event is borrowed for the call. |
| failure | Ordinary reference-container allocation failures propagate; no production error category is translated. |
| cost | One ordered-container update plus full-row comparison/copy costs. |
| Design | [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0004

[Lines 19–41](../../../../../tests/unit/generation_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void typed_case(bool indexed,unsigned kind,bool pending)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check typed native generation rotation/reopen with committed or pending next input. |
| inputs / outputs | Builds a genuine fixture, starts at generation7, commits two events, rotates to8, optionally leaves event3 pending, restores, resumes through event4 and rotates to9. |
| invariants | Selected checkpoint hash/bases and retained first generation are exact; restored source/native rows match independent set recomputation. Maintenance mode expects no delta output; pending input is retained rather than treated as a repairable suffix. |
| ownership | Drops the original session before a fresh restore acquires root/log locks. Compiler/fixture state and saved old checkpoint/log bytes outlive both sessions; historical generation7 files remain unchanged. |
| failure | Any binding/state/output/progress/history mismatch fails the fixture; production failures propagate unchanged to main. |
| cost | Several native epochs, full checkpoint/replay/rotation I/O and reference set recomputations per finite backend/query/pending case; not an update timing benchmark. |
| Design | [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [docs/generations.md](../../../../generations.md), [tests/support/session_journal_fixture.hpp](../../../../../tests/support/session_journal_fixture.hpp) |

## B0005

[Lines 42–54](../../../../../tests/unit/generation_test.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string third_record(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the third logical input record for each explicitly supported stream profile. |
| inputs / outputs | Uses production JSONL/binary serializers with the supplied catalog or fixed CSV/legacy spellings for event values3,4 and the appropriate source position. |
| invariants | The returned record matches the selected profile; this is fixture production using native codecs, not an independent wire golden. |
| ownership | Returns an owning std::string; serializers borrow catalog and temporary event values only during the call. |
| failure | Unknown InputFormat throws a test runtime_error; serializer errors propagate. |
| cost | Fixed record size except schema/serializer work; no stream reading happens here. |
| Design | [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [tests/support/session_journal_stream_cases.hpp](../../../../../tests/support/session_journal_stream_cases.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp) |

## B0006

[Lines 55–67](../../../../../tests/unit/generation_test.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void stream_case(bool indexed,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify original-stream seeking and retained input through generation recovery for every input profile. |
| inputs / outputs | Combines profile data and a third record, commits row1 then rotates, logs/optionally commits row2, restores with seek-from-origin and consumes through EOF. |
| invariants | Pending versus committed row2 gives the expected replay output; row3 is not skipped or duplicated. Final command/native progress is3 and the exact self-join result contains the two declared rows. |
| ownership | Original and restored sessions each own their own istringstream. The original session is destroyed before restore; input string and profile/catalog values remain fixture-owned. |
| failure | Missing input, wrong EOF/progress/rows or identity fails the test; real decoder/recovery errors escape to main. |
| cost | Bounded three-record stream scans/seeking plus checkpoint/replay and native/reference work for the selected profile/backend. |
| Design | [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [docs/generations.md](../../../../generations.md), [tests/support/session_journal_stream_cases.hpp](../../../../../tests/support/session_journal_stream_cases.hpp) |

## B0007

[Lines 68–80](../../../../../tests/unit/generation_test.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void window_case(bool indexed,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check generation recovery across pending and partially committed watermark substeps. |
| inputs / outputs | Adds three window events, rotates, logs watermark command4, finishes the requested0–3 substeps, restores, completes the remainder and rotates again. |
| invariants | Rotation rejects a partial watermark. Final command progress4 and physical epoch2 differ intentionally; rows are empty and selected checkpoint bases retain both frontiers. |
| ownership | Session owns window/source/journal state; the fixture plan remains alive across destruction and fresh restore. Recovered output is explicitly discarded before resuming. |
| failure | An admitted partial-command rotation or incorrect substep/progress/state fails; production errors remain intact. |
| cost | Finite window commands/substeps with checkpoint/replay I/O for each backend/FIFO/step case. This is not a watermark delay bound. |
| Design | [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [docs/generations.md](../../../../generations.md), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp) |

## B0008

[Lines 81–81](../../../../../tests/unit/generation_test.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void repair_checksum(std::string& bytes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute the fixed v1 root checksum so hostile metadata reaches semantic binding validation. |
| inputs / outputs | Hashes the first generation_root_size−64 bytes and overwrites the final64 ASCII checksum bytes in the caller string. |
| invariants | Caller supplies a complete212-byte v1 root; the helper is not a safe parser for short or other-version roots. |
| ownership | Mutates only the caller-owned fixture string and retains no view afterward. |
| failure | No validating guard or catch is added; fixture preconditions supply the complete buffer. |
| cost | One fixed148-byte hash and64-byte copy. |
| Design | [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp) |

## B0009

[Lines 82–97](../../../../../tests/unit/generation_test.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void corruption()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check hostile selected roots and binding validation before any selected-log repair. |
| inputs / outputs | For one real two-update generation, tries every root cut/bit flip, trailing byte, checksum-valid field edits and a root/checkpoint mismatch paired with a truncated WAL. |
| invariants | Rejected roots leave selected WAL bytes unchanged. The mismatch must report binding before tail repair; restoring the original root/log must still recover epoch2. |
| ownership | Releases the original session before rewriting fixture files. Saved original root/log and genuine standalone compiler remain available throughout the hostile corpus. |
| failure | Only GenerationFailure or journal codec Failure counts as expected rejection; unrelated exceptions escape. A successful hostile restore is a test failure. |
| cost | Finite212-byte root corpus with repeated file writes/admission; some controls reach actual checkpoint binding. No hardware-crash simulation occurs. |
| Design | [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp) |

## B0010

[Lines 98–119](../../../../../tests/unit/generation_test.cpp#L98); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ownership_and_limits()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check copied generation policies, retained-history caps, root locking, orphan handling and nonwrapping generation counters. |
| inputs / outputs | Mutates caller policy after enable, hits retention limits, drops/releases ownership, measures exact/one-under root work/I/O caps and constructs candidate/orphan/MAX-generation cases. |
| invariants | Preflight refusal preserves confirmed selection without poisoning it. A second writer gets busy. Rotation may clean only the next unselected candidate, keeps older pair bytes and rejects UINT64_MAX increment. |
| ownership | Each fixture owns private paths and session locks. Fixed selection reports and mutated caller policies cannot refill or replace the actual owner policy. |
| failure | Requires the specified GenerationFault for busy/limit/path-related controls; descriptor counts and durable root bytes are rechecked after failure. |
| cost | Multiple bounded rotations/restores and complete historical byte comparisons; operation/validation grants remain distinct from receiving memory and elapsed time. |
| Design | [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [docs/generations.md](../../../../generations.md) |

## B0011

[Lines 120–145](../../../../../tests/unit/generation_test.cpp#L120); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void paths_and_golden(const char* golden)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the independent v1 root golden, nofollow admission and rejection before publishing unreadable pairs. |
| inputs / outputs | Parses supplied lowercase hex with whitespace, verifies exact212-byte/hash/metadata, then tests root/lock symlinks, derived-name length, invalid checkpoint I/O policies and missing root with orphan pair files. |
| invariants | Golden identity is fixed independently of native root encoding. Symlink targets remain untouched; invalid capture policies publish neither root nor checkpoint and permit valid retry; recovery never guesses selection from orphans. |
| ownership | Owns decoded bytes and private fixture directories; root inspections return fixed metadata and never substitute for the actual generation owner. |
| failure | Malformed hex/checks fail the fixture; exact limit/path cases require GenerationFailure and propagate unrelated errors. |
| cost | One fixed golden parse/hash plus several bounded publication/recovery attempts; checksums are corruption detection, not signatures. |
| Design | [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp) |

## B0012

[Lines 146–146](../../../../../tests/unit/generation_test.cpp#L146); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L146-L146:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in generation_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [docs/generations.md](../../../../generations.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 147–155](../../../../../tests/unit/generation_test.cpp#L147); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the bounded typed/stream/window generation matrix and hostile-root/resource/path controls. |
| inputs / outputs | Requires the independent golden path; covers two backends, six query kinds, pending/committed modes, all generated stream profiles and two FIFO policies with four watermark step counts. |
| invariants | Each group supplies its own real session/fixture and independent expected state. These legacy R1 tests do not implement or certify the new R2 durable coordinator. |
| ownership | Group-local owners release locks and paths before the next case; argument bytes are borrowed for process lifetime. |
| failure | The final std::exception boundary prints what() and returns one on any failed check or production exception. |
| cost | Sequential execution of the finite cross-product and adversarial controls; no tests are executed by this documentation pass. |
| Design | [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [docs/generations.md](../../../../generations.md), [tests/support/generation_fixture.hpp](../../../../../tests/support/generation_fixture.hpp) |
