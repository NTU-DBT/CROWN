# `src/io/ingest_program.cpp` — block usage map

[Source](../../../../../src/io/ingest_program.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `9adc43d35e13a1907f153967e3929a51b464c852dbc5da30221220824f38c2c9`. 31 lines partitioned into 9 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../src/io/ingest_program.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 9–10](../../../../../src/io/ingest_program.cpp#L9) | Callable definition: EventReader::EventReader(std::istream& input,const CompiledProgram& program,InputOptions options,InputProgress progress) :EventRe… | calls EventReader, account, source_catalog_owner, std::move · [reviewed contract](#b0002) |
| [B0003 · 11–12](../../../../../src/io/ingest_program.cpp#L11) | Explanatory comments or spacing. | source comment (unverified): // Full schema fingerprint work allocates under program.account(); equality is · [reviewed contract](#b0003) |
| [B0004 · 13–15](../../../../../src/io/ingest_program.cpp#L13) | Callable definition: bool EventReader::matches_catalog(const CompiledProgram& program) const | calls input_detail::catalog_fingerprint, account, source_catalog_owner, view; returns input_detail::catalog_fingerprint(program.account(),program.source_catalog_owner(),true).view()==ca…; source comment (unverified): // Full schema fingerprint work allocates under program.account(); equality is · [reviewed contract](#b0004) |
| [B0005 · 16–21](../../../../../src/io/ingest_program.cpp#L16) | Callable definition: EventReader EventReader::with_options(std::istream& input,const CompiledProgram& program, const AccountedInputOptions& options,In… | calls account, statistics, Error, EventReader; returns EventReader(program.account(),input,program.source_catalog_owner(),options,std::move(progress),true) · [reviewed contract](#b0005) |
| [B0006 · 22–24](../../../../../src/io/ingest_program.cpp#L22) | Callable definition: EventReader EventReader::restore_state(std::istream& input,const CompiledProgram& program,const ReaderCheckpoint& state) | calls restore_state; returns restore_state(input,program,state,SourceStateLimits{}) · [reviewed contract](#b0006) |
| [B0007 · 25–27](../../../../../src/io/ingest_program.cpp#L25) | Callable definition: EventReader EventReader::restore_state(std::istream& input,const CompiledProgram& program,const ReaderCheckpoint& state,const Sou… | calls EventReader, account, source_catalog_owner; returns EventReader(program.account(),input,program.source_catalog_owner(),state,limits,true) · [reviewed contract](#b0007) |
| [B0008 · 28–30](../../../../../src/io/ingest_program.cpp#L28) | Callable definition: void EventReader::validate_checkpoint_options(const CompiledProgram& program,const AccountedInputOptions& options,const Accounted… | calls validate_options, source_catalog_owner · [reviewed contract](#b0008) |
| [B0009 · 31–31](../../../../../src/io/ingest_program.cpp#L31) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0009) |

## B0001

[Lines 1–8](../../../../../src/io/ingest_program.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:5d9a028b19f98bcc268f80b8d7f4077fec0ed68d4d9c2b5e29d615c82b625fe2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports compile-time dependencies (crown/io/ingest.hpp, crown/ir/program.hpp, crown/io/input_options.hpp, crown/api/error.hpp, native_input.hpp, crown/io/checkpoint.hpp) and opens crown::io scope for the declarations or definitions that follow. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/io/ingest_program.cpp](../../../../../src/io/ingest_program.cpp), [docs/code_specs/files/src/io/ingest_program.cpp.md](ingest_program.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0002

[Lines 9–10](../../../../../src/io/ingest_program.cpp#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
EventReader::EventReader(std::istream& input,const CompiledProgram& program,InputOptions options,InputProgress progress)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a program-backed reader without substituting a source owner or query account. |
| inputs / outputs | Forwards program.account(), source_catalog_owner(), moved ordinary options/progress and admitted=true to core EventReader. |
| invariants | Typed program supplies checked immutable schema. This bridge does not decode/acknowledge/seek the borrowed stream or create an unlimited replacement native grant. |
| ownership | Reader retains source owner and funded options/progress/Data, borrowing the caller's istream for its lifetime. |
| failure | Program/options/progress/account/allocation validation failure returns no reader; the borrowed stream is not consumed by this constructor. |
| cost | Core options/progress deep funded import and catalog fingerprint serialization/hash plus fixed forwarding. No source rows are copied into pending events yet. |
| Design | [src/io/ingest_program.cpp](../../../../../src/io/ingest_program.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [tests/unit/ingest_test.cpp](../../../../../tests/unit/ingest_test.cpp), [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 11–12](../../../../../src/io/ingest_program.cpp#L11); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L11-L12:sha256:728cded14401abb864e748bb775e88086d0e3793f65a81e02c3479c49f893adb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Full schema fingerprint work allocates under program.account(); equality is catalog compatibility, not source-owner/account or committed-progress authority. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/ingest_program.cpp lines 9-14; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/ingest_program.cpp](../../../../../src/io/ingest_program.cpp), [docs/code_specs/files/src/io/ingest_program.cpp.md](ingest_program.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0004

[Lines 13–15](../../../../../src/io/ingest_program.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool EventReader::matches_catalog(const CompiledProgram& program) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare complete reader/source catalog fingerprints at an explicit binding boundary. |
| inputs / outputs | Builds a temporary admitted catalog fingerprint from the supplied program account/source owner and compares it with reader.catalog_sha256(). |
| invariants | Equality is catalog compatibility, not source-owner token/account identity, sequence acceptance or a semantic proof. OrderedReplay checks it before first owner binding, not on every accepted event. |
| ownership | Temporarily owns funded canonical catalog buffer/digest text under the supplied program account; reader retains its existing fingerprint. |
| failure | Invalid reader/program, account-cap or fingerprint allocation errors propagate without stream/progress mutation. |
| cost | O(full catalog serialization bytes) and SHA plus funded buffer/digest allocation, then fixed-length hash comparison. Const does not imply allocation-free or O(1). |
| Design | [src/io/ingest_program.cpp](../../../../../src/io/ingest_program.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [tests/unit/ingest_test.cpp](../../../../../tests/unit/ingest_test.cpp), [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 16–21](../../../../../src/io/ingest_program.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
EventReader EventReader::with_options(std::istream& input,const CompiledProgram& program,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share existing immutable input options only within their original program account. |
| inputs / outputs | Checks options.account presence and exact owner identity with program.account, then constructs the reader using retained options and moved progress. |
| invariants | Equal option values alone cannot authorize cross-account retention. Core initialization validates format/table/source/limit/progress semantics; no input is implicitly accepted. |
| ownership | Shares funded immutable options/control/map/text and source owner; progress/Data are funded under the same account and stream remains borrowed. |
| failure | Foreign/absent options account throws invalid_input_options before construction; core validation/allocation failures return no reader. |
| cost | Fixed account check plus core progress/fingerprint/Data setup. It avoids an ordinary InputOptions export or deep clone of same-account options. |
| Design | [src/io/ingest_program.cpp](../../../../../src/io/ingest_program.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [tests/unit/ingest_test.cpp](../../../../../tests/unit/ingest_test.cpp), [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 22–24](../../../../../src/io/ingest_program.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
EventReader EventReader::restore_state(std::istream& input,const CompiledProgram& program,const ReaderCheckpoint& state) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore reader continuation with default bounded source-state limits. |
| inputs / outputs | Forwards stream/program/checkpoint with default SourceStateLimits to explicit restore. |
| invariants | Caller positions stream at the next unread byte; this wrapper does not seek, acknowledge or replay pending input. |
| ownership | Actual restored ownership belongs to the delegated constructor; checkpoint/source stream are borrowed during this call. |
| failure | Explicit restore failures propagate unchanged; no retry with relaxed limits. |
| cost | Fixed forwarding; actual state/option/progress/CSV permutation checks and copies occur in core restore. |
| Design | [src/io/ingest_program.cpp](../../../../../src/io/ingest_program.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [tests/unit/ingest_test.cpp](../../../../../tests/unit/ingest_test.cpp), [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 25–27](../../../../../src/io/ingest_program.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
EventReader EventReader::restore_state(std::istream& input,const CompiledProgram& program,const ReaderCheckpoint& state,const SourceStateLimits& limits) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore bounded reader state using the program's receiving account and immutable source. |
| inputs / outputs | Forwards program account/source, ReaderCheckpoint and SourceStateLimits to admitted core restore. |
| invariants | Core clone validates catalog hash, counters, source progress, option profile and CSV header/permutation under limits. Checkpoint fields are not standalone authority that prior runtime epochs committed. |
| ownership | Receiving account owns cloned immutable options, progress text/maps, CSV state and Data. Borrowed stream must already start at checkpoint's next unread byte. |
| failure | Binding/state/limit/account/allocation failures release partial restore and consume no stream records; no cached unacknowledged record is accepted. |
| cost | Full options/progress deep copies, fingerprint generation, CSV field copy and duplicate-permutation checks that can be quadratic in column count. No hidden unlimited account or per-event retry loop. |
| Design | [src/io/ingest_program.cpp](../../../../../src/io/ingest_program.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [tests/unit/ingest_test.cpp](../../../../../tests/unit/ingest_test.cpp), [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 28–30](../../../../../src/io/ingest_program.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void EventReader::validate_checkpoint_options(const CompiledProgram& program,const AccountedInputOptions& options,const AccountedInputProgress& progress) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check source-option/progress compatibility without restoring or admitting execution. |
| inputs / outputs | Dispatches program.source_catalog_owner with AccountedInputOptions and AccountedInputProgress to core validate_options. |
| invariants | This checks configuration semantics, not option account identity, catalog-digest equality, stream position, full checkpoint counters or runtime commit authority. |
| ownership | Borrows program schema/options/progress synchronously; it creates no retained source/reader owner. |
| failure | Invalid program/option/progress errors propagate; no engine work, source read or acceptance occurs. |
| cost | Actual format/table/token/source/progress validation and UTF-8/name/limit scans, without a reader state clone or parsing any event. |
| Design | [src/io/ingest_program.cpp](../../../../../src/io/ingest_program.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [tests/unit/ingest_test.cpp](../../../../../tests/unit/ingest_test.cpp), [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 31–31](../../../../../src/io/ingest_program.cpp#L31); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L31:sha256:39c2bd587239794e92def2b2ebc5cce8f0acd397d817bceec761a8f61bea3e66
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/ingest_program.cpp](../../../../../src/io/ingest_program.cpp), [docs/code_specs/files/src/io/ingest_program.cpp.md](ingest_program.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |
