# `include/crown/planner/update_pattern.hpp` — block usage map

[Source](../../../../../../include/crown/planner/update_pattern.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Recognize structural query classes, check a proposed CROWN tree and lower checked structure into physical metadata.

Snapshot SHA-256: `35ea8b09d2e4a06bea5cb4c208013a3b4db6cf10bb1828a095e86454db62f6b7`. 61 lines partitioned into 12 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [planner](../../../../subsystem_contracts.md#planner). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../../planner_proofs.md), [docs/tree_plans.md](../../../../../tree_plans.md), [docs/physical_plans.md](../../../../../physical_plans.md), [docs/code_review.md](../../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../../include/crown/planner/update_pattern.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases. | source comment (unverified): // Conditional sufficient cases on genuine P02/P07 candidates. These results · [reviewed contract](#b0001) |
| [B0002 · 15–15](../../../../../../include/crown/planner/update_pattern.hpp#L15) | Type/record definition: enum class SufficientCase | source comment (unverified): // Unknown is an unproved case, never a hardness or impossibility result. · [reviewed contract](#b0002) |
| [B0003 · 16–19](../../../../../../include/crown/planner/update_pattern.hpp#L16) | Explanatory comments or spacing. | source comment (unverified): // Event mapping bounds zero/one row per occurrence; monotone_source additionally · [reviewed contract](#b0003) |
| [B0004 · 20–21](../../../../../../include/crown/planner/update_pattern.hpp#L20) | Type/record definition: enum class Transfer | source comment (unverified): // Event mapping bounds zero/one row per occurrence; monotone_source additionally · [reviewed contract](#b0004) |
| [B0005 · 22–23](../../../../../../include/crown/planner/update_pattern.hpp#L22) | Explanatory comments or spacing. | source comment (unverified): // Child insertion-only and joint FIFO bases describe native leaves. A subtree · [reviewed contract](#b0005) |
| [B0006 · 24–24](../../../../../../include/crown/planner/update_pattern.hpp#L24) | Type/record definition: enum class EdgeBasis | source comment (unverified): // Child insertion-only and joint FIFO bases describe native leaves. A subtree · [reviewed contract](#b0006) |
| [B0007 · 25–28](../../../../../../include/crown/planner/update_pattern.hpp#L25) | declares callable signatures. | source comment (unverified): // Stable diagnostic names; unknown values grant no additional authority. · [reviewed contract](#b0007) |
| [B0008 · 29–34](../../../../../../include/crown/planner/update_pattern.hpp#L29) | Type/record definition: struct EdgeCondition |  · [reviewed contract](#b0008) |
| [B0009 · 35–40](../../../../../../include/crown/planner/update_pattern.hpp#L35) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Plain diagnostic report, not proof authority. Handles retain the exact · [reviewed contract](#b0009) |
| [B0010 · 41–50](../../../../../../include/crown/planner/update_pattern.hpp#L41) | Type/record definition: struct Analysis | source comment (unverified): // Plain diagnostic report, not proof authority. Handles retain the exact · [reviewed contract](#b0010) |
| [B0011 · 51–55](../../../../../../include/crown/planner/update_pattern.hpp#L51) | Type/record definition: struct Attempt |  · [reviewed contract](#b0011) |
| [B0012 · 56–61](../../../../../../include/crown/planner/update_pattern.hpp#L56) | declares values/defaults or compile-time conditions. | source comment (unverified): // Full typed binding is checked before the private visitor. A failed grant · [reviewed contract](#b0012) |

## B0001

[Lines 1–14](../../../../../../include/crown/planner/update_pattern.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:d04257c6010985ee180e0a2b78f8f7ae75611bee1bbc7cadceaefe89c59606d8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the source-bound declaration/ranking API and expose conditional source/tree analysis vocabulary. |
| inputs / outputs | Import declaration/ranking and string_view types for conditional analysis and allocation-free diagnostic enum labels. |
| invariants | P02/P07 supplies genuine candidate/height authority. These enums and reports describe conditional applicability, not actual trace enforcement or a new structural certificate. |
| ownership | No report is constructed by this namespace scaffolding. |
| failure | No runtime failure path. |
| cost | Compile-time only. |
| Design | [docs/update_patterns.md](../../../../../update_patterns.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/selection.md](../../../../../selection.md) |

## B0002

[Lines 15–15](../../../../../../include/crown/planner/update_pattern.hpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L15:sha256:28e5f333321ded179c96ec78efc58a14617a74b87c06785266ec185fc18a506a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify the narrow sufficient cases returned by analysis. |
| inputs / outputs | Existing unknown/constant/insertion-only/height-one/height-two values retain their order; appended subtree_edges identifies the proved taller subtree-or-FIFO-leaf condition. |
| invariants | Sufficient cases are not a complete characterization. Unknown means this analysis did not prove a case; it is not impossibility or hardness. Whole-session CPU/delay remains separate. |
| ownership | Enum has no owned state. |
| failure | No failure path; failed processing is reported by Attempt.stop. |
| cost | O(1) enum. |
| Design | [docs/update_patterns.md](../../../../../update_patterns.md), [docs/planner_proofs.md](../../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0003

[Lines 16–19](../../../../../../include/crown/planner/update_pattern.hpp#L16); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L16-L19:sha256:d623e3806ddad9b4254bbcb44ffba322d6f6a99cc5b5ab1eeddd2d43a62fbcb1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish bounded source events and monotone inputs from the stronger mixed lifetime transfer. |
| inputs / outputs | Comments explain the adjacent Transfer vocabulary; no executable input or output. |
| invariants | Zero/one occurrence events do not establish injectivity or FIFO preservation. checked_typed_cq passes stronger source gates, while edge sufficiency is separate. |
| ownership | Source text only; no runtime owner. |
| failure | No runtime failure behavior. |
| cost | No execution cost. |
| Design | [docs/update_patterns.md](../../../../../update_patterns.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md), [build/verification/v53-taller-mixed-proof-v1/proof.md](../../../../../../build/verification/v53-taller-mixed-proof-v1/proof.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0004

[Lines 20–21](../../../../../../include/crown/planner/update_pattern.hpp#L20); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L21:sha256:2b3db1cbb9e49d461ac50b549e55cb8db36ae8846388382ef536078c891dcd4d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record the source-to-maintenance transfer gate outcome. |
| inputs / outputs | Retain earlier transfer outcomes; append checked_event_mapping for bounded admitted occurrence events and checked_monotone_source when every participating actual physical base is insertion-only. |
| invariants | not_checked is raw report construction; not_required is a constant route. Event mapping and monotone source do not assert injective/FIFO lifetime transfer. checked_typed_cq means the stronger direct typed, non-null, no-ignored-column, self-join-free gates passed; tree edge premises remain separate. |
| ownership | Enum has no owned state. |
| failure | No failure path. |
| cost | O(1) enum. |
| Design | [docs/update_patterns.md](../../../../../update_patterns.md), [docs/planner_proofs.md](../../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0005

[Lines 22–23](../../../../../../include/crown/planner/update_pattern.hpp#L22); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L23:sha256:f63a9cf99f83a58e32c4ca372b61ce805c9caba69a4ba9e4eea1e37cbd7f703f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish leaf-only edge premises from a wholly monotone child subtree. |
| inputs / outputs | Comments explain the neighboring EdgeBasis enum. |
| invariants | The subtree premise includes the child itself and every native descendant. A FIFO basis is not granted for a nonleaf. |
| ownership | Source text only. |
| failure | No runtime failure behavior. |
| cost | No execution cost. |
| Design | [docs/update_patterns.md](../../../../../update_patterns.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md), [build/verification/v53-taller-mixed-proof-v1/proof.md](../../../../../../build/verification/v53-taller-mixed-proof-v1/proof.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0006

[Lines 24–24](../../../../../../include/crown/planner/update_pattern.hpp#L24); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class EdgeBasis
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the evidence used for a retained native edge. |
| inputs / outputs | unproved, child_insertion_only and joint_fifo_scope retain their values; appended subtree_insertion_only names a wholly monotone nonleaf child subtree. |
| invariants | Child-insertion and joint-FIFO bases are used for native leaves. A nonleaf subtree basis requires the child and every native descendant insertion-only. Equal positive raw IDs establish the explicit joint scope; no inferred union. |
| ownership | Enum has no owned state. |
| failure | An unproved edge remains visible and prevents height_two_edges. |
| cost | O(1) enum. |
| Design | [docs/update_patterns.md](../../../../../update_patterns.md), [docs/planner_proofs.md](../../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0007

[Lines 25–28](../../../../../../include/crown/planner/update_pattern.hpp#L25); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L28:sha256:fa31008707394e00898f1c0632e5320ef3c620cfa23bd820c0fdd3efa5290a75
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare allocation-free diagnostic labels for the exact pattern vocabulary. |
| inputs / outputs | Overload name() for SufficientCase, Transfer and EdgeBasis, returning borrowed static string_view labels. |
| invariants | Labels are presentation only; an unrecognized enum value confers no positive case or authority. |
| ownership | Declarations retain nothing; definitions return static text. |
| failure | Header declarations alone do not execute; absent definitions fail linking. |
| cost | Compile-time declaration cost only. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../../selection.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0008

[Lines 29–34](../../../../../../include/crown/planner/update_pattern.hpp#L29); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L34:sha256:697164c7f812a52a4080e4b03e540d48a3093bfcc317aaa63b1dab5fe0636cf9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store one analyzed native parent-child dependency and its declaration premise. |
| inputs / outputs | Carries parent/child NodeIds, parent/child TableIds, basis, and optional raw fifo_scope. |
| invariants | Only native edges in the audited height-two tree are candidates for this record; unproved edges retain basis=unproved and no invented scope. |
| ownership | Analysis owns edge values in its receiving-account vector; IDs do not own tree or declaration storage. |
| failure | Malformed candidate structure is translated through the public Attempt boundary. |
| cost | O(1) per edge cell; Q edges are bounded by query atom count. |
| Design | [docs/update_patterns.md](../../../../../update_patterns.md), [docs/planner_proofs.md](../../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf), [docs/query_memory.md](../../../../../query_memory.md) |

## B0009

[Lines 35–40](../../../../../../include/crown/planner/update_pattern.hpp#L35); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L40:sha256:7326750dc9bfd52ac1b3706fac75010c991b32c0da15ccc852f44c73cafe33db
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the receiving-account vector type and delimit Analysis as a conditional diagnostic report. |
| inputs / outputs | Vector&lt;T&gt; uses OwnerAllocator&lt;T&gt;; adjacent comment says candidate/declaration handles retain their funded owners and edge storage is newly charged to the receiving account. |
| invariants | Analysis is not proof authority and claims no live compliance, total session CPU/delay, exhaustive families, or optimal cost. |
| ownership | The allocator is bound to the analysis caller’s MemoryAccount; candidate/declaration copies retain their original owners. |
| failure | Vector growth may report allocation failure through analyse’s noexcept Attempt. |
| cost | O(E) retained edge cells, separately charged to the receiving account. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/update_patterns.md](../../../../../update_patterns.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0010

[Lines 41–50](../../../../../../include/crown/planner/update_pattern.hpp#L41); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L50:sha256:3e1e5d4ce70e959636922747a45237cbdce63b00a9a9e6da3a149dbbecbf5da8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent one candidate’s conditional update-pattern analysis. |
| inputs / outputs | Retain candidate and Declaration handles with case/transfer/height/edges. Raw construction starts unknown/not_checked with an empty receiving-account vector and no edge allocation. |
| invariants | A successful analyse/selection path retains the exact checked candidate and source-bound declaration. Analysis is mutable diagnostic data; direct construction does not validate handles or grant runtime/proof authority. |
| ownership | Candidate/declaration handle copies share original owners; \`edges\` is separately allocated from the receiving account. |
| failure | This constructor copies handles and creates an empty vector without allocating edge storage. Later visitor edge growth can fail and the public analyse boundary returns no partial report. |
| cost | O(1) handles plus O(E) edge storage; analysis also uses O(Q) scratch as documented. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/update_patterns.md](../../../../../update_patterns.md), [docs/update_patterns.md](../../../../../update_patterns.md), [docs/planner_proofs.md](../../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0011

[Lines 51–55](../../../../../../include/crown/planner/update_pattern.hpp#L51); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L55:sha256:2e9c051413fdf7be91e393d007739f319a4fa053e7882f97374866ced5c8f0d5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pair a stop/result with the aggregate ranking usage measured by analysis. |
| inputs / outputs | stop defaults internal_error; optional Analysis is present only after complete success; Usage records charged work/cells/payload/time. |
| invariants | A failed Attempt must not expose a partial Analysis. |
| ownership | Optional owns an Analysis value on success, including its copied candidate/declaration handles and receiving-account edge vector. |
| failure | Stop differentiates binding, work, resource, allocation, and internal failures per existing ranking categories. |
| cost | O(1) result wrapper plus report storage on success. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/update_patterns.md](../../../../../update_patterns.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |

## B0012

[Lines 56–61](../../../../../../include/crown/planner/update_pattern.hpp#L56); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L56-L61:sha256:fe54257b39766d7b58e303c6e0b9c2f004bd4c3e9ecf5dfc2f5afdcd8748d999
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the public nonthrowing analyzer for a genuine candidate, source, declaration, and finite ranking limits. |
| inputs / outputs | Inputs are receiving account, CompiledProgram, MinimumHeightCandidate, Declaration, optional ranking Limits; output is Attempt. |
| invariants | Full typed binding is checked before private analysis; failure returns no partial report. Report is conditional metadata, not runtime enforcement or a theorem token. |
| ownership | The source is a synchronous borrow, not retained by the report. Candidate and Declaration copies retain their existing owners under those owners' allocation contracts; newly allocated scratch/edges use the receiving account. |
| failure | noexcept boundary translates known ranking failures, bad_alloc, and unexpected failures into Attempt.stop. |
| cost | Includes source binding and candidate analysis costs; no runtime per-update work or delay guarantee. |
| Design | [docs/update_patterns.md](../../../../../update_patterns.md), [docs/planner_proofs.md](../../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf), [docs/selection.md](../../../../../selection.md), [docs/update_patterns.md](../../../../../update_patterns.md), [docs/query_memory.md](../../../../../query_memory.md) |
