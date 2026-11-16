# `src/recovery/sql_aggregate_file_detail.cpp` — block usage map

[Source](../../../../../src/recovery/sql_aggregate_file_detail.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `98b4a50d0411a36f82c4b59949f7ddc773d99726fa076d95a86bdf935c8ecc65`. 327 lines partitioned into 40 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L1) | Imports dependencies; controls preprocessing; declares namespace scope; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 19–19](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L19) | Callable definition: void set_file_hook(FileHook value,void* data) noexcept | calls  · [reviewed contract](#b0002) |
| [B0003 · 20–24](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L20) | controls preprocessing; declares namespace scope; declares aliases. | source comment (unverified): // namespace testing · [reviewed contract](#b0003) |
| [B0004 · 25–25](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L25) | Callable definition: bool closing(FileStage stage) noexcept | calls ; returns stage==FileStage::close_file \|\| stage==FileStage::close_directory · [reviewed contract](#b0004) |
| [B0005 · 26–30](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L26) | Callable definition: bool same(const struct stat& a,const struct stat& b) noexcept | calls ; returns a.st_dev==b.st_dev && a.st_ino==b.st_ino && a.st_size==b.st_size && · [reviewed contract](#b0005) |
| [B0006 · 31–31](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L31) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0006) |
| [B0007 · 32–34](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L32) | Callable definition: \[\[noreturn\]\] void fail(FileFault fault,FileStage stage,FileOutcome outcome,int error) | calls FileFailure · [reviewed contract](#b0007) |
| [B0008 · 35–37](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L35) | Callable definition: void raw_close(int fd) noexcept | calls close · [reviewed contract](#b0008) |
| [B0009 · 38–38](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L38) | Callable definition: Directory::Directory(Directory&& other) noexcept : fd(other.release()) | calls fd, release · [reviewed contract](#b0009) |
| [B0010 · 39–39](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L39) | Callable definition: Directory::~Directory() | calls raw_close · [reviewed contract](#b0010) |
| [B0011 · 40–40](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L40) | Callable definition: int Directory::release() noexcept | calls ; returns old · [reviewed contract](#b0011) |
| [B0012 · 41–54](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L41) | Callable definition: Path::Path(std::string_view path,const FileLimits& limits) | calls size, max, fail, empty · [reviewed contract](#b0012) |
| [B0013 · 55–55](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L55) | Callable definition: std::string_view view(const ImageVector&lt;char&gt;& bytes) noexcept | calls data, size; returns {bytes.data(),bytes.size()} · [reviewed contract](#b0013) |
| [B0014 · 56–58](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L56) | Callable definition: void binding(const Descriptor& descriptor,const Binding& expected) | calls require, bool, sha256; guard require(bool(descriptor) && expected.descriptor_sha256==descriptor.sha256(),ImageFault::binding); · [reviewed contract](#b0014) |
| [B0015 · 59–78](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L59) | Callable definition: std::uint64_t envelope(std::string_view bytes,const Limits& limits,std::string_view magic) | calls require, size, substr, std::uint64_t; guard require(magic.size()==8,ImageFault::binding);; returns frame_header_size+body; 2 loop sites · [reviewed contract](#b0015) |
| [B0016 · 79–94](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L79) | Callable definition: void tail(std::string_view bytes,std::uint64_t ordinal,bool input,bool decision,bool group) | calls require, size, std::uint64_t; guard require(input \|\| decision \|\| group); // No next record is possible at a terminal frontier.; 2 loop sites; source comment (unverified): // No next record is possible at a terminal frontier. · [reviewed contract](#b0016) |
| [B0017 · 95–99](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L95) | Callable definition: Hash chain(const Hash& previous,const char* checksum) | calls std::copy, begin, end, std::copy_n; returns sha256_fixed({bytes.data(),bytes.size()}) · [reviewed contract](#b0017) |
| [B0018 · 100–100](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L100) | Explanatory comments or spacing. |  |
| [B0019 · 101–104](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L101) | Callable definition: Io::Io(FileLimits value,std::string_view frame_magic) : limits(value) | calls limits, require, size, std::copy; guard require(frame_magic.size()==magic.size(),ImageFault::binding); · [reviewed contract](#b0019) |
| [B0020 · 105–105](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L105) | Callable definition: Io::~Io() | calls raw_close · [reviewed contract](#b0020) |
| [B0021 · 106–106](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L106) | Callable definition: void Io::ready() const | calls fail · [reviewed contract](#b0021) |
| [B0022 · 107–109](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L107) | Callable definition: void Io::consume(std::uint64_t amount) | calls require; guard require(work&lt;=limits.scan.work && amount&lt;=limits.scan.work-work,ImageFault::work);work+=amount; · [reviewed contract](#b0022) |
| [B0023 · 110–113](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L110) | Callable definition: Limits Io::record_limits() const | calls require, std::min; guard require(work&lt;=limits.scan.work,ImageFault::work);; returns result · [reviewed contract](#b0023) |
| [B0024 · 114–114](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L114) | Callable definition: FileStatistics Io::statistics() const noexcept | calls ; returns {operations,work} · [reviewed contract](#b0024) |
| [B0025 · 115–173](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L115) | Callable definition: std::int64_t Io::call(FileStage stage,std::size_t requested,int descriptor,const char* name,int other_fd, const char* other_name,… | calls closing, raw_close, fail, testing::hook; returns result; source comment (unverified): // A hook cannot acquire an FD and hide it from its guard. Inject acquisition · [reviewed contract](#b0025) |
| [B0026 · 174–183](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L174) | Callable definition: std::int64_t Io::checked(FileStage stage,std::size_t count,int descriptor,const char* name,int other_fd, const char* other_name,v… | calls call, closing, fail; returns result; 1 loop sites · [reviewed contract](#b0026) |
| [B0027 · 184–192](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L184) | Callable definition: void Io::transfer(bool write,char* bytes,std::size_t size,std::uint64_t offset) | calls checked, std::min, fail; 1 loop sites · [reviewed contract](#b0027) |
| [B0028 · 193–202](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L193) | Callable definition: bool Io::cleanup(int directory,const char* name) noexcept | calls call; returns true; false; 1 loop sites; source comment (unverified): // Mandatory temporary cleanup has eight attempts outside the normal op cap; · [reviewed contract](#b0028) |
| [B0029 · 203–243](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L203) | Callable definition: void Io::create(const Path& path,std::string_view header) | calls checked, data, size, fail; 5 loop sites; source comment (unverified): // No-replace publication of a fully synced inode. An uncertain link is · [reviewed contract](#b0029) |
| [B0030 · 244–254](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L244) | Callable definition: Directory Io::open(const Path& path) | calls checked, data, refresh, S_ISREG; returns directory · [reviewed contract](#b0030) |
| [B0031 · 255–263](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L255) | Callable definition: void Io::finish_open(Directory& directory) | calls checked, fail, unchanged, release · [reviewed contract](#b0031) |
| [B0032 · 264–287](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L264) | Callable definition: bool Io::read_frame(std::uint64_t offset,ImageVector&lt;char&gt;& scratch) | calls size, read, data, consume; guard require(total&lt;=limits.scan.bytes-offset,ImageFault::limit);; returns false; false; growth resize; source comment (unverified): // An incomplete body's typed payload cannot be authenticated. Retain only · [reviewed contract](#b0032) |
| [B0033 · 288–292](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L288) | Callable definition: void Io::unchanged() | calls checked, same, fail · [reviewed contract](#b0033) |
| [B0034 · 293–293](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L293) | Callable definition: void Io::refresh() | calls checked · [reviewed contract](#b0034) |
| [B0035 · 294–301](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L294) | Callable definition: void Io::validate() | calls ready, unchanged, checked, fail; source comment (unverified): // A receiving session rechecks both locked files after semantic replay and · [reviewed contract](#b0035) |
| [B0036 · 302–302](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L302) | Callable definition: void Io::read(char* bytes,std::size_t size,std::uint64_t offset) | calls transfer · [reviewed contract](#b0036) |
| [B0037 · 303–312](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L303) | Callable definition: void Io::append(std::string_view bytes,std::uint64_t offset) | calls ready, require, unchanged, transfer; guard ready();require(offset==static_cast&lt;std::uint64_t&gt;(stamp.st_size),ImageFault::binding);; source comment (unverified): // Caller has completed validation, hashing and all growth. The latch precedes · [reviewed contract](#b0037) |
| [B0038 · 313–321](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L313) | Callable definition: void Io::repair(std::uint64_t bytes) | calls ready, unchanged, checked, refresh · [reviewed contract](#b0038) |
| [B0039 · 322–325](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L322) | Callable definition: void Io::close() | calls fail, checked · [reviewed contract](#b0039) |
| [B0040 · 326–327](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L326) | Closes surrounding scope/type. | source comment (unverified): // namespace file_detail · [reviewed contract](#b0040) |

## B0001

[Lines 1–18](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L18:sha256:bb60427392918698056a71af5756df4a235d44dc9771449c6839e00bd9d43303
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports descriptor file helpers and Linux syscall headers. CROWN_SQL_AGGREGATE_FILE_TESTING conditionally adds a thread-local syscall hook; the enclosing production file namespace remains available in both variants. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The syscall hook and its setter exist only when CROWN_SQL_AGGREGATE_FILE_TESTING is defined; production builds compile the same file-I/O implementation without that seam. |
| ownership | The testing hook and context are thread_local raw pointers, zero-initialized and set only by the testing setter; production does not retain these hook values. |
| failure | This block adds no runtime error conversion. Linux syscall/helper failures are handled by the later explicit FileFailure paths. |
| cost | Headers and the testing conditional affect compile-time closure; the test hook is absent from production code, so this boundary adds no production operation overhead. |
| Design | [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_file_detail.cpp.md](sql_aggregate_file_detail.cpp.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0002

[Lines 19–19](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L19:sha256:ece045b7e72163487160c4283bb81fd5dbdd4f030999f570e9d05682e197e707
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the optional thread-local file fault seam in a build compiled with CROWN_SQL_AGGREGATE_FILE_TESTING. |
| inputs / outputs | A FileHook function pointer and opaque context enter; later Io::call invocations in the same thread consult them before/after the actual operation. |
| invariants | The hook exists only under the test compile definition and replacement resets both pointer/context; production builds omit this storage and function. |
| ownership | The seam borrows the context; it retains neither account storage, frames nor descriptors and the test must keep context alive while armed. |
| failure | The setter is noexcept; injected acquisition/close/transfer behavior is implemented by Io::call rather than here. |
| cost | Two thread-local scalar stores, with no allocation or syscall. |
| Design | [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [tests/support/sql_aggregate_file_probe.hpp](../../../../../tests/support/sql_aggregate_file_probe.hpp), [tests/unit/sql_aggregate_files_fault_test.cpp](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp) |

## B0003

[Lines 20–24](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L20); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L24:sha256:5ef28181c5d9a0c459fea804bb522f92aa9a39037343dbbaeae33305ebd577ad
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the optional testing namespace/guard, opens file_detail, aliases binary require, and opens the private namespace for stat/path/syscall helpers. |
| inputs / outputs | No external runtime input/output is performed by the declaration itself; callable signatures in the block describe future use. |
| invariants | The declaration fixes the source-local names and member/type shape; runtime validation and authority remain with the actual implementations. |
| ownership | No owner is added merely by a declaration. Typed fields keep the ownership behavior of their C++ types and any explicit account allocator. |
| failure | No runtime catch or translation is added here; constructor/member failures remain in their implementation. |
| cost | Declaration-only compile/link work, except that constructing a declared type later may initialize or allocate its members. |
| Design | [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_file_detail.cpp.md](sql_aggregate_file_detail.cpp.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0004

[Lines 25–25](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L25:sha256:e401f7974a09ce160cd697150fee260fd066437f4c0542664bb2002973a27b71
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify the two FD-consuming stages that must not be retried after Linux close. |
| inputs / outputs | A FileStage enters; true is returned for close_file or close_directory only. |
| invariants | No other stage receives close-specific quota fallback, injection or EINTR treatment through this predicate. |
| ownership | The function reads a scalar and owns no FD or stage history. |
| failure | The noexcept predicate cannot fail; checked/call apply its result when handling their own errors. |
| cost | Two enum comparisons and one Boolean result, O(1). |
| Design | [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [src/recovery/sql_aggregate_file_detail.hpp](../../../../../src/recovery/sql_aggregate_file_detail.hpp), [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp) |

## B0005

[Lines 26–30](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L30:sha256:283cd5e71f6d08b4bb64d992ff2e68da5897bac8c218f02c07d48d8e445f3564
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the local file-identity and modification evidence used around scans, comparisons and writes. |
| inputs / outputs | Two borrowed stat snapshots enter; true means device, inode, size, mtime and ctime seconds/nanoseconds all match. |
| invariants | The comparison deliberately checks fixed identity/size/time fields rather than raw struct bytes or unrelated permission metadata. |
| ownership | Both snapshots remain caller-owned and unchanged; no path or FD is followed. |
| failure | False is only comparison evidence; Io::unchanged converts it to FileFailure(changed). This cannot defeat a hostile writer that ignores the cooperation boundary. |
| cost | Seven fixed field comparisons and no syscall or allocation. |
| Design | [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0006

[Lines 31–31](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L31); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L31:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_file_detail.cpp.md](sql_aggregate_file_detail.cpp.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0007

[Lines 32–34](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L32-L34:sha256:7a3c58496ff13399800b409d854b14de36d3ac538efcfde1a000aabce92e270c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Throw one fixed FileFailure with the supplied primary file diagnosis. |
| inputs / outputs | Fault, stage, outcome and optional errno enter; control leaves by throwing a FileFailure with cleanup initially false. |
| invariants | The helper preserves all supplied metadata and adds no dynamic diagnostic text or translation to a semantic Reject. |
| ownership | The exception owns only fixed scalar metadata; borrowed path/FD/buffer values are not captured. |
| failure | This is an unconditional throw, with no catch, cleanup, retry or outcome inference at the helper boundary. |
| cost | Constant-sized exception construction; no application-level heap buffer, formatting pass or syscall. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [src/recovery/sql_aggregate_file_detail.hpp](../../../../../src/recovery/sql_aggregate_file_detail.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0008

[Lines 35–37](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L37:sha256:4b471be31eb85a7c741fbab0e09c5f35d7959913b14dda18b945d6dde6649a6f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release a live descriptor best effort while preserving the caller errno during destruction or quota safety fallback. |
| inputs / outputs | A nonnegative FD causes one ::close; negative FD is ignored; the saved errno is restored before return. |
| invariants | Close is never retried, including EINTR, so a consumed numeric FD cannot be closed again after reuse. |
| ownership | The caller gives up the descriptor lifetime; raw_close owns no guard and records no success metadata. |
| failure | All close results are ignored by this noexcept function. These best-effort calls bypass Io::call and its operations counter. |
| cost | At most one raw Linux close and two errno accesses; no allocation or logical-work charge. |
| Design | [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [src/recovery/sql_aggregate_file_detail.hpp](../../../../../src/recovery/sql_aggregate_file_detail.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0009

[Lines 38–38](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L38:sha256:bb6dd70f853fefdd4575c5f209129404236eb5b1c169c2ef563427a0cdeefe4c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer the directory guard descriptor without duplicating ownership. |
| inputs / outputs | A source Directory enters by rvalue; this.fd receives its old FD and source.fd becomes -1. |
| invariants | Exactly one guard retains responsibility for any nonnegative descriptor after the move. |
| ownership | The destination assumes the same directory FD; no dup, account or pathname copy is made. |
| failure | The move is noexcept and cannot report OS errors because no syscall occurs. |
| cost | O(1) two integer stores through release(). |
| Design | [src/recovery/sql_aggregate_file_detail.hpp](../../../../../src/recovery/sql_aggregate_file_detail.hpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp) |

## B0010

[Lines 39–39](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L39-L39:sha256:2a3b6ce81aa3f33c6467d89a974e441397c9ef9247fe511cdeefba0839779874
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close an unreleased directory handle when a factory or open-confirmation guard leaves scope. |
| inputs / outputs | The stored fd enters raw_close; no value or error escapes destruction. |
| invariants | Released and moved-from guards have fd=-1 and therefore make no close attempt. |
| ownership | Destruction ends this guard ownership but does not close the separate Io file FD. |
| failure | Best-effort close failures are ignored and errno is preserved; use release plus checked close when a report is required. |
| cost | O(1), at most one unmetered close attempt, without allocation. |
| Design | [src/recovery/sql_aggregate_file_detail.hpp](../../../../../src/recovery/sql_aggregate_file_detail.hpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0011

[Lines 40–40](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L40-L40:sha256:58c0669587a3bd3487636d0d2e14896bc4286167aee7ed9cd114e3422a1cd6d1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove directory FD ownership before transferring it to another guard or a checked close. |
| inputs / outputs | The old fd is returned and the member becomes -1, including if it was already -1. |
| invariants | Clearing happens before any subsequent close operation can fail, preventing guard-destructor retry. |
| ownership | The caller takes responsibility for the returned nonnegative descriptor; the method itself releases no OS resource. |
| failure | Noexcept scalar transfer; a caller using an invalid returned FD will fail at its own syscall boundary. |
| cost | Constant integer copy/store with no metered operation. |
| Design | [src/recovery/sql_aggregate_file_detail.hpp](../../../../../src/recovery/sql_aggregate_file_detail.hpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp) |

## B0012

[Lines 41–54](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L54:sha256:f59eb32749c8a3256ec967cf5b7e3cf0400b983ff40d2a097d26eafae210f4ec
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit finite Linux transfer/path policy and split a usable pathname before any acquisition. |
| inputs / outputs | A borrowed byte path and FileLimits enter; zero-filled parent/name arrays receive directory and basename, using dot for a bare filename and slash for a root child. |
| invariants | Limits enforce 157-byte minimum possible record grant, representable offsets/chunks and nonzero operation/chunk counts. The path rejects NUL, empty input, oversized input and empty/dot/dotdot basename. |
| ownership | Only inline arrays retain copied bytes; the caller path may die after construction and no unaccounted owning string is allocated. |
| failure | Invalid policy is FileFailure(limit,path,unchanged), invalid path is FileFailure(path,path,unchanged); parent symlink/trusted-namespace semantics are not resolved by string splitting. |
| cost | O(path bytes) scan/copy bounded below 4096 bytes per split array, plus fixed 8192-byte zero initialization. |
| Design | [src/recovery/sql_aggregate_file_detail.hpp](../../../../../src/recovery/sql_aggregate_file_detail.hpp), [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0013

[Lines 55–55](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L55-L55:sha256:fedb4e1675a7a6f9ffcfaa0e0c95e3d2cd99dc7e964986106779fa9c4f985bf2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Present owner-funded scratch to nonowning record validators without another byte copy. |
| inputs / outputs | A live ImageVector&lt;char&gt; reference enters; the returned string_view spans its data()/size(). |
| invariants | The helper does not parse bytes or extend storage lifetime; any vector resize/swap/destruction can invalidate the view. |
| ownership | All byte ownership remains with the vector and its receiving-account allocator. |
| failure | The conversion is noexcept; using the view after owner mutation is outside the borrowing precondition. |
| cost | O(1) pointer/size construction, with zero allocation and zero byte visits. |
| Design | [src/recovery/sql_aggregate_file_detail.hpp](../../../../../src/recovery/sql_aggregate_file_detail.hpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_wal_file.cpp](../../../../../src/recovery/sql_aggregate_wal_file.cpp), [src/recovery/sql_aggregate_sink_file.cpp](../../../../../src/recovery/sql_aggregate_sink_file.cpp) |

## B0014

[Lines 56–58](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L56-L58:sha256:ad2835ae414c75e3a4fb8794170e58112cf53c21a7324aea18f26af6e540a643
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a missing or differently identified genuine descriptor before the file factory owns an inode. |
| inputs / outputs | The admitted Descriptor and expected header Binding enter; success means descriptor is nonempty and descriptor_sha256 exactly matches its whole-descriptor hash. |
| invariants | The check is only the identity half of the file boundary; Data construction must also freeze the actual descriptor.program() for schema validation. |
| ownership | Both objects are borrowed, with no DTO-to-program construction, metadata copy or native runtime retention in this helper. |
| failure | Failure uses ImageFailure(binding); this hash comparison alone neither checks every expected header field nor grants native replay/file durability. |
| cost | O(64) fixed hash comparison and no allocation/syscall; the cold receiving freeze is charged outside this helper. |
| Design | [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [src/recovery/sql_aggregate_wal_file.cpp](../../../../../src/recovery/sql_aggregate_wal_file.cpp), [src/recovery/sql_aggregate_sink_file.cpp](../../../../../src/recovery/sql_aggregate_sink_file.cpp), [docs/sql_aggregate_descriptor.md](../../../../sql_aggregate_descriptor.md) |

## B0015

[Lines 59–78](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L59-L78:sha256:9a57dd6ede3cd5fbcbc63050d99977466805ca39ee81784b2dc1be749c3a29ea
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate every available envelope byte before using its protected body length to size scratch. |
| inputs / outputs | Up to 148 borrowed bytes and an already admitted record-byte limit enter; the returned uint64_t is 148 plus decoded body length when its eight length bytes are available. Envelope/read_frame uses this Io owner's fixed eight-byte family; constructor copies that value. Aggregate callers keep the CROWNAG2 default, rows callers use CROWNRW2. |
| invariants | Magic/version/reserved bytes and lowercase-hex checksum text must match their available prefixes; body length is at least nine and fits limits/size_t. Any available protected-prefix checksum bytes match SHA256(bytes0..83). Protected length, version/reserved, prefix hash, bounded extents and torn-prefix rules are unchanged; framing bytes confer no SQL/native authority. |
| ownership | The helper owns only a fixed digest and scalars; it never retains bytes or resizes body storage. The family is retained inline in the same file owner and all scratch remains under its existing account/finite grants. |
| failure | Corrupt/version/limit ImageFailure propagates. Partial checksum agreement is only possible-envelope evidence, and a complete body still needs inspect/feed authentication. A wrong-width family is rejected explicitly; other error, poison, lock and cleanup ownership is unchanged. No extra catch/retry is added. |
| cost | At most 148 bytes of validation and one 84-byte fixed-prefix hash, with prefix work charged by the caller read_frame rather than by this helper. Fixed-width copy/check; existing actual byte visits, reads and scratch requests remain charged without a refill. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0016

[Lines 79–94](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L79-L94:sha256:4458e38938cc6e9f7714c3eef0795d694e0ce76a3d6a3c38e41c3467173b0707
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject an incomplete suffix whose visible kind, ordinal or body length contradicts a possible next record. |
| inputs / outputs | An envelope-validated partial frame, expected transport/absolute-C ordinal and allowed-next-kind Booleans enter; success returns no new record. |
| invariants | A terminal frontier admits no tail. Available ordinal bytes must equal the expected little-endian value; Commit body is exactly169, Reject98, Input at least27 and GroupEpoch at least107. |
| ownership | Bytes are borrowed from bounded scan scratch; no partial native payload, pending command copy or output epoch is materialized. |
| failure | Inconsistent visible evidence throws ImageFailure(corrupt). Missing unauthenticated typed content is neither accepted as complete nor semantically proven by tail(). |
| cost | O(1) bounded checks over at most kind+8 ordinal bytes and eight already present length bytes; no body scan or allocation. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_wal_file.cpp](../../../../../src/recovery/sql_aggregate_wal_file.cpp), [src/recovery/sql_aggregate_sink_file.cpp](../../../../../src/recovery/sql_aggregate_sink_file.cpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0017

[Lines 95–99](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L95); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L95-L99:sha256:d1019c4700e61f781392d6a1ee3a8de2a3dfa0236551bfd3a264e7012a7e4c9e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute the next sink-prefix fingerprint from the prior chain and an epoch protected-prefix checksum. |
| inputs / outputs | A 64-byte prior ASCII hash and pointer to 64 readable checksum bytes enter; a new fixed SHA256 Hash is returned. |
| invariants | Exactly previous\|\|checksum, 128 bytes, is hashed in that order. The result is a prefix chain, not SHA256 of raw concatenated file frames. |
| ownership | Inputs are borrowed only during the call and a fixed stack array owns the intermediate bytes. |
| failure | The internal caller supplies authenticated checksum bytes; this helper does not validate hex or authenticate a record on its own. |
| cost | Copies128 bytes and hashes128 bytes; SinkFile::Data::next explicitly charges256 logical work before calling it. |
| Design | [src/recovery/sql_aggregate_sink_file.cpp](../../../../../src/recovery/sql_aggregate_sink_file.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/ir/digest.cpp](../../../../../src/ir/digest.cpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0019

[Lines 101–104](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L101-L104:sha256:cbc1d11f037e5f7db7abfb70d621cd07d1696d8dedc7823393175f424c589e0d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize a fresh bounded transport engine with one copied receiving file policy. |
| inputs / outputs | FileLimits enters by value; fd/counters/outcome/poison/torn/stamp retain their in-class fresh defaults. Envelope/read_frame uses this Io owner's fixed eight-byte family; constructor copies that value. Aggregate callers keep the CROWNAG2 default, rows callers use CROWNRW2. |
| invariants | Construction does not open a file, pre-admit a path, or replenish another owner existing counter. Protected length, version/reserved, prefix hash, bounded extents and torn-prefix rules are unchanged; framing bytes confer no SQL/native authority. |
| ownership | The Io object owns only inline metadata at this point; Path and enclosing Data handle subsequent validation/account storage. The family is retained inline in the same file owner and all scratch remains under its existing account/finite grants. |
| failure | There is no constructor I/O failure; invalid limits are rejected by the required factory Path construction before use. A wrong-width family is rejected explicitly; other error, poison, lock and cleanup ownership is unchanged. No extra catch/retry is added. |
| cost | Constant-size policy/default-state initialization without heap or syscall work. Fixed-width copy/check; existing actual byte visits, reads and scratch requests remain charged without a refill. |
| Design | [src/recovery/sql_aggregate_file_detail.hpp](../../../../../src/recovery/sql_aggregate_file_detail.hpp), [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [src/recovery/sql_aggregate_wal_file.cpp](../../../../../src/recovery/sql_aggregate_wal_file.cpp), [src/recovery/sql_aggregate_sink_file.cpp](../../../../../src/recovery/sql_aggregate_sink_file.cpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0020

[Lines 105–105](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L105-L105:sha256:51e070c5c42ef14c135df22bc6f4a79565b8896494a96972fd69a7e4ebbf6a1b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | End the actual file FD lifetime on successful-owner destruction or abandoned factory construction. |
| inputs / outputs | The current fd is passed once to raw_close; negative fd from explicit close is ignored. |
| invariants | No checked close retry occurs and destruction never marks file contents as confirmed or publishes native state. |
| ownership | The Io destructor releases the one file descriptor; enclosing Data separately releases schema/index/scratch ownership. |
| failure | Best-effort close cannot throw and is outside the operation counter; callers needing diagnostics must use close(). |
| cost | At most one unmetered raw close, with constant state and no allocation. |
| Design | [src/recovery/sql_aggregate_file_detail.hpp](../../../../../src/recovery/sql_aggregate_file_detail.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0021

[Lines 106–106](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L106-L106:sha256:60bf7fe1cedf2e6e65e32eb5e399d8ac38d9d5dea8403216461426a2207cc424
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Gate ordinary owner operations on a live descriptor with no unresolved I/O uncertainty. |
| inputs / outputs | The const Io state enters implicitly; success returns void only when fd&gt;=0 and poisoned is false. |
| invariants | The test does not clear poison, inspect torn or touch a file, so it cannot make failed owners reusable. |
| ownership | Only fixed Io flags are borrowed; no ownership or lock changes. |
| failure | Closed/poisoned state throws FileFailure(state,state,unchanged), describing invalid use rather than the earlier mutation outcome. |
| cost | Two scalar checks, O(1), without counter expenditure. |
| Design | [src/recovery/sql_aggregate_wal_file.cpp](../../../../../src/recovery/sql_aggregate_wal_file.cpp), [src/recovery/sql_aggregate_sink_file.cpp](../../../../../src/recovery/sql_aggregate_sink_file.cpp), [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp) |

## B0022

[Lines 107–109](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L107-L109:sha256:5a2d4df33aa05bca5cfdc5941da530293a41e45458d26d465526bf3e548afb70
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spend the cumulative charged-file-work grant without overflow or implicit per-operation refill. |
| inputs / outputs | An explicit logical amount enters; on success work increases by that amount. |
| invariants | Both existing work&lt;=scan.work and amount&lt;=scan.work-work are checked before addition. This counter is distinct from WalCursor accepted codec-only work. |
| ownership | The scalar grant belongs to this Io owner and creates no MemoryAccount allocation or native runtime budget. |
| failure | Insufficient grant throws ImageFailure(work) before incrementing. Earlier successfully charged work remains spent even if later I/O/admission fails. |
| cost | Constant checked subtraction/addition; amount denotes caller-defined codec/prefix/hash/comparison visits, not CPU duration. |
| Design | [src/recovery/sql_aggregate_file_detail.hpp](../../../../../src/recovery/sql_aggregate_file_detail.hpp), [src/recovery/sql_aggregate_wal_file.cpp](../../../../../src/recovery/sql_aggregate_wal_file.cpp), [src/recovery/sql_aggregate_sink_file.cpp](../../../../../src/recovery/sql_aggregate_sink_file.cpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0023

[Lines 110–113](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L110-L113:sha256:86e9e376ca890cc9cc9bde217918178ca08d08cfbbbb52766763694274566a37
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Derive a single codec-call grant from the remaining cumulative file work. |
| inputs / outputs | Io limits/work enter implicitly; a copy of scan.frame returns with record.work=min(original per-frame work,scan.work-work). |
| invariants | Original frame/scalar/schema bounds are preserved and no codec call can receive more remaining file work than is currently available. |
| ownership | The returned value owns policy scalars only; it neither mutates a genuine program nor transfers a memory grant. |
| failure | An already inconsistent spent counter throws ImageFailure(work); failed codec validation has no returned statistics to consume. |
| cost | O(1) fixed Limits copy and minimum calculation, without parsing/allocation/syscalls. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [src/recovery/sql_aggregate_wal_file.cpp](../../../../../src/recovery/sql_aggregate_wal_file.cpp), [src/recovery/sql_aggregate_sink_file.cpp](../../../../../src/recovery/sql_aggregate_sink_file.cpp) |

## B0024

[Lines 114–114](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L114-L114:sha256:5def81d972c5d07514bef18a3d1d784b0a7fa5041a6b7fcd5fad83d84f9e7b21
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Snapshot the two file-specific charged counters without changing the owner. |
| inputs / outputs | The implicit Io operations/work members are returned as a FileStatistics value. |
| invariants | This method does not substitute WalState.work: that cursor number tracks accepted codec feeds, while Io work includes explicit file-side charges. |
| ownership | The caller receives an independent two-scalar copy with no right to the underlying FD or grant. |
| failure | The accessor is noexcept and does not call ready(); public owner getters perform health gating before invoking it. |
| cost | Constant two-scalar copy, with no I/O or logical-work charge. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [src/recovery/sql_aggregate_wal_file.cpp](../../../../../src/recovery/sql_aggregate_wal_file.cpp), [src/recovery/sql_aggregate_sink_file.cpp](../../../../../src/recovery/sql_aggregate_sink_file.cpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0025

[Lines 115–173](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L115-L173:sha256:6e0b869b2f215d75c93349f1dabafb56c2a180695b61dde48b6a9d39cee2e597
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch one typed private POSIX operation while spending the owner syscall-attempt counter and preserving uncertainty semantics. |
| inputs / outputs | Stage, count, FD/name pairs, buffer, offset, stat output and emergency_cleanup enter; int64_t result and errno leave. Optional test hooks can cap transfer or inject before/after errors. |
| invariants | Overflow always fails; the ordinary operation cap applies unless emergency_cleanup is true, which only cleanup passes. Each admitted attempt increments operations. Nine affected cases guard their required path(s), buffer or stat pointer before libc, allowing irrelevant-stage arguments to stay null. Write/truncate/link set unknown before mutation; close always consumes the actual FD even for injected EINTR. |
| ownership | Arguments are synchronous borrowed storage/FDs owned by guards or Io. Successful acquisitions cannot be hidden by after-error injection; dispatcher retains no extra request, command or output object. |
| failure | A cap failure throws FileFailure and raw-closes a close-stage FD as a safety fallback. Missing case-required pointers throw FileFailure(state,stage,current outcome) after the attempt charge but before libc. Actual syscall errors return -1/errno for checked/create/cleanup to interpret; path/state dispatch throws state. |
| cost | O(1) switch, case-specific pointer guard and hook/counter bookkeeping per syscall attempt; data work is bounded by requested chunk and offsets already admitted by callers. |
| Design | [src/recovery/sql_aggregate_file_detail.hpp](../../../../../src/recovery/sql_aggregate_file_detail.hpp), [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [tests/support/sql_aggregate_file_probe.hpp](../../../../../tests/support/sql_aggregate_file_probe.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0026

[Lines 174–183](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L174); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L174-L183:sha256:dec5d10d57d94c64a530ec622c510f243f6105cc8a9f4453561cade6aa47fc66
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert syscall results to fixed file failures while retrying only safe EINTR operations within the same finite attempt grant. |
| inputs / outputs | The same typed stage/arguments as call enter without an emergency flag; success returns a nonnegative result. |
| invariants | Every loop iteration calls the metered dispatcher. EINTR retries exclude descriptor-consuming close and uncertain no-replace link publication. |
| ownership | Pointers and descriptors stay caller-owned across synchronous retries; no buffer or exception queue is retained. |
| failure | Lock EWOULDBLOCK/EAGAIN maps to busy; other nonretry errors map to io with original stage/outcome/errno. Limit failures from call propagate directly. |
| cost | One dispatch per actual attempt, bounded by limits.operations; no unbounded normal retry allowance is introduced. |
| Design | [src/recovery/sql_aggregate_file_detail.hpp](../../../../../src/recovery/sql_aggregate_file_detail.hpp), [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0027

[Lines 184–192](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L184); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L184-L192:sha256:4d2dd65473a04d642f48440c4d6d5135282910fc0e85c0797523d7c989f662a2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Perform an exact positional transfer with bounded chunks and mandatory forward progress. |
| inputs / outputs | A read/write selector, borrowed writable or const-cast read-only source buffer, size and admitted offset enter; success transfers all requested bytes. |
| invariants | Each pread/pwrite request is at most chunk_bytes, and done advances only by the positive actual result; zero progress cannot spin. |
| ownership | The caller owns the buffer throughout synchronous transfer; no second buffer or seek-position state is retained. |
| failure | A zero write becomes FileFailure(io,write_data,EIO); zero read becomes truncated. EINTR and other errors follow checked semantics and mutation outcome stays conservative. |
| cost | O(size) byte I/O; at least ceil(size/chunk_bytes) successful attempts and potentially more short/interrupted attempts, all under the operation cap. |
| Design | [src/recovery/sql_aggregate_file_detail.hpp](../../../../../src/recovery/sql_aggregate_file_detail.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0028

[Lines 193–202](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L193); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L193-L202:sha256:03df6b96fc0df203e249326c78b4cee9ff1ba7335f4d50241bca5333e8da1fe2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attempt mandatory removal of the one temporary name without hiding primary creation failure. |
| inputs / outputs | Borrowed directory FD/name enter; true means unlink succeeded or the name was already absent, false means cleanup could not be confirmed. |
| invariants | Only this eight-iteration helper passes emergency_cleanup=true to call. It retries EINTR only, still increments operations, and never bypasses uint64_t overflow; ordinary unlink remains quota-limited. |
| ownership | The helper owns no FD/path storage and relies on create keeping Directory and temporary array alive. |
| failure | Non-EINTR errors and caught dispatcher exceptions return false. The noexcept catch is bounded cleanup containment, not a main-path retry/undo system. |
| cost | At most eight unlink attempts outside the ordinary cap, constant stack/counter cost and no allocation. |
| Design | [src/recovery/sql_aggregate_file_detail.hpp](../../../../../src/recovery/sql_aggregate_file_detail.hpp), [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0029

[Lines 203–243](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L203); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L203-L243:sha256:f4c021e28e7197981dafb1ad3f7a8c1de9b32c6912654f88a36943f3febd5822
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install one synced header inode at a previously absent destination using a same-directory no-replace link. |
| inputs / outputs | A prevalidated fixed Path and caller-owned encoded header enter; success retains the locked file FD, a final stat stamp and durable outcome after directory confirmation. |
| invariants | At most16 random-name candidates use16 entropy bytes each; O_EXCL/O_NOFOLLOW create0600, lock, complete write and fsync precede linkat. Uncertain link is not retried or rolled back; normal temporary unlink obeys operation quota. |
| ownership | Directory is stack-guarded, temporary/random/name storage is fixed, header is borrowed, and Io owns the new FD. No preexisting destination entry is replaced. |
| failure | The sole create catch rethrows FileFailure with corrected unpublished outcome and bounded-cleanup status. Temporary cleanup has at most8 emergency attempts; a process crash can still leave a temporary name. |
| cost | O(header bytes) chunked I/O plus finite entropy/collision attempts, file/directory fsyncs and final stat; all ordinary attempts are capped, with the explicit eight-unlink cleanup exception. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [src/recovery/sql_aggregate_file_detail.hpp](../../../../../src/recovery/sql_aggregate_file_detail.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0030

[Lines 244–254](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L244); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L244-L254:sha256:0fff68b73836da0fbf35f3f84b278eb728acd00eab5e7159cf4fdec656d0e0d6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Acquire and admit an existing regular file before owner-specific sequential validation. |
| inputs / outputs | A validated Path enters; a Directory guard returns while Io retains the O_RDWR/O_NOFOLLOW/O_NONBLOCK file FD and locked stat stamp. |
| invariants | The file is statted before and after nonblocking exclusive flock; size must contain at least148 bytes, fit size_t and stay within scan.bytes. |
| ownership | The returned guard owns the directory FD until finish_open; provisional Io owns the file FD, so a later scan failure closes both through RAII. |
| failure | Open/symlink/type/lock/size errors throw fixed FileFailure. This step does not validate header/body identity, sync accepted bytes or truncate anything. |
| cost | A fixed number of acquisition/stat/lock calls under the operations cap; scanning and scratch growth occur in WalFile/SinkFile. |
| Design | [src/recovery/sql_aggregate_wal_file.cpp](../../../../../src/recovery/sql_aggregate_wal_file.cpp), [src/recovery/sql_aggregate_sink_file.cpp](../../../../../src/recovery/sql_aggregate_sink_file.cpp), [src/recovery/sql_aggregate_file_detail.hpp](../../../../../src/recovery/sql_aggregate_file_detail.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0031

[Lines 255–263](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L255); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L255-L263:sha256:c574ff946b5284b4c49b46be175b31a2046c09789a3ef2e9d05e7022bbf0d4eb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Confirm the scanned file whole-size observation and durability before a factory publishes its owner. |
| inputs / outputs | A live directory guard and existing file stamp enter; success consumes the directory FD and sets durable after file and directory fsync. |
| invariants | A one-byte read at stamped EOF must return0; stamps must match both before syncs and after syncs. No root/native/sink semantic authority is inferred. |
| ownership | The guard retains its FD until release immediately before checked close; the file FD stays owned by Io and scan scratch is caller-managed. |
| failure | Extra bytes, changed stamps, sync/read/close/cap errors abandon the provisional owner. The function neither catches nor truncates an admitted torn suffix. |
| cost | One EOF read, two fstats, two fsyncs and one directory close, each metered; no per-record traversal or allocation. |
| Design | [src/recovery/sql_aggregate_wal_file.cpp](../../../../../src/recovery/sql_aggregate_wal_file.cpp), [src/recovery/sql_aggregate_sink_file.cpp](../../../../../src/recovery/sql_aggregate_sink_file.cpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0032

[Lines 264–287](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L264); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L264-L287:sha256:1631badceca90ab76d2e13cd6552018c40f3ceff936a1913e88754d45dfbebdd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one complete admitted frame or retain only enough authenticated-envelope and visible-body evidence to classify a torn suffix. |
| inputs / outputs | An offset within the stamped bounded file and receiving-account scratch enter; true returns whole-frame bytes, false marks torn and returns available envelope plus at most nine kind/ordinal bytes. Envelope/read_frame uses this Io owner's fixed eight-byte family; constructor copies that value. Aggregate callers keep the CROWNAG2 default, rows callers use CROWNRW2. |
| invariants | Read/validate the148-byte length-protecting envelope before resize; declared frame must fit remaining scan.bytes. Incomplete body scratch/read is capped at157 even if the actual suffix is larger; EOF/stat still cover that actual full size. Protected length, version/reserved, prefix hash, bounded extents and torn-prefix rules are unchanged; framing bytes confer no SQL/native authority. |
| ownership | The fixed envelope array is stack storage; body scratch is supplied by the owner account. No partial typed payload or second command/output owner is created. The family is retained inline in the same file owner and all scratch remains under its existing account/finite grants. |
| failure | A partial first frame throws truncated; malformed available envelope or excess grant throws ImageFailure; read errors propagate. Caller must reject impossible next kind/ordinal/terminal frontiers using tail(). A wrong-width family is rejected explicitly; other error, poison, lock and cleanup ownership is unchanged. No extra catch/retry is added. |
| cost | Prefix work charges have+(have&gt;84?84:0); incomplete body charges retained-148. Prefix checks are prepaid even if envelope validation later rejects; failed codec inspection has no returned work to charge. Complete body codec work is consumed separately after successful inspect/feed; complete-frame scratch size is O(frame bytes), while incomplete-frame size is at most157 (earlier vector capacity can remain until factory release). Fixed-width copy/check; existing actual byte visits, reads and scratch requests remain charged without a refill. |
| Design | [src/recovery/sql_aggregate_file_detail.hpp](../../../../../src/recovery/sql_aggregate_file_detail.hpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_wal_file.cpp](../../../../../src/recovery/sql_aggregate_wal_file.cpp), [src/recovery/sql_aggregate_sink_file.cpp](../../../../../src/recovery/sql_aggregate_sink_file.cpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0033

[Lines 288–292](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L288); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L288-L292:sha256:5647876f430d87d5604c0778e178f4ef133fb737c3669bf30a1f1273c46ca655
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a file whose current identity/size/time evidence differs from the owner last confirmed stamp. |
| inputs / outputs | A fresh local stat is filled from Io.fd, compared with stamp, and discarded on success. |
| invariants | The stored stamp is not refreshed by this method, so an unapproved modification cannot become a new baseline. |
| ownership | Both stat objects are fixed inline/stack metadata and fd remains owned by Io. |
| failure | fstat/cap errors propagate; mismatch throws FileFailure(changed,stat_file,current outcome). A caller that latched before this check stays poisoned. |
| cost | One metered fstat and constant seven-field comparison, with no byte I/O or heap work. |
| Design | [src/recovery/sql_aggregate_file_detail.hpp](../../../../../src/recovery/sql_aggregate_file_detail.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0034

[Lines 293–293](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L293); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L293-L293:sha256:056429be2d6bed5e308ac7e871afd31ebd12ee190b4eb676bd482fe9122c3f6c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace the owner stamp after acquisition or a successfully synced mutation. |
| inputs / outputs | The live fd enters fstat through checked; stamp receives the OS result on success. |
| invariants | Only explicit refresh adopts current metadata; mutation callers still validate the resulting exact expected size before publishing higher state. |
| ownership | The one inline Io stamp is overwritten; no additional owner, path or frame is retained. |
| failure | fstat failure propagates fixed file metadata and may leave a mutation caller poisoned even after fsync reached durable. |
| cost | One metered fstat and fixed stat output, O(1) local work. |
| Design | [src/recovery/sql_aggregate_file_detail.hpp](../../../../../src/recovery/sql_aggregate_file_detail.hpp), [src/recovery/sql_aggregate_wal_file.cpp](../../../../../src/recovery/sql_aggregate_wal_file.cpp), [src/recovery/sql_aggregate_sink_file.cpp](../../../../../src/recovery/sql_aggregate_sink_file.cpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0035

[Lines 294–301](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L294); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L294-L301:sha256:fd50f3fec7adb8cc00f7bf358c7ba22e2f5904e25104d82ce2539d5ce9263899
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recheck a held locked full physical file at the Session semantic barrier without truncating it. |
| inputs / outputs | Healthy Io with its accepted full-file stamp enters; stat, one-byte EOF probe at original size and another stat must agree. |
| invariants | Set poison before the first I/O. This observes the original complete-plus-torn physical extent, not merely the valid record prefix; it does not decode, hash all file contents or confer tail-repair permission. |
| ownership | Borrows the existing FD and one stack byte; retains no new payload or allocation. |
| failure | Any stage/EOF/stamp failure leaves poison set and propagates fixed file metadata. Only all three successful checks clear poison. |
| cost | Three admitted dispatcher calls (stat/read/stat) plus retries under the owner cap, constant storage and no C++ allocation; kernel latency remains unbounded. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp) |

## B0036

[Lines 302–302](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L302); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L302-L302:sha256:42eebd55cf8795b364aa9c31307a0ea06ac758ed026bd0b87cbbc7e0e4830f39
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route positional reads through the common exact, chunked transfer engine. |
| inputs / outputs | Caller-owned output storage, byte count and admitted offset enter; success fills every requested byte. |
| invariants | The wrapper selects transfer(false) and does not advance a shared file seek offset or silently accept EOF. |
| ownership | The destination remains borrowed for the call and all retained allocation responsibility stays with the owner scratch. |
| failure | Zero/short terminal EOF and checked I/O errors propagate from transfer; readiness/stamp/latching policy is established by the outer scan or duplicate verifier. |
| cost | O(size) read work with requests at most chunk_bytes and finite operation attempts; the wrapper itself adds constant dispatch. |
| Design | [src/recovery/sql_aggregate_file_detail.hpp](../../../../../src/recovery/sql_aggregate_file_detail.hpp), [src/recovery/sql_aggregate_sink_file.cpp](../../../../../src/recovery/sql_aggregate_sink_file.cpp), [src/recovery/sql_aggregate_wal_file.cpp](../../../../../src/recovery/sql_aggregate_wal_file.cpp) |

## B0037

[Lines 303–312](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L303); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L303-L312:sha256:b8991128916549b21082bc2a8e24d42d260145eff002150531417da302be07a0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write a prevalidated, fully funded frame at confirmed EOF and leave publication to the enclosing owner. |
| inputs / outputs | Borrowed immutable bytes and expected offset enter; success has synced the frame, refreshed stamp and verified exact offset+size. |
| invariants | ready and old-size binding precede the latch; outcome resets unchanged, poisoned becomes true before the first stamp check, and no success path clears it here. |
| ownership | Io borrows the frame buffer without retaining a copy; callers must finish validation/hashing/index/scratch growth before invoking this mutation boundary. |
| failure | Any subsequent stamp/write/fsync/stat/size failure preserves poison. fsync success sets durable even when final stat fails; outer fixed-state/index publication alone clears poison. |
| cost | O(frame bytes) chunked write plus stamp/fsync/stat, no allocation or codec work within the boundary. |
| Design | [src/recovery/sql_aggregate_wal_file.cpp](../../../../../src/recovery/sql_aggregate_wal_file.cpp), [src/recovery/sql_aggregate_sink_file.cpp](../../../../../src/recovery/sql_aggregate_sink_file.cpp), [src/recovery/sql_aggregate_file_detail.hpp](../../../../../src/recovery/sql_aggregate_file_detail.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0038

[Lines 313–321](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L313); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L313-L321:sha256:b3a7d08a946ff6297948098e37625bb4c0ad9d15342fecd268f14ef89919f64d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove only the owner-known incomplete suffix after the caller-established semantic repair barrier. |
| inputs / outputs | The complete-prefix byte count enters; a healthy untorn owner returns immediately, while a torn owner truncates/syncs/validates that exact size. |
| invariants | The helper does not validate root/native replay/output equality itself. Poison is latched before stamp check and cleared with torn only after successful truncate/fsync/final stat. |
| ownership | The existing file FD is reused and no source/runtime state, output spool or complete frame is copied. |
| failure | Any repair I/O failure requires reopening, including a final stat failure after durable fsync; bad owner state fails before mutation. |
| cost | O(1) metadata and one stamp check, truncate, fsync, refresh/stat-size test, all subject to normal operation quota. |
| Design | [src/recovery/sql_aggregate_wal_file.cpp](../../../../../src/recovery/sql_aggregate_wal_file.cpp), [src/recovery/sql_aggregate_sink_file.cpp](../../../../../src/recovery/sql_aggregate_sink_file.cpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0039

[Lines 322–325](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L322); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L322-L325:sha256:c30b84340ceae734b7e5ea8ceb150fa3cfe9663776525e094cc00c3d06e42cb3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume the file FD exactly once while reporting the explicit close result. |
| inputs / outputs | If fd is live it is copied to old and the member is set -1 before checked(close_file); otherwise state failure is thrown. |
| invariants | Poison does not block close. The old descriptor is never retried after EINTR, and later destruction sees -1. |
| ownership | The method ends Io descriptor ownership before the syscall result, retaining only non-FD metadata afterward. |
| failure | Already closed fails state; close error propagates. If the normal operation cap rejects close, Io::call raw-closes old before raising limit. |
| cost | One metered close when admitted, or one unmetered fallback close on cap rejection; constant storage and no allocation. |
| Design | [src/recovery/sql_aggregate_file_detail.hpp](../../../../../src/recovery/sql_aggregate_file_detail.hpp), [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0040

[Lines 326–327](../../../../../src/recovery/sql_aggregate_file_detail.cpp#L326); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L326-L327:sha256:8c251763eb7dae4f1737ff4dd63a97725579cdeedf6813cddf20a04b5dc083fc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes file_detail and crown::recovery::sql_aggregate after the shared Linux file-I/O implementation. |
| inputs / outputs | No external runtime input/output is performed by the declaration itself; callable signatures in the block describe future use. |
| invariants | The declaration fixes the source-local names and member/type shape; runtime validation and authority remain with the actual implementations. |
| ownership | No owner is added merely by a declaration. Typed fields keep the ownership behavior of their C++ types and any explicit account allocator. |
| failure | No runtime catch or translation is added here; constructor/member failures remain in their implementation. |
| cost | Declaration-only compile/link work, except that constructing a declared type later may initialize or allocate its members. |
| Design | [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_file_detail.cpp.md](sql_aggregate_file_detail.cpp.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |
