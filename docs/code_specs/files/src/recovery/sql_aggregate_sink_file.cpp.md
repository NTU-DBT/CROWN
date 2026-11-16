# `src/recovery/sql_aggregate_sink_file.cpp` — block usage map

[Source](../../../../../src/recovery/sql_aggregate_sink_file.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `78a08f5a2c71d5740f2943ef1e04cee7de46bdb17a45dc7e6a6d3ef052135c50`. 130 lines partitioned into 25 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares types or opens a type body. |  · [reviewed contract](#b0001) |
| [B0002 · 8–8](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L8) | Type/record definition: struct Index |  · [reviewed contract](#b0002) |
| [B0003 · 9–14](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L9) | Member/declaration region. |  · [reviewed contract](#b0003) |
| [B0004 · 15–17](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L15) | Callable definition: Data(const resource::MemoryAccount& account,const Descriptor& descriptor,const SinkHeader& value,FileLimits limits) : io(limits),… | calls io, program, frontend::SqlAggregateProgram::freeze, header · [reviewed contract](#b0004) |
| [B0005 · 18–18](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L18) | Callable definition: \[\[nodiscard\]\] const SinkPrefix& latest() const noexcept | calls empty, back; returns index.empty()?baseline:index.back().prefix · [reviewed contract](#b0005) |
| [B0006 · 19–24](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L19) | Callable definition: void header_frame(std::string_view bytes,const Inspected& info) | calls require, consume, size, std::copy_n; guard require(io.limits.scan.records&gt;0,ImageFault::limit); · [reviewed contract](#b0006) |
| [B0007 · 25–26](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L25) | Explanatory comments or spacing. | source comment (unverified): // New epoch admission and index growth finish before any append I/O. A · [reviewed contract](#b0007) |
| [B0008 · 27–43](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L27) | Callable definition: \[\[nodiscard\]\] Index next(std::string_view bytes,const Inspected& info) | calls require, latest, size, consume; guard require(info.kind==Kind::group_epoch,ImageFault::binding);; returns result; growth reserve; source comment (unverified): // New epoch admission and index growth finish before any append I/O. A · [reviewed contract](#b0008) |
| [B0009 · 44–44](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L44) | Closes surrounding scope/type. |  · [reviewed contract](#b0009) |
| [B0010 · 45–45](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L45) | Callable definition: SinkFile::SinkFile(resource::AccountedUnique&lt;Data&gt; value) noexcept : data_(std::move(value)) | calls data_, std::move · [reviewed contract](#b0010) |
| [B0011 · 46–47](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L46) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0011) |
| [B0012 · 48–51](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L48) | Callable definition: SinkFile::Data& SinkFile::data() const | calls file_detail::fail, ready; returns *data_ · [reviewed contract](#b0012) |
| [B0013 · 52–52](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L52) | Callable definition: bool SinkFile::requires_reopen() const noexcept | calls ; returns !data_ \|\| data_-&gt;io.fd&lt;0 \|\| data_-&gt;io.poisoned · [reviewed contract](#b0013) |
| [B0014 · 53–55](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L53) | Callable definition: SinkFileState SinkFile::state() const | calls data, latest, size, statistics; returns {d.header,d.latest(),d.index.size()+1,d.io.statistics(),d.io.torn} · [reviewed contract](#b0014) |
| [B0015 · 56–59](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L56) | Callable definition: SinkPrefix SinkFile::prefix(std::uint64_t sequence) const | calls data, require, size; guard const auto& d=data();require(sequence&gt;=d.header.base_sequence && sequence-d.header.base_sequence&lt;=d…; returns sequence==d.header.base_sequence?d.baseline:d.index\[static_cast&lt;std::size_t&gt;(sequence-d.header.base… · [reviewed contract](#b0015) |
| [B0016 · 60–63](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L60) | Callable definition: SinkReceipt SinkFile::receipt() const | calls data, file_detail::fail, SinkReceipt, latest; returns SinkReceipt(d.header,d.latest()) · [reviewed contract](#b0016) |
| [B0017 · 64–71](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L64) | Callable definition: SinkFile SinkFile::create(const resource::MemoryAccount& account,std::string_view path, const Descriptor& descriptor,const SinkHe… | calls parsed, file_detail::binding, encode, record_limits; guard require(frame.bytes().size()&lt;=limits.scan.bytes,ImageFault::limit);owner-&gt;header_frame(frame.bytes(…; returns SinkFile(std::move(owner)); growth make_accounted_unique · [reviewed contract](#b0017) |
| [B0018 · 72–91](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L72) | Callable definition: SinkFile SinkFile::open(const resource::MemoryAccount& account,std::string_view path, const Descriptor& descriptor,const SinkHead… | calls parsed, file_detail::binding, open, require; guard require((offset==0?0:owner-&gt;index.size()+1)&lt;limits.scan.records,ImageFault::limit);; returns SinkFile(std::move(owner)); growth make_accounted_unique, push_back; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 92–92](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L92) | Callable definition: bool SinkFile::append(const Frame& frame) & | calls accept; returns accept(frame,false) · [reviewed contract](#b0019) |
| [B0020 · 93–93](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L93) | Callable definition: void SinkFile::verify(const Frame& frame) & | calls accept · [reviewed contract](#b0020) |
| [B0021 · 94–123](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L94) | Callable definition: bool SinkFile::accept(const Frame& frame,bool verify_only) | calls data, file_detail::fail, bytes, inspect; guard require(info.kind==Kind::group_epoch,ImageFault::binding);; returns false; true; growth push_back, resize; 1 loop sites; source comment (unverified): // Compare the whole real epoch in bounded chunks; no second owned output · [reviewed contract](#b0021) |
| [B0022 · 124–124](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L124) | Callable definition: void SinkFile::repair_tail() & | calls data, repair, latest · [reviewed contract](#b0022) |
| [B0023 · 125–125](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L125) | Callable definition: void SinkFile::validate() & | calls data, validate · [reviewed contract](#b0023) |
| [B0024 · 126–129](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L126) | Callable definition: void SinkFile::close() & | calls file_detail::fail, close · [reviewed contract](#b0024) |
| [B0025 · 130–130](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L130) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::recovery::sql_aggregate · [reviewed contract](#b0025) |

## B0001

[Lines 1–7](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SinkFile::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the actual sink identity, frozen receiving schema and bounded complete-epoch lookup metadata. |
| inputs / outputs | Account/Descriptor/SinkHeader/limits initialize Io, program, exact header, zero baseline, an empty Index vector and empty byte scratch. |
| invariants | Index holds only complete prefixes/offsets/sizes. A header-only baseline has C=declared base and generation/I zero after header_frame, not an earlier-epoch proof. No hot runtime field, native state or output queue is added. |
| ownership | Accounted Data owns one Io FD, genuine immutable program, funded Index capacity and reusable scratch; it never owns the caller output spool. |
| failure | Partial factory construction is released through AccountedUnique. Later main-path codec/account/file failures propagate without catch/retry/undo. |
| cost | Fixed metadata plus O(N) Index capacity for N complete epochs and O(min(duplicate bytes,chunk_bytes)) retained comparison scratch; open scratch can temporarily reach a complete frame. |
| Design | [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp), [src/recovery/sql_aggregate_file_detail.hpp](../../../../../src/recovery/sql_aggregate_file_detail.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0002

[Lines 8–8](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Index { SinkPrefix prefix;std::uint64_t offset,size; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Locate one complete sink epoch and preserve its cumulative prefix fingerprint without its payload. |
| inputs / outputs | A newly validated epoch yields a fixed Index containing resulting SinkPrefix and the old-prefix offset/new frame size. |
| invariants | Entry position maps to absolute C-base_sequence-1; offset/size always describe complete durable bytes before the entry becomes public. |
| ownership | The fixed entry is owned inline within the account-backed vector; Hash bytes are copied but no group row/text/output frame is retained. |
| failure | An entry alone is internal lookup metadata, not receipt/native authority; the vector publishes it only after open validation or successful append confirmation. |
| cost | Constant-size construction/copy and O(1) lookup; aggregate retained storage is O(number of complete epochs). |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [src/recovery/sql_aggregate_sink_file.cpp](../../../../../src/recovery/sql_aggregate_sink_file.cpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0003

[Lines 9–14](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L9); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
file_detail::Io io;
  frontend::SqlAggregateProgram program;
  SinkHeader header;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Separate private sink I/O/schema/identity/frontier metadata from payload scratch and per-epoch index ownership. |
| inputs / outputs | Io supplies limits/FD/stamps/counters; program supplies genuine schema; header/baseline/index/scratch form the sink-only retained state. |
| invariants | Header is immutable by use after construction, baseline generation/I stay zero, and only complete Index entries advance latest(). No field mirrors native group state or a pending output queue. |
| ownership | Program is receiving-account frozen metadata, index/scratch use image_allocator(account), and all fields die with the single Data owner. |
| failure | A failed append leaves Index unpublished and Io poisoned; cold account/freeze failures unwind storage before an owner returns. |
| cost | O(1) fixed fields plus account-funded geometric index capacity and bounded scratch; no per-runtime-update cost is introduced. |
| Design | [src/recovery/sql_aggregate_file_detail.hpp](../../../../../src/recovery/sql_aggregate_file_detail.hpp), [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0004

[Lines 15–17](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Data(const resource::MemoryAccount& account,const Descriptor& descriptor,const SinkHeader& value,FileLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct sink-only retained resources under the actual receiving account and genuine descriptor schema. |
| inputs / outputs | Account, Descriptor, expected SinkHeader and limits enter; Io/program/header/index/scratch are initialized without opening a file. |
| invariants | Factories perform descriptor hash binding before this call; program freezes the actual descriptor.program(), preserving immutable schema identity rather than importing editable DTO claims. |
| ownership | Same-account genuine program metadata can share; cross-account freeze funds a copy. Index and scratch retain account-aware allocators and header is a fixed copy. |
| failure | Memory/metadata failures propagate; the accounted unique factory deallocates partially constructed Data and no FD is acquired here. |
| cost | Cold schema share or metadata-sized freeze plus constant empty-vector/header construction; no codec/file work is charged by the constructor. |
| Design | [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp), [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0005

[Lines 18–18](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] const SinkPrefix& latest() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the last complete sink frontier without retaining another copy of every prefix. |
| inputs / outputs | Const Data enters; a reference to baseline is returned when the index is empty, otherwise to index.back().prefix. |
| invariants | A torn suffix never enters index, so latest always describes a complete admitted prefix; header-only generation/I zero remain distinguishable. |
| ownership | The reference borrows Data/vector storage and is valid only while that storage remains live and unchanged. |
| failure | The helper is noexcept and assumes Data header initialization has already occurred when a meaningful prefix is requested. |
| cost | O(1) empty/back selection, no allocation, hashing or syscall. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [src/recovery/sql_aggregate_sink_file.cpp](../../../../../src/recovery/sql_aggregate_sink_file.cpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0006

[Lines 19–24](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void header_frame(std::string_view bytes,const Inspected& info) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit the actual sink header and initialize the selected file baseline fingerprint. |
| inputs / outputs | Complete validated header bytes and Inspected metadata enter; baseline receives base C, header byte size and the64 protected-prefix checksum bytes. |
| invariants | scan.records must admit a header; kind/ordinal must be sink_header/0 and full SinkHeader must equal expected. Baseline generation/input remain0 and contain no evidence of epochs before base C. |
| ownership | The fixed header was already copied into Data; borrowed frame bytes are not retained beyond checksum copy. |
| failure | Wrong header/type/ordinal fails binding; insufficient records or64 additional work fails before a file is created/published. |
| cost | One exact fixed-header comparison,64-byte checksum copy and explicit64 work charge; no vector growth or I/O. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0007

[Lines 25–26](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L25); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L26:sha256:4f3de13c80019d97288f2ffab78b88eb23b8a8239d446a8538bc28a8830849f1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: New epoch admission and index growth finish before any append I/O. A header-only baseline contains no prior generation or command observation. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/recovery/sql_aggregate_sink_file.cpp lines 23-28; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/recovery/sql_aggregate_sink_file.cpp](../../../../../src/recovery/sql_aggregate_sink_file.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_sink_file.cpp.md](sql_aggregate_sink_file.cpp.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0008

[Lines 27–43](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Index next(std::string_view bytes,const Inspected& info) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prevalidate and fund a new complete epoch index entry before sink append I/O. |
| inputs / outputs | Actual complete frame bytes and successfully inspected group metadata enter; a fixed candidate Index returns without inserting it. |
| invariants | Kind is group_epoch; absolute C and ordinal equal prior C+1 without wrap, I strictly increases, generation never decreases. Remaining scan record/file-byte bounds are checked with header already admitted. |
| ownership | Candidate is fixed stack metadata; vector capacity is geometrically reserved in the receiving account before mutation. No caller output bytes become owned by Data. |
| failure | Order/binding/limit/work/account failures occur before append I/O. The explicit256 chain work can stay charged if later reserve or write fails; no index entry publishes on failure. |
| cost | 128 copied plus128 hashed bytes cost256 logical work, and occasional O(N) geometric reserve moves fixed entries; amortized O(1) metadata work per admitted epoch and O(N) retained index. |
| Design | [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0009

[Lines 44–44](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L44); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L44-L44:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the enclosing helper type at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/sql_aggregate_sink_file.cpp](../../../../../src/recovery/sql_aggregate_sink_file.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_sink_file.cpp.md](sql_aggregate_sink_file.cpp.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0010

[Lines 45–45](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SinkFile::SinkFile(resource::AccountedUnique<Data> value) noexcept : data_(std::move(value)) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer confirmed private sink storage into the public move-only handle. |
| inputs / outputs | An AccountedUnique&lt;Data&gt; value enters; data_ takes its owner/deleter without any new file or vector work. |
| invariants | Factories call this only after Io create/finish_open has completed, so constructor publication cannot fail midway. |
| ownership | The account-bound Data owner moves once and the temporary unique argument becomes empty. |
| failure | The private constructor is noexcept and performs no validation or durability claim beyond receiving already confirmed Data. |
| cost | O(1) unique pointer/deleter transfer, with no allocation/output-byte copy/syscall. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [src/recovery/sql_aggregate_sink_file.cpp](../../../../../src/recovery/sql_aggregate_sink_file.cpp) |

## B0011

[Lines 46–47](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L46); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SinkFile::~SinkFile()=default;
SinkFile::SinkFile(SinkFile&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define sink destruction and unique-owner movement with complete private Data available. |
| inputs / outputs | Destruction deletes Data; move transfers it without copying the index, program or FD. |
| invariants | The moved-from handle is empty and no second advisory-lock owner is created by C++ copying. |
| ownership | The final owner releases account-funded index/scratch/schema and its Io file FD; transfer preserves their existing account identities. |
| failure | Best-effort destructor close ignores failures; explicit close provides checked consumption, while the noexcept move itself cannot fail. |
| cost | Constant move; destruction releases actual retained O(index capacity+schema+scratch) storage and at most one raw close. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp) |

## B0012

[Lines 48–51](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SinkFile::Data& SinkFile::data() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Gate internal sink access on live unique storage and a healthy file engine. |
| inputs / outputs | A const public handle returns mutable Data only after data_ exists and io.ready() accepts it. |
| invariants | Poisoned/closed/moved-from owners cannot expose state, prefixes or receipts; a merely torn suffix still allows complete-prefix observation/verify. |
| ownership | The returned reference is internal borrowed access, not a new owner or externally mutable DTO. |
| failure | Missing storage or failed ready throws fixed FileFailure(state); no check clears the uncertainty latch. |
| cost | O(1) pointer/flag inspection without syscall, index scan or allocation. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [src/recovery/sql_aggregate_sink_file.cpp](../../../../../src/recovery/sql_aggregate_sink_file.cpp) |

## B0013

[Lines 52–52](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool SinkFile::requires_reopen() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report sink-owner usability even after its ordinary operations have been poisoned. |
| inputs / outputs | Implicit handle state returns true for no Data, fd&lt;0 or poison; false otherwise. |
| invariants | The torn bit is deliberately separate: an incomplete suffix forbids new append/receipt but can retain healthy complete-prefix verification. |
| ownership | Only existing pointer/FD/flag values are read, with no lock transfer or snapshot authority minted. |
| failure | The predicate is noexcept and does not call the throwing data() accessor. |
| cost | Constant three-part state check, no I/O or work-counter expenditure. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0014

[Lines 53–55](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SinkFileState SinkFile::state() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the actual sink complete frontier and current transport accounting from a healthy owner. |
| inputs / outputs | A gated Data view supplies header, latest prefix, index.size()+1 records, statistics and torn flag by value. |
| invariants | Header counts as one record and a torn suffix adds no record/index entry. Latest can be the selected header baseline with generation/I0. |
| ownership | The result owns fixed copies while index/scratch/program/FD remain private to Data. |
| failure | Closed/empty/poisoned access fails through data(); the copy is transport observation rather than native replay or current-root authority. |
| cost | O(1) vector-size/latest selection and fixed DTO copies, no byte comparison or syscall. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0015

[Lines 56–59](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SinkPrefix SinkFile::prefix(std::uint64_t sequence) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retrieve an exact complete prefix by absolute physical sequence even when the file starts above zero. |
| inputs / outputs | A healthy owner and uint64_t C enter; C=base returns baseline, otherwise direct index\[C-base-1\].prefix is copied. |
| invariants | C&gt;=base and C-base&lt;=index.size are checked before indexing, preventing underflow or a prefix beyond the admitted complete frontier. |
| ownership | The caller receives only a fixed SinkPrefix copy; it gains no receipt privilege, vector reference or file lock. |
| failure | Out-of-range C throws ImageFailure(binding); unhealthy owner throws FileFailure(state). A baseline prefix does not prove earlier epochs. |
| cost | O(1) guarded absolute-C arithmetic, lookup and fixed copy, with no allocation or I/O. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0016

[Lines 60–63](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SinkReceipt SinkFile::receipt() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mint an immutable actual-sink observation only when the current complete file has no admitted torn suffix. |
| inputs / outputs | A healthy Data owner supplies its exact header/latest prefix to the private SinkReceipt constructor. |
| invariants | Torn state is rejected in addition to data() health gating; only SinkFile friendship can call the receipt constructor, so editable root/checkpoint DTOs cannot mint one. |
| ownership | The receipt owns const copies and retains neither the FD/lock nor a live current-owner pointer. |
| failure | Empty/closed/poisoned/torn owner throws FileFailure(state). A later coordinator must still match current owner/selected identity, C, bytes and fingerprint. |
| cost | O(1) flags plus fixed metadata copies; no hashing, allocation or file operation. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [include/crown/recovery/sql_aggregate_checkpoint.hpp](../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp) |

## B0017

[Lines 64–71](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SinkFile SinkFile::create(const resource::MemoryAccount& account,std::string_view path,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a new locked sink with a fully validated and pre-funded header baseline. |
| inputs / outputs | Receiving account/path/genuine Descriptor/expected SinkHeader/limits enter; a confirmed SinkFile returns after Io no-replace creation. |
| invariants | Path/hash admission precede actual-schema freeze; encoded header work and header_frame64 work share the remaining file work grant. Header bytes must fit full-file scan.bytes before I/O. |
| ownership | Accounted Data owns schema/empty vectors/FD; one temporary account-owned encoded Frame is released after installation, leaving no payload queue. |
| failure | Path/descriptor/codec/header/budget/account failures occur before inode mutation; file failures propagate exact outcome/cleanup metadata and release provisional ownership. |
| cost | Cold schema share/freeze and fixed-header codec/fingerprint work, then bounded chunked write/fsync/link/unlink/directory sync/final stat. |
| Design | [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp), [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0018

[Lines 72–91](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SinkFile SinkFile::open(const resource::MemoryAccount& account,std::string_view path,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Scan and confirm a complete actual sink prefix, admitting only a possible incomplete final epoch. |
| inputs / outputs | Account/path/genuine Descriptor/exact expected SinkHeader/limits enter; a locked owner with complete per-epoch index returns after EOF/stamp/file-directory sync checks. |
| invariants | Each complete record is inspected under actual frozen schema. Header must match exactly; group ordinals equal absolute C, C is contiguous from base, I rises and generation does not fall. Terminal record/I/C limits forbid further tails. |
| ownership | Provisional Data owns account-backed scan scratch/index; no epoch payload queue is kept. Whole scan scratch is swapped free before the owner is returned. |
| failure | Complete corruption, wrong header/order, impossible tail, allocation or file confirmation failure aborts open without truncation. A valid torn suffix remains for separately authorized repair. |
| cost | O(admitted file bytes) codec/prefix work plus O(N) geometric index storage; peak complete-frame scratch during open; incomplete-body size at most157, with any prior capacity and all scan scratch released before return. |
| Design | [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0019

[Lines 92–92](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool SinkFile::append(const Frame& frame) & {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invoke common sink acceptance with permission to publish one new complete epoch. |
| inputs / outputs | An lvalue sink and borrowed immutable Frame enter; accept(frame,false) returns true for new durable delivery or false for complete-byte duplicate equality. |
| invariants | The wrapper cannot bypass torn-state rejection, actual-byte inspection, index prepayment or I/O latching in accept. |
| ownership | Frame ownership remains with the caller and no wrapper-local buffer is created. |
| failure | All ImageFailure, account and FileFailure results propagate directly, with no catch or retry. |
| cost | O(1) wrapper overhead plus accept actual validation/comparison or append cost. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [src/recovery/sql_aggregate_sink_file.cpp](../../../../../src/recovery/sql_aggregate_sink_file.cpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0020

[Lines 93–93](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void SinkFile::verify(const Frame& frame) & {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invoke the same exact-byte path while forbidding delivery of a previously absent epoch. |
| inputs / outputs | An lvalue sink and live Frame enter; accept(frame,true) performs existing-prefix validation and its Boolean is intentionally discarded. |
| invariants | A validated torn suffix is allowed for prior-entry comparison, but verify_only rejects any requested C after the complete index. |
| ownership | The caller retains output bytes and Data supplies only bounded read scratch; no new Index entry or output owner is produced. |
| failure | Mismatch, absent epoch, invalid Frame or read/stamp failure propagates; I/O failure preserves the poison latch. |
| cost | Constant wrapper work plus O(frame bytes) inspection/full-byte comparison, with no write or fsync of a new epoch. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [src/recovery/sql_aggregate_sink_file.cpp](../../../../../src/recovery/sql_aggregate_sink_file.cpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0021

[Lines 94–123](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool SinkFile::accept(const Frame& frame,bool verify_only) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish actual-byte duplicate confirmation from pre-funded new epoch delivery under one sink uncertainty policy. |
| inputs / outputs | A borrowed live Frame and verify_only flag enter; inspected group metadata maps absolute C to a prior entry or validates one successor. False means complete existing bytes matched; true means one new epoch synced and indexed. |
| invariants | Actual bytes, not Frame::info(), are inspected under frozen schema and successful codec work is consumed. Existing entries require length/generation/I agreement and every encoded byte is read/compared in chunks with stamps before/after; digest-only equality never suffices. |
| ownership | Duplicate scratch is account-funded to min(entry bytes,chunk_bytes) and comparison2*bytes is prepaid before I/O. New path computes/reserves one fixed Index first; caller keeps its sole output spool and publication pushes only that reserved entry. |
| failure | Torn append, invalid/missing verify epoch or metadata mismatch fails before mutation. Duplicate read/stamp and new append I/O latch poison before first stamp check; complete byte mismatch clears poison after a healthy full comparison, then throws binding. New index publishes only after fsync/final stat. |
| cost | O(B) codec plus full duplicate read/comparison with explicit2B charge, or O(B) write plus256 chain work and amortized O(1) index growth. Scratch&lt;=chunk_bytes; no second full output frame, catch, native work or output queue. |
| Design | [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0022

[Lines 124–124](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void SinkFile::repair_tail() & {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Truncate only after the final complete sink prefix, using the low-level caller-authorized repair primitive. |
| inputs / outputs | A healthy owner passes latest().bytes to Io::repair; all selected-root/native replay/output-equality/sink-coverage/EOF/stamp checks must already have succeeded in its receiving session. |
| invariants | No complete header/epoch is discarded and the method does not itself enforce the semantic precondition or attest earlier epochs before a header base. |
| ownership | Only the existing locked file is mutated; index/header/schema stay fixed and no native state or epoch payload is retained. |
| failure | Untorn state is a no-op; Io repair errors propagate directly and uncertain mutation requires fresh open. |
| cost | O(1) last-prefix selection plus bounded truncate/fsync/stat calls, with no index walk or full replay. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0023

[Lines 125–125](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void SinkFile::validate() &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply the existing held-file validation barrier to the private SinkFile receiver. |
| inputs / outputs | Friend Session calls a healthy live owner; data() checks ownership before delegating to Io::validate. |
| invariants | Validation neither advances transport/native frontiers nor repairs a suffix. A poisoned file cannot manufacture a healthy observation. |
| ownership | Borrows the existing private Io/FD; no extra frame, schema or lock owner. |
| failure | State/I/O failures propagate directly; Io retains poison after any admitted validation uncertainty. |
| cost | Fixed wrapper work plus the three-call Io stamp/EOF barrier; no allocation. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [src/recovery/sql_aggregate_sink_file.cpp](../../../../../src/recovery/sql_aggregate_sink_file.cpp) |

## B0024

[Lines 126–129](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L126); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void SinkFile::close() & {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | End the sink FD lifetime through the checked path even after other operations have become unavailable. |
| inputs / outputs | A nonempty Data handle forwards directly to io.close and returns void on the one successful checked consumption. |
| invariants | It avoids data()/ready solely so poison cannot prevent resource disposal; the stored FD is removed before checked close. |
| ownership | Data still owns account metadata/index/scratch until destruction, but it no longer owns a live FD or lock after the attempt. |
| failure | Empty/moved handle fails state; already-closed/quota/close failures follow Io close semantics and are never retried by this wrapper. |
| cost | Constant handle check and close dispatch, without allocation, output validation or native update work. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../src/recovery/sql_aggregate_file_detail.cpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0025

[Lines 130–130](../../../../../src/recovery/sql_aggregate_sink_file.cpp#L130); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L130-L130:sha256:92582b45ad46706cdfae3684126917692713a5a92eff88bf2e3bcc42f5a8da44
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::recovery::sql_aggregate at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/sql_aggregate_sink_file.cpp](../../../../../src/recovery/sql_aggregate_sink_file.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_sink_file.cpp.md](sql_aggregate_sink_file.cpp.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |
