# C02 baseline ranking: excluded preflight

Date: 2026-11-07. Status: **design preparation only; C02 remains `not_started`**.

This packet defines a proposed C02 implementation against the pinned P07 and
newly integrated C01 native APIs. It contains no implementation overlay and
registers no native source, test, report, or command. At assignment, the C01
131-test, five-configuration matrix was running against frozen native sources.
This packet makes no claim about that matrix's eventual result.

The proposed policies rank only factory-produced P07 candidates at their
original query's verified minimum native height:

| Policy | Secondary ordering after required height | Evidence |
| --- | --- | --- |
| `height_only_v1` | None; full structural key breaks ties | P07 typed snapshot/proof |
| `committed_input_native_depth_v1` | Exact integer weighted native-depth numerator | Current physical table/operation input census |
| `tuple_index_slots_v1` | Candidate-local tuple/index-slot upper-bound proxy | Exact physical source cardinalities and each candidate's own lowered layouts |

All policy names in this packet are proposed ranking names, not accepted P07
`CandidateContext` values. P07 still accepts `cost_model = "no-cost-v1"` and
`optimization = "structural-height-v1"` only. Costs and observations confer no
structural, certificate, cache-import, or deployment authority.

Read [CONTRACT.md](CONTRACT.md) for admission, arithmetic, freshness, fallback,
and timeout rules; [ARITHMETIC.md](ARITHMETIC.md) for the exact portable 512-bit
backend and admitted-domain bounds; [WORKED_EXAMPLES.md](WORKED_EXAMPLES.md) for independently
checkable score calculations; [SOURCE_MAP.md](SOURCE_MAP.md) for existing APIs
and required integration seams; and
[INTEGRATION_TEST_PLAN.md](INTEGRATION_TEST_PLAN.md) for implementation stages
and meaningful independent tests.

The principal design choices are:

- Count committed physical insert and erase events, including no-op commits.
  Count each affected alias's native depth, but count a physical event once in
  the shared denominator. Failed attempts do not enter the weight census.
- Use the current workload segment only. Never add previous segments, scale a
  sampled detail population into physical inputs, or infer arrival Hz.
- Keep missing, stale, degraded, and saturated data explicit. Default requested
  statistical policies fail without a score if their required facts are
  unavailable. An explicit `height_only` fallback scores the whole snapshot
  under that policy and records the reason.
- Promote exact native counts into bounded wide nonnegative integers before
  arithmetic. A 512-bit default covers the current admitted score domains;
  explicit bit/work-cap exhaustion is a resource stop, not missing statistics
  or a reason to change policies. No wrapping, saturation, floating-point
  ordering, or silent rescaling.
- Evaluate all retained candidates or publish no ranking. A complete ranking
  of a partial provider snapshot remains a best-among-retained result.
- Derive the memory proxy from source counts and the candidate's own structure.
  Its units are abstract tuple/index slots, not bytes, time, allocator totals,
  or a memory-budget guarantee.

Source inspection found two integration traps that the design addresses:
P07's full binding encoder is private to `candidates.cpp`, and catalog statistics
are themselves part of that certificate/cache binding. A later implementation
must share the exact binding comparison without replacing catalog metadata with
fresh observations. Neither a semantic digest nor alpha-equivalence suffices.

`INPUT_SHA256SUMS` pins the repository files used for this design. `input-paths.txt`
lists those files. `PACKAGE_SHA256SUMS` seals every packet file except itself.
`STATIC_CHECKS.md` records the checks and explicit limits. No binary, Python
checker, CMake, CTest, benchmark, or `nm` was executed; no direct compile was
needed for a design-only packet. Native code, frozen C01 packages, ledger,
handoff, and matrix helpers were not edited.
