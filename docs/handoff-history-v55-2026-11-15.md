# CROWN continuation handoff — V55

Goal active. Ledger: 61 verified / 2 in_progress (A02/C04) /15 not_started =78.
This is implementation progress, not completion of the original Refactor goal.
[V54 history](handoff-history-v54-2026-11-15.md) preserves the exact prior handoff.

Current seal: `build/verification/human-inspection-v55-progress-v1.json`.
Frozen source: `build/verification/human-inspection-v55-source-v1`.
Postcheck: `build/verification/human-inspection-v55-postseal-check-v1.json`.
Packet: `build/verification/meta-candidate-adapter-v55-v1`.
Parent V54 seal SHA256:
`9c35258ee78afcbe9d6f10c47fb1206a14af13c54d40e638cfc2464d5a153484`.

The [review continuation](verification/meta-adapter-review-v55-2026-11-15.md)
receives all 366 production /419 primary paths with zero unread primary paths.
All 45 affected checks are validated in Debug and ASan/UBSan/leak profiles across
preserved initial/corrective runs; no new358-test full-suite claim. Three current
build refreshes pass (zero C++ compilations). Each profile passes 7,750 GYO
comparisons and real finite-proposal/cache/report regressions. The schema-only
correction leaves production C++ unchanged. Native failures and their repairs
remain explicit in the packet. Final source/block/link checks are separate.

C04 now has [meta construction/checking](meta_decompositions.md) and an owning
[finite proposal admission bridge](candidate_alternatives.md#supplied-finite-proposals).
The code preserves occurrence/special identities, independent original proof,
P02/height/key gates and truthful finite-family provenance. Review fixed checker
domain, cyclic super-bag, early disconnected root and nested grouping failures.
No runtime update hook, retained row/index graph or runtime error layer is added.
Selected cold planning counters do not promise allocator bytes or total CPU.

C04 is NOT complete. Next required work: implement bounded meta join-tree
enumeration, compare small ordinary-tree families independently, implement
CROWN/head/generalized mapping with original-binding P02 checks, and integrate
selection. Never substitute ordinary-tree optimality for generalized minimum
height. P3's cardinality objective is not CROWN maintenance cost. Keep the old
normal-form route as the independently complete minimum-height route.

The exact P3v2 PDF/HTML are pinned. Read the sealed primary review and its
successor independent meta review before enumeration. The initial construction
pseudocode missed fixed-point grouping; current source/cards explain the repair.
Appendix enumeration needs corrected child composition and typed external-parent
placeholders; disconnected empty roots need explicit handling. Full family
coverage, local exhaustive/heuristic status and head constraints remain required.
Do not narrow C04 to one proposal or metadata-only acceptance.

All 16,947 nonblank blocks across 776 files /177,669 lines /19,879 blocks have
19,382 authored contracts. V55 adds 98 cards, amends 37 and rebinds 45 CMake
references. Maps, independent structural receiving and links are checked;
contracts/finite tests are not exhaustive formal correctness proof.

Keep completed packets, frozen sources, private SDKs and dependency prefixes
immutable. .git is read-only; exec_command requires require_escalated. Use
PYTHONDONTWRITEBYTECODE=1. Mutable builds: build/w05-debug,
build/w05-sanitizer, build/inspection-build-scope-off-v1. Freeze native inputs
during recorded jobs and copied documentation during source/install jobs.

User scope persists: licenses deferred, rights/notices preserved; A02 does not
block C04/B01 technical work. Comparisons/top-k/difference may use ordinary change
propagation or exact recomputation. Approximation and shared-query algorithms
are deferred; preserve independent query state/results/progress/budgets behind
the interface. Parallel/distributed engine execution is deferred. Keep code direct
with explicit primitive costs. Use own model and parallel independent reviewers;
Astra Max sparingly, Luna Max for simple mechanical tasks. Continue the full goal.
