# Human inspection continuation: Boolean and native primitives

This pass integrates two bounded reviewers using the current model and root's
physical transaction review after the [W03 checkpoint](w03-projected-bags-2026-11-11.md).
The full implementation and repository-wide per-block semantic review remain
active. Both reviewers worked read-only and ran no builds or tests; root owns
integration and the executed validation below. No additional Astra run was used.

## Direct code and failure boundaries

Four redundant mechanisms are removed:

- Boolean and physical category overflow guards after cumulative charging.
  Each managed category starts at zero and is a subset of charged work, so
  successful charging proves both additions fit.
- A null check on the address of a successful `next_entry()` tuple. Real nullable
  lookup checks remain; selected cursor tuples are borrowed under their lease.
- A physical preparation rollback/rethrow catch. Its sole caller holds fully
  constructed Data in an accounted unique owner. On failure that owner runs
  the rollback destructor before the existing public diagnostic translation.

Resumed stage/route cleanup stays explicit because callers retain those tokens.
Allocation-factory cleanup and native/public error presentation retain distinct
ownership and diagnostic obligations. The [error dispositions](../code_specs/error_handling.md)
and [usage cards](../code_specs/primitives.md) state those boundaries.

No runtime owner, allocation, registry, framework or instrumentation is added.
The source-edit audit proves that the nine changed native files contain only
the four intended removals plus comments. Seven native files change comments
alone. A tenth maintained code input is the offline source-map generator.

## Comments and usage specifications

The Boolean reviewer supplied 102 cards, the native reviewer 68 and root 15.
There are now 317 authored seven-field contracts across 305 mapped blocks. The
structural map covers 664 maintained files, 152,263 lines and 16,815 blocks.
Other blocks remain labeled as structural facts; this is not semantic coverage
of every repository line or retained comment.

Fourteen staged comment/documentation edits correct stale account scope,
deep-plan-copy and cursor-lookup wording, clarify output ordering and borrowed
accessor lifetimes, and expose actual diagnostic/fan-out costs. Root also
documents the unique preparation owner and corrects historical test-count and
memory-accounting wording in the physical guide. Comment edits preserve
executable tokens; the intended guard/catch removals are audited separately.

Important cost boundaries are explicit:

- Boolean child updates materialize O(matches) accounted bucket handles, while
  result cursors use lazy native entries. Full child-flag copies and separately
  funded Boolean inverse images retain their existing costs.
- Allocating hash diagnostics cost O(capacity + n log n) with ordinary temporary
  pointer sets. The nonallocating diagnostic can instead cost O(capacity + n²)
  under collisions. Neither is a hot-probe bound.
- Arena memory reports scan the account ledger and slot high-water storage.
  Direct allocation-header classification and containing-pointer ledger scans
  have different costs.
- Public/native tuple construction currently validates twice. Public field-index
  diagnostics and invalid-layout ordering differ from native presentation, so
  removing a validation pass remains a separate measured optimization candidate.

Corrected P1 v2 §4.2 Algorithms 2–4 and §5.1 Algorithm 5 supply support/enumeration
context. Native allocator framing, rollback, overlays, reader lifetimes and
public costs are local engineering contracts linked from each appropriate card.
No paper theorem is used to certify the native extensions automatically.

The generator now locates a unique authored anchor in the actual source and
attaches it to that line's block. It rejects ambiguous/missing anchors instead
of guessing between class forward declarations or matching an incomplete
signature. Two older anchors were qualified to identify their definitions.
All 317 real anchors resolve once; eight focused fixtures cover class forwards,
inline/multiline bodies, formatting, ambiguity, missing and empty anchors.

## Executed validation

| Configuration | Selected linked checks | Elapsed |
| --- | ---: | ---: |
| Fresh GCC Debug | 18 passed | 13.99 s |
| Fresh ASan + UBSan with leak detection | 18 passed | 46.29 s |

The checks cover physical source/projection collisions and alias rollback,
prepared epochs, Boolean support models/journals, current/view/fragment/witness
cursors, allocation failures, owner/reader lifetimes and indexed storage grants.
Each configuration exercises 1,011 reported update-allocation failure points
and 41 basic result-cursor failure points, plus the view/witness factory and
resumed-output failure sweeps. Timings describe this verification run, not a
comparative performance result.

Four additional actual objects compile support.cpp/physical.cpp under strict
optimized GCC and Clang flags. These are compilation controls, not linked
Release test runs. Both linked builds retain warnings as errors. Final receipts
have stable current inputs. Preparatory dependency receipts that recorded
concurrent support edits and the first rejected documentation map remain
separate exploratory evidence.

The checker passes current hashes, complete line partitions and 25,408 local
links. Ten malformed checker controls are rejected, in addition to the eight
anchor fixtures. All 314 test commands/properties remain unchanged against each
matching W03 build profile; sanitizer environment properties are compared with
the sanitizer baseline. CMake/install declarations are unchanged. This packet
does not claim a full 314-test run.

All 2,443 predecessor source paths have preserved before-images. W03's frozen
source/build/evidence remains intact. Acceptance, source-edit/anchor controls,
native artifacts and raw logs are in build/verification/inspection-v2-*. The
acceptance record is inspection-v2-acceptance-v1.json and the progress/source
closure is inspection-v2-progress-v1.json. See [handoff.md](../handoff.md) for
remaining scopes and the full active goal.
