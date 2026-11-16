# `tests/unit/session_journal_test.cpp` — block usage map

[Source](../../../../../tests/unit/session_journal_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `3887c41d3289c6ae4ee2efe689e04856656d424896a1f634b81ca085eeaf476a`. 142 lines partitioned into 10 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../tests/unit/session_journal_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 8–32](../../../../../tests/unit/session_journal_test.cpp#L8) | Callable definition: void typed_case(bool indexed,unsigned kind) | calls f, resize, source_catalog, size; guard const auto input_log=contents(f.log);const auto pending=jp::scan(input_log);check(pending.pending &…; growth emplace, insert, resize; 3 loop sites · [reviewed contract](#b0002) |
| [B0003 · 33–58](../../../../../tests/unit/session_journal_test.cpp#L33) | Callable definition: void windows(bool indexed) | calls file, window::plan, QuerySession::create_windowed, window::config; guard check(source-&gt;begin_next() && reference-&gt;begin_next(),"window journal fixture head missing");; 3 loop sites · [reviewed contract](#b0003) |
| [B0004 · 59–74](../../../../../tests/unit/session_journal_test.cpp#L59) | Callable definition: void duplicate_expiration(bool indexed,WindowFifoPolicy fifo) | calls QuerySession::create_windowed, window::plan, window::config, start; guard check(source-&gt;begin_next(),"duplicate expiration head missing");const auto output=typed::finish(*so…; 2 loop sites · [reviewed contract](#b0004) |
| [B0005 · 75–95](../../../../../tests/unit/session_journal_test.cpp#L75) | Callable definition: void stream_and_resources() | calls file, typed::fixture, QuerySession::create, start; guard check(account.statistics().successful_allocations-before==allocations,"session journal enable escap…; growth make_unique; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 96–116](../../../../../tests/unit/session_journal_test.cpp#L96) | Callable definition: void all_stream_formats() | calls session_journal_stream_test::cases, file, typed::fixture, QuerySession::create; guard if(seeded){check(source-&gt;begin_next(),"seeded stream missing first row");static_cast&lt;void&gt;(typed::f…; growth make_unique; 4 loop sites · [reviewed contract](#b0006) |
| [B0007 · 117–130](../../../../../tests/unit/session_journal_test.cpp#L117) | Callable definition: void lifecycle() | calls typed::fixture, QuerySession::create_typed, file, start; guard if(control==SessionState::stopped){bool rejected=false;try{source-&gt;enable_journal(checkpoint,log,op…; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 131–140](../../../../../tests/unit/session_journal_test.cpp#L131) | Callable definition: void drain_and_retry() | calls f, offer, check, begin_next; guard Fixture f(false,1);f.offer();check(f.session-&gt;begin_next(),"drain fixture missing");f.session-&gt;paus… · [reviewed contract](#b0008) |
| [B0009 · 141–141](../../../../../tests/unit/session_journal_test.cpp#L141) | Closes surrounding scope/type. |  · [reviewed contract](#b0009) |
| [B0010 · 142–142](../../../../../tests/unit/session_journal_test.cpp#L142) | Callable definition: int main() | calls typed_case, windows, duplicate_expiration, stream_and_resources; returns 1; 3 loop sites · [reviewed contract](#b0010) |

## B0001

[Lines 1–7](../../../../../tests/unit/session_journal_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:c0b786c564352790b034c6d0790355b110390692426fd9312119e989ecc214e2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare session_journal_test.cpp: include "session_journal_fixture.hpp", "session_journal_stream_cases.hpp", "crown/api/error.hpp"; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/session_journal_test.cpp](../../../../../tests/unit/session_journal_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 8–32](../../../../../tests/unit/session_journal_test.cpp#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void typed_case(bool indexed,unsigned kind) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare durable journaled typed updates with independent set semantics and exact input/decision ordering. |
| inputs / outputs | Indexed flag and query kind; database oracle advances before each input; source is offered/prepared then committed through journal. |
| invariants | Input frame is durable before preparation; progress/physical sequence do not advance early; postcommit output and relation equal oracle; fixed journal records and counters match; active checkpoint/log cannot be replaced; header binds exact stored checkpoint digest and query identity. |
| ownership | Fixture's QuerySession owns writer and account; Database oracle owns separate rows; output rows transferred from QuerySession. |
| failure | Wrong records, checksum binding, source position, output or replacement admission fails via assertions or expected state fault. |
| cost | Two storage modes times six query kinds times four updates, plus two blocked checkpoint replacement attempts each. |
| Design | tests/unit/session_journal_test.cpp:8-32, docs/session-journal.md:13-55, docs/session-journal.md:57-88, docs/journal.md:24-50, docs/journal-files.md:16-55, src/runtime/session.cpp:286-345, src/runtime/session.cpp:747-763, src/runtime/session.cpp:1449-1476, src/recovery/journal_file.cpp:231-254, tests/support/session_journal_fixture.hpp:17-40, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0003

[Lines 33–58](../../../../../tests/unit/session_journal_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void windows(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare journaled window commands and partial watermark metadata with an independent live reference session. |
| inputs / outputs | Indexed mode; five window commands are enqueued to source/reference, stepped until command completion; each input and commit is scanned from WAL. |
| invariants | Physical sequence matches native commit count; accepted command progress matches source; metadata steps retain pending input and advance substep while physical state changes only when expiry commits; final log has all inputs and partial metadata commits. |
| ownership | Two QuerySessions own separate window state; reference has no journal; command values are enqueued independently. |
| failure | Missing input/substep/output equivalence or changed recorded counters fails. |
| cost | Five commands with a finite per-command substep loop; three inserted labels include duplicate row expiration. |
| Design | tests/unit/session_journal_test.cpp:33-58, docs/session-journal.md:13-55, docs/session-journal.md:57-88, docs/journal.md:24-50, docs/journal-files.md:16-55, src/runtime/session.cpp:286-345, src/runtime/session.cpp:747-763, src/runtime/session.cpp:1449-1476, src/recovery/journal_file.cpp:231-254, tests/support/session_journal_fixture.hpp:17-40, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0004

[Lines 59–74](../../../../../tests/unit/session_journal_test.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void duplicate_expiration(bool indexed,WindowFifoPolicy fifo) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check duplicate-row expiration advances metadata substeps and releases the journal on drop. |
| inputs / outputs | Indexed flag and FIFO policy; three labels hold one row, then watermark removes duplicates over three commits. |
| invariants | First two steps emit no physical output and preserve row/pending command; final step emits one erase and completes progress; drop disables journal and releases its file descriptor. |
| ownership | QuerySession owns journal lock and window state; decoded \`frames\` views borrow saved log until inspection. |
| failure | Wrong logical/physical counters, row membership, output, journal state or reopen fails. |
| cost | Three inserts and three bounded watermark steps per mode, then one drop and one journal reopen. |
| Design | tests/unit/session_journal_test.cpp:59-74, docs/session-journal.md:13-55, docs/session-journal.md:57-88, docs/journal.md:24-50, docs/journal-files.md:16-55, src/runtime/session.cpp:286-345, src/runtime/session.cpp:747-763, src/runtime/session.cpp:1449-1476, src/recovery/journal_file.cpp:231-254, tests/support/session_journal_fixture.hpp:17-40, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0005

[Lines 75–95](../../../../../tests/unit/session_journal_test.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void stream_and_resources() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify CSV decoder metadata, query-account journal allocations and exact checkpoint binding. |
| inputs / outputs | Creates offset CSV stream with reordered header, counts S04 during enable, decodes two inputs, then attempts enable against stale checkpoint. |
| invariants | Journal enable allocations equal account successful allocation deltas; persisted records retain reader bytes/records/header/permutation/source offsets; stale checkpoint cannot create a WAL or replace checkpoint. |
| ownership | Source owns input stream and session account; decoded views borrow account-funded journal decoder output only while the \`Decoded\` owner exists; saved checkpoint/log bytes are copies. |
| failure | Expected checkpoint fault is caught; allocation mismatch, wrong origin or stale file mutation fails. |
| cost | Two CSV records and two decoded journal input frames; one enable allocation sample and one stale restore/enable path. |
| Design | tests/unit/session_journal_test.cpp:75-95, docs/session-journal.md:13-55, docs/session-journal.md:57-88, docs/journal.md:24-50, docs/journal-files.md:16-55, src/runtime/session.cpp:286-345, src/runtime/session.cpp:747-763, src/runtime/session.cpp:1449-1476, src/recovery/journal_file.cpp:231-254, tests/support/session_journal_fixture.hpp:17-40, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0006

[Lines 96–116](../../../../../tests/unit/session_journal_test.cpp#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void all_stream_formats() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check source and decoder positions for all supported journaled stream encodings. |
| inputs / outputs | Two storage modes, eight shared profiles and optional seeded checkpoint row; journal records are decoded and checked for row, source offset and CSV permutation. |
| invariants | Persisted decoder bytes/record counts reflect each profile; CSV alone records header/permutation; stream progress physical and command sequence reaches 2. |
| ownership | Profile owns exact source bytes; QuerySession owns stream/journal; \`frames\` and decoded views borrow only within each iteration. |
| failure | Any missing profile position, field order, source value, or changed count fails. |
| cost | Two indexed modes times eight formats times two baseline-seed choices, at most two rows and records per source. |
| Design | tests/unit/session_journal_test.cpp:96-116, docs/session-journal.md:13-55, docs/session-journal.md:57-88, docs/journal.md:24-50, docs/journal-files.md:16-55, src/runtime/session.cpp:286-345, src/runtime/session.cpp:747-763, src/runtime/session.cpp:1449-1476, src/recovery/journal_file.cpp:231-254, tests/support/session_journal_fixture.hpp:17-40, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0007

[Lines 117–130](../../../../../tests/unit/session_journal_test.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void lifecycle() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise journal lifecycle states and reject semantic window errors before WAL admission. |
| inputs / outputs | Created, paused and stopped typed sessions plus a window command with invalid withdrawal label. |
| invariants | Created/paused sessions may enable and commit; stopped session leaves no WAL; invalid semantic command leaves only header record and does not poison recovery state. |
| ownership | Each Directory owns files; each session owns its writer lock until scope end. |
| failure | Stopped/state and invalid-window errors are checked by category; any WAL input append or recovery_required flag fails. |
| cost | Three lifecycle fixtures and one invalid-command fixture, each with at most one input. |
| Design | tests/unit/session_journal_test.cpp:117-130, docs/session-journal.md:13-55, docs/session-journal.md:57-88, docs/journal.md:24-50, docs/journal-files.md:16-55, src/runtime/session.cpp:286-345, src/runtime/session.cpp:747-763, src/runtime/session.cpp:1449-1476, src/recovery/journal_file.cpp:231-254, tests/support/session_journal_fixture.hpp:17-40, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0008

[Lines 131–140](../../../../../tests/unit/session_journal_test.cpp#L131); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void drain_and_retry() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check paused drain uses the durable journal decision and predecision allocation failure preserves retryable input. |
| inputs / outputs | Fixture offers first input, pauses and drains; then commits a second prepared input with S04 failing at the next intercepted new call. |
| invariants | Drain advances journal command/native progress but does not expose output; predecision bad_alloc leaves committed sequence unchanged, session healthy and pending input frame present; retry commits once without duplicate input. |
| ownership | Fixture retains QuerySession and cached input across retry; S04 Scope ends before subsequent checks. |
| failure | Expected first fault is bad_alloc before the durable decision; missing retry/output or wrong record count fails. |
| cost | Two inputs; one paused drain, one injected allocation attempt, then one replayed commit retry. |
| Design | tests/unit/session_journal_test.cpp:131-140, docs/session-journal.md:13-55, docs/session-journal.md:57-88, docs/journal.md:24-50, docs/journal-files.md:16-55, src/runtime/session.cpp:286-345, src/runtime/session.cpp:747-763, src/runtime/session.cpp:1449-1476, src/recovery/journal_file.cpp:231-254, tests/support/session_journal_fixture.hpp:17-40, tests/support/session_journal_stream_cases.hpp:14-115 |

## B0009

[Lines 141–141](../../../../../tests/unit/session_journal_test.cpp#L141); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L141-L141:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in session_journal_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/session_journal_test.cpp](../../../../../tests/unit/session_journal_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 142–142](../../../../../tests/unit/session_journal_test.cpp#L142); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(){try{for(const bool indexed:{false,true}){for(unsigned kind=0;kind<6;++kind)typed_case(indexed,kind);windows(indexed);for(const auto fifo:{WindowFifoPolicy::global,WindowFifoPolicy::per_relation})duplicate_expiration(indexed,fifo);}stream_and_resources();all_stream_formats();lifecycle();drain_and_retry();}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the journaled typed, window, stream-format, lifecycle and drain acceptance cases. |
| inputs / outputs | main executes two storage modes, six query kinds, both window FIFO policies, stream suites and lifecycle/retry checks. |
| invariants | This entry defines only bounded dispatch; the assertions and their limits are in the callees. |
| ownership | main owns ordering; fixtures own sessions/files/streams. |
| failure | Any standard exception prints diagnostic and returns 1. |
| cost | Two storage modes times six typed query kinds, two duplicate-expiration FIFO policies, eight stream formats, plus bounded lifecycle and drain suites. |
| Design | tests/unit/session_journal_test.cpp:142-142, docs/session-journal.md:13-55, docs/session-journal.md:57-88, docs/journal.md:24-50, docs/journal-files.md:16-55, src/runtime/session.cpp:286-345, src/runtime/session.cpp:747-763, src/runtime/session.cpp:1449-1476, src/recovery/journal_file.cpp:231-254, tests/support/session_journal_fixture.hpp:17-40, tests/support/session_journal_stream_cases.hpp:14-115 |
