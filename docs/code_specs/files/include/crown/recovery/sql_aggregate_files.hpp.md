# `include/crown/recovery/sql_aggregate_files.hpp` — block usage map

[Source](../../../../../../include/crown/recovery/sql_aggregate_files.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `a102bb1b419f978fd4039fd96abd77615e937922d1f51d0574fdd38d0773d702`. 148 lines partitioned into 17 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../../checkpoints.md), [docs/journal.md](../../../../../journal.md), [docs/journal-files.md](../../../../../journal-files.md), [docs/generations.md](../../../../../generations.md), [docs/local-sink.md](../../../../../local-sink.md), [docs/history-retirement.md](../../../../../history-retirement.md), [docs/update_patterns.md](../../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Concrete Linux regular files for CROWNAG2. One owner holds an advisory flock; · [reviewed contract](#b0001) |
| [B0002 · 10–14](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L10) | Type/record definition: enum class FileStage : std::uint8_t | source comment (unverified): // Concrete Linux regular files for CROWNAG2. One owner holds an advisory flock; · [reviewed contract](#b0002) |
| [B0003 · 15–15](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L15) | Type/record definition: enum class FileFault : std::uint8_t |  · [reviewed contract](#b0003) |
| [B0004 · 16–16](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L16) | Type/record definition: enum class FileOutcome : std::uint8_t |  · [reviewed contract](#b0004) |
| [B0005 · 17–19](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L17) | Explanatory comments or spacing. | source comment (unverified): // Fixed failure metadata requires no allocation. An unknown outcome may have · [reviewed contract](#b0005) |
| [B0006 · 20–32](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L20) | Type/record definition: class FileFailure final : public std::exception | returns fault_; stage_; source comment (unverified): // Fixed failure metadata requires no allocation. An unknown outcome may have · [reviewed contract](#b0006) |
| [B0007 · 33–37](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L33) | Type/record definition: struct FileLimits |  · [reviewed contract](#b0007) |
| [B0008 · 38–42](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L38) | Explanatory comments or spacing. | source comment (unverified): // Operations counts attempts routed through the bounded dispatcher; best-effort · [reviewed contract](#b0008) |
| [B0009 · 43–43](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L43) | Type/record definition: struct FileStatistics | source comment (unverified): // Operations counts attempts routed through the bounded dispatcher; best-effort · [reviewed contract](#b0009) |
| [B0010 · 44–48](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L44) | Type/record definition: struct WalFileState | source comment (unverified): // Confirmed transport frontiers, not native replay authority. · [reviewed contract](#b0010) |
| [B0011 · 49–83](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L49) | declares aliases; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // No retained command copy: append borrows an immutable pre-funded Frame for · [reviewed contract](#b0011) |
| [B0012 · 84–86](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L84) | Explanatory comments or spacing. | source comment (unverified): // A chained fingerprint of a complete sink prefix, not the raw file SHA256. · [reviewed contract](#b0012) |
| [B0013 · 87–91](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L87) | Type/record definition: struct SinkPrefix | source comment (unverified): // A chained fingerprint of a complete sink prefix, not the raw file SHA256. · [reviewed contract](#b0013) |
| [B0014 · 92–98](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L92) | Type/record definition: struct SinkFileState |  · [reviewed contract](#b0014) |
| [B0015 · 99–101](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L99) | Explanatory comments or spacing. | source comment (unverified): // Only a healthy, untorn actual SinkFile mints this evidence. Copies preserve · [reviewed contract](#b0015) |
| [B0016 · 102–115](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L102) | Type/record definition: class SinkReceipt | returns header_; prefix_; source comment (unverified): // Only a healthy, untorn actual SinkFile mints this evidence. Copies preserve · [reviewed contract](#b0016) |
| [B0017 · 116–148](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L116) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // One bounded offset/fingerprint entry per complete epoch; no retained output · [reviewed contract](#b0017) |

## B0001

[Lines 1–9](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:2440aa10f10423c8793edec96e5ffa32bb9091703165feb46806d0162e6c2b94
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Header guard and descriptor/account-owner dependencies, then crown::recovery::sql_aggregate scope for Linux file fault, limits, receipt, and file-owner declarations. Embedded source note records intended usage: Concrete Linux regular files for CROWNAG2. One owner holds an advisory flock; the containing namespace and other writers must cooperate. See docs/sql_aggregate_files.md for the separate native-replay/repair barrier. Treat that prose as guidance, not as independently verified executable behavior. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The header guard prevents repeat inclusion in a translation unit; imported declarations determine compile-time names. The note/type comments in this span are guidance and do not add runtime validation or a capability. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path is introduced by the guard/imports; incompatible or missing declarations fail during compilation or linking. |
| cost | Preprocessor/compiler work only for these lines; the guard adds no per-operation runtime work. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../../include/crown/recovery/sql_aggregate_files.hpp), [docs/code_specs/files/include/crown/recovery/sql_aggregate_files.hpp.md](sql_aggregate_files.hpp.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [docs/sql_aggregate_session.md](../../../../../sql_aggregate_session.md) |

## B0002

[Lines 10–14](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class FileStage : std::uint8_t {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the bounded file-operation stage carried by a fixed FileFailure and by the private syscall dispatcher. |
| inputs / outputs | A stage value identifies path/state admission or one Linux operation; callers observe it through FileFailure::stage(). |
| invariants | The enumerators distinguish temporary creation/publication, data transfer, file/directory sync, truncation and checked close; path and state are not syscall cases. |
| ownership | The uint8_t value owns no descriptor, pathname or runtime object. |
| failure | Selecting path/state in Io::call is a state failure; the enum itself neither throws nor conveys native commit authority. |
| cost | One fixed-width discriminator, with constant copy and comparison cost. |
| Design | [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [src/recovery/sql_aggregate_file_detail.hpp](../../../../../../src/recovery/sql_aggregate_file_detail.hpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../../src/recovery/sql_aggregate_file_detail.cpp) |

## B0003

[Lines 15–15](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class FileFault : std::uint8_t {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify local file failures independently of their stage and observed durability. |
| inputs / outputs | The fixed fault tag accompanies stage/outcome/native-error metadata and is returned unchanged by FileFailure::fault(). |
| invariants | I/O, admission, path, nonregular, busy-lock, changed-file, premature-EOF and owner-state failures remain distinguishable; wire/schema errors use ImageFailure instead. |
| ownership | The tag retains no exception string, inode or account allocation. |
| failure | A FileFault reports a failed file boundary; it cannot authorize retry, semantic rejection or native publication. |
| cost | Constant storage and branching; it does not count bytes or work. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../../include/crown/recovery/sql_aggregate_files.hpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../../src/recovery/sql_aggregate_file_detail.cpp), [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp) |

## B0004

[Lines 16–16](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class FileOutcome : std::uint8_t {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record the file operation outcome known at the point of a file failure. |
| inputs / outputs | unchanged, unknown or durable enters FileFailure; callers inspect outcome() before disposing of or reopening the owner. |
| invariants | Mutation attempts conservatively move to unknown, successful fsync can move to durable, and a later failure may still poison the owner. |
| ownership | Outcome is fixed observation metadata and holds neither a lock nor a native transaction. |
| failure | Even durable does not make a failed owner reusable; unknown may describe bytes or a name already reaching disk. |
| cost | One scalar transition per relevant operation, with no allocation or filesystem work by the enum. |
| Design | [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../../src/recovery/sql_aggregate_file_detail.cpp), [src/recovery/sql_aggregate_wal_file.cpp](../../../../../../src/recovery/sql_aggregate_wal_file.cpp), [src/recovery/sql_aggregate_sink_file.cpp](../../../../../../src/recovery/sql_aggregate_sink_file.cpp) |

## B0005

[Lines 17–19](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L17); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L19:sha256:a23e6167878c8c570ff7773e3ddc2e7679bcfbcab96edc43f5c2d37b665cd273
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Fixed failure metadata requires no allocation. An unknown outcome may have reached disk; an append/repair I/O failure requires a fresh owner, even if fsync succeeded and only the following stat failed. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/recovery/sql_aggregate_files.hpp lines 15-21; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../../include/crown/recovery/sql_aggregate_files.hpp), [docs/code_specs/files/include/crown/recovery/sql_aggregate_files.hpp.md](sql_aggregate_files.hpp.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [docs/sql_aggregate_session.md](../../../../../sql_aggregate_session.md) |

## B0006

[Lines 20–32](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L20); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class FileFailure final : public std::exception {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry file fault, stage, outcome, errno and temporary-cleanup status without allocating diagnostic storage. |
| inputs / outputs | Construction stores the five supplied values; noexcept getters and what() return those observations or the fixed literal. |
| invariants | The object preserves its original fixed metadata; cleanup_ reports bounded temporary-name cleanup failure separately from the primary failure. |
| ownership | All fields and the diagnostic literal are self-contained; no borrowed pathname, Descriptor, Frame or FD survives in the carrier. |
| failure | Constructors/accessors are noexcept; the thrown carrier alone does not distinguish surviving file contents, which a new owner must validate. |
| cost | Fixed-size copy/throw payload and constant accessor cost; no formatting, heap allocation or syscall occurs inside the class. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../../include/crown/recovery/sql_aggregate_files.hpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../../src/recovery/sql_aggregate_file_detail.cpp), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md) |

## B0007

[Lines 33–37](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L33); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FileLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bundle finite receiving scan grants with fixed pathname, transfer-chunk and syscall-attempt admissions. |
| inputs / outputs | Factories receive the value by copy; scan bounds frame/file work, bytes and records, while path_bytes, chunk_bytes and operations govern local I/O. |
| invariants | Path admission requires path_bytes below 4096, nonzero chunk/operations, chunk within ssize_t, record bytes at least 157 and file bytes representable by off_t. |
| ownership | The limits object contains policy values only; passing it creates no new MemoryAccount and does not rewrite descriptor runtime policy. |
| failure | Invalid I/O sizing policy fails as FileFailure at path; later byte/record/codec-work violations may use ImageFailure. |
| cost | Constant-size cold policy copy; the limits bound logical counters and allocation extents, not native replay or wall-clock CPU. |
| Design | [src/recovery/sql_aggregate_file_detail.cpp](../../../../../../src/recovery/sql_aggregate_file_detail.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [docs/sql_aggregate_descriptor.md](../../../../../sql_aggregate_descriptor.md) |

## B0008

[Lines 38–42](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L38); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L42:sha256:ae626112bb7cc32802f9474d72ebfe6ce4d6623bc32b19b67c394e8b7c3260b9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Operations counts attempts routed through the bounded dispatcher; best-effort raw close is outside it. Work charges explicit codec/prefix/chain/comparison checkpoints. Failed inspect/WAL feed returns no codec work; earlier prefix or successful sink-inspect charges remain if later admission fails. Cold metadata copying, native replay and wall-clock CPU are outside this logical counter. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/recovery/sql_aggregate_files.hpp lines 36-44; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../../include/crown/recovery/sql_aggregate_files.hpp), [docs/code_specs/files/include/crown/recovery/sql_aggregate_files.hpp.md](sql_aggregate_files.hpp.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [docs/sql_aggregate_session.md](../../../../../sql_aggregate_session.md) |

## B0009

[Lines 43–43](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L43); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FileStatistics {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose metered syscall attempts and charged logical file work as distinct counters. |
| inputs / outputs | Io::statistics() returns operations/work by value; WalFileState and SinkFileState carry that copy to a healthy-owner caller. |
| invariants | Io::call attempts, including EINTR and emergency cleanup, increment operations. Work includes successful returned codec work plus explicit prefix/hash/duplicate charges; failing codec validations and failed WalCursor transitions return no charge to the file. |
| ownership | The two counters own no history, retained frames or resource grant; raw best-effort destructor/limit-fallback closes bypass the metered dispatcher. |
| failure | A successful codec call can be charged before later file admission/I/O fails; the statistic is not all failed-validation CPU, cold metadata-copy cost or a retry allowance proof. |
| cost | Two uint64_t values; counter reads are O(1), and measured units are logical visits/attempts rather than elapsed time. |
| Design | [src/recovery/sql_aggregate_file_detail.cpp](../../../../../../src/recovery/sql_aggregate_file_detail.cpp), [src/recovery/sql_aggregate_wal_file.cpp](../../../../../../src/recovery/sql_aggregate_wal_file.cpp), [src/recovery/sql_aggregate_sink_file.cpp](../../../../../../src/recovery/sql_aggregate_sink_file.cpp), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md) |

## B0010

[Lines 44–48](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L44); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WalFileState {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the confirmed WAL transport frontier alongside file accounting and an admitted incomplete-tail flag. |
| inputs / outputs | WalFile::state() copies the cursor WalState, Io statistics and torn bit into this value. |
| invariants | wal.work remains codec-only cumulative accepted-feed work; statistics.work also includes file prefix charges. A torn tail lies after wal.bytes and never becomes a complete accepted record. |
| ownership | This DTO contains fixed cursor/pending identity metadata, not pending command bytes, a file lock or native runtime state. |
| failure | The DTO can be obtained only through a healthy owner getter; an editable copy grants no replay, sink-coverage or tail-repair authority. |
| cost | Fixed-size value copy with no file read or native replay. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_wal.cpp](../../../../../../src/recovery/sql_aggregate_wal.cpp), [src/recovery/sql_aggregate_wal_file.cpp](../../../../../../src/recovery/sql_aggregate_wal_file.cpp), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md) |

## B0011

[Lines 49–83](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L49); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class WalFile {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one locked Linux WAL file and its genuine receiving schema, validating durable transport progress. |
| inputs / outputs | Factories bind a Descriptor and WalHeader to an actual path; append borrows a Frame; state reports confirmed frontiers and requires_reopen reports unusability. |
| invariants | One owner holds the advisory lock. Input/decision order follows WalCursor; successful append publishes a fixed candidate only after write/fsync/final stat. The containing namespace and other writers must cooperate. |
| ownership | Move-only AccountedUnique&lt;Data&gt; owns FD, frozen schema and scan scratch; it retains no extra command frame, native execution token, undo record or output queue. |
| failure | Wire/order/admission failures propagate; any append I/O failure poisons getters until a fresh open. The class does not enforce the caller semantic barrier required before repair_tail(). |
| cost | Transport validation is linear in frame/scan codec work under finite grants; retained steady WAL metadata is fixed beyond genuine schema and opening scratch. |
| Design | [src/recovery/sql_aggregate_wal_file.cpp](../../../../../../src/recovery/sql_aggregate_wal_file.cpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../../src/recovery/sql_aggregate_file_detail.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md) |

```text
[[nodiscard]] static WalFile create(const resource::MemoryAccount&,std::string_view,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare creation/open factories requiring the genuine descriptor and exact expected WAL header. |
| inputs / outputs | Receiving account, borrowed path, Descriptor, WalHeader and FileLimits enter; a move-only locked WalFile leaves only after all file validation and confirmation. |
| invariants | Descriptor hash equality is paired with freezing descriptor.program(); neither a matching header hash alone nor an edited schema DTO authorizes interpretation. |
| ownership | Arguments are borrowed during the call; returned Data retains receiving-account ownership and immutable program metadata independently of caller handles. |
| failure | Create preserves existing destinations; open refuses a leaf symlink, nonregular inode, busy lock or corrupt file. Incomplete provisional owners are released when factory work throws. |
| cost | Cold metadata freeze plus header encoding or a bounded full-file scan; syscall attempts and successful codec work spend separate cumulative file grants. |
| Design | [src/recovery/sql_aggregate_wal_file.cpp](../../../../../../src/recovery/sql_aggregate_wal_file.cpp), [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [src/frontend/sql_aggregate.cpp](../../../../../../src/frontend/sql_aggregate.cpp), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md) |

```text
~WalFile();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare unique WAL lifetime and move transfer without copying a locked owner. |
| inputs / outputs | Destruction releases Data; move construction transfers it; copy and both assignments are deleted. |
| invariants | A moved-from handle is empty and reports requires_reopen; the one Data owner controls the one FD lifetime. |
| ownership | The destination move owns the same account-funded Data and metadata; destruction invokes best-effort close through Io rather than publishing a replacement owner. |
| failure | Move/destruction do not report checked-close errors; callers needing a close result must call close() before lifetime ends. |
| cost | Move is constant pointer/deleter transfer; destruction releases schema/scratch and attempts at most one raw close for its live FD. |
| Design | [src/recovery/sql_aggregate_wal_file.cpp](../../../../../../src/recovery/sql_aggregate_wal_file.cpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../../src/recovery/sql_aggregate_file_detail.cpp), [include/crown/resource/ownership.hpp](../../../../../../include/crown/resource/ownership.hpp) |

```text
[[nodiscard]] WalFileState state() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare healthy WAL state observation and a separate noexcept reopen predicate. |
| inputs / outputs | state() returns a value snapshot; requires_reopen() answers whether the handle is empty, closed or poisoned. |
| invariants | state() never exposes provisional append candidate state; requires_reopen() can be queried even on a failed or moved-from owner. |
| ownership | Observations borrow the live Data only for the call and transfer no lock or mutable cursor reference. |
| failure | state() rejects empty, closed and poisoned owners with FileFailure(state); requires_reopen() itself cannot throw. |
| cost | Constant fixed-state/counter access, with no syscall, frame parse or allocation. |
| Design | [src/recovery/sql_aggregate_wal_file.cpp](../../../../../../src/recovery/sql_aggregate_wal_file.cpp), [include/crown/recovery/sql_aggregate_files.hpp](../../../../../../include/crown/recovery/sql_aggregate_files.hpp), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md) |

```text
void append(const Frame&) &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare WAL append of one caller-owned immutable complete frame. |
| inputs / outputs | An lvalue WalFile borrows the Frame bytes for validation and I/O; success returns void after confirmed cursor publication. |
| invariants | Actual bytes are inspected under the receiving frozen schema; cached Frame::info() is not trusted, and a torn suffix blocks appending. |
| ownership | The caller keeps the live, unmoved Frame throughout the call. The file owns only a fixed cursor candidate and does not retain a second pending command. |
| failure | Validation can fail before I/O without poisoning; once Io::append starts, later failure keeps the uncertainty latch set and requires reopening. |
| cost | One complete inspect/feed pass plus chunked write and fsync/stat; no additional frame allocation on the WAL append path. |
| Design | [src/recovery/sql_aggregate_wal_file.cpp](../../../../../../src/recovery/sql_aggregate_wal_file.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_wal.cpp](../../../../../../src/recovery/sql_aggregate_wal.cpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../../src/recovery/sql_aggregate_file_detail.cpp) |

```text
void repair_tail() &;
  void close() &; // Destruction closes best effort; close reports errors once.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose low-level WAL suffix truncation after the caller has established whole-session semantic safety. |
| inputs / outputs | A healthy lvalue owner repairs only its previously admitted incomplete suffix; the receiving session must first validate root identities, native replay, sink coverage, EOF and stamps. |
| invariants | Complete records, including a final pending Input, remain at cursor.state().bytes. The public method does not itself prove or enforce the semantic caller precondition. |
| ownership | No repair token or native owner is retained here; the caller bears the semantic validation obligation and the file retains its locked FD. |
| failure | Untorn state is a no-op; truncate/fsync/final-stat failure poisons the owner, while complete corruption was already rejected by open. |
| cost | Constant metadata work and at most the bounded stamp/truncate/sync/stat calls; it performs no native replay or scan itself. |
| Design | [src/recovery/sql_aggregate_wal_file.cpp](../../../../../../src/recovery/sql_aggregate_wal_file.cpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../../src/recovery/sql_aggregate_file_detail.cpp), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md) |

```text
void close() &; // Destruction closes best effort; close reports errors once.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare explicit checked consumption of the WAL file descriptor. |
| inputs / outputs | A nonempty lvalue WalFile calls close once; no value is returned, and subsequent healthy-state use is invalid. |
| invariants | The FD is removed from Data before the checked close result; EINTR never causes a second Linux close of a potentially reused descriptor. |
| ownership | Data and its accounted metadata can outlive close, but FD ownership has ended even when the close reports failure. |
| failure | Close remains available for a poisoned owner; absent/already closed handles fail state, and close I/O/quota errors propagate once. |
| cost | O(1) descriptor consumption and one metered close attempt, or one raw safety close if the normal operation grant is already exhausted. |
| Design | [src/recovery/sql_aggregate_wal_file.cpp](../../../../../../src/recovery/sql_aggregate_wal_file.cpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../../src/recovery/sql_aggregate_file_detail.cpp), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md) |

```text
using ReplayVisitor=void(*)(std::string_view,const Inspected&,const WalState&,void*);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restrict incremental WAL replay observation to the friend Session receiving factory. |
| inputs / outputs | The private receiver gets the borrowed complete frame, the already accepted Inspected metadata, its post-feed WalState and opaque context; public open passes null. |
| invariants | Visitor effects must remain private until full scan, EOF/stamp, fsync and directory confirmation succeed. Complete-frame success does not certify later records. |
| ownership | The visitor owns its context and any single decoded pending command it needs; frame views expire when the reusable scan scratch changes. |
| failure | A visitor exception abandons the provisional owner and propagates directly; this declaration supplies no catch, publication or rollback framework. |
| cost | One optional callback per complete frame. Reusing accepted Inspected metadata avoids a second coordinator inspect pass; genuine Input decoding/native/output work remains separate from file scan counters. |
| Design | [src/recovery/sql_aggregate_wal_file.cpp](../../../../../../src/recovery/sql_aggregate_wal_file.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md) |

```text
resource::AccountedUnique<Data> data_;
};

// A chained fingerprint
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep WAL implementation storage private and account-owned behind the public move-only handle. |
| inputs / outputs | The private constructor receives one AccountedUnique&lt;Data&gt;; data() is the guarded internal access route. |
| invariants | Empty storage is a valid moved-from handle but cannot pass data(); no public DTO can construct a WalFile Data object. |
| ownership | The unique deleter retains the receiving account and destroys the complete Data out of line, preserving FD and nested allocator lifetime. |
| failure | Allocation/construction failures are handled by the accounted ownership factory before a public owner escapes; getters reject empty ownership. |
| cost | One accounted Data allocation plus its explicitly funded nested metadata/scratch, with constant public handle size. |
| Design | [include/crown/resource/ownership.hpp](../../../../../../include/crown/resource/ownership.hpp), [src/recovery/sql_aggregate_wal_file.cpp](../../../../../../src/recovery/sql_aggregate_wal_file.cpp), [src/recovery/sql_aggregate_file_detail.hpp](../../../../../../src/recovery/sql_aggregate_file_detail.hpp) |

```text
void validate() &; // Receiving Session
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose WAL continuity validation only to the upper receiving Session. |
| inputs / outputs | Private lvalue method delegates to the actual held-file stamp/EOF barrier. |
| invariants | No public repair authorization or native replay hook is added; all complete semantic and coverage checks stay in the receiving Session. |
| ownership | Uses the existing unique WalFile owner and fixed state. |
| failure | Rejects missing/poisoned/closed ownership; admitted validation failure requires reopen. |
| cost | Declaration adds no field or runtime work; invocation performs fixed checks and bounded real I/O. |
| Design | [docs/sql_aggregate_session.md](../../../../../sql_aggregate_session.md), [include/crown/recovery/sql_aggregate_files.hpp](../../../../../../include/crown/recovery/sql_aggregate_files.hpp) |

## B0012

[Lines 84–86](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L84); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L84-L86:sha256:55fe0be11160e2985afed78bbad16e9dec02f5f598a35d8170a5b0c4466a9be9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: A chained fingerprint of a complete sink prefix, not the raw file SHA256. Generation/input_sequence=0 on a header-only prefix mean "no output epoch"; physical_sequence is then the header's explicitly declared base_sequence. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/recovery/sql_aggregate_files.hpp lines 82-88; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../../include/crown/recovery/sql_aggregate_files.hpp), [docs/code_specs/files/include/crown/recovery/sql_aggregate_files.hpp.md](sql_aggregate_files.hpp.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [docs/sql_aggregate_session.md](../../../../../sql_aggregate_session.md) |

## B0013

[Lines 87–91](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L87); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SinkPrefix {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe a complete sink prefix with absolute output frontier and a chained protected-prefix fingerprint. |
| inputs / outputs | The value holds generation, input I, absolute physical C, complete bytes and content_sha256; equality compares all fields. |
| invariants | A header-only baseline has generation/I zero, C=header.base_sequence and its header checksum. Later C is contiguous; this baseline contains no observation/proof of earlier epochs. |
| ownership | The fixed DTO owns only counters and 64 checksum bytes; it neither owns a file nor retains group output payload. |
| failure | An edited prefix is not SinkReceipt authority. Its hash is a chain over protected prefix checksums, not raw-file SHA256. |
| cost | Fixed-size equality/copy; chain construction is paid separately by SinkFile::Data::next. |
| Design | [src/recovery/sql_aggregate_sink_file.cpp](../../../../../../src/recovery/sql_aggregate_sink_file.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md) |

## B0014

[Lines 92–98](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L92); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SinkFileState {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Package healthy sink header, last complete prefix, record count, statistics and incomplete-tail observation. |
| inputs / outputs | SinkFile::state() returns this value; records counts the header plus complete indexed epochs. |
| invariants | prefix excludes any torn suffix, and header identity/base remain the expected header validated by creation/open. |
| ownership | The state copy retains no index vector, scratch, receipt privilege or advisory lock. |
| failure | The getter rejects poisoned/closed/empty owners; a copied state cannot attest that the current inode or selected root is unchanged. |
| cost | O(1) copy of fixed header/prefix/counters; no replay or file read is performed. |
| Design | [src/recovery/sql_aggregate_sink_file.cpp](../../../../../../src/recovery/sql_aggregate_sink_file.cpp), [include/crown/recovery/sql_aggregate_files.hpp](../../../../../../include/crown/recovery/sql_aggregate_files.hpp), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md) |

## B0015

[Lines 99–101](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L99); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L99-L101:sha256:180e116653f997a009cd1775836c47f806b27d234d63c37f09e1a62a949ed23a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Only a healthy, untorn actual SinkFile mints this evidence. Copies preserve an observation; they retain no file lock and cannot replace current-owner checks by a coordinator. Editable checkpoint/root DTOs cannot construct one. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/recovery/sql_aggregate_files.hpp lines 97-103; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../../include/crown/recovery/sql_aggregate_files.hpp), [docs/code_specs/files/include/crown/recovery/sql_aggregate_files.hpp.md](sql_aggregate_files.hpp.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [docs/sql_aggregate_session.md](../../../../../sql_aggregate_session.md) |

## B0016

[Lines 102–115](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L102); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class SinkReceipt {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide immutable evidence minted only from an actual healthy, untorn sink owner. |
| inputs / outputs | SinkFile privately constructs the object from its validated header/latest prefix; lvalue getters borrow its const members and copy construction preserves the observation. |
| invariants | No public/default DTO constructor exists; assignment and rvalue reference getters are deleted. Editable checkpoint/root records cannot mint this type. |
| ownership | The receipt owns fixed const header/prefix copies, with no FD, lock, Data pointer or promise that the observation remains current. |
| failure | Receipt creation is blocked for a missing/moved-from, closed, poisoned or torn owner. A healthy header-only sink can mint its declared baseline observation; it proves no earlier epochs. A coordinator still checks the current owner and exact selected sink binding/sequence/bytes/fingerprint. |
| cost | Constant fixed-member construction and access, with no allocation, file access or output-byte copy. |
| Design | [src/recovery/sql_aggregate_sink_file.cpp](../../../../../../src/recovery/sql_aggregate_sink_file.cpp), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [include/crown/recovery/sql_aggregate_checkpoint.hpp](../../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp) |

## B0017

[Lines 116–148](../../../../../../include/crown/recovery/sql_aggregate_files.hpp#L116); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class SinkFile {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one locked group-output file with an admitted absolute-C prefix and bounded epoch index. |
| inputs / outputs | Factories bind actual Descriptor/SinkHeader to a path; append delivers or byte-verifies a GroupEpoch, verify checks only prior delivery, and prefix/receipt expose confirmed facts. |
| invariants | Each epoch ordinal equals absolute C even for base_sequence&gt;0; C increments by one, I strictly increases and generation never falls. Header baseline generation/I zero proves no earlier epoch. |
| ownership | One receiving-account Data owns Io, genuine schema, one fixed index entry per complete epoch and bounded scratch; it owns no output payload queue or hot native runtime fields. |
| failure | Malformed/ordered mismatches fail before mutation; any actual I/O failure after latching requires reopen. Public repair carries the same caller-enforced full semantic validation obligation as WAL. |
| cost | O(N) retained index for N complete epochs, O(B) per new/duplicate frame validation and bounded chunked I/O; caller output encoding remains separate. |
| Design | [src/recovery/sql_aggregate_sink_file.cpp](../../../../../../src/recovery/sql_aggregate_sink_file.cpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../../src/recovery/sql_aggregate_file_detail.cpp), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp) |

```text
[[nodiscard]] static SinkFile create(const resource::MemoryAccount&,std::string_view,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare actual sink factories with an exact expected identity and selected absolute baseline. |
| inputs / outputs | Receiving account, path, Descriptor, SinkHeader and FileLimits enter; a locked SinkFile returns after header or whole-prefix confirmation. |
| invariants | Header descriptor hash is checked against an admitted Descriptor and paired with descriptor.program() freeze; sink_id/base_sequence remain exact header identity. |
| ownership | The returned sink independently retains funded immutable metadata/index/scratch and its FD; supplied arguments are not stored as borrowed views. |
| failure | Factories reject path/type/lock/wire/header/order/budget failures and release incomplete Data; creation never replaces an existing destination. |
| cost | Cold freeze plus fixed header encoding for create or O(file bytes+N index entries) scan for open, under receiving file/codec grants. |
| Design | [src/recovery/sql_aggregate_sink_file.cpp](../../../../../../src/recovery/sql_aggregate_sink_file.cpp), [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [src/frontend/sql_aggregate.cpp](../../../../../../src/frontend/sql_aggregate.cpp), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md) |

```text
~SinkFile();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare exclusive sink-owner lifetime, movable once without copying the lock or index. |
| inputs / outputs | Destructor releases Data; move construction takes its unique storage; copy and assignment are unavailable. |
| invariants | The transferred owner has the existing FD/index/account, and the moved-from handle is empty rather than a second sink owner. |
| ownership | Nested account allocators release index/scratch/schema after the receiving owner dies; Io closes its FD best effort. |
| failure | No close error is thrown from destruction; callers use explicit close() to observe the one checked close result. |
| cost | O(1) move; destruction releases O(index capacity+schema/scratch storage) owned memory and performs at most one raw file close. |
| Design | [src/recovery/sql_aggregate_sink_file.cpp](../../../../../../src/recovery/sql_aggregate_sink_file.cpp), [include/crown/resource/ownership.hpp](../../../../../../include/crown/resource/ownership.hpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../../src/recovery/sql_aggregate_file_detail.cpp) |

```text
[[nodiscard]] SinkFileState state() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare healthy sink observations, exact absolute-prefix lookup and private receipt minting. |
| inputs / outputs | state returns the last complete frontier; prefix(C) returns header baseline or indexed C; receipt returns a const snapshot from an untorn owner; requires_reopen is noexcept. |
| invariants | Prefix queries stay within \[base_sequence, last C\]; state/prefix can describe complete data through a validated torn suffix but receipt cannot be minted then. |
| ownership | Returned state/prefix values own fixed copies; a receipt retains no file lock and all queries leave Data unchanged. |
| failure | Empty/closed/poisoned getters fail state; out-of-range prefix fails binding; requires_reopen remains safe on those handles. |
| cost | O(1) direct absolute-C indexing and fixed snapshot copies, without syscalls or output materialization. |
| Design | [src/recovery/sql_aggregate_sink_file.cpp](../../../../../../src/recovery/sql_aggregate_sink_file.cpp), [include/crown/recovery/sql_aggregate_files.hpp](../../../../../../include/crown/recovery/sql_aggregate_files.hpp), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md) |

```text
bool append(const Frame&) &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare sink delivery of a new epoch or full-byte confirmation of an existing one. |
| inputs / outputs | A live immutable Frame is borrowed; true means one newly written/synced epoch, false means every encoded byte matched the actual recorded epoch. |
| invariants | Frame::info() is not an admission credential. Actual bytes are inspected under the frozen schema; metadata/hash match alone never accepts a duplicate. |
| ownership | Caller retains the one output spool during the call; sink retains only fixed index/fingerprint entries and bounded comparison scratch. |
| failure | Torn owners reject append. New-write or duplicate-read/stamp I/O failure poisons the owner; pure byte mismatch is reported after a healthy completed comparison. |
| cost | One O(frame bytes) inspection plus either chunked write/fsync/stat or O(frame bytes) actual read/comparison; duplicate scratch is at most min(epoch bytes,chunk_bytes). |
| Design | [src/recovery/sql_aggregate_sink_file.cpp](../../../../../../src/recovery/sql_aggregate_sink_file.cpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../../src/recovery/sql_aggregate_file_detail.cpp), [src/recovery/sql_aggregate_records.cpp](../../../../../../src/recovery/sql_aggregate_records.cpp), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md) |

```text
void verify(const Frame&) &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare confirmation against an already complete sink prefix without adding an epoch. |
| inputs / outputs | A borrowed group Frame enters; success returns void after exact byte comparison to the existing indexed epoch. |
| invariants | Verification may pass through a validated incomplete suffix because it targets only a prior complete entry; an absent future C is a binding failure. |
| ownership | The file does not retain the supplied output payload; it reuses its account-funded chunk scratch and existing immutable index. |
| failure | Wrong type/order/identity/length/bytes fails; duplicate-read or stamp failure latches requires_reopen just as append I/O does. |
| cost | Linear inspect and full-byte comparison, with precharged 2*epoch bytes plus successful codec work and bounded read chunks. |
| Design | [src/recovery/sql_aggregate_sink_file.cpp](../../../../../../src/recovery/sql_aggregate_sink_file.cpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../../src/recovery/sql_aggregate_file_detail.cpp), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md) |

```text
void repair_tail() &; // Same whole-session validation precondition as WalFile.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare sink truncation limited to a validated incomplete final epoch after receiving-session semantic checks. |
| inputs / outputs | A healthy sink owner uses its latest complete byte count; caller must first validate selected root/native replay/output equality, WAL/sink coverage, EOF and stamps. |
| invariants | The function cannot establish that semantic barrier and exposes no enforcement token; every complete epoch and header remains intact. |
| ownership | Only the actual locked sink FD is mutated; neither source rows nor native replay state are owned or reconstructed here. |
| failure | No torn suffix means no mutation; an uncertain truncate/sync/stat failure keeps the owner poisoned for fresh open. |
| cost | O(1) frontier lookup plus bounded truncation confirmation calls; no epoch decoding, index traversal or native work. |
| Design | [src/recovery/sql_aggregate_sink_file.cpp](../../../../../../src/recovery/sql_aggregate_sink_file.cpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../../src/recovery/sql_aggregate_file_detail.cpp), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md) |

```text
void close() &;
 private:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the checked sink descriptor lifetime boundary before Data destruction. |
| inputs / outputs | The lvalue owner consumes its FD on the first call, including when it is already poisoned. |
| invariants | The stored FD becomes -1 before the actual close result is checked, so an EINTR result is never retried. |
| ownership | Data, schema and prefix metadata remain allocated until owner destruction, while file-lock ownership ends with FD close. |
| failure | Empty/already closed owners fail state; I/O or normal-cap exhaustion is reported after descriptor consumption. |
| cost | One descriptor handoff and close attempt, with raw safety close only when Io::call cannot admit a metered close. |
| Design | [src/recovery/sql_aggregate_sink_file.cpp](../../../../../../src/recovery/sql_aggregate_sink_file.cpp), [src/recovery/sql_aggregate_file_detail.cpp](../../../../../../src/recovery/sql_aggregate_file_detail.cpp), [include/crown/recovery/sql_aggregate_files.hpp](../../../../../../include/crown/recovery/sql_aggregate_files.hpp) |

```text
bool accept(const Frame&,bool verify_only);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep the common new-delivery/existing-prefix algorithm private to append and verify. |
| inputs / outputs | The private Boolean chooses whether a missing epoch may be appended; the borrowed Frame remains unchanged throughout acceptance. |
| invariants | Public append and verify cannot bypass actual-byte validation, complete-byte duplicate comparison, index prepayment or uncertainty latching. |
| ownership | AccountedUnique&lt;Data&gt; below this declaration is the only retained implementation owner; no public constructor accepts an index, receipt or output DTO. |
| failure | All codec/file/account exceptions propagate through the public wrapper; this helper adds no catch or retry policy. |
| cost | Shared implementation has O(B) work and either amortized index growth or bounded duplicate scratch; wrapper dispatch is O(1). |
| Design | [src/recovery/sql_aggregate_sink_file.cpp](../../../../../../src/recovery/sql_aggregate_sink_file.cpp), [include/crown/resource/ownership.hpp](../../../../../../include/crown/resource/ownership.hpp), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md) |

```text
void validate() &;
  bool accept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose sink continuity validation only to its friend receiving Session. |
| inputs / outputs | Private lvalue validation uses the existing held sink stamp and physical EOF. |
| invariants | No new receipt, delivery or repair authority is minted by the declaration. |
| ownership | Retains the existing account/FD/index only. |
| failure | Its implementation rejects invalid ownership and propagates file poison on admitted uncertainty. |
| cost | No field/layout overhead; fixed wrapper and three-call barrier when used. |
| Design | [docs/sql_aggregate_session.md](../../../../../sql_aggregate_session.md), [include/crown/recovery/sql_aggregate_files.hpp](../../../../../../include/crown/recovery/sql_aggregate_files.hpp) |
