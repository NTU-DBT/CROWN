# `include/crown/recovery/sql_aggregate_checkpoint.hpp` — block usage map

[Source](../../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `06654ca0eed28782e47cd4e8ef7a296b106704278e4b4480c09b56a360ff5629`. 68 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../../checkpoints.md), [docs/journal.md](../../../../../journal.md), [docs/journal-files.md](../../../../../journal-files.md), [docs/generations.md](../../../../../generations.md), [docs/local-sink.md](../../../../../local-sink.md), [docs/history-retirement.md](../../../../../history-retirement.md), [docs/update_patterns.md](../../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. |  · [reviewed contract](#b0001) |
| [B0002 · 9–14](../../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp#L9) | Type/record definition: struct CheckpointMetadata |  · [reviewed contract](#b0002) |
| [B0003 · 15–18](../../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp#L15) | Type/record definition: struct CheckpointLimits |  · [reviewed contract](#b0003) |
| [B0004 · 19–25](../../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp#L19) | Type/record definition: struct InspectedCheckpoint |  · [reviewed contract](#b0004) |
| [B0005 · 26–28](../../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp#L26) | Explanatory comments or spacing. | source comment (unverified): // Immutable account-owned wire data. Neither this image nor its delivery DTO is · [reviewed contract](#b0005) |
| [B0006 · 29–44](../../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp#L29) | Type/record definition: class Checkpoint | returns {bytes_.data(),bytes_.size()}; info_; source comment (unverified): // Immutable account-owned wire data. Neither this image nor its delivery DTO is · [reviewed contract](#b0006) |
| [B0007 · 45–52](../../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp#L45) | Type/record definition: struct RestoredCheckpoint | source comment (unverified): // I, independently of native C after Reject. · [reviewed contract](#b0007) |
| [B0008 · 53–68](../../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp#L53) | declares values/defaults or compile-time conditions. | source comment (unverified): // Snapshot fields are untrusted data. Encode checks full binding/schema/domain · [reviewed contract](#b0008) |

## B0001

[Lines 1–8](../../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
namespace detail { struct CheckpointAccess; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward-declare the internal checkpoint-access helper named by the later \`Checkpoint\` friend declaration. |
| inputs / outputs | The declaration introduces \`recovery::sql_aggregate::detail::CheckpointAccess\`; it declares no function or object interface here. The later \`Checkpoint\` class names this type as a friend. |
| invariants | A forward declaration grants no private access by itself. Construction control comes from the separate friend and private constructor; an encoded image does not establish file selection, sink receipt, or durable-root authority. |
| ownership | The forward declaration owns no bytes or handle. A later \`Checkpoint\` value owns account-allocated frame bytes plus fixed inspection metadata. |
| failure | There is no runtime failure path at declaration. Later codec validation reports image/limit faults through \`ImageFailure\`; supplied-account allocation failures propagate separately. |
| cost | No runtime work occurs at this declaration. \`encode_checkpoint\` separately scans, measures, writes, and hashes source/frame data before constructing the handle. |
| Design | [include/crown/recovery/sql_aggregate_checkpoint.hpp §friend access](../../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp), [src/recovery/sql_aggregate_checkpoint.cpp §CheckpointAccess and encode](../../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [docs/sql_aggregate_checkpoint.md §wire and ownership](../../../../../sql_aggregate_checkpoint.md) |

## B0002

[Lines 9–14](../../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CheckpointMetadata
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry descriptive identity and the two independently advancing physical/command frontiers in a checkpoint frame. |
| inputs / outputs | Binding/query identity, generation, physical sequence C, command sequence I and a \`GenerationDeliveryAnchor\` DTO in; metadata validation and exact expected-metadata comparison out. |
| invariants | Requires valid lower-case query/descriptor and anchor hashes, generation &gt; 0, C &lt;= I, anchor sequence C and positive described byte extent. This DTO is not evidence of a real sink receipt. |
| ownership | Fixed value fields are copied into the frame/result; callers own this value and provide it by reference to encode/restore. |
| failure | Invalid combinations fail through the fixed image binding path before a checkpoint is accepted. |
| cost | Fixed-size metadata; hash validation visits fixed arrays. |
| Design | [include/crown/recovery/sql_aggregate_checkpoint.hpp](../../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp), [docs/sql_aggregate_checkpoint.md §State and authority](../../../../../sql_aggregate_checkpoint.md) |

## B0003

[Lines 15–18](../../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CheckpointLimits
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound checkpoint wire bytes, cumulative codec work, physical dimensions and source-progress names. |
| inputs / outputs | \`image\` carries frame/work/table/row/field/scalar limits; \`sources\` and \`source_bytes\` bound progress count and each UTF8 name. |
| invariants | These limits govern codec inspection/encoding/materialization only; actual cold lowering/source/native/group grants are separately supplied to restore. |
| ownership | A plain caller-owned value copied into each operation; it retains no image or account. |
| failure | Excess dimensions or cumulative byte work produce ImageFailure limit rejection. |
| cost | Fixed scalar policy values; no work until an operation traverses admitted data. |
| Design | [include/crown/recovery/sql_aggregate_checkpoint.hpp](../../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp), [docs/sql_aggregate_checkpoint.md §Limits and cost](../../../../../sql_aggregate_checkpoint.md) |

## B0004

[Lines 19–25](../../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InspectedCheckpoint
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report fixed checkpoint identity, reader/frontier metadata, dimensions, whole-frame hash and codec statistics. |
| inputs / outputs | Contains \`CheckpointMetadata\`, optional ReaderPosition, source/row/max-field counts, full SHA256 and ImageStatistics. |
| invariants | Inspection exposes no decoded source rows and no sink/root-selection capability; statistics count codec visits, not compiler work or elapsed CPU. |
| ownership | Returned by value with fixed arrays/scalars/optional; it owns no frame or row payload. |
| failure | No result is returned for malformed framing, hashes, schema, order, or limits. |
| cost | Fixed-size result independent of row payload size. |
| Design | [include/crown/recovery/sql_aggregate_checkpoint.hpp](../../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp), [docs/sql_aggregate_checkpoint.md §Wire contract](../../../../../sql_aggregate_checkpoint.md), [docs/sql_aggregate_checkpoint.md §Limits and cost](../../../../../sql_aggregate_checkpoint.md) |

## B0005

[Lines 26–28](../../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp#L26); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L28:sha256:bc69e6edeef2f3b58b1fde86f0c4a538f58ff2836debe366e29de316955f4d69
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Immutable account-owned wire data. Neither this image nor its delivery DTO is a file lock, sink receipt or root-selection capability. The durable owner must capture only at W=I,D=C and bind this metadata to actual selected files. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/recovery/sql_aggregate_checkpoint.hpp lines 24-30; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/recovery/sql_aggregate_checkpoint.hpp](../../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp), [docs/code_specs/files/include/crown/recovery/sql_aggregate_checkpoint.hpp.md](sql_aggregate_checkpoint.hpp.md), [docs/sql_aggregate_checkpoint.md](../../../../../sql_aggregate_checkpoint.md), [docs/sql_source_images.md](../../../../../sql_source_images.md) |

## B0006

[Lines 29–44](../../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp#L29); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Checkpoint
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold immutable account-funded CROWNAC2 frame bytes and the fixed inspection summary. |
| inputs / outputs | \`bytes() const &\` and \`info() const &\` provide lvalue borrows; the private factory builds it from the encoded vector and summary. |
| invariants | Copy is deleted and moves transfer ownership; rvalue borrow accessors are deleted so a returned view/reference cannot be taken from a temporary handle. |
| ownership | The frame vector retains its MemoryAccount owner until the last Checkpoint handle is destroyed; returned string_view/info reference this handle. |
| failure | Only the private access type can construct a Checkpoint; encoding/account failures return no handle. |
| cost | One retained account-backed image vector plus fixed summary; moves do not clone the payload. |
| Design | [include/crown/recovery/sql_aggregate_checkpoint.hpp](../../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp), [docs/sql_aggregate_checkpoint.md §Lifecycle and ownership](../../../../../sql_aggregate_checkpoint.md) |

## B0007

[Lines 45–52](../../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp#L45); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct RestoredCheckpoint
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the genuine rebuilt runtime together with input progress and checkpoint/rebuild evidence. |
| inputs / outputs | Contains a real SqlAggregateRuntime, AccountedInputProgress at I, optional reader, metadata, codec statistics and separate RebuildMetrics. |
| invariants | The runtime frontier is C while command progress is I; temporary decoded rows are gone before return. Codec work and cold build grants/metrics remain distinct. |
| ownership | Returned runtime/program/source state and progress names are charged to and survive under the receiving account; no input wire borrow is retained. |
| failure | Inspection, metadata mismatch, account, source-constraint, arithmetic or cold factory failures propagate before a value is returned. |
| cost | Fixed result handles and metrics; retained state is the real receiving runtime/progress, not a duplicate checkpoint row image. |
| Design | [include/crown/recovery/sql_aggregate_checkpoint.hpp](../../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp), [docs/sql_aggregate_checkpoint.md §State and authority](../../../../../sql_aggregate_checkpoint.md), [docs/sql_aggregate_checkpoint.md §Lifecycle and ownership](../../../../../sql_aggregate_checkpoint.md) |

## B0008

[Lines 53–68](../../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp#L53); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Checkpoint encode_checkpoint(const resource::MemoryAccount&,const Descriptor&,
    const runtime::sql_aggregate::SourceSnapshot&,const CheckpointMetadata&,
    const io::AccountedInputProgress&,std::optional<ReaderPosition> = {},CheckpointLimits = {});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode the complete authentic physical source bags and C/I progress as a canonical CROWNAC2 frame. |
| inputs / outputs | Takes the image account, genuine descriptor, current SourceSnapshot, descriptive metadata, accounted input progress, optional stream reader position and codec limits; returns an owning Checkpoint. |
| invariants | Checks program/source/native binding identity, C and I, schemas, nullable cell domains, positive in-domain weights, unique complete row keys, canonical source positions and exact metadata. Snapshot fields remain editable data; cold restore performs final source constraints/arithmetic. |
| ownership | Borrows descriptor/source/progress and reader for the call; returned bytes are owned by the supplied image account. |
| failure | Malformed identity/domain/order or over-cap data yields ImageFailure; MemoryAccount and standard allocation failures propagate without a new catch/retry. |
| cost | Measures and writes rows, packs typed keys for O(R log R) sorting/duplicate checks, then hashes protected frame regions. Key scratch and index vector die before Checkpoint escapes. |
| Design | [include/crown/recovery/sql_aggregate_checkpoint.hpp](../../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp), [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [docs/sql_aggregate_checkpoint.md §Wire contract](../../../../../sql_aggregate_checkpoint.md), [docs/sql_aggregate_checkpoint.md §Lifecycle and ownership](../../../../../sql_aggregate_checkpoint.md) |

```text
[[nodiscard]] InspectedCheckpoint inspect_checkpoint(const Descriptor&,std::string_view,CheckpointLimits = {});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a complete checkpoint against the genuine descriptor without creating a receiving runtime. |
| inputs / outputs | Takes a genuine Descriptor, immutable checkpoint bytes and codec caps; returns fixed metadata, source/row dimensions, hash and work statistics. |
| invariants | Checks envelope and both hashes, exact frame length, metadata, progress ordering, complete table/schema shape, canonical row-key order, domains and weights. No sink/root authority follows from descriptive metadata. |
| ownership | All byte views are borrowed only during the call; returned fields own no view into the input. |
| failure | Any wire/schema/domain/order/cap issue uses ImageFailure; descriptor misuse fails before a result. |
| cost | Linear admitted data visits and selected comparison extents; success is allocation-free only under the covered C++ \`new\` denial seam, not a global malloc/syscall claim. |
| Design | [include/crown/recovery/sql_aggregate_checkpoint.hpp](../../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp), [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [docs/sql_aggregate_checkpoint.md §Wire contract](../../../../../sql_aggregate_checkpoint.md), [docs/sql_aggregate_checkpoint.md §Lifecycle and ownership](../../../../../sql_aggregate_checkpoint.md) |

```text
[[nodiscard]] RestoredCheckpoint restore_checkpoint_into(const resource::MemoryAccount&,const Descriptor&,
    std::string_view,const CheckpointMetadata&,const runtime::sql_aggregate::RebuildLimits&,CheckpointLimits = {});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore a whole physical checkpoint into a fresh receiving account using the genuine cold runtime factory. |
| inputs / outputs | Takes receiving account, authentic Descriptor, unchanged wire bytes, complete expected metadata, separate cold RebuildLimits and codec caps; returns genuine runtime and input progress. |
| invariants | Completes full inspection and exact expected-metadata match before any receiver state allocation; materializes all physical rows and invokes the actual whole-image rebuild at C. Final uniqueness/FK constraints and aggregate arithmetic are rechecked. |
| ownership | Input bytes are borrowed only through the call. A reused Cell vector feeds account-owned temporary Tuples, which are copied into the live rebuilt runtime; temporary decode rows die before return. |
| failure | Wire/metadata failure precedes account materialization; account, genuine compiler/native, final-constraint or arithmetic failures propagate with partial local owners unwound. |
| cost | Inspection plus second decode/copy plus cold source/native/group work. Temporary decoded tuples overlap rebuilt source rows; codec unit/cell and TEXT extent charges are not \`sizeof(Cell)\` memcpy bytes or CPU instructions. |
| Design | [include/crown/recovery/sql_aggregate_checkpoint.hpp](../../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp), [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [docs/sql_aggregate_checkpoint.md §Lifecycle and ownership](../../../../../sql_aggregate_checkpoint.md), [docs/sql_aggregate_checkpoint.md §Limits and cost](../../../../../sql_aggregate_checkpoint.md) |
