# P05 residual candidate construction

Status: implemented and verified, 2026-11-07 (Asia/Shanghai). All 89 tests
pass in the five configurations below, with an explicitly audited
sanitizer-watchdog bridge. The complete 78-card goal remains active:
35 verified, two in progress (A02/O06), 41 not started. P07 remains not started.

## Implementation and authority

`ResidualSearch` owns frozen-ear reduction, identity-preserving dense query
views, independent trace replay, checked reconstruction and P06 exact repair.
See the [contract](../residual_candidates.md) and
[proof notes](../planner_proofs.md). Each round freezes eligibility and every
supporting anchor before deletion; mutual ears retain a representative.
Original occurrence/variable IDs, full terms/types/source metadata and
ordered/repeated head outputs survive explicit forward/inverse dense maps.
The replay worker independently rederives the trace from the original input.

Reconstruction tries native placements, generalized leaves and guarded
generalized grafts. Every draft passes independent P02 before use, and every
published upper passes final full-original-binding P02. This greedy candidate
family is not claimed complete. Failed extension starts owned exact prefix
repair; partial infeasibility transfers to full original search and is never
exported as original infeasibility. The default mode completes a separate
original-query P06 proof before publishing a minimum. Candidate mode may
finish with only a checked upper. Round counts and terminal residual minima
never provide an original lower bound.

Retained immutable trace/candidate/proof handles preserve binding and lifetime.
An original exact improvement publishes a new handle and leaves an older upper
unchanged. Origin names the last successful construction step; counters/trace
retain earlier graft and repair activity. Logical work/time/depth/content
stops retain actual positions. Residual content caps exclude admission copies,
delegated P02 validator scratch and delegated exact storage; capacity, scalar
widths, cleanup and retained history are explicit separate costs. They are not
allocator-capacity byte caps or hard CPU bounds; S05 remains separate.
Delegated logical counter exhaustion is terminal.

## Acceptance evidence

- All 225 three-atom/two-variable valid-head queries compare the trace to an
  independent direct-set reference and candidate/default modes to the unchanged
  literal P03 oracle. Every emitted candidate is checked against its original
  binding with P02.
- Mandatory seven-/nine-atom cases have one productive round, terminal height
  one and original minimum three. Wrong-anchor alternatives, generalized grafts,
  exact prefix repair, stalled/empty/nullary inputs, constants/ignored/repeated
  terms, source metadata/aliases, 70-variable/70-occurrence inputs, corruption,
  slicing, zero grants, resource raises, cancellation and owning handles pass.
- Twelve actual typed reports and twelve strict-schema mutations cover upper,
  trace, exact, infeasible and resource states, including CQ versions 1/2/3,
  date and decimal values. A candidate report remains upper-only; original
  certificate export requires a completed typed P06 proof.
- Independent Astra mathematical/source/API/proof review found no blocker.
  Project warnings remain errors; no warning or sanitizer check was suppressed.

Each matrix configuration completes the same five exhaustive observed-allocation
sweeps, without a position cap. Every position forces persistent failure,
retries twice at the pending operation and then continues the same owner to
its uninterrupted result/accounting:

| Fixture | Allocation positions |
| --- | ---: |
| Projected candidate mode | 423 |
| Projected exact-original mode | 952 |
| Five-atom candidate mode | 1,198 |
| Five-atom exact-original mode | 14,140 |
| Seven-atom exact repair | 7,742 |

A [supplemental Release probe](p05-supplemental-tests/duplicate-ear-replacement.cpp)
also passes all 15,908 allocation positions on A(x,y), B(x,y), C(x,y), D(y,z),
E(z), empty head. It replaces a checked height-three residual upper with a new
proved minimum-two upper while preserving the retained old handle. This is
additional Release evidence, not an extra CTest or sixth sweep in every matrix.
Raw output: `build/verification/residual-candidates-supplemental-replacement.log`.

## Five-configuration matrix

