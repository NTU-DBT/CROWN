# `include/crown/runtime/topk.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/topk.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Declare exact snapshot rank keys, compressed result identity, finite grants and SQL runtime overloads.

Snapshot SHA-256: `3617af77b50004dc95896379b2e9249edb114740aa03dc15cb11830236f586eb`. 58 lines partitioned into 12 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [topk](../../../../subsystem_contracts.md#topk). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/topk.md](../../../../../topk.md), [Refactor.md](../../../../../../Refactor.md), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/aggregates.md](../../../../../aggregates.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../../include/crown/runtime/topk.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 6–6](../../../../../../include/crown/runtime/topk.hpp#L6) | Type/record definition: enum class Direction |  · [reviewed contract](#b0002) |
| [B0003 · 7–7](../../../../../../include/crown/runtime/topk.hpp#L7) | Type/record definition: enum class NullOrder |  · [reviewed contract](#b0003) |
| [B0004 · 8–9](../../../../../../include/crown/runtime/topk.hpp#L8) | Explanatory comments or spacing. | source comment (unverified): // Zero-based SQL output field. NULL placement is independent of direction. · [reviewed contract](#b0004) |
| [B0005 · 10–14](../../../../../../include/crown/runtime/topk.hpp#L10) | Type/record definition: struct Key | source comment (unverified): // Zero-based SQL output field. NULL placement is independent of direction. · [reviewed contract](#b0005) |
| [B0006 · 15–19](../../../../../../include/crown/runtime/topk.hpp#L15) | Type/record definition: struct Limits | source comment (unverified): // Compressed output tuples or aggregate groups. · [reviewed contract](#b0006) |
| [B0007 · 20–22](../../../../../../include/crown/runtime/topk.hpp#L20) | Explanatory comments or spacing. | source comment (unverified): // Rows use the full nullable output tuple as identity. Aggregates keep the full · [reviewed contract](#b0007) |
| [B0008 · 23–26](../../../../../../include/crown/runtime/topk.hpp#L23) | Type/record definition: struct Entry | source comment (unverified): // Rows use the full nullable output tuple as identity. Aggregates keep the full · [reviewed contract](#b0008) |
| [B0009 · 27–29](../../../../../../include/crown/runtime/topk.hpp#L27) | Type/record definition: struct Metrics |  · [reviewed contract](#b0009) |
| [B0010 · 30–32](../../../../../../include/crown/runtime/topk.hpp#L30) | declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Owning compact output and genuine immutable schema retain the original query · [reviewed contract](#b0010) |
| [B0011 · 33–39](../../../../../../include/crown/runtime/topk.hpp#L33) | Type/record definition: struct Snapshot | source comment (unverified): // Owning compact output and genuine immutable schema retain the original query · [reviewed contract](#b0011) |
| [B0012 · 40–58](../../../../../../include/crown/runtime/topk.hpp#L40) | declares namespace scope; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::runtime::topk · [reviewed contract](#b0012) |

## B0001

[Lines 1–5](../../../../../../include/crown/runtime/topk.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L5:sha256:b8e32b5839da4f1cabef2a783491b42b8ab380eed8594714ffb119c02f66cf20
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the optional exact snapshot top-k interface and its genuine SQL/accounted output dependencies. |
| inputs / outputs | Compile-time include/namespace setup; no query is opened or admitted by including this header. |
| invariants | Types belong to crown::runtime::topk; genuine row/aggregate schemas and Tuple/account containers come from existing APIs. |
| ownership | Includes and namespace declarations own no runtime object. |
| failure | No runtime failure behavior; compilation requires the included declarations. |
| cost | Compile-time declarations only; no query-update instruction or allocation. |
| Design | [docs/topk.md](../../../../../topk.md), [Refactor.md](../../../../../../Refactor.md) |

## B0002

[Lines 6–6](../../../../../../include/crown/runtime/topk.hpp#L6); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L6-L6:sha256:fac06b94495aeadb169a0a89c0dd17775dac59382b3b8384af649df5b1569d80
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the two admitted present-value ranking directions. |
| inputs / outputs | Direction::ascending or Direction::descending configures one Key. |
| invariants | Direction reverses present scalar order only. validate rejects arbitrary unsupported enum casts. |
| ownership | Value enum; no owning state. |
| failure | The enum itself performs no validation; operator admission reports invalid values as topk_order. |
| cost | Fixed-size metadata; one admission comparison sequence per key. |
| Design | [docs/topk.md](../../../../../topk.md), [Refactor.md](../../../../../../Refactor.md) |

## B0003

[Lines 7–7](../../../../../../include/crown/runtime/topk.hpp#L7); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L7-L7:sha256:220b3aa0731a0105683b174eab8c0c3b33755927b65a0f14ee79706becea0379
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name explicit NULL placement independently from scalar direction. |
| inputs / outputs | NullOrder::first or NullOrder::last configures one Key. |
| invariants | DESC does not reverse the declared NULL placement; identity ties always use NULL first. |
| ownership | Value enum; no owning state. |
| failure | Unsupported enum casts are rejected by operator validation, not by enum construction. |
| cost | Fixed-size metadata; no update-path work. |
| Design | [docs/topk.md](../../../../../topk.md), [Refactor.md](../../../../../../Refactor.md) |

## B0004

[Lines 8–9](../../../../../../include/crown/runtime/topk.hpp#L8); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L8-L9:sha256:9d71ea05afad1743e0f6955313859fdb2256aeae0954b82054543246e0665aa2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain rank-field indexing, independent NULL order and empty/repeated-key usage. |
| inputs / outputs | Source prose guides callers creating borrowed Key spans; it produces no runtime result. |
| invariants | The implementation, not this note, checks output bounds and enum values. Empty keys use identity order and repetition is admitted. |
| ownership | The comment owns no objects or borrows. |
| failure | No executable failure boundary is created by the comment. |
| cost | Prose only; key validation and comparison carry the actual costs. |
| Design | [docs/topk.md](../../../../../topk.md), [Refactor.md](../../../../../../Refactor.md) |

## B0005

[Lines 10–14](../../../../../../include/crown/runtime/topk.hpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L10-L14:sha256:af79779b1e204a0362e6325ba9bb57e5bf907ec644f95248219625969219027b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one lexicographic ranking term over rendered SQL output. |
| inputs / outputs | Zero-based output field plus direction and NULL placement; the synchronous operator reads these in span order. |
| invariants | Field must be inside the genuine output schema. Defaults are ASC and NULLS LAST; repeated fields are allowed. |
| ownership | Key is caller-owned metadata. The span is borrowed only until snapshot_topk returns and is not retained in Snapshot. |
| failure | Construction does not validate; validate charges a unit then checks field/enums before producer creation. |
| cost | Fixed metadata per term; validation is linear in terms and each comparator can visit all terms. |
| Design | [docs/topk.md](../../../../../topk.md), [Refactor.md](../../../../../../Refactor.md) |

## B0006

[Lines 15–19](../../../../../../include/crown/runtime/topk.hpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L19:sha256:62bb37cc55932acb3dec310c9df064a277f65c998d55cd2894833a68c51750ef
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Separate finite compressed-result, top-k logical-work and existing producer-work admissions. |
| inputs / outputs | Three uint64 grants configure one synchronous call; defaults are 65536 candidates and 1000000 units for each work domain. |
| invariants | Candidates are compressed tuples/groups, not expanded bag copies. Top-k work and producer_work are distinct, finite domains and neither refills per row/comparison. |
| ownership | Caller value copied for the call; all owned data still uses the original runtime account, not a new allowance. |
| failure | Zero grants are valid metadata. k=0 with empty order opens no producer; positive calls refuse actual exceeded candidate/work/producer bounds. |
| cost | Constant options storage. These logical bounds do not claim a CPU, stack, allocator or whole-process-byte bound. |
| Design | [docs/topk.md](../../../../../topk.md), [Refactor.md](../../../../../../Refactor.md) |

## B0007

[Lines 20–22](../../../../../../include/crown/runtime/topk.hpp#L20); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L22:sha256:61b36a384c5082d857356e9a92fa5fb7848e0b415ef67b4f425ed4f61ba9f6ab
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain row-versus-group result identity and compressed selected copies. |
| inputs / outputs | Usage note for Entry; row identity is its full output tuple and aggregate identity its full key. |
| invariants | Identity is query/program scoped. Omitted aggregate output keys stay in identity; \[0,m) describes indistinguishable selected bag-copy ordinals. |
| ownership | Comment only; actual Entry fields retain immutable Tuple backing. |
| failure | No runtime admission or proof authority is supplied by prose. |
| cost | No executable work; copy compression avoids work proportional to multiplicity. |
| Design | [docs/topk.md](../../../../../topk.md), [Refactor.md](../../../../../../Refactor.md) |

## B0008

[Lines 23–26](../../../../../../include/crown/runtime/topk.hpp#L23); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L26:sha256:356177aa46097e5260160385ca521071b195d4797b7fd6c8e06cdc974cf24b02
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return one selected snapshot identity with rendered values and selected multiplicity. |
| inputs / outputs | identity and values are owning immutable Tuple handles; multiplicity is a positive selected copy count for returned entries. |
| invariants | Rows retain full nullable tuple identity; groups retain complete group key with unit weight. Equal projected group values do not merge identities. |
| ownership | Handle copies share account-owned immutable payload, preserving strings and NULLs after source/cursor teardown. |
| failure | A public edited Entry is presentation data and cannot import native/recovery state. Factory failures do not expose partial entries. |
| cost | Fixed handle/counter storage and reference-count work; copying Entry does not deep-copy tuple strings. |
| Design | [docs/topk.md](../../../../../topk.md), [Refactor.md](../../../../../../Refactor.md) |

## B0009

[Lines 27–29](../../../../../../include/crown/runtime/topk.hpp#L27); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L29:sha256:fc5f7a052a53e25578ce1be00fe763ac325025ec406efd944ad9621e1de61ad3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe selected top-k logical work and collection/comparison phases. |
| inputs / outputs | Metrics contains work, candidates, comparisons, fields and scalar_bytes from the completed operator. |
| invariants | Candidates counts actual collected compressed records, including zero at k=0. Charged phase counters cannot exceed the original finite top-k work balance. |
| ownership | Returned scalar counters own no separate account or runtime authority. |
| failure | Incomplete local metrics do not escape on failure. Producer work, allocator work and observation/account history are separate. |
| cost | Constant output size. Metrics exclude CPU time and uncharged row/handle moves. |
| Design | [docs/topk.md](../../../../../topk.md), [Refactor.md](../../../../../../Refactor.md) |

## B0010

[Lines 30–32](../../../../../../include/crown/runtime/topk.hpp#L30); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L30-L32:sha256:9aa122cf365989682315761fce4863bc78676cba6c52f42d01c1e7210bbff10d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the correct genuine source-program family in an owning result. |
| inputs / outputs | Program is a variant of existing SqlRowsProgram and SqlAggregateProgram factory handles; adjacent prose describes Snapshot ownership. |
| invariants | Returned overload selects its genuine family. A caller-edited variant is not native, proof or recovery admission authority. |
| ownership | Program copies share immutable metadata and its original account, keeping output names/types live. |
| failure | The alias/prose add no runtime failure boundary or reparse operation. |
| cost | Handle/variant metadata only; no new query owner or mutable shared query state. |
| Design | [docs/topk.md](../../../../../topk.md), [Refactor.md](../../../../../../Refactor.md) |

## B0011

[Lines 33–39](../../../../../../include/crown/runtime/topk.hpp#L33); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L39:sha256:e876f0b9b65c8ec1c78408ed7efdc7261fbd4b4c0cfadbc37bce0b2c7c0848e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one ranked snapshot result and its exact request/epoch context. |
| inputs / outputs | sequence, requested_k, selected_rows, genuine program, account-funded entries and metrics are returned together. |
| invariants | selected_rows is at most requested_k and equals the sum of returned selected weights. Each entry follows requested rank keys then identity ASC NULLS FIRST. |
| ownership | OwnerAllocator output storage and immutable Tuple/program handles retain original query funding after runtime facade destruction. |
| failure | The constructor establishes presentation ownership, not query/recovery authority. Public fields may be edited only as external result data. |
| cost | O(M) retained entry metadata for M selected identities plus shared selected tuple/program backing; copying the vector can allocate on the same account. |
| Design | [docs/topk.md](../../../../../topk.md), [Refactor.md](../../../../../../Refactor.md) |

## B0012

[Lines 40–58](../../../../../../include/crown/runtime/topk.hpp#L40); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L40-L58:sha256:6faee5a02f644e6afe62e22f9b5b01fd40b2f7e5d21edd6c239cfb91e72b7ac9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the two explicit exact snapshot-sorting operations and their caller obligations. |
| inputs / outputs | A ready genuine SQL row or SQL aggregate runtime, borrowed rank span, uint64 k and finite limits yield one owning topk::Snapshot. |
| invariants | Ready admission precedes key validation, which precedes producer creation. k=0 opens no producer; no root-weight shortcut drops EXISTS false or global-empty aggregate output. |
| ownership | Serialize calls with the owner. Temporary cursor/image/candidates close locally; returned payload/schema own their backing. No new update hook or runtime owner is retained. |
| failure | Invalid order, work/candidate denial and existing producer/account failures unwind private state. Committed results/sequence remain unchanged; observations/account history may record attempted work. Diagnostics/exception storage is separate. |
| cost | Full snapshot collection plus O(N log N) comparator calls over N compressed identities, including visited field/string extents. O(N) scratch and existing producer/image costs plus O(M) retained metadata. No P10, constant-delay or SQL-clause claim. |
| Design | [docs/topk.md](../../../../../topk.md), [Refactor.md](../../../../../../Refactor.md) |
