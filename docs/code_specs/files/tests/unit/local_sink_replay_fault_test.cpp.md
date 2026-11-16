# `tests/unit/local_sink_replay_fault_test.cpp` — block usage map

[Source](../../../../../tests/unit/local_sink_replay_fault_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `28efefba17150063acc00ae34f8b53fa9ef79fcfcb4099fa723ae225fbe68bf0`. 89 lines partitioned into 11 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../tests/unit/local_sink_replay_fault_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 11–11](../../../../../tests/unit/local_sink_replay_fault_test.cpp#L11) | Type/record definition: enum class Channel |  · [reviewed contract](#b0002) |
| [B0003 · 12–24](../../../../../tests/unit/local_sink_replay_fault_test.cpp#L12) | Type/record definition: struct Hook | returns result; result · [reviewed contract](#b0003) |
| [B0004 · 25–28](../../../../../tests/unit/local_sink_replay_fault_test.cpp#L25) | Type/record definition: struct Installed |  · [reviewed contract](#b0004) |
| [B0005 · 29–42](../../../../../tests/unit/local_sink_replay_fault_test.cpp#L29) | Type/record definition: struct Files | guard check((actual_sink==sink \|\| actual_sink==clean_sink) && (actual_wal==wal \|\| actual_wal==clean_wal),… · [reviewed contract](#b0005) |
| [B0006 · 43–45](../../../../../tests/unit/local_sink_replay_fault_test.cpp#L43) | Callable definition: Hook trace(Files& files,Channel channel) | calls reset, installed, emplace, restore; returns hook; growth emplace · [reviewed contract](#b0006) |
| [B0007 · 46–62](../../../../../tests/unit/local_sink_replay_fault_test.cpp#L46) | Callable definition: void failures() | calls files, trace, reset, descriptors; guard check(failed && descriptors()==before,"sink-aware factory ignored file error or leaked locks");file…; 4 loop sites · [reviewed contract](#b0007) |
| [B0008 · 63–74](../../../../../tests/unit/local_sink_replay_fault_test.cpp#L63) | Callable definition: void crashes() | calls files, trace, reset, fork; guard files.reset();const auto child=::fork();check(child&gt;=0,"sink-aware crash fork failed");; 4 loop sites · [reviewed contract](#b0008) |
| [B0009 · 75–87](../../../../../tests/unit/local_sink_replay_fault_test.cpp#L75) | Callable definition: void allocations() | calls files, emplace, restore, get_deleter; guard const auto account=value-&gt;get_deleter().account();check(count==account.statistics().successful_allo…; growth emplace; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 88–88](../../../../../tests/unit/local_sink_replay_fault_test.cpp#L88) | Closes surrounding scope/type. |  · [reviewed contract](#b0010) |
| [B0011 · 89–89](../../../../../tests/unit/local_sink_replay_fault_test.cpp#L89) | Callable definition: int main(int argc,char** argv) | calls check, std::string_view, crashes, allocations; guard int main(int argc,char** argv){try{check(argc==2,"expected sink-aware fault mode");if(std::string_v…; returns 1 · [reviewed contract](#b0011) |

## B0001

[Lines 1–10](../../../../../tests/unit/local_sink_replay_fault_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:8717760f7e50a96909191edcfbf116f6b4110051289b504ee943a2fee023ade9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare local_sink_replay_fault_test.cpp: include "sink_replay_fixture.hpp", "local_sink_probe.hpp", "journal_file_probe.hpp", &lt;cerrno&gt;, &lt;sys/wait.h&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/local_sink_replay_fault_test.cpp](../../../../../tests/unit/local_sink_replay_fault_test.cpp), [docs/local-sink.md](../../../../local-sink.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 11–11](../../../../../tests/unit/local_sink_replay_fault_test.cpp#L11); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Channel {sink,journal};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select whether sink or journal-file syscalls are faulted during sink-aware restore. |
| inputs / outputs | Channel controls which probe callback is installed and which error type is expected. |
| invariants | Both channels share the same ordinal counter through Hook; only one callback is installed for a given attempt. |
| ownership | Channel is a tag; Saved owns native/sink/JOURNAL files. |
| failure | The matrices use only the two declared channels. |
| cost | Two channels per clean/torn fixture. |
| Design | tests/unit/local_sink_replay_fault_test.cpp:11-11, docs/local-sink.md:49-78, docs/local-sink.md:110-145, docs/native-replay.md:36-43, src/runtime/session.cpp:773-846, src/recovery/journal_file.cpp:199-229, src/recovery/local_sink.cpp:191-229, tests/support/sink_replay_fixture.hpp:6-42, tests/support/local_sink_probe.hpp:1-11, tests/support/journal_file_probe.hpp:1-17, tests/support/index_allocation.hpp:11-70 |

## B0003

[Lines 12–24](../../../../../tests/unit/local_sink_replay_fault_test.cpp#L12); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Hook {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe either actual sink or journal file I/O and synthesize bounded transfer, EINTR, EIO, or child exit. |
| inputs / outputs | A channel-specific Event plus borrowed Hook; returns correct Decision/FileDecision. |
| invariants | Before events increment the shared ordinal; \`maximum\` constrains read/write; synthetic interrupt applies only to read_data; selected fail side can be before or after. |
| ownership | Hook is borrowed under Installed; FileEvent values are not retained. |
| failure | Callbacks are noexcept; component failure carriers remain sk::Failure or jp::FileFailure. |
| cost | Constant scalar operations per boundary; no allocator count is implied. |
| Design | tests/unit/local_sink_replay_fault_test.cpp:12-24, docs/local-sink.md:49-78, docs/local-sink.md:110-145, docs/native-replay.md:36-43, src/runtime/session.cpp:773-846, src/recovery/journal_file.cpp:199-229, src/recovery/local_sink.cpp:191-229, tests/support/sink_replay_fixture.hpp:6-42, tests/support/local_sink_probe.hpp:1-11, tests/support/journal_file_probe.hpp:1-17, tests/support/index_allocation.hpp:11-70 |

## B0004

[Lines 25–28](../../../../../tests/unit/local_sink_replay_fault_test.cpp#L25); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Installed {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install a hook on exactly one selected file channel and clear both possible channels on scope exit. |
| inputs / outputs | Channel and Hook in; selects sink or journal callback. |
| invariants | This does not preserve nested hook values; both setters are reset to null on destruction. |
| ownership | Installed borrows Hook for the full recovery call; caller owns channel and fixture. |
| failure | No custom failure mapping. |
| cost | One selected setter plus two clear calls. |
| Design | tests/unit/local_sink_replay_fault_test.cpp:25-28, docs/local-sink.md:49-78, docs/local-sink.md:110-145, docs/native-replay.md:36-43, src/runtime/session.cpp:773-846, src/recovery/journal_file.cpp:199-229, src/recovery/local_sink.cpp:191-229, tests/support/sink_replay_fixture.hpp:6-42, tests/support/local_sink_probe.hpp:1-11, tests/support/journal_file_probe.hpp:1-17, tests/support/index_allocation.hpp:11-70 |

## B0005

[Lines 29–42](../../../../../tests/unit/local_sink_replay_fault_test.cpp#L29); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Files {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare clean or torn sink and journal files with a saved generation fixture. |
| inputs / outputs | Torn toggle selects a two-epoch prefix and optionally appends 85 bytes from the next sink/WAL frame; clean and test copies are retained. |
| invariants | intact() permits only the original torn files or the fully repaired clean files; this is a prefix check, not semantic proof by itself. |
| ownership | Saved owns query program and directory; four strings own independent byte snapshots; reset rewrites both paths. |
| failure | Truncated setup frame or unexpected bytes fails fixture checks; saved.verify adds native/output validation. |
| cost | One restore of three source changes, copies two complete files and optionally one 85-byte suffix; fixed three-epoch scenario. |
| Design | tests/unit/local_sink_replay_fault_test.cpp:29-42, docs/local-sink.md:49-78, docs/local-sink.md:110-145, docs/native-replay.md:36-43, src/runtime/session.cpp:773-846, src/recovery/journal_file.cpp:199-229, src/recovery/local_sink.cpp:191-229, tests/support/sink_replay_fixture.hpp:6-42, tests/support/local_sink_probe.hpp:1-11, tests/support/journal_file_probe.hpp:1-17, tests/support/index_allocation.hpp:11-70 |

## B0006

[Lines 43–45](../../../../../tests/unit/local_sink_replay_fault_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Hook trace(Files& files,Channel channel) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count baseline I/O calls for sink-aware factory reconstruction on one channel. |
| inputs / outputs | Files fixture and Channel in; resets files and runs restore with Hook installed; returns count. |
| invariants | Baseline includes actual open/validation/replay operations for that channel and fixture state; it performs no intentional sink/WAL repair until factory policy permits. |
| ownership | Temporary restored owner dies before return; Hook is destroyed only after Installed clears callback. |
| failure | File or native restore errors stop baseline collection. |
| cost | One whole sink-aware recovery for a clean or torn two-epoch prefix. |
| Design | tests/unit/local_sink_replay_fault_test.cpp:43-45, docs/local-sink.md:49-78, docs/local-sink.md:110-145, docs/native-replay.md:36-43, src/runtime/session.cpp:773-846, src/recovery/journal_file.cpp:199-229, src/recovery/local_sink.cpp:191-229, tests/support/sink_replay_fixture.hpp:6-42, tests/support/local_sink_probe.hpp:1-11, tests/support/journal_file_probe.hpp:1-17, tests/support/index_allocation.hpp:11-70 |

## B0007

[Lines 46–62](../../../../../tests/unit/local_sink_replay_fault_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void failures() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject before/after failures across both file channels and verify neither premature repair nor leaked owner escapes. |
| inputs / outputs | Clean/torn toggle and channel choose each observed boundary/side; a fresh restore must fail with the matching carrier. |
| invariants | Short read cap is accepted; repeated EINTR exhausts that copied channel quota without changing source files; successful later saved.verify reopens and checks native state/output. |
| ownership | Temporary QuerySession owners and file locks are released by failed factory unwinding; descriptor count is compared around each attempt. |
| failure | Expected carrier is channel specific; file bytes may be unchanged or repaired only on normal successful restart, never by the failing attempt. |
| cost | Two torn states times two channels times two sides per baseline boundary, plus short-I/O and finite-interrupt case per channel. |
| Design | tests/unit/local_sink_replay_fault_test.cpp:46-62, docs/local-sink.md:49-78, docs/local-sink.md:110-145, docs/native-replay.md:36-43, src/runtime/session.cpp:773-846, src/recovery/journal_file.cpp:199-229, src/recovery/local_sink.cpp:191-229, tests/support/sink_replay_fixture.hpp:6-42, tests/support/local_sink_probe.hpp:1-11, tests/support/journal_file_probe.hpp:1-17, tests/support/index_allocation.hpp:11-70 |

## B0008

[Lines 63–74](../../../../../tests/unit/local_sink_replay_fault_test.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void crashes() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Terminate child recovery at each sink or WAL syscall and verify parent recovery. |
| inputs / outputs | Torn toggle, channel, observed boundary and side; child restores; parent waits for exit 77 and calls saved.verify. |
| invariants | Accepted post-crash bytes are only the saved or complete repaired prefixes; process exits do not model power loss. |
| ownership | Child's partial owner is process-local; parent owns Saved and checks its immutable target bytes before/after restart. |
| failure | Fork/wait failure, wrong crash ordinal or changed complete prefix fails. |
| cost | Two tail states times two channels and two sides for every baseline event; one bounded parent verification per point. |
| Design | tests/unit/local_sink_replay_fault_test.cpp:63-74, docs/local-sink.md:49-78, docs/local-sink.md:110-145, docs/native-replay.md:36-43, src/runtime/session.cpp:773-846, src/recovery/journal_file.cpp:199-229, src/recovery/local_sink.cpp:191-229, tests/support/sink_replay_fixture.hpp:6-42, tests/support/local_sink_probe.hpp:1-11, tests/support/journal_file_probe.hpp:1-17, tests/support/index_allocation.hpp:11-70 |

## B0009

[Lines 75–87](../../../../../tests/unit/local_sink_replay_fault_test.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void allocations() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail every intercepted allocation during sink-aware construction and test receiving-account limits. |
| inputs / outputs | A successful restore counts S04 replacement-new attempts and captures account peak; each position repeats restore under fault; exact and one-under caps bracket success. |
| invariants | The counter is C++ new-call count, not bytes; equality with account successful allocations is asserted only for the clean successful restore; one-under account cap must reject with MemoryFailure. |
| ownership | Receiving QuerySession owns its MemoryAccount and sink/WAL locks; each temporary result is destroyed before checking file/descriptor stability. |
| failure | Each selected allocation must throw bad_alloc with files unchanged; exact peak succeeds and one byte below peak rejects. |
| cost | One counted restore, one retry per intercepted new position, and two cap-edge restores of the same small native fixture. |
| Design | tests/unit/local_sink_replay_fault_test.cpp:75-87, docs/local-sink.md:49-78, docs/local-sink.md:110-145, docs/native-replay.md:36-43, src/runtime/session.cpp:773-846, src/recovery/journal_file.cpp:199-229, src/recovery/local_sink.cpp:191-229, tests/support/sink_replay_fixture.hpp:6-42, tests/support/local_sink_probe.hpp:1-11, tests/support/journal_file_probe.hpp:1-17, tests/support/index_allocation.hpp:11-70 |

## B0010

[Lines 88–88](../../../../../tests/unit/local_sink_replay_fault_test.cpp#L88); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L88-L88:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in local_sink_replay_fault_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/local_sink_replay_fault_test.cpp](../../../../../tests/unit/local_sink_replay_fault_test.cpp), [docs/local-sink.md](../../../../local-sink.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 89–89](../../../../../tests/unit/local_sink_replay_fault_test.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv){try{check(argc==2,"expected sink-aware fault mode");if(std::string_view(argv[1])=="crash")crashes();else{allocations();failures();}}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch child crash mode or combined allocation/error checks. |
| inputs / outputs | Exactly one mode argument chooses \`crashes\`; other values run allocations and failures. |
| invariants | The wrapper itself adds no acceptance beyond inner assertions. |
| ownership | main does not own the Saved fixture. |
| failure | Wrong argc or standard exception reports exit status 1. |
| cost | One bounded fault suite selected by the mode argument. |
| Design | tests/unit/local_sink_replay_fault_test.cpp:89-89, docs/local-sink.md:49-78, docs/local-sink.md:110-145, docs/native-replay.md:36-43, src/runtime/session.cpp:773-846, src/recovery/journal_file.cpp:199-229, src/recovery/local_sink.cpp:191-229, tests/support/sink_replay_fixture.hpp:6-42, tests/support/local_sink_probe.hpp:1-11, tests/support/journal_file_probe.hpp:1-17, tests/support/index_allocation.hpp:11-70 |
