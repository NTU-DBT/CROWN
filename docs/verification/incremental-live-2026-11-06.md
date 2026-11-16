# D05 live-maintenance component, 2026-11-06

Input: uncommitted `master` based on
`e369a623517723b3be3ea3e9806779f3c591e7f9`.
The live-maintenance component and indexed before-state access are implemented
and verified: all 59 tests pass the final five-configuration matrix, with an
independent source/proof review. **D05 remains in progress.**
The full 78-card goal remains active: 26 verified, six in progress and
46 not started. The [D04 packet](delta-runtime-2026-11-06.md) and its
473-input manifest describe the preceding verified snapshot.

Contracts: [live-maintenance argument](../incremental_live.md),
[delta owner](../delta_runtime.md), [epoch views](../epoch_views.md), and the
[D03 partition](../delta_transition_spec.md).
Sources: [delta.hpp](../../include/crown/runtime/delta.hpp),
[delta.cpp](../../src/runtime/delta.cpp), and
[support.cpp](../../src/runtime/support.cpp).

## Requirement audit

| Obligation | Current evidence and limit |
| --- | --- |
| Remove per-route full L rebuilds from the default | `on_output` projects each accepted core delta row top down and immediately adjusts child separator counts. It opens no child E bucket. Full rebuilds remain explicit bootstrap/invariant costs and the optional `eager` reference path. |
| Preserve unchanged E keys whose global liveness changes | Exact live-parent support counts implement the D03 recurrence. The row-coupled deletion certificate proves that later completions remove keys first seen while another parent still supported them. The `incremental` comparison path instead propagates support 0↔1 through matching E buckets. |
| Last-parent removal after earlier child visits | A four-level R(k)→P(k,a,x)→S(x,y)→T(y,z) fixture has two parents sharing x and two descendant choices per y. Deleting R emits eight exact answers, removes nine L keys and makes five parent-count updates; reinsertion restores all keys. Full invariant rebuilds check counts as well as L memberships. |
| Exact delta and alias-prefix behavior | Each of the three policies runs the same 2,712-event A04 corpus with 1,408 raw records and 2,504 exhaustive toggles. Raw cardinality, signed sets, stage intervals, source state, endpoint L projections and invariants are checked. Every non-eager event additionally checks exact L-mutation and degree-weighted separator/undo counters. |
| Avoid unrelated inverse-patch scans | Before-view construction indexes restored tuples by full key and every existing compiled separator index. A bucket with seven matching restored rows and 41 unrelated restored rows visits only the seven matches; misses visit zero. A fixed local key uses a direct restored-key lookup. |
| Atomic physical/L/output failure | Affected node handles and saved count values roll back before public readiness. Policy-selectable persistent allocation sweeps cover insertion, erasure, shared-separator 2→1→0 count undo and mode bootstrap. Spool/work failures, owning output and allocation-free final delivery remain covered. |
| Full intended D05 lazy-output contract | **Open.** Root-first completions can still inspect unrelated rows; canonical rank rejection bounds total candidate duplication but not every successful-output gap. Discovery, journal/index preparation and atomic full-epoch spooling also remain in first-public-output latency. |

The exhaustive finite scope is unchanged from D04: 64 transitions for
`Q(x):R(x,z)`, 384 for `Q(x):R(x),S(x,y)`, 2,048 for
`Q(x):R(x,z),S(z,y)`, and eight for Boolean unary R, over `{0,1}`. Manual
cases and two 72-event seeded alias traces complete the corpus. These tests
do not substitute for an arbitrary-query proof.

Persistent allocation-failure positions in final GCC Debug (each followed by
exact state/pin/L checks and a same-sequence retry):

| Live policy | Insert | Erase | Shared-separator erase | Bootstrap |
| --- | --- | --- | --- | --- |
| `on_output` (default) | 225 | 194 | 241 | 40 |
| `incremental` | 219 | 186 | 250 | 40 |
| `eager` | 291 | 251 | 237 | 40 |

Allocation failure remains armed during rollback. The shared-separator case
changes one count 2→1 and later extracts it at 1→0, exercising saved-value
address restoration after node reinsertion. Fault-position counts are
implementation/configuration evidence, not a public stable format.

## Proof and source review

The root implemented production live maintenance and integration. Luna Max
implemented restored-key indexes and their independent fixture, the original
bucket/eager fixtures, the shared-separator allocation sweep, and the expanded
three-policy fixtures. A separate fresh-context read-only Luna Max agent
reviewed the bucket argument and then the row-coupled insertion/deletion
argument against the actual implementation. The reviewer ran no builds/tests.

The deletion proof uses a fresh certificate on a connected ancestor path,
including a full key absent from E-after. A dead child's last removed matching
parent supplies such a certificate. Running intersection and downward totality
allow a before-completion containing that certificate and the child's key.
D03 completeness processes this deleted answer; freshness prevents it from
preceding the selected parent's removal. Its top-down visit therefore sees
zero child support and finishes that key's removal. This addresses repeated
early visits while other parents remain live, without assuming output order.

The reviewer found no remaining live-coupling correctness blocker under the
stated D03 assumptions. This disposition does not establish completion delay,
public startup, external G2/V02 review or release approval.

## Cost and retention

