# `tests/unit/native_replay_test.cpp` — block usage map

[Source](../../../../../tests/unit/native_replay_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `66ff0eb23e2dcbbf3adaa3ce2106ade8ef57985a2dd8e8fa100021b5d8cd4d7a`. 168 lines partitioned into 18 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../tests/unit/native_replay_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 10–10](../../../../../tests/unit/native_replay_test.cpp#L10) | Callable definition: SessionJournalRecoveryOptions recovery_options() | calls options; returns result · [reviewed contract](#b0002) |
| [B0003 · 11–11](../../../../../tests/unit/native_replay_test.cpp#L11) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 12–15](../../../../../tests/unit/native_replay_test.cpp#L12) | Callable definition: void append_events(QuerySession& session,Events& events) | calls status, next_output, push_back, options; growth push_back; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 16–16](../../../../../tests/unit/native_replay_test.cpp#L16) | Callable definition: Events finish_events(QuerySession& session) | calls step, commit, append_events; returns events; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 17–17](../../../../../tests/unit/native_replay_test.cpp#L17) | Callable definition: Events recovered(QuerySession& session) | calls next_recovered_output, push_back, std::move; returns events; growth push_back; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 18–21](../../../../../tests/unit/native_replay_test.cpp#L18) | Callable definition: void same_events(const Events& actual,const Events& expected) | calls check, size, seen, same_identity; guard check(actual.size()==expected.size(),"replay event count differs");std::vector&lt;bool&gt; seen(expected.…; 2 loop sites · [reviewed contract](#b0007) |
| [B0008 · 22–35](../../../../../tests/unit/native_replay_test.cpp#L22) | Callable definition: void typed_case(bool indexed,unsigned kind,bool pending_input) | calls f, offer, prepare, commit; guard check(result-&gt;status().state==SessionState::paused && result-&gt;status().committed_sequence==3 && res…; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 36–48](../../../../../tests/unit/native_replay_test.cpp#L36) | Callable definition: std::string third_record(const session_journal_stream_test::Case& profile,const Catalog& catalog) | calls io::write_input_json, io::write_input_binary, std::runtime_error; returns io::write_input_json(io::InputEvent{{3,TableId{0},SetOperation::insert,Row{std::int64_t{3},std::int…; growth insert · [reviewed contract](#b0009) |
| [B0010 · 49–67](../../../../../tests/unit/native_replay_test.cpp#L49) | Callable definition: void stream_case(bool indexed,const session_journal_stream_test::Case& profile,bool baseline_first,bool commit_second,bool seek) | calls typed::fixture, file, third_record, size; guard if(baseline_first){check(source-&gt;begin_next(),"stream first seed missing");static_cast&lt;void&gt;(typed:…; growth insert, make_unique · [reviewed contract](#b0010) |
| [B0011 · 68–76](../../../../../tests/unit/native_replay_test.cpp#L68) | Callable definition: void csv_variants(bool indexed) | calls session_journal_stream_test::cases, stream_case, typed::fixture, QuerySession::create; guard auto source=QuerySession::create(test.plan,std::make_unique&lt;std::istringstream&gt;("\"\"\r\n\r\n"),con…; growth make_unique; 3 loop sites · [reviewed contract](#b0011) |
| [B0012 · 77–92](../../../../../tests/unit/native_replay_test.cpp#L77) | Callable definition: void windows(bool indexed,WindowFifoPolicy fifo,unsigned committed_steps) | calls window::plan, QuerySession::create_windowed, window::config, start; guard for(unsigned step=0;step&lt;committed_steps;++step){check(source-&gt;begin_next(),"watermark step missing…; growth insert; 3 loop sites · [reviewed contract](#b0012) |
| [B0013 · 93–93](../../../../../tests/unit/native_replay_test.cpp#L93) | Callable definition: void put(const std::string& path,std::string_view data) | calls out, write, data, size; guard void put(const std::string& path,std::string_view data) {std::ofstream out(path,std::ios::binary\|st… · [reviewed contract](#b0013) |
| [B0014 · 94–109](../../../../../tests/unit/native_replay_test.cpp#L94) | Callable definition: void truncations() | calls offer, prepare, commit, next_output; guard check(result-&gt;progress().sequence==(complete?1U:0U) && result-&gt;recovery_status().pending_input_sequ…; 2 loop sites · [reviewed contract](#b0014) |
| [B0015 · 110–138](../../../../../tests/unit/native_replay_test.cpp#L110) | Callable definition: void malformed_native() | calls window::plan, QuerySession::create_windowed, window::config, start; guard const auto checkpoint=dir.file("base.crown"),log=dir.file("query.wal");static_cast&lt;void&gt;(source-&gt;ch…; growth make_unique; 1 loop sites · [reviewed contract](#b0015) |
| [B0016 · 139–157](../../../../../tests/unit/native_replay_test.cpp#L139) | Callable definition: void caps_and_identity() | calls offer, prepare, commit, append_events; guard auto result=QuerySession::restore_journal(compiler,f.checkpoint,f.log,recovery_options());const aut…; 2 loop sites · [reviewed contract](#b0016) |
| [B0017 · 158–158](../../../../../tests/unit/native_replay_test.cpp#L158) | Closes surrounding scope/type. |  · [reviewed contract](#b0017) |
| [B0018 · 159–168](../../../../../tests/unit/native_replay_test.cpp#L159) | Callable definition: int main() | calls typed_case, session_journal_stream_test::cases, stream_case, csv_variants; returns 1; 8 loop sites · [reviewed contract](#b0018) |

## B0001

[Lines 1–9](../../../../../tests/unit/native_replay_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:5f678a05c430206e1d3d29d2fec8f607733e7e499fa813835d584c5c8a166800
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare native_replay_test.cpp: include "session_journal_fixture.hpp", "session_journal_stream_cases.hpp", "crown/api/error.hpp", &lt;fstream&gt;, &lt;tuple&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/native_replay_test.cpp](../../../../../tests/unit/native_replay_test.cpp), [docs/native-replay.md](../../../../native-replay.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 10–10](../../../../../tests/unit/native_replay_test.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SessionJournalRecoveryOptions recovery_options(){SessionJournalRecoveryOptions result;result.journal=options();return result;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide default native replay limits bound to the shared session-journal identity. |
| inputs / outputs | No input; returns recovery options whose journal member uses the test's fixed query/generation options. |
| invariants | The helper does not mutate fixture files or supply a stream continuation. |
| ownership | Returned options are an independent value copied by recovery factory. |
| failure | Any later recovery failure retains its native file, codec, image or journal category; the helper adds no catch. |
| cost | One options value construction. |
| Design | tests/unit/native_replay_test.cpp:10-10, docs/native-replay.md:16-67, docs/native-replay.md:69-121, docs/journal.md:30-50, src/runtime/session.cpp:630-657, src/runtime/session.cpp:773-862, src/recovery/journal_file.cpp:199-250, tests/support/session_journal_fixture.hpp:17-40, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0003

[Lines 11–11](../../../../../tests/unit/native_replay_test.cpp#L11); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L11-L11:sha256:638da39b87e2ab28a91ee5f357914f6785492ecbf1635d95c0cc6f63cc7b4e4f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare native_replay_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/native_replay_test.cpp](../../../../../tests/unit/native_replay_test.cpp), [docs/native-replay.md](../../../../native-replay.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 12–15](../../../../../tests/unit/native_replay_test.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void append_events(QuerySession& session,Events& events) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append current committed output to an expected replay identity list. |
| inputs / outputs | QuerySession and event vector in; drains next_output and appends RecoveredResult records tagged with query, generation and committed physical sequence. |
| invariants | The expected list records emitted signed rows only; ordinal/order are not treated as semantic identity. |
| ownership | Session owns each output until transfer; vector owns moved SignedResult values and any copied metadata. |
| failure | Native output transfer/allocation errors propagate. |
| cost | Drains one committed epoch; work scales with output rows and vector growth. |
| Design | tests/unit/native_replay_test.cpp:12-15, docs/native-replay.md:16-67, docs/native-replay.md:69-121, docs/journal.md:30-50, src/runtime/session.cpp:630-657, src/runtime/session.cpp:773-862, src/recovery/journal_file.cpp:199-250, tests/support/session_journal_fixture.hpp:17-40, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0005

[Lines 16–16](../../../../../tests/unit/native_replay_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Events finish_events(QuerySession& session){while(session.step()!=DeltaStep::prepared){}session.commit();Events events;append_events(session,events);return events;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Finish one prepared epoch and collect its signed output as expected replay events. |
| inputs / outputs | QuerySession in; repeatedly steps to prepared, commits, then returns all output from append_events. |
| invariants | The helper does not change journal setup or claim durability beyond the attached journal commit path. |
| ownership | Session retains native state; returned vector owns transferred results. |
| failure | Preparation, journal commit or output collection failures propagate. |
| cost | One epoch's bounded preparation/commit and output drain. |
| Design | tests/unit/native_replay_test.cpp:16-16, docs/native-replay.md:16-67, docs/native-replay.md:69-121, docs/journal.md:30-50, src/runtime/session.cpp:630-657, src/runtime/session.cpp:773-862, src/recovery/journal_file.cpp:199-250, tests/support/session_journal_fixture.hpp:17-40, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0006

[Lines 17–17](../../../../../tests/unit/native_replay_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Events recovered(QuerySession& session){Events events;while(auto value=session.next_recovered_output())events.push_back(std::move(*value));return events;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain identity-bearing recovered output from a restored session. |
| inputs / outputs | QuerySession in; moves every next_recovered_output value into an Events vector. |
| invariants | Only the recovery-output API is used; it is distinct from regular next_output and attached sink delivery. |
| ownership | Moved result tuples are owned by returned vector/account semantics; session releases consumed backlog entries. |
| failure | Replay buffer/API failures propagate. |
| cost | One drain of the remaining replayed rows; linear in row count. |
| Design | tests/unit/native_replay_test.cpp:17-17, docs/native-replay.md:16-67, docs/native-replay.md:69-121, docs/journal.md:30-50, src/runtime/session.cpp:630-657, src/runtime/session.cpp:773-862, src/recovery/journal_file.cpp:199-250, tests/support/session_journal_fixture.hpp:17-40, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0007

[Lines 18–21](../../../../../tests/unit/native_replay_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void same_events(const Events& actual,const Events& expected) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare replay event sets without depending on container order or output ordinal. |
| inputs / outputs | Actual and expected RecoveredResult vectors in; checks equal sizes and greedily matches each actual value to one unused expected value by same_identity. |
| invariants | Each expected identity is consumed at most once; query/generation/physical sequence/operation/exact tuple define identity. |
| ownership | Both vectors own their values; local seen vector is only an observer marker. |
| failure | Missing, repeated or semantically different events become assertion failures. |
| cost | Quadratic identity comparisons in these small fixture outputs; one bool marker per expected result. |
| Design | tests/unit/native_replay_test.cpp:18-21, docs/native-replay.md:16-67, docs/native-replay.md:69-121, docs/journal.md:30-50, src/runtime/session.cpp:630-657, src/runtime/session.cpp:773-862, src/recovery/journal_file.cpp:199-250, tests/support/session_journal_fixture.hpp:17-40, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0008

[Lines 22–35](../../../../../tests/unit/native_replay_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void typed_case(bool indexed,unsigned kind,bool pending_input) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconstruct typed physical updates, optional uncommitted input, output identities and next admission. |
| inputs / outputs | Indexed mode, query kind and pending toggle; three changes commit, with optional fourth prepared input before owner destruction. |
| invariants | Restore returns paused with same rows/progress/commit sequence; pending input is reported and not reoffered; recovered output identities match; next input commits once and journal record count/counters advance to 9/4. |
| ownership | Original QuerySession is destroyed before recovery; fixture owns checkpoint/WAL/program; recovered owner owns receiving account and journal lock. |
| failure | Mismatched native relation, source positions, pending flag, output backlog or retry sequence fails. |
| cost | Two storage modes times six query kinds times both pending flags; at most four source changes and their output per case. |
| Design | tests/unit/native_replay_test.cpp:22-35, docs/native-replay.md:16-67, docs/native-replay.md:69-121, docs/journal.md:30-50, src/runtime/session.cpp:630-657, src/runtime/session.cpp:773-862, src/recovery/journal_file.cpp:199-250, tests/support/session_journal_fixture.hpp:17-40, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0009

[Lines 36–48](../../../../../tests/unit/native_replay_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string third_record(const session_journal_stream_test::Case& profile,const Catalog& catalog) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode the third source row in each stream profile's native format. |
| inputs / outputs | Profile and Catalog in; JSONL, binary, header-aware CSV, or legacy row bytes out. |
| invariants | The generated row has sequence 3 and explicit source name/offset for wire formats; CSV honors header/field order. |
| ownership | Returned string owns bytes; the shared profile and catalog are borrowed. |
| failure | Unsupported enum value throws runtime_error. |
| cost | One source record encode or bounded literal string construction. |
| Design | tests/unit/native_replay_test.cpp:36-48, docs/native-replay.md:16-67, docs/native-replay.md:69-121, docs/journal.md:30-50, src/runtime/session.cpp:630-657, src/runtime/session.cpp:773-862, src/recovery/journal_file.cpp:199-250, tests/support/session_journal_fixture.hpp:17-40, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0010

[Lines 49–67](../../../../../tests/unit/native_replay_test.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void stream_case(bool indexed,const session_journal_stream_test::Case& profile,bool baseline_first,bool commit_second,bool seek) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recover stream decoder position, cached input, and unread continuation under both origin policies. |
| inputs / outputs | Storage mode, profile, baseline-seeded flag, commit-second flag and seek flag; source has up to three rows and one owned continuation. |
| invariants | Reader bytes/records and source offset match profile; pending row is resumed without reoffer; later third input and EOF reach exact native relation/progress; origin seek uses full stream while nonseek mode starts at generated unread tail. |
| ownership | Original stream/session are destroyed before recovery; caller transfers a new istringstream to restore; recovered result owns reader and journal state. |
| failure | Bad stream seek, lost cached row, duplicate input or wrong source checkpoint fails. |
| cost | Two storage modes times eight shared profiles times baseline/commit/seek combinations (only tested combinations at callers); at most three records per source. |
| Design | tests/unit/native_replay_test.cpp:49-67, docs/native-replay.md:16-67, docs/native-replay.md:69-121, docs/journal.md:30-50, src/runtime/session.cpp:630-657, src/runtime/session.cpp:773-862, src/recovery/journal_file.cpp:199-250, tests/support/session_journal_fixture.hpp:17-40, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0011

[Lines 68–76](../../../../../tests/unit/native_replay_test.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void csv_variants(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise quoted CRLF and headerless CSV mapping plus a nullary table's quoted empty header. |
| inputs / outputs | Storage mode in; extends shared CSV profiles with quoted-header and headerless variants, then creates one nullary source. |
| invariants | Quoted header consumes correct CRLF bytes; headerless source skips header mapping; nullary quoted empty header advances byte origin to six while preserving source offset 104. |
| ownership | Each stream is owned by QuerySession then separately recreated for origin-seek recovery; profile strings own fixture input. |
| failure | CSV mapping/source/output mismatch fails the checks. |
| cost | Four baseline/commit/pending combinations per two CSV variants, plus one nullary replay; no large data scan. |
| Design | tests/unit/native_replay_test.cpp:68-76, docs/native-replay.md:16-67, docs/native-replay.md:69-121, docs/journal.md:30-50, src/runtime/session.cpp:630-657, src/runtime/session.cpp:773-862, src/recovery/journal_file.cpp:199-250, tests/support/session_journal_fixture.hpp:17-40, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0012

[Lines 77–92](../../../../../tests/unit/native_replay_test.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void windows(bool indexed,WindowFifoPolicy fifo,unsigned committed_steps) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replay a watermark after zero through three committed expiration substeps. |
| inputs / outputs | Storage mode, FIFO policy and number of completed steps choose window state and expected output events. |
| invariants | Partial metadata substeps retain command/input state; recovery emits only already committed physical output; finishing remaining steps gives physical=2, command=4 and empty rows without re-journaling records. |
| ownership | Window source is destroyed before replay; expected event vector owns transferred output; result owner owns journal and resumed window runtime. |
| failure | Lost/duplicated step, output mismatch or record-count change fails. |
| cost | Three inserted labels plus up to three watermark steps across two FIFO policies and two storage modes. |
| Design | tests/unit/native_replay_test.cpp:77-92, docs/native-replay.md:16-67, docs/native-replay.md:69-121, docs/journal.md:30-50, src/runtime/session.cpp:630-657, src/runtime/session.cpp:773-862, src/recovery/journal_file.cpp:199-250, tests/support/session_journal_fixture.hpp:17-40, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0013

[Lines 93–93](../../../../../tests/unit/native_replay_test.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void put(const std::string& path,std::string_view data) {std::ofstream out(path,std::ios::binary|std::ios::trunc);out.write(data.data(),static_cast<std::streamsize>(data.size()));check(static_cast<bool>(out),"test file write failed");}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace one journal file with an exact binary prefix for truncation or forgery cases. |
| inputs / outputs | Path and string_view in; opens/truncates/writes binary bytes and checks stream success. |
| invariants | Writes only requested log path; parsing/recovery validation is the caller's responsibility. |
| ownership | Byte view is borrowed through write; ofstream owns descriptor until function exit. |
| failure | I/O failure is a runtime_error from check. |
| cost | One bounded test-file rewrite. |
| Design | tests/unit/native_replay_test.cpp:93-93, docs/native-replay.md:16-67, docs/native-replay.md:69-121, docs/journal.md:30-50, src/runtime/session.cpp:630-657, src/runtime/session.cpp:773-862, src/recovery/journal_file.cpp:199-250, tests/support/session_journal_fixture.hpp:17-40, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0014

[Lines 94–109](../../../../../tests/unit/native_replay_test.cpp#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void truncations() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check every recoverable input/decision byte cut and retry the missing native operation. |
| inputs / outputs | A committed one-row log is saved; loop truncates from header end through full file; no-repair and checksum-corrupt variants follow. |
| invariants | Only incomplete later tails can be repaired; complete log reopens at commit; torn input/decision preserves the right pending state; retry produces original complete bytes exactly once; no-repair and complete corruption leave bytes unchanged. |
| ownership | Saved fixture owns checkpoint/query; each restored owner is scoped; \`frames\` views borrow the \`full\` string. |
| failure | Unexpected accepted state, duplicate/lost input, wrong fault or changed corrupt bytes fails. |
| cost | Every suffix byte cut from one header boundary through EOF, plus two policy/corruption cases and one retry per cut; file size is fixture-bounded. |
| Design | tests/unit/native_replay_test.cpp:94-109, docs/native-replay.md:16-67, docs/native-replay.md:69-121, docs/journal.md:30-50, src/runtime/session.cpp:630-657, src/runtime/session.cpp:773-862, src/recovery/journal_file.cpp:199-250, tests/support/session_journal_fixture.hpp:17-40, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0015

[Lines 110–138](../../../../../tests/unit/native_replay_test.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void malformed_native() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forge checksum-valid journal transitions and known stream metadata to test native semantic validation. |
| inputs / outputs | Builds a window watermark physical-commit forgery, CSV permutation/offset mutations, impossible first-header offset, and malformed CSV/native profiles. |
| invariants | Codec scan alone is not sufficient: session replay rejects a checksum-valid commit that disagrees with native transition, checkpoint-known CSV mapping or source record boundaries without rewriting the file. |
| ownership | Encoded views borrow their decoded row/frame owner only through immediate encode; MemoryAccount is a test helper; each query/file lives in a scoped fixture. |
| failure | Expected transition or binding errors are checked by category; accepting any forgery or mutating bytes fails. |
| cost | Several one-record/window fixtures, four relevant stream profile traces, and a bounded per-profile rewrite; no adversarial unbounded input is generated. |
| Design | tests/unit/native_replay_test.cpp:110-138, docs/native-replay.md:16-67, docs/native-replay.md:69-121, docs/journal.md:30-50, src/runtime/session.cpp:630-657, src/runtime/session.cpp:773-862, src/recovery/journal_file.cpp:199-250, tests/support/session_journal_fixture.hpp:17-40, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0016

[Lines 139–157](../../../../../tests/unit/native_replay_test.cpp#L139); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void caps_and_identity() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check replay identity, exact/under cumulative limits, and drop cleanup on a committed output fixture. |
| inputs / outputs | Restores one or two committed epochs; compares statistics and same_identity fields; sets exact/one-under decode/source/output-work/byte/row caps and wrong generation. |
| invariants | Ordinal changes do not affect identity; generation and physical sequence do; exact cumulative grants succeed, one-under work/bytes reject; source grant is not reset between records; drop releases journal descriptor. |
| ownership | Returned recovered outputs live independently of the first session; each restore owns its own account and lock; statistics are snapshots. |
| failure | Expected failures retain ImageFailure(work/limit) or journal binding carrier; cap mismatch or descriptor leak fails. |
| cost | One identity fixture with one recovered row, exact/under pairs for decode/source/output bytes and output rows, plus a two-input cumulative source case. |
| Design | tests/unit/native_replay_test.cpp:139-157, docs/native-replay.md:16-67, docs/native-replay.md:69-121, docs/journal.md:30-50, src/runtime/session.cpp:630-657, src/runtime/session.cpp:773-862, src/recovery/journal_file.cpp:199-250, tests/support/session_journal_fixture.hpp:17-40, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0017

[Lines 158–158](../../../../../tests/unit/native_replay_test.cpp#L158); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L158-L158:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in native_replay_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/native_replay_test.cpp](../../../../../tests/unit/native_replay_test.cpp), [docs/native-replay.md](../../../../native-replay.md), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 159–168](../../../../../tests/unit/native_replay_test.cpp#L159); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(){try{
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run typed, stream, CSV, window, tail, semantic-forgery and resource/identity replay cases. |
| inputs / outputs | main iterates storage/query/profile matrices then calls bounded singleton coverage suites. |
| invariants | The wrapper specifies matrices but does not infer successful execution; each callee checks actual state. |
| ownership | main owns call order only; fixture source/session/file lifetimes stay in callees. |
| failure | Any standard exception prints and returns 1. |
| cost | Two storage modes times six query kinds and bounded stream/window profiles; csv_variants runs per storage mode, followed by caps/identity, truncation, and malformed-native suites. |
| Design | tests/unit/native_replay_test.cpp:159-168, docs/native-replay.md:16-67, docs/native-replay.md:69-121, docs/journal.md:30-50, src/runtime/session.cpp:630-657, src/runtime/session.cpp:773-862, src/recovery/journal_file.cpp:199-250, tests/support/session_journal_fixture.hpp:17-40, tests/support/session_journal_stream_cases.hpp:14-115 |
