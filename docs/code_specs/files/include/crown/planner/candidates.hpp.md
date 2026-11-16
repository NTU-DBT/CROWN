# `include/crown/planner/candidates.hpp` — block usage map

[Source](../../../../../../include/crown/planner/candidates.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Retain and enumerate checked minimum-height candidate alternatives under bounded content budgets.

Snapshot SHA-256: `e6ea30cbc9e97bd90c0b3eb152685a6b0f79802f6bb1cf445aef3c095bdf1d6d`. 207 lines partitioned into 25 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [search](../../../../subsystem_contracts.md#search). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../../tree_oracle.md), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../../candidate_alternatives.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../../include/crown/planner/candidates.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. |  · [reviewed contract](#b0001) |
| [B0002 · 19–19](../../../../../../include/crown/planner/candidates.hpp#L19) | Type/record definition: enum class CandidateUpdateProfile |  · [reviewed contract](#b0002) |
| [B0003 · 20–21](../../../../../../include/crown/planner/candidates.hpp#L20) | Explanatory comments or spacing. | source comment (unverified): // Exhaustion covers only the declared family, never all tree shapes or a · [reviewed contract](#b0003) |
| [B0004 · 22–22](../../../../../../include/crown/planner/candidates.hpp#L22) | Type/record definition: enum class CandidateFamily | source comment (unverified): // Exhaustion covers only the declared family, never all tree shapes or a · [reviewed contract](#b0004) |
| [B0005 · 23–23](../../../../../../include/crown/planner/candidates.hpp#L23) | Type/record definition: enum class CandidateSource |  · [reviewed contract](#b0005) |
| [B0006 · 24–33](../../../../../../include/crown/planner/candidates.hpp#L24) | Type/record definition: struct CandidateContext | source comment (unverified): // Admission rejects unknown profiles/versions. No runtime complexity or · [reviewed contract](#b0006) |
| [B0007 · 34–43](../../../../../../include/crown/planner/candidates.hpp#L34) | Type/record definition: struct CandidateLimits | source comment (unverified): // Cumulative logical construction, not S05 allocator bytes. Binding/context · [reviewed contract](#b0007) |
| [B0008 · 44–45](../../../../../../include/crown/planner/candidates.hpp#L44) | Explanatory comments or spacing. | source comment (unverified): // Original generation provenance survives cache reuse. The new provider · [reviewed contract](#b0008) |
| [B0009 · 46–52](../../../../../../include/crown/planner/candidates.hpp#L46) | Type/record definition: struct CandidateProvenance | source comment (unverified): // Original generation provenance survives cache reuse. The new provider · [reviewed contract](#b0009) |
| [B0010 · 53–82](../../../../../../include/crown/planner/candidates.hpp#L53) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Owned original-binding P02 upper at the supplied original minimum. Getters · [reviewed contract](#b0010) |
| [B0011 · 83–86](../../../../../../include/crown/planner/candidates.hpp#L83) | Type/record definition: enum class CandidatePhase |  · [reviewed contract](#b0011) |
| [B0012 · 87–91](../../../../../../include/crown/planner/candidates.hpp#L87) | Type/record definition: enum class CandidateStop |  · [reviewed contract](#b0012) |
| [B0013 · 92–95](../../../../../../include/crown/planner/candidates.hpp#L92) | Type/record definition: struct CandidateStatistics |  · [reviewed contract](#b0013) |
| [B0014 · 96–110](../../../../../../include/crown/planner/candidates.hpp#L96) | Type/record definition: struct CandidateProgress | source comment (unverified): // Exhaustion covers the declared normal-form family or the supplied finite · [reviewed contract](#b0014) |
| [B0015 · 111–111](../../../../../../include/crown/planner/candidates.hpp#L111) | Type/record definition: struct CandidateAdvance |  · [reviewed contract](#b0015) |
| [B0016 · 112–115](../../../../../../include/crown/planner/candidates.hpp#L112) | Explanatory comments or spacing. | source comment (unverified): // Immutable owning prefix admitted outside advance; it copies handle/event · [reviewed contract](#b0016) |
| [B0017 · 116–133](../../../../../../include/crown/planner/candidates.hpp#L116) | Type/record definition: class CandidateSnapshot | source comment (unverified): // Immutable owning prefix admitted outside advance; it copies handle/event · [reviewed contract](#b0017) |
| [B0018 · 134–169](../../../../../../include/crown/planner/candidates.hpp#L134) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Exclusive single caller. No borrowed input, background work or callbacks. · [reviewed contract](#b0018) |
| [B0019 · 170–177](../../../../../../include/crown/planner/candidates.hpp#L170) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Explicit allocating snapshot admission, outside advance. It owns a prefix · [reviewed contract](#b0019) |
| [B0020 · 178–178](../../../../../../include/crown/planner/candidates.hpp#L178) | Type/record definition: enum class CandidateCacheInstall |  · [reviewed contract](#b0020) |
| [B0021 · 179–180](../../../../../../include/crown/planner/candidates.hpp#L179) | Explanatory comments or spacing. | source comment (unverified): // Cumulative activity survives clear(); entries is the current list size, · [reviewed contract](#b0021) |
| [B0022 · 181–184](../../../../../../include/crown/planner/candidates.hpp#L181) | Type/record definition: struct CandidateCacheStatistics | source comment (unverified): // Cumulative activity survives clear(); entries is the current list size, · [reviewed contract](#b0022) |
| [B0023 · 185–189](../../../../../../include/crown/planner/candidates.hpp#L185) | Explanatory comments or spacing. | source comment (unverified): // Bounded explicit exact-binding cache; lookup/install are allocating admission · [reviewed contract](#b0023) |
| [B0024 · 190–206](../../../../../../include/crown/planner/candidates.hpp#L190) | Type/record definition: class CandidateCache | source comment (unverified): // Bounded explicit exact-binding cache; lookup/install are allocating admission · [reviewed contract](#b0024) |
| [B0025 · 207–207](../../../../../../include/crown/planner/candidates.hpp#L207) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner · [reviewed contract](#b0025) |

## B0001

[Lines 1–18](../../../../../../include/crown/planner/candidates.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L18:sha256:1b2d02c88042e025b44ef417dc2177b99d87a21a31991db082c416ac3d2eaf8d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Guard repeated header inclusion and import owned finite-vector admission with the existing candidate declarations. |
| inputs / outputs | Preprocessor directives resolve compile-time declarations. This block has no runtime call inputs or result. |
| invariants | Includes, namespace openings, aliases, and forward declarations determine C++ name visibility and type availability; they do not validate planner data or grant proof authority. |
| ownership | No runtime object is owned by the include or scope directives. Any state belongs to the types and functions declared after them. |
| failure | A missing header, incompatible declaration, or ill-formed type use fails during compilation; runtime failures remain in the called code. |
| cost | Adds preprocessing, parsing, and any later template-instantiation work in this translation unit. It adds no runtime timer, counter, branch, or allocation. |
| Design | [include/crown/planner/candidates.hpp](../../../../../../include/crown/planner/candidates.hpp), [docs/planner_proofs.md](../../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../../residual_candidates.md), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../../meta_decompositions.md) |

## B0002

[Lines 19–19](../../../../../../include/crown/planner/candidates.hpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class CandidateUpdateProfile {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the only admitted candidate update namespace. |
| inputs / outputs | mixed_full_row_set_v1 value used by CandidateContext. |
| invariants | Acceptance provides identity context; it establishes no runtime update bound. |
| ownership | Scalar enum; no input or plan ownership. |
| failure | context_valid rejects unsupported enum values. |
| cost | Constant storage/comparison. |
| Design | [docs/candidate_alternatives.md](../../../../../candidate_alternatives.md), [src/planner/candidates.cpp](../../../../../../src/planner/candidates.cpp) |

## B0003

[Lines 20–21](../../../../../../include/crown/planner/candidates.hpp#L20); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L21:sha256:42d60dd223eba7b4089f987676f92ba42615013922c640ea7e80a16f25acf809
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain that exhaustion applies to the declared family and cannot establish global maintenance-cost optimality. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies CandidateFamily; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for CandidateFamily come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/candidates.hpp](../../../../../../include/crown/planner/candidates.hpp), [docs/planner_proofs.md](../../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../../residual_candidates.md), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../../meta_decompositions.md) |

## B0004

[Lines 22–22](../../../../../../include/crown/planner/candidates.hpp#L22); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class CandidateFamily {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the original seed/normal-form family and the supplied finite-batch family. |
| inputs / outputs | One versioned family in progress/provenance/snapshots. |
| invariants | Exhaustion concerns exactly the declared family; a consumed finite batch makes no upstream-generator or global cost completeness claim. |
| ownership | Scalar enum retained with immutable artifacts. |
| failure | Type itself validates nothing; provider assigns the supported value. |
| cost | Constant storage. |
| Design | [docs/candidate_alternatives.md](../../../../../candidate_alternatives.md), [docs/planner_proofs.md](../../../../../planner_proofs.md), [src/planner/candidates.cpp](../../../../../../src/planner/candidates.cpp), [docs/meta_decompositions.md](../../../../../meta_decompositions.md) |

## B0005

[Lines 23–23](../../../../../../include/crown/planner/candidates.hpp#L23); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class CandidateSource {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify primary generation provenance. |
| inputs / outputs | exact_witness, residual_seed, normal_form or supplied_proposal; existing enum values retain their order. |
| invariants | Cached reuse preserves original generation source rather than inventing cache as its source. |
| ownership | Scalar copied with provenance. |
| failure | No exceptions; only private construction publishes provenance. |
| cost | Constant storage. |
| Design | [docs/candidate_alternatives.md](../../../../../candidate_alternatives.md), [src/planner/candidates.cpp](../../../../../../src/planner/candidates.cpp), [docs/meta_decompositions.md](../../../../../meta_decompositions.md) |

## B0006

[Lines 24–33](../../../../../../include/crown/planner/candidates.hpp#L24); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CandidateContext {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fence candidate/cache identity by supported semantic and algorithm namespaces. |
| inputs / outputs | Update profile plus arithmetic/planner/optimization/cost-model/canonicalization version strings. |
| invariants | Every field is compared exactly; currently only default named versions are admitted. no-cost-v1 supplies no cost-optimality claim. |
| ownership | Owns strings; artifacts retain immutable context in InputData. |
| failure | Unknown profile/version rejects create/lookup. Default string construction or context copying can allocate. |
| cost | String construction/copy/comparison is variable-width; fixed number of fields. |
| Design | [docs/candidate_alternatives.md](../../../../../candidate_alternatives.md), [src/planner/candidates.cpp](../../../../../../src/planner/candidates.cpp), [src/planner/candidate_binding.hpp](../../../../../../src/planner/candidate_binding.hpp) |

## B0007

[Lines 34–43](../../../../../../include/crown/planner/candidates.hpp#L34); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CandidateLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure cooperative enumeration, logical content/depth and retained-candidate ceilings. |
| inputs / outputs | Default 50M attempts, depth256, 1M records,10M cells,128 candidates. |
| invariants | Logical construction accumulates discarded drafts; admission/binding serialization, P02 scratch, capacities/history/snapshots/cache are excluded. No delegated exact search runs. |
| ownership | Fixed-size copied limit value. |
| failure | Negative time rejects admission; resource stops permit monotone extension; logical overflow terminalizes. |
| cost | Constant limit checks; work units are neither bytes nor hard deadlines. |
| Design | [docs/candidate_alternatives.md](../../../../../candidate_alternatives.md), [src/planner/candidates.cpp](../../../../../../src/planner/candidates.cpp), [src/planner/candidate_machine.hpp](../../../../../../src/planner/candidate_machine.hpp) |

## B0008

[Lines 44–45](../../../../../../include/crown/planner/candidates.hpp#L44); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L44-L45:sha256:75b43d06ae339f0aac40bb3b73e32c52cc77fdb3d9addfbfed7139ff93cf7e99
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for CandidateProvenance: Original generation provenance survives cache reuse. The new provider retains its own supplied original proof, whose witness remains unchanged. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies CandidateProvenance; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for CandidateProvenance come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/candidates.hpp](../../../../../../include/crown/planner/candidates.hpp), [docs/planner_proofs.md](../../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../../residual_candidates.md), [docs/planner_continuations.md](../../../../../planner_continuations.md) |

## B0009

[Lines 46–52](../../../../../../include/crown/planner/candidates.hpp#L46); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CandidateProvenance {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain original generation activity separately from proof authority. |
| inputs / outputs | Source/family/sequence plus optional residual last-step and owning trace. |
| invariants | First published duplicate source wins; cache retains its generation provenance but uses the new provider original proof. |
| ownership | Owns scalar fields and optional immutable ResidualTrace handle. |
| failure | Type validates nothing; source data never upgrades a trace into tree/minimum proof. |
| cost | Constant copy of scalars/optional shared handle, no payload allocation. |
| Design | [docs/candidate_alternatives.md](../../../../../candidate_alternatives.md), [src/planner/candidates.cpp](../../../../../../src/planner/candidates.cpp) |

## B0010

[Lines 53–82](../../../../../../include/crown/planner/candidates.hpp#L53); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class MinimumHeightCandidate {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own an original-bound checked alternative matching a supplied original minimum. |
| inputs / outputs | Const binding/tree/report/key/context access, provenance copy and retained VerifiedOptimum. |
| invariants | Independent P02 validates upper and exact height gate matches supplied proof. Original certificate keeps its original witness; alternative is separate. |
| ownership | Shared immutable payload retains InputData, upper/report/key; borrowed getters require an owning handle alive. |
| failure | Moved-from getters throw invalid_candidate_handle. Private factory prevents caller-edited progress/tree flags manufacturing authority. |
| cost | Handle copy/access constant except variable-width error/reporting; final payload cleanup size-dependent. |
| Design | [docs/candidate_alternatives.md](../../../../../candidate_alternatives.md), [src/planner/candidates.cpp](../../../../../../src/planner/candidates.cpp), [src/planner/verify.cpp](../../../../../../src/planner/verify.cpp), [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp) |

## B0011

[Lines 83–86](../../../../../../include/crown/planner/candidates.hpp#L83); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class CandidatePhase {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the retained provider activity or terminal state. |
| inputs / outputs | Seed/enumerate/validate/canonicalize/publish/exhausted/failed/cancelled/moved_from. |
| invariants | Phase is diagnostic; supplied original minimum is already known independently. |
| ownership | Scalar snapshot. |
| failure | No validation or exceptions in enum. |
| cost | Constant storage. |
| Design | [docs/candidate_alternatives.md](../../../../../candidate_alternatives.md), [src/planner/candidates.cpp](../../../../../../src/planner/candidates.cpp) |

## B0012

[Lines 87–91](../../../../../../include/crown/planner/candidates.hpp#L87); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class CandidateStop {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report publication, grant/resource stops or terminal outcomes. |
| inputs / outputs | Fixed enum in CandidateAdvance/progress. |
| invariants | candidate_ready is a published member, not family exhaustion. Capacity/limits/allocation are resumable; logical overflow/internal failure terminalize. |
| ownership | Returned without dynamic diagnostic ownership. |
| failure | No exceptions in enum; advance translates child failures. |
| cost | Constant storage. |
| Design | [docs/candidate_alternatives.md](../../../../../candidate_alternatives.md), [src/planner/candidates.cpp](../../../../../../src/planner/candidates.cpp) |

## B0013

[Lines 92–95](../../../../../../include/crown/planner/candidates.hpp#L92); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CandidateStatistics {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose activity counts from facade and generator. |
| inputs / outputs | Proposed/rejected/taller/duplicate/published/topology/scope/cache counters. |
| invariants | Diagnostics cannot manufacture proof or exhaustion. scope_tuples reflects generator drafts_ready, including duplicate representations. |
| ownership | Eight scalar counters copied to progress. |
| failure | All logical increments preflight exhaustion; statistics never intentionally wrap. |
| cost | Constant-size snapshot. |
| Design | [docs/candidate_alternatives.md](../../../../../candidate_alternatives.md), [src/planner/candidates.cpp](../../../../../../src/planner/candidates.cpp), [src/planner/candidate_generator.cpp](../../../../../../src/planner/candidate_generator.cpp) |

## B0014

[Lines 96–110](../../../../../../include/crown/planner/candidates.hpp#L96); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CandidateProgress {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report enumeration state while retaining the separately proved original height. |
| inputs / outputs | Phase/last stop/family/height/exhaustion, work/content/revision/statistics/count. |
| invariants | verified_original_height comes from the supplied genuine proof. family_exhausted requires actual exhaustion of the original seed/normal-form route or consumption of every supplied proposal; neither establishes global maintenance-cost optimality. |
| ownership | Value snapshot with no tree/key/proof ownership. |
| failure | Moved-from returns a marked diagnostic; editing fields creates no authority. |
| cost | Constant-size nonallocating copy. |
| Design | [docs/candidate_alternatives.md](../../../../../candidate_alternatives.md), [src/planner/candidates.cpp](../../../../../../src/planner/candidates.cpp), [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp), [docs/meta_decompositions.md](../../../../../meta_decompositions.md) |

## B0015

[Lines 111–111](../../../../../../include/crown/planner/candidates.hpp#L111); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CandidateAdvance {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return an ephemeral stop alongside current diagnostic state. |
| inputs / outputs | CandidateStop and CandidateProgress by value. |
| invariants | Zero grants leave stored progress unchanged even when returned stop is a quantum reason. |
| ownership | Owns scalar/optional snapshot only. |
| failure | Nonallocating result used by noexcept advance under allocation failure. |
| cost | Constant-size return. |
| Design | [docs/candidate_alternatives.md](../../../../../candidate_alternatives.md), [src/planner/candidates.cpp](../../../../../../src/planner/candidates.cpp) |

## B0016

[Lines 112–115](../../../../../../include/crown/planner/candidates.hpp#L112); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L112-L115:sha256:a39fff28190e1f67af89c8950cda7d1b6956f9431014920f32f88514f201b89a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for CandidateSnapshot: Immutable owning prefix admitted outside advance; it copies handle/event vectors and retains actual completion. Reuse starts a fresh generator and rechecks trees; no live cursor or earlier completion state is transplanted. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies CandidateSnapshot; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for CandidateSnapshot come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/candidates.hpp](../../../../../../include/crown/planner/candidates.hpp), [docs/planner_proofs.md](../../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../../residual_candidates.md), [docs/planner_continuations.md](../../../../../planner_continuations.md) |

## B0017

[Lines 116–133](../../../../../../include/crown/planner/candidates.hpp#L116); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class CandidateSnapshot {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own an immutable candidate prefix and its actual completion state. |
| inputs / outputs | Count/indexed optional candidate/family/exhaustion/context/original proof. |
| invariants | Snapshot is separate admission, not a live cursor. Reuse starts a fresh generator; old completion never proves new-provider exhaustion. The snapshot retains its actual family. The old factory/cache accept only the original normal-form family. |
| ownership | Shared SnapshotData owns input, candidate handles and reuse diagnostics; public handles survive facade lifetime. |
| failure | Moved-from getters reject; out-of-range candidate returns empty. Snapshot creation can allocate outside advance. |
| cost | Handle copies constant; provider snapshot copies O(candidate+reuse counts) handles/records. |
| Design | [docs/candidate_alternatives.md](../../../../../candidate_alternatives.md), [src/planner/candidates.cpp](../../../../../../src/planner/candidates.cpp), [src/planner/selection.cpp](../../../../../../src/planner/selection.cpp), [docs/meta_decompositions.md](../../../../../meta_decompositions.md) |

## B0018

[Lines 134–169](../../../../../../include/crown/planner/candidates.hpp#L134); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class CandidateProvider {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own exclusive resumable alternative enumeration under an already verified original optimum. |
| inputs / outputs | create with proof/context/limits and optional residual/cache seed; advance, publication getters, raises/cancel/snapshot. |
| invariants | create visits exact witness, residual, cached prefix and fresh normal form; from_proposals visits only its supplied batch. All members pass original P02/height/key gates. Invalid/taller proposals discard, while a valid upper below the original proved minimum is an internal contradiction. |
| ownership | Move-only unique pimpl; InputData excludes seed/snapshot holders, avoiding retained history chains. Published artifacts share immutable source/proof. |
| failure | Admission may throw; noexcept advance returns retryable stops or terminal failure. Single caller; no concurrent methods. |
| cost | Admission copies full binding and serializes identity; saved steps meter work while comparisons/relocations/cleanup have variable costs. Finite input production and retained vector storage are allocating admission costs outside advance grants; each proposed tree moves once to an independent owner. |
| Design | [docs/candidate_alternatives.md](../../../../../candidate_alternatives.md), [src/planner/candidates.cpp](../../../../../../src/planner/candidates.cpp), [src/planner/candidate_machine.hpp](../../../../../../src/planner/candidate_machine.hpp), [docs/planner_proofs.md](../../../../../planner_proofs.md), [docs/meta_decompositions.md](../../../../../meta_decompositions.md) |

## B0019

[Lines 170–177](../../../../../../include/crown/planner/candidates.hpp#L170); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L170-L177:sha256:cfb8642f84f2da5e89234587f29c9c2837eac63ce1e6b48c9c4aa4e3088bb62b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare immutable snapshot export and private exclusive provider ownership. |
| inputs / outputs | snapshot returns an owning prefix/completion value; private unique_ptr keeps implementation construction controlled. |
| invariants | A snapshot does not borrow a live cursor or transfer completion to a fresh provider. |
| ownership | Provider owns its Impl; exported candidates/snapshots retain independent immutable owners. |
| failure | Snapshot allocation can fail; a moved-from provider rejects. |
| cost | Snapshot copies handle/reuse vectors; a private owner declaration adds no per-update operation. |
| Design | [docs/candidate_alternatives.md](../../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../../meta_decompositions.md), [Refactor.md](../../../../../../Refactor.md) |

## B0020

[Lines 178–178](../../../../../../include/crown/planner/candidates.hpp#L178); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class CandidateCacheInstall {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe installation result for an immutable snapshot. |
| inputs / outputs | disabled/inserted/replaced. |
| invariants | Replacement preserves FIFO position; disabled capacity does not install. |
| ownership | Scalar value only. |
| failure | Exceptions report invalid handle/conflict/overflow/allocation separately. |
| cost | Constant storage. |
| Design | [docs/candidate_alternatives.md](../../../../../candidate_alternatives.md), [src/planner/candidates.cpp](../../../../../../src/planner/candidates.cpp) |

## B0021

[Lines 179–180](../../../../../../include/crown/planner/candidates.hpp#L179); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L179-L180:sha256:4cfffa7e81f5934e3e2e87acede18800c880c8cf6d40a1a13a0a57dd7eabc5cb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for CandidateCacheStatistics: Cumulative activity survives clear(); entries is the current list size, independent of caller-retained snapshots after eviction or cache destruction. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies CandidateCacheStatistics; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for CandidateCacheStatistics come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/candidates.hpp](../../../../../../include/crown/planner/candidates.hpp), [docs/planner_proofs.md](../../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../../residual_candidates.md), [docs/planner_continuations.md](../../../../../planner_continuations.md) |

## B0022

[Lines 181–184](../../../../../../include/crown/planner/candidates.hpp#L181); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CandidateCacheStatistics {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report cache lookup/install activity and current entry count. |
| inputs / outputs | Hits/misses/insertions/replacements/evictions plus entries. |
| invariants | Clear removes entries but preserves cumulative counters. Counters stop before wrap. |
| ownership | Fixed scalar copy independent of cache lifetime. |
| failure | statistics on moved-from cache yields default; mutating operations can throw counter overflow. |
| cost | Constant-size snapshot. |
| Design | [docs/candidate_alternatives.md](../../../../../candidate_alternatives.md), [src/planner/candidates.cpp](../../../../../../src/planner/candidates.cpp) |

## B0023

[Lines 185–189](../../../../../../include/crown/planner/candidates.hpp#L185); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L185-L188:sha256:fa23c9fae6136128d97e66c8e43693022213779e74b3218cb8496690d2f01661
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for CandidateCache: Bounded explicit exact-binding cache; lookup/install are allocating admission operations, not advance units. FIFO insertion order is deterministic; a hit does not change it. Replacements preserve their original FIFO position. Full equality is required; no digest-only or alpha-remapped proof reuse. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies CandidateCache; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for CandidateCache come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/candidates.hpp](../../../../../../include/crown/planner/candidates.hpp), [docs/planner_proofs.md](../../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../../residual_candidates.md), [docs/planner_continuations.md](../../../../../planner_continuations.md) |

## B0024

[Lines 190–206](../../../../../../include/crown/planner/candidates.hpp#L190); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class CandidateCache {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain a bounded exact-binding FIFO of immutable prefixes. |
| inputs / outputs | create capacity, allocating lookup/install, statistics and clear. |
| invariants | Complete binding bytes plus all context fields fence reuse; conflicting verified heights reject. Hits/replacements keep order. Prefix hits still pass provider checks. Installation rejects the finite-proposal family before checking disabled capacity; lookup cannot return such a batch. |
| ownership | Move-only pimpl owns list of shared snapshots; caller copies can retain evicted payloads. |
| failure | Admission/allocation/conflict/counter errors throw; prepare node before eviction preserves existing state on bad_alloc. |
| cost | Lookup/install scan entries with full variable-width equality; entry cap is not a byte cap. Clear/final release may destroy retained payloads. |
| Design | [docs/candidate_alternatives.md](../../../../../candidate_alternatives.md), [src/planner/candidates.cpp](../../../../../../src/planner/candidates.cpp), [src/planner/candidate_binding.hpp](../../../../../../src/planner/candidate_binding.hpp), [docs/meta_decompositions.md](../../../../../meta_decompositions.md) |

## B0025

[Lines 207–207](../../../../../../include/crown/planner/candidates.hpp#L207); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L207-L207:sha256:acb95521e5c8cc117a4f60f87ae076d39f48ab1ff02f31d3b8a4ada933fd3da0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace crown::planner. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [include/crown/planner/candidates.hpp](../../../../../../include/crown/planner/candidates.hpp), [docs/planner_proofs.md](../../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../../residual_candidates.md), [docs/planner_continuations.md](../../../../../planner_continuations.md) |