For one monotone route, let K be changed E keys, J actual L membership changes,
B bucket rows, U child-separator updates, D exact core delta rows and m factors.
Each factor has at most D changed L keys, hence J≤mD and
U=Σ degree(i)J_i≤(m−1)D for a nonempty tree. The bucket path has B≤J and
O(K+J+B+U) abstract container/queue actions. The default has B=0 and
O(mD+J+U) live actions, spread across accepted core rows rather than drained
before enumeration. Projection widths, ordered comparisons, allocations and
owned payloads remain real costs.

With one versus 64 unrelated dead E rows, bucket-incremental empty-delta
aggregate work stays 5→5; neither non-eager policy rebuilds/scans L. A separate diagnostic
uses R(a,x)→S(x,z), with N existing R/S matches, then inserts one new S key
for the last root row. The full child witness leaves root a unbound. At N=1
and N=64, default live actions remain equal (J=1,U=0,one accepted answer),
but `cursor_results_work` grows 21→273. This is evidence of the remaining
root-first completion scan, not D05 performance acceptance. Replace that
growth diagnostic with a justified bounded-transition check when anchored
completions are implemented.

Additional live storage is affected undo/events and stage-local removed keys;
there is no full L rollback clone in non-eager modes. Extracted nodes remain
owned until commit/abort. The count undo saves value addresses, and reverse
undo reinserts later-extracted nodes before restoring earlier saved values.
Pending events are cleared before reinsertion. Indexed before views own local
affected keys and retain the cumulative journal for pins and active writers.

The default still prepares bounded private output before physical publication.
Its public `next()` moves committed records; its public first-row latency
includes all preparation. No spill, durable delivery or unpublished
pause/resume interface is inferred.

## Verification

| Configuration | Result | CTest time |
| --- | --- | --- |
| GCC 13.3 Debug | 59/59 pass | 90.87 s |
| GCC 13.3 Release | 59/59 pass | 11.35 s |
| ASan/UBSan including parser C | 59/59 pass | 417.55 s |
| Clang 18.1.3 C/C++ Debug | 59/59 pass | 69.92 s |
| Fresh source-only Release | 59/59 pass | 10.67 s |

Every final process handle is terminal/successful. The four in-place jobs
have the same unchanged before/after native/build/test fingerprint:
`fba728af74b52b60b7a28db8cfb77383c571dcba40cb2c97b5cafaf215dfc912`.
The fresh configure/build/test took 279.80 s and removed its temporary tree.

All preceding 53 tests remain; two new executables cover indexed epoch views
and comparative live maintenance. Two additional semantic invocations and two
additional fault invocations exercise the comparison policies, for 59 tests.
Warnings remain errors and the sanitizer configuration includes parser C,
leak detection and halt-on-error.

Final targeted preflight passed the comparative fixture and all three semantic
invocations, 4/4 in 14.08 s. Earlier targeted runs passed all three policies'
persistent fault suites and the affected epoch-view/fragment lifecycle tests.

The final Release CLI passes 25 support checks and 34 manual logical states
under Python `-O`. The optional schema audit passes 18 meta-checks, 26
normalized artifacts, 19 identity artifacts, 59 admission artifacts, two
layout/projection artifacts, 31 physical artifacts, three support traces/reports
and two rejected-update reports. Frozen plan/trace/report formats are unchanged;
no new CLI delta-stream protocol is implied.

The [476-input manifest](incremental-live-sources.sha256) covers the preceding
473 ordinary source/build/test/dependency/contract inputs plus this component's
proof note and two new test files. All hashes pass; Refactor.md retains its
original hash. Verification packets/manifests and mutable handoff/ledger are
excluded. Ignored `build/verification/incremental-live-*` logs and per-job JSON
summaries retain the actual commands and full successful CTest output, including
all oracle/fault/cost traces. `incremental-live-summary.json` is the aggregate;
CLI and schema outputs are retained separately with successful exit status.

Reproduction commands:

```sh
cmake --preset debug
cmake --build --preset debug --parallel 2
ctest --preset debug --output-on-failure
cmake --preset release
cmake --build --preset release --parallel 2
ctest --preset release --output-on-failure
cmake --preset sanitize
cmake --build --preset sanitize --parallel 2
ctest --preset sanitize --output-on-failure
cmake -S . -B build/clang-debug
cmake --build build/clang-debug --parallel 2
ctest --test-dir build/clang-debug --output-on-failure
python3 -O tests/integration/support.py build/release/crown .
python3 tools/verify_schemas.py build/release/crown
python3 tools/verify_clean_build.py --configuration Release --parallel 2 --log build/verification/incremental-live-clean-source.log
sha256sum -c docs/verification/incremental-live-sources.sha256
```

## Continuation

D05 still requires anchored completion access and bounded successful-output
scheduling, separate first/result/last proof-to-counter mapping and an accurate
runtime guarantee profile with discovery, journal, comparison and width costs.
D06/O06 require unpublished pause/drain and operational sink/backpressure/
recovery protocols. The ledger retains the full original scope, including
planner, initialization/rebuild, distribution/provenance and release gates.

After the source freeze, the user authorized Astra for complex tasks. Its
read-only design review recommends the anchored cursor/index foundation next
and identifies unresolved insertion initialization for a proposed residual
scheduler. That proposal is recorded in the live argument's continuation
section; it adds no implementation or verified delay claim to this packet.
