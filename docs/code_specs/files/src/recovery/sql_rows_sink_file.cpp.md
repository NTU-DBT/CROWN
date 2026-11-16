# `src/recovery/sql_rows_sink_file.cpp` — block usage map

[Source](../../../../../src/recovery/sql_rows_sink_file.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `4531959de9a52607ff45b78f6863bad9e11955f426afe23506e9f120255b486b`. 130 lines partitioned into 25 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../src/recovery/sql_rows_sink_file.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares types or opens a type body. |  · [reviewed contract](#b0001) |
| [B0002 · 8–8](../../../../../src/recovery/sql_rows_sink_file.cpp#L8) | Type/record definition: struct Index |  · [reviewed contract](#b0002) |
| [B0003 · 9–14](../../../../../src/recovery/sql_rows_sink_file.cpp#L9) | Member/declaration region. |  · [reviewed contract](#b0003) |
| [B0004 · 15–17](../../../../../src/recovery/sql_rows_sink_file.cpp#L15) | Callable definition: Data(const resource::MemoryAccount& account,const Descriptor& descriptor,const SinkHeader& value,FileLimits limits) : io(limits,"… | calls io, program, frontend::SqlRowsProgram::freeze, header · [reviewed contract](#b0004) |
| [B0005 · 18–18](../../../../../src/recovery/sql_rows_sink_file.cpp#L18) | Callable definition: \[\[nodiscard\]\] const SinkPrefix& latest() const noexcept | calls empty, back; returns index.empty()?baseline:index.back().prefix · [reviewed contract](#b0005) |
| [B0006 · 19–24](../../../../../src/recovery/sql_rows_sink_file.cpp#L19) | Callable definition: void header_frame(std::string_view bytes,const Inspected& info) | calls require, consume, size, std::copy_n; guard require(io.limits.scan.records&gt;0,ImageFault::limit); · [reviewed contract](#b0006) |
| [B0007 · 25–26](../../../../../src/recovery/sql_rows_sink_file.cpp#L25) | Explanatory comments or spacing. | source comment (unverified): // New epoch admission and index growth finish before any append I/O. A · [reviewed contract](#b0007) |
| [B0008 · 27–43](../../../../../src/recovery/sql_rows_sink_file.cpp#L27) | Callable definition: \[\[nodiscard\]\] Index next(std::string_view bytes,const Inspected& info) | calls require, latest, size, consume; guard require(info.kind==Kind::row_epoch,ImageFault::binding);; returns result; growth reserve; source comment (unverified): // New epoch admission and index growth finish before any append I/O. A · [reviewed contract](#b0008) |
| [B0009 · 44–44](../../../../../src/recovery/sql_rows_sink_file.cpp#L44) | Closes surrounding scope/type. |  · [reviewed contract](#b0009) |
| [B0010 · 45–45](../../../../../src/recovery/sql_rows_sink_file.cpp#L45) | Callable definition: SinkFile::SinkFile(resource::AccountedUnique&lt;Data&gt; value) noexcept : data_(std::move(value)) | calls data_, std::move · [reviewed contract](#b0010) |
| [B0011 · 46–47](../../../../../src/recovery/sql_rows_sink_file.cpp#L46) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0011) |
| [B0012 · 48–51](../../../../../src/recovery/sql_rows_sink_file.cpp#L48) | Callable definition: SinkFile::Data& SinkFile::data() const | calls file_detail::fail, ready; returns *data_ · [reviewed contract](#b0012) |
| [B0013 · 52–52](../../../../../src/recovery/sql_rows_sink_file.cpp#L52) | Callable definition: bool SinkFile::requires_reopen() const noexcept | calls ; returns !data_ \|\| data_-&gt;io.fd&lt;0 \|\| data_-&gt;io.poisoned · [reviewed contract](#b0013) |
| [B0014 · 53–55](../../../../../src/recovery/sql_rows_sink_file.cpp#L53) | Callable definition: SinkFileState SinkFile::state() const | calls data, latest, size, statistics; returns {d.header,d.latest(),d.index.size()+1,d.io.statistics(),d.io.torn} · [reviewed contract](#b0014) |
| [B0015 · 56–59](../../../../../src/recovery/sql_rows_sink_file.cpp#L56) | Callable definition: SinkPrefix SinkFile::prefix(std::uint64_t sequence) const | calls data, require, size; guard const auto& d=data();require(sequence&gt;=d.header.base_sequence && sequence-d.header.base_sequence&lt;=d…; returns sequence==d.header.base_sequence?d.baseline:d.index\[static_cast&lt;std::size_t&gt;(sequence-d.header.base… · [reviewed contract](#b0015) |
| [B0016 · 60–63](../../../../../src/recovery/sql_rows_sink_file.cpp#L60) | Callable definition: SinkReceipt SinkFile::receipt() const | calls data, file_detail::fail, SinkReceipt, latest; returns SinkReceipt(d.header,d.latest()) · [reviewed contract](#b0016) |
| [B0017 · 64–71](../../../../../src/recovery/sql_rows_sink_file.cpp#L64) | Callable definition: SinkFile SinkFile::create(const resource::MemoryAccount& account,std::string_view path, const Descriptor& descriptor,const SinkHe… | calls parsed, file_detail::binding, encode, record_limits; guard require(frame.bytes().size()&lt;=limits.scan.bytes,ImageFault::limit);owner-&gt;header_frame(frame.bytes(…; returns SinkFile(std::move(owner)); growth make_accounted_unique · [reviewed contract](#b0017) |
| [B0018 · 72–91](../../../../../src/recovery/sql_rows_sink_file.cpp#L72) | Callable definition: SinkFile SinkFile::open(const resource::MemoryAccount& account,std::string_view path, const Descriptor& descriptor,const SinkHead… | calls parsed, file_detail::binding, open, require; guard require((offset==0?0:owner-&gt;index.size()+1)&lt;limits.scan.records,ImageFault::limit);; returns SinkFile(std::move(owner)); growth make_accounted_unique, push_back; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 92–92](../../../../../src/recovery/sql_rows_sink_file.cpp#L92) | Callable definition: bool SinkFile::append(const Frame& frame) & | calls accept; returns accept(frame,false) · [reviewed contract](#b0019) |
| [B0020 · 93–93](../../../../../src/recovery/sql_rows_sink_file.cpp#L93) | Callable definition: void SinkFile::verify(const Frame& frame) & | calls accept · [reviewed contract](#b0020) |
| [B0021 · 94–123](../../../../../src/recovery/sql_rows_sink_file.cpp#L94) | Callable definition: bool SinkFile::accept(const Frame& frame,bool verify_only) | calls data, file_detail::fail, bytes, inspect; guard require(info.kind==Kind::row_epoch,ImageFault::binding);; returns false; true; growth push_back, resize; 1 loop sites; source comment (unverified): // Compare the whole real epoch in bounded chunks; no second owned output · [reviewed contract](#b0021) |
| [B0022 · 124–124](../../../../../src/recovery/sql_rows_sink_file.cpp#L124) | Callable definition: void SinkFile::repair_tail() & | calls data, repair, latest · [reviewed contract](#b0022) |
| [B0023 · 125–125](../../../../../src/recovery/sql_rows_sink_file.cpp#L125) | Callable definition: void SinkFile::validate() & | calls data, validate · [reviewed contract](#b0023) |
| [B0024 · 126–129](../../../../../src/recovery/sql_rows_sink_file.cpp#L126) | Callable definition: void SinkFile::close() & | calls file_detail::fail, close · [reviewed contract](#b0024) |
| [B0025 · 130–130](../../../../../src/recovery/sql_rows_sink_file.cpp#L130) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::recovery::sql_rows · [reviewed contract](#b0025) |

## B0001

[Lines 1–7](../../../../../src/recovery/sql_rows_sink_file.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:c298dce2e5bace44873484b67385973a951941fc292f8240d08260e2dfd40ee0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Include row-file/algorithm helpers and open the sink Data type. |
| inputs / outputs | Expose shared helpers/binary require and begin SinkFile::Data. |
| invariants | No file operation or instance construction executes. |
| ownership | No runtime owner or backing allocation is created by these declarations. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0002

[Lines 8–8](../../../../../src/recovery/sql_rows_sink_file.cpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L8-L8:sha256:aa0853155b54176bc59549212148fdb6e2d1d898de016749ec37e93e414a9860
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define one descriptive sink prefix index entry. |
| inputs / outputs | Index contains SinkPrefix prefix and uint64 offset,size. |
| invariants | The entry does not own payload bytes or validate its numeric relationship to any file. |
| ownership | Owns fixed scalar/hash metadata only; vector storage belongs to enclosing Data. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0003

[Lines 9–14](../../../../../src/recovery/sql_rows_sink_file.cpp#L9); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L9-L14:sha256:512342e844205e0256c63a641e5aca7c508eed4985e13c05f678e42fcfd05ce1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare sink file/program/header/baseline/index/scratch members. |
| inputs / outputs | Members are Io,SqlRowsProgram,SinkHeader,SinkPrefix,ImageVector&lt;Index&gt;,ImageVector&lt;char&gt;. |
| invariants | Declarations alone do not freeze a program, fund buffers, scan a file or populate an index. |
| ownership | Io/program/vectors retain their actual owners when constructed; no payload queue is declared. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0004

[Lines 15–17](../../../../../src/recovery/sql_rows_sink_file.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L17:sha256:23e7ecea959375387d8639339ca31db072462af99f48c0768d1d660b6341a05c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize the concrete rows sink metadata and empty receiving buffers. |
| inputs / outputs | Account, genuine Descriptor, SinkHeader value and FileLimits -&gt; CROWNRW2 Io, receiving-frozen program, copied header and empty index/scratch. |
| invariants | No sink header bytes are encoded/accepted and no file is opened by this constructor. |
| ownership | Program freeze aliases/copies receiver metadata; index/scratch retain receiver allocators; Io later owns FD. |
| failure | Io/freeze/member construction failures unwind partial ownership; no retry/fallback. |
| cost | Fixed metadata/vector setup plus actual cold program freeze if needed; no payload scan or syscall. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0005

[Lines 18–18](../../../../../src/recovery/sql_rows_sink_file.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L18:sha256:e0dcb81a613e5e5fb7b58cf4ca303b0e9290753170126f5a0dd1fd851ebb8031
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the last indexed confirmed prefix or the header-only baseline. |
| inputs / outputs | This Sink Data -&gt; const SinkPrefix& from index.back().prefix when nonempty, else baseline. |
| invariants | No guard/validation runs here; caller must use the correct retained Data and valid index/baseline state. |
| ownership | Reference borrows baseline or vector entry; vector reallocation/reset/destruction can invalidate an indexed reference. |
| failure | noexcept; no explicit failing check. |
| cost | O(1) empty/back access; no copy, allocation, scan or I/O. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0006

[Lines 19–24](../../../../../src/recovery/sql_rows_sink_file.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L24:sha256:59fecbcfb5bc5f0fe7b427b46639c3722be4b13d2e6d355b274dba1e1e3e9aa6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit the actual row-sink header and seed its confirmed baseline prefix. |
| inputs / outputs | Complete typed inspected header plus its exact bytes in; baseline C/bytes/prefix hash out. |
| invariants | Header kind/ordinal/binding/sink identity must equal expected; no prior generation/I is inferred from a header-only prefix. |
| ownership | Copy fixed metadata/hash only; the actual owner retains file/provenance. |
| failure | Record-limit or binding mismatch rejects the unpublished factory state. |
| cost | Fixed copied prefix/hash charge; no native query, payload queue or scan. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0007

[Lines 25–26](../../../../../src/recovery/sql_rows_sink_file.cpp#L25); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L26:sha256:4f3de13c80019d97288f2ffab78b88eb23b8a8239d446a8538bc28a8830849f1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the adjacent reviewed ownership/barrier rule in this comment block. |
| inputs / outputs | No executable input/output; the nearby callable supplies the actual protocol. |
| invariants | The prose is guidance tied to the adjacent code and pinned bytes, not an independent correctness or delay proof. |
| ownership | No runtime object, borrow or FD is created by comments. |
| failure | No failure/repair behavior is installed by prose. |
| cost | No executable cost. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0008

[Lines 27–43](../../../../../src/recovery/sql_rows_sink_file.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L43:sha256:5a7e05eb84a7297379d3a85057c72d6e75238d74478233e55c6d87626bee6a68
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit and pre-fund the next row-sink epoch offset/fingerprint entry. |
| inputs / outputs | Validated row info/complete encoded bytes and current prefix in; fixed new Index out. |
| invariants | C must be previous+1, I strictly increases, generation never falls, record/byte caps admit the append. Header-only prefix has no previous epoch. |
| ownership | Reserve actual account-owned geometric index capacity before any write, retaining only offset/size/chained prefix metadata. |
| failure | Failed admission/allocation performs no I/O or fixed-index publication. |
| cost | Fixed chained SHA input plus admitted index growth; metadata count bounded by sink records and native array size. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0009

[Lines 44–44](../../../../../src/recovery/sql_rows_sink_file.cpp#L44); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L44-L44:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
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

## B0010

[Lines 45–45](../../../../../src/recovery/sql_rows_sink_file.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L45:sha256:d156043b06043e1b6aebc8a87cf4d9845a0e7fa72a2142feb8ce917094200bf5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt the already funded private SinkFile owner. |
| inputs / outputs | AccountedUnique&lt;Data&gt; -&gt; moved data_ member. |
| invariants | No file is opened, scanned or validated by this constructor. |
| ownership | Transfers sole Data ownership without copying program/file/buffer state. |
| failure | Declared noexcept. |
| cost | O(1) handle move; no allocation or syscall. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0011

[Lines 46–47](../../../../../src/recovery/sql_rows_sink_file.cpp#L46); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L46-L47:sha256:b01a936f7cb0692d804155cb2963b8cda470ed308453021562b941bf0df4c6e6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Default SinkFile destruction and noexcept move construction. |
| inputs / outputs | Declare default destructor and default move constructor. |
| invariants | Move transfers the unique Data; destructor releases existing members, including best-effort Io close, rather than recovering a file. |
| ownership | Actual Data/program/vector/FD teardown follows member RAII; no state copy is created by move. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0012

[Lines 48–51](../../../../../src/recovery/sql_rows_sink_file.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L51:sha256:ee4c2246d9147c2b4e05699371817c92eed6f381773d3d61b64d704747babe54
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an existing healthy SinkFile private owner. |
| inputs / outputs | This facade -&gt; Data& after data_ presence check and io.ready(). |
| invariants | Guard tests fd/poison state only, not current inode/EOF contents. |
| ownership | Reference borrows existing unique Data; no account/FD ownership change. |
| failure | FileFailure(state,state,unchanged) for empty owner; io.ready failure propagates. |
| cost | O(1) pointer/flag tests; no allocation or syscall. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0013

[Lines 52–52](../../../../../src/recovery/sql_rows_sink_file.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L52-L52:sha256:72ce4740ddb48dd64cbe06658ff0f637dccba1c59c396d23c5158c100adf009c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe whether SinkFile is absent, closed or poisoned. |
| inputs / outputs | This facade -&gt; !data_ \|\| io.fd&lt;0 \|\| io.poisoned. |
| invariants | Does not call data()/ready(), validate bytes or reopen a file. |
| ownership | Reads fixed pointer/fd/flag values only. |
| failure | noexcept; missing owner returns true. |
| cost | O(1) tests; no allocation or syscall. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0014

[Lines 53–55](../../../../../src/recovery/sql_rows_sink_file.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L53-L55:sha256:1e83e04d8395c58ec33a76fb055f1082767e0cf02029a20ff9e14e4c7c292cec
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy retained SinkFile transport state without rereading the file. |
| inputs / outputs | Healthy SinkFile -&gt; SinkFileState{header,latest(),index.size()+1,io.statistics(),io.torn}. |
| invariants | State describes retained validated prefix/counters; this getter neither establishes current EOF/stamp continuity nor native recovery authority. |
| ownership | Returns fixed-value copies; retains no file lock or payload backing. |
| failure | data() health guard propagates; no repair/reopen. |
| cost | O(1) fixed copies/index-end access; no allocation, scan or syscall. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0015

[Lines 56–59](../../../../../src/recovery/sql_rows_sink_file.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L56-L59:sha256:7e722b208090280938aa73ccbcd438db1c02db5f3e1f633b68548bb4da11ccf3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the retained sink prefix at one admitted absolute native sequence. |
| inputs / outputs | uint64 sequence in \[header.base_sequence,base+index.size()\] -&gt; baseline or matching index prefix. |
| invariants | Checks range using bounded subtraction before indexing; does not observe current file contents. |
| ownership | Returns fixed prefix values by copy; no borrowed payload escapes. |
| failure | data() health failure or ImageFailure(binding) for out-of-range sequence. |
| cost | O(1) arithmetic/index/fixed copy; no allocation or syscall. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0016

[Lines 60–63](../../../../../src/recovery/sql_rows_sink_file.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L60-L63:sha256:0a62a91957ce99c99d1cd4f7a1ae822854cd061b3eb513e175f29f5836c0c4d2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mint a fixed sink receipt from healthy untorn retained state. |
| inputs / outputs | This SinkFile -&gt; SinkReceipt copied from header and latest(). |
| invariants | data() checks owner health and an explicit torn flag rejects; this function performs no fresh stat, sync or file-byte comparison. |
| ownership | Receipt owns fixed header/prefix copies and retains no FD/lock. |
| failure | FileFailure(state,state,unchanged) for a torn owner; data() failures propagate. |
| cost | O(1) guard and fixed copies; no allocation, hash or syscall. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0017

[Lines 64–71](../../../../../src/recovery/sql_rows_sink_file.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L64-L71:sha256:06a005fd3b0cfab47dd9eb8e3a52421b01181e8fa713642eb8ac562f5a8187c0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a typed sink file from a genuine rows descriptor and fully funded header. |
| inputs / outputs | New path, receiving account, descriptor/header and finite FileLimits in; actual locked regular-file owner out. |
| invariants | Descriptor/header binding and row-family magic are checked; headers/schema/cursor/index metadata are admitted before inode publication. |
| ownership | The owner freezes genuine program metadata under the receiving account and shares the existing bounded Io engine. |
| failure | Any admission/creation failure follows actual file outcome and RAII FD/temp cleanup; existing entries are not silently replaced. |
| cost | Explicit header encoding/inspection and bounded durable create/link/sync; no native/source query or retained output queue. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0018

[Lines 72–91](../../../../../src/recovery/sql_rows_sink_file.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L72-L91:sha256:11a725dc95b468e80b35c4db6b383808034db83782ac2447ddec55150698f3cf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open and validate the real typed row sink prefix. |
| inputs / outputs | Path/genuine descriptor/expected header/finite scan grants in; locked complete-prefix owner and torn-tail observation out. |
| invariants | Authenticate lengths/magic/types/ordinals/bindings; maintain cumulative grants and actual EOF/stamps. Replay callbacks stay private until Session's whole barrier; lower open does not repair tails. |
| ownership | One receiving-account scratch buffer and bounded index/cursor state; release scan scratch before returning, retain no decoded command/payload graph. |
| failure | Any malformed/changed/limited file closes the incomplete owner. Typed replay mismatch aborts private construction; no complete corruption is truncated. |
| cost | Actual bounded sequential byte/codec/I/O work and index metadata; per-frame work cannot refill cumulative scan/file grants. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0019

[Lines 92–92](../../../../../src/recovery/sql_rows_sink_file.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L92-L92:sha256:22985a605889a5eeec3d76089439ff4c9ab914d6753de9065a2cf42c220b82e6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append or exactly confirm one typed row-sink epoch through the shared accept path. |
| inputs / outputs | Genuine immutable Frame and this healthy real sink in; true for newly synced bytes, false for identical already recorded bytes. |
| invariants | The concrete accept path validates typed row magic/schema/ordinal and complete byte identity; new append cannot proceed through a torn suffix; retry acknowledgment compares every byte. |
| ownership | Borrow Frame only during the call; the existing file owner retains locks/index/finite scratch. No payload queue, receipt DTO import or extra owner is constructed. |
| failure | Propagate exact accept admission/I/O/binding failure and its owner poison rules; no wrapper catch, automatic reopen or inferred durability outcome. |
| cost | Constant direct delegation plus the explicitly charged typed inspection, actual chunk comparison or append/sync work in accept; no new dispatch framework. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0020

[Lines 93–93](../../../../../src/recovery/sql_rows_sink_file.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L93-L93:sha256:e7676557fb078f1056ceb539d971b6ea382459483083612f254edc34137561ae
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify only an already confirmed actual row-sink epoch, without appending. |
| inputs / outputs | Genuine immutable Frame and this healthy real sink in; normal return only on exact existing bytes. |
| invariants | The concrete accept path validates typed row magic/schema/ordinal and complete byte identity; verify-only cannot append and may check the confirmed prefix through a torn suffix. |
| ownership | Borrow Frame only during the call; the existing file owner retains locks/index/finite scratch. No payload queue, receipt DTO import or extra owner is constructed. |
| failure | Propagate exact accept admission/I/O/binding failure and its owner poison rules; no wrapper catch, automatic reopen or inferred durability outcome. |
| cost | Constant direct delegation plus the explicitly charged typed inspection, actual chunk comparison or append/sync work in accept; no new dispatch framework. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0021

[Lines 94–123](../../../../../src/recovery/sql_rows_sink_file.cpp#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L94-L123:sha256:650dbbd6330a86d09013a04b8bcd14a35d97cf71e7918991331b4e3908c4988b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one new row epoch or verify every byte of an already recorded epoch before accepting retry. |
| inputs / outputs | Owned file plus genuine Frame and verify-only flag in; true only for a newly synced epoch, false for exact existing bytes. |
| invariants | Require row kind/absolute C/lineage and sequence continuity. Existing ordinal must match complete bytes and metadata, not only digest; verify-only never appends and may validate the prefix before a torn suffix. |
| ownership | Bounded scratch chunks and offset/fingerprint index belong to same account; reserve new fixed index entry before append. No output payload queue or second full comparison image. |
| failure | I/O uncertainty poisons until reopen; mismatched complete bytes reject without acknowledgment; new append through a torn tail rejects. |
| cost | Charged typed inspection, complete bounded-chunk comparison or write/sync and fixed index publication; no allocation after the prepared append boundary. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0022

[Lines 124–124](../../../../../src/recovery/sql_rows_sink_file.cpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L124-L124:sha256:79b6b1d07bd08148e59e50ca347af9a737ce1bc684cece7c93a7a61a3d068cd3
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

## B0023

[Lines 125–125](../../../../../src/recovery/sql_rows_sink_file.cpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L125-L125:sha256:e9e7f2be64a45342f62022ff2604d478bdc4d2f10b76582b7c14d66dfeeb61e2
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

## B0024

[Lines 126–129](../../../../../src/recovery/sql_rows_sink_file.cpp#L126); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L126-L129:sha256:5f8e846a75ab3896e8ce1deb24c06c7a01a749aa6c4e0f068f86887a16d2ebe5
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

## B0025

[Lines 130–130](../../../../../src/recovery/sql_rows_sink_file.cpp#L130); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L130-L130:sha256:5a88989d646de8c904ac4cbcd84db92dc85500003eb77614a29dedc10d8206dd
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
