# `include/crown/recovery/journal_file.hpp` — block usage map

[Source](../../../../../../include/crown/recovery/journal_file.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Own locked WAL descriptors, validate prefix state and poison uncertain append attempts.

Snapshot SHA-256: `66082466e2efa908934a85be5015d64f6ee84a8cf2d8d9b6cab8893134f7ac1b`. 84 lines partitioned into 12 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../../checkpoints.md), [docs/journal.md](../../../../../journal.md), [docs/journal-files.md](../../../../../journal-files.md), [docs/generations.md](../../../../../generations.md), [docs/local-sink.md](../../../../../local-sink.md), [docs/history-retirement.md](../../../../../history-retirement.md), [docs/update_patterns.md](../../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../../include/crown/recovery/journal_file.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. | source comment (unverified): // Linux regular-file storage for the version-1 journal. One cooperating writer · [reviewed contract](#b0001) |
| [B0002 · 9–13](../../../../../../include/crown/recovery/journal_file.hpp#L9) | Type/record definition: enum class FileStage : std::uint8_t |  · [reviewed contract](#b0002) |
| [B0003 · 14–14](../../../../../../include/crown/recovery/journal_file.hpp#L14) | Type/record definition: enum class FileFault : std::uint8_t |  · [reviewed contract](#b0003) |
| [B0004 · 15–16](../../../../../../include/crown/recovery/journal_file.hpp#L15) | Explanatory comments or spacing. | source comment (unverified): // Outcome concerns the attempted operation. Unknown requires reopening and · [reviewed contract](#b0004) |
| [B0005 · 17–17](../../../../../../include/crown/recovery/journal_file.hpp#L17) | Type/record definition: enum class FileOutcome : std::uint8_t | source comment (unverified): // Outcome concerns the attempted operation. Unknown requires reopening and · [reviewed contract](#b0005) |
| [B0006 · 18–30](../../../../../../include/crown/recovery/journal_file.hpp#L18) | Type/record definition: class FileFailure final:public std::exception | returns fault_; stage_ · [reviewed contract](#b0006) |
| [B0007 · 31–35](../../../../../../include/crown/recovery/journal_file.hpp#L31) | Type/record definition: struct FileLimits |  · [reviewed contract](#b0007) |
| [B0008 · 36–52](../../../../../../include/crown/recovery/journal_file.hpp#L36) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Owns the actual descriptor/lock; copied Scanned values retain neither. · [reviewed contract](#b0008) |
| [B0009 · 53–53](../../../../../../include/crown/recovery/journal_file.hpp#L53) | Callable definition: \[\[nodiscard\]\] std::uint64_t operations() const noexcept | calls ; returns operations_ · [reviewed contract](#b0009) |
| [B0010 · 54–78](../../../../../../include/crown/recovery/journal_file.hpp#L54) | declares aliases; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Removes only a validated incomplete tail, retaining every complete input · [reviewed contract](#b0010) |
| [B0011 · 79–79](../../../../../../include/crown/recovery/journal_file.hpp#L79) | Type/record definition: struct stat stamp_ |  · [reviewed contract](#b0011) |
| [B0012 · 80–84](../../../../../../include/crown/recovery/journal_file.hpp#L80) | declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::recovery::journal · [reviewed contract](#b0012) |

## B0001

[Lines 1–8](../../../../../../include/crown/recovery/journal_file.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose Linux WAL file owner separate from codec inspection. |
| inputs / outputs | Includes Cursor/record types and struct stat; forwards QuerySession for private replay. |
| invariants | One cooperating writer advisory-flocks actual file for lifetime; trusted containing namespace is a protocol precondition. |
| ownership | No file/lock opened by inclusion. |
| failure | Compile-time boundary. |
| cost | No runtime action at inclusion. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0002

[Lines 9–13](../../../../../../include/crown/recovery/journal_file.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class FileStage : std::uint8_t {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify WAL file syscall/state phase. |
| inputs / outputs | Path/open/stat/lock/read/write/sync/link/unlink/truncate/close/state. |
| invariants | Failure stage independent from durable prefix outcome. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Constant-size tag, no allocation/IO/clock. Arbitrary casts are not admitted automatically. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 14–14](../../../../../../include/crown/recovery/journal_file.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class FileFault : std::uint8_t {io,limit,path,not_regular,busy,changed,truncated,state};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify actual WAL file failure. |
| inputs / outputs | IO/limit/path/not_regular/busy/changed/truncated/state. |
| invariants | Codec Failure remains distinct from filesystem FileFailure. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Constant-size tag, no allocation/IO/clock. Arbitrary casts are not admitted automatically. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0004

[Lines 15–16](../../../../../../include/crown/recovery/journal_file.hpp#L15); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L16:sha256:e05effd697a5bd1ba880df9cb26349e515352280f35547b79b220edd522f50eb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Outcome concerns the attempted operation. Unknown requires reopening and validating the surviving prefix; it never authorizes an in-place retry. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/recovery/journal_file.hpp lines 13-18; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [docs/code_specs/files/include/crown/recovery/journal_file.hpp.md](journal_file.hpp.md), [docs/journal.md](../../../../../journal.md), [docs/journal-files.md](../../../../../journal-files.md) |

## B0005

[Lines 17–17](../../../../../../include/crown/recovery/journal_file.hpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class FileOutcome : std::uint8_t {unchanged,unknown,durable};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe attempted WAL operation durability. |
| inputs / outputs | unchanged/unknown/durable. |
| invariants | Unknown requires closing/reopening and validating surviving prefix, not same-owner in-place retry. durable can precede later stat/checked-close failure. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Constant-size tag, no allocation/IO/clock. Arbitrary casts are not admitted automatically. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0006

[Lines 18–30](../../../../../../include/crown/recovery/journal_file.hpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class FileFailure final:public std::exception {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry fixed journal FileFailure diagnostics. |
| inputs / outputs | Fault/stage/outcome/native error/temp cleanup flag. |
| invariants | No dynamic message or permission to roll back/retry unknown mutation. |
| ownership | Only fixed enums/native errno/booleans; what() returns static literal, no dynamic message or authority owner. |
| failure | Constructor/getters noexcept; constructing this public diagnostic itself does not prove a file effect or grant recovery authority. |
| cost | Fixed object construction/copy/getters, no dynamic message formatting or IO. Throw/unwind still has normal C++ ABI/stack cost and can require exception storage outside the query payload model. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
FileFailure(FileFault fault,FileStage stage,FileOutcome outcome,int error=0,bool cleanup=false) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct journal FileFailure. |
| inputs / outputs | Stores supplied fixed diagnostic fields. |
| invariants | Actual implementation chooses phase/outcome; caller-created fields are descriptive only. |
| ownership | Inline values only; no file/runtime retained. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] FileFault fault() const noexcept {return fault_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read journal FileFailure fault. |
| inputs / outputs | Returns stored fault by value. |
| invariants | Do not replace actual file/native recovery checks with the descriptive field. |
| ownership | Independent scalar; error object owns no authority. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] FileStage stage() const noexcept {return stage_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read journal FileFailure stage. |
| inputs / outputs | Returns stored stage by value. |
| invariants | Do not replace actual file/native recovery checks with the descriptive field. |
| ownership | Independent scalar; error object owns no authority. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] FileOutcome outcome() const noexcept {return outcome_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read journal FileFailure outcome. |
| inputs / outputs | Returns stored outcome by value. |
| invariants | Do not replace actual file/native recovery checks with the descriptive field. |
| ownership | Independent scalar; error object owns no authority. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] int native_error() const noexcept {return error_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read journal FileFailure native error. |
| inputs / outputs | Returns stored native error by value. |
| invariants | Do not replace actual file/native recovery checks with the descriptive field. |
| ownership | Independent scalar; error object owns no authority. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] bool temporary_cleanup_failed() const noexcept {return cleanup_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read journal FileFailure temporary cleanup failure. |
| inputs / outputs | Returns stored temporary cleanup failure by value. |
| invariants | Do not replace actual file/native recovery checks with the descriptive field. |
| ownership | Independent scalar; error object owns no authority. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] const char* what() const noexcept override {return "journal file operation failed";}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read journal FileFailure static message. |
| inputs / outputs | Returns constant what() literal. |
| invariants | Message is diagnostic label, not serialized recovery proof. |
| ownership | Static storage; pointer does not depend on exception lifetime. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0007

[Lines 31–35](../../../../../../include/crown/recovery/journal_file.hpp#L31); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FileLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound cumulative WAL file validation and IO. |
| inputs / outputs | ScanLimits plus path4095/chunk1MiB/syscalls1M. |
| invariants | Path/host/off_t and minimum record size validated before open. Cleanup unlinks have a separate bounded retry allowance but still count operations; limits are not CPU or account bytes. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0008

[Lines 36–52](../../../../../../include/crown/recovery/journal_file.hpp#L36); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class File {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one validated durable WAL file, lock and validator. |
| inputs / outputs | Unique fd/stat/cursor, funded scratch/pending bytes, cumulative operations/outcome/poison/torn fields; copy and move assignment prohibited. |
| invariants | Only successful durable create/open/append/repair exposes state; poisoned owner rejects state/append until reopened. Complete pending input/window decisions retained across tail repair. |
| ownership | Owns actual fd/advisory lock; vectors retain receiving account. Pending state views borrow its retained pending vector until operation/move/destruction. |
| failure | Create/open/IO/codec/account errors propagate with actual stage/outcome; native replay effects remain private to receiving QuerySession factory. |
| cost | Open full prefix read/hash/scan+file/name sync, append frame copy/validate/write/fsync, state O(1), destruction close and two buffer frees. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] static File create(const resource::MemoryAccount&,std::string_view,const Header&,FileLimits={});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a new WAL without replacing existing entry. |
| inputs / outputs | Account/path/expected Header/FileLimits. Encode/validate ordinal0 header before file publication. |
| invariants | Exclusive sibling temp, hold flock, full write/file fsync, linkat no-overwrite, unlink temp/dir fsync before return. Existing entry/symlink not followed/replaced. |
| ownership | Return unique fd+lock/cursor and funded buffers; path used synchronously, directory RAII closed. |
| failure | Before link failure reports unchanged root-name authority though temp existed; link uncertainty not retried. Cleanup failure attached to FileFailure; partial new owner closes. |
| cost | Header codec preflight/final buffer; bounded entropy/temp attempts/chunked write+sync/link/dirsync/stat/checked-close; actual cumulative syscalls. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] static File open(const resource::MemoryAccount&,std::string_view,const Header&,FileLimits={});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open and admit an existing WAL durable prefix. |
| inputs / outputs | Account/path/expected Header/limits; delegates private open_replay without visitor. |
| invariants | No-follow regular file, exclusive nonblocking advisory lock, complete prefix validation/EOF/stat consistency, file and directory fsync before success. Validated torn suffix reported but not repaired. |
| ownership | Retains actual fd/lock, scratch and complete pending input bytes on receiving account. |
| failure | Complete corruption/foreign header/IO/resource/account failure rejects owner. No public replay effects escape. |
| cost | Read each frame, checksum/structural/continuity and CSV checks, buffer resize, EOF/stat and fsync; O(file bytes+codec work), not a cheap header read. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
~File();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Destroy WAL owner by best-effort close. |
| inputs / outputs | raw_close(fd_) preserves errno; vector/cursor members then destruct. |
| invariants | Destructor cannot report checked close; use close for diagnostic close outcome. |
| ownership | Releases actual fd/advisory lock and scratch/pending blocks/account. |
| failure | Nonthrowing, no new allocation or unlink/repair/history mutation. |
| cost | One raw close and trivial-byte buffer deallocations, no prefix scan. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
File(const File&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject WAL File copy construction. |
| inputs / outputs | Deleted operation. |
| invariants | Cannot duplicate one fd/lock/validator allowance by value. |
| ownership | Unique live authority. |
| failure | Compile-time rejection. |
| cost | No runtime cost. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
File& operator=(const File&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject WAL File copy assignment. |
| inputs / outputs | Deleted operation. |
| invariants | Cannot duplicate one fd/lock/validator allowance by value. |
| ownership | Unique live authority. |
| failure | Compile-time rejection. |
| cost | No runtime cost. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
File(File&&) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume WAL File by move construction. |
| inputs / outputs | Moves Cursor and native vectors, transfers fd/stat/counters/outcome; source fd=-1/poisoned. |
| invariants | Moved source cannot expose valid File state; pending bytes transfer without deep copy. Public state() rebinds pending frame to retained pending_ vector. |
| ownership | Destination owns actual fd/lock/buffers/account; source close harmless. |
| failure | noexcept. |
| cost | Fixed owner/vector/continuation transfer, no file IO or new buffer allocation. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
File& operator=(File&&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject WAL File move assignment. |
| inputs / outputs | Deleted operation. |
| invariants | Avoid overwriting a live file/lock/cursor with another authority lifecycle. |
| ownership | Move construction is supported transfer. |
| failure | Compile-time rejection. |
| cost | No runtime cost. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] Scanned state() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy healthy WAL state with owner-borrowed pending frame. |
| inputs / outputs | Lvalue File.ready then fixed Cursor snapshot, torn flag, optional frame rebound to pending_ bytes. |
| invariants | Poisoned/closed owner rejects; state only reflects successfully admitted durable operations. Scanned copy does not retain file or grant continuation. |
| ownership | Return fixed metadata/view; keep File unchanged/alive until pending frame consumed. |
| failure | FileFailure(state,unchanged) for closed/poisoned; no IO. |
| cost | O(1) counters/view construction, no allocation/hash/scan. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
Scanned state() const &&=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject WAL state from temporary owner. |
| inputs / outputs | Rvalue state deleted. |
| invariants | Prevents immediate dangling pending frame; retained lvalue lifetime still required. |
| ownership | No owner returned. |
| failure | Compile-time rejection. |
| cost | No runtime cost. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0009

[Lines 53–53](../../../../../../include/crown/recovery/journal_file.hpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::uint64_t operations() const noexcept {return operations_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read spent WAL syscall count. |
| inputs / outputs | Returns operations_ even if other owner operations unavailable. |
| invariants | Diagnostic count alone does not imply valid fd/durable prefix or allowance. |
| ownership | Independent scalar. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0010

[Lines 54–78](../../../../../../include/crown/recovery/journal_file.hpp#L54); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void append(std::string_view full_record) &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one validated complete WAL frame durably. |
| inputs / outputs | Healthy nontorn lvalue File plus stable full record. Copy into own scratch, validate/advance Cursor before IO. |
| invariants | Pre-Cursor failure leaves continuation unchanged. After successful feed set poisoned=true, stat-check/write at consumed end/fsync/refresh then retain pending and clear poison. No state after uncertain advance. |
| ownership | Copies record on original account; actual fd/lock retained, pending scratch swapped/cleared without new grant. |
| failure | Codec/OOM before feed does not poison; later IO/stat failure poisons owner even if fsync already durable. Reopen validated surviving prefix before retry. |
| cost | O(frame bytes+codec/CSV validation) copy/hash/scan, chunked append write/fsync/stat. Scratch growth funded; no native query replay in method. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void repair_tail() &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Repair only validated incomplete WAL tail. |
| inputs / outputs | Healthy File; nontorn no-op. Torn path poison, verify stat, ftruncate to Cursor.consumed, fsync/refresh then clear torn/poison. |
| invariants | Never removes complete pending input or partial window commit; no history retirement. Native replay/source/sink validation may be prerequisite at session layer. |
| ownership | Same actual file/lock; buffers and continuation retained. |
| failure | Truncate/sync/stat failure retains poison and actual outcome; cannot claim unchanged bytes or in-place retry. |
| cost | O(1) metadata/syscall sequence, no full prefix rescan or allocation; cost of actual filesystem truncate/sync remains. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void close() &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close WAL with checked diagnostic. |
| inputs / outputs | Requires fd&gt;=0; detach fd before checked close, including poisoned owner. |
| invariants | Close not retried on EINTR/EIO; cannot close a reused descriptor by retrying. Other File operations afterward unavailable. |
| ownership | Releases actual fd/lock; buffers remain until object destruction. |
| failure | FileFailure on closed/limit/IO, but fd already detached/closed best-effort if op cap reached. |
| cost | One charged close attempt, no heap/scan. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
friend class crown::runtime::QuerySession;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restrict native replay hook to actual session factory. |
| inputs / outputs | QuerySession friendship and ReplayVisitor type. |
| invariants | Public Scanned/flags cannot invoke arbitrary replay with durable authority. Visitor effects stay private until whole admission succeeds. |
| ownership | No owner created by access declaration. |
| failure | Compile-time boundary. |
| cost | No runtime work. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
using ReplayVisitor=void(*)(std::string_view,const Scanned&,void*);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define synchronous private replay callback. |
| inputs / outputs | Function pointer receives full frame view, Scanned state and opaque context. |
| invariants | Frame and pending views remain borrowed; consumer must not publish external effects before final prefix/EOF/stat/file-name sync. |
| ownership | Callback/context not owned/retained beyond open_replay. |
| failure | Callback can throw; receiving factory and File unwind; this is not noexcept hot instrumentation. |
| cost | One callback per admitted complete frame; native replay cost separate from WAL codec budget. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
static File open_replay(const resource::MemoryAccount&,std::string_view,const Header&,FileLimits,ReplayVisitor,void*);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit WAL while privately replaying complete frames. |
| inputs / outputs | Account/path/Header/limits and optional visitor/context. |
| invariants | All frame/header/continuity checks precede each callback; entire File admission additionally needs EOF/stat and file/directory sync. No tail repair here. |
| ownership | Hold fd/lock and receiver-native buffers; factory keeps all visitor mutations private until return. |
| failure | Any callback/codec/IO/OOM failure destroys private File and receiving session graph. Prior durable bytes not rolled back. |
| cost | O(file bytes+codec+callback native replay), complete pending retention; file/directory sync and checked close. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
File(const resource::MemoryAccount&,const Header&,FileLimits);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize empty private WAL file state. |
| inputs / outputs | Account/Header/limits bind Cursor and two image allocators; fd remains-1. |
| invariants | No actual file/header validated yet; actual create/open follows. |
| ownership | Buffers retain supplied account, expected Header copied into Cursor; no row/input borrow. |
| failure | Empty allocator/continuation setup no payload allocation; signature not noexcept. |
| cost | Fixed binding, no IO or buffer reserve. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void ready() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject closed or poisoned WAL owner use. |
| inputs / outputs | ready checks fd&lt;0 or poisoned. |
| invariants | Torn healthy state readable, append separately rejects torn until repair. |
| ownership | Reads owned scalars only. |
| failure | Throws fixed FileFailure(state,unchanged), no rescue path. |
| cost | O(1), no allocation/IO. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void unchanged_file();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | WAL verify current file unchanged. |
| inputs / outputs | Uses checked stat_file on actual fd to fstat temporary and compare device/inode/size/mtime/ctime with stamp. |
| invariants | Stat validation is explicit protocol boundary; successful fsync can precede failed stat. |
| ownership | Uses same fd/lock; only fixed stack/stat metadata. |
| failure | IO/changed/limit FileFailure propagates with current actual operation outcome. |
| cost | One charged fstat plus fixed comparisons/copy; no allocation or byte scan. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void refresh();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | WAL refresh actual file stamp. |
| inputs / outputs | Uses checked stat_file on actual fd to fstat into stamp_. |
| invariants | Stat validation is explicit protocol boundary; successful fsync can precede failed stat. |
| ownership | Uses same fd/lock; only fixed stack/stat metadata. |
| failure | IO/changed/limit FileFailure propagates with current actual operation outcome. |
| cost | One charged fstat plus fixed comparisons/copy; no allocation or byte scan. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void retain_pending(std::uint64_t old_records);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain complete pending input without copying buffer bytes. |
| inputs / outputs | After successful feed: new input ordinal==old_records swaps scratch into pending; completed input clears pending size. |
| invariants | Partial window commits retain original complete pending frame. Capacity remains charged; no grant refill. |
| ownership | Owner retains actual pending buffer; borrowed state views invalidated by later operation/move. |
| failure | No allocating operation; private protocol preconditions from successful Cursor feed. |
| cost | O(1) vector swap/clear of trivial bytes, no frame-byte scan. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
std::int64_t call(FileStage,std::size_t=0,int=-1,const char* =nullptr,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch one bounded WAL syscall. |
| inputs / outputs | Stage/arguments/buffer/offset/stat; increments actual operations, invokes test hook only testing build, returns result with errno. |
| invariants | Mutation syscall admission (write/truncate/link) marks unknown conservatively even if interrupted. Mandatory cleanup unlinks bypass ordinary op cap but UINT64 overflow still rejects. Closing detaches/releases fd even at cap. Only the explicit emergency_cleanup flag from the eight-attempt failure helper bypasses the ordinary operation cap; normal post-link unlink/EINTR does not. |
| ownership | Borrow arguments only for syscall; actual File keeps descriptor/lock; no heap message. |
| failure | Typed File failure on limits/state; IO errno left for checked; test hook behavior not a production service. |
| cost | One syscall attempt/fixed accounting; no allocation. Actual blocking IO/fsync cost not modeled as constant CPU. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md), [tests/unit/file_cleanup_quota_test.cpp](../../../../../../tests/unit/file_cleanup_quota_test.cpp) |

```text
std::int64_t checked(FileStage,std::size_t=0,int=-1,const char* =nullptr,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check WAL syscall with exact retry policy. |
| inputs / outputs | Calls dispatch until nonnegative or nonretryable error. |
| invariants | Retries EINTR except close and link publication; lock EWOULDBLOCK/EAGAIN becomes busy. Never retries uncertain publication. |
| ownership | No new owner/buffer retained. |
| failure | Throws fixed staged File failure including errno/outcome; ordinary operation cap bounds retries. |
| cost | One charge per attempt, no allocation/formatting; actual syscall latency explicit. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void transfer(bool write,char*,std::size_t,std::uint64_t);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer exact WAL bytes in bounded chunks. |
| inputs / outputs | Read/write, borrowed char buffer,size,offset; loop until full transfer. |
| invariants | Chunk limit, short transfer and EINTR handling real; zero read→truncated, zero write→IO/EIO. |
| ownership | Buffer must stay writable/readable for call; actual fd retained by File. |
| failure | Checked stage/limit/IO failure propagates current outcome; mutating caller has already arranged poison. |
| cost | O(bytes) transfer and ceil(bytes/chunk) minimum successful syscalls, short/EINTR may add; no new payload allocation. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool cleanup_temporary(int,const char*) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Clean WAL temporary under bounded emergency retry. |
| inputs / outputs | unlink_temporary up to8 attempts; success or ENOENT true, otherwise false. |
| invariants | Outside ordinary IO cap to permit cleanup, still overflow guarded. Cleanup does not roll back an installed destination or durable prefix. This fixed helper alone requests emergency_cleanup; normal publication cannot inherit the exemption by syscall stage. |
| ownership | Borrows directory fd/name, retains no extra owner. |
| failure | noexcept catch converts cleanup error to false for outer diagnostic; this catch is necessary error-report boundary. |
| cost | At most8 unlink attempts, no allocation/scan. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md), [tests/unit/file_cleanup_quota_test.cpp](../../../../../../tests/unit/file_cleanup_quota_test.cpp) |

```text
FileLimits limits_;Cursor cursor_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain validator/buffer/descriptor protocol state. |
| inputs / outputs | Private FileLimits, Cursor, scratch/pending ImageVectors and fd_. |
| invariants | Exactly one File holds live advisory lock; source after move fd=-1 and poisoned. State views borrow retained pending bytes. |
| ownership | Vectors hold actual receiver account; fd owns OS resource, Cursor only continuation authority. |
| failure | Destructor releases buffers/fd without new allocation; no hidden mirrored row graph. |
| cost | Capacity bytes plus bounded fixed state; buffer release fixed per block, no byte rescan. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0011

[Lines 79–79](../../../../../../include/crown/recovery/journal_file.hpp#L79); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct stat stamp_{};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain actual WAL stat snapshot. |
| inputs / outputs | struct stat stamp_ populated by checked fstat. |
| invariants | Fixed metadata used for same-file/stable-length check; stamp value alone does not own or reopen file. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0012

[Lines 80–84](../../../../../../include/crown/recovery/journal_file.hpp#L80); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t operations_=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain WAL spent operation/outcome and poison/torn flags. |
| inputs / outputs | Private operations_, FileOutcome, poisoned_/torn_. |
| invariants | Poison disallows public state after advanced Cursor/failed IO; outcome does not imply native query transition or repair permission. |
| ownership | Fixed fields only; actual fd/lock retained elsewhere in File. |
| failure | No failure/translation in field declarations. |
| cost | O(1) storage/reads, no heap/IO. |
| Design | [include/crown/recovery/journal_file.hpp](../../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal_file.cpp](../../../../../../src/recovery/journal_file.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |
