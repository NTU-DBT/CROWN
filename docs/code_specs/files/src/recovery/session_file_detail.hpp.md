# `src/recovery/session_file_detail.hpp` — block usage map

[Source](../../../../../src/recovery/session_file_detail.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `f7250e21347bcd7f8555107e6f7b87690db820de0aaab147183c7ff14c740b9d`. 44 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../src/recovery/session_file_detail.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 9–20](../../../../../src/recovery/session_file_detail.hpp#L9) | Type/record definition: class FileDescriptor | returns fd_; value · [reviewed contract](#b0002) |
| [B0003 · 21–27](../../../../../src/recovery/session_file_detail.hpp#L21) | Type/record definition: struct FileIo |  · [reviewed contract](#b0003) |
| [B0004 · 28–29](../../../../../src/recovery/session_file_detail.hpp#L28) | Explanatory comments or spacing. | source comment (unverified): // Stack-only path/fd/preamble state. Loading allocates exactly one receiving- · [reviewed contract](#b0004) |
| [B0005 · 30–43](../../../../../src/recovery/session_file_detail.hpp#L30) | Type/record definition: class SessionFileReader | returns memory_limit_; source comment (unverified): // Stack-only path/fd/preamble state. Loading allocates exactly one receiving- · [reviewed contract](#b0005) |
| [B0006 · 44–44](../../../../../src/recovery/session_file_detail.hpp#L44) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::recovery::detail · [reviewed contract](#b0006) |

## B0001

[Lines 1–8](../../../../../src/recovery/session_file_detail.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/recovery/session_file.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fix inline storage and fd/stat dependencies for internal checkpoint loading. |
| inputs / outputs | file_path_capacity4096 and session_preamble_size316. |
| invariants | 316 ends immediately after captured memory ceiling in CROWNSI1 v1; it is sufficient for preliminary cap selection, not whole-frame validation. |
| ownership | Constants and types add no resource instance. |
| failure | Format/version changes require explicit layout review; loader checks current envelope/state versions. |
| cost | Fixed capacities avoid an unaccounted path/preamble heap graph. |
| Design | [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp), [src/runtime/session.cpp § QuerySession::restore_file](../../../../../src/runtime/session.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/session_image.cpp § read](../../../../../src/recovery/session_image.cpp) |

## B0002

[Lines 9–20](../../../../../src/recovery/session_file_detail.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class FileDescriptor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide one noncopyable unique Linux fd owner. |
| inputs / outputs | Default fd=-1, get/reset/release and destructor. |
| invariants | No copy or implicit move duplicates ownership; GenerationOwner explicitly transfers via release/reset. Valid fd0 must be treated as owned. |
| ownership | Member fd_ owns one descriptor when&gt;=0; no name/account ownership. |
| failure | Destructor/reset never throw; checked operational close failures are handled by FileIo after release. |
| cost | Fixed int storage, O(1) access/transfer and at most one cleanup close. |
| Design | [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp), [src/runtime/session.cpp § QuerySession::restore_file](../../../../../src/runtime/session.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp) |

```text
[[nodiscard]] int get() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the currently owned descriptor number. |
| inputs / outputs | Const owner in; int out, possibly -1. |
| invariants | A returned number does not transfer ownership or retain the underlying descriptor; caller must not independently close an owned fd. |
| ownership | Borrow lasts only while owner remains live/unreset. |
| failure | No validity check or syscall. |
| cost | O(1). |
| Design | [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp), [src/runtime/session.cpp § QuerySession::restore_file](../../../../../src/runtime/session.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp) |

```text
void reset(int value=-1) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare best-effort replacement/cleanup for unique descriptor ownership. |
| inputs / outputs | Distinct transferred fd or -1 in. |
| invariants | Old descriptor is closed once; same-fd reset is outside internal use. Use release before checked close when an error must be observed. |
| ownership | Adopts new fd, releases old ownership. |
| failure | noexcept and errno-preserving implementation; cannot unlink names or certify durable data. |
| cost | At most one raw close outside operation budgets. |
| Design | [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp), [src/runtime/session.cpp § QuerySession::restore_file](../../../../../src/runtime/session.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp) |

```text
[[nodiscard]] int release() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer descriptor ownership without closing. |
| inputs / outputs | Owned int out and member becomes -1. |
| invariants | Caller must immediately adopt or close result; current call sites pass it directly to checked close or another FileDescriptor reset. |
| ownership | Owner relinquishes all cleanup obligation for returned fd. |
| failure | noexcept; release itself cannot report or recover close failure. |
| cost | O(1), zero syscalls/allocation. |
| Design | [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp), [src/runtime/session.cpp § QuerySession::restore_file](../../../../../src/runtime/session.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp) |

## B0003

[Lines 21–27](../../../../../src/recovery/session_file_detail.hpp#L21); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FileIo {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry per-operation syscall quota and publication knowledge. |
| inputs / outputs | Copied CheckpointFileLimits, monotone operations0 and publication not_published, stage dispatcher. |
| invariants | Limits/counters are mutable internal plumbing, not a public recovery capability. Publication transitions are maintained by call and publish_session_image. Reader uses the same dispatch with not_published state. |
| ownership | Owns only fixed limits/counters; call borrows every fd/name/buffer. |
| failure | Limit failure/returned errno are handled at real read/publication boundaries; no poison/reset framework is embedded. |
| cost | Fixed storage; operations counts admitted attempts, excluding raw descriptor cleanup and rejected-close raw cleanup. |
| Design | [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp), [src/runtime/session.cpp § QuerySession::restore_file](../../../../../src/runtime/session.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp) |

## B0004

[Lines 28–29](../../../../../src/recovery/session_file_detail.hpp#L28); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L29:sha256:e59a3e5295f5ca5bff8528835e1c29d02388ea02316572e9a7db969199986d69
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Stack-only path/fd/preamble state. Loading allocates exactly one receiving- account byte buffer, then runtime/source/window decode uses that same owner. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/recovery/session_file_detail.hpp lines 26-31; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/recovery/session_file_detail.hpp](../../../../../src/recovery/session_file_detail.hpp), [docs/code_specs/files/src/recovery/session_file_detail.hpp.md](session_file_detail.hpp.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0005

[Lines 30–43](../../../../../src/recovery/session_file_detail.hpp#L30); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class SessionFileReader {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one staged file-load lifecycle before receiving native restoration. |
| inputs / outputs | Constructor opens/preflights; memory_limit accessor supplies captured cap; read consumes remainder once. |
| invariants | Private directory/file ownership and original stat/prefix/size prevent caller substitution. Full checksum/program validation is deliberately deferred to caller after receiving buffer allocation. |
| ownership | Inline316-byte prefix/stat/counters plus two descriptor owners; no account is stored until read receives one. |
| failure | Construct/read failures unwind safely in actual wrappers. After read progress or fd release, reconstruct instead of reusing this loader; there is no retry/poison flag. |
| cost | Fixed preliminary state, one full receiving-account byte vector in read, then separate decoder/native allocations. |
| Design | [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp), [src/runtime/session.cpp § QuerySession::restore_file](../../../../../src/runtime/session.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp) |

```text
[[nodiscard]] std::uint64_t memory_limit_bytes() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the preliminary captured cap for receiving-account construction. |
| inputs / outputs | Decoded preamble memory_limit_ out. |
| invariants | Full checksum has not yet been verified. Caller may supply an explicit override and must still validate whole envelope/native binding before returning a session. |
| ownership | Returns a scalar, no account or authority. |
| failure | No throw or further validation. |
| cost | O(1), no file reread. |
| Design | [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp), [src/runtime/session.cpp § QuerySession::restore_file](../../../../../src/runtime/session.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp) |

```text
FileIo io_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep file identity, read position prerequisites and cap together in the loader. |
| inputs / outputs | FileIo, directory_/file_, original stat, prefix_, size_ and memory_limit_. |
| invariants | Fields are private; constructor establishes regular bounded file and316 consumed bytes. Sequential fd position is implicit and not reset by failed read. |
| ownership | Descriptors own resources; prefix owns inline bytes; no borrowed path survives. |
| failure | Member RAII closes acquired fds on any later wrapper unwind; raw cleanup is not an admitted FileIo operation. |
| cost | Fixed per-loader storage; full image and restored graph are allocated only from explicit account. |
| Design | [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp), [src/runtime/session.cpp § QuerySession::restore_file](../../../../../src/runtime/session.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp) |

## B0006

[Lines 44–44](../../../../../src/recovery/session_file_detail.hpp#L44); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L44-L44:sha256:acdf1b5fc75d5c18b842bb7fb52e994294982fe0260b6a9937115ce51c7d9072
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::recovery::detail at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/session_file_detail.hpp](../../../../../src/recovery/session_file_detail.hpp), [docs/code_specs/files/src/recovery/session_file_detail.hpp.md](session_file_detail.hpp.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |
