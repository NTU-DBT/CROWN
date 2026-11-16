# `tests/unit/session_image_test.cpp` — block usage map

[Source](../../../../../tests/unit/session_image_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `0d776ab6e0e1a198a52a07a2b8f6d61cbfa80fe0241ecd4b12802dad5e423eb5`. 283 lines partitioned into 15 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../tests/unit/session_image_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 13–13](../../../../../tests/unit/session_image_test.cpp#L13) | Callable definition: std::string_view bytes(const recovery::SessionImage& value) | calls data, size; returns {value.bytes.data(),value.bytes.size()} · [reviewed contract](#b0002) |
| [B0003 · 14–63](../../../../../tests/unit/session_image_test.cpp#L14) | Callable definition: void typed_case(bool indexed,unsigned kind,SessionState control) | calls typed::fixture, CompiledProgram::standalone, QuerySession::create_typed, get_deleter; guard check(captures==original.statistics().successful_allocations-before.successful_allocations,"binary …; growth resize; 4 loop sites · [reviewed contract](#b0003) |
| [B0004 · 64–91](../../../../../tests/unit/session_image_test.cpp#L64) | Callable definition: void stream_case(bool indexed,io::InputFormat format) | calls typed::fixture, CompiledProgram::standalone, io::write_input_json, source_catalog; guard source-&gt;start();check(source-&gt;begin_next(),"binary stream fixture missing");typed::finish(*source);…; growth emplace, make_unique · [reviewed contract](#b0004) |
| [B0005 · 92–106](../../../../../tests/unit/session_image_test.cpp#L92) | Callable definition: void window_case(bool indexed,WindowFifoPolicy fifo,SessionState control) | calls window::plan, CompiledProgram::standalone, QuerySession::create_windowed, window::config; guard check(target-&gt;status().state==control && target-&gt;window_state()==source-&gt;window_state() && target-&gt;… · [reviewed contract](#b0005) |
| [B0006 · 107–132](../../../../../tests/unit/session_image_test.cpp#L107) | Callable definition: void golden(const char* path) | calls resource::MemoryAccount::create, io::AccountedInputOptions, io::AccountedInputProgress, fill; guard std::ifstream file(path);std::string expected;file&gt;&gt;expected;check(expected.size()==2*image.bytes.s…; returns c&gt;=@ && c&lt;=@ ?static_cast&lt;unsigned&gt;(c-@ ):static_cast&lt;unsigned&gt;(c-@ +10); growth copy_of; 3 loop sites; source comment (unverified): // Construct policy independently from the encoder, using the public defaults. · [reviewed contract](#b0006) |
| [B0007 · 133–135](../../../../../tests/unit/session_image_test.cpp#L133) | Callable definition: void reseal(recovery::SessionImage& image) | calls sha256_fixed, bytes, substr, std::copy · [reviewed contract](#b0007) |
| [B0008 · 136–138](../../../../../tests/unit/session_image_test.cpp#L136) | Callable definition: void word(recovery::SessionImage& image,std::size_t position,std::uint64_t value) | calls ; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 139–142](../../../../../tests/unit/session_image_test.cpp#L139) | Callable definition: template&lt;class Action&gt; void preflight_failure(Action action) | calls deny, action, check; guard check(failed && s04_alloc::calls==0,"malformed/limited binary session was not rejected before alloc… · [reviewed contract](#b0009) |
| [B0010 · 143–178](../../../../../tests/unit/session_image_test.cpp#L143) | Callable definition: void corruptions_and_limits() | calls typed::fixture, CompiledProgram::standalone, QuerySession::create_typed, start; guard check(rejected && typed::rows(*source)==Relation{{Row{std::int64_t{1}}}},"valid wrong binding admit…; growth make_unique, resize; 3 loop sites; source comment (unverified): // The fixed-width prefix offsets are derived independently from the documented · [reviewed contract](#b0010) |
| [B0011 · 179–217](../../../../../tests/unit/session_image_test.cpp#L179) | Callable definition: void lifetime_csv_and_scalars(bool indexed) | calls typed::fixture, CompiledProgram::standalone, QuerySession::create, get_deleter; guard source-&gt;start();check(source-&gt;begin_next(),"CSV permutation fixture missing");typed::finish(*source…; growth make_unique; source comment (unverified): // The native component boundary accepts raw scalar bytes. Text input adapters · [reviewed contract](#b0011) |
| [B0012 · 218–243](../../../../../tests/unit/session_image_test.cpp#L218) | Callable definition: void barriers_and_failed_source(bool indexed) | calls typed::fixture, QuerySession::create_typed, typed::enqueue, typed::rejected; guard source-&gt;start();check(source-&gt;begin_next(),"binary busy fixture missing");typed::rejected(\[&\]{auto …; growth make_unique; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 244–269](../../../../../tests/unit/session_image_test.cpp#L244) | Callable definition: void encoder_consistency() | calls typed::fixture, QuerySession::create_typed, get_deleter, account; 2 loop sites · [reviewed contract](#b0013) |
| [B0014 · 270–270](../../../../../tests/unit/session_image_test.cpp#L270) | Closes surrounding scope/type. |  · [reviewed contract](#b0014) |
| [B0015 · 271–283](../../../../../tests/unit/session_image_test.cpp#L271) | Callable definition: int main(int argc,char** argv) | calls check, golden, corruptions_and_limits, encoder_consistency; guard check(argc==2,"session fixture path required");golden(argv\[1\]);corruptions_and_limits();encoder_con…; returns 1; 6 loop sites · [reviewed contract](#b0015) |

## B0001

[Lines 1–12](../../../../../tests/unit/session_image_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L12:sha256:be9ac5a50c6dee83f258926866193ab2c37f7f171678f5257ee40b69459f7f05
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare session_image_test.cpp: include "crown/recovery/session_image.hpp", "crown/ir/digest.hpp", "session_checkpoint_test_fixture.hpp", "window_checkpoint_test_fixture.hpp", &lt;fstream&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/session_image_test.cpp](../../../../../tests/unit/session_image_test.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 13–13](../../../../../tests/unit/session_image_test.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view bytes(const recovery::SessionImage& value){return {value.bytes.data(),value.bytes.size()};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the funded SessionImage byte vector as a non-owning view for inspection and restore calls. |
| inputs / outputs | SessionImage in; string_view over its bytes out. |
| invariants | The view is valid only while the image and its byte storage remain alive and unmodified. |
| ownership | Borrows image storage; performs no byte copy or allocation. |
| failure | No failure path is added; callers must not retain the view past the image lifetime. |
| cost | Constant-time pointer/length construction; no byte scan. |
| Design | [tests/unit/session_image_test.cpp § std::string_view bytes(const recovery::SessionImage& value) (lines 13-13)](../../../../../tests/unit/session_image_test.cpp), [include/crown/recovery/session_image.hpp § SessionImage (lines 18-25)](../../../../../include/crown/recovery/session_image.hpp) |

## B0003

[Lines 14–63](../../../../../tests/unit/session_image_test.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void typed_case(bool indexed,unsigned kind,SessionState control) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare a live typed session with a restored binary image across native state, account attribution, bounded allocation faults, and continuation. |
| inputs / outputs | Inputs: backend flag, fixture kind 0..5, and created/running/paused/stopped state. Builds one source and restored session; checks status, progress, rows, policy, next deltas, and EOF. |
| invariants | Only kind 1 in running state receives allocation sweeps, calibrated from successful capture/restore calls. The exact restore cap is the measured receiving-account peak, with one byte less rejected. typed::grant checks the single indexed admission grant only in the CROWN_RUNTIME_TESTING executable; it is a no-op in the ordinary executable. |
| ownership | Source and restored owners use their own query accounts; SessionImage owns funded bytes; expected exported rows and copied Database are ordinary test values. |
| failure | Each calibrated capture cut must throw bad_alloc and preserve original current usage, progress and rows. Each restore cut must throw bad_alloc and preserve original current usage and rows; that loop does not recheck source progress. A one-byte-under receiving cap must report MemoryFault::limit. |
| cost | Capture/restore counters are per invocation. Five repeat captures compare bytes and account current usage; the function does not bound wall time or all allocations outside s04_alloc. |
| Design | [tests/unit/session_image_test.cpp § void typed_case(bool indexed,unsigned kind,SessionState control) (lines 14-63)](../../../../../tests/unit/session_image_test.cpp), [src/runtime/session.cpp § checkpoint and restore_image (lines 1153-1207)](../../../../../src/runtime/session.cpp), [tests/support/index_allocation.hpp § replacement new/delete and nonnested thread-local Scope (lines 11-70)](../../../../../tests/support/index_allocation.hpp), [tests/support/session_checkpoint_test_fixture.hpp § grant, rows, finish, fixture and step (lines 20-113)](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [docs/verification/o04-session-image-native-2026-11-10.md § Implementation (lines 8-32)](../../../../verification/o04-session-image-native-2026-11-10.md) |

## B0004

[Lines 64–91](../../../../../tests/unit/session_image_test.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void stream_case(bool indexed,io::InputFormat format) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify that an owned-stream checkpoint resumes from a caller-supplied continuation after restoring each exercised input codec. |
| inputs / outputs | Inputs: backend and one of eight JSONL, binary, CSV, or legacy formats; creates a two-record stream, captures after record one, and supplies the second record as continuation. |
| invariants | The source has a two-record limit and a total-byte limit equal to the fixture payload; tested state is paused at the first committed record, then EOF, then stopped. This covers only these fixture bytes and formats. |
| ownership | Source and restored sessions own their readers; image bytes own a separate copy. Input strings and copied row expectations are ordinary test storage. |
| failure | Assertions reject missing records, mismatched progress/results, extra EOF input, or lost stopped state; codec/restore exceptions propagate to main. |
| cost | Builds a two-record payload and performs three capture/restore pairs: paused continuation, EOF with extra supplied bytes, and stopped without a stream. It consumes only the two intended input records; no throughput measurement is made. |
| Design | [tests/unit/session_image_test.cpp § void stream_case(bool indexed,io::InputFormat format) (lines 64-91)](../../../../../tests/unit/session_image_test.cpp), [src/runtime/session.cpp § checkpoint and restore_image (lines 1153-1207)](../../../../../src/runtime/session.cpp), [tests/support/session_checkpoint_test_fixture.hpp § finish and fixture (lines 39-93)](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [docs/verification/o04-session-image-native-2026-11-10.md § Implementation (lines 8-32)](../../../../verification/o04-session-image-native-2026-11-10.md) |

## B0005

[Lines 92–106](../../../../../tests/unit/session_image_test.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void window_case(bool indexed,WindowFifoPolicy fifo,SessionState control) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare restored window-session state and two subsequent commands with the original session. |
| inputs / outputs | Inputs: backend, FIFO policy, and created/running/paused/stopped control. Captures a SessionImage and restores with the matching standalone compiler plan. |
| invariants | Non-created controls are seeded before capture. Created source and target are seeded after restore when started. Every non-stopped case compares watermark 6 and insertion 7, then rows/window state; command outputs are signed-set unions across subepochs, so their equality does not count repeated identical output across subepochs. |
| ownership | Each session owns its runtime and window controller; the image owns its encoded bytes; exported result comparisons are test copies. |
| failure | A mismatch throws through check; image/restore or command failures propagate to main. The finite fixture does not cover arbitrary window histories. |
| cost | One capture/restore per selected backend/FIFO/control. Non-stopped cases run two continuation commands on each session; created cases additionally run the five-command seed on each after restore. Step and command helpers run until completion without a numeric loop guard. |
| Design | [tests/unit/session_image_test.cpp § void window_case(bool indexed,WindowFifoPolicy fifo,SessionState control) (lines 92-106)](../../../../../tests/unit/session_image_test.cpp), [src/runtime/session.cpp § checkpoint and restore_image (lines 1153-1207)](../../../../../src/runtime/session.cpp), [tests/support/window_checkpoint_test_fixture.hpp § command and seed (lines 53-65)](../../../../../tests/support/window_checkpoint_test_fixture.hpp), [docs/verification/o04-session-image-native-2026-11-10.md § Implementation (lines 8-32)](../../../../verification/o04-session-image-native-2026-11-10.md) |

## B0006

[Lines 107–132](../../../../../tests/unit/session_image_test.cpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void golden(const char* path) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare one independently constructed binary session image with the checked-in hexadecimal fixture and exercise bytewise rejection boundaries. |
| inputs / outputs | Input: golden fixture path; constructs a stopped typed checkpoint with fixed manifest, policy, two tables and one mixed-scalar row, then encodes it. |
| invariants | Checks one fixture byte-for-byte, zero-covered-new inspection, every strict prefix, and XOR 1 at every byte position (one low-bit mutation per byte). Synthetic hashes and policy are codec test constants; they do not establish compiler binding. |
| ownership | The local MemoryAccount funds encoded bytes and scalar row storage; expected hex text is a standard string read from the file. |
| failure | Every tested truncation or flipped byte must raise ImageFailure while the s04 allocator reports zero calls; file/codec/check failures propagate. |
| cost | Per run scans one encoded image, every prefix length, and one copy/flip per image byte; image length bounds the finite work but no asymptotic runtime is benchmarked. |
| Design | [tests/unit/session_image_test.cpp § void golden(const char* path) (lines 107-132)](../../../../../tests/unit/session_image_test.cpp), [src/recovery/session_image.cpp § encode, validate, inspect and materialize (lines 343-385)](../../../../../src/recovery/session_image.cpp), [tests/support/index_allocation.hpp § replacement new/delete and nonnested thread-local Scope (lines 11-70)](../../../../../tests/support/index_allocation.hpp), [tests/recovery/session-image-v1.hex](../../../../../tests/recovery/session-image-v1.hex), [include/crown/recovery/session_image.hpp § SessionImage and header size (lines 18-38)](../../../../../include/crown/recovery/session_image.hpp) |

## B0007

[Lines 133–135](../../../../../tests/unit/session_image_test.cpp#L133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reseal(recovery::SessionImage& image) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute the outer session-image payload digest after a test mutates a CROWNSI1 envelope. |
| inputs / outputs | Mutable SessionImage in; hashes bytes after the fixed session-image header and writes the digest into the header digest slot. |
| invariants | Uses session_image_header_size for the payload boundary and fixed digest offset 20; it does not repair structural invariants. |
| ownership | Mutates the caller-owned image byte vector in place; hash result is a fixed-size value. |
| failure | No error handling; caller must provide a complete image with the expected header layout. |
| cost | One SHA-256 payload pass and one fixed-size digest copy. |
| Design | [tests/unit/session_image_test.cpp § void reseal(recovery::SessionImage& image) (lines 133-135)](../../../../../tests/unit/session_image_test.cpp), [src/recovery/session_image.cpp § encode, validate, inspect and materialize (lines 343-385)](../../../../../src/recovery/session_image.cpp), [include/crown/recovery/session_image.hpp § session_image_header_size (line 38)](../../../../../include/crown/recovery/session_image.hpp) |

## B0008

[Lines 136–138](../../../../../tests/unit/session_image_test.cpp#L136); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void word(recovery::SessionImage& image,std::size_t position,std::uint64_t value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write one unsigned 64-bit value into a test image at a selected byte offset in little-endian order. |
| inputs / outputs | Inputs: mutable image, byte offset, and uint64 value; updates eight bytes in place. |
| invariants | The caller must choose an in-range offset and a field whose wire width is eight bytes. |
| ownership | Borrows and mutates the image; owns no storage. |
| failure | No bounds check is present; invalid offsets would index outside the vector. |
| cost | Exactly eight stores. |
| Design | [tests/unit/session_image_test.cpp § void word(recovery::SessionImage& image,std::size_t position,std::uint64_t value) (lines 136-138)](../../../../../tests/unit/session_image_test.cpp), [include/crown/recovery/session_image.hpp § SessionImage (lines 18-25)](../../../../../include/crown/recovery/session_image.hpp) |

## B0009

[Lines 139–142](../../../../../tests/unit/session_image_test.cpp#L139); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void preflight_failure(Action action) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that a malformed or over-limit inspection/encoding action rejects before any instrumented allocation. |
| inputs / outputs | Input: callable; returns no value. Catches ImageFailure and then checks the failure flag and zero s04_alloc calls. |
| invariants | Only ImageFailure counts as the expected rejection; other exceptions escape. The no-allocation observation is limited to the installed s04 allocator scope. |
| ownership | The helper owns its by-value callable parameter and invokes it as a named lvalue once; any referenced payload remains owned by the caller. |
| failure | ImageFailure sets the expected-failure flag; check throws if that flag is false or covered-new calls are nonzero. A different exception, including bad_alloc caused by denial, escapes directly. |
| cost | One action invocation and constant helper bookkeeping. |
| Design | [tests/unit/session_image_test.cpp § template<class Action> void preflight_failure(Action action) (lines 139-142)](../../../../../tests/unit/session_image_test.cpp), [tests/support/index_allocation.hpp § replacement new/delete and nonnested thread-local Scope (lines 11-70)](../../../../../tests/support/index_allocation.hpp), [include/crown/recovery/session_image.hpp § encode_session_image and inspect_session_image (lines 33-37)](../../../../../include/crown/recovery/session_image.hpp) |

## B0010

[Lines 143–178](../../../../../tests/unit/session_image_test.cpp#L143); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void corruptions_and_limits() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise fixed malformed-field offsets, resealed integer/enum corruptions, wrong-program binding, and exact envelope/native work limits. |
| inputs / outputs | Creates one stopped typed-session image; inspects its manifest; mutates copies at the listed offsets and attempts inspection/restore/encode under explicit limits. |
| invariants | The fixture depends on its documented default layout and one feed position. It checks only the enumerated offsets, five uint64 offsets, exact byte/work caps and source-work zero; a structurally valid changed plan digest is rejected only when admitted against the actual compiler program. |
| ownership | Each mutated image is an owned copy; source image/account remain the authority for baseline checks. Restore and encoded temporaries are scoped per assertion. |
| failure | Enumerated malformed/limited inspect and encode actions and the incompatible continuation must raise ImageFailure with zero covered-new calls. The resealed wrong-plan restore must report ImageFault::binding and preserve source rows; its allocation behavior is not checked by preflight_failure. |
| cost | Finite loops over 26 byte offsets, five word offsets, image work/bytes, and one-under limits; cost grows with the fixed fixture size and each mutated image copy. |
| Design | [tests/unit/session_image_test.cpp § void corruptions_and_limits() (lines 143-178)](../../../../../tests/unit/session_image_test.cpp), [src/recovery/session_image.cpp § encode, validate, inspect and materialize (lines 343-385)](../../../../../src/recovery/session_image.cpp), [src/runtime/session.cpp § checkpoint and restore_image (lines 1153-1207)](../../../../../src/runtime/session.cpp), [tests/support/index_allocation.hpp § replacement new/delete and nonnested thread-local Scope (lines 11-70)](../../../../../tests/support/index_allocation.hpp) |

## B0011

[Lines 179–217](../../../../../tests/unit/session_image_test.cpp#L179); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void lifetime_csv_and_scalars(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check source-closed CSV continuation and byte-exact window scalar payloads through session image restore. |
| inputs / outputs | Inputs: backend flag. Captures a CSV stream after one record, closes its source, restores with its tail, then round-trips a window row containing boundary integers, long/embedded-NUL/non-UTF8 string bytes, boolean, date and decimal. |
| invariants | The raw scalar row is seeded through native admission; text adapters have separate UTF-8 checks. The CSV fixture covers one reordered header and one unread record, not all CSV dialects. |
| ownership | The CSV image retains its original account after source reset. After restoring and destroying that image, the test checks original current requested bytes equal control_bytes(); it does not compare allocation counts or exact attribution. CSV and scalar restores own their receiving native state. |
| failure | Checks continuation progress, destruction without instrumented allocation, retained account bytes, CSV alias result, exact scalar equality and subsequent expiration; errors propagate. |
| cost | The CSV setup has one image capture/restore. The scalar setup builds native runtime/window state, restores a SessionCheckpoint, then captures/restores another image and expires the row. Its string contains an 8192-byte prefix plus NUL and 0xff; exported comparisons and codecs copy that payload. |
| Design | [tests/unit/session_image_test.cpp § void lifetime_csv_and_scalars(bool indexed) (lines 179-217)](../../../../../tests/unit/session_image_test.cpp), [src/runtime/session.cpp § checkpoint and restore_image (lines 1153-1207)](../../../../../src/runtime/session.cpp), [tests/support/window_checkpoint_test_fixture.hpp § command (lines 53-60)](../../../../../tests/support/window_checkpoint_test_fixture.hpp), [docs/verification/o04-session-image-native-2026-11-10.md § Implementation (lines 8-32)](../../../../verification/o04-session-image-native-2026-11-10.md) |

## B0012

[Lines 218–243](../../../../../tests/unit/session_image_test.cpp#L218); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void barriers_and_failed_source(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject checkpoint capture across selected writer, output, thread, reader, and active-window barriers, and preserve a stopped failed-reader prefix. |
| inputs / outputs | Input: backend flag. Exercises queued, pending, prepared, partial-output, wrong-thread and dropped sessions, malformed stream failure, active watermark, stop, and indexed zero-work restore. |
| invariants | The assertions describe only these barriers: after draining output one ready image is captured; stopped failed-reader restore retains sequence zero and input_failed. Indexed-work denial is checked only when indexed. |
| ownership | Sessions own runtime/readers/queues; the worker thread only borrows the source session; captured ready image owns bytes. |
| failure | Expected barrier failures are \`Error\`/ImageFailure via fixture rejection helpers; wrong-thread must report session_wrong_thread; a zero indexed structural grant must report storage_work_limit. |
| cost | One invocation per backend includes one joined thread, a step-until-prepared loop with no numeric guard, fixture command/output drains, and an indexed-only zero-work restore. The finite scenario list is not a bound on engine steps or elapsed time. |
| Design | [tests/unit/session_image_test.cpp § void barriers_and_failed_source(bool indexed) (lines 218-243)](../../../../../tests/unit/session_image_test.cpp), [src/runtime/session.cpp § checkpoint and restore_image (lines 1153-1207)](../../../../../src/runtime/session.cpp), [tests/support/session_checkpoint_test_fixture.hpp § rejected (lines 114-117)](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [tests/support/index_allocation.hpp § replacement new/delete and nonnested thread-local Scope (lines 11-70)](../../../../../tests/support/index_allocation.hpp) |

## B0013

[Lines 244–269](../../../../../tests/unit/session_image_test.cpp#L244); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void encoder_consistency() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject eight inconsistent window checkpoints and four typed-source checkpoints before encoder allocation. |
| inputs / outputs | Mutates four typed checkpoints and eight window checkpoints, including unsupported FIFO value 4, then checks zero-allocation preflight rejection. |
| invariants | Includes progress/EOF/input/sequence and window width/progress/id/count/deadline/stopped/work/enum contradictions. This fixed mutation set does not exhaust schema or restore semantics. The invalid-window-enum control now casts 5 because appended value 4 is a valid explicit unrestricted policy. |
| ownership | State copies and input/window payloads use the source account wrappers; no encoded image is retained on rejected actions. |
| failure | Each selected mutation must be rejected as ImageFailure before an instrumented allocation. |
| cost | Twelve preflight attempts plus setup and fixture checkpoint copies. |
| Design | [tests/unit/session_image_test.cpp § void encoder_consistency() (lines 244-268)](../../../../../tests/unit/session_image_test.cpp), [src/recovery/session_image.cpp § encode, validate, inspect and materialize (lines 343-385)](../../../../../src/recovery/session_image.cpp), [tests/support/index_allocation.hpp § replacement new/delete and nonnested thread-local Scope (lines 11-70)](../../../../../tests/support/index_allocation.hpp), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0014

[Lines 270–270](../../../../../tests/unit/session_image_test.cpp#L270); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L270-L270:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in session_image_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/session_image_test.cpp](../../../../../tests/unit/session_image_test.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 271–283](../../../../../tests/unit/session_image_test.cpp#L271); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the golden, corruption, encoder-consistency, typed-session, stream, window, lifetime and barrier fixtures. |
| inputs / outputs | Requires one session-image golden path; runs three common fixture groups, then both backends × six typed kinds × four controls, eight stream formats, four FIFO modes × four controls, plus scalar/lifetime and barrier cases. |
| invariants | Requires argc==2, runs the explicit matrix, prints std::exception and returns 1 on failure; successful fallthrough from main returns 0. CMake compiles this source into ordinary and CROWN_RUNTIME_TESTING grant executables, so configuration describes two binaries rather than two fresh executions. |
| ownership | Main borrows argv\[1\] for golden file loading; each helper owns its images/sessions and temporary expectations within its call. std::cout/std::cerr receive diagnostics. |
| failure | Wrong argc fails the check; any fixture exception prints its message and returns 1. |
| cost | Selected matrix is 2 times (6 times 4 typed controls +8 stream formats +4 times 4 window controls +2 other groups), plus common fixtures; no benchmark is collected. |
| Design | [tests/unit/session_image_test.cpp § int main(int argc,char** argv) (lines 270-282)](../../../../../tests/unit/session_image_test.cpp), [CMakeLists.txt § crown_session_image_test (lines 256-261)](../../../../../CMakeLists.txt), [CMakeLists.txt § crown_session_image_grant_test (lines 448-453)](../../../../../CMakeLists.txt), [Refactor.md § O04 — Implement versioned checkpoints (lines 1253-1255)](../../../../../Refactor.md), [docs/update_patterns.md](../../../../update_patterns.md) |
