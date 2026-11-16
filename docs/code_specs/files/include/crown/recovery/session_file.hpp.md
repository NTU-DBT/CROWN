# `include/crown/recovery/session_file.hpp` — block usage map

[Source](../../../../../../include/crown/recovery/session_file.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `43392c4425b490354cc48f79d4b53eb51f7d8254155d0ae0aafbabbcc7f8dc82`. 48 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../../checkpoints.md), [docs/journal.md](../../../../../journal.md), [docs/journal-files.md](../../../../../journal-files.md), [docs/generations.md](../../../../../generations.md), [docs/local-sink.md](../../../../../local-sink.md), [docs/history-retirement.md](../../../../../history-retirement.md), [docs/update_patterns.md](../../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../../include/crown/recovery/session_file.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 6–6](../../../../../../include/crown/recovery/session_file.hpp#L6) | Type/record definition: enum class PublicationState |  · [reviewed contract](#b0002) |
| [B0003 · 7–10](../../../../../../include/crown/recovery/session_file.hpp#L7) | Type/record definition: enum class FileStage |  · [reviewed contract](#b0003) |
| [B0004 · 11–11](../../../../../../include/crown/recovery/session_file.hpp#L11) | Type/record definition: enum class FileFault |  · [reviewed contract](#b0004) |
| [B0005 · 12–28](../../../../../../include/crown/recovery/session_file.hpp#L12) | Type/record definition: class FileFailure final:public std::exception | returns fault_; stage_ · [reviewed contract](#b0005) |
| [B0006 · 29–33](../../../../../../include/crown/recovery/session_file.hpp#L29) | Type/record definition: struct CheckpointFileLimits |  · [reviewed contract](#b0006) |
| [B0007 · 34–38](../../../../../../include/crown/recovery/session_file.hpp#L34) | Type/record definition: struct PublishedCheckpoint |  · [reviewed contract](#b0007) |
| [B0008 · 39–48](../../../../../../include/crown/recovery/session_file.hpp#L39) | declares values/defaults or compile-time conditions. | source comment (unverified): // Linux local-file publication: exclusive sibling temporary, complete write, · [reviewed contract](#b0008) |

## B0001

[Lines 1–5](../../../../../../include/crown/recovery/session_file.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose checked Linux checkpoint file publication. |
| inputs / outputs | Includes complete session image types and limits. |
| invariants | Publishing wire bytes does not admit a Program/native runtime; trusted parent namespace is required. |
| ownership | No file owner created at inclusion. |
| failure | Compile-time boundary. |
| cost | No runtime action. |
| Design | [include/crown/recovery/session_file.hpp](../../../../../../include/crown/recovery/session_file.hpp), [src/recovery/session_file.cpp](../../../../../../src/recovery/session_file.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |

## B0002

[Lines 6–6](../../../../../../include/crown/recovery/session_file.hpp#L6); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class PublicationState { not_published, unknown, published_unsynced, durable };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe standalone checkpoint name publication phase. |
| inputs / outputs | not_published/unknown/published_unsynced/durable. |
| invariants | Rename error unknown; successful rename but failed directory sync leaves complete visible file with unconfirmed durability. durable can precede failed checked close. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Constant-size tag, no allocation/IO/clock. Arbitrary casts are not admitted automatically. |
| Design | [include/crown/recovery/session_file.hpp](../../../../../../include/crown/recovery/session_file.hpp), [src/recovery/session_file.cpp](../../../../../../src/recovery/session_file.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 7–10](../../../../../../include/crown/recovery/session_file.hpp#L7); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class FileStage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify standalone checkpoint IO phase. |
| inputs / outputs | Path/open/entropy/temp/write/sync/close/rename/read/stat/unlink. |
| invariants | Stage separate from PublicationState; native codec failure is ImageFailure. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Constant-size tag, no allocation/IO/clock. Arbitrary casts are not admitted automatically. |
| Design | [include/crown/recovery/session_file.hpp](../../../../../../include/crown/recovery/session_file.hpp), [src/recovery/session_file.cpp](../../../../../../src/recovery/session_file.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |

## B0004

[Lines 11–11](../../../../../../include/crown/recovery/session_file.hpp#L11); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class FileFault { io,limit,path,not_regular,changed,truncated };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify standalone checkpoint file failure. |
| inputs / outputs | IO/limit/path/not_regular/changed/truncated. |
| invariants | Fixed tag alone cannot state which name survived rename. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Constant-size tag, no allocation/IO/clock. Arbitrary casts are not admitted automatically. |
| Design | [include/crown/recovery/session_file.hpp](../../../../../../include/crown/recovery/session_file.hpp), [src/recovery/session_file.cpp](../../../../../../src/recovery/session_file.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 12–28](../../../../../../include/crown/recovery/session_file.hpp#L12); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class FileFailure final:public std::exception {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry fixed checkpoint FileFailure diagnostics. |
| inputs / outputs | Fault/stage/publication/native errno/temp cleanup flag. |
| invariants | No allocating message; actual publication status must guide recovery after rename/dirsync failures. |
| ownership | Only fixed enums/native errno/booleans; what() returns static literal, no dynamic message or authority owner. |
| failure | Constructor/getters noexcept; constructing this public diagnostic itself does not prove a file effect or grant recovery authority. |
| cost | Fixed object construction/copy/getters, no dynamic message formatting or IO. Throw/unwind still has normal C++ ABI/stack cost and can require exception storage outside the query payload model. |
| Design | [include/crown/recovery/session_file.hpp](../../../../../../include/crown/recovery/session_file.hpp), [src/recovery/session_file.cpp](../../../../../../src/recovery/session_file.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |

```text
FileFailure(FileFault fault,FileStage stage,PublicationState state,int native_error=0,bool cleanup_failed=false) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct checkpoint FileFailure. |
| inputs / outputs | Stores supplied fixed diagnostic fields. |
| invariants | Actual implementation chooses phase/outcome; caller-created fields are descriptive only. |
| ownership | Inline values only; no file/runtime retained. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/session_file.hpp](../../../../../../include/crown/recovery/session_file.hpp), [src/recovery/session_file.cpp](../../../../../../src/recovery/session_file.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] FileFault fault() const noexcept {return fault_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read checkpoint FileFailure fault. |
| inputs / outputs | Returns stored fault by value. |
| invariants | Do not replace actual file/native recovery checks with the descriptive field. |
| ownership | Independent scalar; error object owns no authority. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/session_file.hpp](../../../../../../include/crown/recovery/session_file.hpp), [src/recovery/session_file.cpp](../../../../../../src/recovery/session_file.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] FileStage stage() const noexcept {return stage_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read checkpoint FileFailure stage. |
| inputs / outputs | Returns stored stage by value. |
| invariants | Do not replace actual file/native recovery checks with the descriptive field. |
| ownership | Independent scalar; error object owns no authority. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/session_file.hpp](../../../../../../include/crown/recovery/session_file.hpp), [src/recovery/session_file.cpp](../../../../../../src/recovery/session_file.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] PublicationState publication() const noexcept {return state_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read checkpoint FileFailure publication state. |
| inputs / outputs | Returns stored publication state by value. |
| invariants | Do not replace actual file/native recovery checks with the descriptive field. |
| ownership | Independent scalar; error object owns no authority. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/session_file.hpp](../../../../../../include/crown/recovery/session_file.hpp), [src/recovery/session_file.cpp](../../../../../../src/recovery/session_file.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] int native_error() const noexcept {return native_error_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read checkpoint FileFailure native error. |
| inputs / outputs | Returns stored native error by value. |
| invariants | Do not replace actual file/native recovery checks with the descriptive field. |
| ownership | Independent scalar; error object owns no authority. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/session_file.hpp](../../../../../../include/crown/recovery/session_file.hpp), [src/recovery/session_file.cpp](../../../../../../src/recovery/session_file.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] bool temporary_cleanup_failed() const noexcept {return cleanup_failed_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read checkpoint FileFailure temporary cleanup failure. |
| inputs / outputs | Returns stored temporary cleanup failure by value. |
| invariants | Do not replace actual file/native recovery checks with the descriptive field. |
| ownership | Independent scalar; error object owns no authority. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/session_file.hpp](../../../../../../include/crown/recovery/session_file.hpp), [src/recovery/session_file.cpp](../../../../../../src/recovery/session_file.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] const char* what() const noexcept override {return "checkpoint file operation failed";}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read checkpoint FileFailure static message. |
| inputs / outputs | Returns constant what() literal. |
| invariants | Message is diagnostic label, not serialized recovery proof. |
| ownership | Static storage; pointer does not depend on exception lifetime. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/session_file.hpp](../../../../../../include/crown/recovery/session_file.hpp), [src/recovery/session_file.cpp](../../../../../../src/recovery/session_file.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |

## B0006

[Lines 29–33](../../../../../../include/crown/recovery/session_file.hpp#L29); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CheckpointFileLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound standalone checkpoint envelope/IO. |
| inputs / outputs | SessionImageLimits, path4095/chunk1MiB and operations1M. |
| invariants | Validation before file work; actual syscalls/short IO/EINTR charged, bounded temp cleanup outside ordinary cap; no fresh query memory allowance. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/session_file.hpp](../../../../../../include/crown/recovery/session_file.hpp), [src/recovery/session_file.cpp](../../../../../../src/recovery/session_file.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |

## B0007

[Lines 34–38](../../../../../../include/crown/recovery/session_file.hpp#L34); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PublishedCheckpoint {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report actual completed checkpoint publication. |
| inputs / outputs | SessionImageManifest, byte count, syscall count and publication defaultdurable. |
| invariants | Successful publisher sets actual durable; publicly constructing this record/default flag cannot create a durable file or restore/native admission authority. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/session_file.hpp](../../../../../../include/crown/recovery/session_file.hpp), [src/recovery/session_file.cpp](../../../../../../src/recovery/session_file.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |

## B0008

[Lines 39–48](../../../../../../include/crown/recovery/session_file.hpp#L39); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] PublishedCheckpoint publish_session_image(std::string_view path,const SessionImage&,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish a structurally checked session envelope to a local path. |
| inputs / outputs | Opaque non-NUL path, SessionImage bytes, native validation limits and CheckpointFileLimits. |
| invariants | Inspect actual bytes rather than trust manifest fields; create exclusive sibling temporary, full write/fsync/checked close, atomic final-entry replacement then dirfsync/checked close. Final symlink entry replaced, never followed; parent namespace trusted. |
| ownership | Borrow bytes/path synchronously; no new retained account/File handle. Input byte vector already owns actual funded storage, publisher uses fixed stack IO metadata. |
| failure | Staged FileFailure carries exact not_published/unknown/published_unsynced/durable and bounded temp-cleanup result. Image validation before open may throw. Never retry rename/close blindly or claim rollback all visible publication. |
| cost | O(image bytes) inspect/hash/write, bounded entropy/temp names and chunk syscalls plus file/directory fsync; no byte-vector clone or native runtime rebuild. |
| Design | [include/crown/recovery/session_file.hpp](../../../../../../include/crown/recovery/session_file.hpp), [src/recovery/session_file.cpp](../../../../../../src/recovery/session_file.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |
