# `include/crown/runtime/session_journal.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/session_journal.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Coordinate input, window control, native epoch preparation, output delivery and durable recovery at one session lifecycle boundary.

Snapshot SHA-256: `dea0bf145000fe5d363cf96ea7dbb7313f8c2a0599a90b578a39fcee6ad1a838`. 66 lines partitioned into 11 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [session](../../../../subsystem_contracts.md#session). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/session-journal.md](../../../../../session-journal.md), [docs/generations.md](../../../../../generations.md), [docs/local-sink.md](../../../../../local-sink.md), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/native-replay.md](../../../../../native-replay.md), [docs/update_patterns.md](../../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../../include/crown/runtime/session_journal.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 6–12](../../../../../../include/crown/runtime/session_journal.hpp#L6) | Type/record definition: struct SessionJournalOptions |  · [reviewed contract](#b0002) |
| [B0003 · 13–13](../../../../../../include/crown/runtime/session_journal.hpp#L13) | Type/record definition: enum class SessionJournalFault : std::uint8_t |  · [reviewed contract](#b0003) |
| [B0004 · 14–21](../../../../../../include/crown/runtime/session_journal.hpp#L14) | Type/record definition: class SessionJournalFailure final:public std::exception | returns fault_; @ · [reviewed contract](#b0004) |
| [B0005 · 22–37](../../../../../../include/crown/runtime/session_journal.hpp#L22) | Type/record definition: struct SessionJournalRecoveryOptions | source comment (unverified): // Codec inspection/materialization work across this reconstruction. Engine · [reviewed contract](#b0005) |
| [B0006 · 38–50](../../../../../../include/crown/runtime/session_journal.hpp#L38) | Type/record definition: struct RecoveredResult | returns query_id==other.query_id && generation==other.generation && physical_sequence==other.physical_seque…; source comment (unverified): // Native tuple copies share payload; legacy tuple copies can clone/allocate. · [reviewed contract](#b0006) |
| [B0007 · 51–53](../../../../../../include/crown/runtime/session_journal.hpp#L51) | Explanatory comments or spacing. | source comment (unverified): // Records/work/reader/pending fields describe the reconstruction handoff. · [reviewed contract](#b0007) |
| [B0008 · 54–58](../../../../../../include/crown/runtime/session_journal.hpp#L54) | Type/record definition: struct SessionJournalRecoveryStatus | source comment (unverified): // Records/work/reader/pending fields describe the reconstruction handoff. · [reviewed contract](#b0008) |
| [B0009 · 59–60](../../../../../../include/crown/runtime/session_journal.hpp#L59) | Explanatory comments or spacing. | source comment (unverified): // Fixed metadata about the last confirmed durable prefix. After an I/O failure · [reviewed contract](#b0009) |
| [B0010 · 61–65](../../../../../../include/crown/runtime/session_journal.hpp#L61) | Type/record definition: struct SessionJournalState | source comment (unverified): // Fixed metadata about the last confirmed durable prefix. After an I/O failure · [reviewed contract](#b0010) |
| [B0011 · 66–66](../../../../../../include/crown/runtime/session_journal.hpp#L66) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0011) |

## B0001

[Lines 1–5](../../../../../../include/crown/runtime/session_journal.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose session WAL policy, errors and recovered results. |
| inputs / outputs | Includes native checkpoint, checked session files and WAL File types. |
| invariants | Native session publication, durable record and output-delivery acceptance remain distinct. |
| ownership | No File/session owner created by inclusion. |
| failure | Compile-time boundary. |
| cost | No runtime action. |
| Design | [include/crown/runtime/session_journal.hpp](../../../../../../include/crown/runtime/session_journal.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0002

[Lines 6–12](../../../../../../include/crown/runtime/session_journal.hpp#L6); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionJournalOptions {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure WAL against an exact durable checkpoint. |
| inputs / outputs | Expected query ID/generation plus native capture, checkpoint-file and WAL-file limits. |
| invariants | enable_journal compares actual encoded session/checkpoint bytes before File create; supplied IDs/limits do not replace that check or a new allowance. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/runtime/session_journal.hpp](../../../../../../include/crown/runtime/session_journal.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 13–13](../../../../../../include/crown/runtime/session_journal.hpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class SessionJournalFault : std::uint8_t {state,checkpoint,recovery_required,tail,continuation,transition};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify session WAL coordination rejection. |
| inputs / outputs | state/checkpoint/recovery_required/tail/continuation/transition. |
| invariants | Errors describe real session preconditions/reconstruction, separate from filesystem stage/outcome and codec faults. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Constant-size tag, no allocation/IO/clock. Arbitrary casts are not admitted automatically. |
| Design | [include/crown/runtime/session_journal.hpp](../../../../../../include/crown/runtime/session_journal.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0004

[Lines 14–21](../../../../../../include/crown/runtime/session_journal.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class SessionJournalFailure final:public std::exception {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry fixed SessionJournalFailure diagnostics. |
| inputs / outputs | One SessionJournalFault and static text. |
| invariants | No allocated message; no durable authority follows from diagnostic fields. |
| ownership | Only fixed enums/native errno/booleans; what() returns static literal, no dynamic message or authority owner. |
| failure | Constructor/getters noexcept; constructing this public diagnostic itself does not prove a file effect or grant recovery authority. |
| cost | Fixed object construction/copy/getters, no dynamic message formatting or IO. Throw/unwind still has normal C++ ABI/stack cost and can require exception storage outside the query payload model. |
| Design | [include/crown/runtime/session_journal.hpp](../../../../../../include/crown/runtime/session_journal.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
explicit SessionJournalFailure(SessionJournalFault fault) noexcept:fault_(fault) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct SessionJournalFailure. |
| inputs / outputs | Stores supplied fixed diagnostic fields. |
| invariants | Actual implementation chooses phase/outcome; caller-created fields are descriptive only. |
| ownership | Inline values only; no file/runtime retained. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/runtime/session_journal.hpp](../../../../../../include/crown/runtime/session_journal.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] SessionJournalFault fault() const noexcept {return fault_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read SessionJournalFailure fault. |
| inputs / outputs | Returns stored fault by value. |
| invariants | Do not replace actual file/native recovery checks with the descriptive field. |
| ownership | Independent scalar; error object owns no authority. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/runtime/session_journal.hpp](../../../../../../include/crown/runtime/session_journal.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] const char* what() const noexcept override {return "session journal operation rejected";}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read SessionJournalFailure static message. |
| inputs / outputs | Returns constant what() literal. |
| invariants | Message is diagnostic label, not serialized recovery proof. |
| ownership | Static storage; pointer does not depend on exception lifetime. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/runtime/session_journal.hpp](../../../../../../include/crown/runtime/session_journal.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 22–37](../../../../../../include/crown/runtime/session_journal.hpp#L22); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionJournalRecoveryOptions {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound native WAL reconstruction and output handoff. |
| inputs / outputs | Journal policy/BuildOptions/optional receiving memory cap; decode512Mi/source256Mi work; output65536rows/64MiB; optional output frontier; tail-repair and seek-source options. |
| invariants | Codec/source/native engine grants independent. outputs_after filters reconstructed backlog, never sink/retirement authority. False seek requires stream at first unread byte after all complete logged inputs including cached uncommitted; true explicitly seeks origin to recovered decoder position. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/runtime/session_journal.hpp](../../../../../../include/crown/runtime/session_journal.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0006

[Lines 38–50](../../../../../../include/crown/runtime/session_journal.hpp#L38); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct RecoveredResult {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one identity-bearing reconstructed signed result. |
| inputs / outputs | Fixed query ID/generation/physical epoch plus SignedResult{ordinal,operation,Tuple}. |
| invariants | same_identity excludes spool ordinal and iteration order; identifies exact signed typed value within lineage, not actual durable acceptance. Public fields may be caller-constructed. |
| ownership | Actual native replay Tuple copy shares immutable funded payload/layout, move transfers. Caller-created legacy Tuple copy instead deep-copies ordinary Row/string values and may allocate; type alone promises neither mode. |
| failure | Tuple owning copy can throw for legacy representation; replay transfer is native move. No whole-record assignment publication guarantee beyond member behavior. |
| cost | Native copy fixed refcounts/metadata; legacy copy O(row bytes) allocation. Equality scans typed values; last tuple owner can release native block/control/layout graph. |
| Design | [include/crown/runtime/session_journal.hpp](../../../../../../include/crown/runtime/session_journal.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md), [src/storage/layout.cpp](../../../../../../src/storage/layout.cpp), [include/crown/storage/layout.hpp](../../../../../../include/crown/storage/layout.hpp) |

```text
[[nodiscard]] bool same_identity(const RecoveredResult& other) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare recovered result semantic identity without hashes. |
| inputs / outputs | Compare query ID/generation/physical epoch, sign and exact typed tuple values; ignore value.ordinal. |
| invariants | No digest collision argument needed; equality alone does not prove delivered/fsynced/native-source authority. Distinct layouts with same typed values may compare equal. |
| ownership | Read both tuple owners synchronously, retain neither or export Row. |
| failure | Signature not noexcept; underlying typed comparison may propagate invalid/caller scalar faults. |
| cost | O(compared fields/string bytes) plus fixed ID compares, no full row export or file IO. |
| Design | [include/crown/runtime/session_journal.hpp](../../../../../../include/crown/runtime/session_journal.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0007

[Lines 51–53](../../../../../../include/crown/runtime/session_journal.hpp#L51); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L53:sha256:b46d9db2385bc9a707a60088e33c943166b60319633dd9f14a84eeaf46128277
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`struct SessionJournalRecoveryStatus\`: Records/work/reader/pending fields describe the reconstruction handoff. Output fields describe the currently retained replay buffer. Live source progress and journal_state remain separate from this recovery report. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/runtime/session_journal.hpp:L54; use that declaration for the actual input/output shape. |
| invariants | The source note states: Records/work/reader/pending fields describe the reconstruction handoff. Output fields describe the currently retained replay buffer. Live source progress and journal_state remain separate from this recovery report. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Records/work/reader/pending fields describe the reconstruction handoff. Output fields describe the currently retained replay buffer. Live source progress and journal_state remain separate from this recovery report. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The note states a local cost boundary: Records/work/reader/pending fields describe the reconstruction handoff. Output fields describe the currently retained replay buffer. Live source progress and journal_state remain separate from this recovery report. Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/session-journal.md](../../../../../session-journal.md), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0008

[Lines 54–58](../../../../../../include/crown/runtime/session_journal.hpp#L54); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionJournalRecoveryStatus {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe recovery reconstruction handoff and current backlog. |
| inputs / outputs | Records/decode/source work/reader bytes+records, output remaining/bytes, optional pending input sequence. |
| invariants | Replay-handoff counters are not live input progress or last confirmed journal state. Output counters change with retained native backlog, not delivery proof. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/runtime/session_journal.hpp](../../../../../../include/crown/runtime/session_journal.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0009

[Lines 59–60](../../../../../../include/crown/runtime/session_journal.hpp#L59); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L59-L60:sha256:c98f9a4a9a0706af6c55ad95d299d7fee6e77a81d56ce70bd14195fda4ab1aae
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`struct SessionJournalState\`: Fixed metadata about the last confirmed durable prefix. After an I/O failure this is a lower bound; recovery_required forbids further session publication. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/runtime/session_journal.hpp:L61; use that declaration for the actual input/output shape. |
| invariants | The source note states: Fixed metadata about the last confirmed durable prefix. After an I/O failure this is a lower bound; recovery_required forbids further session publication. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | The note describes a failure or stop boundary: Fixed metadata about the last confirmed durable prefix. After an I/O failure this is a lower bound; recovery_required forbids further session publication. The comment adds no handler; the surrounding code determines the outcome. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/session-journal.md](../../../../../session-journal.md), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0010

[Lines 61–65](../../../../../../include/crown/runtime/session_journal.hpp#L61); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionJournalState {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe last confirmed durable WAL frontier. |
| inputs / outputs | Enabled/recovery_required, records/physical/command/next_substep and optional pending input. |
| invariants | After IO failure confirmed state only lower bound; recovery_required forbids session publication. Copied state cannot reinitialize File/Cursor or claim native decision applied. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/runtime/session_journal.hpp](../../../../../../include/crown/runtime/session_journal.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0011

[Lines 66–66](../../../../../../include/crown/runtime/session_journal.hpp#L66); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L66-L66:sha256:024a31d07f0690bcfeef2cd00cf111a56223bd48741eae7b548b6bc9143d9111
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime\` at its lexical source position in include/crown/runtime/session_journal.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/session-journal.md](../../../../../session-journal.md), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |
