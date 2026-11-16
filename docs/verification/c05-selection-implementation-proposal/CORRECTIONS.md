# C05 staged correction history

All changes below are inside the new excluded implementation packet. No C02,
native, ledger, handoff or frozen design file is changed.

| Checkpoint/review | Finding | Correction and evidence boundary |
| --- | --- | --- |
| Historical GNU six-unit checkpoint 1 | All six then-current implementation units compiled under the six strict flags | Preserve its objects/logs as-of; later source changes mean it is not the current closure. No consumer ran. |
| Producer transaction inspection | Evicting with pop_front could destroy a last plan reference inside commit; normal native JSON cleanup can allocate a stack even though its persistent-OOM fallback is safe | Commit now splices evicted list nodes into Prepared.retired. Post-publication destruction handles cleanup; actual commit consists only of nonallocating list splices/scalar assignments. |
| Root strict checkpoint 2 | 18 of 19 TUs and 9 of 10 links succeeded. The binding fixture's DecimalSpec initializer comma was parsed as a second preprocessor argument | Parenthesize the expression; preserve the exact failed compiler/link logs and all old artifacts. No assertion or runtime oracle changed. |
| Producer first-Direct admission audit | SelectionData's DirectCQ options copy was precharged, but an additional known options copy inside native lower was only in post-lower compiled payload | Precharge its fixed PhysicalOptions object and four policy strings before lower. The later compiled walk remains conservative and unchanged. Public API and score semantics do not change. |
| Root dependency request | Initial recipes used -MMD, excluding system dependencies | New build-checkpoint-3.sh uses -MD and stronger missing-input checks; old recipe/output remain untouched. |
| Additional producer assertions before checkpoint 3 | Wide comparison and retained raw current-capture checks benefit from explicit coverage | Add literal integer strings above UINT64_MAX and compare the old current wrapper's full workload/owner stamp throughout failure sweeps. These do not fabricate public score or freshness authority. |
| Root strict checkpoint 3 | The same binding consumer reached optimized GCC13 nested-variant maybe-uninitialized diagnostics; eighteen other TUs and all three archives/nine links passed | Construct the nested string alternative in place and assign the same three bytes. Keep all flags and mutation assertions. Targeted checkpoint4 rebuilds only that consumer, guarded against every other changed input. |
| Producer normalized-fixture source inspection, after strict4 and smoke8 | Catalog name R was paired with unquoted SQL R, which PostgreSQL folds to r; exact catalog lookup would reject before the intended normalized path | Quote the SQL name as `FROM "R"`. Root authorized this single-source correction only after both input guards closed. Targeted checkpoint5 rebuilds that consumer alone with an explicit strict4/strict3 artifact chain; numeric expectations and all implementation/API/support bytes are unchanged. |
| Independent ordinary cache consumer and isolated root diagnostic | The fixture appended `-namespace` to the only supported native arithmetic value, then required a successful lower/cache insertion. Root's diagnostic confirmed the first rejected call was 33, physical-options field 0: lowering_failure at lowering, with no result; the previous 32 calls succeeded | No implementation change. The new sibling correction preserves the original failure/diagnostic and checks explicit unsupported-arithmetic rejection, unchanged cache and successful supported retry; all five supported option-namespace variants retain their positive distinct-key assertions. Root ordinary execution now passes all five independent consumers/22 groups; matching sanitizer execution remains separate. |

The stable API checkpoint lives under `checkpoints/api-1/`. It preserves its
copied interface/framing/accounting bytes and pins all current overlay sources
plus the next root recipe. This is a review checkpoint, not implementation
completion. Root still owns compilation, ordinary/sanitizer/fault execution and
any later native integration. Results and exact terminal pins will be reconciled
before the final proposal freeze; no unrun position totals are asserted here.
The later `api-2` and `normalized-1` checkpoints preserve their own exact input
generations. Historical manifests are not silently regenerated after a live
source entry changes. [Recorded outcomes](EVIDENCE.md) lists completed root
checks separately from authored assertions and staged builds.
