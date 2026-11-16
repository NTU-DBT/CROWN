# `include/crown/planner/residual.hpp` — block usage map

[Source](../../../../../../include/crown/planner/residual.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Generate and replay residual-reduction/reconstruction candidates as a structural aid to the exact planner.

Snapshot SHA-256: `e56d29ef4302d9af6036f99af868fe837dde8f21259cb0c9034809408c0e06df`. 208 lines partitioned into 33 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [residual](../../../../subsystem_contracts.md#residual). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/residual_candidates.md](../../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../../planner_proofs.md), [docs/code_review.md](../../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../../include/crown/planner/residual.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. | source comment (unverified): // Candidate mode may finish with a checked upper; the default also completes · [reviewed contract](#b0001) |
| [B0002 · 18–18](../../../../../../include/crown/planner/residual.hpp#L18) | Type/record definition: enum class ResidualMode | source comment (unverified): // Candidate mode may finish with a checked upper; the default also completes · [reviewed contract](#b0002) |
| [B0003 · 19–20](../../../../../../include/crown/planner/residual.hpp#L19) | Explanatory comments or spacing. | source comment (unverified): // Last successful tree-construction step, independent of exactness. Earlier · [reviewed contract](#b0003) |
| [B0004 · 21–21](../../../../../../include/crown/planner/residual.hpp#L21) | Type/record definition: enum class ResidualOrigin | source comment (unverified): // Last successful tree-construction step, independent of exactness. Earlier · [reviewed contract](#b0004) |
| [B0005 · 22–25](../../../../../../include/crown/planner/residual.hpp#L22) | Type/record definition: enum class ResidualPhase |  · [reviewed contract](#b0005) |
| [B0006 · 26–26](../../../../../../include/crown/planner/residual.hpp#L26) | Type/record definition: enum class ResidualResult |  · [reviewed contract](#b0006) |
| [B0007 · 27–27](../../../../../../include/crown/planner/residual.hpp#L27) | Type/record definition: enum class ResidualProofStatus |  · [reviewed contract](#b0007) |
| [B0008 · 28–32](../../../../../../include/crown/planner/residual.hpp#L28) | Type/record definition: enum class ResidualStopReason |  · [reviewed contract](#b0008) |
| [B0009 · 33–33](../../../../../../include/crown/planner/residual.hpp#L33) | Type/record definition: enum class ResidualTerminal |  · [reviewed contract](#b0009) |
| [B0010 · 34–35](../../../../../../include/crown/planner/residual.hpp#L34) | Explanatory comments or spacing. | source comment (unverified): // Frozen ear-condition bits: P2 arXiv:2603.14754v1, Section 2.1.4, · [reviewed contract](#b0010) |
| [B0011 · 36–36](../../../../../../include/crown/planner/residual.hpp#L36) | Type/record definition: enum class EarCondition : unsigned | source comment (unverified): // Frozen ear-condition bits: P2 arXiv:2603.14754v1, Section 2.1.4, · [reviewed contract](#b0011) |
| [B0012 · 37–40](../../../../../../include/crown/planner/residual.hpp#L37) | Type/record definition: struct EarAnchor |  · [reviewed contract](#b0012) |
| [B0013 · 41–46](../../../../../../include/crown/planner/residual.hpp#L41) | Type/record definition: struct EarRecord |  · [reviewed contract](#b0013) |
| [B0014 · 47–47](../../../../../../include/crown/planner/residual.hpp#L47) | Type/record definition: struct EarDeletion |  · [reviewed contract](#b0014) |
| [B0015 · 48–52](../../../../../../include/crown/planner/residual.hpp#L48) | Explanatory comments or spacing. | source comment (unverified): // Every ID in the trace is an original occurrence/variable ID. The dense view · [reviewed contract](#b0015) |
| [B0016 · 53–59](../../../../../../include/crown/planner/residual.hpp#L53) | Type/record definition: struct ResidualView | source comment (unverified): // Every ID in the trace is an original occurrence/variable ID. The dense view · [reviewed contract](#b0016) |
| [B0017 · 60–62](../../../../../../include/crown/planner/residual.hpp#L60) | Explanatory comments or spacing. | source comment (unverified): // Snapshot all eligibility before deletion. Repeatedly remove the smallest · [reviewed contract](#b0017) |
| [B0018 · 63–70](../../../../../../include/crown/planner/residual.hpp#L63) | Type/record definition: struct ResidualLayer | source comment (unverified): // Snapshot all eligibility before deletion. Repeatedly remove the smallest · [reviewed contract](#b0018) |
| [B0019 · 71–79](../../../../../../include/crown/planner/residual.hpp#L71) | Type/record definition: struct ResidualTraceRecord |  · [reviewed contract](#b0019) |
| [B0020 · 80–92](../../../../../../include/crown/planner/residual.hpp#L80) | Type/record definition: struct ResidualLimits | source comment (unverified): // Residual/view/P02 frames; delegated exact owners use exact.logical_depth · [reviewed contract](#b0020) |
| [B0021 · 93–96](../../../../../../include/crown/planner/residual.hpp#L93) | Type/record definition: struct ResidualOptions |  · [reviewed contract](#b0021) |
| [B0022 · 97–102](../../../../../../include/crown/planner/residual.hpp#L97) | Type/record definition: struct ResidualStatistics |  · [reviewed contract](#b0022) |
| [B0023 · 103–106](../../../../../../include/crown/planner/residual.hpp#L103) | Explanatory comments or spacing. | source comment (unverified): // Bounds concern the full original query. The lower remains universal 0/1 · [reviewed contract](#b0023) |
| [B0024 · 107–119](../../../../../../include/crown/planner/residual.hpp#L107) | Type/record definition: struct ResidualProgress | source comment (unverified): // Bounds concern the full original query. The lower remains universal 0/1 · [reviewed contract](#b0024) |
| [B0025 · 120–120](../../../../../../include/crown/planner/residual.hpp#L120) | Type/record definition: struct ResidualAdvance |  · [reviewed contract](#b0025) |
| [B0026 · 121–121](../../../../../../include/crown/planner/residual.hpp#L121) | Explanatory comments or spacing. |  |
| [B0027 · 122–125](../../../../../../include/crown/planner/residual.hpp#L122) | Type/record definition: enum class ResidualTraceRule |  · [reviewed contract](#b0027) |
| [B0028 · 126–131](../../../../../../include/crown/planner/residual.hpp#L126) | Type/record definition: struct ResidualTraceReport |  · [reviewed contract](#b0028) |
| [B0029 · 132–135](../../../../../../include/crown/planner/residual.hpp#L132) | Explanatory comments or spacing. | source comment (unverified): // Immutable replayed reduction with owned original binding; no tree/height · [reviewed contract](#b0029) |
| [B0030 · 136–150](../../../../../../include/crown/planner/residual.hpp#L136) | Type/record definition: class ResidualTrace | source comment (unverified): // Immutable replayed reduction with owned original binding; no tree/height · [reviewed contract](#b0030) |
| [B0031 · 151–153](../../../../../../include/crown/planner/residual.hpp#L151) | Explanatory comments or spacing. | source comment (unverified): // Immutable original-query P02 upper witness with owned source and trace. · [reviewed contract](#b0031) |
| [B0032 · 154–172](../../../../../../include/crown/planner/residual.hpp#L154) | Type/record definition: class ResidualCandidate | source comment (unverified): // Immutable original-query P02 upper witness with owned source and trace. · [reviewed contract](#b0032) |
| [B0033 · 173–208](../../../../../../include/crown/planner/residual.hpp#L173) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Exclusive single-caller resumable owner; movable between threads under · [reviewed contract](#b0033) |

## B0001

[Lines 1–17](../../../../../../include/crown/planner/residual.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L17:sha256:9409775941b87625b4712d802cb7d9b76a869b20687d3eec194385b1c0cdc680
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use #pragma once to suppress repeated header processing within a translation unit. Make #include "crown/planner/search.hpp", #include &lt;memory&gt;, #include &lt;optional&gt;, #include &lt;string_view&gt; available to include/crown/planner/residual.hpp; open crown::planner and residual_detail; forward-declare TraceData, CandidateData, ArtifactFactory. Attached note: Candidate mode may finish with a checked upper; the default also completes original-query exact proof. Both modes use original exact fallback if needed. |
| inputs / outputs | Preprocessor directives resolve compile-time declarations. This block has no runtime call inputs or result. |
| invariants | Includes, namespace openings, aliases, and forward declarations determine C++ name visibility and type availability; they do not validate planner data or grant proof authority. |
| ownership | No runtime object is owned by the include or scope directives. Any state belongs to the types and functions declared after them. |
| failure | A missing header, incompatible declaration, or ill-formed type use fails during compilation; runtime failures remain in the called code. |
| cost | Adds preprocessing, parsing, and any later template-instantiation work in this translation unit. It adds no runtime timer, counter, branch, or allocation. |
| Design | [include/crown/planner/residual.hpp](../../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md](../../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../../Refactor.md) |

## B0002

[Lines 18–18](../../../../../../include/crown/planner/residual.hpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class ResidualMode {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose whether successful reconstruction finishes with an upper witness or also requires original-query exact proof. |
| inputs / outputs | Two policy values; default ResidualOptions chooses require_exact_original. |
| invariants | Both modes run original exact search if reconstruction fails. Candidate mode can still end with a verified exact result after fallback. |
| ownership | Value-sized policy; owns no query. |
| failure | ResidualSearch::create rejects unknown enum values before search admission. |
| cost | Constant storage and comparisons. |
| Design | [docs/residual_candidates.md](../../../../../residual_candidates.md), [src/planner/residual.cpp](../../../../../../src/planner/residual.cpp) |

## B0003

[Lines 19–20](../../../../../../include/crown/planner/residual.hpp#L19); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L20:sha256:273a3e1daf1b58f8fc48002b5ebd991c83c94460d29c65e6cc416f1a1b7abea9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ResidualOrigin: Last successful tree-construction step, independent of exactness. Earlier graft/repair activity remains in statistics even after later native restores. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ResidualOrigin; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ResidualOrigin come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/residual.hpp](../../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md](../../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../../Refactor.md) |

## B0004

[Lines 21–21](../../../../../../include/crown/planner/residual.hpp#L21); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class ResidualOrigin {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the last successful operation producing a published tree. |
| inputs / outputs | Seed, native/generalized restoration, graft, prefix exact repair, or original exact search. |
| invariants | Origin is provenance, not proof strength. Equal-height original optimum retains the earlier construction origin; statistics retain earlier activity. |
| ownership | Copied enum stored with the immutable candidate. |
| failure | No validation or exceptions in the enum; facade controls assignments. |
| cost | Constant storage. |
| Design | [docs/residual_candidates.md](../../../../../residual_candidates.md), [src/planner/residual_reconstruct.cpp](../../../../../../src/planner/residual_reconstruct.cpp), [src/planner/residual.cpp](../../../../../../src/planner/residual.cpp) |

## B0005

[Lines 22–25](../../../../../../include/crown/planner/residual.hpp#L22); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class ResidualPhase {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the observable retained search phase. |
| inputs / outputs | Progress reports admission, reduction, replay, restoration, validation, repair, original search or terminal state. |
| invariants | Phases do not confer tree or minimum authority; exact_progress separately describes delegated search. |
| ownership | Value snapshot with no references. |
| failure | No failure in the enum; internal stage mapping provides the phase. |
| cost | Constant storage. |
| Design | [docs/residual_candidates.md](../../../../../residual_candidates.md), [src/planner/residual.cpp](../../../../../../src/planner/residual.cpp) |

## B0006

[Lines 26–26](../../../../../../include/crown/planner/residual.hpp#L26); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class ResidualResult {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State whether search is unfinished, has a completed checked candidate, has original exact authority, or failed. |
| inputs / outputs | Returned through ResidualProgress.result. |
| invariants | checked_candidate is upper-only; verified values require completed original P06 authority. Cancellation preserves unfinished result with a cancelled phase. |
| ownership | Value snapshot, independent of owner lifetime. |
| failure | The enum cannot manufacture an artifact or validate a query. |
| cost | Constant storage. |
| Design | [docs/residual_candidates.md](../../../../../residual_candidates.md), [src/planner/residual.cpp](../../../../../../src/planner/residual.cpp), [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp) |

## B0007

[Lines 27–27](../../../../../../include/crown/planner/residual.hpp#L27); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class ResidualProofStatus {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish verified reduction metadata, checked upper witness and exact original proof. |
| inputs / outputs | Progress flag with four increasing authority descriptions. |
| invariants | Trace verification does not establish any height. A prefix proof never becomes exact_original_verified. |
| ownership | Value snapshot; no proof ownership. |
| failure | No exceptions or enforcement in the type; publication paths enforce meaning. |
| cost | Constant storage. |
| Design | [docs/residual_candidates.md](../../../../../residual_candidates.md), [src/planner/residual.cpp](../../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../../src/planner/residual_trace.cpp) |

## B0008

[Lines 28–32](../../../../../../include/crown/planner/residual.hpp#L28); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class ResidualStopReason {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report cooperative grant stops, resource stops, terminal failures and lifecycle outcomes. |
| inputs / outputs | ResidualAdvance.stopped_for and stored nonzero-call last_stop. |
| invariants | exact_limit carries a separate StopReason; counter exhaustion is terminal. A grant stop does not mean infeasible. |
| ownership | Value only, returned without allocating diagnostics. |
| failure | No exceptions in the enum; advance catches failures into these values. |
| cost | Constant storage. |
| Design | [docs/residual_candidates.md](../../../../../residual_candidates.md), [src/planner/residual.cpp](../../../../../../src/planner/residual.cpp), [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp) |

## B0009

[Lines 33–33](../../../../../../include/crown/planner/residual.hpp#L33); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class ResidualTerminal {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain why frozen-ear reduction stopped. |
| inputs / outputs | Empty original body, q-hierarchical remaining query, or a nonhierarchical round with no deletion. |
| invariants | stalled transfers to complete search; neither a stalled nor hierarchical residual proves original optimum. |
| ownership | Value stored in immutable trace records. |
| failure | No rejection in enum; independent replay checks the claimed terminal against derived state. |
| cost | Constant storage. |
| Design | [docs/residual_candidates.md](../../../../../residual_candidates.md), [src/planner/residual_reduce.cpp](../../../../../../src/planner/residual_reduce.cpp), [src/planner/residual_trace.cpp](../../../../../../src/planner/residual_trace.cpp) |

## B0010

[Lines 34–35](../../../../../../include/crown/planner/residual.hpp#L34); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L34-L35:sha256:cbda03420555d1e4278d5ab5f05bceb75b0c28e07e7d1f664cefddc261340711
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for EarCondition: Frozen ear-condition bits: P2 arXiv:2603.14754v1, Section 2.1.4, Definition 2.9. These bits describe supports, not reconstruction or height proof. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies EarCondition; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for EarCondition come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/residual.hpp](../../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md](../../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../../Refactor.md), [P2 arXiv:2603.14754v1 §2.1.4, Definition 2.9 and Algorithm 1 (frozen-ear reduction recipe only)](https://arxiv.org/pdf/2603.14754v1) |

## B0011

[Lines 36–36](../../../../../../include/crown/planner/residual.hpp#L36); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class EarCondition : unsigned {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record exactly which of the two ear conditions held for one frozen supporting anchor. |
| inputs / outputs | Bits 1 and 2, with both represented by 3. |
| invariants | Both applicable conditions are retained; this is metadata rather than a reconstruction or height certificate. |
| ownership | Value in each EarAnchor. |
| failure | Replay rejects missing, extra or incorrect bits. |
| cost | Constant storage. |
| Design | [docs/residual_candidates.md](../../../../../residual_candidates.md), [src/planner/residual_reduce.cpp](../../../../../../src/planner/residual_reduce.cpp), [src/planner/residual_trace.cpp](../../../../../../src/planner/residual_trace.cpp), [P2 arXiv:2603.14754v1 §2.1.4, Definition 2.9](https://arxiv.org/pdf/2603.14754v1) |

## B0012

[Lines 37–40](../../../../../../include/crown/planner/residual.hpp#L37); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct EarAnchor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one supporting original occurrence and the frozen condition bits. |
| inputs / outputs | Original occurrence index and EarCondition. |
| invariants | Anchor differs from the ear; producer orders anchors by original occurrence ID. It may be deleted later in the same round. |
| ownership | Owns scalar fields only; no occurrence reference. |
| failure | Aggregate does no range check; TraceReplayMachine independently checks each support. |
| cost | Constant storage per anchor; all-pairs eligibility may produce quadratic many anchors. |
| Design | [docs/residual_candidates.md](../../../../../residual_candidates.md), [src/planner/residual_reduce.cpp](../../../../../../src/planner/residual_reduce.cpp), [src/planner/residual_trace.cpp](../../../../../../src/planner/residual_trace.cpp) |

## B0013

[Lines 41–46](../../../../../../include/crown/planner/residual.hpp#L41); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct EarRecord {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze the ear scope partition and every eligible anchor before deleting any ear in that round. |
| inputs / outputs | Original ear index, shared and unique variable sets, ordered anchor vector. |
| invariants | shared equals original scope minus current unique variables; unique is its intersection with that set. Equal-scope occurrences retain distinct IDs. |
| ownership | Owns sets/vector; immutable after the trace is published. |
| failure | Raw records are caller-editable data; only replayed ResidualTrace has checked trace status. |
| cost | Storage is scope members plus all eligible supports; set operations are logarithmic. |
| Design | [docs/residual_candidates.md](../../../../../residual_candidates.md), [src/planner/residual_reduce.cpp](../../../../../../src/planner/residual_reduce.cpp), [src/planner/residual_trace.cpp](../../../../../../src/planner/residual_trace.cpp) |

## B0014

[Lines 47–47](../../../../../../include/crown/planner/residual.hpp#L47); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct EarDeletion {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record one actual frozen-ear removal and the still-live anchor chosen at that instant. |
| inputs / outputs | Two original occurrence indexes in deletion order. |
| invariants | The chosen pair is appended successfully before liveness changes. Reverse deletion order restores anchors before dependent ears. |
| ownership | Owns two numeric IDs. |
| failure | Raw aggregate does not check liveness or order; replay does. |
| cost | Constant storage per deleted occurrence. |
| Design | [docs/residual_candidates.md](../../../../../residual_candidates.md), [src/planner/residual_reduce.cpp](../../../../../../src/planner/residual_reduce.cpp), [src/planner/residual_trace.cpp](../../../../../../src/planner/residual_trace.cpp), [src/planner/residual_reconstruct.cpp](../../../../../../src/planner/residual_reconstruct.cpp) |

## B0015

[Lines 48–52](../../../../../../include/crown/planner/residual.hpp#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L52:sha256:685eacd12270c6b6a130f3274eba0e69060a4c5f43eda61407b9e5111167f6ba
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ResidualView: Every ID in the trace is an original occurrence/variable ID. The dense view is an explicit separate binding; its proof never certifies the original query. Dense local occurrence/variable IDs map explicitly to ascending original IDs. Table IDs still address the retained original catalog. Ordered surviving head positions, repeated aliases, constants and ignored columns are preserved. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ResidualView; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ResidualView come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/residual.hpp](../../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md](../../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../../Refactor.md) |

## B0016

[Lines 53–59](../../../../../../include/crown/planner/residual.hpp#L53); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ResidualView {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own an induced query with dense local IDs and explicit maps to the original binding. |
| inputs / outputs | Query, local-to-original occurrence/variable vectors, and original-sized optional inverse vectors. |
| invariants | Occurrences and variables are ascending original IDs; constants, ignored columns, names/types, contradiction and ordered surviving head positions are preserved. Query proof scope is this induced query. |
| ownership | Owns query and maps; table IDs still address the separately retained original catalog. |
| failure | The aggregate validates nothing; InducedViewMachine constructs it and independent replay checks terminal content. |
| cost | Linear map sizes in original atom/variable counts plus induced query contents; strings and terms are copied. |
| Design | [docs/residual_candidates.md](../../../../../residual_candidates.md), [src/planner/residual_view.cpp](../../../../../../src/planner/residual_view.cpp), [src/planner/residual_trace.cpp](../../../../../../src/planner/residual_trace.cpp) |

## B0017

[Lines 60–62](../../../../../../include/crown/planner/residual.hpp#L60); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L60-L62:sha256:7dca56ae69186258e022e7f1d59f45f4b57d390856a1ef88540cb67207b96314
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ResidualLayer: Snapshot all eligibility before deletion. Repeatedly remove the smallest original ear with its smallest still-live frozen anchor; a stalled round is retained and requests complete search rather than claiming infeasibility. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ResidualLayer; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ResidualLayer come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/residual.hpp](../../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md](../../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../../Refactor.md) |

## B0018

[Lines 63–70](../../../../../../include/crown/planner/residual.hpp#L63); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ResidualLayer {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one complete pre-round snapshot and its maximal frozen deletion result. |
| inputs / outputs | Members, variables/head/unique sets, eligible ears, ordered deletions, remaining members and residual head. |
| invariants | No new ears are discovered during deletion; smallest live eligible pair is chosen repeatedly. A stalled layer is retained. |
| ownership | Owns all collections by value; trace publication freezes their use. |
| failure | Replay rejects inconsistent metadata or nonmaximal/deviating deletion sequence. |
| cost | Per-layer member/scope data plus potentially quadratic support records; retained layers accumulate. |
| Design | [docs/residual_candidates.md](../../../../../residual_candidates.md), [src/planner/residual_reduce.cpp](../../../../../../src/planner/residual_reduce.cpp), [src/planner/residual_trace.cpp](../../../../../../src/planner/residual_trace.cpp) |

## B0019

[Lines 71–79](../../../../../../include/crown/planner/residual.hpp#L71); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ResidualTraceRecord {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize complete frozen reduction and terminal binding as untrusted data. |
| inputs / outputs | Version 1, original scopes, layers, final members/head/terminal and dense view. |
| invariants | All trace IDs outside the dense query/maps are original binding IDs. Replay proves these reduction facts only. |
| ownership | Owns nested records, sets and query copies; public verified handle exposes const access. |
| failure | Edited aggregates cannot construct ResidualTrace; verify_residual_trace returns a diagnostic report without upgrading authority. |
| cost | Storage is cumulative retained layers, supports, scopes and terminal query; a raw copy is variable-width. |
| Design | [docs/residual_candidates.md](../../../../../residual_candidates.md), [src/planner/residual_trace.cpp](../../../../../../src/planner/residual_trace.cpp), [src/planner/residual.cpp](../../../../../../src/planner/residual.cpp) |

## B0020

[Lines 80–92](../../../../../../include/crown/planner/residual.hpp#L80); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ResidualLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure distinct outer work/time, residual depth/content and delegated exact ceilings. |
| inputs / outputs | Defaults: 50M outer attempts, depth 256, 1M records, 10M cells, plus ContinuationLimits. |
| invariants | Records/cells charge cumulative logical construction, including discarded drafts/replay. Admission copies, validator scratch, exact storage, capacities and cleanup are outside this content account. |
| ownership | Copied value limits; ConstructionBudget and ResourceLedger retain their current versions. |
| failure | Negative time rejects admission; stops preserve owners for monotone extension except terminal overflow. Limits are not allocator bytes or hard deadlines. |
| cost | Fixed-size limit record; checking is constant-time; operations between checkpoints may have variable cost. |
| Design | [docs/residual_candidates.md](../../../../../residual_candidates.md), [docs/planner_continuations.md](../../../../../planner_continuations.md), [src/planner/residual.cpp](../../../../../../src/planner/residual.cpp), [src/planner/residual_machine.hpp](../../../../../../src/planner/residual_machine.hpp) |

## B0021

[Lines 93–96](../../../../../../include/crown/planner/residual.hpp#L93); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ResidualOptions {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind the search mode and all resource ceilings at admission. |
| inputs / outputs | Default exact-original policy plus ResidualLimits. |
| invariants | Policy never changes on resume; raise_limits changes only monotone ceilings. |
| ownership | Copied into the move-only search owner. |
| failure | create validates policy/time and validates the Catalog/Query before creating workers. |
| cost | Fixed-size record, no allocation in copying options. |
| Design | [docs/residual_candidates.md](../../../../../residual_candidates.md), [src/planner/residual.cpp](../../../../../../src/planner/residual.cpp) |

## B0022

[Lines 97–102](../../../../../../include/crown/planner/residual.hpp#L97); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ResidualStatistics {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose diagnostic counts for reduction, proposals, repairs, admission and publication. |
| inputs / outputs | Twelve uint64 counters accumulated from owner and workers. |
| invariants | Counters are activity/provenance, never lower-bound evidence. Local increment guards stop at exhaustion; merged snapshots saturate. |
| ownership | Value counters; retained across cancellation by the facade. |
| failure | Overflow guards are required before multi-effect publications; snapshot merging does not throw. |
| cost | Constant-size storage and aggregation; no scan of trace/tree data. |
| Design | [docs/residual_candidates.md](../../../../../residual_candidates.md), [src/planner/residual.cpp](../../../../../../src/planner/residual.cpp), [src/planner/residual_reduce.cpp](../../../../../../src/planner/residual_reduce.cpp), [src/planner/residual_reconstruct.cpp](../../../../../../src/planner/residual_reconstruct.cpp) |

## B0023

[Lines 103–106](../../../../../../include/crown/planner/residual.hpp#L103); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L103-L106:sha256:e880263f4a105c158aeeb0b7f9514773865b8038841930c0a2a78726b58d0468
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ResidualProgress: Bounds concern the full original query. The lower remains universal 0/1 until original proof completes; exact_progress may instead describe an induced seed/repair, as distinguished by exact_scope_original. This snapshot is diagnostic data and cannot be edited into authoritative handles. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ResidualProgress; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ResidualProgress come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/residual.hpp](../../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md](../../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../../Refactor.md) |

## B0024

[Lines 107–119](../../../../../../include/crown/planner/residual.hpp#L107); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ResidualProgress {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return an allocating-free diagnostic snapshot of the retained owner and original-query bounds. |
| inputs / outputs | Phase/result/status, outer ledger/content counts, statistics, trace flags and a scope-qualified exact subsearch snapshot. |
| invariants | Original lower stays universal zero/one until original exact completion. Published full original tree alone supplies upper. exact_scope_original distinguishes prefix diagnostics. |
| ownership | Owns only scalar/optional value snapshots; contains no authoritative tree or proof handle. |
| failure | Moved-from/failed/cancelled states are explicit; copied or edited progress cannot construct checked artifacts. |
| cost | Constant-size copy and aggregation over a fixed number of workers. |
| Design | [docs/residual_candidates.md](../../../../../residual_candidates.md), [src/planner/residual.cpp](../../../../../../src/planner/residual.cpp), [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp) |

## B0025

[Lines 120–120](../../../../../../include/crown/planner/residual.hpp#L120); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ResidualAdvance {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return an ephemeral stop reason alongside the current progress snapshot. |
| inputs / outputs | Residual reason, delegated exact reason and ResidualProgress by value. |
| invariants | Zero-work/time calls leave stored progress unchanged even when the returned grant reason differs from stored last_stop. |
| ownership | Owns the snapshot; no borrowed pointers. |
| failure | Construction allocates nothing and is usable in noexcept advance under allocation failure. |
| cost | Constant-size return. |
| Design | [docs/residual_candidates.md](../../../../../residual_candidates.md), [src/planner/residual.cpp](../../../../../../src/planner/residual.cpp) |

## B0027

[Lines 122–125](../../../../../../include/crown/planner/residual.hpp#L122); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class ResidualTraceRule {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify the first failed replay obligation or a replay resource outcome. |
| inputs / outputs | Rules cover version, scope/membership/ear/delete/terminal/map/query and resource/allocation failure. |
| invariants | Rule describes trace consistency, never height feasibility or optimality. |
| ownership | Value in ResidualTraceReport. |
| failure | No exception in the enum; replay/adapter assign it on failure. |
| cost | Constant storage. |
| Design | [docs/residual_candidates.md](../../../../../residual_candidates.md), [src/planner/residual_trace.cpp](../../../../../../src/planner/residual_trace.cpp) |

## B0028

[Lines 126–131](../../../../../../include/crown/planner/residual.hpp#L126); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ResidualTraceReport {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report diagnostic replay success or failure with the current source context. |
| inputs / outputs | valid/resource flags, replay work count, failure rule and optional layer/ear/anchor IDs. |
| invariants | valid is set only after every reduction and terminal-view check. Context is diagnostic and can remain set when a resource stop interrupts work. |
| ownership | Self-contained value; owns no query, trace, tree or lower proof. |
| failure | Allocation and search-limit stops force valid=false; no report creates a ResidualTrace or minimum certificate. |
| cost | Constant-size nonallocating copy. |
| Design | [docs/residual_candidates.md](../../../../../residual_candidates.md), [src/planner/residual_trace.cpp](../../../../../../src/planner/residual_trace.cpp) |

## B0029

[Lines 132–135](../../../../../../include/crown/planner/residual.hpp#L132); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L132-L135:sha256:48e59018348c14e421a28f9aa9bfcafd484ee487b3894ba34bc8a3e5b8dc4d03
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ResidualTrace: Immutable replayed reduction with owned original binding; no tree/height authority. Copies survive facade destruction; getters borrow from a live handle and reject moved-from handles. Copy/move/valid do not allocate. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ResidualTrace; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ResidualTrace come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/residual.hpp](../../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md](../../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../../Refactor.md) |

## B0030

[Lines 136–150](../../../../../../include/crown/planner/residual.hpp#L136); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class ResidualTrace {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain immutable original binding and a fully replayed reduction record. |
| inputs / outputs | Copyable/movable const access to catalog/query/record, with valid() for moved-from detection. |
| invariants | Private construction is restricted to ArtifactFactory after replay; the trace proves neither candidate validity nor minimum height. |
| ownership | Shared ownership lets copies outlive moved, cancelled or destroyed search owners; returned references require a live handle copy. |
| failure | Nonvalid access throws invalid_residual_handle; copy/move/valid allocate nothing. |
| cost | Handle copy/access is constant-time; final payload destruction traverses owned data. |
| Design | [docs/residual_candidates.md](../../../../../residual_candidates.md), [src/planner/residual.cpp](../../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../../src/planner/residual_trace.cpp) |

## B0031

[Lines 151–153](../../../../../../include/crown/planner/residual.hpp#L151); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L151-L153:sha256:4aa3ceab8267933fb52c3a82207af993c40944c08673f5d83f505f5693ac2020
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ResidualCandidate: Immutable original-query P02 upper witness with owned source and trace. Exactness requires the separate original VerifiedOptimum. Old copies keep their checked upper when later search publishes a better candidate. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ResidualCandidate; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ResidualCandidate come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/residual.hpp](../../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md](../../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../../Refactor.md) |

## B0032

[Lines 154–172](../../../../../../include/crown/planner/residual.hpp#L154); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class ResidualCandidate {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain a fully original-bound, independently checked tree as an immutable upper witness. |
| inputs / outputs | Const binding/tree/height/origin access and the corresponding verified trace. |
| invariants | Exactly one checked P02 upper or exact upper backs the tree. A later improved publication does not mutate old handles; exactness requires a separate VerifiedOptimum. |
| ownership | Shared immutable ownership survives facade lifetime; tree/query references borrow from a live copy of this handle. |
| failure | Moved-from access throws invalid_residual_handle; public data cannot construct this private authority. |
| cost | Constant handle copies/getters; tree and binding were prepared before publication; final release is size-dependent. |
| Design | [docs/residual_candidates.md](../../../../../residual_candidates.md), [src/planner/residual.cpp](../../../../../../src/planner/residual.cpp), [src/planner/verify.cpp](../../../../../../src/planner/verify.cpp), [include/crown/planner/search.hpp](../../../../../../include/crown/planner/search.hpp) |

## B0033

[Lines 173–208](../../../../../../include/crown/planner/residual.hpp#L173); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class ResidualSearch {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one exclusive, resumable frozen-reduction, checked reconstruction and optional original exact search. |
| inputs / outputs | create validates owned inputs; advance grants work, progress reports diagnostics, artifact getters publish authority, raise_limits extends and cancel releases work. |
| invariants | Single caller only. Prefix proofs never certify original optimum; default mode completes/replays original P06 proof. Moves transfer the owner. |
| ownership | Move-only pimpl retains binding, workers, cursors and immutable artifact owners. Published handles outlive cancellation/destruction. |
| failure | Admission may throw. advance returns fixed stop enums without throwing; failed invariants are terminal; allocation/limit stops retain retry state. |
| cost | Admission copies/validates variable-width input; advances meter saved operations; cancellation/destruction reclaim retained state outside grants. |
| Design | [docs/residual_candidates.md](../../../../../residual_candidates.md), [src/planner/residual.cpp](../../../../../../src/planner/residual.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md) |
