# `src/recovery/image.cpp` — block usage map

[Source](../../../../../src/recovery/image.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `79b127805940d86614be7ac75d71030729d97c0784527a009580fa3495a5c36f`. 102 lines partitioned into 10 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../src/recovery/image.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 13–28](../../../../../src/recovery/image.cpp#L13) | Callable definition: void write(Writer& writer,const ImageManifest& manifest,std::span&lt;const ImageTableView&gt; tables) | calls put, integer, data, require; guard require(tables.size()&lt;=writer.budget.limits.tables,ImageFault::limit);writer.integer(tables.size(),…; 5 loop sites; source comment (unverified): // exact-nonnull-v1 · [reviewed contract](#b0002) |
| [B0003 · 29–60](../../../../../src/recovery/image.cpp#L29) | Callable definition: ImageManifest read(Reader& reader,const ImageBinding* expected,DecodedImage* result,const resource::MemoryAccount& account) | calls take, std::copy, begin, end; guard require(reader.integer(2)==1,ImageFault::version);; returns manifest; growth copy_of, emplace_back, push_back, reserve; 4 loop sites; source comment (unverified): // This checks wire shape; runtime admission still checks schema and duplicates. · [reviewed contract](#b0003) |
| [B0004 · 61–63](../../../../../src/recovery/image.cpp#L61) | Callable definition: void binding(const ImageBinding& value) | calls require, hex; guard require(hex(value.physical_sha256) && hex(value.source_sha256) && value.catalog_version&gt;0,ImageFaul… · [reviewed contract](#b0004) |
| [B0005 · 64–73](../../../../../src/recovery/image.cpp#L64) | Callable definition: InspectedImage inspect(std::string_view bytes,const ImageBinding* expected,ImageLimits limits) | calls require, size, take, integer; guard require(bytes.size()&lt;=limits.bytes,ImageFault::limit);Budget budget{limits};Reader header{bytes,bud…; returns {manifest,{static_cast&lt;std::uint64_t&gt;(bytes.size()),budget.used,budget.rows}} · [reviewed contract](#b0005) |
| [B0006 · 74–74](../../../../../src/recovery/image.cpp#L74) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0006) |
| [B0007 · 75–88](../../../../../src/recovery/image.cpp#L75) | Callable definition: EncodedImage encode_image(const resource::MemoryAccount& account,const ImageManifest& manifest, std::span&lt;const ImageTableView&gt; t… | calls binding, write, require, charge; guard require(preflight.size&lt;=SIZE_MAX,ImageFault::limit);; returns result; growth reserve; 1 loop sites; source comment (unverified): // Admit all remaining deterministic byte work before the first allocation. · [reviewed contract](#b0007) |
| [B0008 · 89–100](../../../../../src/recovery/image.cpp#L89) | Callable definition: DecodedImage decode_image(const resource::MemoryAccount& account,std::string_view bytes, const ImageBinding& expected,ImageLimits… | calls binding, inspect, charge, size; returns result; source comment (unverified): // Reserve the second payload visit before output growth. The caller keeps · [reviewed contract](#b0008) |
| [B0009 · 101–101](../../../../../src/recovery/image.cpp#L101) | Callable definition: InspectedImage inspect_image(std::string_view bytes,ImageLimits limits) | calls inspect; returns inspect(bytes,nullptr,limits) · [reviewed contract](#b0009) |
| [B0010 · 102–102](../../../../../src/recovery/image.cpp#L102) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::recovery · [reviewed contract](#b0010) |

## B0001

[Lines 1–12](../../../../../src/recovery/image.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/recovery/image.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement CROWNRI1 as a pure in-memory wire component. |
| inputs / outputs | Internal byte helpers, fixed SHA and magic CROWNRI1. |
| invariants | This translation unit performs no file publication, compiler admission or runtime rebuild. Magic/version/arithmetic belong to this local format, not a CROWN paper durability theorem. |
| ownership | No global owning state or hidden account. |
| failure | Per-call validation and funded-output failures are explicit. |
| cost | Fixed constants/dependencies; codec costs are linear serialized visits. |
| Design | [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/runtime/physical.cpp § PhysicalRuntime::restore_image](../../../../../src/runtime/physical.cpp) |

## B0002

[Lines 13–28](../../../../../src/recovery/image.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void write(Writer& writer
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit one deterministic runtime image layout in sizing/materializing mode. |
| inputs / outputs | Manifest and ordered table/row views in; header placeholders, binding/policy and exact scalar rows out. |
| invariants | Table IDs are contiguous positions; total rows and per-row fields are bounded. Caller maintains stable borrowed data across passes. No sorting, schema, duplicate-row or UTF-8 validation is done here. |
| ownership | Borrows manifest/tables/rows/strings; optional Writer owns no output itself. |
| failure | Limit/work/scalar errors may follow earlier writes; enclosing operation discards private output. |
| cost | O(serialized bytes+tables+rows+fields); empty rows/tables still emit counts and are retained. |
| Design | [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/runtime/physical.cpp § PhysicalRuntime::restore_image](../../../../../src/runtime/physical.cpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp) |

## B0003

[Lines 29–60](../../../../../src/recovery/image.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ImageManifest read(Reader& reader
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate payload structure and optionally deep-materialize its rows. |
| inputs / outputs | Payload Reader, optional exact binding and result, account in; manifest out. |
| invariants | Checks arithmetic/binding syntax, sequential table IDs, total row/field limits, minimum remaining-byte bounds and exact exhaustion. Counts cannot force output allocation until the full separate preflight succeeds. |
| ownership | Inspection has no output graph. Materialization owns nested image vectors and AccountedRow copies under supplied account; scratch ScalarViews borrow input until copied. |
| failure | ImageFailure or receiving allocation failure propagates; partially built private vectors/rows unwind. Reader/result may be partially advanced and are not reusable. |
| cost | O(payload bytes+metadata); reserves table/row arrays, reuses one cells vector and allocates one native compact block per row (including framing for empty rows). |
| Design | [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/runtime/physical.cpp § PhysicalRuntime::restore_image](../../../../../src/runtime/physical.cpp), [src/storage/accounted_row.cpp § copy_cells](../../../../../src/storage/accounted_row.cpp) |

```text
if(result){result->manifest=manifest;result->tables.reserve(tables);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare account-funded descriptor arrays and scratch for the materialization pass. |
| inputs / outputs | Validated table/row/field counts determine reserves as read proceeds. |
| invariants | Materialization is reached only after complete inspect and extra work reservation; byte-derived count guards still run on pass two. |
| ownership | Outer/nested vectors and scratch use image_allocator; AccountedRow copies use image_owner with tuple_values purpose, not the vector purpose. |
| failure | Any reserve/copy failure unwinds the enclosing DecodedImage; no input mutation or live runtime installation. |
| cost | O(tables+rows+max fields) descriptor storage plus deep row/string bytes; simultaneous scratch and outputs share one account. |
| Design | [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/runtime/physical.cpp § PhysicalRuntime::restore_image](../../../../../src/runtime/physical.cpp), [include/crown/recovery/image.hpp § image_allocator](../../../../../include/crown/recovery/image.hpp), [src/storage/accounted_row.cpp § copy_cells](../../../../../src/storage/accounted_row.cpp) |

## B0004

[Lines 61–63](../../../../../src/recovery/image.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void binding(const ImageBinding& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate fixed runtime binding syntax before encode/decode work. |
| inputs / outputs | ImageBinding in; no result. |
| invariants | Requires lowercase physical/source SHA arrays and nonzero catalog_version. Policy words remain opaque bound metadata here; semantic option validation is a caller responsibility. |
| ownership | Borrows only fixed fields. |
| failure | ImageFault::binding without output allocation. |
| cost | At most128 character tests and one integer check. |
| Design | [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/runtime/physical.cpp § PhysicalRuntime::restore_image](../../../../../src/runtime/physical.cpp), [src/runtime/checkpoint_policy.hpp](../../../../../src/runtime/checkpoint_policy.hpp) |

## B0005

[Lines 64–73](../../../../../src/recovery/image.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InspectedImage inspect(std::string_view bytes
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a complete checksummed runtime frame without materializing rows. |
| inputs / outputs | Immutable bytes, optional exact expected binding, ImageLimits in; fixed manifest/statistics out. |
| invariants | Bounds bytes, exact header version/flags/payload length and lowercase SHA, verifies body checksum, then parses all payload/count/scalar structure. Digest is corruption detection, not artifact authenticity. |
| ownership | Borrows bytes synchronously; returns no borrowed payload or owning row graph. |
| failure | ImageFailure before any decoded-row allocation; byte-work can reject hashing or preflight. No partial inspected result escapes. |
| cost | For frame B and payload P=B-84, admitted work is B+P:84 header visits+P hash+P payload parse. Additional scalar validation CPU is not an extra byte debit. |
| Design | [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/runtime/physical.cpp § PhysicalRuntime::restore_image](../../../../../src/runtime/physical.cpp) |

## B0006

[Lines 74–74](../../../../../src/recovery/image.cpp#L74); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L74-L74:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/image.cpp](../../../../../src/recovery/image.cpp), [docs/code_specs/files/src/recovery/image.cpp.md](image.cpp.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0007

[Lines 75–88](../../../../../src/recovery/image.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
EncodedImage encode_image(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preflight a complete runtime image, then own one exact encoded buffer. |
| inputs / outputs | Receiving account, manifest, stable borrowed tables and limits in; bytes/statistics/manifest out. |
| invariants | Validate binding and all wire writes, reserve total deterministic work before allocation, rerun identical write pass, patch length and body SHA. Caller DTO statistics are not used as authority. |
| ownership | Final ImageVector owns receiving-account bytes; source runtime/rows are not retained. |
| failure | Preflight/work failure precedes first output allocation; allocation or pass-two failure releases private bytes and leaves caller inputs untouched. |
| cost | For frame B,payload P, work=2B+P (preflight B, materialize B, hash P). One reserve plus append writes, header patch/hash copies and scalar CPU; no native rebuild cost included. |
| Design | [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/runtime/physical.cpp § PhysicalRuntime::restore_image](../../../../../src/runtime/physical.cpp) |

## B0008

[Lines 89–100](../../../../../src/recovery/image.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DecodedImage decode_image(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate completely, precharge materialization, then return independently owned native rows. |
| inputs / outputs | Account, immutable frame, exact expected binding and limits in; DecodedImage out. |
| invariants | inspect completes before output growth; additional P-byte reserve is checked before allocations. Pass two reads the same unchanged input. Native schema/domain/duplicate/build validation remains PhysicalRuntime's responsibility. |
| ownership | All output table/row arrays and compact payloads belong to supplied account; output outlives bytes. Scratch views never escape. |
| failure | Binding/structure/work rejection precedes materialization; account failure releases only private result. No repair, publication or source mutation. |
| cost | Work=B+2P (header+hash+two payload passes); actual deep copy, descriptors and native row framing also consume receiving memory. |
| Design | [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/runtime/physical.cpp § PhysicalRuntime::restore_image](../../../../../src/runtime/physical.cpp) |

## B0009

[Lines 101–101](../../../../../src/recovery/image.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InspectedImage inspect_image(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose allocation-free structural inspection as descriptive metadata. |
| inputs / outputs | Bytes and limits in; InspectedImage out. |
| invariants | No expected binding is supplied, so syntax/arithmetic/checksum pass does not prove a caller's selected program or policy compatibility. |
| ownership | No payload ownership retained; metadata copied by value. |
| failure | Delegates ImageFailure unchanged; performs no filesystem or native admission. |
| cost | Same B+P byte work as inspect; no successful-path native allocation. |
| Design | [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/runtime/physical.cpp § PhysicalRuntime::restore_image](../../../../../src/runtime/physical.cpp) |

## B0010

[Lines 102–102](../../../../../src/recovery/image.cpp#L102); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L102-L102:sha256:95bcfbb6661a8958a33a82a5dc501f63202f4524486b8395aa4ce785f3c26b07
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::recovery at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/image.cpp](../../../../../src/recovery/image.cpp), [docs/code_specs/files/src/recovery/image.cpp.md](image.cpp.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |
