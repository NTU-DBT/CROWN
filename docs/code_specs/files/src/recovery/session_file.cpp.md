# `src/recovery/session_file.cpp` — block usage map

[Source](../../../../../src/recovery/session_file.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `14eaf22b3a106cf25f6c95837031d6f5a02088c7356c5dd773ea9f0afdf702d6`. 228 lines partitioned into 19 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–19](../../../../../src/recovery/session_file.cpp#L1) | Imports dependencies; controls preprocessing; declares namespace scope; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 20–20](../../../../../src/recovery/session_file.cpp#L20) | Callable definition: void set_file_hook(FileHook hook,void* context) noexcept | calls  · [reviewed contract](#b0002) |
| [B0003 · 21–23](../../../../../src/recovery/session_file.cpp#L21) | controls preprocessing; declares namespace scope. |  · [reviewed contract](#b0003) |
| [B0004 · 24–26](../../../../../src/recovery/session_file.cpp#L24) | Callable definition: \[\[noreturn\]\] void fail(FileFault fault,FileStage stage,PublicationState state,int error=0) | calls FileFailure · [reviewed contract](#b0004) |
| [B0005 · 27–29](../../../../../src/recovery/session_file.cpp#L27) | Callable definition: bool closing(FileStage stage) | calls ; returns stage==FileStage::close_file \|\| stage==FileStage::close_directory \|\| stage==FileStage::close_read · [reviewed contract](#b0005) |
| [B0006 · 30–43](../../../../../src/recovery/session_file.cpp#L30) | Type/record definition: struct Path |  · [reviewed contract](#b0006) |
| [B0007 · 44–52](../../../../../src/recovery/session_file.cpp#L44) | Callable definition: std::int64_t checked(detail::FileIo& io,FileStage stage,std::size_t count,int fd,const char* name=nullptr, int other_fd=-1,const … | calls call, closing, fail; returns value; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 53–61](../../../../../src/recovery/session_file.cpp#L53) | Callable definition: void read_exact(detail::FileIo& io,int fd,char* output,std::size_t size) | calls std::min, checked, fail; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 62–71](../../../../../src/recovery/session_file.cpp#L62) | Callable definition: bool unlink_temporary(detail::FileIo& io,int directory,const char* name) noexcept | calls call; returns true; false; 1 loop sites; source comment (unverified): // Mandatory cleanup has a fixed retry bound outside the ordinary I/O budget. · [reviewed contract](#b0009) |
| [B0010 · 72–76](../../../../../src/recovery/session_file.cpp#L72) | Callable definition: bool same_file(const struct stat& a,const struct stat& b) | calls ; returns a.st_dev==b.st_dev && a.st_ino==b.st_ino && a.st_size==b.st_size && · [reviewed contract](#b0010) |
| [B0011 · 77–79](../../../../../src/recovery/session_file.cpp#L77) | declares namespace scope. | source comment (unverified): // namespace · [reviewed contract](#b0011) |
| [B0012 · 80–80](../../../../../src/recovery/session_file.cpp#L80) | Callable definition: FileDescriptor::~FileDescriptor() | calls reset · [reviewed contract](#b0012) |
| [B0013 · 81–86](../../../../../src/recovery/session_file.cpp#L81) | Callable definition: void FileDescriptor::reset(int value) noexcept | calls close; source comment (unverified): // Linux releases descriptors even when close reports EINTR/EIO. Retrying · [reviewed contract](#b0013) |
| [B0014 · 87–142](../../../../../src/recovery/session_file.cpp#L87) | Callable definition: std::int64_t FileIo::call(FileStage stage,std::size_t requested,int fd,const char* name, int other_fd,const char* other_name,void… | calls closing, close, fail, testing::current_hook; returns result; source comment (unverified): // Counts admitted attempts. Raw fd cleanup, including a quota-rejected close, · [reviewed contract](#b0014) |
| [B0015 · 143–167](../../../../../src/recovery/session_file.cpp#L143) | Callable definition: SessionFileReader::SessionFileReader(std::string_view path,CheckpointFileLimits limits):io_{limits} | calls parsed, reset, checked, data; guard binary_detail::require(reader.take(8)=="CROWNSI1");binary_detail::require(reader.integer(2)==1 && r…; 1 loop sites; source comment (unverified): // This fixed preamble exposes the captured cap before receiving allocation. · [reviewed contract](#b0015) |
| [B0016 · 168–180](../../../../../src/recovery/session_file.cpp#L168) | Callable definition: ImageVector&lt;char&gt; SessionFileReader::read(const resource::MemoryAccount& account) | calls result, resize, std::copy, begin; returns result; growth resize; source comment (unverified): // One-shot sequential read: after partial progress/fd release, reconstruct · [reviewed contract](#b0016) |
| [B0017 · 181–182](../../../../../src/recovery/session_file.cpp#L181) | Closes surrounding scope/type. | source comment (unverified): // namespace detail · [reviewed contract](#b0017) |
| [B0018 · 183–227](../../../../../src/recovery/session_file.cpp#L183) | Callable definition: PublishedCheckpoint publish_session_image(std::string_view path,const SessionImage& image, const runtime::SessionCheckpointLimits… | calls parsed, inspect_session_image, data, size; returns {info.manifest,static_cast&lt;std::uint64_t&gt;(image.bytes.size()),io.operations,PublicationState::durab…; 6 loop sites; source comment (unverified): // Reinspect actual bytes; mutable SessionImage reports do not authorize them. · [reviewed contract](#b0018) |
| [B0019 · 228–228](../../../../../src/recovery/session_file.cpp#L228) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::recovery · [reviewed contract](#b0019) |

## B0001

[Lines 1–19](../../../../../src/recovery/session_file.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/recovery/session_file.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the Linux checkpoint file boundary and test-only syscall hook state. |
| inputs / outputs | Linux fd/stat/random APIs plus pure image inspection; CROWN_RUNTIME_TESTING adds thread-local hook/context. |
| invariants | Production ownership/publication logic stays the same with hooks disabled. Hook ABI is noexcept, and successful observed results still come from real syscalls. |
| ownership | Thread-local context is a borrowed testing pointer, not an owning session object. |
| failure | No syscall occurs at inclusion; test hook lifetime is managed by test fixtures. |
| cost | Compile-time platform boundary; two TLS scalar slots only in testing builds. |
| Design | [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [include/crown/recovery/session_file.hpp](../../../../../include/crown/recovery/session_file.hpp), [src/runtime/session.cpp § QuerySession::restore_file](../../../../../src/runtime/session.cpp), [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [tests/support/checkpoint_file_probe.hpp](../../../../../tests/support/checkpoint_file_probe.hpp) |

## B0002

[Lines 20–20](../../../../../src/recovery/session_file.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void set_file_hook(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace the current thread's private fault-observation hook. |
| inputs / outputs | Function pointer and borrowed context pointer in. |
| invariants | Testing build only; callback must match noexcept ABI and context must stay valid while installed. No production dispatch registration exists. |
| ownership | Stores pointers without owning or destroying context. |
| failure | noexcept assignment; fixtures clear hook on scope exit. |
| cost | O(1), no allocation. |
| Design | [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [include/crown/recovery/session_file.hpp](../../../../../include/crown/recovery/session_file.hpp), [src/runtime/session.cpp § QuerySession::restore_file](../../../../../src/runtime/session.cpp), [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [tests/support/checkpoint_file_probe.hpp](../../../../../tests/support/checkpoint_file_probe.hpp) |

## B0003

[Lines 21–23](../../../../../src/recovery/session_file.cpp#L21); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L23:sha256:2cdf9576c15c73a8f4ece08282d4cdd2a44bb5fb31869defd3a37f40b7b45aed
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the CROWN_SESSION_FILE_TESTING hook and its conditional compilation region, then opens the anonymous namespace for file publication helpers. |
| inputs / outputs | No external runtime input/output is performed by the declaration itself; callable signatures in the block describe future use. |
| invariants | Only the CROWN_SESSION_FILE_TESTING-enabled build sees the preceding thread-local test hook; the following anonymous-namespace helpers are compiled for the file implementation. |
| ownership | No owner is added merely by a declaration. Typed fields keep the ownership behavior of their C++ types and any explicit account allocator. |
| failure | The preprocessor guard does not catch filesystem errors. Later checked file operations preserve their declared stage/outcome failure carriers. |
| cost | Preprocessor/scope boundary only; test hook code is not present when its testing macro is absent. |
| Design | [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp), [docs/code_specs/files/src/recovery/session_file.cpp.md](session_file.cpp.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0004

[Lines 24–26](../../../../../src/recovery/session_file.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[noreturn]] void fail(FileFault fault
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise a fixed checkpoint-file failure with the exact observed publication phase. |
| inputs / outputs | Fault, stage, state and optional native errno in. |
| invariants | Failure state describes publication knowledge, not whether old/new artifact contents are logically selected by a query. |
| ownership | Exception contains fixed metadata only. |
| failure | Throws FileFailure; publication catch may add cleanup failure while preserving these fields. |
| cost | Fixed payload and exception machinery; no dynamic diagnostic string. |
| Design | [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [include/crown/recovery/session_file.hpp](../../../../../include/crown/recovery/session_file.hpp), [src/runtime/session.cpp § QuerySession::restore_file](../../../../../src/runtime/session.cpp), [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp) |

## B0005

[Lines 27–29](../../../../../src/recovery/session_file.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool closing(FileStage stage)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify fd-releasing syscall stages for one-attempt close semantics. |
| inputs / outputs | FileStage in; true for close_file/close_directory/close_read. |
| invariants | These stages must not be retried on Linux after ownership was released. Dispatcher still closes on quota or injected pre-close failure. |
| ownership | Classification transfers no resource. |
| failure | No failure/allocation. |
| cost | O(1) three comparisons. |
| Design | [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [include/crown/recovery/session_file.hpp](../../../../../include/crown/recovery/session_file.hpp), [src/runtime/session.cpp § QuerySession::restore_file](../../../../../src/runtime/session.cpp), [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp) |

## B0006

[Lines 30–43](../../../../../src/recovery/session_file.cpp#L30); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Path {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit and split a path into fixed NUL-terminated parent/base buffers before I/O. |
| inputs / outputs | Borrowed opaque path and CheckpointFileLimits in; two zero-filled4096-byte arrays. |
| invariants | path_bytes&lt;4096, chunk in1..SSIZE_MAX, operations&gt;0; path nonempty/bounded/no NUL; base neither empty,. nor ... Parent resolution may follow symlinks before anchoring. |
| ownership | Arrays own copied bytes; source path may expire after construction. No account is needed for fixed stack state. |
| failure | Limit/path failure is not_published before any file operation; filesystem NAME_MAX/existence errors remain syscall outcomes. |
| cost | O(path bytes) search/copy plus fixed8192-byte initialization, no heap allocation. |
| Design | [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [include/crown/recovery/session_file.hpp](../../../../../include/crown/recovery/session_file.hpp), [src/runtime/session.cpp § QuerySession::restore_file](../../../../../src/runtime/session.cpp), [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp) |

## B0007

[Lines 44–52](../../../../../src/recovery/session_file.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::int64_t checked(detail::FileIo& io
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retry only safe interrupted operations and translate syscall errors. |
| inputs / outputs | FileIo and stage-specific borrowed syscall arguments in; nonnegative result out. |
| invariants | EINTR retries only when retry=true and stage is not a close. Publisher passes retry=false for rename and checked closes. Every admitted attempt consumes io.operations. |
| ownership | No resource adoption here; successful open result must be immediately adopted by caller. |
| failure | FileFailure(io,stage,current publication,errno) on nonretryable error; dispatch limit failure propagates. No general syscall rollback. |
| cost | One dispatch per attempt, bounded by operation quota; no time bound on a syscall. |
| Design | [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [include/crown/recovery/session_file.hpp](../../../../../include/crown/recovery/session_file.hpp), [src/runtime/session.cpp § QuerySession::restore_file](../../../../../src/runtime/session.cpp), [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp) |

## B0008

[Lines 53–61](../../../../../src/recovery/session_file.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void read_exact(detail::FileIo& io
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a required byte count with bounded chunk requests and short-read progress. |
| inputs / outputs | Open sequential fd, writable range and size in. |
| invariants | Request=min(chunk,remaining); Path validated nonzero SSIZE_MAX-safe chunk. Internal caller buffer is large enough. |
| ownership | Writes caller-owned storage; does not own fd/buffer. |
| failure | EOF before required size raises truncated; EINTR handled by checked. Earlier successful reads advance fd and buffer, so caller must reconstruct loader after partial failure. |
| cost | O(size) data transfer, at least ceil(size/chunk) successful reads plus shorts/retries; no allocation. |
| Design | [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [include/crown/recovery/session_file.hpp](../../../../../include/crown/recovery/session_file.hpp), [src/runtime/session.cpp § QuerySession::restore_file](../../../../../src/runtime/session.cpp), [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp) |

## B0009

[Lines 62–71](../../../../../src/recovery/session_file.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool unlink_temporary(detail::FileIo& io
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attempt bounded mandatory cleanup without masking the publication failure. |
| inputs / outputs | Directory fd and private temporary name in; removal/ENOENT confirmation Boolean out. |
| invariants | At most8 attempts; only EINTR retries. Cleanup is exempt from ordinary quota but still increments operations unless UINT64_MAX prevents dispatch. |
| ownership | Only unlinks the caller's still-owned private name; never destination. |
| failure | Any call exception becomes false in this noexcept helper; caller preserves original FileFailure and reports cleanup_failed. |
| cost | Up to8 unlink attempts, independent of ordinary quota; no allocation. |
| Design | [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [include/crown/recovery/session_file.hpp](../../../../../include/crown/recovery/session_file.hpp), [src/runtime/session.cpp § QuerySession::restore_file](../../../../../src/runtime/session.cpp), [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp) |

## B0010

[Lines 72–76](../../../../../src/recovery/session_file.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_file(const struct stat& a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detect ordinary size/inode/time changes across one fd-based read. |
| inputs / outputs | Two fstat snapshots in; device/inode/size/mtime/ctime equality out. |
| invariants | This is not atomic adversarial snapshot authentication or final-path identity proof; full checksums and native admission still follow. |
| ownership | Reads scalar stat fields only. |
| failure | False causes FileFault::changed in caller; helper cannot repair or lock a file. |
| cost | O(1) comparisons; no syscall in helper. |
| Design | [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [include/crown/recovery/session_file.hpp](../../../../../include/crown/recovery/session_file.hpp), [src/runtime/session.cpp § QuerySession::restore_file](../../../../../src/runtime/session.cpp), [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp) |

## B0011

[Lines 77–79](../../../../../src/recovery/session_file.cpp#L77); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L77-L79:sha256:27066704b138f267b3c39e88943cf6f5fa3719cc9b32f18a4001c7f7d6b7ca9d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous session-file helper namespace and opens detail for FileDescriptor and SessionFileReader definitions. |
| inputs / outputs | No external runtime input/output is performed by the declaration itself; callable signatures in the block describe future use. |
| invariants | The declaration fixes the source-local names and member/type shape; runtime validation and authority remain with the actual implementations. |
| ownership | No owner is added merely by a declaration. Typed fields keep the ownership behavior of their C++ types and any explicit account allocator. |
| failure | No runtime catch or translation is added here; constructor/member failures remain in their implementation. |
| cost | Declaration-only compile/link work, except that constructing a declared type later may initialize or allocate its members. |
| Design | [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp), [docs/code_specs/files/src/recovery/session_file.cpp.md](session_file.cpp.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0012

[Lines 80–80](../../../../../src/recovery/session_file.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
FileDescriptor::~FileDescriptor()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release a still-owned Linux descriptor during ordinary destruction/unwind. |
| inputs / outputs | Owned descriptor state in; delegates reset(-1). |
| invariants | Cleanup never retries close and does not report close errors as successful durability. Named temporary deletion is a separate obligation. |
| ownership | Releases fd only; no file-name deletion. |
| failure | Destructor does not throw and reset preserves incoming errno. |
| cost | At most one raw close, outside FileIo admitted-operation accounting. |
| Design | [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [include/crown/recovery/session_file.hpp](../../../../../include/crown/recovery/session_file.hpp), [src/runtime/session.cpp § QuerySession::restore_file](../../../../../src/runtime/session.cpp), [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp) |

## B0013

[Lines 81–86](../../../../../src/recovery/session_file.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void FileDescriptor::reset(int value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace fd ownership and close the old descriptor exactly once. |
| inputs / outputs | New fd or -1 in; old fd removed from owner before close. |
| invariants | Caller transfers a distinct live fd or -1; resetting to the same nonnegative number would close it and is outside the internal use contract. Linux close EINTR/EIO is not retried. |
| ownership | Owner assumes new fd; previous fd is best-effort closed. |
| failure | noexcept, ignores close result and restores errno; cannot establish durability or remove a private name. |
| cost | O(1) state and at most one raw close; not charged by FileIo. |
| Design | [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [include/crown/recovery/session_file.hpp](../../../../../include/crown/recovery/session_file.hpp), [src/runtime/session.cpp § QuerySession::restore_file](../../../../../src/runtime/session.cpp), [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [src/recovery/generation.cpp § GenerationOwner::GenerationOwner](../../../../../src/recovery/generation.cpp) |

## B0014

[Lines 87–142](../../../../../src/recovery/session_file.cpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::int64_t FileIo::call(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one syscall attempt, inject test faults safely and report its actual phase. |
| inputs / outputs | Stage/count/fds/names/buffer/stat in; signed result and errno out. |
| invariants | Counts attempts before dispatch; ordinary quota applies except unlink_temporary, counter overflow always rejects. rename sets unknown only after quota admission and before syscall/injected failure. Internal parameters are stage-valid. |
| ownership | Successful fd must be adopted by caller. Injected post-open errors are moved before creation to avoid losing undisclosed fds. Released closes execute even for pre-close injected/quota errors. |
| failure | Limit raises FileFailure; syscall errors return -1+errno. No retry here. Closes never leave ownership for a caller retry; raw quota-cleanup close is outside counted attempts. |
| cost | At most one real syscall per admitted dispatch plus fixed hook/counter work; admitted injected failure can use a count without a syscall. No byte/work/latency equivalence. |
| Design | [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [include/crown/recovery/session_file.hpp](../../../../../include/crown/recovery/session_file.hpp), [src/runtime/session.cpp § QuerySession::restore_file](../../../../../src/runtime/session.cpp), [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [tests/support/checkpoint_file_probe.hpp](../../../../../tests/support/checkpoint_file_probe.hpp) |

```text
if(stage==FileStage::rename_file)publication=PublicationState::unknown;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Latch conservative publication knowledge before any rename effect. |
| inputs / outputs | An admitted rename stage in; io.publication becomes unknown. |
| invariants | Even injected error_before or EINTR is reported unknown once the dispatcher reaches this point. Ordinary quota rejection occurs earlier and leaves prior phase unchanged. |
| ownership | No ownership change until caller observes rename success; private exists marker remains true on error. |
| failure | Neither caller nor cleanup assumes rollback after this latch. Successful rename advances to published_unsynced at the caller. |
| cost | One scalar state store; no new syscall or guard. |
| Design | [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [include/crown/recovery/session_file.hpp](../../../../../include/crown/recovery/session_file.hpp), [src/runtime/session.cpp § QuerySession::restore_file](../../../../../src/runtime/session.cpp), [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp) |

## B0015

[Lines 143–167](../../../../../src/recovery/session_file.cpp#L143); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SessionFileReader::SessionFileReader(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open an anchored regular checkpoint and preflight the fixed316-byte cap preamble. |
| inputs / outputs | Path/limits in; owned directory/file fds, original stat, full size, prefix and captured memory ceiling. |
| invariants | No-follow nonblocking final open; size&gt;=316 and within envelope bytes/SIZE_MAX before any buffer allocation. Version, booleans/enums, length, hash alphabet and policy encodings checked. Full checksum is not verified yet. The same fixed cap preamble admits state versions 1 and 2; the later extension does not move policy/cap fields. |
| ownership | Owns fds and stack prefix only; file offset ends at316. memory_limit_ is an untrusted captured policy until complete validation, optionally overridden by caller. |
| failure | File/ImageFailure during constructor unwinds acquired fds. No surviving loader or native session is published. |
| cost | Fixed prefix reads/parse plus directory/file opens and fstat; prefix byte budget is separate from later full codec accounting. |
| Design | [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [include/crown/recovery/session_file.hpp](../../../../../include/crown/recovery/session_file.hpp), [src/runtime/session.cpp § QuerySession::restore_file](../../../../../src/runtime/session.cpp), [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [src/runtime/checkpoint_policy.hpp § checkpoint_options](../../../../../src/runtime/checkpoint_policy.hpp), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0016

[Lines 168–180](../../../../../src/recovery/session_file.cpp#L168); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ImageVector<char> SessionFileReader::read(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Complete one file read into the actual receiving account before native decode. |
| inputs / outputs | Live loader after constructor and account in; owning full file buffer out. |
| invariants | Copy prefix, read remainder, require exact EOF and unchanged fd stat, then release+checked-close file and directory. The buffer is not yet checksum/native validated. |
| ownership | Exactly one ImageVector allocation path owns the full bytes; scratch prefix remains inline. On wrapper failure loader destruction closes any still-owned fds. |
| failure | Initial allocation failure precedes new fd progress. After read progress or fd release this object is not a retryable stream; callers unwind/reconstruct it. No explicit poison flag/rewind exists. Close error can reject a fully read buffer. |
| cost | O(file bytes) vector initialization/copy/read, remainder chunk calls, one EOF read, fstat and two checked closes; these are additional to codec work. |
| Design | [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [include/crown/recovery/session_file.hpp](../../../../../include/crown/recovery/session_file.hpp), [src/runtime/session.cpp § QuerySession::restore_file](../../../../../src/runtime/session.cpp), [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp) |

## B0017

[Lines 181–182](../../../../../src/recovery/session_file.cpp#L181); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L181-L182:sha256:b23afc92a44293edd31841f0512be65ae6b91c5f500f762bb06b88c959e15d1f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace detail at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp), [docs/code_specs/files/src/recovery/session_file.cpp.md](session_file.cpp.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0018

[Lines 183–227](../../../../../src/recovery/session_file.cpp#L183); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PublishedCheckpoint publish_session_image(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish a complete inspected session envelope through a private sibling and one final rename. |
| inputs / outputs | Path, borrowed immutable SessionImage bytes, native/file limits in; actual inspected manifest/bytes/operations/durable report out. |
| invariants | Re-inspects bytes instead of trusting mutable image.manifest/statistics; validates path before filesystem access. Caller keeps input immutable and parent namespace trusted. This low-level API does not acquire a session/root lock. |
| ownership | Fixed stack names/entropy/fd owners only after pure inspection; file and directory descriptors are locally owned. No staging heap or account refill. |
| failure | Before rename final target is unchanged; admitted rename failure unknown; successful rename+failed dir sync published_unsynced; successful dir sync+failed dir close durable. Catch cleans private name only and preserves exact failure metadata. |
| cost | One complete session inspection plus O(bytes) writes, bounded entropy/collision/retry calls, file fsync+close, rename, directory fsync+close. Filesystem wall-time and native capture are separate. |
| Design | [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [include/crown/recovery/session_file.hpp](../../../../../include/crown/recovery/session_file.hpp), [src/runtime/session.cpp § QuerySession::restore_file](../../../../../src/runtime/session.cpp), [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [src/recovery/session_image.cpp § inspect_session_image](../../../../../src/recovery/session_image.cpp) |

```text
constexpr std::string_view prefix=".crown-checkpoint-";
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Acquire one exclusive private sibling name without exposing destination early. |
| inputs / outputs | 16 random bytes per naming attempt; .crown-checkpoint- plus32 hex digits. |
| invariants | At most16 name candidates; name must differ from destination; O_EXCL/O_NOFOLLOW prevents overwriting a collision. getrandom uses GRND_NONBLOCK, rejects zero progress and only EINTR retries within quota. |
| ownership | Temporary fd/name becomes owned only after successful open; preexisting collision names are never owned or unlinked. |
| failure | Entropy/open/limit failure before rename leaves prior target unchanged. A successfully acquired temporary is later handled by publication catch. |
| cost | O(1) fixed naming per attempt plus potentially short entropy/read retries, all counted; no heap. |
| Design | [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [include/crown/recovery/session_file.hpp](../../../../../include/crown/recovery/session_file.hpp), [src/runtime/session.cpp § QuerySession::restore_file](../../../../../src/runtime/session.cpp), [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp) |

```text
static_cast<void>(checked(io,FileStage::sync_file,0,file.get()));
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Cross the private-write, visibility and durable-publication boundaries in order. |
| inputs / outputs | Complete private image bytes and owned fds in. |
| invariants | fsync private inode then checked close; one nonretried rename; set published_unsynced; fsync parent then set durable; checked parent close. All allocating native preparation must already be complete in higher-level callers. |
| ownership | release() precedes checked closes so unwind cannot close reused descriptor numbers. After rename success private name no longer exists. |
| failure | No rollback of destination at any later error. Durable state remains durable even if directory close or its quota admission rejects. |
| cost | Two fsyncs, two checked closes and one rename after chunked writes; close quota failure still performs raw close outside counter. |
| Design | [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [include/crown/recovery/session_file.hpp](../../../../../include/crown/recovery/session_file.hpp), [src/runtime/session.cpp § QuerySession::restore_file](../../../../../src/runtime/session.cpp), [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp) |

```text
}catch(const FileFailure& error) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the real named-temporary cleanup and outcome-enrichment boundary. |
| inputs / outputs | FileFailure from private preparation/publication in; rethrows same fault/stage/publication/errno plus cleanup flag. |
| invariants | All throwing operations after temporary creation here are FileFailure paths (test hook is noexcept); codecs ran before the try. No extra catch-all is needed for the inspected production path. |
| ownership | Reset private fd first; if exists is still true, unlink only temporary name best-effort; directory owner survives cleanup and then unwinds. |
| failure | Cleanup failure cannot mask the original failure or claim rollback. After successful rename exists=false, so destination is never deleted. |
| cost | At most one raw file close plus up to8 cleanup unlink attempts and fixed rethrow metadata. |
| Design | [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [include/crown/recovery/session_file.hpp](../../../../../include/crown/recovery/session_file.hpp), [src/runtime/session.cpp § QuerySession::restore_file](../../../../../src/runtime/session.cpp), [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [tests/support/checkpoint_file_probe.hpp](../../../../../tests/support/checkpoint_file_probe.hpp) |

## B0019

[Lines 228–228](../../../../../src/recovery/session_file.cpp#L228); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L228-L228:sha256:95bcfbb6661a8958a33a82a5dc501f63202f4524486b8395aa4ce785f3c26b07
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::recovery at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp), [docs/code_specs/files/src/recovery/session_file.cpp.md](session_file.cpp.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |
