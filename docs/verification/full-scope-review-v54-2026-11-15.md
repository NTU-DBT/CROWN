# Full source review — V54, 15 November 2026

This review covers every maintained production file and the maintained build,
tool and example sources. It records actual source reads and invariant checks;
native execution and block documentation checks have separate receipts.

The current review has no unread primary source paths. The primary union is
417 files: 364 production files and 53 additional build/tool/example files.

| Assignment | Files | Inspection |
| --- | ---: | --- |
| Frontend, IR and planner | 89 | Full source plus public/private contract traces; the second packet closes all 51 initially bounded/header gaps |
| Runtime and observability | 82 | Full source; later statistics implementation/header successors received separately |
| Recovery and I/O | 113 | Full implementation or full public/private inline contract, plus recovery context |
| Storage | 58 | Full implementation and public/inline contracts |
| Resource, catalog, annotation policy and API | 13 | Full source and ownership/arithmetic/catalog reasoning |
| CLI | 9 | Included in the 62-file build/tool/example assignment |
| Other build, tools and examples | 53 | Full source; final CMake, five example mains and output regression reread after fixes |

All source reads have exact hashes and retained copies. The root received 14
source/fix packets, verified 1,768 payloads and joined their production paths
against the independent 364-file inventory. Supporting test/fixture/schema
inspection remains explicitly scoped in each packet; it is not described as a
fresh full read of every test file.

## Corrections

| Finding | Trigger and correction | Evidence |
| --- | --- | --- |
| Accounted index metadata | An index on field0 could be exported as field1 when widths matched. Capture now uses the actual index's source/target descriptors and ordered fields; conflicting metadata rejects before exact publication. Equal recreated tokens remain valid. | The new regression fails against the original implementation; both storage backends pass after correction, including exact/one-under work and byte grants and authentic incomplete metadata. |
| Clean source closure | The copier omitted the required aggregate install document, and the current plan depended on an incidental historical pin. Both install documents and current Refactor.md are explicit inputs. | Real copier, byte-preserving positive checks and a missing-document negative; actual copied-source configure/static gates. |
| Free-connex workload label | A cyclic full-head triangle was labeled free-connex because only H+F was checked. Both producers and verifiers now require body AND augmented acyclicity. | Six literal independent shape/label controls, counterfactual old predicates, full static workload/ranking checks. SQL, trace and oracle bytes stay identical. |
| Checker defaults | Standalone composed checker defaults pointed outside the repository and at a historical proposal. Defaults now follow the maintained script/repository/schema paths. | Actual checker from unrelated cwd, default/absolute/relative path modes, synthetic transport explicitly grants no native proof authority. |
| Historical plan provenance | A strict legacy manifest pinned a mutable current plan to old bytes. The exact pinned old plan now has an explicit historical archive path; only dependent active provenance hashes change. | Exact archived bytes equal the old frozen source and original checksum. Unstubbed legacy, workload, ranking and source-snapshot verifiers pass; immutable previous packets stay unchanged. |
| Example report failure | Buffered stdout errors could be missed, and reoptimization returned success unconditionally. Six final flush/state checks across five examples return failure after unsuccessful report delivery. | Real old collector fails the new /dev/full test; current executable regression covers short buffered reports and committed workflow/reoptimization restore/resume. |
| Report memory schema test scope | Whole-schema comparison rejected eight already accepted update-pattern/window additions before invoking the native fixture. Compare the two affected option objects exactly with the frozen objects plus their optional uint64 field. | Both actual native fixtures pass the proposed correction with 116 checks each; eight schema mutations reject. Frozen readiness hashes and legacy default compatibility remain checked. Final maintained-tool receipts are recorded separately. |
| Ranking verification wall budget | The full sanitizer runner exceeded its 1000-second limit around the complete controlled cohort. Existing invocation and CTest limits are now 1800/2400 seconds. | The full unchanged cohort passes in an isolated sanitizer rerun with persistent artifacts: 16 candidates, 240 preflights, 576 retained runs and 486 independent objective checks. Production code and per-command runner limits are unchanged. |
| Reference bucket description | The profile guide incorrectly suggested that a reference bucket scans unrelated records. It now states the maintained-index behavior and keeps separate storage/constraint costs explicit. | Direct source trace through AccountedReferenceTable bucket lookup and member cursor. |

## Validation and human inspection

All 356 registered checks are validated in Debug and ASan/UBSan/leak
configurations across the full suites and corrective reruns. The full Debug run
has 355 passes and the obsolete schema-comparison failure; the full sanitizer run
has 354 passes, that failure and the ranking wall-time limit. The corrected
maintained schema verifier and actual source-snapshot check pass on both builds;
the complete ranking integration passes alone under sanitizers with retained
artifacts. Production C++/headers are identical across these runs. The final
three build refreshes compile no C++ and change only test/checker metadata.

Each full profile also passes the 123-case/two-backend SQL aggregate Session
oracle: 3,952 compared snapshots, 3,706 atomic epochs, 14,824 durable reopens and
3,952 checkpoints. The planner fault test checks all 24,449 observed allocation
cuts per profile. The real five-example ENOSPC/recovery control passes, and the
qualified profile produces 17 inspectable examples per profile with allocation
denial at cut 0 on both storage backends.

The source review checks ownership, arithmetic bounds, admission/publication,
budget and failure boundaries. The complete native suites add independent SQL
oracles, fault/corruption/allocation controls, recovery and installed consumers.
The initial full-suite runs were deliberately interrupted for the confirmed
index metadata defect and are not counted as passes. Later runs preserve the
schema-checker failure and its separately verified correction.

Every nonblank mapped code block has an authored usage contract with input and
output, invariant, ownership, failure, cost and reference fields. Structural line
coverage, source hashes, attachment positions and local links are checked
separately. This makes the implementation inspectable; neither a generated map
nor a finite passing test matrix is an exhaustive formal correctness proof.

The [update-pattern profile](update-pattern-profile-v54-2026-11-15.md) adds only
fixed shared-owner accesses and a fixed physical-hash comparison. It adds no
per-update hook, new retained row/index graph, catch layer or engine execution
framework. The profile's amortized logical support-action bound excludes source
adaptation, storage, monitoring, allocation, retries, output and total CPU/delay.

The implementation goal remains active. License disposition, broader releases
and deferred research cards retain their [ledger](../task_ledger.md) status.
Existing rights, notices and frozen evidence are preserved.

The final block audit covers **772 files /176,389 lines /19,765 blocks** with **19,284 contracts** across all **16,849 nonblank blocks**. The 2,916 remaining regions are blank spacing. All 140,838 generated local links pass. Eighteen inherited numeric CMake references were rebound to their actual current test registrations, including the indexed-component loop and all three shared observability modes.
