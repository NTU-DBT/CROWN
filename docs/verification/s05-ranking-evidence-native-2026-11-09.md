# S05 native runtime ranking evidence checkpoint — 9 November 2026

This is incremental S05 work. S05, the whole-query memory budget, full native
acceptance and the full78-card goal remain open. Root implements the changes;
the existing Luna Max agent supplied a read-only caller/owner census. No Astra
is used. The ledger remains41 verified/3 in progress/34 not started.

## Implementation and boundaries

Actual runtime ranking capture uses the admitted program's original account for
both comparison bindings, retained binding/weight/source/observation arrays,
Evidence object/shared control (capture:9), RuntimeEvidence object/shared control
(capture:10), census seen/root scratch and source-table bitmap scratch. Native
binding formats decimal values into fixed storage and preserves frozen v2 bytes
and logical work/key/payload charging. There is no ordinary evidence/string
mirror in this capture path. The public Evidence array interfaces use
EvidenceVector with OwnerAllocator; shared handle copies allocate nothing.

Generated source selections occupy a fixed256-element array. A synchronous
OwnerRequestView borrows that array while the existing exact C01 builder copies
native captured facts. Existing owning OwnerRequest overloads delegate to view
methods, with no `{}` overload ambiguity and no retained borrowed span. Physical,
delta and session capture use the same native path. Collector-off and source-off
behavior, pending/stopped/dropped visibility, resource stops and owner freshness
remain intact. A denial returns allocation_failure without partial evidence.

Ranking scores/results, score text, lowering scratch and runtime/planner
selection graphs remain open. Caller immutable proof/family/compiler/cache
inputs are explicit boundaries; this checkpoint does not reclassify newly
created score or selected-plan storage as supplied input. Authentic operator
record/byte reconciliation and remaining diagnostic/work audits also remain open.

## Focused checks

Production source1 passes8 existing focused ranking binding/contract/census/
public-independent, selection binding/current and owner/report memory tests.
Only one existing test type assertion changes from std::vector<InputWeight> to
EvidenceVector<InputWeight>; its exact substitution is independently recorded.
All other original assertions, reference encoders, schemas and verifiers stay
unchanged. No warnings, flags, timeouts or assertions are weakened.

Source3 adds/registers ranking_evidence_memory: PASS1/1 in0.47s, both backends.
It measures the actual capture path outside caller proof/setup work, reconciles
every upstream allocation with the original account, sums retained attributions
0..10 and verifies all binding/array allocator identities (including empty
arrays). Ready enabled/source captures retain exactly five capture:9 blocks and
one capture:10 block. Tests cover physical/delta/session owners; all four session
phases; source/collection option combinations; shared copies; owner closure;
controller-only final release; every persistent allocation position; real caps
after hoarding distinct captures; and retry after release at the unchanged cap.

| Debug fixture | Reference faults / peak bytes / pins | Indexed faults / peak bytes / pins |
| --- | --- | --- |
| Physical |26 /497138 /1|28 /505390 /1|
| Delta |26 /499063 /1|28 /507315 /1|
| Ready session |27 /517439 /1|29 /525691 /1|
| Pending session |28 /632221 /1|28 /640958 /1|
| Stopped session |27 /516976 /1|29 /525228 /1|
| Dropped session |16 /271436 /28|16 /286834 /30|

These are fixture/build values, not universal bounds. Optional-fact delta cases
cover20/22/16 reference and22/24/18 indexed fault positions. The native binding
checks compare actual DTO/native encoders with the independent frozen v2 encoder,
including all five scalars, long binary/NUL metadata, raw invalid UTF-8 in the DTO
encoder, constraints/statistics/hints and a38-digit decimal. Both encoders pass
8 persistent string-growth fault positions. Direct binding exact/one-under
query peak is6568 bytes; zero logical prefix room performs zero allocations.
Native catalog/query encoding remains valid after its caller source is destroyed.

The initial new test fixture passed invalid UTF-8 metadata into the compiler's
JSON plan identity. The corrected fixture keeps that direct raw-byte encoder
case and uses compiler-admissible UTF-8/NUL metadata for the lowered plan. This
changes only the new harness. A missing new-target registration build attempt
is also retained. Production source1 is unchanged through source3. Raw failures,
candidate source and all source maps are preserved.

## Broader validation and evidence

Tested source3 freezes955 paths. Production source1 is unchanged; source3 fixes
only the new fixture. Final source4 changes documentation only (956 paths).

| Configuration | Scope | Passed / failed | Seconds |
| --- | --- | --- | --- |
| GCC Debug |All registered tests|218 /0|914.60|
| GCC Release |Selected related cases|105 /0|100.57|
| Clang18 |Selected related cases|105 /0|583.38|
| ASan+UBSan/leaks |Selected related cases|105 /0|3408.06|

The105 selected cases span97 actual native targets in each mode. The selection
extends the previous81-case capture/report/input scope with ranking/selection
cases, excluding the unchanged independent integer-arithmetic matrix outside
Debug. It includes the original exhaustive normalized ranking and selection
failure sweeps. All seven accepted builds have zero compiler diagnostics. No
test timeout, warning, flag, assertion, frozen verifier or schema is weakened.
All19 recorded jobs are closed. Complete detailed stdout is saved without
registration overlap. Final source/receipt/executable readback is recorded by
the checkpoint seal and independent post-seal audit. Full fresh-source acceptance
remains a separate open gate.

The unchanged normalized ranking sanitizer sweep passed in3408.05s under its
existing3600s limit. A partitioned-retry helper was prepared and syntax-checked
but never executed. An attempted read-only progress probe was denied by process
inspection restrictions; its receipt is preserved and no security setting or
test state changed. These supplemental tools supply no acceptance evidence.

Raw inputs/jobs/logs/stdout, test adaptation audit, preimages and immutable helper
versions are in `build/verification/s05-ranking-evidence-native-*`. Live job
authority is jobs-v1, not historical progress snapshots. Detailed CTest stdout
must be saved before another CTest run or enumeration in that build directory.
The [handoff](../handoff.md) identifies current work and the next ownership group.
