# Matching sanitizer and supplemental normalized replay checkpoint 1

Root owns execution. The author compiled/linked all inputs but executed none.
The main sanitizer closure has all 82 project implementation/reference TUs and
ten consumer TUs instrumented with ASan/UBSan; its parser C archive is the
matching pinned native sanitizer build. A separate eleventh consumer exercises
real normalized SQL replay under persistent allocation failure, in both strict
and sanitized configurations against the same held matching archives.

Run the 12 argv records in `root-commands.json` from its stated repository root.
The sanitizer environment is supplied explicitly; record any root override.
This gate is matching sanitized execution plus the two additional normalized
fault executions, not a rerun or replacement of historical strict-1.

Check all four manifests before and after execution: `INPUT_SHA256SUMS`,
`ARTIFACT_SHA256SUMS`, `COMMAND_EVIDENCE_SHA256SUMS`, and
`NORMALIZED_FAULT_SHA256SUMS`. Paths in these manifests resolve from repository
root unless absolute. Compiler dependency aliases can name the same physical
file more than once and must agree on content; they are not distinct inputs
with independent mutation authority. The checkpoint's own manifest resolves
from this checkpoint directory.

The supplemental consumer retains the actual owned normalized program in every
modeled alternative, checks literal memory/depth values, injects every baseline
allocation position with failure persistent through unwind, compares complete
canonical owner and workload fields and prior results, and retries. Native
normalized replay may translate bad_alloc to a native resource diagnostic;
such a failed ranking must return allocation_failure or lowering_limit with no
Result and never fallback. Recoverable cleanup failures may return only the
same complete Result. The parser C allocator is not intercepted by the C++
operator-new harness.

Source/header/implementation/archive bytes are identical to the held strict
closure and independent public test inputs. The new driver/support/recipe do
not modify any strict-1 guarded file. No execution here establishes native C02
registration, a native matrix, C03 calibration, C05 deployment, or S05 totals.
