# `include/crown/planner/meta_candidates.hpp` — block usage map

[Source](../../../../../../include/crown/planner/meta_candidates.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Search the finite canonical tree space and retain resumable evidence for exact minimum-height claims.

Snapshot SHA-256: `f2a2493d4bf7278e927deac3eb655cc2a2d649b5fb5085cf07df45f2ec889ab4`. 83 lines partitioned into 9 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [search](../../../../subsystem_contracts.md#search). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../../tree_oracle.md), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../../candidate_alternatives.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../../include/crown/planner/meta_candidates.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 11–14](../../../../../../include/crown/planner/meta_candidates.hpp#L11) | Type/record definition: struct MetaMappingLimits |  · [reviewed contract](#b0002) |
| [B0003 · 15–18](../../../../../../include/crown/planner/meta_candidates.hpp#L15) | Type/record definition: struct MetaMappingUsage |  · [reviewed contract](#b0003) |
| [B0004 · 19–22](../../../../../../include/crown/planner/meta_candidates.hpp#L19) | Type/record definition: enum class MappingStop |  · [reviewed contract](#b0004) |
| [B0005 · 23–28](../../../../../../include/crown/planner/meta_candidates.hpp#L23) | Type/record definition: struct MetaCandidateLimits |  · [reviewed contract](#b0005) |
| [B0006 · 29–31](../../../../../../include/crown/planner/meta_candidates.hpp#L29) | Explanatory comments or spacing. | source comment (unverified): // Preparation diagnostics, not a height certificate or a checked capability. · [reviewed contract](#b0006) |
| [B0007 · 32–51](../../../../../../include/crown/planner/meta_candidates.hpp#L32) | Type/record definition: struct MetaCandidateReport | source comment (unverified): // Preparation diagnostics, not a height certificate or a checked capability. · [reviewed contract](#b0007) |
| [B0008 · 52–62](../../../../../../include/crown/planner/meta_candidates.hpp#L52) | Type/record definition: struct PreparedMetaCandidates | returns report.ordinary_exhausted && report.mapped_input_fibers_exhausted &&; source comment (unverified): // Fresh diagnostic: complete preparation alone never means P02 admission. · [reviewed contract](#b0008) |
| [B0009 · 63–83](../../../../../../include/crown/planner/meta_candidates.hpp#L63) | declares values/defaults or compile-time conditions. | source comment (unverified): // P3v2 supplies ordinary trees; local inverse contractions supply normalized · [reviewed contract](#b0009) |

## B0001

[Lines 1–10](../../../../../../include/crown/planner/meta_candidates.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:1b5005a335ccf37a8d3f390c03ff23ef21a32b363c81e1ddcc9c2207dc6fe551
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the optional cold candidate-mapping API together with the original-proof, finite-provider and ordinary-enumeration types it uses. |
| inputs / outputs | Including the guarded header imports the named planner types and standard scalar, optional and string-view declarations into a translation unit. |
| invariants | The namespace is crown::planner::meta. These includes and its opening do not construct metadata, prove a height or register a runtime update hook. |
| ownership | This scaffolding creates no live query, candidate owner or mutable global state; ownership starts in the declarations below. |
| failure | Incompatible or unavailable dependencies fail compilation. This region has no executable admission or runtime recovery path. |
| cost | Header parsing is a build cost. The directives and namespace opening perform no per-query search or per-update work. |
| Design | [docs/meta_candidate_adapter.md](../../../../../meta_candidate_adapter.md), [docs/meta_decompositions.md](../../../../../meta_decompositions.md), [include/crown/planner/meta_join_trees.hpp](../../../../../../include/crown/planner/meta_join_trees.hpp), [include/crown/planner/candidates.hpp](../../../../../../include/crown/planner/candidates.hpp) |

## B0002

[Lines 11–14](../../../../../../include/crown/planner/meta_candidates.hpp#L11); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L11-L14:sha256:f2f8f5140a99982ec242391cd3c7ccaee17667c3c7dbf3c6b36759e050decea2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set independent finite grants for inverse-fiber mapping after ordinary enumeration has already produced its input. |
| inputs / outputs | work, fragments and cells are uint64 grants; output_trees caps completed raw drafts and depth caps admitted logical recursive levels. Listed initializers are the defaults. |
| invariants | Zero is an actual zero grant. These caps apply only to their explicit mapping charge sites, independently of construction, ordinary enumeration and provider admission. |
| ownership | MetaMappingLimits owns only scalar configuration. A preparation call retains it by value while its private mapper borrows it synchronously. |
| failure | Denied charges become the matching MappingStop before the prohibited operation. Allocator and input-admission failures are separate propagating exceptions. |
| cost | Fixed-size configuration copy. The grants do not bound total CPU, heap bytes, vector capacity, string formatting, cleanup or the downstream provider. |
| Design | [docs/meta_candidate_adapter.md](../../../../../meta_candidate_adapter.md) |

## B0003

[Lines 15–18](../../../../../../include/crown/planner/meta_candidates.hpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L18:sha256:b5b9feaf640792810d9be1c26a3c8eafc65a835b9a436012cccfe5387a461c78
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe selected charges consumed by this mapping pass and the number of completed raw drafts actually retained. |
| inputs / outputs | work, fragments and cells begin at zero and accumulate; output_trees tracks output.size after successful draft append; peak_depth records the largest admitted logical depth. |
| invariants | Under an unedited result each counter remains within its corresponding grant. Fragments and explicit cells are cumulative, while peak_depth is a maximum rather than a frame count. |
| ownership | The usage value owns scalar diagnostics only; it retains no source tree, scratch family, query binding or allocator state. |
| failure | A caught mapping stop preserves earlier consumed usage and completed outputs. An uncaught OOM or admission failure does not promise a returned usage object. |
| cost | Reading/copying these fields is fixed-size. They are neither requested-memory bytes nor elapsed time, and output count precedes actual P02 admission. |
| Design | [docs/meta_candidate_adapter.md](../../../../../meta_candidate_adapter.md) |

## B0004

[Lines 19–22](../../../../../../include/crown/planner/meta_candidates.hpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L22:sha256:eb7470f2000a1da16ac16c6cf6da20313012065606d75e730a3ccb236c043415
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the initial mapping state, successful completion, independent ordinary-tree rejection and each explicit inverse-mapping grant stop. |
| inputs / outputs | MetaCandidateReport.mapping_stop contains one MappingStop and must be read alongside ordinary and provider completion diagnostics. |
| invariants | complete means all supplied ordinary fibers were processed; it alone means neither all ordinary trees were supplied nor the finite provider was exhausted. |
| ownership | MappingStop is an owning scalar enum with no allocated message or reference to private search scratch. |
| failure | Invalid input topology maps to invalid_join_tree; named grant stops preserve only already completed drafts. OOM and general admission exceptions are not encoded here. |
| cost | Inspecting the enum is fixed-size. Its declaration introduces no scanning, fallback search, runtime work or additional exception framework. |
| Design | [docs/meta_candidate_adapter.md](../../../../../meta_candidate_adapter.md) |

## B0005

[Lines 23–28](../../../../../../include/crown/planner/meta_candidates.hpp#L23); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L28:sha256:cbbfc3355484f8eb0652d336892bcfd8bbf39d38b6e94412c4f538bb5f44cfb3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep construction, ordinary enumeration, inverse mapping and checked candidate admission under separate caller-selected grants. |
| inputs / outputs | A MetaCandidateLimits value supplies existing construction Limits, EnumerationLimits, MetaMappingLimits and CandidateLimits to the corresponding stage. |
| invariants | Preparation defaults enumeration.all_roots to false: one physical-root-0 record per undirected ordinary tree suffices because the mapping enumerates all eligible first-native root sets. |
| ownership | The aggregate owns four configuration values; no stage shares a mutable grant ledger with another, and no cross-query planning owner is introduced. |
| failure | Stage limits retain their existing failure conventions. Changing a preparation grant requires a fresh call; provider limits can be raised later through its existing API. |
| cost | Copying the aggregate is scalar/configuration work. Canonical mode avoids materializing and then discarding n ordinary orientations; all_roots=true remains an explicit inspection option. |
| Design | [docs/meta_candidate_adapter.md](../../../../../meta_candidate_adapter.md), [docs/meta_decompositions.md](../../../../../meta_decompositions.md), [include/crown/planner/meta_join_trees.hpp](../../../../../../include/crown/planner/meta_join_trees.hpp), [include/crown/planner/candidates.hpp](../../../../../../include/crown/planner/candidates.hpp), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm2), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm5) |

## B0006

[Lines 29–31](../../../../../../include/crown/planner/meta_candidates.hpp#L29); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L31:sha256:dc080139b6168f5f839ca6ab7d6ae7a63f99f842faef89686ab9a17e41d3769a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the report authority boundary before the report fields are declared. |
| inputs / outputs | These comments tell callers to distinguish ordinary coverage, returned-fiber coverage and later P02/height/key admission. |
| invariants | A diagnostic report is neither a verified original optimum nor a checked upper capability. A complete preparation can still have no admitted candidate yet. |
| ownership | Comments establish no owner or retention requirement; report ownership and provider ownership are defined by the following aggregates. |
| failure | No executable failure handling occurs here. Treating diagnostics as proof would violate the documented caller contract. |
| cost | Comments have no execution cost; separate preparation and admission costs remain real and must be reported independently. |
| Design | [docs/meta_candidate_adapter.md](../../../../../meta_candidate_adapter.md), [include/crown/planner/candidates.hpp](../../../../../../include/crown/planner/candidates.hpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2) |

## B0007

[Lines 32–51](../../../../../../include/crown/planner/meta_candidates.hpp#L32); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L32-L51:sha256:39840daad7151c0e1f99085059d0e6dab6669ab60622a45c34587ed9bd78553d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return separate construction, checked-enumeration and mapping diagnostics together with the precise family and cost scope. |
| inputs / outputs | Status/usage fields come from their stages; rooted_ordinary_trees counts actual records, undirected_trees counts mapped root-0 records, and root/partition counters describe attempted local search. |
| invariants | ordinary_exhausted requires EnumerationStop::complete in its requested mode. all_ordinary_roots_materialized records that mode even on a stop, so true does not itself assert completed all-root materialization. mapped_input_fibers_exhausted concerns returned input only. Scope excludes unary generalized shapes and global maintenance-cost optimality; heuristic_used=false describes exhaustive capped search. |
| ownership | The public mutable aggregate owns scalar reports and static string views. Editing it creates no proof or admission authority and may invalidate downstream completion diagnostics. |
| failure | Default status values do not attest successful work. Construction/enum/mapping stops remain independent; OOM/admission can propagate rather than produce a report. |
| cost | Fixed-size report fields add no runtime hook. Search work can be exponential despite finite caps; counters do not assert paper delay bounds or total CPU/heap limits. |
| Design | [docs/meta_candidate_adapter.md](../../../../../meta_candidate_adapter.md), [docs/meta_decompositions.md](../../../../../meta_decompositions.md), [include/crown/planner/meta_join_trees.hpp](../../../../../../include/crown/planner/meta_join_trees.hpp), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm2), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm5), [exact paper reference](https://arxiv.org/pdf/2301.04003v2) |

## B0008

[Lines 52–62](../../../../../../include/crown/planner/meta_candidates.hpp#L52); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L52-L62:sha256:cc17df6faa7f12adc751be25d8b68caa1ed3c9ff17e1b02554fd95eb84c41c45
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the preparation diagnostics and optional finite provider, and compute a fresh combined exhaustion diagnostic from their current state. |
| inputs / outputs | normalized_minimum_family_exhausted returns the conjunction of ordinary exhaustion, all returned-fiber exhaustion, provider presence and that provider's actual family_exhausted progress. |
| invariants | The diagnostic assumes the originally returned report/provider pair has not been replaced or edited. Preparation alone is insufficient; moving the provider out leaves no present provider to attest progress. It is not a checked capability. |
| ownership | The aggregate owns its report and move-only optional provider. The method borrows them without exporting or copying candidates; the provider owns its independent binding and continuation. |
| failure | The noexcept method returns false for absent, moved-out or unexhausted provider state; there is no allocation or exception recovery in this predicate. Replaced public members can make its semantic claim invalid. |
| cost | Scalar short-circuit checks plus the existing noexcept progress getter; no mapping search, admission, provider advancement or per-update work is performed. |
| Design | [docs/meta_candidate_adapter.md](../../../../../meta_candidate_adapter.md), [include/crown/planner/candidates.hpp](../../../../../../include/crown/planner/candidates.hpp) |

## B0009

[Lines 63–83](../../../../../../include/crown/planner/meta_candidates.hpp#L63); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L63-L83:sha256:f66470c0d6a22f823e336b314fe0da1fd23d37251fb852bf5eb346011c7289a8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the original-proof-bound preparation entry point and document normalized coverage, head admission, ownership, limits and cost boundaries. |
| inputs / outputs | prepare_meta_candidates takes an owning VerifiedOptimum and optional stage limits, returning diagnostics plus a finite proposal provider when construction permits. Callers then explicitly advance that provider. |
| invariants | P3 Algorithms 2/5 supply ordinary trees; the inverse-fiber proof is local. Generalized scopes are first-native intersections, never copied paper minors. P1 Definition 3.2/P02 establish head, Guard, Connect and Above validity; the provider separately compares measured height with the supplied independently proved original minimum. No witness/residual seed or unconstrained normal-form fallback is added; unary generalized shapes remain outside the mapped family. |
| ownership | The call consumes the proof handle and transfers owned completed drafts into the returned provider. Preparation borrows only during the call; returned state has no borrowed query/scratch lifetime. |
| failure | Mapping resource stops return completed raw drafts and honest partial diagnostics. Preparation is nonresumable; use a fresh call for larger upstream limits. Existing input-admission/OOM errors propagate, and returned provider admission has its own stop/resume contract. |
| cost | Cold bounded preparation plus independent lazy provider work. Work checkpoints, cumulative fragments/cells and pre-push depth caps exclude capacity, allocator bytes, strings, input admission, relocation and destruction; no total-CPU, global-cost or per-update-overhead theorem is claimed. |
| Design | [docs/meta_candidate_adapter.md](../../../../../meta_candidate_adapter.md), [docs/meta_decompositions.md](../../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/pdf/2301.04003v2), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm2), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm5), [src/planner/verify.cpp](../../../../../../src/planner/verify.cpp), [include/crown/planner/candidates.hpp](../../../../../../include/crown/planner/candidates.hpp) |
