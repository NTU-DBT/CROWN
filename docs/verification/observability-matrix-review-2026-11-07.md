# O07 independent matrix evidence review — 2026-11-07

Disposition: **static auditor ready; final matrix acceptance pending**. This review and its helper perform source/metadata/hash/raw-log inspection only. They do not configure, build, execute native binaries or Python acceptance checkers, invoke CTest/nm, or poll root jobs. No native, historical, or frozen proposal input was edited.

The isolated helper is `/tmp/crown-observability-matrix-audit.py`, SHA-256 `6cde7a41b911e24403406bee3ada8bd940816251783133b22319323cb8299241`. It is adapted from the preserved P07 auditor, without importing or modifying that auditor or executing its `nm` subprocesses. Default outputs are `build/verification/observability-matrix-evidence-audit.json` and `.log`; `--output` can select a separate metadata dry-run destination. The root can invoke it after terminal evidence is available. Missing terminal summaries remain pending; focused results and initial builds never substitute for a final configuration.

## Frozen inputs and current evidence

The initial independent metadata dry run at `/tmp/observability-matrix-dry-audit.json` returned `preliminary_pending_matrix`, `accepted=false`, and zero errors. Release is audited pass: configure/build/test exits are zero, all 99 exact test names occur once in both verbose result lines and LastTest records, and all required new acceptance markers are present. Debug, Sanitize, Clang, and clean-source terminal summaries were absent at that dry run and remain explicitly pending in this review. Subsequent completed results must come from the helper's fixed final paths, not from this snapshot of progress.

The helper independently recomputes aggregate and per-file inventories against `build/verification/observability-execution-freeze.json`:

- Native: 585 files, SHA-256 `9ca9005001bda9e56faa0951077e53fc106450d7350bf185cd62556a7af25d0a`.
- Execution: 635 files, SHA-256 `8ae45108daed5530d67372c93b46bb198bf694a5c8bf429cb6905d4b367bbf12`.
- Nine historical manifest **files** retain their recorded hashes. Their old entry checksums are deliberately not applied to the changed native tree.

Each final runner must report the same frozen inputs before/after, source stability, zero exit status, and all three designated stages. Distinct configurations use distinct build/log destinations. Individual names/ordinals and duplicate detection prevent an aggregate count from concealing omitted or repeated tests. This is not a claim that concurrently authorized configuration jobs ran sequentially.

## Corrected inventories and unchanged gates

Raw Release LastTest output has **178 selected numeric/yes-no rows**, using the preserved P07 selector. There are 165 old row positions and 13 new O07 rows: one depth fixture, one query report count, ten composed allocation sweeps, and one composed report count. All 152 unchanged historical rows must remain byte-identical. Exactly thirteen identified allocation rows have fixed old/new mappings: two batch/session admission rows, ten initialization/rebuild rows, and one session admission summary. These changes reflect added runtime/session observation-context ownership (`src/runtime/observation.cpp:136`, `src/runtime/session.cpp:85`, `src/runtime/session.cpp:108`); the unchanged tests still enumerate every persistent allocation-failure position. All work, cost, budget, semantic and output rows retain exact equality. The mapping does not permit arbitrary numeric changes. Every completed configuration must reproduce the same per-test ordered rows, including clean-source.

The raw CMake compilation database has **157 entries**. The pinned libpg_query Makefile selects 92 wildcard C files and four explicit vendor/protobuf C files, hence **96 parser C units**, giving 253 total project-plus-parser translation units. The earlier 27-parser/184-compiler estimate was incorrect and is not a gate. The helper derives the parser file set from the pinned archive and checks the fresh clean log's exact distinct compilation-label set. Upstream Makefile lines 191–193 hide expanded compiler argv with `@`; compilation labels are not presented as raw compiler commands.

