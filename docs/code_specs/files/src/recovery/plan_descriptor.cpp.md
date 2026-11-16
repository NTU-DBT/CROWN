# `src/recovery/plan_descriptor.cpp` — block usage map

[Source](../../../../../src/recovery/plan_descriptor.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode/decode exact selected-plan descriptor identity for generation recovery.

Snapshot SHA-256: `1fc1842bfc79a9e8a7997c8405a498bb22e3bfa75a1152117f8ca50114943a0c`. 115 lines partitioned into 16 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../src/recovery/plan_descriptor.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 9–9](../../../../../src/recovery/plan_descriptor.cpp#L9) | Callable definition: \[\[noreturn\]\] void fail(ImageFault fault) | calls ImageFailure · [reviewed contract](#b0002) |
| [B0003 · 10–12](../../../../../src/recovery/plan_descriptor.cpp#L10) | Callable definition: bool hex(std::span&lt;const char&gt; value) | calls std::all_of, begin, end; returns std::all_of(value.begin(),value.end(),\[\](char c){return (c&gt;=@ && c&lt;=@ ) \|\| (c&gt;=@ && c&lt;=@ ) · [reviewed contract](#b0003) |
| [B0004 · 13–15](../../../../../src/recovery/plan_descriptor.cpp#L13) | Callable definition: bool logical_binding(const ImageBinding& a,const ImageBinding& b) | calls ; returns a.source_sha256==b.source_sha256 && a.catalog_version==b.catalog_version && a.policy==b.policy · [reviewed contract](#b0004) |
| [B0005 · 16–19](../../../../../src/recovery/plan_descriptor.cpp#L16) | Callable definition: void binding(const ImageBinding& value) | calls hex, fail, runtime::detail::checkpoint_options · [reviewed contract](#b0005) |
| [B0006 · 20–39](../../../../../src/recovery/plan_descriptor.cpp#L20) | Callable definition: void validate(const PlanSelection& value,const PlanDescriptorLimits& limits) | calls hex, fail, binding, logical_binding; source comment (unverified): // Metadata continuity is separate from checked compiler/native equivalence · [reviewed contract](#b0006) |
| [B0007 · 40–42](../../../../../src/recovery/plan_descriptor.cpp#L40) | Callable definition: std::uint64_t flags(const PlanSelection& value) | calls ; returns (value.sink_origin?1U:0U)\|(value.predecessor.delivery?2U:0U)\|(value.predecessor.plan_sha256?4U:0U) · [reviewed contract](#b0007) |
| [B0008 · 43–47](../../../../../src/recovery/plan_descriptor.cpp#L43) | Callable definition: ImageStatistics statistics(std::uint64_t bytes,const PlanDescriptorLimits& limits) | calls fail; returns {bytes,bytes*4,0} · [reviewed contract](#b0008) |
| [B0009 · 48–56](../../../../../src/recovery/plan_descriptor.cpp#L48) | Type/record definition: struct Writer | 2 loop sites; source comment (unverified): // encode_plan_descriptor sizes the complete layout before these direct stores. · [reviewed contract](#b0009) |
| [B0010 · 57–71](../../../../../src/recovery/plan_descriptor.cpp#L57) | Type/record definition: struct Reader | returns result; result; 2 loop sites · [reviewed contract](#b0010) |
| [B0011 · 72–79](../../../../../src/recovery/plan_descriptor.cpp#L72) | Callable definition: void write_selection(Writer& w,const PlanSelection& value) | calls text, word, image · [reviewed contract](#b0011) |
| [B0012 · 80–88](../../../../../src/recovery/plan_descriptor.cpp#L80) | Callable definition: PlanSelection read_selection(Reader& r,std::uint64_t bits,bool switched_epoch) | calls text, word, image; returns value · [reviewed contract](#b0012) |
| [B0013 · 89–89](../../../../../src/recovery/plan_descriptor.cpp#L89) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0013) |
| [B0014 · 90–101](../../../../../src/recovery/plan_descriptor.cpp#L90) | Callable definition: EncodedPlanDescriptor encode_plan_descriptor(const resource::MemoryAccount& account,const PlanSelection& value, std::string_view … | calls empty, size, fail, statistics; returns result; growth resize · [reviewed contract](#b0014) |
| [B0015 · 102–114](../../../../../src/recovery/plan_descriptor.cpp#L102) | Callable definition: InspectedPlanDescriptor inspect_plan_descriptor(std::string_view bytes,PlanDescriptorLimits limits) | calls statistics, size, substr, fail; returns {std::move(selection),artifact,stats} · [reviewed contract](#b0015) |
| [B0016 · 115–115](../../../../../src/recovery/plan_descriptor.cpp#L115) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::recovery · [reviewed contract](#b0016) |

## B0001

[Lines 1–8](../../../../../src/recovery/plan_descriptor.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/recovery/plan_descriptor.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement a checksummed opaque compiler-input descriptor with fixed selection metadata. |
| inputs / outputs | Public DTOs, fixed SHA and runtime policy decoder available. |
| invariants | Descriptor inspection validates wire/local continuity, not compiler semantics, exact native equivalence or root selection authority. |
| ownership | No retained global state or hidden account. |
| failure | All dynamic bytes are explicitly funded by encode; inspection uses fixed metadata and borrows artifact bytes. |
| cost | Compile-time dependencies; frame work is a conservative4*bytes debit. |
| Design | [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/recovery/plan_descriptor.hpp](../../../../../include/crown/recovery/plan_descriptor.hpp), [src/runtime/session.cpp § QuerySession::lock_generation_recovery](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § QuerySession::publish_reoptimization](../../../../../src/runtime/session.cpp) |

## B0002

[Lines 9–9](../../../../../src/recovery/plan_descriptor.cpp#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[noreturn]] void fail(ImageFault fault)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise the descriptor's selected fixed codec failure. |
| inputs / outputs | ImageFault in; never returns. |
| invariants | Fault category is chosen at the check site. |
| ownership | No owned diagnostic string. |
| failure | Throws ImageFailure and preserves enclosing RAII cleanup. |
| cost | Fixed payload; exception machinery remains a failure-path cost. |
| Design | [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/recovery/plan_descriptor.hpp](../../../../../include/crown/recovery/plan_descriptor.hpp), [src/runtime/session.cpp § QuerySession::lock_generation_recovery](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § QuerySession::publish_reoptimization](../../../../../src/runtime/session.cpp) |

## B0003

[Lines 10–12](../../../../../src/recovery/plan_descriptor.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool hex(std::span<const char> value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate lowercase hex syntax for fixed descriptor identities. |
| inputs / outputs | Borrowed span in; Boolean out. |
| invariants | No width or authenticity is proved by the alphabet predicate; callers supply fixed32/64-byte arrays. |
| ownership | No retained borrow. |
| failure | No explicit throwing operation. |
| cost | O(span length), short-circuit comparison. |
| Design | [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/recovery/plan_descriptor.hpp](../../../../../include/crown/recovery/plan_descriptor.hpp), [src/runtime/session.cpp § QuerySession::lock_generation_recovery](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § QuerySession::publish_reoptimization](../../../../../src/runtime/session.cpp) |

## B0004

[Lines 13–15](../../../../../src/recovery/plan_descriptor.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool logical_binding(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the logical continuity fields while allowing a physical plan switch. |
| inputs / outputs | Two ImageBinding values in; source SHA/catalog/policy equality out. |
| invariants | Physical SHA is deliberately excluded. Both bindings are separately syntax/policy checked by validate. Equality neither proves equivalent native results nor grants publication. |
| ownership | Borrows fixed values. |
| failure | No mutation or allocation. |
| cost | Fixed64-byte source comparison, catalog and26 policy words. |
| Design | [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/recovery/plan_descriptor.hpp](../../../../../include/crown/recovery/plan_descriptor.hpp), [src/runtime/session.cpp § QuerySession::lock_generation_recovery](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § QuerySession::publish_reoptimization](../../../../../src/runtime/session.cpp) |

## B0005

[Lines 16–19](../../../../../src/recovery/plan_descriptor.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void binding(const ImageBinding& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate descriptor hash/catalog syntax and canonical runtime policy words. |
| inputs / outputs | Fixed ImageBinding in. |
| invariants | Physical/source hashes lowercase, catalog_version nonzero, policy decoded through checkpoint_options with receiving-memory placeholder0. This does not admit a runtime or query cap. |
| ownership | Fixed temporary DeltaOptions only. |
| failure | ImageFault::binding for identity syntax; checkpoint_options can raise ImageFault::corrupt for policy encodings. |
| cost | Fixed-size byte/word checks, no successful-path heap allocation. |
| Design | [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/recovery/plan_descriptor.hpp](../../../../../include/crown/recovery/plan_descriptor.hpp), [src/runtime/session.cpp § QuerySession::lock_generation_recovery](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § QuerySession::publish_reoptimization](../../../../../src/runtime/session.cpp), [src/runtime/checkpoint_policy.hpp § checkpoint_options](../../../../../src/runtime/checkpoint_policy.hpp) |

## B0006

[Lines 20–39](../../../../../src/recovery/plan_descriptor.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validate(const PlanSelection& value
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check local lineage and bounded selection metadata before encode/after decode. |
| inputs / outputs | PlanSelection and limits in. |
| invariants | Predecessor interval valid/nonmax; generation exact successor; physical/command frontiers monotone; optional switch epoch&lt;=physical. Source/target logical binding equal. Optional delivery must match sink id and predecessor physical boundary; sink origin query/logical binding/base/generation/fields checked. |
| ownership | Borrows fixed DTOs; retains no compiler artifact, file owner or receipt. |
| failure | ImageFault::binding/limit or policy corrupt propagates. It does not establish correspondence to actual selected files, semantic equivalence, result schema hash or complete output delivery. |
| cost | Fixed-size identity/policy comparisons and scalar bounds; no scans over artifact bytes. |
| Design | [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/recovery/plan_descriptor.hpp](../../../../../include/crown/recovery/plan_descriptor.hpp), [src/runtime/session.cpp § QuerySession::lock_generation_recovery](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § QuerySession::publish_reoptimization](../../../../../src/runtime/session.cpp) |

## B0007

[Lines 40–42](../../../../../src/recovery/plan_descriptor.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t flags(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode the presence of optional fixed metadata fields. |
| inputs / outputs | PlanSelection in; bits0 sink origin,1 predecessor delivery,2 predecessor plan hash. |
| invariants | last_switch_epoch is signaled by version2, not another flags bit; writer and reader must keep identical presence ordering. |
| ownership | Pure fixed scalar return. |
| failure | No validation/allocation; caller validates separately. |
| cost | O(1). |
| Design | [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/recovery/plan_descriptor.hpp](../../../../../include/crown/recovery/plan_descriptor.hpp), [src/runtime/session.cpp § QuerySession::lock_generation_recovery](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § QuerySession::publish_reoptimization](../../../../../src/runtime/session.cpp) |

## B0008

[Lines 43–47](../../../../../src/recovery/plan_descriptor.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ImageStatistics statistics(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit total descriptor bytes and a conservative four-visits work reserve. |
| inputs / outputs | Frame byte count and limits in; bytes/work=4*bytes/rows0 out. |
| invariants | Check bytes&lt;=limits.bytes and SIZE_MAX; bytes&lt;=UINT64_MAX/4 before multiplication. Four visits are codec admission units, not compiler/native CPU or memory guarantees. |
| ownership | Fixed result only. |
| failure | ImageFault::limit/work before output allocation or hashing. |
| cost | O(1) arithmetic; actual encode initializes/copies/hashes frame bytes separately. |
| Design | [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/recovery/plan_descriptor.hpp](../../../../../include/crown/recovery/plan_descriptor.hpp), [src/runtime/session.cpp § QuerySession::lock_generation_recovery](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § QuerySession::publish_reoptimization](../../../../../src/runtime/session.cpp) |

## B0009

[Lines 48–56](../../../../../src/recovery/plan_descriptor.cpp#L48); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Writer {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write into an already sized private descriptor buffer. |
| inputs / outputs | Borrowed ImageVector and offset0. |
| invariants | Only encode calls this writer after exact overhead+artifact sizing. Helpers perform no independent output bound checks; the complete layout and fixed widths are internal preconditions. |
| ownership | Vector retains account ownership; Writer only borrows it. |
| failure | No rollback; final offset check is a consistency check, not a substitute for capacity preconditions. |
| cost | Fixed state; text/word methods write directly without vector growth. |
| Design | [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/recovery/plan_descriptor.hpp](../../../../../include/crown/recovery/plan_descriptor.hpp), [src/runtime/session.cpp § QuerySession::lock_generation_recovery](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § QuerySession::publish_reoptimization](../../../../../src/runtime/session.cpp) |

```text
void text(std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy one descriptor field into its predetermined output interval. |
| inputs / outputs | Borrowed field bytes in; offset advances by size. |
| invariants | Output interval must fit and source must remain valid/nonoverlapping as provided by encoder. |
| ownership | Copies bytes into already funded vector; no retained source view. |
| failure | No explicit guard/throw under valid internal bounds. |
| cost | O(field bytes) copy, no allocation. |
| Design | [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/recovery/plan_descriptor.hpp](../../../../../include/crown/recovery/plan_descriptor.hpp), [src/runtime/session.cpp § QuerySession::lock_generation_recovery](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § QuerySession::publish_reoptimization](../../../../../src/runtime/session.cpp) |

```text
template<std::size_t N> void text(const std::array
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize one fixed identity array without an intermediate string. |
| inputs / outputs | Const fixed char array in; forwards exact N-byte view. |
| invariants | Array width determines wire width; no NUL terminator is serialized. |
| ownership | Borrow lasts only through underlying text copy. |
| failure | Relies on Writer interval preconditions. |
| cost | O(N), no separate dynamic copy. |
| Design | [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/recovery/plan_descriptor.hpp](../../../../../include/crown/recovery/plan_descriptor.hpp), [src/runtime/session.cpp § QuerySession::lock_generation_recovery](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § QuerySession::publish_reoptimization](../../../../../src/runtime/session.cpp) |

```text
void word(std::uint64_t value,unsigned width=8)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit a bounded internal little-endian word. |
| inputs / outputs | u64, default width8 or known width2 in; advances writer offset. |
| invariants | Inspected calls use width2/8 and already sized output; no per-word guard is required for those private constants. |
| ownership | Uses only vector-owned output and scalar locals. |
| failure | Invalid internal width/bounds would violate preconditions; external descriptor fields cannot choose width. |
| cost | O(width) stores and shifts, no allocation. |
| Design | [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/recovery/plan_descriptor.hpp](../../../../../include/crown/recovery/plan_descriptor.hpp), [src/runtime/session.cpp § QuerySession::lock_generation_recovery](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § QuerySession::publish_reoptimization](../../../../../src/runtime/session.cpp) |

```text
void image(const ImageBinding& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write the fixed344-byte binding representation. |
| inputs / outputs | Physical/source64-byte SHA, catalog u64 and26 u64 policies. |
| invariants | Caller validated binding and reserved this exact layout before invoking. |
| ownership | Copies all fields into the private output buffer. |
| failure | No new validation or account growth. |
| cost | Fixed344 bytes of stores/copies. |
| Design | [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/recovery/plan_descriptor.hpp](../../../../../include/crown/recovery/plan_descriptor.hpp), [src/runtime/session.cpp § QuerySession::lock_generation_recovery](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § QuerySession::publish_reoptimization](../../../../../src/runtime/session.cpp) |

## B0010

[Lines 57–71](../../../../../src/recovery/plan_descriptor.cpp#L57); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Reader {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Track bounded slices of descriptor framing or selection payload. |
| inputs / outputs | Immutable bytes and offset0. |
| invariants | Slice ownership remains external; every text read bounds-checks before cursor movement. Complete outer checksum/length validation precedes selection parsing. |
| ownership | No owned bytes or account. |
| failure | Later failure does not rewind earlier reads. |
| cost | Fixed state; no successful-path allocation. |
| Design | [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/recovery/plan_descriptor.hpp](../../../../../include/crown/recovery/plan_descriptor.hpp), [src/runtime/session.cpp § QuerySession::lock_generation_recovery](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § QuerySession::publish_reoptimization](../../../../../src/runtime/session.cpp) |

```text
std::string_view text(std::uint64_t size)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the next descriptor interval after overflow-safe remaining-length validation. |
| inputs / outputs | u64 count in; string_view out and offset advances. |
| invariants | offset&lt;=bytes.size and size&lt;=remaining prove safe size_t narrowing and substring bounds. |
| ownership | Returned slice aliases immutable descriptor. |
| failure | ImageFault::corrupt before this cursor advance; no partial slice return. |
| cost | O(1) arithmetic/view construction; actual hash/copy costs are separate. |
| Design | [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/recovery/plan_descriptor.hpp](../../../../../include/crown/recovery/plan_descriptor.hpp), [src/runtime/session.cpp § QuerySession::lock_generation_recovery](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § QuerySession::publish_reoptimization](../../../../../src/runtime/session.cpp) |

```text
template<std::size_t N> void text(std::array
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy a checked fixed field into owned metadata. |
| inputs / outputs | Mutable fixed array out, next N wire bytes in. |
| invariants | text(N) bounds checking precedes copy. Alphabet/lineage checks follow in validate. |
| ownership | Result array owns its bytes independent of descriptor. |
| failure | Truncation propagates before copying this field; earlier fields may have been filled in the private result. |
| cost | O(N) copy; no allocation. |
| Design | [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/recovery/plan_descriptor.hpp](../../../../../include/crown/recovery/plan_descriptor.hpp), [src/runtime/session.cpp § QuerySession::lock_generation_recovery](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § QuerySession::publish_reoptimization](../../../../../src/runtime/session.cpp) |

```text
std::uint64_t word(unsigned width=8)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a private fixed-width unsigned word in little-endian order. |
| inputs / outputs | Width2/8 selected by codec in; u64 out. |
| invariants | Width&lt;=8 is a private precondition; text checks available bytes. |
| ownership | Only a temporary borrowed slice and scalar accumulator. |
| failure | Truncation propagates; cursor is consumed once text succeeds. |
| cost | O(width), no separate work debit beyond admitted4*frame reserve. |
| Design | [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/recovery/plan_descriptor.hpp](../../../../../include/crown/recovery/plan_descriptor.hpp), [src/runtime/session.cpp § QuerySession::lock_generation_recovery](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § QuerySession::publish_reoptimization](../../../../../src/runtime/session.cpp) |

```text
void image(ImageBinding& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the fixed binding fields into a metadata record. |
| inputs / outputs | Reader bytes in; physical/source hashes, catalog and policy in destination. |
| invariants | Wire widths are fixed; semantic/syntax policy validation is performed after read_selection. |
| ownership | Destination arrays/scalars own all binding data. |
| failure | Truncation can leave private value partly filled; it never escapes a failed inspector. |
| cost | Fixed344-byte decode, no dynamic owner. |
| Design | [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/recovery/plan_descriptor.hpp](../../../../../include/crown/recovery/plan_descriptor.hpp), [src/runtime/session.cpp § QuerySession::lock_generation_recovery](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § QuerySession::publish_reoptimization](../../../../../src/runtime/session.cpp) |

## B0011

[Lines 72–79](../../../../../src/recovery/plan_descriptor.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void write_selection(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write selection metadata in the version/flag-defined order. |
| inputs / outputs | Validated PlanSelection and sized Writer in. |
| invariants | Predecessor optional delivery/plan precede source/target; version-dependent switch epoch precedes optional sink origin. Overhead calculation must match this exact ordering. |
| ownership | Copies fixed DTO values; retains none. |
| failure | No account growth; relies on validated input and sizing preconditions. |
| cost | Fixed840 base metadata bytes plus present112/64/496/8-byte additions, excluding header, artifact length/content and checksum. |
| Design | [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/recovery/plan_descriptor.hpp](../../../../../include/crown/recovery/plan_descriptor.hpp), [src/runtime/session.cpp § QuerySession::lock_generation_recovery](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § QuerySession::publish_reoptimization](../../../../../src/runtime/session.cpp) |

## B0012

[Lines 80–88](../../../../../src/recovery/plan_descriptor.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PlanSelection read_selection(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconstruct fixed selection DTO fields using already checked flags/version. |
| inputs / outputs | Reader, bits0..7 and switched_epoch flag in; PlanSelection out. |
| invariants | Presence bits/version determine exact field order; this routine only parses, then inspect invokes validate and exact payload exhaustion. |
| ownership | Returned optional arrays/records are fixed owning values. |
| failure | Truncation may interrupt private assembly; no partial output escapes. |
| cost | Fixed metadata visits proportional to present optional variants; no artifact parse. |
| Design | [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/recovery/plan_descriptor.hpp](../../../../../include/crown/recovery/plan_descriptor.hpp), [src/runtime/session.cpp § QuerySession::lock_generation_recovery](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § QuerySession::publish_reoptimization](../../../../../src/runtime/session.cpp) |

## B0013

[Lines 89–89](../../../../../src/recovery/plan_descriptor.cpp#L89); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L89-L89:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/plan_descriptor.cpp](../../../../../src/recovery/plan_descriptor.cpp), [docs/code_specs/files/src/recovery/plan_descriptor.cpp.md](plan_descriptor.cpp.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md) |

## B0014

[Lines 90–101](../../../../../src/recovery/plan_descriptor.cpp#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
EncodedPlanDescriptor encode_plan_descriptor(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze bounded selection metadata and opaque compiler bytes into one funded frame. |
| inputs / outputs | Account, PlanSelection, nonempty artifact and limits in; EncodedPlanDescriptor out. |
| invariants | Overhead932+delivery112+predecessor-plan64+sink-origin496+switch-epoch8; checked total/4x work and metadata validation precede allocation. v1/v2 is chosen by switch-epoch presence. |
| ownership | One sized ImageVector owns account-funded bytes. Input artifact/selection remain borrowed during the call. |
| failure | Limit/work/binding errors before allocation; allocation/private layout failure unwinds. No file publication or compiler checking is attempted. |
| cost | O(frame bytes) zero-initialization, field/artifact copy and SHA of all but trailing64;4*frame admission reserve, rows0. |
| Design | [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/recovery/plan_descriptor.hpp](../../../../../include/crown/recovery/plan_descriptor.hpp), [src/runtime/session.cpp § QuerySession::lock_generation_recovery](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § QuerySession::publish_reoptimization](../../../../../src/runtime/session.cpp) |

## B0015

[Lines 102–114](../../../../../src/recovery/plan_descriptor.cpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InspectedPlanDescriptor inspect_plan_descriptor(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate full descriptor framing and expose immutable compiler input for separate replay. |
| inputs / outputs | Borrowed descriptor and limits in; fixed selection, borrowed artifact, statistics out. |
| invariants | Admit4*bytes first; check minimum/magic/trailing SHA, version1/2, bits&lt;=7/body size, selection continuity, nonempty bounded artifact and exact exhaustion. The outer root separately binds whole descriptor bytes. |
| ownership | Selection owns metadata; compiler_artifact aliases input until compiler admission finishes. Caller must keep full frame immutable/alive. |
| failure | ImageFailure before native publication; no successful-path account/heap graph. Caller-edited return fields are not authority. |
| cost | O(frame bytes) SHA plus bounded metadata parsing and constant artifact slicing; compiler parse/rebuild cost is separate. |
| Design | [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/recovery/plan_descriptor.hpp](../../../../../include/crown/recovery/plan_descriptor.hpp), [src/runtime/session.cpp § QuerySession::lock_generation_recovery](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § QuerySession::publish_reoptimization](../../../../../src/runtime/session.cpp) |

## B0016

[Lines 115–115](../../../../../src/recovery/plan_descriptor.cpp#L115); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L115-L115:sha256:95bcfbb6661a8958a33a82a5dc501f63202f4524486b8395aa4ce785f3c26b07
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::recovery at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/plan_descriptor.cpp](../../../../../src/recovery/plan_descriptor.cpp), [docs/code_specs/files/src/recovery/plan_descriptor.cpp.md](plan_descriptor.cpp.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md) |