| Configuration | Tests | CTest seconds | Input revision |
| --- | --- | ---: | --- |
| GCC Debug | 89/89 | 1228.04 | A |
| GCC Release | 89/89 | 221.90 | A |
| Clang Debug | 89/89 | 1037.14 | A |
| Fresh source-only Release | 89/89 | 214.71 | A |
| ASan + UBSan + leak checking | 89/89 | 5186.86 | B |

All jobs are terminal and closed. The clean helper took 622.41 seconds
(622.52 including its wrapper), with configure/build/test stages
0.96/406.52/214.72 seconds. `/tmp/crown-clean-source-zzzhu4sl` is removed.
The focused Debug five-sweep target passed in 859.13 seconds before full Debug.
The final sanitizer semantic and exception targets pass in 621.44 and 3571.35
seconds, respectively, with normal teardown. All previous tests remain enabled.

Raw stage logs, verbose stdout and summaries use
`build/verification/residual-candidates-{configuration}-*`.
The independent matrix audit accepts the complete matrix, 162 identical
structured fixture rows (157 preserved plus five P05) and the bridge;
JSON/log: `build/verification/residual-candidates-matrix-evidence-audit.*`.

Revision A: 469 native inputs,
`69695cb7efc0a816fbce741cb311382521822d5d680f52a0c0dabf1068bc332a`;
509 complete execution inputs,
`653e1a127f2cf2c601f6c6726fafa1b550254f6244e57629aefe035daad4d518`.
Revision B: 469 native inputs,
`20d00cca9705dfe8a1f9e5775865963bcc3b09f3f41bfe17a4d9d39f79c6d3ca`;
509 execution inputs,
`c1a2d23edc5b605982b22db81ffbf706410e2d56614ad13af75d6aa9c4323d47`.
Every successful job preserves its own before/after fingerprints.

The [restricted watchdog bridge](p05-watchdog-bridge-2026-11-07.md) connects
four successful configurations at A and sanitizer at B. Only one conditional
CMake sanitizer test TIMEOUT changes, 3600 to 7200 seconds; the other 508
execution files, compiler commands, assertions, commands, environments and
memory settings remain unchanged. Generated non-sanitizer policy is unchanged.
Removed clean metadata was not compared; its unchanged helper leaves
sanitizers disabled, so the conditional is inactive there. The five full
input fingerprints are not claimed identical.

The first sanitizer attempt hit `***Timeout 3600.11 sec` during the final
sweep and did not complete normal teardown. Its unchanged failed/interrupted
evidence is archived under `residual-candidates-sanitize-attempt-1-watchdog/`.
Targeted fixture/grant/build attempts and the first full Release's 88/89
last-step-origin fixture failure remain separately archived and unaccepted.
No fault positions, assertions or memory checks were removed for the rerun.

## Source seal and continuation

The [563-input ordinary source manifest](residual-candidates-sources.sha256)
has SHA-256 `36be533d3eee783e6a0a75c46cd875e37dbf1f122d1cf43e322c7167398f0734`. Its inventory is the historical P06 546 plus
17 new files, without removals. Historical P06 and six earlier manifest file
bytes remain unchanged; they are snapshots, not current-source seals.
`Refactor.md` remains
`bb90e4a4e97e2817a0869ad86c5c8b00e571bb241f153fb44641c71f86fcd5ce`.
The independent Luna Max source/seal/documentation audit passes all 563
checksums, the exact inventory, preserved historical seals, ledger and proof
scope. It checks 108 Markdown documents, 821 local destinations and 61 schema
references without missing targets. Its JSON/log use
`build/verification/residual-candidates-source-seal-audit.*`.

P07's excluded API/generator/reference/key/facade/cache/report proposals and
their isolated checks are preparation only. They change no P05 native or
execution input and are not native P07 verification. Continue with P07
integration, then respect S04/S05's dependency/license chain and the remaining
runtime/recovery/optimizer/extension/experiment/release cards.
