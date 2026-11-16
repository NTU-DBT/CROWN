# `tests/unit/local_sink_replay_test.cpp` — block usage map

[Source](../../../../../tests/unit/local_sink_replay_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `1426db27f98ce0c1c552694e9da85d0de8f236db87ec394069b55e06430d02e4`. 104 lines partitioned into 11 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../tests/unit/local_sink_replay_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 8–25](../../../../../tests/unit/local_sink_replay_test.cpp#L8) | Callable definition: void typed_case(bool indexed,unsigned kind,std::size_t accepted) | calls saved, prefix, contents, size; guard check(value-&gt;status().state==SessionState::paused && value-&gt;status().committed_sequence==3 && value…; 3 loop sites · [reviewed contract](#b0002) |
| [B0003 · 26–33](../../../../../tests/unit/local_sink_replay_test.cpp#L26) | Callable definition: void rotation() | calls commit, deliver_local_epoch, rotate_generation, typed::rows; guard check(value-&gt;local_sink_state().verified_sequence==3 && value-&gt;local_sink_state().persisted.header.…; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 34–45](../../../../../tests/unit/local_sink_replay_test.cpp#L34) | Callable definition: void stream_case(bool indexed,const session_journal_stream_test::Case& profile,bool pending) | calls typed::fixture, file, QuerySession::create, start; guard check(source-&gt;begin_next(),"sink-aware first stream input absent");finish(*source);static_cast&lt;void…; growth insert, make_unique · [reviewed contract](#b0004) |
| [B0005 · 46–56](../../../../../tests/unit/local_sink_replay_test.cpp#L46) | Callable definition: void window_case(bool indexed,WindowFifoPolicy fifo,unsigned steps) | calls file, window::plan, QuerySession::create_windowed, window::config; guard for(std::uint64_t i=1;i&lt;=3;++i){typed::enqueue(*source,io::WindowCommand{i,io::WindowInsert{i,Table…; 3 loop sites · [reviewed contract](#b0005) |
| [B0006 · 57–60](../../../../../tests/unit/local_sink_replay_test.cpp#L57) | Callable definition: void checksum(std::string& frame) | calls sha256_fixed, std::string_view, substr, std::copy · [reviewed contract](#b0006) |
| [B0007 · 61–65](../../../../../tests/unit/local_sink_replay_test.cpp#L61) | Callable definition: template&lt;class F&gt; void rejects_unchanged(Saved& saved,F&& run) | calls contents, descriptors, run, check; guard check(rejected && contents(saved.source.path)==sink && contents(saved.log)==wal && descriptors()==b… · [reviewed contract](#b0007) |
| [B0008 · 66–83](../../../../../tests/unit/local_sink_replay_test.cpp#L66) | Callable definition: void hostile_and_limits() | calls contents, session_journal_test::frames, generation_test::recovery_options, rejects_unchanged; guard recovery=generation_test::recovery_options();saved.prefix(2,true);auto value=saved.restore(recovery…; returns saved.restore(recovery); saved.restore(); 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 84–96](../../../../../tests/unit/local_sink_replay_test.cpp#L84) | Callable definition: void source_failure_before_repair() | calls typed::fixture, file, session_journal_stream_test::cases, QuerySession::create; guard for(unsigned i=0;i&lt;2;++i){check(source-&gt;begin_next(),"sink-aware source fixture absent");finish(*so…; growth make_unique; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 97–97](../../../../../tests/unit/local_sink_replay_test.cpp#L97) | Closes surrounding scope/type. |  · [reviewed contract](#b0010) |
| [B0011 · 98–104](../../../../../tests/unit/local_sink_replay_test.cpp#L98) | Callable definition: int main() | calls typed_case, session_journal_stream_test::cases, stream_case, window_case; returns 1; 7 loop sites · [reviewed contract](#b0011) |

## B0001

[Lines 1–7](../../../../../tests/unit/local_sink_replay_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:ef8e85d033d0ea5ee64609fd1fd349cb36eafb5850943a64e1e6634b9e7f80a7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare local_sink_replay_test.cpp: include "sink_replay_fixture.hpp", "session_journal_stream_cases.hpp", "crown/api/error.hpp"; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/local_sink_replay_test.cpp](../../../../../tests/unit/local_sink_replay_test.cpp), [docs/local-sink.md](../../../../local-sink.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 8–25](../../../../../tests/unit/local_sink_replay_test.cpp#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void typed_case(bool indexed,unsigned kind,std::size_t accepted) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconstruct the native journal together with exactly the output missing from a chosen sink prefix. |
| inputs / outputs | Indexed flag, query kind and accepted physical epoch count select Saved; replay row/byte caps are set to remaining expected output. |
| invariants | Stored epochs are verified as duplicates and absent committed epochs remain buffered; no replay publication changes sink or WAL; delivering missing epochs reaches the complete expected three-epoch sink. |
| ownership | Saved owns original sink/WAL/checkpoint; returned owner owns receiving account, locks and missing output; output values are compared through the independent typed oracle. |
| failure | Binding, cap, source, delivery or state mismatch fails; fixture verifies a subsequent update after restored delivery. |
| cost | Six query kinds times two storage modes times four accepted-prefix lengths; each case replays at most three physical epochs and reads three rowsets. |
| Design | tests/unit/local_sink_replay_test.cpp:8-25, docs/local-sink.md:49-78, docs/local-sink.md:88-107, docs/native-replay.md:26-67, docs/native-replay.md:78-121, src/runtime/session.cpp:773-846, tests/support/sink_replay_fixture.hpp:6-42, tests/support/session_journal_stream_cases.hpp:14-115, src/recovery/journal_file.cpp:199-229 |

## B0003

[Lines 26–33](../../../../../tests/unit/local_sink_replay_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void rotation() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve an older sink origin across generation rotation during sink-aware restore. |
| inputs / outputs | Three delivered generations and a fourth committed update in generation 2; restore opens the older-origin sink against generation 2 root. |
| invariants | Verified sequence remains 3 while sink base remains 0; next delivered epoch records generation 2 and sequence 4. |
| ownership | Fixture owns generation history and sink file; returned owner owns generation and sink locks. |
| failure | An origin or checkpoint mismatch, lost native state, or wrong generation/sequence fails the case. |
| cost | Four typed commits, three initial deliveries, one rotation, one generation-aware replay and one final delivery. |
| Design | tests/unit/local_sink_replay_test.cpp:26-33, docs/local-sink.md:49-78, docs/local-sink.md:88-107, docs/native-replay.md:26-67, docs/native-replay.md:78-121, src/runtime/session.cpp:773-846, tests/support/sink_replay_fixture.hpp:6-42, tests/support/session_journal_stream_cases.hpp:14-115, src/recovery/journal_file.cpp:199-229 |

## B0004

[Lines 34–45](../../../../../tests/unit/local_sink_replay_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void stream_case(bool indexed,const session_journal_stream_test::Case& profile,bool pending) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resume typed stream input with a pending or committed second row while matching durable sink coverage. |
| inputs / outputs | Indexed flag, shared stream profile and pending toggle; original seekable source supplied to generation restore. |
| invariants | Replayed first empty/accepted epoch is duplicate; a committed but unaccepted row is published once, while pending input is finished once; decoder bytes/record count and later EOF remain exact. |
| ownership | The original source owner is reset before recovery; recovery receives a new owned istringstream; profile owns source bytes. |
| failure | Sink binding, source seek, replay output or post-restore continuation mismatch fails. |
| cost | One initial and one subsequent source row plus optional third continuation; loops bounded by the shared profile set and two pending states. |
| Design | tests/unit/local_sink_replay_test.cpp:34-45, docs/local-sink.md:49-78, docs/local-sink.md:88-107, docs/native-replay.md:26-67, docs/native-replay.md:78-121, src/runtime/session.cpp:773-846, tests/support/sink_replay_fixture.hpp:6-42, tests/support/session_journal_stream_cases.hpp:14-115, src/recovery/journal_file.cpp:199-229 |

## B0005

[Lines 46–56](../../../../../tests/unit/local_sink_replay_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void window_case(bool indexed,WindowFifoPolicy fifo,unsigned steps) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resume a partially committed watermark together with only its physical output epochs. |
| inputs / outputs | Indexed flag, FIFO policy and 0-3 completed substeps select a three-label window fixture. |
| invariants | Metadata substeps do not create sink epochs; verified sink sequence stays at 1 until physical delete is committed and delivered; resumed progress is command 4/physical 2 with exact erase output. |
| ownership | Window queue/runtime own active command and rows; durable sink owns accepted physical epochs; source and recovery owners have separate lifetimes. |
| failure | Duplicated/lost watermark, physical output, generation, or next update causes an assertion failure. |
| cost | Three inserts and up to three watermark substeps for each of two FIFO modes, two storage modes and four cut positions. |
| Design | tests/unit/local_sink_replay_test.cpp:46-56, docs/local-sink.md:49-78, docs/local-sink.md:88-107, docs/native-replay.md:26-67, docs/native-replay.md:78-121, src/runtime/session.cpp:773-846, tests/support/sink_replay_fixture.hpp:6-42, tests/support/session_journal_stream_cases.hpp:14-115, src/recovery/journal_file.cpp:199-229 |

## B0006

[Lines 57–60](../../../../../tests/unit/local_sink_replay_test.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void checksum(std::string& frame) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute body and protected-header checksums after a controlled frame mutation. |
| inputs / outputs | A mutable frame string in; SHA256(body) is written at offset 20 and SHA256(fixed prefix) at the protected-header offset. |
| invariants | The helper intentionally restores structural checksum validity so callers can test semantic/binding rejection separately. |
| ownership | String owns frame bytes; hashes are fixed-size local arrays. |
| failure | Short/invalid frame layout is outside this helper's callers; caller assertions test rejection. |
| cost | Two linear SHA256 passes over one bounded frame. |
| Design | tests/unit/local_sink_replay_test.cpp:57-60, docs/local-sink.md:49-78, docs/local-sink.md:88-107, docs/native-replay.md:26-67, docs/native-replay.md:78-121, src/runtime/session.cpp:773-846, tests/support/sink_replay_fixture.hpp:6-42, tests/support/session_journal_stream_cases.hpp:14-115, src/recovery/journal_file.cpp:199-229 |

## B0007

[Lines 61–65](../../../../../tests/unit/local_sink_replay_test.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class F> void rejects_unchanged(Saved& saved,F&& run) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run a restore callback and require rejection without file changes or leaked descriptors. |
| inputs / outputs | Saved fixture plus callable in; captures sink/WAL bytes and descriptor count, invokes restore, catches standard exception. |
| invariants | The check establishes failure before changed files or escaped owner; it is a test wrapper, not proof that every exception is safe beyond captured paths. |
| ownership | Captured bytes are copies; local result owner, if produced, dies inside the try scope. |
| failure | Only standard exceptions count as rejection; nonstandard failure propagates. |
| cost | One restore and two file reads per invocation. |
| Design | tests/unit/local_sink_replay_test.cpp:61-65, docs/local-sink.md:49-78, docs/local-sink.md:88-107, docs/native-replay.md:26-67, docs/native-replay.md:78-121, src/runtime/session.cpp:773-846, tests/support/sink_replay_fixture.hpp:6-42, tests/support/session_journal_stream_cases.hpp:14-115, src/recovery/journal_file.cpp:199-229 |

## B0008

[Lines 66–83](../../../../../tests/unit/local_sink_replay_test.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void hostile_and_limits() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject malformed or over-cap sink-aware recovery combinations, then accept a valid torn suffix after full validation. |
| inputs / outputs | Mutates durable frame values/checksums, advances sink beyond WAL, corrupts journal, varies identity/options/caps, and tests a valid torn tail. |
| invariants | No invalid origin/frontier, mismatched canonical epoch, ahead WAL, wrong schema/id, insufficient replay/work/heap allowance may mutate either file; valid accepted prefix repairs only after checks and retries sequence 3. |
| ownership | Saved owns test bytes and paths; each restore owns temporary receiver and lock; encoded mutations are local string copies. |
| failure | All adverse factories must throw while preserving tracked bytes/descriptors; the final valid path retains sequence-2 verified boundary then delivers sequence 3. |
| cost | Three-entry sink and journal; bounded scenarios for 9 input/config rejections, checksum forging, one valid two-tail repair and one retry. |
| Design | tests/unit/local_sink_replay_test.cpp:66-83, docs/local-sink.md:49-78, docs/local-sink.md:88-107, docs/native-replay.md:26-67, docs/native-replay.md:78-121, src/runtime/session.cpp:773-846, tests/support/sink_replay_fixture.hpp:6-42, tests/support/session_journal_stream_cases.hpp:14-115, src/recovery/journal_file.cpp:199-229 |

## B0009

[Lines 84–96](../../../../../tests/unit/local_sink_replay_test.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void source_failure_before_repair() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove source seek validation happens before either torn sink or journal tail is repaired. |
| inputs / outputs | CSV source with two committed rows; appends an 85-byte suffix to both files and restores once with an empty seekable stream, then with the original source. |
| invariants | Bad continuation preserves both torn byte strings and descriptor count; valid full input restores receipt 2 and repairs both tails to their saved complete prefixes. |
| ownership | Initial session is closed before file tampering; each restoration receives a newly owned stream and file locks. |
| failure | The first recovery must fail specifically with continuation; a different failure or early repair is rejected by assertions. |
| cost | Two source events, two torn suffix writes and two complete sink-aware reconstructions. |
| Design | tests/unit/local_sink_replay_test.cpp:84-96, docs/local-sink.md:49-78, docs/local-sink.md:88-107, docs/native-replay.md:26-67, docs/native-replay.md:78-121, src/runtime/session.cpp:773-846, tests/support/sink_replay_fixture.hpp:6-42, tests/support/session_journal_stream_cases.hpp:14-115, src/recovery/journal_file.cpp:199-229 |

## B0010

[Lines 97–97](../../../../../tests/unit/local_sink_replay_test.cpp#L97); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L97-L97:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in local_sink_replay_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/local_sink_replay_test.cpp](../../../../../tests/unit/local_sink_replay_test.cpp), [docs/local-sink.md](../../../../local-sink.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 98–104](../../../../../tests/unit/local_sink_replay_test.cpp#L98); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(){try{
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run sink-aware typed, stream, window, rotation, hostile-input and tail-order profiles. |
| inputs / outputs | main owns no fixture; loops over two storage modes, six queries, 4 output frontiers, shared stream profiles/pending flags and watermark cuts. |
| invariants | Every behavior assertion is delegated to the named case; stream and window profile coverage stays finite. |
| ownership | Callees own all QuerySession, stream and file resources. |
| failure | Any exception prints and returns status 1. |
| cost | Two modes times six query kinds times four prefix lengths, plus bounded profile matrices and three singleton cases. |
| Design | tests/unit/local_sink_replay_test.cpp:98-104, docs/local-sink.md:49-78, docs/local-sink.md:88-107, docs/native-replay.md:26-67, docs/native-replay.md:78-121, src/runtime/session.cpp:773-846, tests/support/sink_replay_fixture.hpp:6-42, tests/support/session_journal_stream_cases.hpp:14-115, src/recovery/journal_file.cpp:199-229 |
