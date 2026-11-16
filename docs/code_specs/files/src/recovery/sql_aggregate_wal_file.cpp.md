# `src/recovery/sql_aggregate_wal_file.cpp` — block usage map

[Source](../../../../../src/recovery/sql_aggregate_wal_file.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `aed45010e93d16b4a26a4d4a153697d523f53bae6b81d921a578066ceb2a6162`. 85 lines partitioned into 15 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 6–14](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L6) | Type/record definition: struct WalFile::Data |  · [reviewed contract](#b0002) |
| [B0003 · 15–15](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L15) | Callable definition: WalFile::WalFile(resource::AccountedUnique&lt;Data&gt; value) noexcept : data_(std::move(value)) | calls data_, std::move · [reviewed contract](#b0003) |
| [B0004 · 16–17](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L16) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0004) |
| [B0005 · 18–21](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L18) | Callable definition: WalFile::Data& WalFile::data() const | calls file_detail::fail, ready; returns *data_ · [reviewed contract](#b0005) |
| [B0006 · 22–22](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L22) | Callable definition: bool WalFile::requires_reopen() const noexcept | calls ; returns !data_ \|\| data_-&gt;io.fd&lt;0 \|\| data_-&gt;io.poisoned · [reviewed contract](#b0006) |
| [B0007 · 23–25](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L23) | Callable definition: WalFileState WalFile::state() const | calls data, state, statistics; returns {d.cursor.state(),d.io.statistics(),d.io.torn} · [reviewed contract](#b0007) |
| [B0008 · 26–35](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L26) | Callable definition: WalFile WalFile::create(const resource::MemoryAccount& account,std::string_view path, const Descriptor& descriptor,const WalHeade… | calls parsed, file_detail::binding, encode, record_limits; returns WalFile(std::move(owner)); growth make_accounted_unique · [reviewed contract](#b0008) |
| [B0009 · 36–39](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L36) | Callable definition: WalFile WalFile::open(const resource::MemoryAccount& account,std::string_view path, const Descriptor& descriptor,const WalHeader&… | calls open_replay; returns open_replay(account,path,descriptor,expected,limits,nullptr,nullptr) · [reviewed contract](#b0009) |
| [B0010 · 40–66](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L40) | Callable definition: WalFile WalFile::open_replay(const resource::MemoryAccount& account,std::string_view path, const Descriptor& descriptor,const Wal… | calls parsed, file_detail::binding, open, require; guard require(owner-&gt;cursor.state().records&lt;limits.scan.records,ImageFault::limit);; returns WalFile(std::move(owner)); growth make_accounted_unique; 1 loop sites; source comment (unverified): // Open scratch never retains the pending command; the receiving replay · [reviewed contract](#b0010) |
| [B0011 · 67–78](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L67) | Callable definition: void WalFile::append(const Frame& frame) & | calls data, file_detail::fail, next, record_limits; source comment (unverified): // Private fixed-state staging preserves both cursor frontiers and its spent · [reviewed contract](#b0011) |
| [B0012 · 79–79](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L79) | Callable definition: void WalFile::repair_tail() & | calls data, repair, state · [reviewed contract](#b0012) |
| [B0013 · 80–80](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L80) | Callable definition: void WalFile::validate() & | calls data, validate · [reviewed contract](#b0013) |
| [B0014 · 81–84](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L81) | Callable definition: void WalFile::close() & | calls file_detail::fail, close · [reviewed contract](#b0014) |
| [B0015 · 85–85](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L85) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::recovery::sql_aggregate · [reviewed contract](#b0015) |

## B0001

[Lines 1–5](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L5:sha256:9563270c61ade3a51c52abf3fa51172d7d91bf56feb008241847d4eeadaf99cb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports shared aggregate file I/O/binary helpers, opens the aggregate recovery namespace, and aliases the fixed validation helper used by WalFile operations. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/recovery/sql_aggregate_wal_file.cpp](../../../../../src/recovery/sql_aggregate_wal_file.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_wal_file.cpp.md](sql_aggregate_wal_file.cpp.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md) |

## B0002

[Lines 6–14](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L6); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WalFile::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund and retain the private WAL transport resources without retaining a second pending Input. |
| inputs / outputs | Receiving account, genuine Descriptor and FileLimits initialize Io, a frozen actual SqlAggregateProgram, a bounded WalCursor and empty account-backed scratch. |
| invariants | The schema freeze is paired with factory descriptor-hash binding; cursor holds original cumulative spent state/grants, not native replay authority. Scratch is used only for opening and released before return. |
| ownership | Data storage uses AccountedUnique with recovery_log purpose. Same-account freeze shares genuine immutable metadata; cross-account freeze funds the copy. Io owns the FD; no native state/token/undo/output queue is added. |
| failure | Account or metadata-freeze construction failures propagate and the accounted factory releases partial storage; no public owner escapes before file confirmation. |
| cost | Fixed cursor/Io state plus genuine schema and peak O(admitted frame bytes) opening scratch; cold metadata-copy work is outside file logical work. |
| Design | [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0003

[Lines 15–15](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WalFile::WalFile(resource::AccountedUnique<Data> value) noexcept : data_(std::move(value)) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish a fully prepared private Data owner as the public move-only WAL handle. |
| inputs / outputs | One AccountedUnique&lt;Data&gt; enters by value and is moved into data_; the private constructor returns a WalFile. |
| invariants | Factories invoke this only after create/open confirmation. The constructor performs no cursor transition, byte copy or additional FD acquisition. |
| ownership | Unique ownership and its receiving-account deleter transfer to the handle; the moved argument becomes empty. |
| failure | The constructor is noexcept; all allocating/validating/I/O work must have completed before it is called. |
| cost | Constant pointer/deleter move with no allocation or syscall. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [src/recovery/sql_aggregate_wal_file.cpp](../../../../../src/recovery/sql_aggregate_wal_file.cpp) |

## B0004

[Lines 16–17](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L16); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WalFile::~WalFile()=default;
WalFile::WalFile(WalFile&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define out-of-line WAL destruction and constant unique-owner move where private Data is complete. |
| inputs / outputs | Destruction releases data_; move transfers the AccountedUnique without duplicating Data or descriptor. |
| invariants | The moved-from handle is empty and the Data destructor is nothrow, satisfying the accounted ownership deleter requirement. |
| ownership | Destruction releases genuine schema/scratch and Io best-effort closes its live FD; move preserves existing account and lock lifetime in the destination. |
| failure | Neither defaulted operation reports file-close errors; explicit close is the reporting path. |
| cost | O(1) move; destruction pays actual retained metadata/scratch deallocation plus at most one raw close, outside metered operations. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp) |

## B0005

[Lines 18–21](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WalFile::Data& WalFile::data() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the guarded private route from a public WAL handle to its implementation state. |
| inputs / outputs | A const handle enters; a mutable Data reference is returned only after unique storage exists and Io::ready succeeds. |
| invariants | The helper rejects moved-from/closed/poisoned owners before callers read frontiers or attempt new transport work; it does not reject a merely torn suffix. |
| ownership | Returned reference borrows Data for the internal operation and does not extend lifetime or transfer FD ownership. |
| failure | Missing Data or unhealthy Io throws FileFailure(state,state,unchanged); no attempt is made to recover or clear poison. |
| cost | O(1) pointer and two scalar health checks, no allocation/I/O. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [src/recovery/sql_aggregate_wal_file.cpp](../../../../../src/recovery/sql_aggregate_wal_file.cpp) |

## B0006

[Lines 22–22](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool WalFile::requires_reopen() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allow reliable failure-state inspection even when normal WAL getters are unavailable. |
| inputs / outputs | The handle state enters implicitly; true means empty Data, negative FD or a latched Io poison flag. |
| invariants | A validated torn suffix alone does not set requires_reopen; it instead blocks append until authorized repair. |
| ownership | The predicate reads private scalar state and owns no snapshot, FD or recovery resource. |
| failure | It is noexcept and deliberately does not call data()/ready(), so moved-from and failed owners remain queryable. |
| cost | Constant pointer/flag checks without syscall or counter charge. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0007

[Lines 23–25](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WalFileState WalFile::state() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return only the WAL cursor state whose bytes were completely validated and durably confirmed. |
| inputs / outputs | A healthy owner returns cursor.state(), Io statistics and torn status by value. |
| invariants | An append candidate is not visible here until Io append/fsync/final stat succeed. wal.work counts accepted cursor codec work; statistics.work additionally includes prefix charges and other successful file-side charges. |
| ownership | The caller owns a fixed DTO copy while Data/FD and any account storage stay with the WalFile. |
| failure | data() rejects closed/empty/poisoned handles; the returned frontiers alone do not prove native replay or actual sink delivery. |
| cost | Constant-size state/counter copy with no file reads, hashing or memory growth. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_wal.cpp](../../../../../src/recovery/sql_aggregate_wal.cpp), [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0008

[Lines 26–35](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WalFile WalFile::create(const resource::MemoryAccount& account,std::string_view path,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a new durable WAL header with receiving-schema and cumulative-work admission before the first file mutation. |
| inputs / outputs | Account/path/genuine Descriptor/WalHeader/limits enter; a locked WalFile returns after header installation and final stat. |
| invariants | Path and descriptor hash binding precede Data allocation; Data freezes actual schema. Header encode work is charged, then the same bytes feed a zero-state cursor under remaining work before Io::create. |
| ownership | One receiving-account Data and one temporary encoded Frame own all retained/provisional storage; the header Frame dies after creation and no command is retained. |
| failure | Path/binding/codec/cursor/account failures happen before file creation; Io create failures propagate its no-replace/outcome/cleanup metadata and RAII releases the provisional owner. |
| cost | Cold schema share/freeze plus fixed-header encode and inspect/feed passes, then O(header bytes) chunked file creation; encoding and cursor codec work are separately consumed from the same cumulative file grant. |
| Design | [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp), [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [src/recovery/sql_aggregate_wal.cpp](../../../../../src/recovery/sql_aggregate_wal.cpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0009

[Lines 36–39](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WalFile WalFile::open(const resource::MemoryAccount& account,std::string_view path,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a transport-only WAL open that uses the complete private replay scanner without a callback. |
| inputs / outputs | Account/path/Descriptor/exact expected header/limits enter; open_replay receives null visitor/context and returns the confirmed owner. |
| invariants | Public open cannot visit partial scan results or publish a replay effect before full EOF/stamp/sync confirmation. |
| ownership | Arguments are borrowed and all resulting file/schema/scratch ownership belongs to the delegated receiving factory. |
| failure | Every scanner, account and file error propagates unchanged; the wrapper adds no catch, repair or fallback. |
| cost | Constant delegation overhead plus the full bounded opening scan cost of open_replay. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [src/recovery/sql_aggregate_wal_file.cpp](../../../../../src/recovery/sql_aggregate_wal_file.cpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0010

[Lines 40–66](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WalFile WalFile::open_replay(const resource::MemoryAccount& account,std::string_view path,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate an entire locked WAL prefix and optionally feed private receiving-session replay before publishing the owner. |
| inputs / outputs | Receiving account/path/genuine Descriptor/exact WalHeader/limits and private function/context enter; each accepted frame is visited with its existing Inspected result and post-feed WalState, then the confirmed owner returns after finish_open. |
| invariants | Every frame consumes record/byte/work admission and must preserve exact expected header. Incomplete suffix must fit next ordinal/allowed Input-or-decision/terminal constraints. Complete bad frames are fatal; open never truncates. |
| ownership | Provisional Data owns FD/frozen schema/accounted scratch. Visitor bytes borrow scratch and must not escape; the receiving coordinator owns any one decoded pending command. Scratch is swapped out before return. |
| failure | Any wire/order/header/account/callback/EOF/stamp/sync failure discards provisional Data. Visitor effects are required to stay private until the whole function succeeds; no catch/undo system enforces that external discipline. |
| cost | Sequential admitted file scan with one transport inspect per complete frame; callback reuses that result. Input decoding/native work remains separate. Opening scratch is released before return; no second command or runtime copy is retained. |
| Design | [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_wal.cpp](../../../../../src/recovery/sql_aggregate_wal.cpp), [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0011

[Lines 67–78](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void WalFile::append(const Frame& frame) & {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stage a genuine transport transition in fixed private state, durably write its borrowed bytes, then publish the confirmed cursor. |
| inputs / outputs | A healthy untorn owner and live immutable Frame enter; bytes are re-fed under the frozen receiving program, and success replaces d.cursor with the accepted candidate. |
| invariants | The candidate copies d.cursor.state_, including spent records/bytes/codec work, rather than refilling it. Its per-call frame grant is bounded by Io remaining work; Frame::info() and moved-from cached metadata cannot authorize bytes. |
| ownership | The caller owns Frame through validation/write; the candidate is fixed stack state and owns no command payload. Publication is nonallocating cursor move followed by poison clear, after fsync plus final size/stat. |
| failure | Failed feed preserves original cursor and returns no codec charge to Io. Successful codec work is consumed before I/O; any later Io append failure keeps poison set and original cursor unpublished until fresh open. |
| cost | O(frame bytes/fields) allocation-free codec validation plus bounded chunked write/fsync/stat, fixed candidate storage and no second owned pending-command/frame buffer. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_wal.cpp](../../../../../src/recovery/sql_aggregate_wal.cpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0012

[Lines 79–79](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void WalFile::repair_tail() & {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the validated WAL complete-byte frontier as the only permitted low-level truncation point. |
| inputs / outputs | A healthy owner passes cursor.state().bytes to Io::repair; no additional parameter or native replay token enters. |
| invariants | Complete pending Inputs and decisions remain within that frontier. The caller must already have completed selected-root/native/sink/EOF/stamp semantic validation; this public method does not enforce it. |
| ownership | The existing Io FD is reused; no command bytes, native runtime or output spool are retained by repair. |
| failure | Health/repair exceptions propagate directly; untorn state is a no-op and uncertain repair requires reopening. |
| cost | O(1) cursor-frontier access plus bounded stamp/truncate/fsync/final-stat work in Io. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0013

[Lines 80–80](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void WalFile::validate() &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply the existing held-file validation barrier to the private WalFile receiver. |
| inputs / outputs | Friend Session calls a healthy live owner; data() checks ownership before delegating to Io::validate. |
| invariants | Validation neither advances transport/native frontiers nor repairs a suffix. A poisoned file cannot manufacture a healthy observation. |
| ownership | Borrows the existing private Io/FD; no extra frame, schema or lock owner. |
| failure | State/I/O failures propagate directly; Io retains poison after any admitted validation uncertainty. |
| cost | Fixed wrapper work plus the three-call Io stamp/EOF barrier; no allocation. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [src/recovery/sql_aggregate_wal_file.cpp](../../../../../src/recovery/sql_aggregate_wal_file.cpp) |

## B0014

[Lines 81–84](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void WalFile::close() & {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allow explicit checked FD consumption even after WAL uncertainty has disabled normal getters. |
| inputs / outputs | A nonempty WalFile forwards to Io::close without calling data()/ready(); success returns void. |
| invariants | Poison is not bypassed for writes or state; this bypass exists solely to end the FD lifetime once. |
| ownership | Data/accounted schema remain in the owner while the underlying FD is set -1 and consumed. |
| failure | Moved-from handle throws state; Io reports already-closed, quota or close errors after its documented descriptor-consumption rule. |
| cost | Constant handle check plus one checked close path, without parsing, allocation or state publication. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0015

[Lines 85–85](../../../../../src/recovery/sql_aggregate_wal_file.cpp#L85); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L85-L85:sha256:92582b45ad46706cdfae3684126917692713a5a92eff88bf2e3bcc42f5a8da44
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::recovery::sql_aggregate at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/sql_aggregate_wal_file.cpp](../../../../../src/recovery/sql_aggregate_wal_file.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_wal_file.cpp.md](sql_aggregate_wal_file.cpp.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md) |
