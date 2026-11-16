# `include/crown/runtime/owner_statistics.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/owner_statistics.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Capture selected table/index distributions with owner/sequence stamps and partial-completion status.

Snapshot SHA-256: `cf2c4bfead054e3cb3326108cecd6e58925afa693d8d239a76030bf85ac1a67c`. 84 lines partitioned into 31 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../../statistics.md), [docs/observability.md](../../../../../observability.md), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../../include/crown/runtime/owner_statistics.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 7–7](../../../../../../include/crown/runtime/owner_statistics.hpp#L7) | Type/record definition: struct SourceScope |  · [reviewed contract](#b0002) |
| [B0003 · 8–8](../../../../../../include/crown/runtime/owner_statistics.hpp#L8) | Type/record definition: struct NodeScope |  · [reviewed contract](#b0003) |
| [B0004 · 9–9](../../../../../../include/crown/runtime/owner_statistics.hpp#L9) | Type/record definition: struct OccurrenceScope |  · [reviewed contract](#b0004) |
| [B0005 · 10–10](../../../../../../include/crown/runtime/owner_statistics.hpp#L10) | Type/record definition: struct IndexScope |  · [reviewed contract](#b0005) |
| [B0006 · 11–11](../../../../../../include/crown/runtime/owner_statistics.hpp#L11) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0006) |
| [B0007 · 12–19](../../../../../../include/crown/runtime/owner_statistics.hpp#L12) | Type/record definition: struct Selection | source comment (unverified): // Present fields own an ordered vector; copies may allocate before capture. · [reviewed contract](#b0007) |
| [B0008 · 20–20](../../../../../../include/crown/runtime/owner_statistics.hpp#L20) | Type/record definition: struct OwnerRequest | source comment (unverified): // Maximum 256. · [reviewed contract](#b0008) |
| [B0009 · 21–22](../../../../../../include/crown/runtime/owner_statistics.hpp#L21) | Explanatory comments or spacing. | source comment (unverified): // Synchronous borrowed input, including query-funded or fixed internal request · [reviewed contract](#b0009) |
| [B0010 · 23–28](../../../../../../include/crown/runtime/owner_statistics.hpp#L23) | Type/record definition: struct OwnerRequestView | source comment (unverified): // Synchronous borrowed input, including query-funded or fixed internal request · [reviewed contract](#b0010) |
| [B0011 · 29–33](../../../../../../include/crown/runtime/owner_statistics.hpp#L29) | Type/record definition: struct CapturedSelection |  · [reviewed contract](#b0011) |
| [B0012 · 34–34](../../../../../../include/crown/runtime/owner_statistics.hpp#L34) | Type/record definition: enum class Availability |  · [reviewed contract](#b0012) |
| [B0013 · 35–35](../../../../../../include/crown/runtime/owner_statistics.hpp#L35) | Type/record definition: enum class OwnerLayer |  · [reviewed contract](#b0013) |
| [B0014 · 36–36](../../../../../../include/crown/runtime/owner_statistics.hpp#L36) | Type/record definition: struct OwnerStamp |  · [reviewed contract](#b0014) |
| [B0015 · 37–49](../../../../../../include/crown/runtime/owner_statistics.hpp#L37) | Type/record definition: struct Component | source comment (unverified): // Population layout; explicit selection.fields describes the ordered key · [reviewed contract](#b0015) |
| [B0016 · 50–57](../../../../../../include/crown/runtime/owner_statistics.hpp#L50) | declares namespace scope; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Owning copies clone native vectors/keys on their original account. · [reviewed contract](#b0016) |
| [B0017 · 58–60](../../../../../../include/crown/runtime/owner_statistics.hpp#L58) | Callable definition: OwnerCapture& operator=(const OwnerCapture& other) | calls std::move; returns *this; source comment (unverified): // A failed owning copy must not pair a new stamp with old component facts. · [reviewed contract](#b0017) |
| [B0018 · 61–61](../../../../../../include/crown/runtime/owner_statistics.hpp#L61) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0018) |
| [B0019 · 62–62](../../../../../../include/crown/runtime/owner_statistics.hpp#L62) | Callable definition: const OwnerStamp& stamp() const noexcept | calls ; returns stamp_ · [reviewed contract](#b0019) |
| [B0020 · 63–63](../../../../../../include/crown/runtime/owner_statistics.hpp#L63) | Callable definition: const CompiledProgram& plan() const noexcept | calls ; returns plan_ · [reviewed contract](#b0020) |
| [B0021 · 64–64](../../../../../../include/crown/runtime/owner_statistics.hpp#L64) | Callable definition: Availability availability() const noexcept | calls ; returns availability_ · [reviewed contract](#b0021) |
| [B0022 · 65–65](../../../../../../include/crown/runtime/owner_statistics.hpp#L65) | Callable definition: Availability physical_source_scope() const noexcept | calls ; returns physical_source_scope_ · [reviewed contract](#b0022) |
| [B0023 · 66–66](../../../../../../include/crown/runtime/owner_statistics.hpp#L66) | Callable definition: const CaptureVector&lt;Component&gt;& components() const noexcept | calls ; returns components_ · [reviewed contract](#b0023) |
| [B0024 · 67–67](../../../../../../include/crown/runtime/owner_statistics.hpp#L67) | Callable definition: const Usage& usage() const noexcept | calls ; returns usage_ · [reviewed contract](#b0024) |
| [B0025 · 68–68](../../../../../../include/crown/runtime/owner_statistics.hpp#L68) | Callable definition: const Limits& limits() const noexcept | calls ; returns limits_ · [reviewed contract](#b0025) |
| [B0026 · 69–69](../../../../../../include/crown/runtime/owner_statistics.hpp#L69) | Callable definition: std::size_t requested_components() const noexcept | calls ; returns requested_components_ · [reviewed contract](#b0026) |
| [B0027 · 70–72](../../../../../../include/crown/runtime/owner_statistics.hpp#L70) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0027) |
| [B0028 · 73–75](../../../../../../include/crown/runtime/owner_statistics.hpp#L73) | Callable definition: OwnerCapture(OwnerStamp stamp,const CompiledProgram& plan,Limits limits,std::size_t requested) :stamp_(stamp),plan_(plan),physica… | calls stamp_, plan_, physical_source_scope_, components_ · [reviewed contract](#b0028) |
| [B0029 · 76–81](../../../../../../include/crown/runtime/owner_statistics.hpp#L76) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0029) |
| [B0030 · 82–82](../../../../../../include/crown/runtime/owner_statistics.hpp#L82) | Type/record definition: enum class Freshness |  · [reviewed contract](#b0030) |
| [B0031 · 83–84](../../../../../../include/crown/runtime/owner_statistics.hpp#L83) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0031) |

## B0001

[Lines 1–6](../../../../../../include/crown/runtime/owner_statistics.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose typed actual-owner population capture. |
| inputs / outputs | Includes SupportRole/CompiledProgram/statistics support and std::variant. |
| invariants | Capture is explicit synchronous diagnostics, separate from transaction hooks and global answer counting. |
| ownership | No runtime owner created by header inclusion. |
| failure | Compile-time dependency boundary only. |
| cost | No runtime work; actual scans/storage below are explicit. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0002

[Lines 7–7](../../../../../../include/crown/runtime/owner_statistics.hpp#L7); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SourceScope { TableId table; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select physical source rows by actual catalog table. |
| inputs / outputs | SourceScope carries one TableId. |
| invariants | ID must belong to actual physical owner catalog; support-only owners report unavailable source scope. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 8–8](../../../../../../include/crown/runtime/owner_statistics.hpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct NodeScope { NodeId node; SupportRole role; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select an actual support node population. |
| inputs / outputs | NodeScope carries NodeId and records/survivors/parent_support/visible SupportRole. |
| invariants | Records/S permit table projection; P/E expose stored support multiplicities; absent E is not_applicable, not empty exact data. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0004

[Lines 9–9](../../../../../../include/crown/runtime/owner_statistics.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct OccurrenceScope { OccurrenceId occurrence; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select actual occurrence derivation multiplicities. |
| inputs / outputs | OccurrenceScope carries an admitted OccurrenceId. |
| invariants | Physical owner reads complete native-key derivation map; another projection is rejected, support-only occurrence scope unavailable. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 10–10](../../../../../../include/crown/runtime/owner_statistics.hpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct IndexScope { IndexRequirementId requirement; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select admitted index bucket-degree population. |
| inputs / outputs | IndexScope carries actual IndexRequirementId. |
| invariants | Uses existing admitted nonempty buckets; capture never registers/builds an index and rejects another fields projection. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0006

[Lines 11–11](../../../../../../include/crown/runtime/owner_statistics.hpp#L11); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Scope=std::variant<SourceScope,NodeScope,OccurrenceScope,IndexScope>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent a typed owner-capture population selection. |
| inputs / outputs | Scope is a variant of SourceScope/NodeScope/OccurrenceScope/IndexScope. |
| invariants | Trivial tag/IDs alone do not validate source ownership or import an authentic report. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0007

[Lines 12–19](../../../../../../include/crown/runtime/owner_statistics.hpp#L12); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Selection {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own an optional ordered field request for one typed population. |
| inputs / outputs | Scope plus optional&lt;std::vector&lt;FieldId&gt;&gt;: absent requests cardinality for tables or native P/E/occurrence/index distributions; present requests table projection. |
| invariants | Empty/repeated fields are valid ordered table projections. Present fields on P/E, occurrence or index are rejected by actual owner; IDs must match real population layout. |
| ownership | Owns ordinary vector storage; copies deep-copy requested fields outside native account. Scope is fixed. |
| failure | Vector construction/copy can throw. OwnerBuilder validates count/width/IDs at capture; this record performs no admission itself. |
| cost | O(F) field copy/allocation; release deallocates one trivial-ID vector without a population/byte scan. No table scan until capture. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0008

[Lines 20–20](../../../../../../include/crown/runtime/owner_statistics.hpp#L20); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct OwnerRequest { std::vector<Selection> selections; }; // Maximum 256.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the public owner-state request sequence. |
| inputs / outputs | std::vector&lt;Selection&gt; selections; actual OwnerBuilder admits at most 256 selections. |
| invariants | The comment maximum is an enforced capture precondition, not a bounded vector implementation. Duplicate selections retain independent ordered components. |
| ownership | Owns ordinary outer vector plus each fields vector; copying deep-copies both. No live runtime or grant retained. |
| failure | Construct/copy can allocate and throw; &gt;256 rejects before scanning. |
| cost | O(N+sum F) deep copy/allocations; release visits N selections and frees their field buffers plus outer vector, with no per-field scan. Request construction scans no rows. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0009

[Lines 21–22](../../../../../../include/crown/runtime/owner_statistics.hpp#L21); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L22:sha256:ae2f9b84916895dbd5152a8f7b729fbf241f3a39f0d988d291f8fe12b2951196
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`struct OwnerRequestView\`: Synchronous borrowed input, including query-funded or fixed internal request storage. Captures retain their own native copies, never this span. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/runtime/owner_statistics.hpp:L23; use that declaration for the actual input/output shape. |
| invariants | The source note states: Synchronous borrowed input, including query-funded or fixed internal request storage. Captures retain their own native copies, never this span. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Synchronous borrowed input, including query-funded or fixed internal request storage. Captures retain their own native copies, never this span. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/statistics.md](../../../../../statistics.md), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0010

[Lines 23–28](../../../../../../include/crown/runtime/owner_statistics.hpp#L23); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct OwnerRequestView {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a synchronous owner-request selection range. |
| inputs / outputs | Default span empty; constructors view OwnerRequest.selections or supplied span. |
| invariants | Capture consumes synchronously and retains its own native copies; caller must keep selections and nested ordinary fields vectors unchanged/alive until return. |
| ownership | Span owns no selections or fields and does not extend OwnerRequest lifetime. |
| failure | View construction is fixed; dangling source is caller misuse, not an allocating fallback. |
| cost | O(1) span construction/copy; no allocation or deep copy. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
OwnerRequestView()=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an empty borrowed request view. |
| inputs / outputs | Default span contains zero selections. |
| invariants | An empty request is legal metadata-only capture, not an unavailable selection. |
| ownership | Owns only empty span bits, no backing owner. |
| failure | No allocation or validation. |
| cost | O(1). |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
OwnerRequestView(const OwnerRequest& request):selections(request.selections) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow selections from an owning public request. |
| inputs / outputs | Initializes span from request.selections, preserving order. |
| invariants | request and nested fields storage must outlive synchronous capture; temporary-to-view persistence is unsafe. |
| ownership | No ownership/refcount/copy of vectors. |
| failure | No allocation; lifetime is caller precondition. |
| cost | O(1). |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
explicit OwnerRequestView(std::span<const Selection> values):selections(values) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow fixed or query-funded internal selection storage. |
| inputs / outputs | Explicit span constructor preserves pointer/count. |
| invariants | All elements/nested fields remain alive and unchanged during use; span does not prove account/owner authority. |
| ownership | No storage retained beyond borrowed span bits. |
| failure | No allocation/validation. |
| cost | O(1). |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0011

[Lines 29–33](../../../../../../include/crown/runtime/owner_statistics.hpp#L29); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CapturedSelection {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a native copy of one selected scope/ordered field list. |
| inputs / outputs | Scope fixed value plus optional&lt;CaptureVector&lt;FieldId&gt;&gt;; constructor copies a public Selection on supplied account. |
| invariants | Preserves absent vs engaged-empty projection and exact field order; not an independent validation of those IDs. |
| ownership | Owns original-account capture/2 fields vector. Copies can allocate/deep-copy; OwnerAllocator moves/assignments carry account/storage. |
| failure | Field allocation/copy may throw; partial object cleanup preserves source. |
| cost | O(F) funded copy; release deallocates one trivial-ID buffer. Empty/absent fields need no field payload, no population scan. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../../include/crown/resource/owner_allocator.hpp) |

```text
CapturedSelection(const Selection&,const resource::MemoryAccount&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy a borrowed/public selection into funded report storage. |
| inputs / outputs | Copies scope, and when fields engaged constructs CaptureVector from exact iterator range with capture allocator(account). |
| invariants | Engaged empty remains engaged empty; caller already budget-charged projected FieldId payload in OwnerBuilder::append. |
| ownership | Receiver owns field vector on supplied original account; source not retained. |
| failure | Copy allocation failure aborts append/report; this constructor does not translate OOM to budget-exhausted. |
| cost | O(F) field copy/allocation; fixed scope copy. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp) |

## B0012

[Lines 34–34](../../../../../../include/crown/runtime/owner_statistics.hpp#L34); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Availability { available, budget_exhausted, pending_private_state, unavailable, not_applicable };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Qualify owner report applicability, admission and completeness. |
| inputs / outputs | available/budget_exhausted/pending_private_state/unavailable/not_applicable. |
| invariants | Missing/unknown is not exact zero. A component can retain exact cardinality even when its requested distribution exhausts. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Constant-size tag; no runtime allocation, work scan or clock. Invalid casts are not automatically checked by this declaration. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0013

[Lines 35–35](../../../../../../include/crown/runtime/owner_statistics.hpp#L35); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class OwnerLayer { support, physical };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind owner-state evidence to support or physical layer. |
| inputs / outputs | OwnerLayer tags support/physical. |
| invariants | Same support owner ID at another layer is scope_mismatch, not current equivalent population. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Constant-size tag; no runtime allocation, work scan or clock. Invalid casts are not automatically checked by this declaration. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0014

[Lines 36–36](../../../../../../include/crown/runtime/owner_statistics.hpp#L36); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct OwnerStamp { SupportOwnerId owner; std::uint64_t sequence; OwnerLayer layer; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stamp capture with actual committed owner sequence. |
| inputs / outputs | SupportOwnerId, committed sequence, OwnerLayer copied from actual runtime. |
| invariants | Storage revision can advance during rollback; only owner committed sequence is used for owner freshness. Public OwnerStamp fields alone do not mint OwnerCapture authority. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0015

[Lines 37–49](../../../../../../include/crown/runtime/owner_statistics.hpp#L37); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Component {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one selected population report and its applicability/quality facts. |
| inputs / outputs | Native CapturedSelection; availability; optional NodeKind/layout/cardinality/CapturedDistribution/storage-invalidation Stamp. |
| invariants | Population layout and ordered projection fields are distinct. Incomplete distribution keeps visited progress but NDV/top-K unknown and histogram empty; storage stamp is invalidation only. |
| ownership | Owns native fields/distribution arrays and captured heavy-key rows; layout shares immutable descriptor token. Copying deep-copies native arrays/keys and retains layout owner. |
| failure | Owning copies can allocate/throw. Capture maps only actual logical/storage-work exhaustion to incomplete; corruption/ownership/OOM propagate at owner boundary. |
| cost | Copy O(fields+histogram+heavy key bytes); release visits heavy-key owners and frees fields/histogram/row blocks plus last layout metadata. Actual distribution construction scans/groups/sorts explicitly. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [include/crown/storage/layout.hpp](../../../../../../include/crown/storage/layout.hpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp) |

## B0016

[Lines 50–57](../../../../../../include/crown/runtime/owner_statistics.hpp#L50); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class OwnerCapture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a factory-created detached actual-owner state report. |
| inputs / outputs | OwnerBuilder supplies real stamp, plan and ordered components plus Usage/Limits/request count; callers receive const accessor views. |
| invariants | Private construction and actual owner scan establish report authority, not labels/DTO numbers. Pending returns metadata-only; completed components remain detached across later runtime changes. |
| ownership | Owns funded component/field/distribution/row vectors plus shared plan/layout metadata. This is an owning value, not merely a shared handle; copies allocate/deep-copy. |
| failure | Copies can throw. Copy assignment prepares a full temporary before noexcept move publication. No runtime state is mutated by report copy or destruction. |
| cost | Deep copy O(N+fields+histogram+heavy-key bytes), original-account source/destination overlap. Release visits components and retained heavy keys and deallocates their buffers, not every string/field byte; getters O(1). |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/resource/owner_allocator.hpp](../../../../../../include/crown/resource/owner_allocator.hpp), [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp) |

```text
OwnerCapture(const OwnerCapture&)=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deep-copy an OwnerCapture on its original report account. |
| inputs / outputs | Default copy duplicates components and nested owning distribution/field/key values, retaining immutable plan/layout handles. |
| invariants | Copied stamp/facts remain paired; later owner writes do not update either report. |
| ownership | OwnerAllocator copies use source original account. CapturedKey copy clones row bytes, not a borrowed view. |
| failure | Allocation failure destroys incomplete new report; source intact. |
| cost | O(all retained report payload) allocation/copy; no live-owner scan or new allowance. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp) |

```text
OwnerCapture(OwnerCapture&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move-construct owning OwnerCapture storage. |
| inputs / outputs | Default noexcept move transfers component vectors/account and shared plan handle; scalars remain ordinary moved-from values. |
| invariants | Moved-from report is destructible/assignable; no guarantee its plan accessor remains valid. |
| ownership | Destination adopts native report storage; source does not retain a duplicate payload. |
| failure | noexcept. |
| cost | Fixed vector/plan transfer; no deep copy or new allocation. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0017

[Lines 58–60](../../../../../../include/crown/runtime/owner_statistics.hpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
OwnerCapture& operator=(const OwnerCapture& other) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy-assign a report with paired stamp/facts publication. |
| inputs / outputs | Self-check; build next(other), then move-assign into destination and return *this. |
| invariants | A failed deep copy cannot pair the source stamp with old destination components. |
| ownership | Temporary owns a complete original-account copy; successful publication frees old destination payload. |
| failure | Only private copy construction may throw; destination unchanged before it completes, move publication noexcept. |
| cost | O(new report payload) copy plus old report cleanup, simultaneous old/new/source retention; no redundant catch. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0018

[Lines 61–61](../../../../../../include/crown/runtime/owner_statistics.hpp#L61); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
OwnerCapture& operator=(OwnerCapture&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move-assign a report and its original allocation owner together. |
| inputs / outputs | Default noexcept move replaces stamp/plan/components/usage/limits/request count. |
| invariants | OwnerAllocator propagation prevents account mismatch element-copy fallback. Source is only promised normal moved-from validity. |
| ownership | Adopts source vectors/account; releases destination old components/plan. |
| failure | noexcept. |
| cost | O(1) transfer plus destruction of old report payload; no new allocation. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/resource/owner_allocator.hpp](../../../../../../include/crown/resource/owner_allocator.hpp) |

## B0019

[Lines 62–62](../../../../../../include/crown/runtime/owner_statistics.hpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const OwnerStamp& stamp() const noexcept { return stamp_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow OwnerCapture actual owner stamp. |
| inputs / outputs | Returns const OwnerStamp& from this report. |
| invariants | Actual committed owner sequence/layer, distinct from storage revision. |
| ownership | Reference borrows this OwnerCapture; copying a reference does not retain report/native vectors or plan. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0020

[Lines 63–63](../../../../../../include/crown/runtime/owner_statistics.hpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const CompiledProgram& plan() const noexcept { return plan_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow OwnerCapture admitted plan. |
| inputs / outputs | Returns const CompiledProgram& from this report. |
| invariants | Owns plan metadata used for selection IDs/layouts; no runtime pointer. |
| ownership | Reference borrows this OwnerCapture; copying a reference does not retain report/native vectors or plan. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0021

[Lines 64–64](../../../../../../include/crown/runtime/owner_statistics.hpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Availability availability() const noexcept { return availability_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read OwnerCapture overall availability. |
| inputs / outputs | Returns Availability by value. |
| invariants | Aggregates budget exhaustion but does not erase earlier components; pending metadata-only is distinct. |
| ownership | Independent scalar; report owns payload during read. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0022

[Lines 65–65](../../../../../../include/crown/runtime/owner_statistics.hpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Availability physical_source_scope() const noexcept { return physical_source_scope_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read OwnerCapture physical source scope availability. |
| inputs / outputs | Returns Availability by value. |
| invariants | Physical layer initializes available; support layer initializes unavailable. Component availability still controls actual selected facts. |
| ownership | Independent scalar; report owns payload during read. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0023

[Lines 66–66](../../../../../../include/crown/runtime/owner_statistics.hpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const CaptureVector<Component>& components() const noexcept { return components_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow OwnerCapture ordered captured components. |
| inputs / outputs | Returns const CaptureVector&lt;Component&gt;& from this report. |
| invariants | May be fewer than requested if metadata budget exhausted; inspect component statuses. |
| ownership | Reference borrows this OwnerCapture; copying a reference does not retain report/native vectors or plan. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0024

[Lines 67–67](../../../../../../include/crown/runtime/owner_statistics.hpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Usage& usage() const noexcept { return usage_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow OwnerCapture logical processing usage. |
| inputs / outputs | Returns const Usage& from this report. |
| invariants | Work/payload model excludes allocator framing/capacity and caller copy costs. |
| ownership | Reference borrows this OwnerCapture; copying a reference does not retain report/native vectors or plan. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0025

[Lines 68–68](../../../../../../include/crown/runtime/owner_statistics.hpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Limits& limits() const noexcept { return limits_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow OwnerCapture requested processing limits. |
| inputs / outputs | Returns const Limits& from this report. |
| invariants | These logical limits are independent of actual query MemoryAccount cap. |
| ownership | Reference borrows this OwnerCapture; copying a reference does not retain report/native vectors or plan. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0026

[Lines 69–69](../../../../../../include/crown/runtime/owner_statistics.hpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t requested_components() const noexcept { return requested_components_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read OwnerCapture requested component count. |
| inputs / outputs | Returns size_t by value. |
| invariants | Original request length remains visible when an exhausted report contains a prefix. |
| ownership | Independent scalar; report owns payload during read. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0027

[Lines 70–72](../../../../../../include/crown/runtime/owner_statistics.hpp#L70); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static constexpr std::uint32_t format_version=1;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Version the owner-report representation and restrict its factory. |
| inputs / outputs | format_version=1 and private OwnerBuilder friendship follow const public getters. |
| invariants | The marker alone grants no current-owner/freshness authority; private factory binds actual runtime state. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0028

[Lines 73–75](../../../../../../include/crown/runtime/owner_statistics.hpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
OwnerCapture(OwnerStamp stamp,const CompiledProgram& plan,Limits limits,std::size_t requested)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an empty private owner report from actual owner/plan. |
| inputs / outputs | Stamp, CompiledProgram, Limits and request count initialize report; physical source scope available only for physical layer. |
| invariants | Called only by OwnerBuilder before its shared budget validation/reservation; no components fabricated by constructor. |
| ownership | Retains plan/shared account, binds empty capture/2 component allocator to plan.account(); no component payload allocated here. |
| failure | Invalid/unreadable plan account access can throw; real runtime factories pass admitted plan. No local catch. |
| cost | Fixed plan/account refcount and scalars; no row scan or vector reserve. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp) |

## B0029

[Lines 76–81](../../../../../../include/crown/runtime/owner_statistics.hpp#L76); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
OwnerStamp stamp_; CompiledProgram plan_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store owned report payload and independent scope/budget facts. |
| inputs / outputs | Private stamp/plan/status/source-scope/components/Usage/Limits/request count back const getters. |
| invariants | Only OwnerBuilder mutates these before return. Report copies remain detached; private construction prevents arbitrary public DTO relabeling. |
| ownership | Components own nested native vectors/rows, layout shares descriptor; plan retains admitted graph/original account. |
| failure | Last destruction releases all actual nested payload; no runtime rollback or rescue allocation. |
| cost | Storage proportional to selected report output; release visits vectors/keys and possible last metadata graph, not a constant shared-handle release. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0030

[Lines 82–82](../../../../../../include/crown/runtime/owner_statistics.hpp#L82); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Freshness { current, within_lag, stale, foreign_owner, future_sequence, scope_mismatch };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify owner-stamp freshness without a scan. |
| inputs / outputs | current/within_lag/stale/foreign_owner/future_sequence/scope_mismatch. |
| invariants | Freshness concerns captured committed event lag, not storage invalidation, equal rows or a cost-model prediction. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Constant-size tag; no runtime allocation, work scan or clock. Invalid casts are not automatically checked by this declaration. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0031

[Lines 83–84](../../../../../../include/crown/runtime/owner_statistics.hpp#L83); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Freshness compare_freshness(const OwnerStamp& captured,const OwnerStamp& actual,std::uint64_t max_event_lag);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare actual committed owner stamps with an admitted lag bound. |
| inputs / outputs | Compare captured owner first, then layer, then future/equal sequence; otherwise subtraction &lt;= max_event_lag gives within_lag, else stale. |
| invariants | Ordered future check prevents unsigned underflow. Public helper compares supplied stamps only; actual runtime statistics_freshness provides live actual stamp. |
| ownership | Pure scalar read/result; neither report nor runtime retained. |
| failure | No allocation/catch; declaration is not noexcept but implementation has no throwing operations. |
| cost | O(1), no table scan/clock. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |
