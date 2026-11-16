# `src/recovery/sql_aggregate_file_detail.hpp` — block usage map

[Source](../../../../../src/recovery/sql_aggregate_file_detail.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `be7805381eed114b2ee6e1e5725b18b390df2b7afabd7cf03823f1e958a0cdde`. 76 lines partitioned into 7 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../src/recovery/sql_aggregate_file_detail.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Stack descriptor guard for directory handles; explicit release enables one · [reviewed contract](#b0001) |
| [B0002 · 11–19](../../../../../src/recovery/sql_aggregate_file_detail.hpp#L11) | Type/record definition: struct Directory | source comment (unverified): // Stack descriptor guard for directory handles; explicit release enables one · [reviewed contract](#b0002) |
| [B0003 · 20–20](../../../../../src/recovery/sql_aggregate_file_detail.hpp#L20) | Explanatory comments or spacing. | source comment (unverified): // Fixed path split: no unaccounted owning string, embedded NUL or empty basename. · [reviewed contract](#b0003) |
| [B0004 · 21–24](../../../../../src/recovery/sql_aggregate_file_detail.hpp#L21) | Type/record definition: struct Path | source comment (unverified): // Fixed path split: no unaccounted owning string, embedded NUL or empty basename. · [reviewed contract](#b0004) |
| [B0005 · 25–44](../../../../../src/recovery/sql_aggregate_file_detail.hpp#L25) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Validate all available envelope bytes before trusting a stored body length. · [reviewed contract](#b0005) |
| [B0006 · 45–45](../../../../../src/recovery/sql_aggregate_file_detail.hpp#L45) | Type/record definition: struct stat stamp |  · [reviewed contract](#b0006) |
| [B0007 · 46–76](../../../../../src/recovery/sql_aggregate_file_detail.hpp#L46) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Create installs one synced header without replacing any existing entry. · [reviewed contract](#b0007) |

## B0001

[Lines 1–10](../../../../../src/recovery/sql_aggregate_file_detail.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:7b1366c9139ad7dc252f3f5e61598679a8507bbbcb8bc295f8bcf97bc412bce6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Header guard and regular-file descriptor dependencies; opens the private file_detail namespace, declares the fixed failure/raw-close entry points, and begins the stack Directory descriptor guard. Embedded source note records intended usage: Stack descriptor guard for directory handles; explicit release enables one checked close without accidentally retrying Linux close after EINTR. Treat that prose as guidance, not as independently verified executable behavior. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/recovery/sql_aggregate_file_detail.hpp](../../../../../src/recovery/sql_aggregate_file_detail.hpp), [docs/code_specs/files/src/recovery/sql_aggregate_file_detail.hpp.md](sql_aggregate_file_detail.hpp.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0002

[Lines 11–19](../../../../../src/recovery/sql_aggregate_file_detail.hpp#L11); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L11-L19:sha256:611bbee3da94913e387c3ce4c80bfaad19be06c8558b2f8be7c9de4a7e522109
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent exclusive stack ownership of a directory FD across factory admission and confirmation. |
| inputs / outputs | Default state is -1; move takes release() from another guard; explicit release returns the FD and clears this guard before a checked close. |
| invariants | Copy and assignment are deleted, and a released/moved guard cannot raw-close that FD again. |
| ownership | The guard owns only one int descriptor, using raw_close in destruction without retaining a pathname or account. |
| failure | Destructor is best effort and preserves errno; checked errors belong to the caller that first releases the FD. |
| cost | Constant stack storage and transfer; destruction performs at most one unmetered raw close. |
| Design | [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0003

[Lines 20–20](../../../../../src/recovery/sql_aggregate_file_detail.hpp#L20); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L20:sha256:a6445e836d66940d49ad4f543fd21352665283b615e40c7bb184dffd08ebb1d2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Fixed path split: no unaccounted owning string, embedded NUL or empty basename. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/recovery/sql_aggregate_file_detail.hpp lines 18-22; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/recovery/sql_aggregate_file_detail.hpp](../../../../../src/recovery/sql_aggregate_file_detail.hpp), [docs/code_specs/files/src/recovery/sql_aggregate_file_detail.hpp.md](sql_aggregate_file_detail.hpp.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0004

[Lines 21–24](../../../../../src/recovery/sql_aggregate_file_detail.hpp#L21); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L24:sha256:4880e7681ffb6564e3e4dcfafc209e3f24ab6118e6a88624a3c2f933efb9e7b4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store a validated path split in bounded zero-initialized arrays for POSIX calls. |
| inputs / outputs | A borrowed path and FileLimits enter construction; parent/name hold NUL-terminated directory and basename bytes afterward. |
| invariants | No embedded NUL or empty/dot/dotdot basename is admitted, and path size fits both 4096-byte arrays. Limits are validated before syscall work. |
| ownership | Both 4096-byte arrays are owned inline; no ordinary or accounted string allocation and no input lifetime dependency is retained. |
| failure | Bad policy throws FileFailure(limit,path,unchanged); bad path throws FileFailure(path,path,unchanged), before a file can change. |
| cost | O(path bytes) find/copy and 8192 inline bytes, bounded by path_bytes; no filesystem normalization or traversal-proof cost is claimed. |
| Design | [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0005

[Lines 25–44](../../../../../src/recovery/sql_aggregate_file_detail.hpp#L25); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::string_view view(const ImageVector<char>&) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the shared borrowing, descriptor-binding and fixed-envelope/tail/hash helpers used by both file owners. |
| inputs / outputs | view borrows scratch bytes; binding checks a genuine Descriptor hash; envelope/tail inspect available transport evidence; chain returns a fixed 64-byte digest. The shared envelope/Io declarations now accept one exactly eight-byte record-family magic, default CROWNAG2; rows owners explicitly supply CROWNRW2. |
| invariants | These helpers do not construct native state or declare a partial body authentic. Full record inspection and replay remain separate caller steps. Magic selects only framing. Complete typed row/group validation and genuine admission remain separate; default aggregate behavior and every I/O/length/hash rule are unchanged. |
| ownership | Borrowed Descriptor/vector/views must outlive each call; returned views retain no memory ownership, while Hash is a fixed value. Io stores eight inline bytes rather than a borrowed magic string; no additional allocation/account or callback state is retained. |
| failure | Transport validation reports ImageFailure and a borrowed view cannot make a Frame/SinkReceipt authority; helpers contain no file retry logic. Invalid magic width is a fixed binding failure at construction/envelope admission; no fallback or family guessing. |
| cost | Bounded envelope/tail work is at most 148/157 bytes, binding compares one fixed hash, and chain hashes exactly 128 bytes. Fixed eight-byte owner storage/copy and bounded prefix comparisons; no data-size-dependent new state or virtual dispatch. |
| Design | [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

```text
struct Io {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Confine Linux file lifetime, finite I/O grants, stamps, tail status and uncertainty to the R2 transport owners. |
| inputs / outputs | Private file owners call bounded create/open/read/append/repair/close plus a stamp/EOF validation barrier; the latter observes the held full physical file and never authorizes repair itself. The shared envelope/Io declarations now accept one exactly eight-byte record-family magic, default CROWNAG2; rows owners explicitly supply CROWNRW2. |
| invariants | No source/native token, prepared transaction, undo journal, semantic replay policy or command/output queue exists in Io. All metered POSIX operations use its central FileStage switch. Magic selects only framing. Complete typed row/group validation and genuine admission remain separate; default aggregate behavior and every I/O/length/hash rule are unchanged. |
| ownership | Io owns the FD and fixed limits/stat/counters; owner Data funds external schema/index/scratch. Copy is deleted to preserve unique descriptor ownership. Io stores eight inline bytes rather than a borrowed magic string; no additional allocation/account or callback state is retained. |
| failure | FileFailure covers stage/fault/outcome/errno; ImageFailure covers logical work/wire checks. Main paths propagate directly; only create cleanup and the eight-attempt cleanup helper catch. Invalid magic width is a fixed binding failure at construction/envelope admission; no fallback or family guessing. |
| cost | Constant retained Io storage; chunked transfers spend finite syscall attempts while byte/frame owners supply their actual funded buffers. Fixed eight-byte owner storage/copy and bounded prefix comparisons; no data-size-dependent new state or virtual dispatch. |
| Design | [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [src/recovery/sql_aggregate_wal_file.cpp](../../../../../src/recovery/sql_aggregate_wal_file.cpp), [src/recovery/sql_aggregate_sink_file.cpp](../../../../../src/recovery/sql_aggregate_sink_file.cpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0006

[Lines 45–45](../../../../../src/recovery/sql_aggregate_file_detail.hpp#L45); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L45:sha256:6c393f332426eeef7080af3bf91e66d875dacef4437b0a5f37e7aab151c81b13
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the last confirmed inode identity/size/time stamp used to detect cooperating-file changes. |
| inputs / outputs | refresh fills stamp through fstat; unchanged compares a fresh stat; read/append offsets and complete-size checks use stamp.st_size. |
| invariants | Comparison covers device, inode, size, mtime and ctime seconds/nanoseconds; this field is a stat value initializer, not a new semantic type despite lexical segmentation. |
| ownership | The struct stat object is inline Io state and retains no FD of its own or name-resolution authority. |
| failure | A changed stamp rejects the operation; timestamps/advisory locking are local cooperation checks, not a malicious concurrent-writer or trusted-namespace proof. |
| cost | One fixed OS metadata object, O(1) comparisons and one metered fstat for refresh/unchanged. |
| Design | [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0007

[Lines 46–76](../../../../../src/recovery/sql_aggregate_file_detail.hpp#L46); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void create(const Path&,std::string_view header);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the private create/open/final-open confirmation protocol used only after owner schema/path admission. |
| inputs / outputs | create consumes a validated Path and complete encoded header; open returns a guarded directory; finish_open confirms scanned bytes and closes that guard. |
| invariants | create uses a same-directory no-replace link after header fsync. Open does not truncate and exposes no public owner until EOF/stamps and both syncs succeed. |
| ownership | Io keeps the file FD; returned Directory temporarily owns the directory FD; header bytes and Path arrays are borrowed only for each call. |
| failure | Acquisition/publication/sync failures propagate fixed metadata; create alone performs bounded temporary-name cleanup and does not roll back an uncertain published name. |
| cost | Finite entropy/collision/operation budgets and chunked header I/O; full scan is done by the owners between open and finish_open. |
| Design | [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [src/recovery/sql_aggregate_wal_file.cpp](../../../../../src/recovery/sql_aggregate_wal_file.cpp), [src/recovery/sql_aggregate_sink_file.cpp](../../../../../src/recovery/sql_aggregate_sink_file.cpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

```text
[[nodiscard]] bool read_frame(std::uint64_t,ImageVector<char>&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare bounded reading of complete records or minimal evidence of an incomplete final frame. |
| inputs / outputs | An admitted offset and receiving-account scratch enter; true supplies complete bytes, false supplies validated partial envelope/kind/ordinal evidence and marks torn. |
| invariants | Protected length is checked before body resize. A partial body retains at most 157 bytes; the actual full file size is still covered by EOF/stamp confirmation. |
| ownership | Scratch stays owner-funded and mutable only within the scan; no body is decoded or native rows retained by this interface. |
| failure | A short first frame is fatal, malformed available bytes fail ImageFailure, and read failures are FileFailure; caller validates permissible next kind/ordinal. |
| cost | Full frames require O(frame bytes) scratch/read plus codec inspection elsewhere; partial retention/read is capped at 148+9 bytes. |
| Design | [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [src/recovery/sql_aggregate_wal_file.cpp](../../../../../src/recovery/sql_aggregate_wal_file.cpp), [src/recovery/sql_aggregate_sink_file.cpp](../../../../../src/recovery/sql_aggregate_sink_file.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp) |

```text
std::int64_t call(FileStage,std::size_t=0,int=-1,const char* =nullptr,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the sole metered typed-argument POSIX dispatcher and its checked EINTR wrapper. |
| inputs / outputs | Stage plus size, FD/name pairs, buffer, offset and optional stat pointer select the syscall; call returns int64_t result/errno and checked returns success or throws. |
| invariants | The private emergency_cleanup argument defaults false; only the eight-attempt temporary cleanup passes true. Ordinary unlink obeys the normal operations cap; selected name/buffer/stat-pointer arguments are checked at the libc case boundary while irrelevant arguments may be null. |
| ownership | All pointers/FDS are borrowed for one synchronous invocation; the dispatcher does not allocate a request object or own an asynchronous command queue. |
| failure | Every admitted attempt increments operations; overflow always fails. A missing stage-required name, buffer or stat pointer fails state before libc; checked retries EINTR except close and uncertain link, and busy flock maps to a distinct fault. |
| cost | O(1) dispatch/counter work per syscall attempt; bounded normal operation count plus at most eight emergency unlink attempts per create cleanup. |
| Design | [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

```text
void transfer(bool,char*,std::size_t,std::uint64_t);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep chunked exact transfer and mandatory temporary-name cleanup private to Io. |
| inputs / outputs | transfer borrows a buffer and offset, selecting read/write with a Boolean; cleanup borrows directory/name and returns whether the temporary name was removed or absent. |
| invariants | Transfers require progress and bound each chunk; cleanup has exactly one local maximum of eight attempts and cannot activate a general retry framework. |
| ownership | Neither helper retains bytes/name beyond its call; cleanup owns no directory/file FD and relies on the create boundary guard. |
| failure | Zero read is truncated, zero write is EIO; cleanup is noexcept and reports false instead of throwing a nested error. |
| cost | Transfer takes O(bytes) I/O with ceil(bytes/chunk_bytes) successful chunks plus finite interrupted/short attempts; cleanup is O(8) attempts. |
| Design | [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

```text
void validate();
  void refresh
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the private stamp/EOF barrier separately from stamp refresh and tail truncation. |
| inputs / outputs | Io callers request validation of their already held full physical extent. |
| invariants | Validation compares the accepted stamp instead of silently adopting changed bytes; refresh remains the separate postwrite stamp operation. |
| ownership | No additional member/storage is declared. |
| failure | Actual validation poisons before I/O and clears only after agreement. |
| cost | Declaration cost zero; implementation is constant-space, bounded real I/O. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [src/recovery/sql_aggregate_file_detail.hpp](../../../../../src/recovery/sql_aggregate_file_detail.hpp) |
