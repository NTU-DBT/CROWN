# `src/recovery/local_sink.cpp` — block usage map

[Source](../../../../../src/recovery/local_sink.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Persist canonical complete epoch output and return authority-bearing delivery receipts.

Snapshot SHA-256: `d5a5a49555ae01474c1d57fb23e3cfa82a8084a53cd4b832f4ddfaaa713e1597`. 319 lines partitioned into 39 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../src/recovery/local_sink.cpp#L1) | Imports dependencies; controls preprocessing; declares namespace scope; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 18–18](../../../../../src/recovery/local_sink.cpp#L18) | Callable definition: void set_hook(Hook value,void* data) noexcept | calls  · [reviewed contract](#b0002) |
| [B0003 · 19–21](../../../../../src/recovery/local_sink.cpp#L19) | controls preprocessing; declares namespace scope. |  · [reviewed contract](#b0003) |
| [B0004 · 22–24](../../../../../src/recovery/local_sink.cpp#L22) | Callable definition: \[\[noreturn\]\] void fail(Fault fault,Stage stage,Outcome outcome,int error=0) | calls Failure · [reviewed contract](#b0004) |
| [B0005 · 25–25](../../../../../src/recovery/local_sink.cpp#L25) | Callable definition: bool closing(Stage stage) | calls ; returns stage==Stage::close_file \|\| stage==Stage::close_directory · [reviewed contract](#b0005) |
| [B0006 · 26–26](../../../../../src/recovery/local_sink.cpp#L26) | Callable definition: void raw_close(int fd) noexcept | calls close · [reviewed contract](#b0006) |
| [B0007 · 27–31](../../../../../src/recovery/local_sink.cpp#L27) | Type/record definition: struct Descriptor | returns value · [reviewed contract](#b0007) |
| [B0008 · 32–46](../../../../../src/recovery/local_sink.cpp#L32) | Type/record definition: struct Path |  · [reviewed contract](#b0008) |
| [B0009 · 47–51](../../../../../src/recovery/local_sink.cpp#L47) | Callable definition: bool same(const struct stat& a,const struct stat& b) | calls ; returns a.st_dev==b.st_dev && a.st_ino==b.st_ino && a.st_size==b.st_size && · [reviewed contract](#b0009) |
| [B0010 · 52–52](../../../../../src/recovery/local_sink.cpp#L52) | Callable definition: std::string_view view(const ImageVector&lt;char&gt;& bytes) | calls data, size; returns {bytes.data(),bytes.size()} · [reviewed contract](#b0010) |
| [B0011 · 53–55](../../../../../src/recovery/local_sink.cpp#L53) | Callable definition: std::array&lt;char,64&gt; chain(const std::array&lt;char,64&gt;& previous,const char* checksum) | calls std::copy, begin, end, std::copy_n; returns sha256_fixed({bytes.data(),bytes.size()}) · [reviewed contract](#b0011) |
| [B0012 · 56–56](../../../../../src/recovery/local_sink.cpp#L56) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0012) |
| [B0013 · 57–63](../../../../../src/recovery/local_sink.cpp#L57) | Callable definition: File::File(const resource::MemoryAccount& account,const Header& header,std::span&lt;const ScalarType&gt; schema,Limits limits) :account… | calls account_, header_, limits_, schema_ · [reviewed contract](#b0013) |
| [B0014 · 64–64](../../../../../src/recovery/local_sink.cpp#L64) | Callable definition: File::~File() | calls raw_close · [reviewed contract](#b0014) |
| [B0015 · 65–66](../../../../../src/recovery/local_sink.cpp#L65) | Callable definition: File::File(File&& other) noexcept :account_(other.account_),header_(other.header_),limits_(other.limits_),schema_(std::move(other… | calls account_, header_, limits_, schema_ · [reviewed contract](#b0015) |
| [B0016 · 67–67](../../../../../src/recovery/local_sink.cpp#L67) | Callable definition: void File::consume(std::uint64_t amount) | calls ImageFailure · [reviewed contract](#b0016) |
| [B0017 · 68–68](../../../../../src/recovery/local_sink.cpp#L68) | Callable definition: ImageLimits File::record_limits() const | calls std::min; returns result · [reviewed contract](#b0017) |
| [B0018 · 69–121](../../../../../src/recovery/local_sink.cpp#L69) | Callable definition: std::int64_t File::call(Stage stage,std::size_t requested,int fd,const char* name,int other_fd,const char* other_name, void* buff… | calls closing, raw_close, fail, testing::hook; returns result; source comment (unverified): // Even an interrupted/failed mutation can have a filesystem effect. Admission · [reviewed contract](#b0018) |
| [B0019 · 122–131](../../../../../src/recovery/local_sink.cpp#L122) | Callable definition: std::int64_t File::checked(Stage stage,std::size_t count,int fd,const char* name,int other_fd,const char* other_name, void* buffe… | calls call, closing, fail; returns result; 1 loop sites · [reviewed contract](#b0019) |
| [B0020 · 132–140](../../../../../src/recovery/local_sink.cpp#L132) | Callable definition: void File::transfer(bool write,char* data,std::size_t size,std::uint64_t offset) | calls checked, std::min, fail; 1 loop sites · [reviewed contract](#b0020) |
| [B0021 · 141–147](../../../../../src/recovery/local_sink.cpp#L141) | Callable definition: bool File::cleanup_temporary(int directory,const char* name) noexcept | calls call; returns true; false; 1 loop sites · [reviewed contract](#b0021) |
| [B0022 · 148–189](../../../../../src/recovery/local_sink.cpp#L148) | Callable definition: File File::create(const resource::MemoryAccount& account,std::string_view path,const Header& header,std::span&lt;const ScalarType&gt; s… | calls parsed, result, detail::encode_header, record_limits; returns result; 5 loop sites; source comment (unverified): // linkat installs a complete synced inode without overwriting any existing · [reviewed contract](#b0022) |
| [B0023 · 190–190](../../../../../src/recovery/local_sink.cpp#L190) | Callable definition: void File::ready() const | calls fail · [reviewed contract](#b0023) |
| [B0024 · 191–196](../../../../../src/recovery/local_sink.cpp#L191) | Callable definition: State File::state() const | calls fail, get_allocator, allocation_usage, data; returns values.get_allocator().allocation_usage(values.data(),values.capacity()).requested_bytes; {header_,… · [reviewed contract](#b0024) |
| [B0025 · 197–201](../../../../../src/recovery/local_sink.cpp#L197) | Callable definition: Prefix File::prefix(std::uint64_t sequence) const | calls ready, size, ImageFailure; returns {header_.first_generation,sequence,header_bytes_,header_sha256_}; {entry.generation,sequence,entry.… · [reviewed contract](#b0025) |
| [B0026 · 202–202](../../../../../src/recovery/local_sink.cpp#L202) | Callable definition: Receipt File::receipt() const | calls ready, fail, Receipt, prefix; returns Receipt(header_,prefix(header_.base_sequence+index_.size())) · [reviewed contract](#b0026) |
| [B0027 · 203–203](../../../../../src/recovery/local_sink.cpp#L203) | Callable definition: void File::refresh() | calls checked · [reviewed contract](#b0027) |
| [B0028 · 204–207](../../../../../src/recovery/local_sink.cpp#L204) | Callable definition: void File::unchanged_file() | calls checked, same, fail · [reviewed contract](#b0028) |
| [B0029 · 208–208](../../../../../src/recovery/local_sink.cpp#L208) | declares namespace scope. |  · [reviewed contract](#b0029) |
| [B0030 · 209–219](../../../../../src/recovery/local_sink.cpp#L209) | Callable definition: void incomplete_prefix(std::string_view bytes,ImageLimits limits) | calls substr, size, ImageFailure, std::uint64_t; 3 loop sites · [reviewed contract](#b0030) |
| [B0031 · 220–220](../../../../../src/recovery/local_sink.cpp#L220) | Closes surrounding scope/type. |  · [reviewed contract](#b0031) |
| [B0032 · 221–268](../../../../../src/recovery/local_sink.cpp#L221) | Callable definition: File File::open(const resource::MemoryAccount& account,std::string_view path,const Header& expected,std::span&lt;const ScalarType&gt; s… | calls parsed, result, checked, data; returns result; growth push_back, resize; 1 loop sites; source comment (unverified): // Open scans the whole admitted prefix and syncs its file/name before · [reviewed contract](#b0032) |
| [B0033 · 269–271](../../../../../src/recovery/local_sink.cpp#L269) | Callable definition: bool File::append(std::uint64_t generation,std::uint64_t sequence,std::span&lt;const RowView&gt; rows) | calls accept_epoch; returns accept_epoch(generation,sequence,rows,false) · [reviewed contract](#b0033) |
| [B0034 · 272–274](../../../../../src/recovery/local_sink.cpp#L272) | Callable definition: void File::verify_epoch(std::uint64_t generation,std::uint64_t sequence,std::span&lt;const RowView&gt; rows) | calls accept_epoch · [reviewed contract](#b0034) |
| [B0035 · 275–301](../../../../../src/recovery/local_sink.cpp#L275) | Callable definition: bool File::accept_epoch(std::uint64_t generation,std::uint64_t sequence,std::span&lt;const RowView&gt; rows,bool verify_only) | calls ready, fail, ImageFailure, size; returns false; true; growth push_back, reserve, resize; source comment (unverified): // Freeze canonical bytes and fund new index capacity before append I/O. · [reviewed contract](#b0035) |
| [B0036 · 302–313](../../../../../src/recovery/local_sink.cpp#L302) | Callable definition: Epoch File::read_epoch(std::uint64_t sequence) | calls ready, size, ImageFailure, resize; returns detail::decode(account_,view(scratch_),schema_,limits); growth reserve, resize; source comment (unverified): // The returned decoded rows own this account's payload independently of · [reviewed contract](#b0036) |
| [B0037 · 314–317](../../../../../src/recovery/local_sink.cpp#L314) | Callable definition: void File::repair_tail() | calls ready, unchanged_file, checked, refresh · [reviewed contract](#b0037) |
| [B0038 · 318–318](../../../../../src/recovery/local_sink.cpp#L318) | Callable definition: void File::close() | calls fail, checked · [reviewed contract](#b0038) |
| [B0039 · 319–319](../../../../../src/recovery/local_sink.cpp#L319) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::recovery::sink · [reviewed contract](#b0039) |

## B0001

[Lines 1–17](../../../../../src/recovery/local_sink.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/recovery/local_sink.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble Linux local epoch sink storage and optional syscall fault instrumentation. |
| inputs / outputs | Public recovery types, platform file/entropy/locking calls and, only under CROWN_RUNTIME_TESTING, thread-local hook/context declarations. |
| invariants | Trusted stable containing namespace and cooperating single writer are assumptions. These local durable/ownership protocols are not paper theorems. |
| ownership | Declarations hold no production query allocation. Testing context is a borrowed thread-local pointer, never a production owner. |
| failure | No filesystem effect or recovery handler is introduced by includes/declarations. |
| cost | No dynamic runtime work for declarations; test hook code is compiled out in ordinary production. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 18–18](../../../../../src/recovery/local_sink.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void set_hook(Hook value,void* data) noexcept {hook=value;context=data;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install this thread's local epoch sink syscall fault hook in the testing build. |
| inputs / outputs | Hook function and opaque context replace the current thread-local pair; null disables injection. |
| invariants | Only available under CROWN_RUNTIME_TESTING. Test harness must keep context readable until restoring/unsetting the hook. |
| ownership | Borrows context; retains no account, descriptor or callback owner. |
| failure | noexcept scalar assignments; callbacks can alter later syscall behavior but no call occurs here. |
| cost | Two thread-local writes; absent from normal production API/runtime path. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0003

[Lines 19–21](../../../../../src/recovery/local_sink.cpp#L19); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L21:sha256:2cdf9576c15c73a8f4ece08282d4cdd2a44bb5fb31869defd3a37f40b7b45aed
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the CROWN_LOCAL_SINK_TESTING hook and its conditional compilation region, then opens the anonymous namespace for sink file helpers. |
| inputs / outputs | No external runtime input/output is performed by the declaration itself; callable signatures in the block describe future use. |
| invariants | Only the CROWN_LOCAL_SINK_TESTING-enabled build sees the preceding thread-local test hook; the following anonymous-namespace helpers are compiled for the file implementation. |
| ownership | No owner is added merely by a declaration. Typed fields keep the ownership behavior of their C++ types and any explicit account allocator. |
| failure | The preprocessor guard does not catch filesystem errors. Later checked file operations preserve their declared stage/outcome failure carriers. |
| cost | Preprocessor/scope boundary only; test hook code is not present when its testing macro is absent. |
| Design | [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [docs/code_specs/files/src/recovery/local_sink.cpp.md](local_sink.cpp.md), [docs/local-sink.md](../../../../local-sink.md), [docs/journal-files.md](../../../../journal-files.md) |

## B0004

[Lines 22–24](../../../../../src/recovery/local_sink.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[noreturn]] void fail(Fault fault,Stage stage,Outcome outcome,int error=0) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise a fixed typed local epoch sink file failure. |
| inputs / outputs | Fault, syscall stage, operation outcome and native errno construct the corresponding Failure/FileFailure and never return. |
| invariants | Reports established uncertainty; does not infer rollback, retry, cleanup success or durable acknowledgment from errno alone. |
| ownership | Exception contains fixed enums/errno/flags; no copied diagnostic string or query state. |
| failure | Throws to the caller. Publication catches may enrich cleanup/outcome metadata without erasing the original stage/fault/errno. |
| cost | Fixed failure object; success paths do not call it. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0005

[Lines 25–25](../../../../../src/recovery/local_sink.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool closing(Stage stage) {return stage==Stage::close_file || stage==Stage::close_directory;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify checked close operations that Linux must execute at most once. |
| inputs / outputs | Stage enum returns true for close_file or close_directory. |
| invariants | EINTR close is not retried; closing a reused descriptor after an ambiguous retry could release another resource. |
| ownership | Scalar enum input/result only. |
| failure | No allocation, syscall or exception for the admitted enum domain. |
| cost | Two bounded comparisons. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0006

[Lines 26–26](../../../../../src/recovery/local_sink.cpp#L26); `callable`; `contains_scoped_manual_contract`.

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
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0007

[Lines 27–31](../../../../../src/recovery/local_sink.cpp#L27); `type`; `contains_scoped_manual_contract`.

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
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0008

[Lines 32–46](../../../../../src/recovery/local_sink.cpp#L32); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Path {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate local epoch sink path and Linux transfer/byte limits before opening anything. |
| inputs / outputs | Nonempty non-NUL path and limits populate zero-initialized fixed parent/name arrays, separating last component and parent directory. |
| invariants | Require representable path/chunk/off_t domains, positive operation/chunk limits and minimum frame allowance; basename cannot be empty, dot or dot-dot. Parent path may follow trusted namespace components; no adversarial-directory security claim. |
| ownership | Copies path bytes into stack arrays; no borrowed path survives the call and no query heap account is created. |
| failure | Fixed path/limit failure reports unchanged before any open or mutation. |
| cost | O(path bytes) scans/copies and two 4096-byte stack arrays; no heap allocation. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0009

[Lines 47–51](../../../../../src/recovery/local_sink.cpp#L47); `callable`; `contains_scoped_manual_contract`.

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
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0010

[Lines 52–52](../../../../../src/recovery/local_sink.cpp#L52); `callable`; `contains_scoped_manual_contract`.

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
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0011

[Lines 53–55](../../../../../src/recovery/local_sink.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::array<char,64> chain(const std::array<char,64>& previous,const char* checksum) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extend the sink complete-prefix fingerprint with one canonical frame checksum. |
| inputs / outputs | Previous ASCII64 chain and readable current ASCII64 body checksum form a 128-byte stack buffer, returning fixed SHA256 text. |
| invariants | Digest describes content in a trusted namespace; exact duplicate acceptance still compares the entire canonical frame, never checksum alone. |
| ownership | Fixed arrays own bytes/result; checksum is borrowed for the call. |
| failure | No account allocation or filesystem action; caller admits declared hash/copy work before use. |
| cost | 128 bytes copied/hashed and fixed 64-byte output; no epoch/history scan. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0012

[Lines 56–56](../../../../../src/recovery/local_sink.cpp#L56); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L56-L56:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [docs/code_specs/files/src/recovery/local_sink.cpp.md](local_sink.cpp.md), [docs/local-sink.md](../../../../local-sink.md), [docs/journal-files.md](../../../../journal-files.md) |

## B0013

[Lines 57–63](../../../../../src/recovery/local_sink.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
File::File(const resource::MemoryAccount& account,const Header& header,std::span<const ScalarType> schema,Limits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit and own a sink header/schema on the actual receiving account. |
| inputs / outputs | Account, Header, scalar schema and Limits initialize account-funded schema/index/frame allocators; schema arity/hash must match Header. |
| invariants | Checks field/host arithmetic, charges 1024+4*arity declared work, computes bound schema SHA and copies type tags before filesystem work. Header identity is independent of producer row iteration. |
| ownership | Retains same account and copies schema; no row/runtime pointers are kept. Index/frame buffers initially empty. |
| failure | ImageFailure on binding/limit/work or allocation precedes any file open/publication; scoped vectors unwind. |
| cost | O(schema fields) validation/hash/copy plus fixed holder; query-account allocation for schema and delegated schema-hash workspace. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink_codec.cpp](../../../../../src/recovery/local_sink_codec.cpp) |

## B0014

[Lines 64–64](../../../../../src/recovery/local_sink.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
File::~File(){raw_close(fd_);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | End local epoch sink ownership by releasing its fd/lock best effort. |
| inputs / outputs | Current fd passes to raw_close; member vectors then release their accounted payload. |
| invariants | Destruction is not a checked sync, acknowledgment or filesystem rollback. Closing releases this advisory-lock reference. |
| ownership | Owns fd and schema/epoch index/frame vectors; member teardown releases their same-account buffers. |
| failure | Destructor cleanup does not throw; caller must use checked close when an error outcome is needed. |
| cost | One close syscall plus buffer/account release; may deallocate capacity, with no file-prefix scan. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0015

[Lines 65–66](../../../../../src/recovery/local_sink.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
File::File(File&& other) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer the sole local epoch sink descriptor, validation state and buffers. |
| inputs / outputs | Move constructor transfers limits, scanner/header/index, buffers, fd/stamp/counters/outcome/poison/torn state; source fd becomes -1 and source poisoned. |
| invariants | No second live writer/lock owner is created. Source must not be used for further file operations. |
| ownership | Moves accounted vectors/metadata and fd; destination retains existing account authority, without reopening or allocating a fresh grant. |
| failure | noexcept move; no filesystem syscall, sync or catch. |
| cost | Constant moves of fixed metadata/array and vector handles, not a copy of stored epochs/log bytes. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0016

[Lines 67–67](../../../../../src/recovery/local_sink.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void File::consume(std::uint64_t amount){if(amount>limits_.work-work_)throw ImageFailure(ImageFault::work);work_+=amount;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge cumulative sink codec/validation work without a grant refill. |
| inputs / outputs | Amount increments private work_ if it fits remaining limits_.work. |
| invariants | work_ begins within cap and is monotone; subtraction remains valid. Failure never refunds earlier work or changes the configured limit. |
| ownership | One owner counter; no storage/query mutation. |
| failure | ImageFailure(work) before counter overflow or over-cap increment. |
| cost | Constant checked arithmetic. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0017

[Lines 68–68](../../../../../src/recovery/local_sink.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ImageLimits File::record_limits() const {auto result=limits_.record;result.work=std::min(result.work,limits_.work-work_);return result;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Derive a per-record codec view bounded by the owner's remaining work. |
| inputs / outputs | Copied ImageLimits get work=min(record.work, total limit-work_). |
| invariants | Does not reset record fields/rows/bytes limits or owner cumulative accounting. Caller debits returned codec work with consume. |
| ownership | Returns fixed options copy, not an owning fresh account. |
| failure | No allocation or exception for admitted private counter invariant. |
| cost | Constant struct copy/min/subtraction. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0018

[Lines 69–121](../../../../../src/recovery/local_sink.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::int64_t File::call(Stage stage,std::size_t requested,int fd,const char* name,int other_fd,const char* other_name,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Perform one bounded Linux syscall attempt for the local epoch sink owner. |
| inputs / outputs | Validated stage-specific descriptors/names/buffer/offset/request drive openat/flock/pread/pwrite/fsync/linkat/unlinkat/ftruncate/close or entropy; returns result and sets errno. |
| invariants | Every attempt debits operations, including EINTR. Temporary cleanup bypasses ordinary cap but not U64 exhaustion. Admitting write/truncate/final link sets outcome unknown before the syscall, even on interruption; close executes once. Test-only hooks preserve real close and prevent hidden opened-fd leaks on synthetic after-open errors. Only the explicit emergency_cleanup flag from the eight-attempt failure helper bypasses the ordinary operation cap; normal post-link unlink/EINTR does not. |
| ownership | Borrows call buffers/names only synchronously; returned descriptors immediately enter a scoped/File owner at call sites. No buffer allocation in dispatcher. |
| failure | Limit/state failures throw fixed file Failure with current outcome; otherwise errno/result are interpreted by checked/caller. Close still releases fd when operation budget rejects its checked attempt. |
| cost | One syscall attempt plus fixed dispatch/counters, optionally transferring requested bytes. Attempts/byte caps do not bound fsync/lock/kernel wall time. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [tests/unit/file_cleanup_quota_test.cpp](../../../../../tests/unit/file_cleanup_quota_test.cpp) |

## B0019

[Lines 122–131](../../../../../src/recovery/local_sink.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::int64_t File::checked(Stage stage,std::size_t count,int fd,const char* name,int other_fd,const char* other_name,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Interpret local epoch sink syscall results and retry only safe interrupted stages. |
| inputs / outputs | Repeated call returns first nonnegative result; EINTR retries exclude close and final link. |
| invariants | Publication interruption is not retried or assumed absent. EWOULDBLOCK/EAGAIN on nonblocking flock maps busy; other errors map io. |
| ownership | No new resources retained beyond caller-provided fd/buffer; retries consume same cumulative operation budget. |
| failure | Typed Failure preserves syscall stage/current outcome/native errno. Retry ends at success, nonretryable failure or operation cap. |
| cost | One syscall per loop iteration; finite attempt budget bounds retries, not elapsed kernel time. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0020

[Lines 132–140](../../../../../src/recovery/local_sink.cpp#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void File::transfer(bool write,char* data,std::size_t size,std::uint64_t offset) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Complete a bounded positional local epoch sink read/write over short transfers. |
| inputs / outputs | Mutable buffer, byte count and validated offset loop checked pread/pwrite in at most configured chunk bytes until done. |
| invariants | Caller ensures offset/size fit admitted file/off_t bounds and buffer lifetime. Positive short transfers advance; zero write is EIO and zero read is truncated. |
| ownership | Borrows caller storage for this synchronous call; no copy/mirror/heap allocation here. |
| failure | Propagates fixed syscall/limit/zero-progress failure with current uncertainty. Writes may partially persist; no inverse/truncate-on-error is attempted. |
| cost | O(bytes transferred) kernel traffic and ceil(bytes/chunk) successful calls plus bounded EINTR retries. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0021

[Lines 141–147](../../../../../src/recovery/local_sink.cpp#L141); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool File::cleanup_temporary(int directory,const char* name) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove a private temporary name during local epoch sink exception unwinding. |
| inputs / outputs | Directory fd and private generated name attempt unlink up to eight times; success/ENOENT returns true. |
| invariants | Only EINTR retries. Mandatory temp cleanup bypasses ordinary operation cap, without permitting final-file rollback or history deletion. This fixed helper alone requests emergency_cleanup; normal publication cannot inherit the exemption by syscall stage. |
| ownership | Borrows name/directory; never unlinks the public destination from this helper. |
| failure | noexcept catch converts call exceptions/limit exhaustion to false, preserving the original publishing failure. Failed cleanup can leave an orphan temp. |
| cost | At most eight unlink attempts; no allocation/sync or directory scan. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [tests/unit/file_cleanup_quota_test.cpp](../../../../../tests/unit/file_cleanup_quota_test.cpp) |

## B0022

[Lines 148–189](../../../../../src/recovery/local_sink.cpp#L148); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
File File::create(const resource::MemoryAccount& account,std::string_view path,const Header& header,std::span<const ScalarType> schema,Limits limits) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create and durably publish a fresh local epoch sink without replacing any existing destination. |
| inputs / outputs | Account/path/Header plus typed output schema/limits privately encode/admit initial canonical epoch header, create an entropy-named 0600 O_EXCL sibling, lock it, write/fsync, link without replacement, unlink temp and fsync parent; returns sole File owner. |
| invariants | Existing final file/symlink is never replaced. At most sixteen name attempts; safe entropy/open retries consume cumulative operations. Final link is never retried on EINTR. Success adopts both complete header and directory entry as durable. |
| ownership | Account funds initial encoded bytes/schema/epoch index/frame vectors; scoped directory and returned File own descriptors. Generated path/name arrays stay on stack. |
| failure | Typed publication catch cleans only temp and enriches cleanup failure; before final-link admission it normalizes operation outcome unchanged, even if private inode bytes were written. Link-stage/postpublication uncertainty remains. Broad cleanup catch preserves other original exceptions. Final destination is never rolled back. |
| cost | Header encode/hash/copy plus bounded entropy/create attempts, write chunks, file fsync, link/unlink, directory fsync and metadata refresh. No old-prefix scan. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [tests/unit/local_sink_fault_test.cpp](../../../../../tests/unit/local_sink_fault_test.cpp) |

## B0023

[Lines 190–190](../../../../../src/recovery/local_sink.cpp#L190); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void File::ready() const {if(fd_<0 || poisoned_)fail(Fault::state,Stage::state,Outcome::unchanged);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject closed, moved-from or poisoned local epoch sink owners. |
| inputs / outputs | File fd/poison state returns normally only when fd&gt;=0 and not poisoned. |
| invariants | A failed post-validation I/O path must reopen/validate rather than blindly continue. This check does not itself rescan disk. |
| ownership | Reads owner flags; retains nothing. |
| failure | Fixed state Failure with unchanged attempted-operation outcome; no repair or implicit retry. |
| cost | Constant branches, no syscall or allocation. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0024

[Lines 191–196](../../../../../src/recovery/local_sink.cpp#L191); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
State File::state() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe current sink prefix, buffers and recovery-required status without minting authority. |
| inputs / outputs | Open File returns Header, indexed epoch/generation/sequence/bytes, spent work/operations, requested buffer allocations and torn/poison markers. |
| invariants | Unlike ready(), state intentionally remains readable while poisoned so callers can see recovery_required. It grants no Receipt or query-correctness claim. |
| ownership | Returns copied fixed metadata. allocation_usage reads actual schema/index/scratch/other capacities from their existing account allocation headers. |
| failure | Closed/moved owner throws fixed state failure; no file sync or validation is attempted. |
| cost | Fixed four buffer-accounting lookups and metadata copy; no prefix/row scan. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0025

[Lines 197–201](../../../../../src/recovery/local_sink.cpp#L197); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Prefix File::prefix(std::uint64_t sequence) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a descriptive fingerprint for one admitted complete sink prefix. |
| inputs / outputs | Ready File and sequence within header.base_sequence..current return generation, sequence, byte end and header/chain checksum. |
| invariants | Uses actual validated epoch index; base uses header fingerprint. A Prefix report cannot construct a Receipt or authorize history retirement by itself. Valid complete prefixes remain inspectable through a torn suffix. |
| ownership | Copies fixed values; no array view or writer ownership escapes. |
| failure | Closed/poisoned/out-of-range binding rejects before lookup. |
| cost | Constant checked index access, no I/O/hash/re-encoding. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0026

[Lines 202–202](../../../../../src/recovery/local_sink.cpp#L202); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Receipt File::receipt() const {ready();if(torn_)fail(Fault::state,Stage::state,outcome_);return Receipt(header_,prefix(header_.base_sequence+index_.size()));}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mint a local storage Receipt only from a healthy complete sink owner. |
| inputs / outputs | Ready, non-torn File constructs private Receipt from bound Header and current complete prefix. |
| invariants | Receipt authenticates this file's admitted durable prefix, not arbitrary producer query correctness. Torn suffix prevents acknowledgment until repair. |
| ownership | Copies fixed immutable header/prefix into Receipt; it survives File destruction without retaining an fd or rows. |
| failure | State/torn failure precedes receipt construction; no mutable import path. |
| cost | Constant fixed metadata copy, no syscall or heap allocation. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0027

[Lines 203–203](../../../../../src/recovery/local_sink.cpp#L203); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void File::refresh(){static_cast<void>(checked(Stage::stat_file,0,fd_,nullptr,-1,nullptr,nullptr,0,&stamp_));}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record current stat metadata after admitted local epoch sink progress. |
| inputs / outputs | Checked fstat(fd) replaces stamp_. |
| invariants | Caller invokes only on an owned descriptor. Refresh does not prove content correctness or perform fsync by itself. |
| ownership | Writes fixed stat record; borrows no payload. |
| failure | Operation/syscall failure propagates; after durable write callers may remain poisoned despite durable outcome. |
| cost | One checked fstat attempt plus allowed EINTR retries. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0028

[Lines 204–207](../../../../../src/recovery/local_sink.cpp#L204); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void File::unchanged_file() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that the owned local epoch sink file still matches its admitted stamp. |
| inputs / outputs | Checked fstat compared with stamp_ fails changed on inode/size/mtime/ctime mismatch. |
| invariants | Assumes cooperating single writer and stable trusted namespace; hash/frame/EOF validation remains separate. |
| ownership | Stack stat record, no retained allocation. |
| failure | Typed changed/io/limit failure preserves current outcome; no automatic rescan/rollback. |
| cost | One checked fstat plus fixed comparisons, not a file scan. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0029

[Lines 208–208](../../../../../src/recovery/local_sink.cpp#L208); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L208-L208:sha256:cf04d99c0f5d3521f67f7c587d20dd3592a5024b903529e1e468844f7fae8135
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Opens a private namespace for incomplete-prefix validation used by the sink-file open path. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [docs/code_specs/files/src/recovery/local_sink.cpp.md](local_sink.cpp.md), [docs/local-sink.md](../../../../local-sink.md), [docs/journal-files.md](../../../../journal-files.md) |

## B0030

[Lines 209–219](../../../../../src/recovery/local_sink.cpp#L209); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void incomplete_prefix(std::string_view bytes,ImageLimits limits) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate the actually present prefix of an incomplete later sink header. |
| inputs / outputs | At most frame_header_size-1 bytes plus ImageLimits check available magic/version/body-size/lowercase digest prefix and protected-header checksum prefix. |
| invariants | Only a later frame may be incomplete; open separately rejects incomplete mandatory initial header. Any impossible available bytes are corruption, not repairable tail. |
| ownership | Borrows stack/scratch prefix; SHA output uses fixed array, retains no source bytes. |
| failure | ImageFailure(corrupt/version/limit) rejects without disk mutation. Caller admits one/two-pass declared work before validation. |
| cost | Bounded &lt;=147-byte scans/hash; no whole-body or file scan. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0031

[Lines 220–220](../../../../../src/recovery/local_sink.cpp#L220); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L220-L220:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the enclosing implementation scope at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [docs/code_specs/files/src/recovery/local_sink.cpp.md](local_sink.cpp.md), [docs/local-sink.md](../../../../local-sink.md), [docs/journal-files.md](../../../../journal-files.md) |

## B0032

[Lines 221–268](../../../../../src/recovery/local_sink.cpp#L221); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
File File::open(const resource::MemoryAccount& account,std::string_view path,const Header& expected,std::span<const ScalarType> schema,Limits limits,HeaderMatch match) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open, lock, validate and adopt the complete sink prefix before exposing an owner. |
| inputs / outputs | Account/path/expected Header/schema/limits/HeaderMatch open no-follow regular inode, flock, scan header/epochs, build typed index and mark only a valid incomplete later tail. |
| invariants | Exact mode compares full header; identity mode may discover stored first_generation/base while keeping other identity/schema fields exact. Ordinal/sequence contiguous and generation nondecreasing. Full corruption never repairs. Exact EOF/stamp and file+directory fsync finish admission. |
| ownership | Original account owns schema/index/scratch; retains one bounded frame and O(epochs) index, not all decoded rows. File lock stays until close/destruction. |
| failure | Any path/type/binding/codec/allocation/work/I/O/EOF/stamp/sync failure destroys private owners; no truncation or append occurs. Successful open can adopt a complete frame formerly reported unknown. |
| cost | O(file bytes + epochs) framed scan/hash, per-frame codec visits and chain work, index growth, reads/stat/lock plus file and directory fsync. Not constant-time reopen. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink_codec.cpp](../../../../../src/recovery/local_sink_codec.cpp), [tests/unit/local_sink_test.cpp](../../../../../tests/unit/local_sink_test.cpp) |

```text
const auto info=detail::inspect(view(result.scratch_),result.schema_,result.record_limits());result.consume(info.work);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit each complete sink frame before extending the indexed prefix. |
| inputs / outputs | Schema-bound inspect validates canonical frame; first record binds Header, later records must be exact next ordinal/sequence and nondecreasing generation before chain/index append. |
| invariants | Only complete frames update bytes_. Later valid incomplete suffix is marked torn; mandatory header cannot be partial. |
| ownership | Scratch holds one frame; account-funded index retains offsets/fingerprints rather than decoded rows. |
| failure | Any complete corruption/binding/work/cap failure aborts private open without repair. |
| cost | Per-frame schema/typed-byte/hash scan plus fixed chain hash and geometric metadata append. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink_codec.cpp](../../../../../src/recovery/local_sink_codec.cpp) |

## B0033

[Lines 269–271](../../../../../src/recovery/local_sink.cpp#L269); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool File::append(std::uint64_t generation,std::uint64_t sequence,std::span<const RowView> rows) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accept one complete physical output epoch through canonical append-or-duplicate logic. |
| inputs / outputs | Generation, physical sequence and immutable RowView span forward to accept_epoch(...,false); true means newly durable append, false exact existing epoch. |
| invariants | No per-row publication and no ordinal/checksum-only deduplication. Empty epoch rows still form a complete physical closure. |
| ownership | Borrows rows/scalars only synchronously; encoder freezes account-funded bytes before I/O. |
| failure | All state/binding/codec/work/allocation/I/O outcomes are those of accept_epoch; producer must retain output until acceptance. |
| cost | Constant forwarding plus canonical encoding/comparison/write/fsync costs below. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0034

[Lines 272–274](../../../../../src/recovery/local_sink.cpp#L272); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void File::verify_epoch(std::uint64_t generation,std::uint64_t sequence,std::span<const RowView> rows) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify an already persisted complete epoch without appending missing output. |
| inputs / outputs | Generation/sequence/RowViews call accept_epoch(...,true), rejecting absence and allowing validation through a well-formed incomplete later tail. |
| invariants | Recovery verification grants no append or implicit repair and compares full canonical frame against actual persisted bytes. |
| ownership | Input views remain caller-owned; account funds canonical/comparison buffers. |
| failure | Any mismatch/absence/codec/work/I/O failure propagates; no disk mutation by this mode. |
| cost | Canonical encoding plus one stored frame read/exact comparison and metadata checks; no whole-prefix rescan. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0035

[Lines 275–301](../../../../../src/recovery/local_sink.cpp#L275); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool File::accept_epoch(std::uint64_t generation,std::uint64_t sequence,std::span<const RowView> rows,bool verify_only) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare canonical bytes and funded metadata before writing or verifying one sink epoch. |
| inputs / outputs | Ready File, generation/sequence/rows and verify_only choose exact existing-frame comparison or contiguous new append; returns false only for exact duplicate. |
| invariants | New epochs require no torn suffix, next sequence, epoch cap and nondecreasing generation. Duplicate requires same generation/size and full encoded-byte equality. Index capacity/hash work are prepared before I/O; fsync and refresh precede nonallocating index/byte publication. |
| ownership | Account owns temporary canonical frame, reusable comparison buffer and geometric index capacity. No runtime/source row mirror or rollback log is added. |
| failure | Pre-I/O codec/allocation/binding/work failures keep File usable (spent work may increase). Around reads/writes, poisoned_ is set before unchanged-file/I/O checks; any such failure requires reopen. Duplicate clears poison before later work/mismatch checks. New append outcome becomes durable after fsync, but later refresh failure still leaves poison set. |
| cost | Encoder canonical sort/copy/hash cost depends on rows/typed bytes; duplicate reads and compares one full frame, new append writes frame chunks+fsync+stat and O(1) index append after possible geometric reserve. No historical epoch scan. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink_codec.cpp](../../../../../src/recovery/local_sink_codec.cpp), [tests/unit/local_sink_fault_test.cpp](../../../../../tests/unit/local_sink_fault_test.cpp) |

```text
if(duplicate) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify a duplicate sink epoch against its complete canonical persisted bytes. |
| inputs / outputs | Existing indexed generation/size must match encoded frame, then one frame is reread between stamp checks and compared byte for byte. |
| invariants | Checksums/ordinals alone never deduplicate. verify_only cannot append absent epochs; valid incomplete later suffix does not prevent comparison. |
| ownership | Canonical temporary and reusable other_ buffer use same account; no mutable row view retained. |
| failure | Read/stamp failure leaves poison; after successful I/O poison clears before comparison-work/mismatch errors. Disk is never written by this branch. |
| cost | One bounded frame read + full comparison and declared2*frame work; encoder canonicalization precedes this branch. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

```text
if(index_.size()==index_.capacity()) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund geometric sink-index growth before any appended epoch can persist. |
| inputs / outputs | Full index capacity doubles up to admitted epochs/SIZE_MAX maximum; reserve occurs before poisoned write path. |
| invariants | After fsync/refresh, push of plain Index must not allocate/throw. Account covers transient old/new vector capacity overlap. |
| ownership | Same-account vector owns index entries; only fixed hash/offset/size per complete epoch, no row mirror. |
| failure | reserve allocation failure precedes disk mutation and leaves old index/prefix usable with already-spent work retained. |
| cost | Amortized geometric metadata growth, worst-case O(existing epochs) relocation at a growth step; no per-append old-file scan. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0036

[Lines 302–313](../../../../../src/recovery/local_sink.cpp#L302); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Epoch File::read_epoch(std::uint64_t sequence) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read and decode one actual complete sink epoch into independently owned native rows. |
| inputs / outputs | Ready File and in-range sequence select indexed offset/size, fill account-funded scratch under before/after stamp checks, inspect binding and decode Epoch. |
| invariants | Checks generation/sequence/ordinal against admitted index; returning Epoch owns its values after File/session destruction. Does not consume/acknowledge producer output. |
| ownership | Scratch retained by File; decoded ImageVector&lt;Row&gt;/AccountedRow payload use same receiving account and escape by ownership. |
| failure | Scratch allocation precedes poisoning; I/O/stamp failure leaves poisoned. Poison clears before codec/decode so later allocation/validation/work failure does not itself poison this owner. Spent codec/reserved decode work is not refunded. |
| cost | One frame read plus inspection/hash/decode and O(rows+scalar bytes) owning payload; consume reserves 3*inspection work for decode rather than a fresh grant. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink_codec.cpp](../../../../../src/recovery/local_sink_codec.cpp) |

## B0037

[Lines 314–317](../../../../../src/recovery/local_sink.cpp#L314); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void File::repair_tail() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Repair only the validated incomplete sink suffix after the last complete indexed epoch. |
| inputs / outputs | Ready File resets attempted outcome; non-torn returns, otherwise poison/check stamp/ftruncate(bytes_)/fsync/refresh then clears torn/poison. |
| invariants | Complete epochs and their chain/index remain intact. Receipt/append blocked until successful explicit repair; complete corruption is not admitted as a torn suffix. |
| ownership | Uses the owned locked fd and existing metadata; no row copy/extra account. |
| failure | After poison, any failure retains recovery requirement. Truncate admission marks unknown; fsync marks durable; later stat failure still requires reopen. |
| cost | Fixed checks plus fstat, truncate, fsync and refresh syscall attempts; no whole-prefix rescan. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [tests/unit/local_sink_fault_test.cpp](../../../../../tests/unit/local_sink_fault_test.cpp) |

## B0038

[Lines 318–318](../../../../../src/recovery/local_sink.cpp#L318); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void File::close() {if(fd_<0)fail(Fault::state,Stage::state,Outcome::unchanged);const int old=fd_;fd_=-1;static_cast<void>(checked(Stage::close_file,0,old));}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release the sink writer lock with an explicit checked close. |
| inputs / outputs | Open fd is copied locally and fd_ reset to -1 before one checked close. |
| invariants | A close error never permits fd reuse/retry through this File. Does not implicitly sync or repair. |
| ownership | Transfers the sole descriptor to the one close attempt; buffers release later with owner. |
| failure | Already closed rejects; Linux EINTR is reported once, and operation-cap failure still calls raw_close. |
| cost | One close syscall and fixed state updates. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0039

[Lines 319–319](../../../../../src/recovery/local_sink.cpp#L319); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L319-L319:sha256:37c337ca25e31742986e5a4f5e34f43c093849c52aa8d6fc3ab940d164862d27
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::recovery::sink at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [docs/code_specs/files/src/recovery/local_sink.cpp.md](local_sink.cpp.md), [docs/local-sink.md](../../../../local-sink.md), [docs/journal-files.md](../../../../journal-files.md) |
