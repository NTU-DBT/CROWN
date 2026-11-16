# `tests/unit/local_sink_test.cpp` — block usage map

[Source](../../../../../tests/unit/local_sink_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `80c79f762cf21739192a3b72b43c3e6d355b01928b36cb2b265dbd97abe38e49`. 179 lines partitioned into 13 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../tests/unit/local_sink_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(!std::is_trivially_copyable_v&lt;sk::Receipt&gt;); · [reviewed contract](#b0001) |
| [B0002 · 10–31](../../../../../tests/unit/local_sink_test.cpp#L10) | Callable definition: void typed_case(bool indexed,unsigned kind,bool crash_before_delivery) | calls f, resize, source_catalog, size; guard f.commit(i);check(f.query.session-&gt;begin_next_result()==SessionBegin::would_block,"local sink did n…; growth resize; 2 loop sites · [reviewed contract](#b0002) |
| [B0003 · 32–49](../../../../../tests/unit/local_sink_test.cpp#L32) | Callable definition: void canonical_and_schema(const char* golden) | calls resource::MemoryAccount::create, file, checkpoint_image, generation_test::options; guard {auto file=sk::File::create(account,path,header,schema);check(file.append(7,11,rows),"first canonic…; growth insert, push_back; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 50–58](../../../../../tests/unit/local_sink_test.cpp#L50) | Callable definition: void reject_incomplete_replay() | calls commit, deliver_local_epoch, CompiledProgram::standalone, reset; guard try{value-&gt;open_local_sink(f.path,options());}catch(const Error&){rejected=true;}check(rejected,"pa…; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 59–71](../../../../../tests/unit/local_sink_test.cpp#L59) | Callable definition: std::string third_record(const session_journal_stream_test::Case& profile,const Catalog& catalog) | calls io::write_input_json, io::write_input_binary, std::runtime_error; returns io::write_input_json(io::InputEvent{{3,TableId{0},SetOperation::insert,Row{std::int64_t{3},std::int…; growth insert · [reviewed contract](#b0005) |
| [B0006 · 72–84](../../../../../tests/unit/local_sink_test.cpp#L72) | Callable definition: void stream_case(bool indexed,const session_journal_stream_test::Case& profile,bool pending) | calls typed::fixture, file, third_record, size; guard check(source-&gt;begin_next(),"sink first stream row missing");finish(*source);static_cast&lt;void&gt;(sourc…; growth insert, make_unique · [reviewed contract](#b0006) |
| [B0007 · 85–99](../../../../../tests/unit/local_sink_test.cpp#L85) | Callable definition: void window_case(bool indexed,WindowFifoPolicy fifo,unsigned steps) | calls file, window::plan, QuerySession::create_windowed, window::config; guard for(std::uint64_t label=1;label&lt;=3;++label){typed::enqueue(*source,io::WindowCommand{label,io::Wind…; 3 loop sites · [reviewed contract](#b0007) |
| [B0008 · 100–121](../../../../../tests/unit/local_sink_test.cpp#L100) | Callable definition: void cancellation_and_queue() | calls commit, deliver_local_epoch, typed::enqueue, check; guard Fixture f;f.commit(0);static_cast&lt;void&gt;(f.query.session-&gt;deliver_local_epoch());typed::enqueue(*f.q…; 3 loop sites · [reviewed contract](#b0008) |
| [B0009 · 122–134](../../../../../tests/unit/local_sink_test.cpp#L122) | Callable definition: void delivery_budget_and_private_barrier() | calls file, options, create_local_sink, typed::enqueue; guard typed::enqueue(*f.session,io::InputEvent{f.test.updates\[0\],io::SourcePosition{"feed",10}});check(f.…; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 135–138](../../../../../tests/unit/local_sink_test.cpp#L135) | Callable definition: void checksum(std::string& frame) | calls sha256_fixed, std::string_view, substr, std::copy · [reviewed contract](#b0010) |
| [B0011 · 139–174](../../../../../tests/unit/local_sink_test.cpp#L139) | Callable definition: void hostile_and_caps() | calls file, resource::MemoryAccount::create, generation_test::options, options; guard {auto file=sk::File::create(account,path,header,schema);check(file.append(1,1,rows) && file.append(…; growth insert; 7 loop sites · [reviewed contract](#b0011) |
| [B0012 · 175–175](../../../../../tests/unit/local_sink_test.cpp#L175) | Closes surrounding scope/type. |  · [reviewed contract](#b0012) |
| [B0013 · 176–179](../../../../../tests/unit/local_sink_test.cpp#L176) | Callable definition: int main(int argc,char** argv) | calls check, typed_case, session_journal_stream_test::cases, stream_case; guard int main(int argc,char** argv){try{check(argc==2,"expected independent epoch golden");for(const boo…; returns 1; 7 loop sites · [reviewed contract](#b0013) |

## B0001

[Lines 1–9](../../../../../tests/unit/local_sink_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:683dba649ac2620e0ea908857f0224d628e6a7354aa33c4b1da231b4fd636205
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare local_sink_test.cpp: include "local_sink_fixture.hpp", "session_journal_stream_cases.hpp", "crown/api/error.hpp", &lt;algorithm&gt;; bind local aliases/name imports; require 1 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/local_sink_test.cpp](../../../../../tests/unit/local_sink_test.cpp), [docs/local-sink.md](../../../../local-sink.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 10–31](../../../../../tests/unit/local_sink_test.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void typed_case(bool indexed,unsigned kind,bool crash_before_delivery) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check committed signed output delivery against an independent set oracle across native query kinds. |
| inputs / outputs | Indexed flag, query kind and restart toggle; each of four updates is applied to an independent Database before commit/delivery. |
| invariants | Producer admission blocks while output is pending; ordinary next_output cannot bypass sink; delivery publishes generation 1 sequence i+1; persisted changes equal oracle difference except maintenance; restart deduplicates prior frames and rotation keeps sink identity/base. |
| ownership | Fixture owns source session and sink; copied Epoch rows have account-funded payloads and remain valid after session drop; ordinary oracle Database is separate. |
| failure | Wrong delivery kind/frontier/output/restart/next self-join state fails assertions; process restart is exercised before each current delivery when enabled. |
| cost | Two storage modes times six query kinds times four commits and both restart settings; each oracle step mutates at most one fixture update. |
| Design | tests/unit/local_sink_test.cpp:10-31, docs/local-sink.md:13-47, docs/local-sink.md:49-107, docs/local-sink.md:110-158, docs/history-retirement.md:22-58, src/runtime/session.cpp:864-935, src/recovery/local_sink.cpp:148-189, src/recovery/local_sink.cpp:269-317, tests/support/local_sink_fixture.hpp:12-29, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0003

[Lines 32–49](../../../../../tests/unit/local_sink_test.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void canonical_and_schema(const char* golden) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate canonical scalar encoding, order-independent retry, duplicate rejection and decoded epoch lifetime. |
| inputs / outputs | Standalone sink Header/schema plus two typed signed rows; independent golden bytes supplied by a path. |
| invariants | All five scalar kinds round-trip including embedded NUL, UTF8, leap date and canonical decimal; row order does not affect retry bytes; a changed sign/value and duplicate same-sign tuple reject; empty epoch advances generation/receipt. |
| ownership | Standalone File owns account-funded buffers/index; input RowViews borrow fixture rows during synchronous calls; retained Epoch owns decoded rows beyond File scope. |
| failure | Golden hash/bytes mismatch, noncanonical duplicate, invalid retry, or lost post-close row lifetime fails. |
| cost | Two rows and one empty epoch, with canonical encode/retry/read and one reopen; exact golden frame is 265 bytes. |
| Design | tests/unit/local_sink_test.cpp:32-49, docs/local-sink.md:13-47, docs/local-sink.md:49-107, docs/local-sink.md:110-158, docs/history-retirement.md:22-58, src/runtime/session.cpp:864-935, src/recovery/local_sink.cpp:148-189, src/recovery/local_sink.cpp:269-317, tests/support/local_sink_fixture.hpp:12-29, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0004

[Lines 50–58](../../../../../tests/unit/local_sink_test.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reject_incomplete_replay() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject sink attachment after replay output was partially transferred or caller-frontier suppressed. |
| inputs / outputs | Two native committed epochs with only first sink delivery; tests bare recovery after consuming output or setting replay frontier. |
| invariants | Neither caller progress nor transfer/discard history creates complete durable sink coverage; original sink is not expanded by the rejected attach. |
| ownership | Each recovered owner owns its replay buffer and generation lock until destruction; original sink file remains fixture-owned. |
| failure | Only an attachment Error is accepted; any opened sink is a failed test. |
| cost | Two restore/attach cases against a two-epoch native fixture. |
| Design | tests/unit/local_sink_test.cpp:50-58, docs/local-sink.md:13-47, docs/local-sink.md:49-107, docs/local-sink.md:110-158, docs/history-retirement.md:22-58, src/runtime/session.cpp:864-935, src/recovery/local_sink.cpp:148-189, src/recovery/local_sink.cpp:269-317, tests/support/local_sink_fixture.hpp:12-29, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0005

[Lines 59–71](../../../../../tests/unit/local_sink_test.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string third_record(const session_journal_stream_test::Case& profile,const Catalog& catalog) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the next stream record in the exact wire/text format selected by a profile. |
| inputs / outputs | Stream profile and catalog in; one record string out for JSONL, binary, CSV, and five legacy formats. |
| invariants | CSV field order/header behavior follows the supplied profile; explicit source positions are preserved for JSON/binary/timestamp records. |
| ownership | Returned string owns encoded bytes; profile/catalog are borrowed only during construction. |
| failure | Unknown profile format throws runtime_error. |
| cost | One record encoded/copied per call; size follows the selected input format. |
| Design | tests/unit/local_sink_test.cpp:59-71, docs/local-sink.md:13-47, docs/local-sink.md:49-107, docs/local-sink.md:110-158, docs/history-retirement.md:22-58, src/runtime/session.cpp:864-935, src/recovery/local_sink.cpp:148-189, src/recovery/local_sink.cpp:269-317, tests/support/local_sink_fixture.hpp:12-29, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0006

[Lines 72–84](../../../../../tests/unit/local_sink_test.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void stream_case(bool indexed,const session_journal_stream_test::Case& profile,bool pending) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify a durable sink continues native stream replay at the first unread input. |
| inputs / outputs | Storage mode, shared profile and pending toggle; source contains two profile rows plus generated third record. |
| invariants | First accepted epoch deduplicates; committed second row is published once unless cached pending; third input then finishes; sink receipt reaches 3 and persisted epochs 2/3 match exact output. |
| ownership | Source is destroyed before restart; profile string and extra record form owned input; recovered QuerySession holds the receiving account and file locks. |
| failure | Decoder origin, no-duplicate input, final EOF, output or receipt mismatch fails. |
| cost | Three stream rows, one sink-origin checkpoint and at most two initial/recovery deliveries per profile and pending state. |
| Design | tests/unit/local_sink_test.cpp:72-84, docs/local-sink.md:13-47, docs/local-sink.md:49-107, docs/local-sink.md:110-158, docs/history-retirement.md:22-58, src/runtime/session.cpp:864-935, src/recovery/local_sink.cpp:148-189, src/recovery/local_sink.cpp:269-317, tests/support/local_sink_fixture.hpp:12-29, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0007

[Lines 85–99](../../../../../tests/unit/local_sink_test.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void window_case(bool indexed,WindowFifoPolicy fifo,unsigned steps) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recover sink delivery across partially completed window watermarks and generation rotation. |
| inputs / outputs | Storage mode, FIFO policy and 0-3 executed substeps select a three-label fixture. |
| invariants | Only physical epochs count toward persisted epoch number; final erase is sequence 2, progress sequence 4; rotation preserves sink origin and the next insert is generation 2 sequence 3. |
| ownership | Source and recovered sessions own separate window runtimes; local sink and generation root retain their file locks until owner destruction. |
| failure | Unexpected metadata output, duplicated deletion, changed FIFO/native rows or next-generation identity fails. |
| cost | Three insert commands, one watermark with at most three substeps, one recovery and one rotated post-recovery insert. |
| Design | tests/unit/local_sink_test.cpp:85-99, docs/local-sink.md:13-47, docs/local-sink.md:49-107, docs/local-sink.md:110-158, docs/history-retirement.md:22-58, src/runtime/session.cpp:864-935, src/recovery/local_sink.cpp:148-189, src/recovery/local_sink.cpp:269-317, tests/support/local_sink_fixture.hpp:12-29, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0008

[Lines 100–121](../../../../../tests/unit/local_sink_test.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cancellation_and_queue() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check cancellation before, during and after private work while preserving journal recovery semantics. |
| inputs / outputs | Three phases choose whether the second input is absent, private, or committed-but-undelivered before pause/stop/drop. |
| invariants | Uncommitted cached input is not reoffered; committed output is delivered on restart; final receipt is exactly 2 with one row in epoch 2. |
| ownership | The original owner is explicitly stopped/dropped/reset; recovery has a new owner; sink file persists independently. |
| failure | Missing retained input, duplicated output, failure to cancel, or wrong final epoch fails. |
| cost | Three fixture restarts and one bounded second update; input queue scenario separately admits one event, retains one rejected batch, blocks ten times and retries it after delivery. |
| Design | tests/unit/local_sink_test.cpp:100-121, docs/local-sink.md:13-47, docs/local-sink.md:49-107, docs/local-sink.md:110-158, docs/history-retirement.md:22-58, src/runtime/session.cpp:864-935, src/recovery/local_sink.cpp:148-189, src/recovery/local_sink.cpp:269-317, tests/support/local_sink_fixture.hpp:12-29, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0009

[Lines 122–134](../../../../../tests/unit/local_sink_test.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void delivery_budget_and_private_barrier() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Show private work blocks delivery and that copied cumulative delivery-work limit preserves pending output. |
| inputs / outputs | For exact and one-under policy, configure cap 3 or 2, mutate caller options after attach, and run two committed epochs. |
| invariants | Private fan-out never writes sink; exact budget succeeds, one-under fails without changing file or output; reopening does not reset consumed work and a larger copied limit allows retry. |
| ownership | QuerySession stores copied SessionLocalSinkOptions; fixture output remains owned until accepted; current limit counters live in session/sink owner. |
| failure | Expected work error is recovery::ImageFailure(work) only on under case; exact case completing at sequence 2 proves budget boundary. |
| cost | Two fixtures, two epochs each, one private rejection and optional reopen/retry; cap totals are small logical work units, not bytes. |
| Design | tests/unit/local_sink_test.cpp:122-134, docs/local-sink.md:13-47, docs/local-sink.md:49-107, docs/local-sink.md:110-158, docs/history-retirement.md:22-58, src/runtime/session.cpp:864-935, src/recovery/local_sink.cpp:148-189, src/recovery/local_sink.cpp:269-317, tests/support/local_sink_fixture.hpp:12-29, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0010

[Lines 135–138](../../../../../tests/unit/local_sink_test.cpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void checksum(std::string& frame) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute both sink frame checksums after a mutation for hostile semantic fixtures. |
| inputs / outputs | Frame string in; hashes body and protected prefix into wire offsets. |
| invariants | Checksum repair is used only to ensure subsequent validation reaches semantic/binding checks. |
| ownership | String owns bytes and local hash arrays; no File state is modified. |
| failure | Malformed short frames are outside callers; rejection assertions own the result. |
| cost | Two bounded hashes over one frame. |
| Design | tests/unit/local_sink_test.cpp:135-138, docs/local-sink.md:13-47, docs/local-sink.md:49-107, docs/local-sink.md:110-158, docs/history-retirement.md:22-58, src/runtime/session.cpp:864-935, src/recovery/local_sink.cpp:148-189, src/recovery/local_sink.cpp:269-317, tests/support/local_sink_fixture.hpp:12-29, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0011

[Lines 139–174](../../../../../tests/unit/local_sink_test.cpp#L139); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void hostile_and_caps() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test torn-tail repair, all-byte corruption, semantic forgeries, cumulative limits and file ownership. |
| inputs / outputs | Creates a one-row and empty-epoch corpus; enumerates all cuts after complete header, all single-bit flips, selected header/body fields with recomputed checksums, exact/under caps, writer lock and symlink cases. |
| invariants | Only an incomplete later suffix is repairable; mandatory header and complete corrupt/semantic frames reject without mutation; exact cumulative work/bytes succeed, one-under fails at the second append; receipt reports cannot alter authority; no symlink following or concurrent writer. |
| ownership | Standalone File owns account-funded buffers/index and flock; corpus strings and expected bytes are independent observer copies. |
| failure | Each hostile file is rejected through sink/Image failure without changing written bytes; byte/cap/resource assertion failures identify the case. |
| cost | Two epochs plus header; every suffix cut and file byte is visited, with selected semantic forgeries and two cap boundaries; loop counts scale with this one small encoded file, not unbounded data. |
| Design | tests/unit/local_sink_test.cpp:139-174, docs/local-sink.md:13-47, docs/local-sink.md:49-107, docs/local-sink.md:110-158, docs/history-retirement.md:22-58, src/runtime/session.cpp:864-935, src/recovery/local_sink.cpp:148-189, src/recovery/local_sink.cpp:269-317, tests/support/local_sink_fixture.hpp:12-29, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0012

[Lines 175–175](../../../../../tests/unit/local_sink_test.cpp#L175); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L175-L175:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in local_sink_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/local_sink_test.cpp](../../../../../tests/unit/local_sink_test.cpp), [docs/local-sink.md](../../../../local-sink.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 176–179](../../../../../tests/unit/local_sink_test.cpp#L176); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv){try{check(argc==2,"expected independent epoch golden");for(const bool indexed:{false,true}){for(unsigned kind=0;kind<6;++kind)for(const bool restart:{false,true})typed_case(indexed,kind,restart);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run all typed, stream, window, canonical-wire, cancellation, budget and hostile sink cases. |
| inputs / outputs | An independent canonical epoch golden path is required; main iterates two storage modes and bounded fixture profiles. |
| invariants | No test result is inferred from main; each subcase performs the actual assertions. |
| ownership | main owns only order/argument dispatch; callee-local owners and strings control lifetimes. |
| failure | Wrong argc or any standard exception reports status 1. |
| cost | Two modes times six query kinds and restart toggles, eight stream cases/pending toggles, two FIFO modes/four step cuts, and five singleton suites. |
| Design | tests/unit/local_sink_test.cpp:176-179, docs/local-sink.md:13-47, docs/local-sink.md:49-107, docs/local-sink.md:110-158, docs/history-retirement.md:22-58, src/runtime/session.cpp:864-935, src/recovery/local_sink.cpp:148-189, src/recovery/local_sink.cpp:269-317, tests/support/local_sink_fixture.hpp:12-29, tests/support/session_journal_stream_cases.hpp:14-115 |
