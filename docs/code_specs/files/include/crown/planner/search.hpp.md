# `include/crown/planner/search.hpp` — block usage map

[Source](../../../../../../include/crown/planner/search.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Search the finite canonical tree space and retain resumable evidence for exact minimum-height claims.

Snapshot SHA-256: `a752c661732ef55559564d2c35b2217b5b94b29629c06d34585aee61f5244dff`. 323 lines partitioned into 51 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [search](../../../../subsystem_contracts.md#search). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../../tree_oracle.md), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../../candidate_alternatives.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–24](../../../../../../include/crown/planner/search.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. | source comment (unverified): // Owned in-process exact-search and independent proof-replay continuations. · [reviewed contract](#b0001) |
| [B0002 · 25–25](../../../../../../include/crown/planner/search.hpp#L25) | Type/record definition: enum class SearchPolicy | source comment (unverified): // Policy controls upper-handle exposure; both modes continue exact search and independent · [reviewed contract](#b0002) |
| [B0003 · 26–27](../../../../../../include/crown/planner/search.hpp#L26) | Explanatory comments or spacing. | source comment (unverified): // Algorithm names describe proof families; production search has no public v1 toggle. See · [reviewed contract](#b0003) |
| [B0004 · 28–28](../../../../../../include/crown/planner/search.hpp#L28) | Type/record definition: enum class ProofAlgorithm | source comment (unverified): // Algorithm names describe proof families; production search has no public v1 toggle. See · [reviewed contract](#b0004) |
| [B0005 · 29–30](../../../../../../include/crown/planner/search.hpp#L29) | Explanatory comments or spacing. | source comment (unverified): // continuation_v1 names attempted controlled transitions rather than CPU or byte accounting. · [reviewed contract](#b0005) |
| [B0006 · 31–31](../../../../../../include/crown/planner/search.hpp#L31) | Type/record definition: enum class AccountingVersion | source comment (unverified): // continuation_v1 names attempted controlled transitions rather than CPU or byte accounting. · [reviewed contract](#b0006) |
| [B0007 · 32–36](../../../../../../include/crown/planner/search.hpp#L32) | Explanatory comments or spacing. | source comment (unverified): // Finite counters never wrap. Exhaustion is an explicit terminal reason. · [reviewed contract](#b0007) |
| [B0008 · 37–40](../../../../../../include/crown/planner/search.hpp#L37) | Type/record definition: struct PhaseCeiling | source comment (unverified): // Finite counters never wrap. Exhaustion is an explicit terminal reason. · [reviewed contract](#b0008) |
| [B0009 · 41–42](../../../../../../include/crown/planner/search.hpp#L41) | Explanatory comments or spacing. | source comment (unverified): // Separate phase ceilings from active-worker logical depth; these options do not cap all · [reviewed contract](#b0009) |
| [B0010 · 43–50](../../../../../../include/crown/planner/search.hpp#L43) | Type/record definition: struct ContinuationLimits | source comment (unverified): // Separate phase ceilings from active-worker logical depth; these options do not cap all · [reviewed contract](#b0010) |
| [B0011 · 51–52](../../../../../../include/crown/planner/search.hpp#L51) | Explanatory comments or spacing. | source comment (unverified): // Fix policy and binding at admission; later changes can only extend resources. See · [reviewed contract](#b0011) |
| [B0012 · 53–58](../../../../../../include/crown/planner/search.hpp#L53) | Type/record definition: struct SearchOptions | source comment (unverified): // Fix policy and binding at admission; later changes can only extend resources. See · [reviewed contract](#b0012) |
| [B0013 · 59–60](../../../../../../include/crown/planner/search.hpp#L59) | Explanatory comments or spacing. | source comment (unverified): // Configure replay resources without changing or trusting the admitted proof claim. See · [reviewed contract](#b0013) |
| [B0014 · 61–64](../../../../../../include/crown/planner/search.hpp#L61) | Type/record definition: struct ReplayOptions | source comment (unverified): // Configure replay resources without changing or trusting the admitted proof claim. See · [reviewed contract](#b0014) |
| [B0015 · 65–66](../../../../../../include/crown/planner/search.hpp#L65) | Explanatory comments or spacing. | source comment (unverified): // A nonnegative zero grant is inert; negative time is invalid, and moved-from owners are · [reviewed contract](#b0015) |
| [B0016 · 67–70](../../../../../../include/crown/planner/search.hpp#L67) | Type/record definition: struct WorkQuantum | source comment (unverified): // A nonnegative zero grant is inert; negative time is invalid, and moved-from owners are · [reviewed contract](#b0016) |
| [B0017 · 71–73](../../../../../../include/crown/planner/search.hpp#L71) | Explanatory comments or spacing. | source comment (unverified): // Read phase with typed authority/result; cancelled is terminal even when the result is · [reviewed contract](#b0017) |
| [B0018 · 74–77](../../../../../../include/crown/planner/search.hpp#L74) | Type/record definition: enum class SearchPhase | source comment (unverified): // Read phase with typed authority/result; cancelled is terminal even when the result is · [reviewed contract](#b0018) |
| [B0019 · 78–79](../../../../../../include/crown/planner/search.hpp#L78) | Explanatory comments or spacing. | source comment (unverified): // Replay phase is progress; valid is withheld until final checked-artifact publication. See · [reviewed contract](#b0019) |
| [B0020 · 80–84](../../../../../../include/crown/planner/search.hpp#L80) | Type/record definition: enum class ReplayPhase | source comment (unverified): // Replay phase is progress; valid is withheld until final checked-artifact publication. See · [reviewed contract](#b0020) |
| [B0021 · 85–86](../../../../../../include/crown/planner/search.hpp#L85) | Explanatory comments or spacing. | source comment (unverified): // Separate grant/resource stops from terminal proof outcomes; a reason is never proof · [reviewed contract](#b0021) |
| [B0022 · 87–91](../../../../../../include/crown/planner/search.hpp#L87) | Type/record definition: enum class StopReason | source comment (unverified): // Separate grant/resource stops from terminal proof outcomes; a reason is never proof · [reviewed contract](#b0022) |
| [B0023 · 92–93](../../../../../../include/crown/planner/search.hpp#L92) | Explanatory comments or spacing. | source comment (unverified): // Only completed independent whole-root proof upgrades lower evidence. See · [reviewed contract](#b0023) |
| [B0024 · 94–94](../../../../../../include/crown/planner/search.hpp#L94) | Type/record definition: enum class BoundEvidence | source comment (unverified): // Only completed independent whole-root proof upgrades lower evidence. See · [reviewed contract](#b0024) |
| [B0025 · 95–96](../../../../../../include/crown/planner/search.hpp#L95) | Explanatory comments or spacing. | source comment (unverified): // Interpret unfinished with phase: cancelled owners cannot resume. See · [reviewed contract](#b0025) |
| [B0026 · 97–97](../../../../../../include/crown/planner/search.hpp#L97) | Type/record definition: enum class ResultKind | source comment (unverified): // Interpret unfinished with phase: cancelled owners cannot resume. See · [reviewed contract](#b0026) |
| [B0027 · 98–99](../../../../../../include/crown/planner/search.hpp#L98) | Explanatory comments or spacing. | source comment (unverified): // Resource raises are atomic and monotone; even an accepted equal request increments · [reviewed contract](#b0027) |
| [B0028 · 100–100](../../../../../../include/crown/planner/search.hpp#L100) | Type/record definition: enum class LimitChange | source comment (unverified): // Resource raises are atomic and monotone; even an accepted equal request increments · [reviewed contract](#b0028) |
| [B0029 · 101–103](../../../../../../include/crown/planner/search.hpp#L101) | Explanatory comments or spacing. | source comment (unverified): // Attempts include failed or blocked units; active time/failure diagnostics saturate and · [reviewed contract](#b0029) |
| [B0030 · 104–112](../../../../../../include/crown/planner/search.hpp#L104) | Type/record definition: struct WorkCounters | source comment (unverified): // Attempts include failed or blocked units; active time/failure diagnostics saturate and · [reviewed contract](#b0030) |
| [B0031 · 113–114](../../../../../../include/crown/planner/search.hpp#L113) | Explanatory comments or spacing. | source comment (unverified): // Null lower also occurs in default/moved-from snapshots; only checked infeasible=true proves · [reviewed contract](#b0031) |
| [B0032 · 115–125](../../../../../../include/crown/planner/search.hpp#L115) | Type/record definition: struct HeightInterval | source comment (unverified): // Null lower also occurs in default/moved-from snapshots; only checked infeasible=true proves · [reviewed contract](#b0032) |
| [B0033 · 126–127](../../../../../../include/crown/planner/search.hpp#L126) | Explanatory comments or spacing. | source comment (unverified): // Progress is scalar observation: producer completion and an upper are distinct from · [reviewed contract](#b0033) |
| [B0034 · 128–139](../../../../../../include/crown/planner/search.hpp#L128) | Type/record definition: struct SearchProgress | source comment (unverified): // Progress is scalar observation: producer completion and an upper are distinct from · [reviewed contract](#b0034) |
| [B0035 · 140–141](../../../../../../include/crown/planner/search.hpp#L140) | Explanatory comments or spacing. | source comment (unverified): // complete can mean terminal rejection; valid requires the fully published checked artifact. · [reviewed contract](#b0035) |
| [B0036 · 142–150](../../../../../../include/crown/planner/search.hpp#L142) | Type/record definition: struct ReplayProgress | source comment (unverified): // complete can mean terminal rejection; valid requires the fully published checked artifact. · [reviewed contract](#b0036) |
| [B0037 · 151–154](../../../../../../include/crown/planner/search.hpp#L151) | Explanatory comments or spacing. | source comment (unverified): // Value snapshots keep stop reporting nonallocating. For a live owner, · [reviewed contract](#b0037) |
| [B0038 · 155–155](../../../../../../include/crown/planner/search.hpp#L155) | Type/record definition: struct SearchAdvance | source comment (unverified): // Value snapshots keep stop reporting nonallocating. For a live owner, · [reviewed contract](#b0038) |
| [B0039 · 156–156](../../../../../../include/crown/planner/search.hpp#L156) | Type/record definition: struct ReplayAdvance |  · [reviewed contract](#b0039) |
| [B0040 · 157–162](../../../../../../include/crown/planner/search.hpp#L157) | Explanatory comments or spacing. | source comment (unverified): // Immutable owned exact binding. No default construction or caller mutation. · [reviewed contract](#b0040) |
| [B0041 · 163–177](../../../../../../include/crown/planner/search.hpp#L163) | Type/record definition: class SearchBinding | source comment (unverified): // Immutable owned exact binding. No default construction or caller mutation. · [reviewed contract](#b0041) |
| [B0042 · 178–181](../../../../../../include/crown/planner/search.hpp#L178) | Explanatory comments or spacing. | source comment (unverified): // A complete, P02-checked tree. Establishes ONLY an upper bound. · [reviewed contract](#b0042) |
| [B0043 · 182–196](../../../../../../include/crown/planner/search.hpp#L182) | Type/record definition: class ValidatedIncumbent | source comment (unverified): // A complete, P02-checked tree. Establishes ONLY an upper bound. · [reviewed contract](#b0043) |
| [B0044 · 197–199](../../../../../../include/crown/planner/search.hpp#L197) | Explanatory comments or spacing. | source comment (unverified): // Retain matching upper/lower evidence for this exact admitted query; a prefix optimum stays · [reviewed contract](#b0044) |
| [B0045 · 200–215](../../../../../../include/crown/planner/search.hpp#L200) | Type/record definition: class VerifiedOptimum | source comment (unverified): // Retain matching upper/lower evidence for this exact admitted query; a prefix optimum stays · [reviewed contract](#b0045) |
| [B0046 · 216–218](../../../../../../include/crown/planner/search.hpp#L216) | Explanatory comments or spacing. | source comment (unverified): // Retain a complete no-tree proof for this binding; prefix infeasibility is not original · [reviewed contract](#b0046) |
| [B0047 · 219–232](../../../../../../include/crown/planner/search.hpp#L219) | Type/record definition: class VerifiedInfeasible | source comment (unverified): // Retain a complete no-tree proof for this binding; prefix infeasibility is not original · [reviewed contract](#b0047) |
| [B0048 · 233–237](../../../../../../include/crown/planner/search.hpp#L233) | Explanatory comments or spacing. | source comment (unverified): // External certificate replay produces a checked authority handle; arbitrary · [reviewed contract](#b0048) |
| [B0049 · 238–253](../../../../../../include/crown/planner/search.hpp#L238) | Type/record definition: class CheckedCertificate | source comment (unverified): // External certificate replay produces a checked authority handle; arbitrary · [reviewed contract](#b0049) |
| [B0050 · 254–289](../../../../../../include/crown/planner/search.hpp#L254) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Exclusive single caller; no background work, callbacks or borrowed inputs. · [reviewed contract](#b0050) |
| [B0051 · 290–323](../../../../../../include/crown/planner/search.hpp#L290) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Own claim replay against the supplied model; serialized exact binding belongs to IO and · [reviewed contract](#b0051) |

## B0001

[Lines 1–24](../../../../../../include/crown/planner/search.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L24:sha256:32b807dafad44a446824ec73525de7719de73481c2f4b2fdac1849fce9309ba9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use #pragma once to suppress repeated header processing within a translation unit. Make #include "crown/planner/oracle.hpp", #include &lt;chrono&gt;, #include &lt;cstdint&gt;, #include &lt;memory&gt;, #include &lt;optional&gt;, #include &lt;string_view&gt; available to include/crown/planner/search.hpp; open crown::planner and continuation_detail; forward-declare BindingData, IncumbentData, OptimumData, InfeasibleData, CheckedCertificateData, ArtifactFactory. Attached note: Owned in-process exact-search and independent proof-replay continuations. Existing oracle.hpp entry points and v1/v2 certificate formats stay intact. Policy controls upper-handle exposure; both modes continue exact search and independent replay. |
| inputs / outputs | Preprocessor directives resolve compile-time declarations. This block has no runtime call inputs or result. |
| invariants | Includes, namespace openings, aliases, and forward declarations determine C++ name visibility and type availability; they do not validate planner data or grant proof authority. |
| ownership | No runtime object is owned by the include or scope directives. Any state belongs to the types and functions declared after them. |
| failure | A missing header, incompatible declaration, or ill-formed type use fails during compilation; runtime failures remain in the called code. |
| cost | Adds preprocessing, parsing, and any later template-instantiation work in this translation unit. It adds no runtime timer, counter, branch, or allocation. |
| Design | [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0002

[Lines 25–25](../../../../../../include/crown/planner/search.hpp#L25); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class SearchPolicy { strict, best_found };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose whether a session exposes its checked incumbent before full proof completion. |
| inputs / outputs | strict withholds incumbent(); best_found can return the latest P02-checked upper. |
| invariants | Both policies run the same exact producer and independent replay; neither permits an unfinished lower proof to establish a minimum. |
| ownership | Scalar policy is copied into the admitted owner. |
| failure | create rejects unknown enum values; policy is immutable after admission. |
| cost | Fixed option storage; choosing best_found does not bound the remaining search. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md) |

## B0003

[Lines 26–27](../../../../../../include/crown/planner/search.hpp#L26); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L27:sha256:23b1e8cf559f7005a404cba46ca5f5cedec441a381d92c7cd3dceb73b4c4d383
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ProofAlgorithm: Algorithm names describe proof families; production search has no public v1 toggle. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ProofAlgorithm; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ProofAlgorithm come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0004

[Lines 28–28](../../../../../../include/crown/planner/search.hpp#L28); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class ProofAlgorithm { partition_v1, partition_v2 };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the supported certificate algorithm families without offering a public producer switch. |
| inputs / outputs | Enumerates v1 and v2 terminology; SearchOptions contains no algorithm field. |
| invariants | Production ExactSearch emits v2; independent certificate replay dispatches existing v1/v2 algorithm strings. |
| ownership | Enum owns no producer, proof or binding. |
| failure | Casting an enum does not select an algorithm or validate a certificate. |
| cost | Fixed-size tag only; algorithm execution occurs in the retained workers. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md) |

## B0005

[Lines 29–30](../../../../../../include/crown/planner/search.hpp#L29); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L30:sha256:9948c511f132652d73df52bdf859844a74fe555cc83e76f6a54b65ae77695ca1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for AccountingVersion: continuation_v1 names attempted controlled transitions rather than CPU or byte accounting. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies AccountingVersion; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for AccountingVersion come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0006

[Lines 31–31](../../../../../../include/crown/planner/search.hpp#L31); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class AccountingVersion { continuation_v1 };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify the controlled-transition accounting convention attached to admitted input. |
| inputs / outputs | SearchBinding.accounting() returns the admission tag. |
| invariants | The tag describes cursor/control transition counting, not CPU instruction, allocator-byte or historical P03 work equivalence. |
| ownership | Stored as a scalar in immutable BindingData. |
| failure | No caller-editable accounting override exists in create options. |
| cost | Fixed tag; comparison/storage costs do not include counted algorithm work. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../../planner_continuations.md) |

## B0007

[Lines 32–36](../../../../../../include/crown/planner/search.hpp#L32); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L32-L36:sha256:79f25c18f59477dffbfdbeca9b48d3612705cdc7d4d1a3afc7298c3cb616fb0c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for PhaseCeiling: Finite counters never wrap. Exhaustion is an explicit terminal reason. Time below is ACTIVE execution time, excluding time between advance calls. Cumulative work and active-time ceilings are separate; null is unbounded and time stops are cooperative. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies PhaseCeiling; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for PhaseCeiling come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0008

[Lines 37–40](../../../../../../include/crown/planner/search.hpp#L37); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhaseCeiling {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure one cumulative producer or replay phase allowance. |
| inputs / outputs | Optional attempted-work and active-nanosecond ceilings; null means unbounded. |
| invariants | Work is checked before the next attempt; cooperative active sampling can exceed a time ceiling during an indivisible operation. |
| ownership | Owns scalar options copied into a ResourceLedger. |
| failure | Negative active time rejects admission/raising; exhaustion retains work unless counter overflow is terminal. |
| cost | No allocator-byte cap or hard latency bound; ordinary container/scalar costs remain separate. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../../planner_continuations.md) |

## B0009

[Lines 41–42](../../../../../../include/crown/planner/search.hpp#L41); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L42:sha256:a65d0d0b507a0ba257814bd0093543c1d423cac38b77fd77414b51d5440a798c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ContinuationLimits: Separate phase ceilings from active-worker logical depth; these options do not cap all retained bytes. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ContinuationLimits; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ContinuationLimits come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0010

[Lines 43–50](../../../../../../include/crown/planner/search.hpp#L43); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ContinuationLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep independent producer/replay ceilings and one logical active-worker depth ceiling. |
| inputs / outputs | Producer includes witness/P02/export; replay includes independent replay and final typed-owner preparation. |
| invariants | Depth measures active worker nesting, not the sum of all parked frames or breadth/storage. Empty administrative input uses zero depth. |
| ownership | Value options are retained by ExactSearch; they do not own worker storage. |
| failure | raise_limits permits only monotone extensions above consumed phase work/time, with no counter reset. |
| cost | Fixed configuration; retained search memory can grow independently of the logical depth/work ceilings. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../../planner_continuations.md), [docs/planner_continuations.md §Grants and retained state](../../../../../planner_continuations.md) |

## B0011

[Lines 51–52](../../../../../../include/crown/planner/search.hpp#L51); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L52:sha256:9cf4da5b7e3dd4b5985e560b05431d326056ab70a78c471871d79a81140dfa2d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for SearchOptions: Fix policy and binding at admission; later changes can only extend resources. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies SearchOptions; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for SearchOptions come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0012

[Lines 53–58](../../../../../../include/crown/planner/search.hpp#L53); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SearchOptions {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit the immutable search policy with its resource ceilings. |
| inputs / outputs | Policy defaults strict; producer/replay/depth limits configure the owned session. |
| invariants | No query, policy or algorithm replacement is accepted by advance; only monotone resource raising is available. |
| ownership | Copied into Impl while binding ownership remains separate. |
| failure | Unknown policy and invalid negative time ceilings reject create. |
| cost | Small option copy; catalog/query admission and search allocations are separate. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/planner_continuations.md §Resource accounting](../../../../../planner_continuations.md) |

## B0013

[Lines 59–60](../../../../../../include/crown/planner/search.hpp#L59); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L59-L60:sha256:6323d0fc48368bccb08aabebad7285b43513483d79c1ea9632f181d1bd5fb2fe
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ReplayOptions: Configure replay resources without changing or trusting the admitted proof claim. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ReplayOptions; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ReplayOptions come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0014

[Lines 61–64](../../../../../../include/crown/planner/search.hpp#L61); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ReplayOptions {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure standalone independent certificate replay. |
| inputs / outputs | One cumulative phase allowance and optional active logical-depth ceiling. |
| invariants | Options govern checking and typed-artifact preparation, not trust in the caller-supplied claim. |
| ownership | Value-owned by CertificateReplay. |
| failure | Negative active time rejects; ceilings may later rise monotonically without changing the certificate. |
| cost | Small configuration; proof maps, port caches and upper validation keep their actual storage costs. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../../planner_continuations.md) |

## B0015

[Lines 65–66](../../../../../../include/crown/planner/search.hpp#L65); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L65-L66:sha256:8abc5efdab3098ec351930f356780aa28c81b7036c2796b2fa74f307818dd87c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for WorkQuantum: A nonnegative zero grant is inert; negative time is invalid, and moved-from owners are detected first. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies WorkQuantum; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for WorkQuantum come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0016

[Lines 67–70](../../../../../../include/crown/planner/search.hpp#L67); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WorkQuantum {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Grant at most a requested number of attempted transitions and cooperative wall duration to one advance. |
| inputs / outputs | work defaults one; optional active_time bounds the nonzero advance call. |
| invariants | Negative duration takes invalid_quantum precedence; otherwise zero work/time is inert before terminal checks or clock samples. |
| ownership | Passed by value; retained session state does not borrow it. |
| failure | Invalid/zero grants do not overwrite stored last_stop; moved-from facade detection precedes this helper. |
| cost | Per-call grant is distinct from cumulative ledgers; allocator/container operations inside a transition are not split. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../../planner_continuations.md) |

## B0017

[Lines 71–73](../../../../../../include/crown/planner/search.hpp#L71); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L71-L73:sha256:f3779b20fefd26299329367b44f98abe21e33f6879ca580ccbe6b982a10df35a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for SearchPhase: Read phase with typed authority/result; cancelled is terminal even when the result is unfinished. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies SearchPhase; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for SearchPhase come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0018

[Lines 74–77](../../../../../../include/crown/planner/search.hpp#L74); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class SearchPhase {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the active ExactSearch driver stage at snapshot time. |
| inputs / outputs | Includes preprocessing/search, witness/P02, export/replay, completed, failed, cancelled and moved-from phases. |
| invariants | Phase is descriptive progress; optimum/infeasibility access requires completed typed publication. |
| ownership | Scalar copied into SearchProgress. |
| failure | A cancelled owner is terminal even though ResultKind remains unfinished; phase must accompany result interpretation. |
| cost | Fixed tag; observing it advances no worker. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/planner_continuations.md §Lifetime and output](../../../../../planner_continuations.md) |

## B0019

[Lines 78–79](../../../../../../include/crown/planner/search.hpp#L78); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L78-L79:sha256:b7a11cf3fbafdfe800c2822815d8c88a6b7ba8465d4b3f2892135994b21e69cd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ReplayPhase: Replay phase is progress; valid is withheld until final checked-artifact publication. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ReplayPhase; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ReplayPhase come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0020

[Lines 80–84](../../../../../../include/crown/planner/search.hpp#L80); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class ReplayPhase {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe independent checker progress and outer replay-owner state. |
| inputs / outputs | Names dispatch, upper check, reconstruction/indexing/claim/root phases and terminal states. |
| invariants | Outer post-check owner preparation reports match_root until the final artifact is published. |
| ownership | Scalar snapshot; it carries no certificate owner. |
| failure | failed is terminal and complete without valid; cancelled is terminal but not marked complete. |
| cost | Fixed tag read without claim traversal. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/planner_continuations.md §Lifetime and output](../../../../../planner_continuations.md) |

## B0021

[Lines 85–86](../../../../../../include/crown/planner/search.hpp#L85); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L85-L86:sha256:9db1e7722a9a0ea12a335b1c72412f4fd5110385b201d470ae481c7afb65e7ae
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for StopReason: Separate grant/resource stops from terminal proof outcomes; a reason is never proof authority. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies StopReason; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for StopReason come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0022

[Lines 87–91](../../../../../../include/crown/planner/search.hpp#L87); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class StopReason {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish per-call stops, resumable resource boundaries and terminal outcomes. |
| inputs / outputs | advance returns a reason independently of the stored progress last_stop. |
| invariants | Zero/invalid grants are ephemeral; total/depth/allocation stops retain owners; counter/internal/proof failures are terminal. |
| ownership | Enum stores no diagnostic text or evidence. |
| failure | A stop reason alone never establishes feasibility or infeasibility; callers inspect phase and owning artifacts. |
| cost | Fixed result tag permits noexcept stop reporting under persistent allocation failure. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../../planner_continuations.md), [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md) |

## B0023

[Lines 92–93](../../../../../../include/crown/planner/search.hpp#L92); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L92-L93:sha256:89d1d66614731977e1b102f3ad011c253aab1af59a13c4e12bb453ad6105965f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for BoundEvidence: Only completed independent whole-root proof upgrades lower evidence. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies BoundEvidence; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for BoundEvidence come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0024

[Lines 94–94](../../../../../../include/crown/planner/search.hpp#L94); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class BoundEvidence { universal, independently_checked };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Label the basis for a reported lower bound. |
| inputs / outputs | universal means zero for a bound empty body or one for bound nonempty unfinished search; independently_checked follows full publication. |
| invariants | Visited children or a valid incumbent cannot upgrade whole-query lower evidence. |
| ownership | Scalar in mutable HeightInterval, which itself confers no authority. |
| failure | Edited progress labels do not create VerifiedOptimum or VerifiedInfeasible. |
| cost | Fixed label; actual lower replay may be exponential. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../../planner_proofs.md) |

## B0025

[Lines 95–96](../../../../../../include/crown/planner/search.hpp#L95); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L95-L96:sha256:e3e353f35d11288c620221a082522b93ba8a66e1add5c0d9a6b4b1ec87283d86
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ResultKind: Interpret unfinished with phase: cancelled owners cannot resume. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ResultKind; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ResultKind come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0026

[Lines 97–97](../../../../../../include/crown/planner/search.hpp#L97); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class ResultKind { unfinished, verified_optimum, verified_infeasible, failed };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Summarize the published exact-search result category. |
| inputs / outputs | Computed from stage: completed owner exposes optimum/infeasible, failed exposes failed, cancelled remains unfinished. |
| invariants | unfinished does not guarantee resumability; consult phase/last_stop for cancellation. |
| ownership | Scalar snapshot owns no proof. |
| failure | Moved-from progress uses failed without making a query-family conclusion. |
| cost | Fixed tag read; no result extraction allocation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/planner_continuations.md §Lifetime and output](../../../../../planner_continuations.md) |

## B0027

[Lines 98–99](../../../../../../include/crown/planner/search.hpp#L98); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L98-L99:sha256:a29843781a025f3ed162d03ece9789388a0d969a264cb186a14e77faf4a44f50
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for LimitChange: Resource raises are atomic and monotone; even an accepted equal request increments revision. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies LimitChange; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for LimitChange come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0028

[Lines 100–100](../../../../../../include/crown/planner/search.hpp#L100); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class LimitChange { applied, not_monotone, below_consumed, invalid, terminal };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report resource-extension acceptance without throwing or mutating on rejection. |
| inputs / outputs | applied increments revision even for equal ceilings; terminal covers moved-from and all terminal owners. |
| invariants | Finite-to-unbounded is monotone; unbounded-to-finite or decreases reject before consumed-value checks. |
| ownership | Returned scalar; new options are copied only on successful validation. |
| failure | Negative time or exhausted revision returns invalid; rejected changes retain old options and counters. |
| cost | Bounded scalar comparisons independent of search size. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../../planner_continuations.md) |

## B0029

[Lines 101–103](../../../../../../include/crown/planner/search.hpp#L101); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L101-L103:sha256:038986c60f0b9d8ba9e0c30be3eaebf8e800272987fbe3011f9b03d4dcb83a84
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for WorkCounters: Attempts include failed or blocked units; active time/failure diagnostics saturate and depth tracks the active worker. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies WorkCounters; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for WorkCounters come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0030

[Lines 104–112](../../../../../../include/crown/planner/search.hpp#L104); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WorkCounters {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose attempted/committed work, failures, active time and saved logical depth. |
| inputs / outputs | attempted counts charged units including blocked/allocation-failed attempts; committed excludes those failures. |
| invariants | Attempt/commit counters stop before wrap; allocation_failures and active_nanoseconds saturate. current_depth is active-worker depth, peak is its historical maximum. |
| ownership | Owns numeric snapshot fields only. |
| failure | Counters are observations, not byte/CPU/proof bounds; cancellation zeros current depth while preserving peak. |
| cost | Fixed snapshot copy; sampling clocks and underlying worker/container operations have separate costs. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../../planner_continuations.md) |

```text
bool operator==(const WorkCounters&) const = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare every recorded work-counter field for snapshot equality. |
| inputs / outputs | Returns memberwise equality of attempts, commits, diagnostics and depths. |
| invariants | Equal counters do not establish equal search bindings or proof validity. |
| ownership | Borrows two value snapshots. |
| failure | No validation or error conversion occurs. |
| cost | Fixed numeric field comparisons without traversal/allocation. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../../planner_continuations.md) |

## B0031

[Lines 113–114](../../../../../../include/crown/planner/search.hpp#L113); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L113-L114:sha256:7f248e4dec44658e1297cc7e0eb315ca9bfc533a9b682e55dc58d6ead1f86db3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for HeightInterval: Null lower also occurs in default/moved-from snapshots; only checked infeasible=true proves an empty family. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies HeightInterval; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for HeightInterval come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0032

[Lines 115–125](../../../../../../include/crown/planner/search.hpp#L115); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct HeightInterval {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe scalar lower/upper observations without replacing typed authority. |
| inputs / outputs | Bound live search starts at universal zero/one; checked incumbent supplies upper even under strict policy; complete replay matches lower or proves infinity. |
| invariants | Default and moved-from snapshots can have null lower with infeasible=false. Only independently checked infeasible=true denotes an empty family; no lower is inferred from null alone. |
| ownership | Owns optional scalars, not the upper tree or proof. |
| failure | A mutable interval cannot manufacture authority; consumers inspect evidence, phase and typed owners. |
| cost | Fixed-size copy; no tree or claim traversal. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../../planner_proofs.md) |

```text
bool operator==(const HeightInterval&) const = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare all scalar interval and evidence fields. |
| inputs / outputs | Tests lower, upper, lower_evidence and infeasible by value. |
| invariants | Matching numeric intervals do not imply matching bindings or the same checked artifacts. |
| ownership | Borrows value snapshots only. |
| failure | No consistency validation occurs when comparing caller-edited aggregates. |
| cost | Fixed optional/scalar comparisons. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md) |

## B0033

[Lines 126–127](../../../../../../include/crown/planner/search.hpp#L126); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L126-L127:sha256:1f66fbab35aa2217b1d4b25b1f82117f699175f264b56457ff28fdc8ae3928fb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for SearchProgress: Progress is scalar observation: producer completion and an upper are distinct from completed independent proof. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies SearchProgress; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for SearchProgress come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0034

[Lines 128–139](../../../../../../include/crown/planner/search.hpp#L128); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SearchProgress {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a nonallocating owned-search snapshot. |
| inputs / outputs | Contains phase/result, scalar bounds, completion flags, both ledgers, structural counters and revision. |
| invariants | producer_complete precedes independent proof; proof_complete is true only at full publication. Strict can show scalar upper while withholding incumbent handles. |
| ownership | Copies scalar statistics only; owns neither tree nor certificate. |
| failure | Moved-from snapshot has failed result and no binding-derived lower; cancelled snapshot can retain a checked upper and unfinished result. |
| cost | Fixed-sized copy; collecting saved producer counters does not rescan the search. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/planner_continuations.md §Resource accounting](../../../../../planner_continuations.md) |

## B0035

[Lines 140–141](../../../../../../include/crown/planner/search.hpp#L140); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L140-L141:sha256:b5ef11439bdeafebae07d18c1498d981a084452ffd855e1a5010093a23034bbb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ReplayProgress: complete can mean terminal rejection; valid requires the fully published checked artifact. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ReplayProgress; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ReplayProgress come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0036

[Lines 142–150](../../../../../../include/crown/planner/search.hpp#L142); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ReplayProgress {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return standalone checker/owner preparation progress. |
| inputs / outputs | Reports phase, stop, complete/valid, checked-claim prefix, work and revision. |
| invariants | complete also covers terminal failure; valid requires final checked-artifact publication. A checked prefix grants no root authority. |
| ownership | Owns fixed scalar snapshot fields. |
| failure | Cancellation/movement remain distinct phases and do not mark a proof valid. |
| cost | Fixed snapshot copy; checker claim count is a saved counter. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/planner_continuations.md §Resource accounting](../../../../../planner_continuations.md) |

## B0037

[Lines 151–154](../../../../../../include/crown/planner/search.hpp#L151); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L151-L154:sha256:a6e216c50fb4d63e0b36f7c2a5345e6537fc4633554fc7d34e3bd5337d800643
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for SearchAdvance: Value snapshots keep stop reporting nonallocating. For a live owner, nonnegative zero-work/time grants return a quantum stop without changing stored progress. Negative time is invalid; moved-from owners report moved_from. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies SearchAdvance; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for SearchAdvance come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0038

[Lines 155–155](../../../../../../include/crown/planner/search.hpp#L155); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SearchAdvance { StopReason stopped_for; SearchProgress progress; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pair an ephemeral per-call stop with the current search snapshot. |
| inputs / outputs | Returned by value from noexcept advance. |
| invariants | For nonnegative zero grants on a live owner, stored fields remain unchanged; negative time and moved-from precedence still apply. |
| ownership | Owns scalars only, with no borrowed data. |
| failure | The stop can differ from progress.last_stop because inert/invalid calls leave stored last_stop alone. |
| cost | Fixed-size reporting without message or evidence allocation. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../../planner_continuations.md) |

## B0039

[Lines 156–156](../../../../../../include/crown/planner/search.hpp#L156); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ReplayAdvance { StopReason stopped_for; ReplayProgress progress; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pair an ephemeral replay call stop with its saved progress. |
| inputs / outputs | Noexcept advance returns this fixed value result. |
| invariants | Zero/invalid grants leave a live owner state unchanged; moved-from returns its explicit moved_from snapshot. |
| ownership | Contains scalars, not checked-certificate ownership. |
| failure | A returned stop never upgrades checked_claims or valid. |
| cost | Fixed report copy under persistent allocation failure. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../../planner_continuations.md) |

## B0040

[Lines 157–162](../../../../../../include/crown/planner/search.hpp#L157); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L157-L162:sha256:2dca9250fb85828115a3172bf169745019dcb1229c563c660dccaffeeb47aae2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for SearchBinding: Immutable owned exact binding. No default construction or caller mutation. Creation validates Catalog/Query; canonical binding serialization is explicit IO work, not hidden in advance. Getters require valid() after a move. Retain the exact admitted model; prefix search binding is never upgraded to the original query by this handle. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies SearchBinding; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for SearchBinding come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0041

[Lines 163–177](../../../../../../include/crown/planner/search.hpp#L163); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class SearchBinding {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own and share the exact admitted Catalog/Query identity. |
| inputs / outputs | catalog/query return borrowed model references; accounting returns the immutable admission convention. |
| invariants | Binding is exactly the supplied model, including original or induced-prefix IDs/heads. It is not a physical source program, semantic hash or permission to transport a proof across scopes. |
| ownership | Shared immutable ownership of BindingData model payload; reference getters require a surviving owner of that payload, not necessarily the original facade. |
| failure | No public default/arbitrary-payload constructor. valid() checks presence; moved-from content access throws invalid_search_handle. |
| cost | Copy/move construction retains/transfers a handle; assignments may release large last-owned payloads. Shared copies do not allocate new payload/control blocks. |
| Design | [docs/residual_candidates.md §Exactness and owning artifacts](../../../../../residual_candidates.md), [docs/physical_plans.md §Admission and routes](../../../../../physical_plans.md), [docs/physical_plans.md §Identity and versioned artifacts](../../../../../physical_plans.md) |

```text
SearchBinding(const SearchBinding&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain another SearchBinding artifact without copying its evidence. |
| inputs / outputs | Copies a const source handle; source remains usable. |
| invariants | Authority and exact binding are unchanged by lifecycle operations; an empty/moved handle confers no new result. |
| ownership | Adds shared ownership of BindingData model payload; no reference getters are invoked. |
| failure | Declared noexcept. Content access on an emptied handle rejects through require_handle; payload destructors follow owned model contracts. |
| cost | Shared-handle copy/refcount work without new payload allocation. |
| Design | [docs/residual_candidates.md §Exactness and owning artifacts](../../../../../residual_candidates.md), [docs/physical_plans.md §Admission and routes](../../../../../physical_plans.md), [docs/physical_plans.md §Identity and versioned artifacts](../../../../../physical_plans.md) |

```text
SearchBinding& operator=(const SearchBinding&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace this SearchBinding artifact with another retained owner. |
| inputs / outputs | Copies source ownership and releases previous destination ownership. |
| invariants | Authority and exact binding are unchanged by lifecycle operations; an empty/moved handle confers no new result. |
| ownership | The old BindingData model payload can be destroyed if the destination held its final owner. |
| failure | Declared noexcept. Content access on an emptied handle rejects through require_handle; payload destructors follow owned model contracts. |
| cost | Reference retention plus potentially size-dependent last-owner teardown; no new evidence allocation. |
| Design | [docs/residual_candidates.md §Exactness and owning artifacts](../../../../../residual_candidates.md), [docs/physical_plans.md §Admission and routes](../../../../../physical_plans.md), [docs/physical_plans.md §Identity and versioned artifacts](../../../../../physical_plans.md) |

```text
SearchBinding(SearchBinding&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer a SearchBinding artifact to a new handle. |
| inputs / outputs | Moves shared ownership without copying evidence; distinct source becomes empty. |
| invariants | Authority and exact binding are unchanged by lifecycle operations; an empty/moved handle confers no new result. |
| ownership | Payload BindingData model payload stays at the same address under the destination owner. |
| failure | Declared noexcept. Content access on an emptied handle rejects through require_handle; payload destructors follow owned model contracts. |
| cost | One shared-handle transfer without evidence traversal. |
| Design | [docs/residual_candidates.md §Exactness and owning artifacts](../../../../../residual_candidates.md), [docs/physical_plans.md §Admission and routes](../../../../../physical_plans.md), [docs/physical_plans.md §Identity and versioned artifacts](../../../../../physical_plans.md) |

```text
SearchBinding& operator=(SearchBinding&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace a SearchBinding owner by moving another handle. |
| inputs / outputs | Transfers source ownership and releases old destination state; self-move follows shared_ptr semantics. |
| invariants | Authority and exact binding are unchanged by lifecycle operations; an empty/moved handle confers no new result. |
| ownership | Any old final-owned BindingData model payload may be released synchronously. |
| failure | Declared noexcept. Content access on an emptied handle rejects through require_handle; payload destructors follow owned model contracts. |
| cost | Handle transfer plus possible full old-payload teardown; no deep evidence copy. |
| Design | [docs/residual_candidates.md §Exactness and owning artifacts](../../../../../residual_candidates.md), [docs/physical_plans.md §Admission and routes](../../../../../physical_plans.md), [docs/physical_plans.md §Identity and versioned artifacts](../../../../../physical_plans.md) |

## B0042

[Lines 178–181](../../../../../../include/crown/planner/search.hpp#L178); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L178-L181:sha256:a4b101e32b8b924fb0c93eb7d92c1a15e971999b05140a3b6405f151c5c903d3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ValidatedIncumbent: A complete, P02-checked tree. Establishes ONLY an upper bound. Retain a complete checked upper; its height is not a minimum claim. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ValidatedIncumbent; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ValidatedIncumbent come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0043

[Lines 182–196](../../../../../../include/crown/planner/search.hpp#L182); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class ValidatedIncumbent {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one complete independently P02-checked upper witness. |
| inputs / outputs | binding returns an owning binding handle; tree is borrowed from retained upper; height is its measured native count. |
| invariants | A valid upper can survive cancelled/failed sessions and still supplies no lower or optimum authority. |
| ownership | Shared immutable ownership of checked upper, tree/report and binding; reference getters require a surviving owner of that payload, not necessarily the original facade. |
| failure | No public default/arbitrary-payload constructor. valid() checks presence; moved-from content access throws invalid_search_handle. |
| cost | Copy/move construction retains/transfers a handle; assignments may release large last-owned payloads. Shared copies do not allocate new payload/control blocks. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../../residual_candidates.md) |

```text
ValidatedIncumbent(const ValidatedIncumbent&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain another ValidatedIncumbent artifact without copying its evidence. |
| inputs / outputs | Copies a const source handle; source remains usable. |
| invariants | Authority and exact binding are unchanged by lifecycle operations; an empty/moved handle confers no new result. |
| ownership | Adds shared ownership of checked upper, tree/report and binding; no reference getters are invoked. |
| failure | Declared noexcept. Content access on an emptied handle rejects through require_handle; payload destructors follow owned model contracts. |
| cost | Shared-handle copy/refcount work without new payload allocation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../../residual_candidates.md) |

```text
ValidatedIncumbent& operator=(const ValidatedIncumbent&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace this ValidatedIncumbent artifact with another retained owner. |
| inputs / outputs | Copies source ownership and releases previous destination ownership. |
| invariants | Authority and exact binding are unchanged by lifecycle operations; an empty/moved handle confers no new result. |
| ownership | The old checked upper, tree/report and binding can be destroyed if the destination held its final owner. |
| failure | Declared noexcept. Content access on an emptied handle rejects through require_handle; payload destructors follow owned model contracts. |
| cost | Reference retention plus potentially size-dependent last-owner teardown; no new evidence allocation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../../residual_candidates.md) |

```text
ValidatedIncumbent(ValidatedIncumbent&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer a ValidatedIncumbent artifact to a new handle. |
| inputs / outputs | Moves shared ownership without copying evidence; distinct source becomes empty. |
| invariants | Authority and exact binding are unchanged by lifecycle operations; an empty/moved handle confers no new result. |
| ownership | Payload checked upper, tree/report and binding stays at the same address under the destination owner. |
| failure | Declared noexcept. Content access on an emptied handle rejects through require_handle; payload destructors follow owned model contracts. |
| cost | One shared-handle transfer without evidence traversal. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../../residual_candidates.md) |

```text
ValidatedIncumbent& operator=(ValidatedIncumbent&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace a ValidatedIncumbent owner by moving another handle. |
| inputs / outputs | Transfers source ownership and releases old destination state; self-move follows shared_ptr semantics. |
| invariants | Authority and exact binding are unchanged by lifecycle operations; an empty/moved handle confers no new result. |
| ownership | Any old final-owned checked upper, tree/report and binding may be released synchronously. |
| failure | Declared noexcept. Content access on an emptied handle rejects through require_handle; payload destructors follow owned model contracts. |
| cost | Handle transfer plus possible full old-payload teardown; no deep evidence copy. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../../residual_candidates.md) |

## B0044

[Lines 197–199](../../../../../../include/crown/planner/search.hpp#L197); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L197-L199:sha256:a9636631131a035bed7b301fee5040fe35703a35a67f4c8f4fa34a4caedd23e0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for VerifiedOptimum: Retain matching upper/lower evidence for this exact admitted query; a prefix optimum stays prefix-scoped. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies VerifiedOptimum; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for VerifiedOptimum come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0045

[Lines 200–215](../../../../../../include/crown/planner/search.hpp#L200); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class VerifiedOptimum {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain matching checked upper and complete independent lower proof. |
| inputs / outputs | upper and binding return owning handles; certificate returns a borrowed immutable claim document; height is the matching upper height. |
| invariants | Authority concerns exactly the admitted model. A proved prefix optimum remains about that prefix, and structural minimum does not prove maintenance-cost optimality. |
| ownership | Shared immutable ownership of incumbent and certificate for the admitted model; reference getters require a surviving owner of that payload, not necessarily the original facade. |
| failure | No public default/arbitrary-payload constructor. valid() checks presence; moved-from content access throws invalid_search_handle. |
| cost | Copy/move construction retains/transfers a handle; assignments may release large last-owned payloads. Shared copies do not allocate new payload/control blocks. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../../residual_candidates.md) |

```text
VerifiedOptimum(const VerifiedOptimum&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain another VerifiedOptimum artifact without copying its evidence. |
| inputs / outputs | Copies a const source handle; source remains usable. |
| invariants | Authority and exact binding are unchanged by lifecycle operations; an empty/moved handle confers no new result. |
| ownership | Adds shared ownership of incumbent and certificate for the admitted model; no reference getters are invoked. |
| failure | Declared noexcept. Content access on an emptied handle rejects through require_handle; payload destructors follow owned model contracts. |
| cost | Shared-handle copy/refcount work without new payload allocation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../../residual_candidates.md) |

```text
VerifiedOptimum& operator=(const VerifiedOptimum&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace this VerifiedOptimum artifact with another retained owner. |
| inputs / outputs | Copies source ownership and releases previous destination ownership. |
| invariants | Authority and exact binding are unchanged by lifecycle operations; an empty/moved handle confers no new result. |
| ownership | The old incumbent and certificate for the admitted model can be destroyed if the destination held its final owner. |
| failure | Declared noexcept. Content access on an emptied handle rejects through require_handle; payload destructors follow owned model contracts. |
| cost | Reference retention plus potentially size-dependent last-owner teardown; no new evidence allocation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../../residual_candidates.md) |

```text
VerifiedOptimum(VerifiedOptimum&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer a VerifiedOptimum artifact to a new handle. |
| inputs / outputs | Moves shared ownership without copying evidence; distinct source becomes empty. |
| invariants | Authority and exact binding are unchanged by lifecycle operations; an empty/moved handle confers no new result. |
| ownership | Payload incumbent and certificate for the admitted model stays at the same address under the destination owner. |
| failure | Declared noexcept. Content access on an emptied handle rejects through require_handle; payload destructors follow owned model contracts. |
| cost | One shared-handle transfer without evidence traversal. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../../residual_candidates.md) |

```text
VerifiedOptimum& operator=(VerifiedOptimum&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace a VerifiedOptimum owner by moving another handle. |
| inputs / outputs | Transfers source ownership and releases old destination state; self-move follows shared_ptr semantics. |
| invariants | Authority and exact binding are unchanged by lifecycle operations; an empty/moved handle confers no new result. |
| ownership | Any old final-owned incumbent and certificate for the admitted model may be released synchronously. |
| failure | Declared noexcept. Content access on an emptied handle rejects through require_handle; payload destructors follow owned model contracts. |
| cost | Handle transfer plus possible full old-payload teardown; no deep evidence copy. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../../residual_candidates.md) |

## B0046

[Lines 216–218](../../../../../../include/crown/planner/search.hpp#L216); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L216-L218:sha256:ef31b61b56a99917c5c85116f591534c501296bc9f4be0f17583a482ef6a11aa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for VerifiedInfeasible: Retain a complete no-tree proof for this binding; prefix infeasibility is not original authority. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies VerifiedInfeasible; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for VerifiedInfeasible come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0047

[Lines 219–232](../../../../../../include/crown/planner/search.hpp#L219); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class VerifiedInfeasible {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain completed independent empty-family proof. |
| inputs / outputs | binding returns an owner; certificate is borrowed through the retained infeasibility payload. |
| invariants | Infeasibility belongs to the exact supplied query; a prefix no-tree result cannot establish original-query infeasibility. |
| ownership | Shared immutable ownership of binding and complete infinite-root certificate; reference getters require a surviving owner of that payload, not necessarily the original facade. |
| failure | No public default/arbitrary-payload constructor. valid() checks presence; moved-from content access throws invalid_search_handle. |
| cost | Copy/move construction retains/transfers a handle; assignments may release large last-owned payloads. Shared copies do not allocate new payload/control blocks. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../../residual_candidates.md) |

```text
VerifiedInfeasible(const VerifiedInfeasible&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain another VerifiedInfeasible artifact without copying its evidence. |
| inputs / outputs | Copies a const source handle; source remains usable. |
| invariants | Authority and exact binding are unchanged by lifecycle operations; an empty/moved handle confers no new result. |
| ownership | Adds shared ownership of binding and complete infinite-root certificate; no reference getters are invoked. |
| failure | Declared noexcept. Content access on an emptied handle rejects through require_handle; payload destructors follow owned model contracts. |
| cost | Shared-handle copy/refcount work without new payload allocation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../../residual_candidates.md) |

```text
VerifiedInfeasible& operator=(const VerifiedInfeasible&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace this VerifiedInfeasible artifact with another retained owner. |
| inputs / outputs | Copies source ownership and releases previous destination ownership. |
| invariants | Authority and exact binding are unchanged by lifecycle operations; an empty/moved handle confers no new result. |
| ownership | The old binding and complete infinite-root certificate can be destroyed if the destination held its final owner. |
| failure | Declared noexcept. Content access on an emptied handle rejects through require_handle; payload destructors follow owned model contracts. |
| cost | Reference retention plus potentially size-dependent last-owner teardown; no new evidence allocation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../../residual_candidates.md) |

```text
VerifiedInfeasible(VerifiedInfeasible&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer a VerifiedInfeasible artifact to a new handle. |
| inputs / outputs | Moves shared ownership without copying evidence; distinct source becomes empty. |
| invariants | Authority and exact binding are unchanged by lifecycle operations; an empty/moved handle confers no new result. |
| ownership | Payload binding and complete infinite-root certificate stays at the same address under the destination owner. |
| failure | Declared noexcept. Content access on an emptied handle rejects through require_handle; payload destructors follow owned model contracts. |
| cost | One shared-handle transfer without evidence traversal. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../../residual_candidates.md) |

```text
VerifiedInfeasible& operator=(VerifiedInfeasible&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace a VerifiedInfeasible owner by moving another handle. |
| inputs / outputs | Transfers source ownership and releases old destination state; self-move follows shared_ptr semantics. |
| invariants | Authority and exact binding are unchanged by lifecycle operations; an empty/moved handle confers no new result. |
| ownership | Any old final-owned binding and complete infinite-root certificate may be released synchronously. |
| failure | Declared noexcept. Content access on an emptied handle rejects through require_handle; payload destructors follow owned model contracts. |
| cost | Handle transfer plus possible full old-payload teardown; no deep evidence copy. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../../residual_candidates.md) |

## B0048

[Lines 233–237](../../../../../../include/crown/planner/search.hpp#L233); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L233-L237:sha256:6360f40f6583deb1b242c2e76e56782f019d0f8e22bf4f045c3f3a5a3ff42601
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for CheckedCertificate: External certificate replay produces a checked authority handle; arbitrary HeightCertificate/OracleResult aggregates cannot manufacture these artifacts. Retain independent replay authority; arbitrary edited proof/result aggregates cannot create this handle. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies CheckedCertificate; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for CheckedCertificate come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0049

[Lines 238–253](../../../../../../include/crown/planner/search.hpp#L238); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class CheckedCertificate {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the fully replayed certificate and its derived typed outcome. |
| inputs / outputs | binding/certificate expose exact checked input; optimum/infeasibility return the matching optional authority. |
| invariants | External HeightCertificate is an untrusted claim until independent checking and final owner publication; mutable aggregates cannot call private constructors. |
| ownership | Shared immutable ownership of checked proof and optimum-or-infeasibility owners; reference getters require a surviving owner of that payload, not necessarily the original facade. |
| failure | No public default/arbitrary-payload constructor. valid() checks presence; moved-from content access throws invalid_search_handle. |
| cost | Copy/move construction retains/transfers a handle; assignments may release large last-owned payloads. Shared copies do not allocate new payload/control blocks. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../../planner_proofs.md) |

```text
CheckedCertificate(const CheckedCertificate&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain another CheckedCertificate artifact without copying its evidence. |
| inputs / outputs | Copies a const source handle; source remains usable. |
| invariants | Authority and exact binding are unchanged by lifecycle operations; an empty/moved handle confers no new result. |
| ownership | Adds shared ownership of checked proof and optimum-or-infeasibility owners; no reference getters are invoked. |
| failure | Declared noexcept. Content access on an emptied handle rejects through require_handle; payload destructors follow owned model contracts. |
| cost | Shared-handle copy/refcount work without new payload allocation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../../planner_proofs.md) |

```text
CheckedCertificate& operator=(const CheckedCertificate&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace this CheckedCertificate artifact with another retained owner. |
| inputs / outputs | Copies source ownership and releases previous destination ownership. |
| invariants | Authority and exact binding are unchanged by lifecycle operations; an empty/moved handle confers no new result. |
| ownership | The old checked proof and optimum-or-infeasibility owners can be destroyed if the destination held its final owner. |
| failure | Declared noexcept. Content access on an emptied handle rejects through require_handle; payload destructors follow owned model contracts. |
| cost | Reference retention plus potentially size-dependent last-owner teardown; no new evidence allocation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../../planner_proofs.md) |

```text
CheckedCertificate(CheckedCertificate&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer a CheckedCertificate artifact to a new handle. |
| inputs / outputs | Moves shared ownership without copying evidence; distinct source becomes empty. |
| invariants | Authority and exact binding are unchanged by lifecycle operations; an empty/moved handle confers no new result. |
| ownership | Payload checked proof and optimum-or-infeasibility owners stays at the same address under the destination owner. |
| failure | Declared noexcept. Content access on an emptied handle rejects through require_handle; payload destructors follow owned model contracts. |
| cost | One shared-handle transfer without evidence traversal. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../../planner_proofs.md) |

```text
CheckedCertificate& operator=(CheckedCertificate&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace a CheckedCertificate owner by moving another handle. |
| inputs / outputs | Transfers source ownership and releases old destination state; self-move follows shared_ptr semantics. |
| invariants | Authority and exact binding are unchanged by lifecycle operations; an empty/moved handle confers no new result. |
| ownership | Any old final-owned checked proof and optimum-or-infeasibility owners may be released synchronously. |
| failure | Declared noexcept. Content access on an emptied handle rejects through require_handle; payload destructors follow owned model contracts. |
| cost | Handle transfer plus possible full old-payload teardown; no deep evidence copy. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../../planner_proofs.md) |

## B0050

[Lines 254–289](../../../../../../include/crown/planner/search.hpp#L254); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class ExactSearch {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one exclusive resumable exact search bound to its admitted model. |
| inputs / outputs | create admits model/options; advance grants work; progress is scalar; artifact accessors return immutable retained owners. |
| invariants | strict withholds incumbent handles, not scalar upper progress. Full original authority requires this owner to have received the full original query; prefix owners prove only their input. |
| ownership | Move-only Impl owns workers/ledgers and shares artifacts; exclusive thread transfer is allowed, concurrent methods are not. |
| failure | Admission may throw. advance is noexcept with retained allocation/resource stops; invalid internal proof is terminal. cancel is a no-op on already terminal owners. |
| cost | Exact work and retained proof/search storage can be exponential; admission, serialization and final teardown lie outside grants. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/planner_continuations.md §Resource accounting](../../../../../planner_continuations.md), [docs/planner_continuations.md §Lifetime and output](../../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../../residual_candidates.md) |

## B0051

[Lines 290–323](../../../../../../include/crown/planner/search.hpp#L290); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class CertificateReplay {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own independent checking and typed publication of one admitted certificate claim. |
| inputs / outputs | create owns model/claim; advance resumes upper/lower checking; checked() returns authority only after all result owners are ready. |
| invariants | No exact serialized binding check is hidden here: typed claim is checked against supplied model; IO separately enforces serialized exact binding. |
| ownership | Move-only owner retains immutable model/claim and flat checker workers; artifact handles outlive it. |
| failure | Admission can throw; invalid proof/internal/counter outcomes are terminal. Allocation/depth/work/time stops retain retryable state; terminal cancel does nothing. |
| cost | Replay can enumerate exponential partition families; admission copies, IO and cleanup are separate costs. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/planner_continuations.md §Resource accounting](../../../../../planner_continuations.md), [docs/planner_continuations.md §Lifetime and output](../../../../../planner_continuations.md), [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../../planner_proofs.md) |
