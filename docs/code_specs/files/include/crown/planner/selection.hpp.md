# `include/crown/planner/selection.hpp` — block usage map

[Source](../../../../../../include/crown/planner/selection.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies.

Snapshot SHA-256: `c3da639cd29ef04f0a5f1a6ab99de4d9bcaee1677b3d3ca5419a3195fed7794d`. 246 lines partitioned into 72 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ranking](../../../../subsystem_contracts.md#ranking). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ranking.md](../../../../../ranking.md), [docs/selection.md](../../../../../selection.md), [docs/selection_binding.md](../../../../../selection_binding.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md), [docs/selection_accounting.md](../../../../../selection_accounting.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../../include/crown/planner/selection.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Select the supported scoring baseline without changing required height. See · [reviewed contract](#b0001) |
| [B0002 · 12–12](../../../../../../include/crown/planner/selection.hpp#L12) | Type/record definition: enum class Policy | source comment (unverified): // Select the supported scoring baseline without changing required height. See · [reviewed contract](#b0002) |
| [B0003 · 13–13](../../../../../../include/crown/planner/selection.hpp#L13) | Explanatory comments or spacing. | source comment (unverified): // Choose retained-prefix scope or require real generator exhaustion. See docs/selection.md. · [reviewed contract](#b0003) |
| [B0004 · 14–14](../../../../../../include/crown/planner/selection.hpp#L14) | Type/record definition: enum class FamilyPolicy | source comment (unverified): // Choose retained-prefix scope or require real generator exhaustion. See docs/selection.md. · [reviewed contract](#b0004) |
| [B0005 · 15–15](../../../../../../include/crown/planner/selection.hpp#L15) | Explanatory comments or spacing. | source comment (unverified): // Name the admitted compiled layout policy. See docs/selection.md. · [reviewed contract](#b0005) |
| [B0006 · 16–16](../../../../../../include/crown/planner/selection.hpp#L16) | Type/record definition: enum class LayoutPolicy | source comment (unverified): // Name the admitted compiled layout policy. See docs/selection.md. · [reviewed contract](#b0006) |
| [B0007 · 17–17](../../../../../../include/crown/planner/selection.hpp#L17) | Explanatory comments or spacing. | source comment (unverified): // Name identical compiled-index requirement sharing. See docs/selection.md. · [reviewed contract](#b0007) |
| [B0008 · 18–18](../../../../../../include/crown/planner/selection.hpp#L18) | Type/record definition: enum class IndexPolicy | source comment (unverified): // Name identical compiled-index requirement sharing. See docs/selection.md. · [reviewed contract](#b0008) |
| [B0009 · 19–19](../../../../../../include/crown/planner/selection.hpp#L19) | Explanatory comments or spacing. | source comment (unverified): // Control whether artifact cache lookup/insertion participates. See docs/selection.md. · [reviewed contract](#b0009) |
| [B0010 · 20–20](../../../../../../include/crown/planner/selection.hpp#L20) | Type/record definition: enum class CacheUse | source comment (unverified): // Control whether artifact cache lookup/insertion participates. See docs/selection.md. · [reviewed contract](#b0010) |
| [B0011 · 21–22](../../../../../../include/crown/planner/selection.hpp#L21) | Explanatory comments or spacing. | source comment (unverified): // Provide explicit initial compiler options for the original proof model. See · [reviewed contract](#b0011) |
| [B0012 · 23–23](../../../../../../include/crown/planner/selection.hpp#L23) | Type/record definition: struct DirectCQ | source comment (unverified): // Provide explicit initial compiler options for the original proof model. See · [reviewed contract](#b0012) |
| [B0013 · 24–25](../../../../../../include/crown/planner/selection.hpp#L24) | Explanatory comments or spacing. | source comment (unverified): // Explicit compiler input or the actual immutable program of a runtime owner. · [reviewed contract](#b0013) |
| [B0014 · 26–26](../../../../../../include/crown/planner/selection.hpp#L26) | Type/record definition: struct PhysicalBasis | source comment (unverified): // Explicit compiler input or the actual immutable program of a runtime owner. · [reviewed contract](#b0014) |
| [B0015 · 27–28](../../../../../../include/crown/planner/selection.hpp#L27) | declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Supply a mandatory unitless modeled slot cap. See docs/selection.md. · [reviewed contract](#b0015) |
| [B0016 · 29–29](../../../../../../include/crown/planner/selection.hpp#L29) | Type/record definition: struct TupleIndexSlotLimit | source comment (unverified): // Supply a mandatory unitless modeled slot cap. See docs/selection.md. · [reviewed contract](#b0016) |
| [B0017 · 30–30](../../../../../../include/crown/planner/selection.hpp#L30) | Explanatory comments or spacing. | source comment (unverified): // Describe reserved allocator-byte prediction choices. See docs/selection.md. · [reviewed contract](#b0017) |
| [B0018 · 31–31](../../../../../../include/crown/planner/selection.hpp#L31) | Type/record definition: enum class BytePrediction | source comment (unverified): // Describe reserved allocator-byte prediction choices. See docs/selection.md. · [reviewed contract](#b0018) |
| [B0019 · 32–32](../../../../../../include/crown/planner/selection.hpp#L32) | Explanatory comments or spacing. | source comment (unverified): // Carry an explicitly unsupported allocator-byte constraint. See docs/selection.md. · [reviewed contract](#b0019) |
| [B0020 · 33–33](../../../../../../include/crown/planner/selection.hpp#L33) | Type/record definition: struct AllocatorByteLimit | source comment (unverified): // Carry an explicitly unsupported allocator-byte constraint. See docs/selection.md. · [reviewed contract](#b0020) |
| [B0021 · 34–37](../../../../../../include/crown/planner/selection.hpp#L34) | declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Select no constraint, mandatory modeled slots or reserved byte prediction. See · [reviewed contract](#b0021) |
| [B0022 · 38–38](../../../../../../include/crown/planner/selection.hpp#L38) | Type/record definition: struct Limits | source comment (unverified): // Use the shared finite ranking processing dimensions for selection. See docs/selection.md. · [reviewed contract](#b0022) |
| [B0023 · 39–40](../../../../../../include/crown/planner/selection.hpp#L39) | Explanatory comments or spacing. | source comment (unverified): // State policy, family, layout/index, slot/pattern conditions and aggregate limits. · [reviewed contract](#b0023) |
| [B0024 · 41–51](../../../../../../include/crown/planner/selection.hpp#L41) | Type/record definition: struct Request | source comment (unverified): // State policy, family, layout/index, slot/pattern conditions and aggregate limits. · [reviewed contract](#b0024) |
| [B0025 · 52–56](../../../../../../include/crown/planner/selection.hpp#L52) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Owning result fields retain the receiving query account. Ordinary Source and · [reviewed contract](#b0025) |
| [B0026 · 57–60](../../../../../../include/crown/planner/selection.hpp#L57) | Type/record definition: struct CapturedCachePolicy | source comment (unverified): // Owning result fields retain the receiving query account. Ordinary Source and · [reviewed contract](#b0026) |
| [B0027 · 61–62](../../../../../../include/crown/planner/selection.hpp#L61) | Explanatory comments or spacing. | source comment (unverified): // Retain account-backed policy with exact physical limits/backend options. See · [reviewed contract](#b0027) |
| [B0028 · 63–68](../../../../../../include/crown/planner/selection.hpp#L63) | Type/record definition: struct CapturedPhysicalOptions | source comment (unverified): // Retain account-backed policy with exact physical limits/backend options. See · [reviewed contract](#b0028) |
| [B0029 · 69–69](../../../../../../include/crown/planner/selection.hpp#L69) | Explanatory comments or spacing. | source comment (unverified): // Keep DirectCQ options in a result-owned account representation. See docs/selection.md. · [reviewed contract](#b0029) |
| [B0030 · 70–70](../../../../../../include/crown/planner/selection.hpp#L70) | Type/record definition: struct CapturedDirectCQ | source comment (unverified): // Keep DirectCQ options in a result-owned account representation. See docs/selection.md. · [reviewed contract](#b0030) |
| [B0031 · 71–71](../../../../../../include/crown/planner/selection.hpp#L71) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0031) |
| [B0032 · 72–72](../../../../../../include/crown/planner/selection.hpp#L72) | Type/record definition: struct CapturedTupleIndexSlotLimit |  · [reviewed contract](#b0032) |
| [B0033 · 73–75](../../../../../../include/crown/planner/selection.hpp#L73) | declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Retain exact request choices, source-bound pattern rules and finite limits. See · [reviewed contract](#b0033) |
| [B0034 · 76–87](../../../../../../include/crown/planner/selection.hpp#L76) | Type/record definition: struct CapturedRequest | source comment (unverified): // Retain exact request choices, source-bound pattern rules and finite limits. See · [reviewed contract](#b0034) |
| [B0035 · 88–88](../../../../../../include/crown/planner/selection.hpp#L88) | Explanatory comments or spacing. | source comment (unverified): // Locate the last synchronous selection stage. See docs/selection.md. · [reviewed contract](#b0035) |
| [B0036 · 89–91](../../../../../../include/crown/planner/selection.hpp#L89) | Type/record definition: enum class Stage | source comment (unverified): // Locate the last synchronous selection stage. See docs/selection.md. · [reviewed contract](#b0036) |
| [B0037 · 92–93](../../../../../../include/crown/planner/selection.hpp#L92) | Explanatory comments or spacing. | source comment (unverified): // Distinguish successful selection, unsupported/unavailable input and failed processing. See · [reviewed contract](#b0037) |
| [B0038 · 94–98](../../../../../../include/crown/planner/selection.hpp#L94) | Type/record definition: enum class Stop | source comment (unverified): // Distinguish successful selection, unsupported/unavailable input and failed processing. See · [reviewed contract](#b0038) |
| [B0039 · 99–99](../../../../../../include/crown/planner/selection.hpp#L99) | Explanatory comments or spacing. | source comment (unverified): // Name the exhausted processing/cache dimension when known. See docs/selection.md. · [reviewed contract](#b0039) |
| [B0040 · 100–102](../../../../../../include/crown/planner/selection.hpp#L100) | Type/record definition: enum class Resource | source comment (unverified): // Name the exhausted processing/cache dimension when known. See docs/selection.md. · [reviewed contract](#b0040) |
| [B0041 · 103–103](../../../../../../include/crown/planner/selection.hpp#L103) | Explanatory comments or spacing. | source comment (unverified): // State whether pure selection retained as-of evidence. See docs/selection.md. · [reviewed contract](#b0041) |
| [B0042 · 104–104](../../../../../../include/crown/planner/selection.hpp#L104) | Type/record definition: enum class EvidenceUse | source comment (unverified): // State whether pure selection retained as-of evidence. See docs/selection.md. · [reviewed contract](#b0042) |
| [B0043 · 105–106](../../../../../../include/crown/planner/selection.hpp#L105) | Explanatory comments or spacing. | source comment (unverified): // Distinguish absent, measured and historically unmeasured evidence preparation. See · [reviewed contract](#b0043) |
| [B0044 · 107–107](../../../../../../include/crown/planner/selection.hpp#L107) | Type/record definition: enum class PreparationTiming | source comment (unverified): // Distinguish absent, measured and historically unmeasured evidence preparation. See · [reviewed contract](#b0044) |
| [B0045 · 108–109](../../../../../../include/crown/planner/selection.hpp#L108) | Explanatory comments or spacing. | source comment (unverified): // Explain whether a retained complete C02 result served primary or mandatory slot filtering. · [reviewed contract](#b0045) |
| [B0046 · 110–110](../../../../../../include/crown/planner/selection.hpp#L110) | Type/record definition: enum class AssessmentPurpose | source comment (unverified): // Explain whether a retained complete C02 result served primary or mandatory slot filtering. · [reviewed contract](#b0046) |
| [B0047 · 111–111](../../../../../../include/crown/planner/selection.hpp#L111) | Explanatory comments or spacing. | source comment (unverified): // Retain one full C02 assessment and its role. See docs/selection.md. · [reviewed contract](#b0047) |
| [B0048 · 112–112](../../../../../../include/crown/planner/selection.hpp#L112) | Type/record definition: struct Assessment | source comment (unverified): // Retain one full C02 assessment and its role. See docs/selection.md. · [reviewed contract](#b0048) |
| [B0049 · 113–114](../../../../../../include/crown/planner/selection.hpp#L113) | Explanatory comments or spacing. | source comment (unverified): // Label slot-cap and optional pattern admissibility of one retained candidate. · [reviewed contract](#b0049) |
| [B0050 · 115–115](../../../../../../include/crown/planner/selection.hpp#L115) | Type/record definition: enum class Eligibility | source comment (unverified): // Label slot-cap and optional pattern admissibility of one retained candidate. · [reviewed contract](#b0050) |
| [B0051 · 116–116](../../../../../../include/crown/planner/selection.hpp#L116) | Explanatory comments or spacing. | source comment (unverified): // Record one candidate index and its eligibility. See docs/selection.md. · [reviewed contract](#b0051) |
| [B0052 · 117–117](../../../../../../include/crown/planner/selection.hpp#L117) | Type/record definition: struct CandidateDecision | source comment (unverified): // Record one candidate index and its eligibility. See docs/selection.md. · [reviewed contract](#b0052) |
| [B0053 · 118–118](../../../../../../include/crown/planner/selection.hpp#L118) | Explanatory comments or spacing. | source comment (unverified): // Bound FIFO entries and logical retained key/plan component bytes. See docs/selection.md. · [reviewed contract](#b0053) |
| [B0054 · 119–124](../../../../../../include/crown/planner/selection.hpp#L119) | Type/record definition: struct CacheLimits | source comment (unverified): // Bound FIFO entries and logical retained key/plan component bytes. See docs/selection.md. · [reviewed contract](#b0054) |
| [B0055 · 125–125](../../../../../../include/crown/planner/selection.hpp#L125) | Explanatory comments or spacing. | source comment (unverified): // Report committed cache counters and retained logical sizes. See docs/selection.md. · [reviewed contract](#b0055) |
| [B0056 · 126–131](../../../../../../include/crown/planner/selection.hpp#L126) | Type/record definition: struct CacheStatistics | source comment (unverified): // Report committed cache counters and retained logical sizes. See docs/selection.md. · [reviewed contract](#b0056) |
| [B0057 · 132–133](../../../../../../include/crown/planner/selection.hpp#L132) | Explanatory comments or spacing. | source comment (unverified): // Exclusive caller; no global state or public raw-key insertion capability. · [reviewed contract](#b0057) |
| [B0058 · 134–150](../../../../../../include/crown/planner/selection.hpp#L134) | Type/record definition: class PlanCache | source comment (unverified): // Exclusive caller; no global state or public raw-key insertion capability. · [reviewed contract](#b0058) |
| [B0059 · 151–151](../../../../../../include/crown/planner/selection.hpp#L151) | Explanatory comments or spacing. | source comment (unverified): // Describe this successful call cache participation. See docs/selection.md. · [reviewed contract](#b0059) |
| [B0060 · 152–152](../../../../../../include/crown/planner/selection.hpp#L152) | Type/record definition: enum class CacheDisposition | source comment (unverified): // Describe this successful call cache participation. See docs/selection.md. · [reviewed contract](#b0060) |
| [B0061 · 153–153](../../../../../../include/crown/planner/selection.hpp#L153) | Explanatory comments or spacing. | source comment (unverified): // Retain cache-use/capacity and byte-comparison diagnostics. See docs/selection.md. · [reviewed contract](#b0061) |
| [B0062 · 154–159](../../../../../../include/crown/planner/selection.hpp#L154) | Type/record definition: struct CacheObservation | source comment (unverified): // Retain cache-use/capacity and byte-comparison diagnostics. See docs/selection.md. · [reviewed contract](#b0062) |
| [B0063 · 160–163](../../../../../../include/crown/planner/selection.hpp#L160) | Explanatory comments or spacing. | source comment (unverified): // A qualified support-process bound for the selected immutable plan. This · [reviewed contract](#b0063) |
| [B0064 · 164–185](../../../../../../include/crown/planner/selection.hpp#L164) | Type/record definition: class PatternGuarantee | returns *this; source comment (unverified): // A qualified support-process bound for the selected immutable plan. This · [reviewed contract](#b0064) |
| [B0065 · 186–195](../../../../../../include/crown/planner/selection.hpp#L186) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Immutable owning result. Neither this handle nor its cache binding asserts · [reviewed contract](#b0065) |
| [B0066 · 196–196](../../../../../../include/crown/planner/selection.hpp#L196) | Callable definition: Selection(Selection&& other) noexcept : data_(other.data_) | calls data_ · [reviewed contract](#b0066) |
| [B0067 · 197–197](../../../../../../include/crown/planner/selection.hpp#L197) | Callable definition: Selection& operator=(Selection&& other) noexcept | returns *this · [reviewed contract](#b0067) |
| [B0068 · 198–226](../../../../../../include/crown/planner/selection.hpp#L198) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Empty when no pattern condition was requested; otherwise one entry per retained candidate. · [reviewed contract](#b0068) |
| [B0069 · 227–227](../../../../../../include/crown/planner/selection.hpp#L227) | Callable definition: explicit Selection(std::shared_ptr&lt;const detail::SelectionData&gt; data) noexcept : data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0069) |
| [B0070 · 228–231](../../../../../../include/crown/planner/selection.hpp#L228) | declares values/defaults or compile-time conditions. | source comment (unverified): // Return fixed diagnostics and optional complete Selection from a noexcept call. See · [reviewed contract](#b0070) |
| [B0071 · 232–242](../../../../../../include/crown/planner/selection.hpp#L232) | Type/record definition: struct Attempt | source comment (unverified): // Return fixed diagnostics and optional complete Selection from a noexcept call. See · [reviewed contract](#b0071) |
| [B0072 · 243–246](../../../../../../include/crown/planner/selection.hpp#L243) | declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::planner::selection · [reviewed contract](#b0072) |

## B0001

[Lines 1–11](../../../../../../include/crown/planner/selection.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
namespace rank = ::crown::planner::ranking;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import C02 ranking and conditional pattern API types; alias selection::rank to planner::ranking. |
| inputs / outputs | Header includes expose ranking and update-pattern types, selection namespace and private forward declarations. |
| invariants | Compile-time dependency only; no base runtime-to-ranking edge or new validation authority is introduced. |
| ownership | No object or payload is owned. |
| failure | The alias itself has no runtime failure path. |
| cost | Compile-time alias only; no runtime work or allocation. |
| Design | [include/crown/planner/selection.hpp §rank namespace use](../../../../../../include/crown/planner/selection.hpp), [include/crown/planner/ranking.hpp](../../../../../../include/crown/planner/ranking.hpp), [docs/selection.md](../../../../../selection.md), [docs/update_patterns.md](../../../../../update_patterns.md) |

## B0002

[Lines 12–12](../../../../../../include/crown/planner/selection.hpp#L12); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Policy {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the supported scoring baseline without changing required height. |
| inputs / outputs | Height, committed-input native depth, slots, or reserved maintenance model. |
| invariants | maintenance_cost rejects; every accepted candidate already has original minimum-height authority. |
| ownership | Scalar option. |
| failure | Unknown tags reject admission. |
| cost | Tag dispatch; actual assessments visit the whole retained set. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0003

[Lines 13–13](../../../../../../include/crown/planner/selection.hpp#L13); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L13-L13:sha256:45f0967264cd52636c321ddc99c8a51ab488e6e8e3100a5048acdcb8dc925d18
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for FamilyPolicy: Choose retained-prefix scope or require real generator exhaustion. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies FamilyPolicy; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for FamilyPolicy come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/selection.hpp](../../../../../../include/crown/planner/selection.hpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

## B0004

[Lines 14–14](../../../../../../include/crown/planner/selection.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class FamilyPolicy {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose retained-prefix scope or require real generator exhaustion. |
| inputs / outputs | Request value controls the exhaustion gate. |
| invariants | A resource-stopped/cancelled family is not exhausted; neither mode proves global maintenance-cost optimality. |
| ownership | Scalar copied option. |
| failure | Unknown policy or unmet exhaustion rejects. |
| cost | Fixed admission test. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0005

[Lines 15–15](../../../../../../include/crown/planner/selection.hpp#L15); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L15:sha256:a5943eb324367aa7f2c379c70abe90a9413bc06a797b7d3f7350af377ea3adcb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for LayoutPolicy: Name the admitted compiled layout policy. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies LayoutPolicy; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for LayoutPolicy come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/selection.hpp](../../../../../../include/crown/planner/selection.hpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

## B0006

[Lines 16–16](../../../../../../include/crown/planner/selection.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class LayoutPolicy {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the admitted compiled layout policy. |
| inputs / outputs | Only native_layout_v1 is supported. |
| invariants | Changing a label cannot enable another layout algorithm. |
| ownership | Scalar option. |
| failure | Unknown value yields unsupported_layout. |
| cost | Fixed check, separate from lowering. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0007

[Lines 17–17](../../../../../../include/crown/planner/selection.hpp#L17); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L17:sha256:a0e069faee00386fc656b542eaab3be096d3a1d975b61c98a514b6c7df8fc74f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for IndexPolicy: Name identical compiled-index requirement sharing. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies IndexPolicy; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for IndexPolicy come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/selection.hpp](../../../../../../include/crown/planner/selection.hpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

## B0008

[Lines 18–18](../../../../../../include/crown/planner/selection.hpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class IndexPolicy {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name identical compiled-index requirement sharing. |
| inputs / outputs | Only share_identical_requirements_v1 is admitted. |
| invariants | This is lowering configuration, not registration of a live runtime index. |
| ownership | Scalar option. |
| failure | Unknown value yields unsupported_layout. |
| cost | Fixed check. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0009

[Lines 19–19](../../../../../../include/crown/planner/selection.hpp#L19); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L19:sha256:bfe01ed9b288ea995a9fa13334806bef1d978ebee09e4ad0570a2796e25a1deb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for CacheUse: Control whether artifact cache lookup/insertion participates. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies CacheUse; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for CacheUse come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/selection.hpp](../../../../../../include/crown/planner/selection.hpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

## B0010

[Lines 20–20](../../../../../../include/crown/planner/selection.hpp#L20); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class CacheUse {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Control whether artifact cache lookup/insertion participates. |
| inputs / outputs | bypass, read_only, read_write. |
| invariants | Hits follow fresh admission/binding/ranking; read_only can commit hit/miss counters but never inserts. |
| ownership | Scalar option with exclusive cache borrow. |
| failure | Unknown mode or missing/empty cache owner rejects when used. |
| cost | Mode dispatch; lookup compares full bytes. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0011

[Lines 21–22](../../../../../../include/crown/planner/selection.hpp#L21); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L22:sha256:ede0bbebf564b932d73f69bcb2a45b90440a7c72439b4afd6ead40b375758398
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for DirectCQ: Provide explicit initial compiler options for the original proof model. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies DirectCQ; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for DirectCQ come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/selection.hpp](../../../../../../include/crown/planner/selection.hpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

## B0012

[Lines 23–23](../../../../../../include/crown/planner/selection.hpp#L23); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DirectCQ {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide explicit initial compiler options for the original proof model. |
| inputs / outputs | Owns PhysicalOptions; model comes from snapshot.original_proof().binding(). |
| invariants | This does not supply a replacement query or normalized SQL source. |
| ownership | Owns ordinary policy strings and scalar options. |
| failure | Arithmetic/layout/source checks occur downstream. |
| cost | Policy copying scales with text; standalone compiler workspace is a separate boundary. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0013

[Lines 24–25](../../../../../../include/crown/planner/selection.hpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L25:sha256:bff95872309824c028d889ab194448c2bc52da7a150f21d6e40eb101724636f1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for PhysicalBasis: Explicit compiler input or the actual immutable program of a runtime owner. Retain a complete physical source for selection/replanning. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies PhysicalBasis; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for PhysicalBasis come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/selection.hpp](../../../../../../include/crown/planner/selection.hpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

## B0014

[Lines 26–26](../../../../../../include/crown/planner/selection.hpp#L26); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhysicalBasis {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain a complete physical source for selection/replanning. |
| inputs / outputs | Variant holds PhysicalPlan or CompiledProgram. |
| invariants | Core proof binding and complete source/evidence must agree; a semantic digest alone is insufficient. |
| ownership | Shares immutable plan handles, including their original metadata accounts. |
| failure | Moved/invalid native handle or mismatched binding rejects. |
| cost | Handle copy; preparing a compiler DTO basis is separate caller work. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0015

[Lines 27–28](../../../../../../include/crown/planner/selection.hpp#L27); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Source = std::variant<DirectCQ, PhysicalBasis>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish exact direct model input from a preserved physical source. |
| inputs / outputs | Variant consumed synchronously by selection. |
| invariants | DirectCQ cannot impersonate a normalized basis; valueless input rejects. |
| ownership | Caller owns input; result captures text or shares a basis. |
| failure | No implicit fallback between alternatives. |
| cost | Variant dispatch plus actual copied text/shared handle costs. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0016

[Lines 29–29](../../../../../../include/crown/planner/selection.hpp#L29); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct TupleIndexSlotLimit {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Supply a mandatory unitless modeled slot cap. |
| inputs / outputs | Owns canonical decimal maximum in 0..2^512-1. |
| invariants | It is never compared as allocator bytes; primary fallback cannot bypass it. |
| ownership | Owns caller string. |
| failure | Empty, leading-zero, nondigit or excessive cap rejects. |
| cost | Digit validation/comparison and later captured string copy. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0017

[Lines 30–30](../../../../../../include/crown/planner/selection.hpp#L30); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L30-L30:sha256:341484497a7be7aaea5b3a4373128ee15750a11883ef714e13ca0bc69621e60b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for BytePrediction: Describe reserved allocator-byte prediction choices. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies BytePrediction; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for BytePrediction come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/selection.hpp](../../../../../../include/crown/planner/selection.hpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

## B0018

[Lines 31–31](../../../../../../include/crown/planner/selection.hpp#L31); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class BytePrediction {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe reserved allocator-byte prediction choices. |
| inputs / outputs | Live/peak tags accompany AllocatorByteLimit. |
| invariants | Neither prediction is implemented by C05. |
| ownership | Scalar tag only. |
| failure | Any AllocatorByteLimit request rejects unsupported_memory_prediction. |
| cost | No allocator prediction work occurs. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0019

[Lines 32–32](../../../../../../include/crown/planner/selection.hpp#L32); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L32-L32:sha256:f2fe8ed3f02b6eb8fd984fd29635ce33b7eb256521f8c6aed17d663ee52332c0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for AllocatorByteLimit: Carry an explicitly unsupported allocator-byte constraint. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies AllocatorByteLimit; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for AllocatorByteLimit come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/selection.hpp](../../../../../../include/crown/planner/selection.hpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

## B0020

[Lines 33–33](../../../../../../include/crown/planner/selection.hpp#L33); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AllocatorByteLimit {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry an explicitly unsupported allocator-byte constraint. |
| inputs / outputs | Maximum and live/peak prediction. |
| invariants | Even zero is rejected; unitless slots cannot satisfy it. |
| ownership | Two scalar values. |
| failure | Admission returns unsupported_memory_prediction. |
| cost | Fixed rejection before ranking/lowering. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0021

[Lines 34–37](../../../../../../include/crown/planner/selection.hpp#L34); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Constraint = std::variant<std::monostate, TupleIndexSlotLimit, AllocatorByteLimit>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select no constraint, mandatory modeled slots or reserved byte prediction. |
| inputs / outputs | Caller variant stores cap data. |
| invariants | Only monostate/slot alternatives can succeed. |
| ownership | Owns optional decimal text through the variant. |
| failure | Valueless/unsupported alternatives reject admission. |
| cost | Variant checks plus cap bytes when present. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0022

[Lines 38–38](../../../../../../include/crown/planner/selection.hpp#L38); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Limits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the shared finite ranking processing dimensions for selection. |
| inputs / outputs | Wraps rank::Limits aggregate. |
| invariants | Logical work/cells/key/payload/native work, candidates, bits and time remain separate from actual account bytes. |
| ownership | Scalar configuration. |
| failure | Invalid score bits/time or exhausted dimensions stop before publication. |
| cost | Fixed options; enforcement is selected logical charging. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0023

[Lines 39–40](../../../../../../include/crown/planner/selection.hpp#L39); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L39-L40:sha256:723390df30ff43a0c4aba2a0b8d456c3f17b79c43be8002fbf297dbd1c8c7d2f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain Request policy/slot/pattern choices and the separation from runtime enforcement. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies Request; use the adjacent declaration and implementation for the actual values and result. |
| invariants | Static usage guidance only; actual optional filtering is in Operation::prepare, with no claim that a runtime monitor exists. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for Request come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/selection.hpp](../../../../../../include/crown/planner/selection.hpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md), [docs/update_patterns.md](../../../../../update_patterns.md) |

## B0024

[Lines 41–51](../../../../../../include/crown/planner/selection.hpp#L41); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Request {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Request C02 ranking, family/layout choices, slot/pattern admissibility and one aggregate processing grant. |
| inputs / outputs | Existing defaults remain; optional update_patterns supplies a source-bound Declaration and requires a proved conditional sufficient case for a candidate to win. |
| invariants | No change to certified height/family or silent grant refill. Presence requests conditional filtering even for an empty rule set; absence skips it. A requested declaration is not runtime enforcement. |
| ownership | Caller owns ordinary option strings and shares the supplied Declaration; successful result copies declaration metadata into the receiving account. |
| failure | Unsupported source/model/bytes/layout or invalid options reject before cache publication; no compatible proved retained candidate yields constraint_unsatisfied. |
| cost | Existing admission/whole-family assessments plus optional one-time rule copy and per-retained-candidate transfer/edge analysis; no input-update work. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md), [docs/update_patterns.md](../../../../../update_patterns.md) |

## B0025

[Lines 52–56](../../../../../../include/crown/planner/selection.hpp#L52); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using SelectionText=resource::OwnerText;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name account-retaining result text and vectors. |
| inputs / outputs | SelectionText and adjacent SelectionVector use propagating OwnerAllocator. |
| invariants | Transfers preserve allocating account/attribution and do not create a fresh allowance. |
| ownership | Containers own payload and retain original account. |
| failure | Allocation failure obeys that account and propagates to selection diagnostics. |
| cost | Real capacity/framing is accounted separately from logical payload charges. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0026

[Lines 57–60](../../../../../../include/crown/planner/selection.hpp#L57); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CapturedCachePolicy {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain policy text inside the receiving selection account. |
| inputs / outputs | Four OwnerText strings copied from CachePolicy. |
| invariants | Capture changes storage ownership, not supported arithmetic/planner capability. |
| ownership | Text owns native account-backed bytes. |
| failure | Constructor can fail before Selection publication. |
| cost | Copies all policy bytes and container allocation framing. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0027

[Lines 61–62](../../../../../../include/crown/planner/selection.hpp#L61); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L61-L62:sha256:aa8a10bdf4a8d46f4c999711a0e29afddd5ce1f7c4db9ebaa82fdb1dcee9737c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for CapturedPhysicalOptions: Retain account-backed policy with exact physical limits/backend options. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies CapturedPhysicalOptions; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for CapturedPhysicalOptions come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/selection.hpp](../../../../../../include/crown/planner/selection.hpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

## B0028

[Lines 63–68](../../../../../../include/crown/planner/selection.hpp#L63); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CapturedPhysicalOptions {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain account-backed policy with exact physical limits/backend options. |
| inputs / outputs | Captured policy, limits and optional IndexedBackendSpec. |
| invariants | No normalization or option reinterpretation occurs. |
| ownership | Owns captured text and scalar copies. |
| failure | Allocation/invalid allocator construction can throw. |
| cost | Policy byte copy plus fixed configuration. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0029

[Lines 69–69](../../../../../../include/crown/planner/selection.hpp#L69); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L69-L69:sha256:7b54aeefd625b3193c4d926facbbc2f81f698c0052c79476952618fd431cbf2e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for CapturedDirectCQ: Keep DirectCQ options in a result-owned account representation. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies CapturedDirectCQ; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for CapturedDirectCQ come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/selection.hpp](../../../../../../include/crown/planner/selection.hpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

## B0030

[Lines 70–70](../../../../../../include/crown/planner/selection.hpp#L70); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CapturedDirectCQ {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep DirectCQ options in a result-owned account representation. |
| inputs / outputs | Contains CapturedPhysicalOptions. |
| invariants | Still derives its model from the retained original proof. |
| ownership | Owns policy text through captured options. |
| failure | Construction relies on admitted caller configuration. |
| cost | Captured text storage plus fixed fields. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0031

[Lines 71–71](../../../../../../include/crown/planner/selection.hpp#L71); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using CapturedSource=std::variant<CapturedDirectCQ,PhysicalBasis>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the selected source without an ordinary internal text mirror. |
| inputs / outputs | Direct source captures native text; physical basis shares its actual program/DTO handle. |
| invariants | This does not authorize a new proof or current-owner claim. |
| ownership | Result owns variant and account-backed strings/shared basis. |
| failure | Prepared privately before publication. |
| cost | Copies direct text or retains handle; no implicit full program export. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0032

[Lines 72–72](../../../../../../include/crown/planner/selection.hpp#L72); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CapturedTupleIndexSlotLimit {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain a validated decimal slot cap under the receiving account. |
| inputs / outputs | OwnerText maximum. |
| invariants | The number retains unitless slot semantics. |
| ownership | Owns captured text/account. |
| failure | Allocation can abort unexposed result construction. |
| cost | Up to admitted cap length plus actual allocation framing. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0033

[Lines 73–75](../../../../../../include/crown/planner/selection.hpp#L73); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using CapturedConstraint=std::variant<std::monostate,CapturedTupleIndexSlotLimit,AllocatorByteLimit>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain constraint values in result storage. |
| inputs / outputs | Variant parallels caller Constraint with native text for slot cap. |
| invariants | AllocatorByteLimit remains a representable aggregate but cannot appear in a successful admitted request. Optional update patterns belong to the adjacent CapturedRequest field and are not a Constraint variant alternative. |
| ownership | Owns captured cap or scalars. |
| failure | Direct construction performs no semantic validation. |
| cost | Variant storage plus cap payload. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md), [docs/update_patterns.md](../../../../../update_patterns.md) |

## B0034

[Lines 76–87](../../../../../../include/crown/planner/selection.hpp#L76); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CapturedRequest {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain exact request choices and finite limits in native result storage. |
| inputs / outputs | Copies policies/limits, captures slot-cap bytes and optionally copies a validated source-bound Declaration into the receiving account. |
| invariants | Published captures follow admission; arbitrary construction itself does not validate tags/valueless source variants. Direct public capture owns no processing grant: the caller must pre-admit declaration copy_usage and copied text. Stored limits are metadata; select() performs these admissions under its aggregate grant. |
| ownership | Owns account-backed cap text and new declaration metadata; shared original proof/source owners retain their existing lifetimes. |
| failure | Constructor allocation can fail before publication. |
| cost | Fixed fields plus O(cap bytes + R) metadata copying when requested; no second sort or per-candidate deep declaration copy. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md), [docs/update_patterns.md](../../../../../update_patterns.md) |

## B0035

[Lines 88–88](../../../../../../include/crown/planner/selection.hpp#L88); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L88-L88:sha256:8567001396892bf069047e44529d27415f17c4f9b14a09fca2b705caa1305d36
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for Stage: Locate the last synchronous selection stage. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies Stage; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for Stage come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/selection.hpp](../../../../../../include/crown/planner/selection.hpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

## B0036

[Lines 89–91](../../../../../../include/crown/planner/selection.hpp#L89); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Stage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Locate the last synchronous selection stage. |
| inputs / outputs | Existing stages retain order; appended pattern_analysis identifies the optional conditional prepass. Labels are synchronous diagnostics, not resumable cursors. |
| invariants | Diagnostic stage is not a resumable cursor or authority. |
| ownership | Scalar Attempt field. |
| failure | Failure retains the last assigned stage. |
| cost | Fixed value copy. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md §Atomic publication](../../../../../selection_accounting.md), [docs/update_patterns.md](../../../../../update_patterns.md) |

## B0037

[Lines 92–93](../../../../../../include/crown/planner/selection.hpp#L92); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L92-L93:sha256:26e3719da7f28606914702898a601d12d47b3bd4ae81ff3a096e5bfaa613aad5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for Stop: Distinguish successful selection, unsupported/unavailable input and failed processing. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies Stop; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for Stop come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/selection.hpp](../../../../../../include/crown/planner/selection.hpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

## B0038

[Lines 94–98](../../../../../../include/crown/planner/selection.hpp#L94); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Stop {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish successful selection, unsupported/unavailable input and failed processing. |
| inputs / outputs | Fixed outcome enum in Attempt. |
| invariants | Only complete with an owning result publishes a Selection; failed calls leave cache/owner unchanged. |
| ownership | Scalar value. |
| failure | Failure categories are preserved rather than treated as fallback success. |
| cost | Fixed reporting without message allocation. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md §Atomic publication](../../../../../selection_accounting.md) |

## B0039

[Lines 99–99](../../../../../../include/crown/planner/selection.hpp#L99); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L99-L99:sha256:68ae6612e393ffbf178c1d11e9a3c71f597e10e55463dc01bd2f078d642db680
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for Resource: Name the exhausted processing/cache dimension when known. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies Resource; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for Resource come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/selection.hpp](../../../../../../include/crown/planner/selection.hpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

## B0040

[Lines 100–102](../../../../../../include/crown/planner/selection.hpp#L100); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Resource {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the exhausted processing/cache dimension when known. |
| inputs / outputs | Work/cells/keys/payload/native/time/cache/counter labels. |
| invariants | Delegated byte_limit remains Resource::none because its combined category cannot be refined. |
| ownership | Scalar diagnostic. |
| failure | Label grants no resource refill or proof authority. |
| cost | Fixed value. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md §Atomic publication](../../../../../selection_accounting.md) |

## B0041

[Lines 103–103](../../../../../../include/crown/planner/selection.hpp#L103); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L103-L103:sha256:643a332152514b83081a8f116a61cf42791fb0189a070e78581f45021a9bd538
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for EvidenceUse: State whether pure selection retained as-of evidence. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies EvidenceUse; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for EvidenceUse come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/selection.hpp](../../../../../../include/crown/planner/selection.hpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

## B0042

[Lines 104–104](../../../../../../include/crown/planner/selection.hpp#L104); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class EvidenceUse {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State whether pure selection retained as-of evidence. |
| inputs / outputs | absent or as_of. |
| invariants | This never asserts actual-owner freshness. |
| ownership | Scalar computed from optional evidence. |
| failure | No current-boundary check is implied. |
| cost | Fixed optional-presence read. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md §Atomic publication](../../../../../selection_accounting.md) |

## B0043

[Lines 105–106](../../../../../../include/crown/planner/selection.hpp#L105); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L105-L106:sha256:3827a2045600bb981144b5669d620a32a0dd694dcd9c605cfad9103ab36ecef2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for PreparationTiming: Distinguish absent, measured and historically unmeasured evidence preparation. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies PreparationTiming; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for PreparationTiming come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/selection.hpp](../../../../../../include/crown/planner/selection.hpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

## B0044

[Lines 107–107](../../../../../../include/crown/planner/selection.hpp#L107); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class PreparationTiming {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish absent, measured and historically unmeasured evidence preparation. |
| inputs / outputs | Derived from capture configuration. |
| invariants | Untimed old preparation is not invented as measured zero. |
| ownership | Scalar diagnostic. |
| failure | No clocks are sampled by classification. |
| cost | Fixed metadata read. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md §Atomic publication](../../../../../selection_accounting.md) |

## B0045

[Lines 108–109](../../../../../../include/crown/planner/selection.hpp#L108); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L108-L109:sha256:4572b225aa446f479d188f54e52ac75f418221c68b015ad931b32758aaf5fac3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for AssessmentPurpose: Explain whether a retained complete C02 result served primary or mandatory slot filtering. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies AssessmentPurpose; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for AssessmentPurpose come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/selection.hpp](../../../../../../include/crown/planner/selection.hpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

## B0046

[Lines 110–110](../../../../../../include/crown/planner/selection.hpp#L110); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class AssessmentPurpose {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain whether a retained complete C02 result served primary or mandatory slot filtering. |
| inputs / outputs | primary, slot_constraint, primary_and_constraint. |
| invariants | Its C02 winner can differ from the constrained C05 winner. |
| ownership | Scalar alongside owning ranking result. |
| failure | Purpose never excuses incomplete candidate scoring. |
| cost | Fixed label. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md §Atomic publication](../../../../../selection_accounting.md) |

## B0047

[Lines 111–111](../../../../../../include/crown/planner/selection.hpp#L111); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L111-L111:sha256:9f281bf6f4f20d1ca2b195b05042e5957057d8429597dccf0fca16e8f12996dc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for Assessment: Retain one full C02 assessment and its role. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies Assessment; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for Assessment come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/selection.hpp](../../../../../../include/crown/planner/selection.hpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

## B0048

[Lines 112–112](../../../../../../include/crown/planner/selection.hpp#L112); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Assessment {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one full C02 assessment and its role. |
| inputs / outputs | Purpose plus rank::Result owner. |
| invariants | All retained members are evaluated before this result exists. |
| ownership | Shares immutable native ranking payload/account. |
| failure | Prepared only after component completion. |
| cost | Handle copy; final release can destroy large score arrays/plans. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md §Atomic publication](../../../../../selection_accounting.md) |

## B0049

[Lines 113–114](../../../../../../include/crown/planner/selection.hpp#L113); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L113-L114:sha256:0025511513cdaf98b8f4557e370bc2f98e1c277c3725cde42d6f045992444657
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain slot/pattern eligibility and slot-failure precedence. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies Eligibility; use the adjacent declaration and implementation for the actual values and result. |
| invariants | Static guidance only; the separate analysis remains inspectable even when the enum records a slot failure. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for Eligibility come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/selection.hpp](../../../../../../include/crown/planner/selection.hpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md), [docs/update_patterns.md](../../../../../update_patterns.md) |

## B0050

[Lines 115–115](../../../../../../include/crown/planner/selection.hpp#L115); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Eligibility {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Label mandatory slot and optional conditional-pattern eligibility of a retained candidate. |
| inputs / outputs | unconstrained/within_slot_limit/above_slot_limit keep original values; appended pattern_unproved excludes an otherwise slot-eligible candidate without a sufficient case. |
| invariants | Neither above_slot_limit nor pattern_unproved can win. Slot failure has precedence; the separate retained analysis still records its pattern result. |
| ownership | Scalar decision field. |
| failure | Unknown is an unproved condition, never hardness, physical byte admission, live compliance or a theorem token. |
| cost | Fixed comparison label. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md §Atomic publication](../../../../../selection_accounting.md), [docs/update_patterns.md](../../../../../update_patterns.md) |

## B0051

[Lines 116–116](../../../../../../include/crown/planner/selection.hpp#L116); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L116-L116:sha256:16288d6aef10ef0baf1351bc4bc2c0707a32ba414b84fefad0393d6699e5a42a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for CandidateDecision: Record one candidate index and its eligibility. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies CandidateDecision; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for CandidateDecision come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/selection.hpp](../../../../../../include/crown/planner/selection.hpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

## B0052

[Lines 117–117](../../../../../../include/crown/planner/selection.hpp#L117); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CandidateDecision {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record one candidate index and its eligibility. |
| inputs / outputs | Complete vector aligns with snapshot order. |
| invariants | It describes retained-set filtering, not generator exhaustion. |
| ownership | Owns two scalars; snapshot retained elsewhere. |
| failure | Standalone values can be invalid; preparation constructs aligned decisions. |
| cost | One entry per retained candidate. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md §Atomic publication](../../../../../selection_accounting.md) |

## B0053

[Lines 118–118](../../../../../../include/crown/planner/selection.hpp#L118); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L118-L118:sha256:be14489089688e655b6f21ec1f3768e9e941993e326be7838a370c649f8d1457
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for CacheLimits: Bound FIFO entries and logical retained key/plan component bytes. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies CacheLimits; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for CacheLimits come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/selection.hpp](../../../../../../include/crown/planner/selection.hpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

## B0054

[Lines 119–124](../../../../../../include/crown/planner/selection.hpp#L119); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CacheLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound FIFO entries and logical retained key/plan component bytes. |
| inputs / outputs | Finite entry, key-byte and modeled payload caps. |
| invariants | These are not allocator requested/peak-byte caps; zero entries disables cache. |
| ownership | Value configuration. |
| failure | Positive entries with zero byte caps rejects cache creation. |
| cost | Fixed fields; retention enforcement scans staged evictions. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md §Atomic publication](../../../../../selection_accounting.md) |

```text
bool operator==(const CacheLimits&) const = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare all cache retention caps. |
| inputs / outputs | Memberwise equality of entries/key/payload limits. |
| invariants | Equal caps do not imply shared cache contents. |
| ownership | Borrows value operands. |
| failure | No validation. |
| cost | Fixed scalar comparisons. |
| Design | [docs/selection.md](../../../../../selection.md) |

## B0055

[Lines 125–125](../../../../../../include/crown/planner/selection.hpp#L125); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L125-L125:sha256:c4afb745151dfe776ad8ac444c0e87c435165012880ca890ff4d14b8fff4aecb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for CacheStatistics: Report committed cache counters and retained logical sizes. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies CacheStatistics; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for CacheStatistics come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/selection.hpp](../../../../../../include/crown/planner/selection.hpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

## B0056

[Lines 126–131](../../../../../../include/crown/planner/selection.hpp#L126); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CacheStatistics {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report committed cache counters and retained logical sizes. |
| inputs / outputs | Hits/misses/insertions/evictions, entries/key/payload totals. |
| invariants | Only Prepared.commit changes speculative operation counters; clear resets them all. |
| ownership | Owns scalars. |
| failure | Overflow prevents commit; failed calls preserve prior statistics. |
| cost | Fixed snapshot; not a memory ledger. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md §Atomic publication](../../../../../selection_accounting.md) |

```text
bool operator==(const CacheStatistics&) const = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare all committed cache diagnostics. |
| inputs / outputs | Memberwise equality of counter/size fields. |
| invariants | Equality proves no artifact binding equivalence. |
| ownership | Borrows scalar snapshots. |
| failure | No validation. |
| cost | Fixed comparisons. |
| Design | [docs/selection.md](../../../../../selection.md) |

## B0057

[Lines 132–133](../../../../../../include/crown/planner/selection.hpp#L132); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L132-L133:sha256:962d85d66e54370bdc252e10ce1f5baa1631939e391ca44305495d19a14c2c05
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for PlanCache: Exclusive caller; no global state or public raw-key insertion capability. Own an exclusive FIFO cache of whole compiled artifacts. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies PlanCache; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for PlanCache come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/selection.hpp](../../../../../../include/crown/planner/selection.hpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

## B0058

[Lines 134–150](../../../../../../include/crown/planner/selection.hpp#L134); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class PlanCache {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own an exclusive FIFO cache of whole compiled artifacts. |
| inputs / outputs | create, move-only lifetime, snapshots and explicit clear. |
| invariants | No raw-key insertion/import capability; hits follow a fresh complete decision and do not reorder. |
| ownership | Unique CacheData owns funded nodes that can originate in different query accounts. |
| failure | Moved-from observers return empty defaults; selection using a moved cache rejects. |
| cost | Lookup compares complete bytes; clear/destruction can release all retained graphs. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md §Atomic publication](../../../../../selection_accounting.md) |

## B0059

[Lines 151–151](../../../../../../include/crown/planner/selection.hpp#L151); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L151-L151:sha256:aae0565929a553c6037d6769e8ec1e8b8b345d35d7971c81790858fa4eaa9e26
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for CacheDisposition: Describe this successful call cache participation. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies CacheDisposition; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for CacheDisposition come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/selection.hpp](../../../../../../include/crown/planner/selection.hpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

## B0060

[Lines 152–152](../../../../../../include/crown/planner/selection.hpp#L152); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class CacheDisposition {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe this successful call cache participation. |
| inputs / outputs | Bypassed/disabled/hit/read-only miss/inserted. |
| invariants | Prepared inserted disposition is not a committed cache entry until finalization. |
| ownership | Scalar in captured observation. |
| failure | Any later failure discards the prospective result. |
| cost | Fixed metadata. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md §Atomic publication](../../../../../selection_accounting.md) |

## B0061

[Lines 153–153](../../../../../../include/crown/planner/selection.hpp#L153); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L153-L153:sha256:a990ecd6d55a73fa928352857100f5ecfa26f632c65f888d06253c1ac650117a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for CacheObservation: Retain cache-use/capacity and byte-comparison diagnostics. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies CacheObservation; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for CacheObservation come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/selection.hpp](../../../../../../include/crown/planner/selection.hpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

## B0062

[Lines 154–159](../../../../../../include/crown/planner/selection.hpp#L154); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CacheObservation {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain cache-use/capacity and byte-comparison diagnostics. |
| inputs / outputs | Requested mode, optional limits, disposition, compared/binding bytes. |
| invariants | Cache-use mode/caps are observation fields excluded from artifact equality. |
| ownership | Owns scalar snapshot independent of cache lifetime. |
| failure | Counters are staged with Selection; no freshness/proof assertion. |
| cost | Fixed fields; underlying comparisons are byte-linear. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md §Atomic publication](../../../../../selection_accounting.md) |

## B0063

[Lines 160–163](../../../../../../include/crown/planner/selection.hpp#L160); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L160-L163:sha256:167eeb8e91b2987f4ad2566851f3d87cd78df1e1f4ab9b6b18746537ebb506bf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the positive support model and its conditional ownership boundary. |
| inputs / outputs | Source comments describe the neighboring PatternGuarantee and charged initialization. |
| invariants | Comments do not enforce history or establish a new tree proof. Replacement has a separately charged starting state. |
| ownership | Source text only. |
| failure | No runtime failure behavior. |
| cost | No executable work. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../../selection.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0064

[Lines 164–185](../../../../../../include/crown/planner/selection.hpp#L164); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L164-L185:sha256:7b7caa583d0f8644dd1a31a275d68a19cf30f31cd393e8418a5344584594d1b8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain a useful conditional support-action guarantee for the actual selected plan. |
| inputs / outputs | Private construction shares SelectionData; analysis()/plan() borrow its exact selected report/program. Static bound/model/input/exclusion/proof text states O_Q(I+U) for successful logical Boolean support actions. |
| invariants | Only Selection publishes a profile after a proved case. Genuine candidate geometry and executable geometry remain distinct for constant routes. No runtime compliance, retrospective CPU/delay, fresh-owner or import authority is asserted. Copies and copy-like moves preserve valid shared context; rvalue borrows are deleted. |
| ownership | One shared pointer retains the existing funded selection, source/rules/edges/candidate/program. No cloned graph, vector, account or new allocation. Borrows require a surviving profile owner. |
| failure | Noexcept handle operations and constant metadata; final owner release uses the existing graph destructors. |
| cost | O(1) descriptor work and no new allocation/cells; last-owner destruction can be proportional to retained graph size. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../../selection.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0065

[Lines 186–195](../../../../../../include/crown/planner/selection.hpp#L186); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Selection {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain a successful immutable chosen native program and complete decision context. |
| inputs / outputs | Returns proof/snapshot/candidate/plan/source/request/assessments/evidence/accounting/cache observations. |
| invariants | No new minimum, actual-owner freshness, import or deployment authority is created. Moves intentionally retain source ownership, supporting noexcept getters. |
| ownership | Shared const SelectionData retains native account and all payload owners; references need some surviving data owner. |
| failure | No public arbitrary/default construction; successful Factory publication establishes chosen/plan fields. |
| cost | Sharing is handle work; assignments/final release may destroy account-backed arrays, text and plans. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md §Atomic publication](../../../../../selection_accounting.md) |

```text
Selection(const Selection&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain another immutable Selection owner. |
| inputs / outputs | Source remains usable; no payload copy. |
| invariants | No new proof/freshness authority follows from handle lifecycle. |
| ownership | Adds shared const Data ownership. |
| failure | Declared noexcept; trusted non-null published owner is preserved. |
| cost | Shared refcount copy without new control block. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
Selection& operator=(const Selection&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace an existing Selection by shared copy. |
| inputs / outputs | Copies source and releases destination ownership. |
| invariants | No new proof/freshness authority follows from handle lifecycle. |
| ownership | Old final-owned native payload may be destroyed synchronously. |
| failure | Declared noexcept; trusted non-null published owner is preserved. |
| cost | Handle copy plus potentially size-dependent old-data teardown. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0066

[Lines 196–196](../../../../../../include/crown/planner/selection.hpp#L196); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Selection(Selection&& other) noexcept : data_(other.data_) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain source ownership during Selection move construction. |
| inputs / outputs | Copies shared data_ rather than emptying other. |
| invariants | No new proof/freshness authority follows from handle lifecycle. |
| ownership | Both handles remain usable and retain the same immutable result. |
| failure | Declared noexcept; trusted non-null published owner is preserved. |
| cost | Shared-handle copy, no evidence/payload allocation. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0067

[Lines 197–197](../../../../../../include/crown/planner/selection.hpp#L197); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Selection& operator=(Selection&& other) noexcept { data_ = other.data_; return *this; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace Selection ownership while preserving the source handle. |
| inputs / outputs | Copies other.data_; self-move is a safe shared self-copy. |
| invariants | No new proof/freshness authority follows from handle lifecycle. |
| ownership | Old final destination data can be released; source stays valid. |
| failure | Declared noexcept; trusted non-null published owner is preserved. |
| cost | Refcount copy plus potential full previous-result teardown. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0068

[Lines 198–226](../../../../../../include/crown/planner/selection.hpp#L198); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const resource::MemoryAccount& account() const &&=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject account borrowing through an rvalue Selection expression. |
| inputs / outputs | Deleted rvalue overload leaves lvalue-only account borrow. |
| invariants | A borrowed account reference cannot gain lifetime from a temporary getter call. |
| ownership | No runtime owner operation. |
| failure | Misuse fails compilation. |
| cost | No runtime cost. |
| Design | [docs/query_memory.md §Boundaries](../../../../../query_memory.md), [docs/update_patterns.md](../../../../../update_patterns.md) |

```text
static constexpr unsigned format_version = 1;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name retained selection and cache-binding format versions. |
| inputs / outputs | Adjacent constants are both one. |
| invariants | Outer selection/cache format constants stay one. Absent-pattern request bytes are unchanged; presence has a separately versioned update-pattern-admissibility record. Tags grant no import or proof authority. |
| ownership | Compile-time scalar metadata. |
| failure | No runtime validation. |
| cost | No runtime work. |
| Design | [docs/selection_binding.md §Physical source and artifact frames](../../../../../selection_binding.md), [docs/update_patterns.md](../../../../../update_patterns.md) |

```text
const CandidateSnapshot& snapshot() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose immutable retained result borrows and explicit caller exports. |
| inputs / outputs | Getters borrow snapshot/chosen/native plan/captured inputs/assessments/evidence/diagnostics; selected index/policy/reasons/timing return scalars; export_source/request allocate ordinary copies. pattern_analyses borrows one report per retained candidate when requested and an empty vector otherwise; each report retains its candidate/declaration context. |
| invariants | Published Data guarantees chosen/plan. Borrowed references need surviving Data ownership; moves preserve source ownership. Cache/evidence diagnostics assert no current-owner freshness or new proof. Conditional reports assert no trace enforcement; the original height proof remains authority. pattern_guarantee additionally shares the selected proved case, exact compiled plan/source/rules/edges and explicit logical Boolean support model; it stays conditional and does not clone a graph or assert runtime enforcement. |
| ownership | Noexcept reference getters retain no additional owner; result/account-backed data stays shared by Selection handles. Exported Request shares the immutable captured Declaration rather than deep-exporting its rules; export_record is the explicit ordinary DTO copy. |
| failure | Trusted result invariant is required; ordinary export may throw. Rvalue account borrowing is deleted. |
| cost | Getter dispatch is fixed; explicit vector/text/export copies and final owner release can be payload-dependent. The optional profile adds O(1) sharing with no allocation or rule/edge scan. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md), [docs/update_patterns.md](../../../../../update_patterns.md) |

```text
std::optional<PatternGuarantee> pattern_guarantee() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the optional conditional selected-plan support-action profile. |
| inputs / outputs | Return the corresponding owning immutable profile handle when its required proof/premises exist; absence remains explicit. |
| invariants | The method does not refresh live state, infer a total CPU bound, or add an update path. Detailed callable/class contracts state exact qualification. |
| ownership | Shares the existing funded graph; no clone or fresh account. |
| failure | Noexcept; unsupported/absent qualification returns none. |
| cost | O(1) and no allocation; last-owner graph teardown remains separately sized. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../../selection.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0069

[Lines 227–227](../../../../../../include/crown/planner/selection.hpp#L227); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit Selection(std::shared_ptr<const detail::SelectionData> data) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt fully prepared immutable selection ownership. |
| inputs / outputs | Friend Factory moves shared Data into handle. |
| invariants | Caller must supply complete chosen/plan and finalized data; constructor itself validates nothing. |
| ownership | Shares native account-backed result. |
| failure | Noexcept; no public arbitrary payload constructor. |
| cost | One handle move without result copying. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../../selection_accounting.md) |

## B0070

[Lines 228–231](../../../../../../include/crown/planner/selection.hpp#L228); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L228-L231:sha256:1752091e17f3496726e986361d9065615654b25c544f6bde3ca789d1e60757ff
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain immutable successful result backing behind the public handle. |
| inputs / outputs | Single shared Data owner. |
| invariants | Friend-only construction and source-preserving moves keep ordinary public getters non-null. |
| ownership | Data retains receiving account plus shared proof/family/evidence/program owners. |
| failure | No field-level validation; no public raw pointer injection. |
| cost | Handle retention; final release can traverse complete native result payload. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0071

[Lines 232–242](../../../../../../include/crown/planner/selection.hpp#L232); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Attempt {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return fixed diagnostics and optional complete Selection from a noexcept call. |
| inputs / outputs | Stop/stage/result, usage, component/resource/reasons and evaluation counts. |
| invariants | Failures publish no selection/cache mutation; partial usage is diagnostic and never resumable state. |
| ownership | Owns scalar snapshot and optional immutable handle. |
| failure | Before Operation construction only already captured preparation diagnostics can be retained. |
| cost | Fixed result transfer; last shared result release may be large. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md §Atomic publication](../../../../../selection_accounting.md) |

## B0072

[Lines 243–246](../../../../../../include/crown/planner/selection.hpp#L243); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Attempt select(const CandidateSnapshot&, const Source&,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose pure synchronous whole-retained-family selection. |
| inputs / outputs | Typed snapshot/source/request/as-of evidence and optional exclusive cache yield Attempt. |
| invariants | No provider advancement, current-owner gate, migration or new height proof. |
| ownership | Borrows caller inputs for the call; success captures owners/text. |
| failure | Noexcept diagnostics; unsupported features or resources never silently become fallback success. |
| cost | Complete admission/ranking/binding/lowering/cache transaction; actual scalar/container costs remain. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md §Atomic publication](../../../../../selection_accounting.md) |
