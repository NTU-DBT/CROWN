# `src/recovery/sql_rows_wal_file.cpp` — block usage map

[Source](../../../../../src/recovery/sql_rows_wal_file.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `f6bdd0e21473a548f873df4c70b9d40520689fbb9913243a909db65e5bf76a52`. 85 lines partitioned into 15 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../src/recovery/sql_rows_wal_file.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 6–14](../../../../../src/recovery/sql_rows_wal_file.cpp#L6) | Type/record definition: struct WalFile::Data |  · [reviewed contract](#b0002) |
| [B0003 · 15–15](../../../../../src/recovery/sql_rows_wal_file.cpp#L15) | Callable definition: WalFile::WalFile(resource::AccountedUnique&lt;Data&gt; value) noexcept : data_(std::move(value)) | calls data_, std::move · [reviewed contract](#b0003) |
| [B0004 · 16–17](../../../../../src/recovery/sql_rows_wal_file.cpp#L16) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0004) |
| [B0005 · 18–21](../../../../../src/recovery/sql_rows_wal_file.cpp#L18) | Callable definition: WalFile::Data& WalFile::data() const | calls file_detail::fail, ready; returns *data_ · [reviewed contract](#b0005) |
| [B0006 · 22–22](../../../../../src/recovery/sql_rows_wal_file.cpp#L22) | Callable definition: bool WalFile::requires_reopen() const noexcept | calls ; returns !data_ \|\| data_-&gt;io.fd&lt;0 \|\| data_-&gt;io.poisoned · [reviewed contract](#b0006) |
| [B0007 · 23–25](../../../../../src/recovery/sql_rows_wal_file.cpp#L23) | Callable definition: WalFileState WalFile::state() const | calls data, state, statistics; returns {d.cursor.state(),d.io.statistics(),d.io.torn} · [reviewed contract](#b0007) |
| [B0008 · 26–35](../../../../../src/recovery/sql_rows_wal_file.cpp#L26) | Callable definition: WalFile WalFile::create(const resource::MemoryAccount& account,std::string_view path, const Descriptor& descriptor,const WalHeade… | calls parsed, file_detail::binding, encode, record_limits; returns WalFile(std::move(owner)); growth make_accounted_unique · [reviewed contract](#b0008) |
| [B0009 · 36–39](../../../../../src/recovery/sql_rows_wal_file.cpp#L36) | Callable definition: WalFile WalFile::open(const resource::MemoryAccount& account,std::string_view path, const Descriptor& descriptor,const WalHeader&… | calls open_replay; returns open_replay(account,path,descriptor,expected,limits,nullptr,nullptr) · [reviewed contract](#b0009) |
| [B0010 · 40–66](../../../../../src/recovery/sql_rows_wal_file.cpp#L40) | Callable definition: WalFile WalFile::open_replay(const resource::MemoryAccount& account,std::string_view path, const Descriptor& descriptor,const Wal… | calls parsed, file_detail::binding, open, require; guard require(owner-&gt;cursor.state().records&lt;limits.scan.records,ImageFault::limit);; returns WalFile(std::move(owner)); growth make_accounted_unique; 1 loop sites; source comment (unverified): // Open scratch never retains the pending command; the receiving replay · [reviewed contract](#b0010) |
| [B0011 · 67–78](../../../../../src/recovery/sql_rows_wal_file.cpp#L67) | Callable definition: void WalFile::append(const Frame& frame) & | calls data, file_detail::fail, next, record_limits; source comment (unverified): // Private fixed-state staging preserves both cursor frontiers and its spent · [reviewed contract](#b0011) |
| [B0012 · 79–79](../../../../../src/recovery/sql_rows_wal_file.cpp#L79) | Callable definition: void WalFile::repair_tail() & | calls data, repair, state · [reviewed contract](#b0012) |
| [B0013 · 80–80](../../../../../src/recovery/sql_rows_wal_file.cpp#L80) | Callable definition: void WalFile::validate() & | calls data, validate · [reviewed contract](#b0013) |
| [B0014 · 81–84](../../../../../src/recovery/sql_rows_wal_file.cpp#L81) | Callable definition: void WalFile::close() & | calls file_detail::fail, close · [reviewed contract](#b0014) |
| [B0015 · 85–85](../../../../../src/recovery/sql_rows_wal_file.cpp#L85) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::recovery::sql_rows · [reviewed contract](#b0015) |

## B0001

[Lines 1–5](../../../../../src/recovery/sql_rows_wal_file.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L5:sha256:3eaa18a4ddc9adefa98861ec491739f2651fea60408ac4db71d98dc345629b5e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Include row-file helpers and open the WAL implementation namespace. |
| inputs / outputs | Expose shared transport helpers and binary require for the typed WalFile bodies. |
| invariants | No executable I/O or state check occurs here. |
| ownership | No runtime owner or backing allocation is created by these declarations. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0002

[Lines 6–14](../../../../../src/recovery/sql_rows_wal_file.cpp#L6); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L6-L14:sha256:dc66d06e11c42a494cddd12925567a3be2dcee852e3ea37671064629340ec94d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define and initialize the concrete rows WAL Data members. |
| inputs / outputs | Account, genuine Descriptor and FileLimits -&gt; Io(limits,CROWNRW2), receiving-frozen program, bounded WalCursor and empty account-backed scratch. |
| invariants | Constructor chooses framing and retained metadata; it does not open a file or validate any WAL frame. |
| ownership | Io later owns FD; program freeze aliases/copies receiving metadata; scratch retains its receiver allocator. |
| failure | Io/freeze/member construction failures unwind constructed members; no fallback account. |
| cost | Fixed Io/cursor/vector setup plus actual cold program freeze if account differs; no row/source scan or syscall. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0003

[Lines 15–15](../../../../../src/recovery/sql_rows_wal_file.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L15:sha256:36b32cb554841cbaa99b283f507ac75b8f9922e3e3ff9c1749183f148782a652
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt the already funded private WalFile owner. |
| inputs / outputs | AccountedUnique&lt;Data&gt; -&gt; moved data_ member. |
| invariants | No file is opened, scanned or validated by this constructor. |
| ownership | Transfers sole Data ownership without copying program/file/buffer state. |
| failure | Declared noexcept. |
| cost | O(1) handle move; no allocation or syscall. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0004

[Lines 16–17](../../../../../src/recovery/sql_rows_wal_file.cpp#L16); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L16-L17:sha256:7bb011bc386852104afbd8b2331876233dcd974ac7b2b406e79b0d80996eabb8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Default WalFile destruction and noexcept move construction. |
| inputs / outputs | Declare default destructor and default move constructor. |
| invariants | Move transfers the unique Data; destructor releases existing members, including best-effort Io close, rather than recovering a file. |
| ownership | Actual Data/program/vector/FD teardown follows member RAII; no state copy is created by move. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0005

[Lines 18–21](../../../../../src/recovery/sql_rows_wal_file.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L21:sha256:bfe9f926e1b44be8510cbedefce198c138f137477c958676311e88cf1f866ecb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an existing healthy WalFile private owner. |
| inputs / outputs | This facade -&gt; Data& after data_ presence check and io.ready(). |
| invariants | Guard tests fd/poison state only, not current inode/EOF contents. |
| ownership | Reference borrows existing unique Data; no account/FD ownership change. |
| failure | FileFailure(state,state,unchanged) for empty owner; io.ready failure propagates. |
| cost | O(1) pointer/flag tests; no allocation or syscall. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0006

[Lines 22–22](../../../../../src/recovery/sql_rows_wal_file.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L22:sha256:d8cd88558019a29973455891bde62dc4003ec8083022ed953b6e4552fbf8fa7e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe whether WalFile is absent, closed or poisoned. |
| inputs / outputs | This facade -&gt; !data_ \|\| io.fd&lt;0 \|\| io.poisoned. |
| invariants | Does not call data()/ready(), validate bytes or reopen a file. |
| ownership | Reads fixed pointer/fd/flag values only. |
| failure | noexcept; missing owner returns true. |
| cost | O(1) tests; no allocation or syscall. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0007

[Lines 23–25](../../../../../src/recovery/sql_rows_wal_file.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L25:sha256:9b7fb49c1a0c9025c2809633148f78e8f5a52ae2934ebe7f983ada8759e6e9f2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy retained WalFile transport state without rereading the file. |
| inputs / outputs | Healthy WalFile -&gt; WalFileState{cursor.state(),io.statistics(),io.torn}. |
| invariants | State describes retained validated prefix/counters; this getter neither establishes current EOF/stamp continuity nor native recovery authority. |
| ownership | Returns fixed-value copies; retains no file lock or payload backing. |
| failure | data() health guard propagates; no repair/reopen. |
| cost | O(1) fixed copies/index-end access; no allocation, scan or syscall. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0008

[Lines 26–35](../../../../../src/recovery/sql_rows_wal_file.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L35:sha256:b5c2050c13d936e4be9323b893e749c59360d2193893c4ec39fba942e88d0bf9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a typed WAL file from a genuine rows descriptor and fully funded header. |
| inputs / outputs | New path, receiving account, descriptor/header and finite FileLimits in; actual locked regular-file owner out. |
| invariants | Descriptor/header binding and row-family magic are checked; headers/schema/cursor/index metadata are admitted before inode publication. |
| ownership | The owner freezes genuine program metadata under the receiving account and shares the existing bounded Io engine. |
| failure | Any admission/creation failure follows actual file outcome and RAII FD/temp cleanup; existing entries are not silently replaced. |
| cost | Explicit header encoding/inspection and bounded durable create/link/sync; no native/source query or retained output queue. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0009

[Lines 36–39](../../../../../src/recovery/sql_rows_wal_file.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L39:sha256:8e0652844d95ce6ac35a88c85f0bbae9951776580b4443f18440bf786818b25e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open a typed rows WAL as transport validation without native replay. |
| inputs / outputs | Expected descriptor/header and finite path/file limits in; open_replay result with null visitor out. |
| invariants | Successful transport decoding confers no native source/proof/recovery authority. |
| ownership | The real file owner retains lock/program/cumulative state; no native database is built. |
| failure | All open_replay failure/outcome rules apply unchanged. |
| cost | Same bounded scan/file work; no hidden query or result evaluation. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0010

[Lines 40–66](../../../../../src/recovery/sql_rows_wal_file.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L40-L66:sha256:ae13ba3125b3fd34bcadef1e18f25f772fd273b5d2d17ec036b1b2075568d248
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open and validate the real typed WAL history, optionally visiting private replay frames. |
| inputs / outputs | Path/genuine descriptor/expected header/finite scan grants in; locked complete-prefix owner and torn-tail observation out. |
| invariants | Authenticate lengths/magic/types/ordinals/bindings; maintain cumulative grants and actual EOF/stamps. Replay callbacks stay private until Session's whole barrier; lower open does not repair tails. |
| ownership | One receiving-account scratch buffer and bounded index/cursor state; release scan scratch before returning, retain no decoded command/payload graph. |
| failure | Any malformed/changed/limited file closes the incomplete owner. Typed replay mismatch aborts private construction; no complete corruption is truncated. |
| cost | Actual bounded sequential byte/codec/I/O work and index metadata; per-frame work cannot refill cumulative scan/file grants. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0011

[Lines 67–78](../../../../../src/recovery/sql_rows_wal_file.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L67-L78:sha256:87d1721bf661f0c43cb36f51210163d10d0fadf9a75539cd74364bb68c05277d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one actual typed row WAL frame after staging all fixed cursor/frontier admissions. |
| inputs / outputs | Borrowed immutable Frame in; durable fixed WalState candidate out. |
| invariants | Re-inspect actual bytes under genuine program, not Frame.info alone; forbid writing through a torn suffix; preserve spent cursor grants. |
| ownership | Pre-fund state and append bytes, then noexcept-move the fixed candidate; retain no command copy. |
| failure | Malformed/admission failure publishes no cursor frontier; uncertain append requires reopen through the poisoned file owner. |
| cost | Actual codec plus write/sync/stat under existing cumulative file/scan limits; post-I/O frontier move allocates nothing. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0012

[Lines 79–79](../../../../../src/recovery/sql_rows_wal_file.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L79-L79:sha256:35f2c7c527e8aa0716ffc45aacdfe2e5da0402dfc9a26a4212de71c8cb0dc880
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Trim only the owner-known incomplete suffix after Session's whole semantic/file barrier. |
| inputs / outputs | Healthy/torn lower file owner and validated complete-prefix byte count in; confirmed truncation or no-op out. |
| invariants | Lower method does not itself prove native replay/sink coverage. A complete pending Input is never discarded as a torn record. |
| ownership | The same actual FD/lock and cumulative grants own truncate/sync/stat. |
| failure | Any uncertain repair requires fresh owner; complete-frame corruption was rejected earlier. |
| cost | Bounded truncate/sync/stat plus fixed state update; no source rebuild at this lower layer. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0013

[Lines 80–80](../../../../../src/recovery/sql_rows_wal_file.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L80-L80:sha256:4e08a24cabfe0e921f3dcba4af13beee5854ddc930de57116a693d556779611e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recheck the actual locked rows file identity/stamp and EOF without repairing it. |
| inputs / outputs | Current healthy owner in; confirmed unchanged observation out. |
| invariants | No DTO/hash alone replaces current-file continuity, and validation truncates nothing. |
| ownership | Retain the same file lock/FD and cumulative allowance. |
| failure | Change/truncation/I/O failure rejects and follows underlying poison/outcome contract. |
| cost | Bounded actual validation reads/stats under the current file grant. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0014

[Lines 81–84](../../../../../src/recovery/sql_rows_wal_file.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L81-L84:sha256:7adccf432bf2daa48f47b6d7ca10350c27133cccccc38ba956b295112ef4751a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume the owned rows-file descriptor exactly once while reporting explicit close failure. |
| inputs / outputs | Possibly live owner in; closed owner or typed FileFailure out. |
| invariants | Never retry Linux close after uncertain consumption; destructor remains best effort. |
| ownership | Move FD out of live ownership according to the existing Io close contract. |
| failure | Missing owner/state rejects; close outcome preserves fixed primary diagnosis and does not reopen automatically. |
| cost | One metered close; no source/query/codec scan. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0015

[Lines 85–85](../../../../../src/recovery/sql_rows_wal_file.cpp#L85); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L85-L85:sha256:5a88989d646de8c904ac4cbcd84db92dc85500003eb77614a29dedc10d8206dd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the surrounding namespace/type at this exact lexical boundary. |
| inputs / outputs | No runtime arguments, results or state transition. |
| invariants | A scope delimiter carries no admission, replay, invariant or rollback authority. |
| ownership | Namespace/type closure does not destroy objects merely by being declared here. |
| failure | No runtime failure or handler exists in this delimiter. |
| cost | No executable or per-query cost. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |
