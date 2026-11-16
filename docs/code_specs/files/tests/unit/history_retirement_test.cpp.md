# `tests/unit/history_retirement_test.cpp` — block usage map

[Source](../../../../../tests/unit/history_retirement_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `49fff89cb529276e2ade5e4dd1496432b7cdb020d916477fde5eedd2605c3765`. 105 lines partitioned into 11 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../tests/unit/history_retirement_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 8–15](../../../../../tests/unit/history_retirement_test.cpp#L8) | Callable definition: void typed_case(bool indexed,unsigned kind) | calls f, generation_state, local_sink_state, contents; guard check(after.selected==expected && !after.retirement_pending && f.session-&gt;local_sink_state().persis… · [reviewed contract](#b0002) |
| [B0003 · 16–22](../../../../../tests/unit/history_retirement_test.cpp#L16) | Callable definition: void retention_reuse() | calls rotate_generation, fault, check, retire_generation_history; guard RetirementFixture f;bool capped=false;try{f.session-&gt;rotate_generation();}catch(const recovery::Gen… · [reviewed contract](#b0003) |
| [B0004 · 23–33](../../../../../tests/unit/history_retirement_test.cpp#L23) | Callable definition: void stream_case(bool indexed,const session_journal_stream_test::Case& profile,bool pending) | calls typed::fixture, file, QuerySession::create, start; guard check(source-&gt;begin_next(),"retirement first stream input absent");finish(*source);static_cast&lt;void…; growth insert, make_unique · [reviewed contract](#b0004) |
| [B0005 · 34–44](../../../../../tests/unit/history_retirement_test.cpp#L34) | Callable definition: void window_case(bool indexed,WindowFifoPolicy fifo,unsigned cut) | calls file, window::plan, QuerySession::create_windowed, window::config; guard for(std::uint64_t i=1;i&lt;=3;++i){typed::enqueue(*source,io::WindowCommand{i,io::WindowInsert{i,Table…; 2 loop sites · [reviewed contract](#b0005) |
| [B0006 · 45–55](../../../../../tests/unit/history_retirement_test.cpp#L45) | Callable definition: void gates() | calls rotate_generation, contents, retire_generation_history, check; guard try{plain.session-&gt;retire_generation_history();}catch(const Error&){rejected=true;}check(rejected &… · [reviewed contract](#b0006) |
| [B0007 · 56–76](../../../../../tests/unit/history_retirement_test.cpp#L56) | Callable definition: void pending_and_hostile() | calls wire, intent, contents, path; guard try{auto value=f.restore();}catch(const std::exception&){rejected=true;}check(rejected && descripto…; 3 loop sites · [reviewed contract](#b0007) |
| [B0008 · 77–82](../../../../../tests/unit/history_retirement_test.cpp#L77) | Callable definition: void wire_golden(const char* path) | calls contents, check, push_back, size; guard const auto text=contents(path);std::string bytes;int high=-1;for(const char c:text){if(c=='\n' \|\| c…; growth push_back; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 83–103](../../../../../tests/unit/history_retirement_test.cpp#L83) | Callable definition: void checkpoint_delivery_binding(const char* golden_path) | calls contents, path, generation_state, check; guard check(root.size()==324 && selected.delivery.has_value() && selected.delivery-&gt;sequence==2 && f.sess…; growth push_back; 5 loop sites · [reviewed contract](#b0009) |
| [B0010 · 104–104](../../../../../tests/unit/history_retirement_test.cpp#L104) | Closes surrounding scope/type. |  · [reviewed contract](#b0010) |
| [B0011 · 105–105](../../../../../tests/unit/history_retirement_test.cpp#L105) | Callable definition: int main(int argc,char** argv) | calls check, typed_case, session_journal_stream_test::cases, stream_case; guard int main(int argc,char** argv){try{check(argc==3,"expected retirement intent and delivery-root gold…; returns 1; 6 loop sites · [reviewed contract](#b0011) |

## B0001

[Lines 1–7](../../../../../tests/unit/history_retirement_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:f3c8b397de3d249663d5800c43edd93ca009e9bc197061a0961e823934281df7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare history_retirement_test.cpp: include "history_retirement_fixture.hpp", "session_journal_stream_cases.hpp", "crown/api/error.hpp"; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/history_retirement_test.cpp](../../../../../tests/unit/history_retirement_test.cpp), [docs/history-retirement.md](../../../../history-retirement.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 8–15](../../../../../tests/unit/history_retirement_test.cpp#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void typed_case(bool indexed,unsigned kind) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retire history after accepted typed output for each plan and storage mode, then reopen and continue. |
| inputs / outputs | Indexed flag and query kind select RetirementFixture; snapshots compare root selection, selected pair, sink and independent relation oracle. |
| invariants | Retirement advances only the retained floor to generation 3, leaves selected checkpoint/WAL and sink bytes unchanged, is idempotent, and bare recovery of the surviving selected pair retains native state. |
| ownership | Fixture owns directory/session/program and copies accepted sink/output bytes; recovered owners are scoped separately. |
| failure | Unexpected deletion, changed output, failed bare recovery or wrong next update trips a check; this does not test syscall crash boundaries. |
| cost | Six query kinds times two storage modes, with three committed/delivered epochs and one post-retirement update each. |
| Design | tests/unit/history_retirement_test.cpp:8-15, docs/history-retirement.md:1-21, docs/history-retirement.md:22-58, docs/history-retirement.md:60-89, src/runtime/session.cpp:1024-1090, src/recovery/generation_retirement.cpp:51-73, src/recovery/generation_retirement.cpp:111-135, tests/support/history_retirement_fixture.hpp:6-41, docs/native-replay.md:45-67 |

## B0003

[Lines 16–22](../../../../../tests/unit/history_retirement_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void retention_reuse() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Show that retirement frees one bounded retained-pair slot without changing sink origin. |
| inputs / outputs | A three-generation fixture first reaches the configured rotation cap; retirement and a subsequent rotation update the root floor. |
| invariants | First retirement permits generation 4 while keeping origin at 3; second retirement deletes only generation-3 checkpoint/WAL; subsequent epoch is identified as generation 4. |
| ownership | RetirementFixture owns all generation files and sink; output is delivered before the second retirement check. |
| failure | A rotation that is not capped, wrong deletion range, changed output generation, or failed post-retirement delivery fails the case. |
| cost | Two retirement operations, one capped and one successful rotation, then one committed/delivered epoch. |
| Design | tests/unit/history_retirement_test.cpp:16-22, docs/history-retirement.md:1-21, docs/history-retirement.md:22-58, docs/history-retirement.md:60-89, src/runtime/session.cpp:1024-1090, src/recovery/generation_retirement.cpp:51-73, src/recovery/generation_retirement.cpp:111-135, tests/support/history_retirement_fixture.hpp:6-41, docs/native-replay.md:45-67 |

## B0004

[Lines 23–33](../../../../../tests/unit/history_retirement_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void stream_case(bool indexed,const session_journal_stream_test::Case& profile,bool pending) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise retirement after stream continuation with and without a cached pending input. |
| inputs / outputs | Indexed flag, one of the shared stream profiles and pending toggle; recovery receives original seekable stream and sink path. |
| invariants | Pending stream input blocks retirement while generation-1 WAL remains; after completion the retired restore preserves CSV/header byte/record counters, delivered epoch and EOF without duplicate input. |
| ownership | The source session owns the original stream until reset; recovery receives a newly owned istringstream; profile owns its input bytes. |
| failure | Retirement admission, source seek, native replay, sink binding or output mismatch fails; coverage is the shared profile list and fixture's selected stream traces. |
| cost | One initial and one post-rotation stream row, optional pending attempt, sink delivery, and a full root/journal/sink recovery per profile. |
| Design | tests/unit/history_retirement_test.cpp:23-33, docs/history-retirement.md:1-21, docs/history-retirement.md:22-58, docs/history-retirement.md:60-89, src/runtime/session.cpp:1024-1090, src/recovery/generation_retirement.cpp:51-73, src/recovery/generation_retirement.cpp:111-135, tests/support/history_retirement_fixture.hpp:6-41, docs/native-replay.md:45-67 |

## B0005

[Lines 34–44](../../../../../tests/unit/history_retirement_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void window_case(bool indexed,WindowFifoPolicy fifo,unsigned cut) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise retirement around private and partial watermark work for both FIFO policies. |
| inputs / outputs | Indexed storage, FIFO policy and cut position choose a three-label fixture and the number of committed metadata substeps before retirement. |
| invariants | Private watermark and incomplete metadata command reject retirement; final state retains physical sequence 2 versus command progress 4, sink stores only two physical epochs, and resumed deletion/next insert match expected rows. |
| ownership | QuerySession and queue own window state; generated WindowCommand values are queued by value; sink retains durable physical output. |
| failure | Any early retirement, changed active command, duplicated/lost deletion, or incorrect generation on next output fails assertions. |
| cost | Three inserts plus three watermark substeps across each cut; two FIFO policies, two storage modes and four cut positions. |
| Design | tests/unit/history_retirement_test.cpp:34-44, docs/history-retirement.md:1-21, docs/history-retirement.md:22-58, docs/history-retirement.md:60-89, src/runtime/session.cpp:1024-1090, src/recovery/generation_retirement.cpp:51-73, src/recovery/generation_retirement.cpp:111-135, tests/support/history_retirement_fixture.hpp:6-41, docs/native-replay.md:45-67 |

## B0006

[Lines 45–55](../../../../../tests/unit/history_retirement_test.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void gates() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify that reports, output consumption, private work and damaged checkpoints cannot authorize retirement. |
| inputs / outputs | Four independent fixtures try plain generation output, undelivered output, edited generation report/private fan-out, and corrupt selected checkpoint. |
| invariants | A mutable state report has no authority; no sink or fully accepted epoch, active private work, or selected checkpoint mismatch leaves root and old files intact and creates no intent. |
| ownership | Each block owns a fresh fixture; copied report/root/sink bytes are observer values, not authority objects. |
| failure | Expected generic state errors or ImageFailure are caught locally; a missing rejection or any mutation fails the test. |
| cost | Four finite fixtures, each with one retirement attempt; the output case then delivers and retires successfully as its positive control. |
| Design | tests/unit/history_retirement_test.cpp:45-55, docs/history-retirement.md:1-21, docs/history-retirement.md:22-58, docs/history-retirement.md:60-89, src/runtime/session.cpp:1024-1090, src/recovery/generation_retirement.cpp:51-73, src/recovery/generation_retirement.cpp:111-135, tests/support/history_retirement_fixture.hpp:6-41, docs/native-replay.md:45-67 |

## B0007

[Lines 56–76](../../../../../tests/unit/history_retirement_test.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void pending_and_hostile() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject hostile retirement intents before repair, then resume cleanup only from the recorded floor. |
| inputs / outputs | A captured intent is truncated at every byte, bit-flipped, extended, checksum-recomputed at selected bindings, and paired with torn sink/WAL tails or interrupted cleanup. |
| invariants | Invalid/mismatched intent keeps root/sink/WAL bytes and descriptors unchanged; bare recovery rejects pending intent; sink-aware recovery checks intent/sink/root authority before repairing either tail and never deletes an unrecorded generation-4 sentinel. |
| ownership | RetirementFixture owns paths; \`reject\` writes a candidate intent and separately tracks descriptor count and durable bytes; captured vectors/strings are observer copies. |
| failure | All hostile cases must reject via an exception; valid interrupted cleanup is accepted only by sink-aware restore and then removes the exact old range. |
| cost | 724-byte intent's every prefix cut and bit flip, 15 selected rechecksummed offsets, one invalid version, two torn tails, and one valid cleanup continuation; these are bounded byte-wise fixture loops. |
| Design | tests/unit/history_retirement_test.cpp:56-76, docs/history-retirement.md:1-21, docs/history-retirement.md:22-58, docs/history-retirement.md:60-89, src/runtime/session.cpp:1024-1090, src/recovery/generation_retirement.cpp:51-73, src/recovery/generation_retirement.cpp:111-135, tests/support/history_retirement_fixture.hpp:6-41, docs/native-replay.md:45-67 |

## B0008

[Lines 77–82](../../../../../tests/unit/history_retirement_test.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void wire_golden(const char* path) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode an independent hex fixture and compare the native retirement-intent wire round trip. |
| inputs / outputs | A text-file path in; decoded byte string, SHA256 and inspected native fields checked against fixed golden expectations. |
| invariants | Whitespace is ignored only while parsing hex; expected format length is 724 bytes and native encode/decode round trips exactly. |
| ownership | Input bytes are owned by local strings; the test-only inspect helper returns a value, not authority to retire a live root. |
| failure | Invalid hex, odd nibble count, wrong hash/fields or nonidentical encoding fails an assertion. |
| cost | One bounded golden byte vector and a linear hex decode/hash/inspect pass. |
| Design | tests/unit/history_retirement_test.cpp:77-82, docs/history-retirement.md:1-21, docs/history-retirement.md:22-58, docs/history-retirement.md:60-89, src/runtime/session.cpp:1024-1090, src/recovery/generation_retirement.cpp:51-73, src/recovery/generation_retirement.cpp:111-135, tests/support/history_retirement_fixture.hpp:6-41, docs/native-replay.md:45-67 |

## B0009

[Lines 83–103](../../../../../tests/unit/history_retirement_test.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void checkpoint_delivery_binding(const char* golden_path) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove checkpoint-root delivery binding with a separately calculated frame chain and hostile restart variants. |
| inputs / outputs | A live retirement fixture, root and sink bytes, and independent root golden; tests forged old epoch, v1 legacy root, every root cut/bit flip and read-only reopen. |
| invariants | The digest chains protected-header checksums through the checkpoint sequence; a checksum-valid changed old output cannot pass sink-aware restore or two-step attachment; legacy unanchored old output cannot retire/rotate; root decode and exact 324-byte independent vector are checked. |
| ownership | Fixture file bytes, local chain buffer and copied receipts are observer values; actual authority stays inside QuerySession and the root/sink owners. |
| failure | Binding, generation, or image failures are expected in hostile cases; descriptor and original bytes must survive; good root is restored before final fixture verify. |
| cost | Three sink frames plus one next frame for chain/reopen; 324 root prefixes and bit flips; one legacy case and one exact golden hash. |
| Design | tests/unit/history_retirement_test.cpp:83-103, docs/history-retirement.md:1-21, docs/history-retirement.md:22-58, docs/history-retirement.md:60-89, src/runtime/session.cpp:1024-1090, src/recovery/generation_retirement.cpp:51-73, src/recovery/generation_retirement.cpp:111-135, tests/support/history_retirement_fixture.hpp:6-41, docs/native-replay.md:45-67 |

## B0010

[Lines 104–104](../../../../../tests/unit/history_retirement_test.cpp#L104); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L104-L104:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in history_retirement_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/history_retirement_test.cpp](../../../../../tests/unit/history_retirement_test.cpp), [docs/history-retirement.md](../../../../history-retirement.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 105–105](../../../../../tests/unit/history_retirement_test.cpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv){try{check(argc==3,"expected retirement intent and delivery-root goldens");const Catalog catalog{5,{{"e",{{"x",ScalarType::int64},{"y",ScalarType::int64}}}}};for(const bool indexed:{false,true}){for(unsigned kind=0;kind<6;++kind)typed_case(indexed,kind);for(const auto& profile:session_journal_stream_test::cases(catalog))for(const bool pending:{false,true})stream_case(indexed,profile,pending);for(const auto fifo:{WindowFifoPolicy::global,WindowFifoPolicy::per_relation})for(unsigned cut=0;cut<4;++cut)window_case(indexed,fifo,cut);}retention_reuse();gates();pending_and_hostile();wire_golden(argv[1]);checkpoint_delivery_binding(argv[2]);}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the fixed retirement, stream, window, hostility and golden case matrices. |
| inputs / outputs | Two CLI golden paths are required; main iterates storage/query/stream/window profiles before singular retention/gate/wire checks. |
| invariants | The wrapper defines the total profile set but assertions live in callees; no runtime result is claimed by this documentation card. |
| ownership | main owns dispatch only; every fixture and owned source stream lives in its callee. |
| failure | Wrong argc or any exception reports failure with status 1. |
| cost | Two storage modes times six query kinds, all shared stream profiles and pending flags, two FIFO modes and four cuts, plus bounded singleton suites. |
| Design | tests/unit/history_retirement_test.cpp:105-105, docs/history-retirement.md:1-21, docs/history-retirement.md:22-58, docs/history-retirement.md:60-89, src/runtime/session.cpp:1024-1090, src/recovery/generation_retirement.cpp:51-73, src/recovery/generation_retirement.cpp:111-135, tests/support/history_retirement_fixture.hpp:6-41, docs/native-replay.md:45-67 |