Project compilation must carry all six strict warning flags and no `-Wno-*`, plus ASan/UBSan and frame pointers in Sanitize. Clang compilation must actually select Clang; parser compiler configuration must select the corresponding C compiler. Vendored C retains its pinned upstream `-Wall` and three `-Wno-unused-*` flags; it is not falsely described as using the project's six-flag `-Werror` policy. Sanitizer parser evidence separately requires both `__asan_` and `__ubsan_` undefined references from the retained archive dump. Project C++ warnings and all unexpected diagnostics are rejected. The clean-source exception is limited to the exact three historical diagnostics described below.

The native query corpus still executes all 437 inputs under both policies with real replay/oracle checks. Its exported family counts are 872 search and 872 replay because the raw-byte anchor deliberately rejects strict JSON export. Native CLI acceptance has 2,749 checks and 175 calls; preparation had 2,750 because it additionally supplied the optional binary-SHA assertion. No gate was removed to reconcile those counts.

## ABI, symbols and clean retention

Both Runtime variants must compile the identical nine-source set, and both report variants their identical four-source set, with `CROWN_RUNTIME_TESTING` only on the testing side. Link metadata rejects mixed Runtime variants, requires the five owner/report tests to use testing Runtime, keeps query acceptance independent of Runtime, and requires the CLI to use production Runtime. Excluded overlay include paths are rejected.

Retained Release and Sanitize symbol records were independently checked against archive/dump/stderr hashes and successful stable capture. Production has no private baseline, RuntimeTestProbe, or observation test-hook definitions. Planner testing has exactly one private baseline; Runtime testing has eleven legacy probes and exactly one definition of each of the two observation hooks. The auditor reads these dumps; only root's separate collector invokes `nm`.

The unchanged clean helper (`tools/verify_clean_build.py:198`) would normally omit verbose successful output and delete LastTest during cleanup. Root's separately hashed runtime adapter addresses that evidence gap without modifying the helper: it adds only verbosity, retains compile/cache/CTest/flags/link/Makefile/LastTest metadata and symbol dumps, and then allows original cleanup. The auditor checks adapter/helper identity, the exact original/executed command relation, copied snapshot fingerprints, every retained artifact hash, terminal status and removal. Clean archives no longer exist after cleanup, so their identity is supported by the collector's recorded stable before/after hashes and retained dump hashes; no post-deletion archive rehash is claimed.

Remaining gates: all five terminal matrices, complete raw clean retention and 96 parser labels, identical 178 rows across configurations, final helper acceptance, ordinary source seal and ledger reconciliation. This static review does not establish those unfinished gates or mark O07 verified.

## Narrow clean-warning policy correction

The first final-path audit failed only because its clean-log warning check treated every vendor/build-tool warning as a new project warning. That failed JSON/log is preserved unchanged at `build/verification/observability-matrix-audit-before-vendor-warning-policy.{json,log}`. The updated helper compares the exact diagnostic-line multiset, including counts, with both fixed literals and the preserved P07 clean log:

- `gmake[3]: warning: jobserver unavailable: using -j1.  Add '+' to parent make rule.`
- `vendor/upb/upb.c:8245:8: warning: ‘sv.data’ may be used uninitialized [-Wmaybe-uninitialized]`
- `vendor/upb/upb.c:9206:6: warning: ‘sv.size’ may be used uninitialized [-Wmaybe-uninitialized]`

These are pre-existing limitations, not asserted safe, fixed, or false positives. The parser archive must remain SHA-256 `2d3486cf6a9d3955b53e66235db39d62b54216c820cd392ab66dc842c5b1316d`, the current recipe/lock must enforce that pin, and the retained clean Makefile must exactly equal the archive's Makefile. Every project warning or additional/changed diagnostic remains a failure. No test, parser-unit, export, sanitizer, source-freeze or 99-case gate is removed.

The corrected metadata-only dry run at `/tmp/observability-matrix-vendor-policy-dry-audit.json` has zero errors: Release, Clang and clean-source are audited pass; Debug and Sanitize terminal summaries remain pending. Clean evidence includes all 99 cases, all 178 structured rows, the exact 96 parser compilation labels, retained metadata and export checks, source stability and removed temporary tree. Final matrix acceptance is still pending; no tests or builds were rerun for this correction.
