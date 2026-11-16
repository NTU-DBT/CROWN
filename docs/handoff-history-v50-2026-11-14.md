# CROWN continuation handoff — V50

The full Refactor goal is active: 60 verified /2 in progress (A02/X01) /
16 not started, 78 total. V50 completes the physical-lifetime FIFO foundation;
X01 still needs insertion/mixed declarations and compatible-plan/profile work.
The exact V49 handoff is [preserved](handoff-history-v49-2026-11-14.md).

Start with [update patterns](update_patterns.md),
[V50 verification](verification/update-pattern-fifo-v50-2026-11-14.md),
[source/block guide](code_review.md), [ledger](task_ledger.md) and
[error-handling dispositions](code_specs/error_handling.md).

## Accepted state and evidence

- HEAD: `e369a623517723b3be3ea3e9806779f3c591e7f9`; `.git` remains read-only.
- Seal: `build/verification/human-inspection-v50-progress-v1.json`.
- Frozen source: `build/verification/human-inspection-v50-source-v1`.
- Postcheck: `build/verification/human-inspection-v50-postseal-check-v1.json`.
- Receiving: `build/verification/update-pattern-planning-v50-v1`.
- Entry audit: `build/verification/continuation-v50-entry-v1`.
- Paper/source audit: `build/verification/v50-pattern-proof-audit-v1`.
- Independent code review: `build/verification/v50-physical-fifo-code-review-v1`.

WindowFifoPolicy values 0/1 retain label FIFO; values 2/3 enforce global/per-table
physical full-row lifetime FIFO. Existing birth count IDs preserve lifetime order
after original-label removal. Explicit final-reference withdrawals check actual
oldest rows; whole watermarks simulate all decrements before first effect.
One funded transient integer vector supplies the zero-prefix predecessor check;
no new retained row graph/index or catch is introduced. Codec and diagnostics
preserve exact scope/value names. Ten native-input files change, including five
production paths; the other 350 production paths and CMake registrations remain
V49 bytes. Source/proof and code reviews retain their separate scopes.

Current maps have 755 files /173,036 lines /19,474 blocks; 19,004 contracts cover
all 16,573 nonblank blocks, with 2,901 blank regions only. The 12 new cards,
17 semantic updates, 12 equal-body anchor moves and 362 hash-only updates are received; original authors
are preserved on nonsemantic updates. Generation/checker/local-link checks pass.

## Verification and working commands

Debug native controls pass for the six targeted window/checkpoint/image/context
groups. Final receipts are `x01-physical-fifo-test-debug-v50-v1` (initial six),
`...-v2` (three changed groups pass; Session test expectation fails), and
`...-v3` (corrected Session group passes). Production source is identical across
these test revisions. ASan/UBSan/leaks `x01-physical-fifo-test-sanitizer-v50-v1`
passes 8/8 on all exact final native inputs, including both admission-grant tests.
`x01-physical-fifo-build-production-release-v50-v1` passes with tests OFF.
No whole-current suite, Clang or fresh SDK/benchmark claim is made.

The earlier `...build-release-v50-v1` failed because tests are disabled there;
`...build-debug-v50-v2` rejected a sign-conversion in a new test. Neither is pass
evidence. Debug builds v3/v4 resolve the test corrections. The sticky Session
contract is FIFO error first and input_failed on retry; the production latch
was already correct. Persistent OOM/work/retry/publish tests pass.

```sh
PYTHONDONTWRITEBYTECODE=1 python3 tools/check_code_specs.py
```

After code edits, review affected contracts/callers, reanchor moved exact spans,
regenerate, and check. Do not update hashes alone for changed semantics. Reuse
main Debug `build/w05-debug`, SAN `build/w05-sanitizer`, and production Release
`build/inspection-build-scope-off-v1`. Tests require a testing-enabled build.
All builds/jobs and review agents are terminal at seal.

## Next X01 implementation

Continue the full X01 requirements in the proof packet's `requirements.md`:
actual insertion-only/mixed per-table declarations and admission monitoring;
explicit jointly FIFO scopes; P07/P02-compatible candidate analysis before
ranking; source/query/tree binding; exact committed monitored status/profile;
appropriate persistence and a declared rejection/downgrade policy. The physical
window modes alone do not complete X01. C01 sampling cannot prove a contract.

Physical FIFO can disappear under non-injective occurrence projection; aliases
also need a transfer argument. Per-table FIFO does not imply pair/global FIFO.
Trim/MixDetect cannot supply an accepted height or pattern-bound certificate
after the preserved counterexample. Analyze genuine checked trees and report
sufficient/unknown results with precise premises. No new theorem or public
constant-delay/maintenance bound is enabled here. Include window scans, sorting,
scratch, initialization, variable-width comparisons, output and recovery costs.

A02's project-license/provenance disposition remains open and blocks C04/B01
acceptance. Other extension/experiment cards and R2 retirement/release gates
remain open. V01/V02/bounded V33 W06 retain their documented scope. B05 keeps
its exact finite V48 cohort (19 families at 4 scales, 456 configurations,
1,368 measured plus 456 warmup reports) and preserved RSS/source-successor qualifications.

Completed packets/snapshots/private SDKs/dependency prefixes stay immutable.
Use PYTHONDONTWRITEBYTECODE=1 for repository/helper imports. exec_command needs
sandbox_permissions="require_escalated" because the default launcher is broken.
No approval was rejected. Prefer own-model work and bounded Luna Max tasks;
this pass used one Astra Max for the complex source/proof audit only.
