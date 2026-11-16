# `include/crown/recovery/sql_rows_checkpoint.hpp` — block usage map

[Source](../../../../../../include/crown/recovery/sql_rows_checkpoint.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `7f2d7b98c9d5ba94640fb9b1efa40f187d79cf227caaae0ec3dd71cdd989c05d`. 68 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../../checkpoints.md), [docs/journal.md](../../../../../journal.md), [docs/journal-files.md](../../../../../journal-files.md), [docs/generations.md](../../../../../generations.md), [docs/local-sink.md](../../../../../local-sink.md), [docs/history-retirement.md](../../../../../history-retirement.md), [docs/update_patterns.md](../../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../../include/crown/recovery/sql_rows_checkpoint.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. |  · [reviewed contract](#b0001) |
| [B0002 · 9–14](../../../../../../include/crown/recovery/sql_rows_checkpoint.hpp#L9) | Type/record definition: struct CheckpointMetadata |  · [reviewed contract](#b0002) |
| [B0003 · 15–18](../../../../../../include/crown/recovery/sql_rows_checkpoint.hpp#L15) | Type/record definition: struct CheckpointLimits |  · [reviewed contract](#b0003) |
| [B0004 · 19–25](../../../../../../include/crown/recovery/sql_rows_checkpoint.hpp#L19) | Type/record definition: struct InspectedCheckpoint |  · [reviewed contract](#b0004) |
| [B0005 · 26–28](../../../../../../include/crown/recovery/sql_rows_checkpoint.hpp#L26) | Explanatory comments or spacing. | source comment (unverified): // Immutable account-owned wire data. Neither this image nor its delivery DTO is · [reviewed contract](#b0005) |
| [B0006 · 29–44](../../../../../../include/crown/recovery/sql_rows_checkpoint.hpp#L29) | Type/record definition: class Checkpoint | returns {bytes_.data(),bytes_.size()}; info_; source comment (unverified): // Immutable account-owned wire data. Neither this image nor its delivery DTO is · [reviewed contract](#b0006) |
| [B0007 · 45–52](../../../../../../include/crown/recovery/sql_rows_checkpoint.hpp#L45) | Type/record definition: struct RestoredCheckpoint | source comment (unverified): // I, independently of native C after Reject. · [reviewed contract](#b0007) |
| [B0008 · 53–68](../../../../../../include/crown/recovery/sql_rows_checkpoint.hpp#L53) | declares values/defaults or compile-time conditions. | source comment (unverified): // Snapshot fields are untrusted data. Encode checks full binding/schema/domain · [reviewed contract](#b0008) |

## B0001

[Lines 1–8](../../../../../../include/crown/recovery/sql_rows_checkpoint.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:6ebe513d46136d03d7e0943b46b861bbd0107f3ac0b6925daf66f76a30eec969
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Include descriptor, generation anchor and accounted input-progress types. |
| inputs / outputs | Open row recovery namespace and forward-declare own CheckpointAccess. |
| invariants | Includes/forward declaration create no checkpoint, sink receipt or root authority. |
| ownership | No new runtime backing storage from declarations; actual declared views/handles obey their named type lifetimes. |
| failure | Compile-time checking only in this span; invoked member/helper operations have separately specified failures. |
| cost | Include/type/signature/constant declarations only; no executed codec/binder/hash/sort/native work or backing allocation. |
| Design | [include/crown/recovery/sql_rows_checkpoint.hpp](../../../../../../include/crown/recovery/sql_rows_checkpoint.hpp) |

## B0002

[Lines 9–14](../../../../../../include/crown/recovery/sql_rows_checkpoint.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L9-L14:sha256:73e90f118dc166b1e55a907bf72b80f8ba2fd2fd0a4c9e2262431983666ab347
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry query/descriptor identity, generation, independent C/I and a descriptive delivery anchor. |
| inputs / outputs | CheckpointMetadata contains Binding, generation, physical_sequence C, command_sequence I and GenerationDeliveryAnchor, with default equality. |
| invariants | Editable DTO only. The type does not check identities/frontiers, observe a sink receipt, select a root or authenticate durable bytes. |
| ownership | Fixed arrays/scalars own all member values. |
| failure | No custom validation path. |
| cost | Fixed field initialization/copy/equality; no hash, file I/O or allocation. |
| Design | [include/crown/recovery/sql_rows_checkpoint.hpp](../../../../../../include/crown/recovery/sql_rows_checkpoint.hpp) |

## B0003

[Lines 15–18](../../../../../../include/crown/recovery/sql_rows_checkpoint.hpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L18:sha256:393e7de90af8e3a087813425426d45a4fc44ab4613c44f364c9781d4db8d9a44
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare finite image and progress-name defaults for checkpoint codecs. |
| inputs / outputs | CheckpointLimits contains ImageLimits {bytes=128MiB, work=1GiB, tables=4096, rows=65536, fields=1024, scalar_bytes=1MiB} and source-position/name-byte caps both4096. |
| invariants | Defaults provide bounds; declaration itself neither validates supplied overrides nor spends a grant. |
| ownership | Plain numeric limits, no external owner. |
| failure | No executable validation path. |
| cost | Fixed values/layout/copy; no parsing, work traversal or allocation. |
| Design | [include/crown/recovery/sql_rows_checkpoint.hpp](../../../../../../include/crown/recovery/sql_rows_checkpoint.hpp), [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp) |

## B0004

[Lines 19–25](../../../../../../include/crown/recovery/sql_rows_checkpoint.hpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L25:sha256:cd1241a80fb4fd6687f096b8925e80d063c6d80c277b586290a0f7c41b7c3d05
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry checkpoint metadata, reader position, counts, digest and codec work. |
| inputs / outputs | InspectedCheckpoint contains CheckpointMetadata, optional ReaderPosition, source/row/max-field counts, Hash and ImageStatistics. |
| invariants | No validation in the carrier. Inspection establishes typed transport facts; native constraints and actual sink delivery remain separate. |
| ownership | All members are fixed-value metadata; no source rows/input frame borrow. |
| failure | No custom validation/error translation. |
| cost | Fixed metadata storage/copy; no parse/hash/rebuild or allocation. |
| Design | [include/crown/recovery/sql_rows_checkpoint.hpp](../../../../../../include/crown/recovery/sql_rows_checkpoint.hpp) |

## B0005

[Lines 26–28](../../../../../../include/crown/recovery/sql_rows_checkpoint.hpp#L26); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L28:sha256:bc69e6edeef2f3b58b1fde86f0c4a538f58ff2836debe366e29de316955f4d69
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the adjacent block boundary. |
| inputs / outputs | Comment/spacing only. |
| invariants | Text is not an executed check or proof. |
| ownership | No ownership operation. |
| failure | No executable failure path. |
| cost | No runtime work/allocation. |
| Design | [include/crown/recovery/sql_rows_checkpoint.hpp](../../../../../../include/crown/recovery/sql_rows_checkpoint.hpp) |

## B0006

[Lines 29–44](../../../../../../include/crown/recovery/sql_rows_checkpoint.hpp#L29); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L44:sha256:ee752e0d9d02881794571a8c6c55bb3cb9d424af1d8f5a50a9534bb364323ccb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one immutable receiving-funded physical row checkpoint with move-only borrowed byte/info views. |
| inputs / outputs | Private Checkpoint(ImageVector&lt;char&gt;,InspectedCheckpoint) moves one byte owner and fixed checkpoint metadata into Checkpoint; lvalue bytes()/info() return borrowed views/references. |
| invariants | Copy and rvalue borrows are deleted; moves are defaulted noexcept. Constructor/getters do not validate hashes/constraints/native state; factory establishes the valid image premise. |
| ownership | bytes_ owns receiving-account storage; info_ owns fixed metadata. Moves transfer vector storage; borrows require the same live unmoved handle. |
| failure | Declared constructor/moves/accessors are noexcept; no parser/error translation. Final destruction releases the byte buffer. |
| cost | Fixed vector/metadata moves and pointer-length/reference getters; no payload traversal/new backing allocation by getters. Teardown releases existing storage. |
| Design | [include/crown/recovery/sql_rows_checkpoint.hpp](../../../../../../include/crown/recovery/sql_rows_checkpoint.hpp) |

## B0007

[Lines 45–52](../../../../../../include/crown/recovery/sql_rows_checkpoint.hpp#L45); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L52:sha256:977e49f0179e219fd4afc692bfe972373d1cf45035cdac43d22e7d4c09e68d09
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a restored native owner and independent disposed input progress with receiving metrics. |
| inputs / outputs | RestoredCheckpoint carries SqlRowsRuntime, AccountedInputProgress, optional reader, metadata, codec statistics and RebuildMetrics. |
| invariants | No extra factory/check occurs in this struct; restore_checkpoint_into supplies the matching members. Progress I can exceed native C after a Reject. |
| ownership | Runtime/progress own receiving-account state; fixed metadata/metrics are copied. No caller-frame borrow is retained. |
| failure | Member construction/move/release rules apply; no catch/error translation here. |
| cost | Only transfer/teardown of member owners; codec/materialization/native rebuild work is performed by the factory, not this declaration. |
| Design | [include/crown/recovery/sql_rows_checkpoint.hpp](../../../../../../include/crown/recovery/sql_rows_checkpoint.hpp) |

## B0008

[Lines 53–68](../../../../../../include/crown/recovery/sql_rows_checkpoint.hpp#L53); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L53-L68:sha256:61920aa301590373fa99de5a4850abc940630757b90186685c4703885e67d9c2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare checkpoint encode, inspection and genuine cold-restore APIs. |
| inputs / outputs | Declare encode_checkpoint(receiver,descriptor,source,metadata,progress,reader,limits), inspect_checkpoint and restore_checkpoint_into(receiver,descriptor,bytes,expected,build,limits). |
| invariants | Comments separate transport validity from final native constraints and actual durable selection; no operation runs here. |
| ownership | No new runtime backing storage from declarations; actual declared views/handles obey their named type lifetimes. |
| failure | Compile-time checking only in this span; invoked member/helper operations have separately specified failures. |
| cost | Include/type/signature/constant declarations only; no executed codec/binder/hash/sort/native work or backing allocation. |
| Design | [include/crown/recovery/sql_rows_checkpoint.hpp](../../../../../../include/crown/recovery/sql_rows_checkpoint.hpp) |
