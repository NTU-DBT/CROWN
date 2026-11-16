# `src/recovery/journal_file.cpp` — block usage map

[Source](../../../../../src/recovery/journal_file.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Own locked WAL descriptors, validate prefix state and poison uncertain append attempts.

Snapshot SHA-256: `83fc6874994114dde25d7294a36e24b1f209ae392aa8e58524f4b76dbed24241`. 256 lines partitioned into 30 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../src/recovery/journal_file.cpp#L1) | Imports dependencies; controls preprocessing; declares namespace scope; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 17–17](../../../../../src/recovery/journal_file.cpp#L17) | Callable definition: void set_file_hook(FileHook value,void* data) noexcept | calls  · [reviewed contract](#b0002) |
| [B0003 · 18–20](../../../../../src/recovery/journal_file.cpp#L18) | controls preprocessing; declares namespace scope. |  · [reviewed contract](#b0003) |
| [B0004 · 21–23](../../../../../src/recovery/journal_file.cpp#L21) | Callable definition: \[\[noreturn\]\] void fail(FileFault fault,FileStage stage,FileOutcome outcome,int error=0) | calls FileFailure · [reviewed contract](#b0004) |
| [B0005 · 24–24](../../../../../src/recovery/journal_file.cpp#L24) | Callable definition: bool closing(FileStage stage) | calls ; returns stage==FileStage::close_file \|\| stage==FileStage::close_directory · [reviewed contract](#b0005) |
| [B0006 · 25–25](../../../../../src/recovery/journal_file.cpp#L25) | Callable definition: void raw_close(int fd) noexcept | calls close · [reviewed contract](#b0006) |
| [B0007 · 26–30](../../../../../src/recovery/journal_file.cpp#L26) | Type/record definition: struct Descriptor | returns value · [reviewed contract](#b0007) |
| [B0008 · 31–45](../../../../../src/recovery/journal_file.cpp#L31) | Type/record definition: struct Path |  · [reviewed contract](#b0008) |
| [B0009 · 46–50](../../../../../src/recovery/journal_file.cpp#L46) | Callable definition: bool same(const struct stat& a,const struct stat& b) | calls ; returns a.st_dev==b.st_dev && a.st_ino==b.st_ino && a.st_size==b.st_size && · [reviewed contract](#b0009) |
| [B0010 · 51–51](../../../../../src/recovery/journal_file.cpp#L51) | Callable definition: std::string_view view(const ImageVector&lt;char&gt;& bytes) | calls data, size; returns {bytes.data(),bytes.size()} · [reviewed contract](#b0010) |
| [B0011 · 52–52](../../../../../src/recovery/journal_file.cpp#L52) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0011) |
| [B0012 · 53–54](../../../../../src/recovery/journal_file.cpp#L53) | Callable definition: File::File(const resource::MemoryAccount& account,const Header& header,FileLimits limits) :limits_(limits),cursor_(limits.scan,&h… | calls limits_, cursor_, scratch_, pending_ · [reviewed contract](#b0012) |
| [B0013 · 55–55](../../../../../src/recovery/journal_file.cpp#L55) | Callable definition: File::~File() | calls raw_close · [reviewed contract](#b0013) |
| [B0014 · 56–60](../../../../../src/recovery/journal_file.cpp#L56) | Callable definition: File::File(File&& other) noexcept :limits_(other.limits_),cursor_(std::move(other.cursor_)),scratch_(std::move(other.scratch_)),p… | calls limits_, cursor_, std::move, scratch_ · [reviewed contract](#b0014) |
| [B0015 · 61–113](../../../../../src/recovery/journal_file.cpp#L61) | Callable definition: std::int64_t File::call(FileStage stage,std::size_t requested,int fd,const char* name,int other_fd,const char* other_name, void* … | calls closing, raw_close, fail, testing::hook; returns result; source comment (unverified): // Even an interrupted/failed mutation can have a filesystem effect. Admission · [reviewed contract](#b0015) |
| [B0016 · 114–123](../../../../../src/recovery/journal_file.cpp#L114) | Callable definition: std::int64_t File::checked(FileStage stage,std::size_t count,int fd,const char* name,int other_fd,const char* other_name, void* b… | calls call, closing, fail; returns result; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 124–132](../../../../../src/recovery/journal_file.cpp#L124) | Callable definition: void File::transfer(bool write,char* data,std::size_t size,std::uint64_t offset) | calls checked, std::min, fail; 1 loop sites · [reviewed contract](#b0017) |
| [B0018 · 133–139](../../../../../src/recovery/journal_file.cpp#L133) | Callable definition: bool File::cleanup_temporary(int directory,const char* name) noexcept | calls call; returns true; false; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 140–140](../../../../../src/recovery/journal_file.cpp#L140) | Callable definition: void File::ready() const | calls fail · [reviewed contract](#b0019) |
| [B0020 · 141–145](../../../../../src/recovery/journal_file.cpp#L141) | Callable definition: Scanned File::state() const & | calls ready, state, view; returns result · [reviewed contract](#b0020) |
| [B0021 · 146–146](../../../../../src/recovery/journal_file.cpp#L146) | Callable definition: void File::refresh() | calls checked · [reviewed contract](#b0021) |
| [B0022 · 147–150](../../../../../src/recovery/journal_file.cpp#L147) | Callable definition: void File::unchanged_file() | calls checked, same, fail · [reviewed contract](#b0022) |
| [B0023 · 151–155](../../../../../src/recovery/journal_file.cpp#L151) | Callable definition: void File::retain_pending(std::uint64_t old_records) | calls state, swap, clear · [reviewed contract](#b0023) |
| [B0024 · 156–195](../../../../../src/recovery/journal_file.cpp#L156) | Callable definition: File File::create(const resource::MemoryAccount& account,std::string_view path,const Header& header,FileLimits limits) | calls parsed, result, encode, std::move; returns result; 5 loop sites; source comment (unverified): // linkat installs a complete synced inode without overwriting any existing · [reviewed contract](#b0024) |
| [B0025 · 196–198](../../../../../src/recovery/journal_file.cpp#L196) | Callable definition: File File::open(const resource::MemoryAccount& account,std::string_view path,const Header& expected,FileLimits limits) | calls open_replay; returns open_replay(account,path,expected,limits,nullptr,nullptr) · [reviewed contract](#b0025) |
| [B0026 · 199–230](../../../../../src/recovery/journal_file.cpp#L199) | Callable definition: File File::open_replay(const resource::MemoryAccount& account,std::string_view path,const Header& expected,FileLimits limits,Repl… | calls parsed, result, checked, data; returns result; growth resize; 2 loop sites; source comment (unverified): // Visitor effects belong to the private receiving factory until the whole · [reviewed contract](#b0026) |
| [B0027 · 231–243](../../../../../src/recovery/journal_file.cpp#L231) | Callable definition: void File::append(std::string_view frame) & | calls ready, fail, state, size; source comment (unverified): // Cursor validation is strong before publication. Once it advances, later · [reviewed contract](#b0027) |
| [B0028 · 244–251](../../../../../src/recovery/journal_file.cpp#L244) | Callable definition: void File::repair_tail() & | calls ready, unchanged_file, checked, state; source comment (unverified): // Truncate only the validated incomplete suffix; complete pending inputs · [reviewed contract](#b0028) |
| [B0029 · 252–255](../../../../../src/recovery/journal_file.cpp#L252) | Callable definition: void File::close() & | calls fail, checked · [reviewed contract](#b0029) |
| [B0030 · 256–256](../../../../../src/recovery/journal_file.cpp#L256) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::recovery::journal · [reviewed contract](#b0030) |

## B0001

[Lines 1–16](../../../../../src/recovery/journal_file.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/recovery/journal_file.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble Linux version-1 journal storage and optional syscall fault instrumentation. |
| inputs / outputs | Public recovery types, platform file/entropy/locking calls and, only under CROWN_RUNTIME_TESTING, thread-local hook/context declarations. |
| invariants | Trusted stable containing namespace and cooperating single writer are assumptions. These local durable/ownership protocols are not paper theorems. |
| ownership | Declarations hold no production query allocation. Testing context is a borrowed thread-local pointer, never a production owner. |
| failure | No filesystem effect or recovery handler is introduced by includes/declarations. |
| cost | No dynamic runtime work for declarations; test hook code is compiled out in ordinary production. |
| Design | [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 17–17](../../../../../src/recovery/journal_file.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void set_file_hook(FileHook value,void* data) noexcept {hook=value;context=data;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install this thread's version-1 journal syscall fault hook in the testing build. |
| inputs / outputs | Hook function and opaque context replace the current thread-local pair; null disables injection. |
| invariants | Only available under CROWN_RUNTIME_TESTING. Test harness must keep context readable until restoring/unsetting the hook. |
| ownership | Borrows context; retains no account, descriptor or callback owner. |
| failure | noexcept scalar assignments; callbacks can alter later syscall behavior but no call occurs here. |
| cost | Two thread-local writes; absent from normal production API/runtime path. |
| Design | [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp) |

## B0003

[Lines 18–20](../../../../../src/recovery/journal_file.cpp#L18); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L20:sha256:2cdf9576c15c73a8f4ece08282d4cdd2a44bb5fb31869defd3a37f40b7b45aed
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the CROWN_JOURNAL_FILE_TESTING hook and its conditional compilation region, then opens the anonymous namespace for journal file helpers. |
| inputs / outputs | No external runtime input/output is performed by the declaration itself; callable signatures in the block describe future use. |
| invariants | Only the CROWN_JOURNAL_FILE_TESTING-enabled build sees the preceding thread-local test hook; the following anonymous-namespace helpers are compiled for the file implementation. |
| ownership | No owner is added merely by a declaration. Typed fields keep the ownership behavior of their C++ types and any explicit account allocator. |
| failure | The preprocessor guard does not catch filesystem errors. Later checked file operations preserve their declared stage/outcome failure carriers. |
| cost | Preprocessor/scope boundary only; test hook code is not present when its testing macro is absent. |
| Design | [src/recovery/journal_file.cpp](../../../../../src/recovery/journal_file.cpp), [docs/code_specs/files/src/recovery/journal_file.cpp.md](journal_file.cpp.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md) |

## B0004

[Lines 21–23](../../../../../src/recovery/journal_file.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[noreturn]] void fail(FileFault fault,FileStage stage,FileOutcome outcome,int error=0) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise a fixed typed version-1 journal file failure. |
| inputs / outputs | Fault, syscall stage, operation outcome and native errno construct the corresponding Failure/FileFailure and never return. |
| invariants | Reports established uncertainty; does not infer rollback, retry, cleanup success or durable acknowledgment from errno alone. |
| ownership | Exception contains fixed enums/errno/flags; no copied diagnostic string or query state. |
| failure | Throws to the caller. Publication catches may enrich cleanup/outcome metadata without erasing the original stage/fault/errno. |
| cost | Fixed failure object; success paths do not call it. |
| Design | [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp) |

## B0005

[Lines 24–24](../../../../../src/recovery/journal_file.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool closing(FileStage stage) {return stage==FileStage::close_file || stage==FileStage::close_directory;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify checked close operations that Linux must execute at most once. |
| inputs / outputs | Stage enum returns true for close_file or close_directory. |
| invariants | EINTR close is not retried; closing a reused descriptor after an ambiguous retry could release another resource. |
| ownership | Scalar enum input/result only. |
| failure | No allocation, syscall or exception for the admitted enum domain. |
| cost | Two bounded comparisons. |
| Design | [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp) |

## B0006

[Lines 25–25](../../../../../src/recovery/journal_file.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void raw_close(int fd) noexcept {if(fd>=0){const int saved=errno;static_cast<void>(::close(fd));errno=saved;}}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release a descriptor best effort while preserving the active errno. |
| inputs / outputs | Nonnegative fd is closed once; negative is ignored, and saved errno is restored. |
| invariants | Destructor/limit cleanup cannot throw. Best-effort release does not certify sync, publication or checked-close success. |
| ownership | Releases the caller-owned fd reference; no allocation or retry. |
| failure | Close error is deliberately ignored in noexcept cleanup. Public close uses the checked boundary instead. |
| cost | At most one close syscall; kernel latency is not bounded by the I/O-attempt counter. |
| Design | [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp) |

## B0007

[Lines 26–30](../../../../../src/recovery/journal_file.cpp#L26); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Descriptor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a temporary directory/file descriptor through scoped unwinding. |
| inputs / outputs | fd starts -1; destructor calls raw_close; release returns fd and resets the owner before a checked close. |
| invariants | Used as local single owner; do not copy this private implicitly copyable carrier. Current call sites do not copy it. |
| ownership | Destructor releases the active descriptor on every path; release transfers responsibility to exactly one checked-close call. |
| failure | Destruction is best effort; no implicit fsync or durable-state rollback. |
| cost | Fixed stack integer; at most one close on destruction. |
| Design | [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp) |

## B0008

[Lines 31–45](../../../../../src/recovery/journal_file.cpp#L31); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Path {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate version-1 journal path and Linux transfer/byte limits before opening anything. |
| inputs / outputs | Nonempty non-NUL path and limits populate zero-initialized fixed parent/name arrays, separating last component and parent directory. |
| invariants | Require representable path/chunk/off_t domains, positive operation/chunk limits and minimum frame allowance; basename cannot be empty, dot or dot-dot. Parent path may follow trusted namespace components; no adversarial-directory security claim. |
| ownership | Copies path bytes into stack arrays; no borrowed path survives the call and no query heap account is created. |
| failure | Fixed path/limit failure reports unchanged before any open or mutation. |
| cost | O(path bytes) scans/copies and two 4096-byte stack arrays; no heap allocation. |
| Design | [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp) |

## B0009

[Lines 46–50](../../../../../src/recovery/journal_file.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same(const struct stat& a,const struct stat& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check admitted file identity and change-sensitive metadata. |
| inputs / outputs | Two stat records compare device, inode, size, mtime and ctime including nanoseconds. |
| invariants | Used with exact EOF/frame validation in a trusted stable namespace; this is not a cryptographic defense against noncooperating mutation. |
| ownership | Borrows two stack/value records; returns Boolean. |
| failure | No syscall/allocation/error translation within this helper. |
| cost | Fixed field comparisons. |
| Design | [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp) |

## B0010

[Lines 51–51](../../../../../src/recovery/journal_file.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view view(const ImageVector<char>& bytes) {return {bytes.data(),bytes.size()};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow encoded file bytes without an ordinary string mirror. |
| inputs / outputs | Accounted ImageVector&lt;char&gt; returns string_view over its current data/size. |
| invariants | View is valid only while that vector storage remains unchanged/alive; it does not extend ownership or freeze bytes. |
| ownership | No allocation/copy; caller retains the vector. |
| failure | No validation or syscall here. |
| cost | Constant pointer/size construction. |
| Design | [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp) |

## B0011

[Lines 52–52](../../../../../src/recovery/journal_file.cpp#L52); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L52-L52:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/journal_file.cpp](../../../../../src/recovery/journal_file.cpp), [docs/code_specs/files/src/recovery/journal_file.cpp.md](journal_file.cpp.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md) |

## B0012

[Lines 53–54](../../../../../src/recovery/journal_file.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
File::File(const resource::MemoryAccount& account,const Header& header,FileLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize a private journal scanner and two account-funded buffer allocators. |
| inputs / outputs | Receiver account, copied expected Header and FileLimits initialize Cursor and empty scratch/pending vectors. |
| invariants | Cursor copies its header binding; no fd is opened and no record is admitted until create/open. Original receiving account remains authoritative. |
| ownership | Vectors retain receiver-account allocators. Cursor owns fixed metadata; no caller header pointer escapes. |
| failure | Private construction precedes filesystem work; container owners release any partial resources on unwind. |
| cost | Fixed Cursor/limits plus empty buffer allocators; no whole-log allocation. |
| Design | [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp) |

## B0013

[Lines 55–55](../../../../../src/recovery/journal_file.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
File::~File(){raw_close(fd_);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | End version-1 journal ownership by releasing its fd/lock best effort. |
| inputs / outputs | Current fd passes to raw_close; member vectors then release their accounted payload. |
| invariants | Destruction is not a checked sync, acknowledgment or filesystem rollback. Closing releases this advisory-lock reference. |
| ownership | Owns fd and scratch/pending frame vectors; member teardown releases their same-account buffers. |
| failure | Destructor cleanup does not throw; caller must use checked close when an error outcome is needed. |
| cost | One close syscall plus buffer/account release; may deallocate capacity, with no file-prefix scan. |
| Design | [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp) |

## B0014

[Lines 56–60](../../../../../src/recovery/journal_file.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
File::File(File&& other) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer the sole version-1 journal descriptor, validation state and buffers. |
| inputs / outputs | Move constructor transfers limits, scanner/header/index, buffers, fd/stamp/counters/outcome/poison/torn state; source fd becomes -1 and source poisoned. |
| invariants | No second live writer/lock owner is created. Source must not be used for further file operations. |
| ownership | Moves accounted vectors/metadata and fd; destination retains existing account authority, without reopening or allocating a fresh grant. |
| failure | noexcept move; no filesystem syscall, sync or catch. |
| cost | Constant moves of fixed metadata/array and vector handles, not a copy of stored epochs/log bytes. |
| Design | [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp) |

## B0015

[Lines 61–113](../../../../../src/recovery/journal_file.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::int64_t File::call(FileStage stage,std::size_t requested,int fd,const char* name,int other_fd,const char* other_name,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Perform one bounded Linux syscall attempt for the version-1 journal owner. |
| inputs / outputs | Validated stage-specific descriptors/names/buffer/offset/request drive openat/flock/pread/pwrite/fsync/linkat/unlinkat/ftruncate/close or entropy; returns result and sets errno. |
| invariants | Every attempt debits operations, including EINTR. Temporary cleanup bypasses ordinary cap but not U64 exhaustion. Admitting write/truncate/final link sets outcome unknown before the syscall, even on interruption; close executes once. Test-only hooks preserve real close and prevent hidden opened-fd leaks on synthetic after-open errors. Only the explicit emergency_cleanup flag from the eight-attempt failure helper bypasses the ordinary operation cap; normal post-link unlink/EINTR does not. |
| ownership | Borrows call buffers/names only synchronously; returned descriptors immediately enter a scoped/File owner at call sites. No buffer allocation in dispatcher. |
| failure | Limit/state failures throw fixed file Failure with current outcome; otherwise errno/result are interpreted by checked/caller. Close still releases fd when operation budget rejects its checked attempt. |
| cost | One syscall attempt plus fixed dispatch/counters, optionally transferring requested bytes. Attempts/byte caps do not bound fsync/lock/kernel wall time. |
| Design | [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp), [tests/unit/file_cleanup_quota_test.cpp](../../../../../tests/unit/file_cleanup_quota_test.cpp) |

## B0016

[Lines 114–123](../../../../../src/recovery/journal_file.cpp#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::int64_t File::checked(FileStage stage,std::size_t count,int fd,const char* name,int other_fd,const char* other_name,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Interpret version-1 journal syscall results and retry only safe interrupted stages. |
| inputs / outputs | Repeated call returns first nonnegative result; EINTR retries exclude close and final link. |
| invariants | Publication interruption is not retried or assumed absent. EWOULDBLOCK/EAGAIN on nonblocking flock maps busy; other errors map io. |
| ownership | No new resources retained beyond caller-provided fd/buffer; retries consume same cumulative operation budget. |
| failure | Typed Failure preserves syscall stage/current outcome/native errno. Retry ends at success, nonretryable failure or operation cap. |
| cost | One syscall per loop iteration; finite attempt budget bounds retries, not elapsed kernel time. |
| Design | [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp) |

## B0017

[Lines 124–132](../../../../../src/recovery/journal_file.cpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void File::transfer(bool write,char* data,std::size_t size,std::uint64_t offset) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Complete a bounded positional version-1 journal read/write over short transfers. |
| inputs / outputs | Mutable buffer, byte count and validated offset loop checked pread/pwrite in at most configured chunk bytes until done. |
| invariants | Caller ensures offset/size fit admitted file/off_t bounds and buffer lifetime. Positive short transfers advance; zero write is EIO and zero read is truncated. |
| ownership | Borrows caller storage for this synchronous call; no copy/mirror/heap allocation here. |
| failure | Propagates fixed syscall/limit/zero-progress failure with current uncertainty. Writes may partially persist; no inverse/truncate-on-error is attempted. |
| cost | O(bytes transferred) kernel traffic and ceil(bytes/chunk) successful calls plus bounded EINTR retries. |
| Design | [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp) |

## B0018

[Lines 133–139](../../../../../src/recovery/journal_file.cpp#L133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool File::cleanup_temporary(int directory,const char* name) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove a private temporary name during version-1 journal exception unwinding. |
| inputs / outputs | Directory fd and private generated name attempt unlink up to eight times; success/ENOENT returns true. |
| invariants | Only EINTR retries. Mandatory temp cleanup bypasses ordinary operation cap, without permitting final-file rollback or history deletion. This fixed helper alone requests emergency_cleanup; normal publication cannot inherit the exemption by syscall stage. |
| ownership | Borrows name/directory; never unlinks the public destination from this helper. |
| failure | noexcept catch converts call exceptions/limit exhaustion to false, preserving the original publishing failure. Failed cleanup can leave an orphan temp. |
| cost | At most eight unlink attempts; no allocation/sync or directory scan. |
| Design | [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp), [tests/unit/file_cleanup_quota_test.cpp](../../../../../tests/unit/file_cleanup_quota_test.cpp) |

## B0019

[Lines 140–140](../../../../../src/recovery/journal_file.cpp#L140); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void File::ready() const {if(fd_<0 || poisoned_)fail(FileFault::state,FileStage::state,FileOutcome::unchanged);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject closed, moved-from or poisoned version-1 journal owners. |
| inputs / outputs | File fd/poison state returns normally only when fd&gt;=0 and not poisoned. |
| invariants | A failed post-validation I/O path must reopen/validate rather than blindly continue. This check does not itself rescan disk. |
| ownership | Reads owner flags; retains nothing. |
| failure | Fixed state Failure with unchanged attempted-operation outcome; no repair or implicit retry. |
| cost | Constant branches, no syscall or allocation. |
| Design | [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp) |

## B0020

[Lines 141–145](../../../../../src/recovery/journal_file.cpp#L141); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Scanned File::state() const & {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the admitted journal prefix and borrow its retained pending input frame. |
| inputs / outputs | Ready lvalue File copies Cursor Scanned, adds torn-tail flag, and rebases pending.frame to pending_ storage. |
| invariants | Only healthy completed/adopted operations expose state. View remains valid until another owner operation, move or destruction; rvalue state() is deleted. |
| ownership | Fixed metadata copy contains a borrowed frame; retain/synchronize this File when decoding it. No record array is copied. |
| failure | Closed/poisoned owner rejects; no disk revalidation or allocation. |
| cost | Constant fixed Scanned copy and optional view rebasing. |
| Design | [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp) |

## B0021

[Lines 146–146](../../../../../src/recovery/journal_file.cpp#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void File::refresh(){static_cast<void>(checked(FileStage::stat_file,0,fd_,nullptr,-1,nullptr,nullptr,0,&stamp_));}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record current stat metadata after admitted version-1 journal progress. |
| inputs / outputs | Checked fstat(fd) replaces stamp_. |
| invariants | Caller invokes only on an owned descriptor. Refresh does not prove content correctness or perform fsync by itself. |
| ownership | Writes fixed stat record; borrows no payload. |
| failure | Operation/syscall failure propagates; after durable write callers may remain poisoned despite durable outcome. |
| cost | One checked fstat attempt plus allowed EINTR retries. |
| Design | [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp) |

## B0022

[Lines 147–150](../../../../../src/recovery/journal_file.cpp#L147); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void File::unchanged_file() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that the owned version-1 journal file still matches its admitted stamp. |
| inputs / outputs | Checked fstat compared with stamp_ fails changed on inode/size/mtime/ctime mismatch. |
| invariants | Assumes cooperating single writer and stable trusted namespace; hash/frame/EOF validation remains separate. |
| ownership | Stack stat record, no retained allocation. |
| failure | Typed changed/io/limit failure preserves current outcome; no automatic rescan/rollback. |
| cost | One checked fstat plus fixed comparisons, not a file scan. |
| Design | [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp) |

## B0023

[Lines 151–155](../../../../../src/recovery/journal_file.cpp#L151); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void File::retain_pending(std::uint64_t old_records) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep only the exact encoded pending input needed by later commits/recovery. |
| inputs / outputs | After successful Cursor feed, new pending input at old_records swaps scratch_ into pending_; fully completed command clears pending_. |
| invariants | A partial window commit retains the original pending input rather than replacing it with a commit frame. cursor/state views are rebound by File::state. |
| ownership | Same-allocator vector swap transfers frame ownership without byte copy; clear retains capacity and ends byte-view lifetime. |
| failure | No throwing growth or syscall here; invoked only after durable append/admitted open replay step. |
| cost | Constant vector swap/byte-vector clear; no whole-file or row scan. |
| Design | [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp) |

## B0024

[Lines 156–195](../../../../../src/recovery/journal_file.cpp#L156); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
File File::create(const resource::MemoryAccount& account,std::string_view path,const Header& header,FileLimits limits) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create and durably publish a fresh version-1 journal without replacing any existing destination. |
| inputs / outputs | Account/path/expected journal Header/limits privately encode/admit initial validated journal record header, create an entropy-named 0600 O_EXCL sibling, lock it, write/fsync, link without replacement, unlink temp and fsync parent; returns sole File owner. |
| invariants | Existing final file/symlink is never replaced. At most sixteen name attempts; safe entropy/open retries consume cumulative operations. Final link is never retried on EINTR. Success adopts both complete header and directory entry as durable. |
| ownership | Account funds initial encoded bytes/scratch/pending frame vectors; scoped directory and returned File own descriptors. Generated path/name arrays stay on stack. |
| failure | Typed publication catch cleans only temp and enriches cleanup failure; before final-link admission it normalizes operation outcome unchanged, even if private inode bytes were written. Link-stage/postpublication uncertainty remains. Broad cleanup catch preserves other original exceptions. Final destination is never rolled back. |
| cost | Header encode/hash/copy plus bounded entropy/create attempts, write chunks, file fsync, link/unlink, directory fsync and metadata refresh. No old-prefix scan. |
| Design | [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp), [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp) |

## B0025

[Lines 196–198](../../../../../src/recovery/journal_file.cpp#L196); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
File File::open(const resource::MemoryAccount& account,std::string_view path,const Header& expected,FileLimits limits) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open a journal through the single prefix-validation implementation. |
| inputs / outputs | Account/path/expected Header/limits call open_replay with no visitor/context and return its locked File. |
| invariants | No alternate permissive scanner or implicit tail repair is introduced. |
| ownership | Returned File owns original-account buffers and fd; caller input path/header are not borrowed afterward. |
| failure | All open/scan/adoption failures propagate from open_replay; local result remains private until success. |
| cost | Constant dispatch plus whole-prefix scan and sync cost of open_replay. |
| Design | [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp) |

## B0026

[Lines 199–230](../../../../../src/recovery/journal_file.cpp#L199); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
File File::open_replay(const resource::MemoryAccount& account,std::string_view path,const Header& expected,FileLimits limits,ReplayVisitor visitor,void* context) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate/adopt a journal incrementally while optional replay effects remain private. |
| inputs / outputs | Account/path/exact expected Header/limits open no-follow regular fd, flock, scan bounded frames through Cursor, retain pending bytes, invoke optional visitor per complete record and recognize only valid incomplete suffix. |
| invariants | Exact EOF/stamp, file fsync and directory fsync complete adoption. Visitor can mutate only private receiving-factory state until all checks finish; no old record corruption is repaired. Complete visible records become the durable prefix. |
| ownership | File owns fd/lock and account-funded scratch/pending buffers; visitor borrows current frame/state synchronously. Caller must retain any needed metadata independently before next frame. |
| failure | Any visitor, validation/allocation/work/I/O/stamp/sync failure unwinds private File and receiving factory. No file truncate/append occurs in open; later repair is explicit and follows native/source validation. |
| cost | O(file bytes) one-frame-at-a-time reads/hash/codec, per-record visitor cost and fixed state, plus stat/lock/EOF/file+directory sync. Retains bounded scratch and pending frame, not all log records. |
| Design | [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp) |

```text
const auto records=result.cursor_.state().records;const auto state=result.cursor_.feed(view(result.scratch_));
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one exact next WAL record before invoking the receiving recovery visitor. |
| inputs / outputs | Cursor.feed validates private next state; optional visitor receives the current frame/state before pending-buffer transfer. |
| invariants | Visitor side effects remain private until full prefix/EOF/stamp/sync and later native/source validation complete; they do not make half-replayed state public. |
| ownership | Views borrow scratch only synchronously. Retain_pending owns a required input frame by swap afterward. |
| failure | Visitor or frame failure destroys private File/factory; no disk append/truncate or committed-owner rollback. |
| cost | Incremental per-frame codec work + caller visitor processing; no second full-log clone. |
| Design | [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp) |

## B0027

[Lines 231–243](../../../../../src/recovery/journal_file.cpp#L231); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void File::append(std::string_view frame) & {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate and durably append exactly one next journal frame without rescanning history. |
| inputs / outputs | Ready non-torn lvalue File checks cumulative bytes, copies frame to account scratch, advances private Cursor, poisons then checks stamp/writes at prior consumed end/fsyncs/refreshes and retains pending input. |
| invariants | Cursor.feed has a private-copy strong guarantee on validation error. After successful feed, subsequent I/O/metadata failure leaves owner poisoned because Cursor may be ahead of durable bytes. No rollback truncation or in-place retry. |
| ownership | Caller frame borrowed only for scratch copy; retained pending_ owns the actual encoded input. Same original account funds simultaneous old/new buffers. |
| failure | Allocation/codec validation failure before feed publication preserves old disk/Cursor; after feed success poisoned remains until write+sync+refresh/pending handoff complete. fsync can establish durable outcome before later refresh failure. |
| cost | O(frame bytes) copy/validate/hash and positional write chunks+file fsync+stat; constant scanner state/pending swap. No old-record scan or whole-state copy. |
| Design | [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [tests/unit/journal_file_test.cpp](../../../../../tests/unit/journal_file_test.cpp) |

```text
static_cast<void>(cursor_.feed(view(scratch_)));poisoned_=true;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mark journal state recovery-required once in-memory next-record admission precedes I/O. |
| inputs / outputs | Successful strong-guarantee Cursor.feed advances private scanner; poison is immediately set before unchanged-file/write/sync operations. |
| invariants | A complete frame can survive an I/O error; undoing Cursor alone would not revoke filesystem authority. Reopen validates/adopts surviving prefix. |
| ownership | Scratch owns frame; native session retains its own decision/output authority above this file layer. |
| failure | Pre-feed validation failure leaves old scanner; all later failures keep poison until complete durable write/refresh/pending handoff. |
| cost | Constant poison assignment after bounded per-record validation; no added inverse log/state copy. |
| Design | [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp) |

## B0028

[Lines 244–251](../../../../../src/recovery/journal_file.cpp#L244); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void File::repair_tail() & {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Durably discard only a previously validated incomplete journal tail. |
| inputs / outputs | Ready owner resets attempted outcome, returns if non-torn, otherwise poisons/checks stamp/truncates at Cursor.consumed/fsyncs/refreshes and clears torn/poison. |
| invariants | Every complete record, including pending input or partial window command commit, remains. This does not retire committed history or grant output acknowledgment. |
| ownership | Operates on the existing locked fd and scanner prefix; no new buffer or source state. |
| failure | Failure after poison requires reopen; truncate admission marks unknown, sync durable, later metadata failure can still poison. |
| cost | Fixed metadata checks plus fstat/truncate/fsync/refresh; no prefix rescan. |
| Design | [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp), [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp) |

## B0029

[Lines 252–255](../../../../../src/recovery/journal_file.cpp#L252); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void File::close() & {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release journal writer ownership with a checked one-shot Linux close. |
| inputs / outputs | Lvalue open owner clears fd_ before passing the former fd to checked close. |
| invariants | Does not sync or undo a previous append and cannot be retried through this owner after close ambiguity. |
| ownership | Close ends this inode-lock reference; accounted buffers remain until File destruction. |
| failure | Closed rejects; close failure propagates once, including EINTR. Operation-budget failure still releases fd best effort. |
| cost | One close syscall plus fixed state change. |
| Design | [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp) |

## B0030

[Lines 256–256](../../../../../src/recovery/journal_file.cpp#L256); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L256-L256:sha256:ade4c7e26c3c86f66e5229b8a85c7b0beb63c4bdd3dee7de6f59075c925502ba
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::recovery::journal at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/journal_file.cpp](../../../../../src/recovery/journal_file.cpp), [docs/code_specs/files/src/recovery/journal_file.cpp.md](journal_file.cpp.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md) |
