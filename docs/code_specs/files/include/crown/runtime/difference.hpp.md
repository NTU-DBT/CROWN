# `include/crown/runtime/difference.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/difference.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Declare independent exact difference ownership, compressed checked counts and exact endpoint replacements distinct from aggregate payloads.

Snapshot SHA-256: `5c2f74cfe8cb1fcba08325bf4524f6d105d0c767fccfc6f8a353bc26e653557e`. 112 lines partitioned into 16 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [difference](../../../../subsystem_contracts.md#difference). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/difference.md](../../../../../difference.md), [docs/source_images.md](../../../../../source_images.md), [docs/annotations.md](../../../../../annotations.md), [Refactor.md](../../../../../../Refactor.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../../include/crown/runtime/difference.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 12–16](../../../../../../include/crown/runtime/difference.hpp#L12) | Type/record definition: struct Limits | source comment (unverified): // One metadata/image/both-operands/residual/delta balance. · [reviewed contract](#b0002) |
| [B0003 · 17–21](../../../../../../include/crown/runtime/difference.hpp#L17) | Type/record definition: struct Options | source comment (unverified): // Positive W01 checked-uint64 domain. · [reviewed contract](#b0003) |
| [B0004 · 22–25](../../../../../../include/crown/runtime/difference.hpp#L22) | Type/record definition: struct Metrics : fallback::Metrics |  · [reviewed contract](#b0004) |
| [B0005 · 26–26](../../../../../../include/crown/runtime/difference.hpp#L26) | Type/record definition: struct SignedMagnitude |  · [reviewed contract](#b0005) |
| [B0006 · 27–27](../../../../../../include/crown/runtime/difference.hpp#L27) | Type/record definition: struct Entry |  · [reviewed contract](#b0006) |
| [B0007 · 28–34](../../../../../../include/crown/runtime/difference.hpp#L28) | Type/record definition: struct Change | returns {after &lt; before, {after &lt; before ? before.value - after.value : after.value - before.value}}; source comment (unverified): // Exact nonnegative endpoint replacement; zero means absent. · [reviewed contract](#b0007) |
| [B0008 · 35–43](../../../../../../include/crown/runtime/difference.hpp#L35) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Both actual original positive CQs, mode/arithmetic and the LEFT headed result · [reviewed contract](#b0008) |
| [B0009 · 44–44](../../../../../../include/crown/runtime/difference.hpp#L44) | Callable definition: \[\[nodiscard\]\] explicit operator bool() const noexcept | calls ; returns bool(data_) · [reviewed contract](#b0009) |
| [B0010 · 45–59](../../../../../../include/crown/runtime/difference.hpp#L45) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0010) |
| [B0011 · 60–60](../../../../../../include/crown/runtime/difference.hpp#L60) | Callable definition: explicit Binding(std::shared_ptr&lt;const Data&gt; data) noexcept : data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0011) |
| [B0012 · 61–65](../../../../../../include/crown/runtime/difference.hpp#L61) | declares aliases; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0012) |
| [B0013 · 66–66](../../../../../../include/crown/runtime/difference.hpp#L66) | Type/record definition: struct Snapshot |  · [reviewed contract](#b0013) |
| [B0014 · 67–67](../../../../../../include/crown/runtime/difference.hpp#L67) | Type/record definition: struct Epoch |  · [reviewed contract](#b0014) |
| [B0015 · 68–76](../../../../../../include/crown/runtime/difference.hpp#L68) | Type/record definition: struct Explain |  · [reviewed contract](#b0015) |
| [B0016 · 77–112](../../../../../../include/crown/runtime/difference.hpp#L77) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // One full-catalog physical SET source owner. Complete physical-row choices · [reviewed contract](#b0016) |

## B0001

[Lines 1–11](../../../../../../include/crown/runtime/difference.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:3c317a229cab2a79674cfddb28077f2a2d487d0dcfd423418465d79ee15a1c8d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the explicit pair-CQ difference runtime vocabulary. |
| inputs / outputs | Imports admitted difference/fallback APIs and aliases planner Mode/Profile and W01 Multiplicity. |
| invariants | Mode is explicitly SET EXCEPT or BAG EXCEPT ALL over physical SET sources. |
| ownership | Aliases/includes create no query, source or output owner. |
| failure | Declaration alone executes no admission/evaluation. |
| cost | Compile-time setup only. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/runtime/difference.hpp](../../../../../../include/crown/runtime/difference.hpp), [include/crown/planner/difference.hpp](../../../../../../include/crown/planner/difference.hpp), [include/crown/annotations/policy.hpp](../../../../../../include/crown/annotations/policy.hpp) |

## B0002

[Lines 12–16](../../../../../../include/crown/runtime/difference.hpp#L12); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L12-L16:sha256:81750ccb06eacb3fdbc7c60de9a72b182bba7eb3d4d2e9ed31ba49744fb1aa25
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound composed exact recomputation and each operand key domain. |
| inputs / outputs | Limits sets one work balance, total full-source image row cap and distinct keys PER operand. |
| invariants | One constructor import/initial answer or one capture/both-operand/residual/delta operation shares work; residual keys are a subset of left; union scratch may hold twice rows. |
| ownership | Plain limits mint neither a memory account nor an indexed-source lease. |
| failure | Insufficient work/source rows/operand keys refuses before publication. |
| cost | Fixed configuration storage; selected work units are not elapsed-time or allocator/cleanup bounds. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/runtime/difference.hpp](../../../../../../include/crown/runtime/difference.hpp) |

## B0003

[Lines 17–21](../../../../../../include/crown/runtime/difference.hpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L21:sha256:f5b0aaf1e7680d9ea256e2f6d28c5431b3a5912fe3c32994fcc37ed073b7ceaa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Combine the original physical source policy with exact wrapper/count ceilings. |
| inputs / outputs | Options contains PhysicalRuntimeOptions, recompute limits and positive checked uint64 multiplicity_limit. |
| invariants | Full catalog constraints/backend/account stay on one source owner; W01 count limit applies to each operand key before subtraction. |
| ownership | Options retains values, not a source image or second query account. |
| failure | Zero multiplicity limit is invalid_annotation; overflow is annotation_overflow even if later subtraction would cancel. |
| cost | Value setup only; native source policy work remains separately inherited. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/runtime/difference.hpp](../../../../../../include/crown/runtime/difference.hpp), [include/crown/annotations/policy.hpp](../../../../../../include/crown/annotations/policy.hpp) |

## B0004

[Lines 22–25](../../../../../../include/crown/runtime/difference.hpp#L22); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L25:sha256:0dd07c4d20d830bd6cea5db470389bb332da5999a78e0b9a8cbee7b1d2dda5ea
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report full-witness work and compressed endpoint results separately. |
| inputs / outputs | Extends fallback Metrics with per-operand assignments/keys and endpoint replacement count. |
| invariants | Assignments count complete physical-row choices, keys count DISTINCT projected rows; changes count unequal before/after pairs. |
| ownership | Counters contain no borrowed rows or account owner. |
| failure | Failed private work publishes no result Metrics and does not refund consumed operation units. |
| cost | Fixed counters plus explicitly admitted traversal/comparison/copy work; not a wall-clock theorem. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/runtime/difference.hpp](../../../../../../include/crown/runtime/difference.hpp) |

## B0005

[Lines 26–26](../../../../../../include/crown/runtime/difference.hpp#L26); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L26:sha256:a6faca8e32dc51836338ce33818f77c17a41cc855566e3cf5e64b263498eb0e7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent an optional signed difference without int64 narrowing. |
| inputs / outputs | SignedMagnitude carries sign and unsigned W01 magnitude. |
| invariants | Magnitude is a nonnegative count delta; this is not an aggregate annotation payload. |
| ownership | POD owns no tuple or allocation. |
| failure | No executable failure. |
| cost | Fixed two-field value storage. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/runtime/difference.hpp](../../../../../../include/crown/runtime/difference.hpp) |

## B0006

[Lines 27–27](../../../../../../include/crown/runtime/difference.hpp#L27); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L27:sha256:e5e2adb189fabeda581c3d09bbe9f2f1e647b92b5feacc3e6447b6e178655402
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent one compressed positive result key. |
| inputs / outputs | Entry contains native Tuple and W01 multiplicity. |
| invariants | Published Entries have positive count; SET mode always uses one; BAG never expands copies. |
| ownership | Tuple is an immutable original-account payload handle with the LEFT schema. |
| failure | Value moves/copies retain existing owners; construction work is performed before source commit. |
| cost | Fixed handle/count storage per distinct result key; payload bytes remain separately owned. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/runtime/difference.hpp](../../../../../../include/crown/runtime/difference.hpp) |

## B0007

[Lines 28–34](../../../../../../include/crown/runtime/difference.hpp#L28); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L34:sha256:5960f4b8bfe29319941579bb303d03d2e1c388e8758ef8f15c64a0a5fa5566c2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe exact nonnegative endpoint multiplicity replacement and safe signed view. |
| inputs / outputs | Change owns tuple and before/after; delta() returns sign and larger-minus-smaller magnitude. |
| invariants | Zero endpoint denotes absence; emitted changes have unequal endpoints; subtraction cannot underflow and never narrows to int64. |
| ownership | The tuple keeps either old or new immutable native payload alive after deletion/Runtime teardown. |
| failure | delta() is noexcept and allocates nothing. |
| cost | Fixed unsigned comparisons/subtraction; eventual shared payload cleanup remains actual cost. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/runtime/difference.hpp](../../../../../../include/crown/runtime/difference.hpp) |

## B0008

[Lines 35–43](../../../../../../include/crown/runtime/difference.hpp#L35); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L43:sha256:59513efd755678f6a1c1295f715391d0d091d4ec16a9b6acf961bb1a1432a8c9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the immutable actual pair-query semantic Binding. |
| inputs / outputs | Forward Runtime declaration and Binding Data/default constructor with provenance comment. |
| invariants | Actual original left/right queries plus mode/arithmetic/LEFT result schema are distinct from genuine source-only Query{} provenance. |
| ownership | A live Binding shares account-funded immutable Data, not an ordinary retained query/catalog DTO. |
| failure | Default Binding is empty; borrowing getters require a live handle. |
| cost | Fixed shared-handle declaration/default construction; final metadata cleanup follows retained allocations. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/runtime/difference.hpp](../../../../../../include/crown/runtime/difference.hpp) |

## B0009

[Lines 44–44](../../../../../../include/crown/runtime/difference.hpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L44-L44:sha256:97dc45bb9885bdd0388f6f214da7c7b65592f7223005ba157410f3c56773a027
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether a Binding owns immutable pair-query data. |
| inputs / outputs | Explicit noexcept bool conversion reports whether data_ is nonnull. |
| invariants | Presence does not claim canonical combined-query identity or execution readiness. |
| ownership | No new owner/cursor/image is created. |
| failure | Noexcept even for an empty Binding. |
| cost | Fixed shared-pointer presence test. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/runtime/difference.hpp](../../../../../../include/crown/runtime/difference.hpp) |

## B0010

[Lines 45–59](../../../../../../include/crown/runtime/difference.hpp#L45); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L59:sha256:bbefd6daa4e903c2cb95f7c87a23b5e3b1ed856203f248d58657906673a9efe1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose borrowed actual pair semantics, genuine source provenance and LEFT layout. |
| inputs / outputs | Lvalue getters return original left/right native Query, Profile, source CompiledProgram, result layout/account; multiplicity_limit returns scalar. |
| invariants | Rvalue borrowed getters are deleted; sources() certifies its own source-only program, not the combined difference query. |
| ownership | Caller retains Binding while using borrowed views; copied Binding retains all actual predicates/terms/schema metadata on original account. |
| failure | Empty Binding getters throw difference_state; deleted rvalue forms fail compilation. |
| cost | Fixed handle/reference/scalar access; no query copy or new memory allowance. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/runtime/difference.hpp](../../../../../../include/crown/runtime/difference.hpp), [src/runtime/cq_recompute.hpp](../../../../../../src/runtime/cq_recompute.hpp) |

## B0011

[Lines 60–60](../../../../../../include/crown/runtime/difference.hpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L60-L60:sha256:9668289c851113e23b4b138479df6ba6907e30ef0ca88daddcc7d769cc258c4f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer the funded immutable semantic Data owner into a Binding. |
| inputs / outputs | Private Runtime-only shared_ptr constructor moves an already allocated Data handle. |
| invariants | Only Runtime creates nonempty Binding storage. |
| ownership | Shared const Data preserves original-account metadata and source-program provenance. |
| failure | Noexcept handle transfer; no new allocation. |
| cost | Fixed shared-pointer move. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/runtime/difference.hpp](../../../../../../include/crown/runtime/difference.hpp) |

## B0012

[Lines 61–65](../../../../../../include/crown/runtime/difference.hpp#L61); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L61-L65:sha256:3fd20be88b6c2685276afd3c580c98ea438a91488faab3ae7a841d2f15a500f9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Complete Binding ownership and declare transferable output container aliases. |
| inputs / outputs | Private checked data() and shared const Data; OutputVector uses OwnerAllocator; Cardinalities reuses funded fallback type. |
| invariants | Outputs can survive facade teardown without retaining a dangling Budget/comparator or source read lease. |
| ownership | OwnerAllocator transfers original account capacity; native tuple/Binding handles retain immutable payload/metadata owners. |
| failure | Future vector growth can refuse through original allocation authority. |
| cost | Empty aliases allocate nothing; actual capacities and final-owner cleanup are explicit. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/runtime/difference.hpp](../../../../../../include/crown/runtime/difference.hpp) |

## B0013

[Lines 66–66](../../../../../../include/crown/runtime/difference.hpp#L66); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L66-L66:sha256:2f2de313ad36cc4e74c206920d971c3ca1a12ab91ba03d36460be4f6f4128514
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return an eager owning compressed committed result snapshot. |
| inputs / outputs | Sequence, actual Binding, sorted Entry array and copy metrics. |
| invariants | One Entry per positive residual key; ordered/repeated head positions use LEFT layout; Boolean result is at most one nullary Entry with possibly large BAG count. |
| ownership | Funded output array, immutable tuple payloads and Binding survive owner teardown without source leases. |
| failure | Copy work/row/account refusal yields no partial snapshot or committed mutation. |
| cost | O(result distinct keys) handle/count copies and funded vector capacity, no multiplicity expansion. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/runtime/difference.hpp](../../../../../../include/crown/runtime/difference.hpp) |

## B0014

[Lines 67–67](../../../../../../include/crown/runtime/difference.hpp#L67); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L67-L67:sha256:f6b88b8919365929d96eafe037f8502a761825824bc686b9c0d265f2fa74a3ce
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return one genuine full-source publication and exact endpoint count changes. |
| inputs / outputs | PhysicalEpoch input, actual Binding, owning Change array and Metrics. |
| invariants | Input source/support changes are separate from original-pair result count replacements; unchanged counts produce no Change. |
| ownership | Old/new row payloads and semantic metadata retain original account after deletion/owner teardown. |
| failure | Epoch exists only after private capture, both queries, residuals and all output allocations succeed before source commit. |
| cost | Source coordination plus actual recomputation and linear endpoint merge; O(changed keys) funded output, no expanded bag copies. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/runtime/difference.hpp](../../../../../../include/crown/runtime/difference.hpp) |

## B0015

[Lines 68–76](../../../../../../include/crown/runtime/difference.hpp#L68); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L68-L76:sha256:90a26b3b0cafaed3f6cf29bdb9556b314cb959eee89000f328e8d4e9ec3373ff
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose actual execution class/cardinality and advisory witness estimates. |
| inputs / outputs | Explain contains Profile, full table_rows, residual distinct rows, W01 limit, optional total count and per-operand Cartesian/prefix products, account stats. |
| invariants | Overflow yields nullopt rather than wrapping; total count may overflow even if every key count is valid; estimates are advisory and include aliases independently. |
| ownership | Cardinality array uses original-account transferable allocation; other values are POD/static labels. |
| failure | Diagnostic allocation/busy rejection leaves committed state unchanged. |
| cost | O(tables+both atom counts+residual distinct keys), ignoring join selectivity/field widths; no CROWN/GHD or constant-delay bound. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/runtime/difference.hpp](../../../../../../include/crown/runtime/difference.hpp) |

## B0016

[Lines 77–112](../../../../../../include/crown/runtime/difference.hpp#L77); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L77-L112:sha256:4b81246e73c38dc4b4e387aad91ea691c6cf5a12e3700b6fa2b6e9225f2480ca
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare one serial exact difference owner over one full physical SET catalog. |
| inputs / outputs | Move-only Runtime constructs initially empty sources; exposes apply/snapshot/explain and explicit source_snapshot diagnostics. |
| invariants | Physical full-row duplicates remain no-ops; aliases/ignored/projection produce complete-witness bags; SET presence or clipped BAG subtraction are explicit; one source image and cumulative wrapper Budget feed both operands before atomic source commit and noexcept result swap. |
| ownership | All persistent/scratch/output native allocations use original account; actual Binding survives facade teardown; source_snapshot is the external ordinary DTO boundary only. |
| failure | Constraint/source/capture/work/key/count/allocation refusal leaves source sequence and answer endpoints unchanged through existing pending-token rollback; busy guard spans publication and old-state retirement. |
| cost | Full source copy, visited prefix/field/byte work, ordered map costs, tuple materialization, endpoint merge and cleanup are explicit; no SQL NULL, signed aggregate payload, negative cycle, recovery, parallel or constant-delay guarantee. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/runtime/difference.hpp](../../../../../../include/crown/runtime/difference.hpp), [include/crown/runtime/source_image.hpp](../../../../../../include/crown/runtime/source_image.hpp), [include/crown/annotations/policy.hpp](../../../../../../include/crown/annotations/policy.hpp), [src/runtime/difference.cpp](../../../../../../src/runtime/difference.cpp) |
